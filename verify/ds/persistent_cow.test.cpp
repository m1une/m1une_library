#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../acted_monoid/range_add_range_sum.hpp"
#include "../../ds/dsu/persistent_dsu.hpp"
#include "../../ds/dsu/persistent_potentialized_dsu.hpp"
#include "../../ds/bst/persistent_ordered_multiset.hpp"
#include "../../ds/dynamic_array/persistent_dynamic_array.hpp"
#include "../../ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp"
#include "../../ds/dynamic_array/persistent_dynamic_monoid_array.hpp"
#include "../../ds/segtree/persistent_dual_segtree.hpp"
#include "../../ds/segtree/persistent_dynamic_dual_segtree.hpp"
#include "../../ds/segtree/persistent_dynamic_lazy_segtree.hpp"
#include "../../ds/segtree/persistent_dynamic_segtree.hpp"
#include "../../ds/segtree/persistent_lazy_segtree.hpp"
#include "../../ds/segtree/persistent_segtree.hpp"
#include "../../ds/segtree/persistent_segtree_beats.hpp"
#include "../../monoid/add.hpp"
#include "../../utilities/fast_io.hpp"

#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

namespace {

using Add = m1une::monoid::Add<long long>;
using RangeAdd = m1une::acted_monoid::RangeAddRangeSum<long long>;

struct RangeAddBeats : RangeAdd {
    static bool can_apply(const operator_type&, const value_type&) {
        return true;
    }
};

template <class Structure, class Update, class Get>
void check_copy_move_and_reuse(Structure base, Update update, Get get) {
    const std::size_t base_nodes = base.node_count();
    Structure current = base;
    Structure sibling = current;

    update(current, 0);
    assert(get(base) == 0);
    assert(get(sibling) == 0);
    assert(get(current) == 1);

    update(sibling, 9);
    assert(get(base) == 0);
    assert(get(current) == 1);
    assert(get(sibling) == 10);

    const std::size_t after_first_write = current.node_count();
    update(current, 1);
    assert(get(current) == 2);
    assert(current.node_count() == after_first_write);

    Structure snapshot = current;
    update(current, 2);
    assert(get(snapshot) == 2);
    assert(get(current) == 3);
    const std::size_t after_reshare = current.node_count();
    update(current, 3);
    assert(get(snapshot) == 2);
    assert(get(current) == 4);
    assert(current.node_count() == after_reshare);

    Structure moved(std::move(current));
    update(moved, 4);
    assert(get(moved) == 5);
    Structure assigned = base;
    assigned = std::move(moved);
    update(assigned, 5);
    assert(get(assigned) == 6);
    assert(get(base) == 0);

    sibling.release();
    snapshot.release();
    assigned.release();
    assert(base.node_count() == base_nodes);

    Structure reused = base;
    update(reused, 6);
    assert(get(reused) == 7);
    reused.release();
    assert(base.node_count() == base_nodes);
}

void test_segment_trees() {
    using Seg = m1une::ds::PersistentSegtree<Add>;
    check_copy_move_and_reuse(
        Seg(std::vector<long long>(8, 0)),
        [](Seg& seg, int step) { seg.set_inplace(3, step + 1); },
        [](const Seg& seg) { return seg.get(3); }
    );

    using Lazy = m1une::ds::PersistentLazySegtree<RangeAdd>;
    check_copy_move_and_reuse(
        Lazy(std::vector<long long>(8, 0)),
        [](Lazy& seg, int step) { seg.set_inplace(3, RangeAdd::make(step + 1)); },
        [](const Lazy& seg) { return seg.get(3).sum; }
    );

    Lazy base(std::vector<long long>(8, 0));
    Lazy current = base;
    current.apply_inplace(0, 8, 10);
    const std::size_t after_full_cover = current.node_count();
    current.apply_inplace(0, 8, 1);
    assert(current.node_count() == after_full_cover);
    Lazy snapshot = current;
    current.apply_inplace(2, 6, 5);
    current.set_inplace(3, RangeAdd::make(100));
    assert(base.all_prod().sum == 0);
    assert(snapshot.all_prod().sum == 88);
    assert(snapshot.get(3).sum == 11);
    assert(current.get(2).sum == 16);
    assert(current.get(3).sum == 100);

    Lazy persistent = base;
    Lazy inplace = base;
    std::uint64_t state = 1;
    for (int operation = 0; operation < 500; ++operation) {
        state = state * 6364136223846793005ULL + 1;
        int left = int(state % 9);
        state = state * 6364136223846793005ULL + 1;
        int right = int(state % 9);
        if (left > right) std::swap(left, right);
        long long add = static_cast<long long>(operation % 13) - 6;
        persistent = persistent.apply(left, right, add);
        inplace.apply_inplace(left, right, add);
        if (operation % 17 == 0) {
            int index = operation % 8;
            auto value = RangeAdd::make(operation);
            persistent = persistent.set(index, value);
            inplace.set_inplace(index, value);
        }
        auto inplace_values = inplace.to_vector();
        auto persistent_values = persistent.to_vector();
        assert(inplace_values.size() == persistent_values.size());
        for (int i = 0; i < int(inplace_values.size()); ++i) {
            assert(inplace_values[i].sum == persistent_values[i].sum);
        }
    }
    assert(base.all_prod().sum == 0);

    using Dual = m1une::ds::PersistentDualSegtree<Add>;
    Dual dual_base(std::vector<long long>(8, 0));
    Dual dual = dual_base;
    dual.apply_inplace(1, 7, 4);
    dual.apply_inplace(3, 6);
    dual.set_inplace(5, 20);
    assert(dual_base.get(5) == 0);
    assert(dual.get(3) == 10);
    assert(dual.get(5) == 20);

    using Beats = m1une::ds::PersistentSegtreeBeats<RangeAddBeats>;
    Beats beats_base(std::vector<long long>(8, 0));
    Beats beats = beats_base;
    beats.apply_inplace(1, 7, 4);
    const std::size_t beats_nodes = beats.node_count();
    beats.apply_inplace(1, 7, 3);
    assert(beats.node_count() == beats_nodes);
    Beats beats_copy = beats;
    beats.set_inplace(3, RangeAddBeats::make(50));
    assert(beats_base.all_prod().sum == 0);
    assert(beats_copy.get(3).sum == 7);
    assert(beats.get(3).sum == 50);
}

void test_dynamic_segment_trees() {
    using Seg = m1une::ds::PersistentDynamicSegtree<Add>;
    Seg base(-100, 100);
    Seg current = base;
    current.set_inplace(17, 1);
    const std::size_t nodes = current.node_count();
    current.set_inplace(17, 2);
    assert(current.node_count() == nodes);
    Seg copy = current;
    current.set_inplace(17, 3);
    assert(base.get(17) == 0);
    assert(copy.get(17) == 2);
    assert(current.get(17) == 3);

    using Lazy = m1une::ds::PersistentDynamicLazySegtree<RangeAdd>;
    Lazy lazy_base(-64, 64, RangeAdd::make(0));
    Lazy lazy = lazy_base;
    lazy.apply_inplace(-20, 30, 5);
    Lazy lazy_copy = lazy;
    lazy.apply_inplace(-5, 10, 7);
    lazy.set_inplace(0, RangeAdd::make(100));
    assert(lazy_base.get(0).sum == 0);
    assert(lazy_copy.get(0).sum == 5);
    assert(lazy.get(-6).sum == 5);
    assert(lazy.get(-5).sum == 12);
    assert(lazy.get(0).sum == 100);

    using Dual = m1une::ds::PersistentDynamicDualSegtree<Add>;
    Dual dual_base(-64, 64, 0);
    Dual dual = dual_base;
    dual.apply_inplace(-20, 30, 5);
    Dual dual_copy = dual;
    dual.apply_inplace(-5, 10, 7);
    dual.set_inplace(0, 100);
    assert(dual_base.get(0) == 0);
    assert(dual_copy.get(0) == 5);
    assert(dual.get(-5) == 12);
    assert(dual.get(0) == 100);
}

void test_dynamic_arrays() {
    using Array = m1une::ds::PersistentDynamicArray<int>;
    Array base = {0, 1, 2, 3, 4, 5};
    Array reversed = base.reverse(1, 6);
    Array copy = reversed;
    reversed.set_inplace(1, 20);
    const std::size_t nodes = reversed.node_count();
    reversed.set_inplace(1, 21);
    assert(reversed.node_count() == nodes);
    assert(base.to_vector() == (std::vector<int>{0, 1, 2, 3, 4, 5}));
    assert(copy.to_vector() == (std::vector<int>{0, 5, 4, 3, 2, 1}));
    assert(reversed.to_vector() == (std::vector<int>{0, 21, 4, 3, 2, 1}));

    using MonoidArray = m1une::ds::PersistentDynamicMonoidArray<Add>;
    MonoidArray monoid(std::vector<long long>{1, 2, 3, 4});
    MonoidArray monoid_copy = monoid;
    monoid.set_inplace(2, 30);
    assert(monoid_copy.all_prod() == 10);
    assert(monoid.all_prod() == 37);

    using LazyArray = m1une::ds::PersistentDynamicLazyMonoidArray<RangeAdd>;
    LazyArray lazy_base(std::vector<long long>{1, 2, 3, 4, 5, 6});
    LazyArray lazy = lazy_base.apply(1, 6, 10).reverse(0, 5);
    LazyArray lazy_copy = lazy;
    lazy.apply_inplace(1, 5, 7);
    lazy.set_inplace(2, RangeAdd::make(100));
    assert(lazy_base.all_prod().sum == 21);
    std::vector<long long> copy_expected = {15, 14, 13, 12, 1, 16};
    auto copy_values = lazy_copy.to_vector();
    for (int i = 0; i < int(copy_expected.size()); ++i) {
        assert(copy_values[i].sum == copy_expected[i]);
    }
    std::vector<long long> expected = {15, 21, 100, 19, 8, 16};
    auto values = lazy.to_vector();
    for (int i = 0; i < int(expected.size()); ++i) assert(values[i].sum == expected[i]);
    assert(lazy.all_prod().sum == 179);
}

void test_dsu() {
    m1une::ds::PersistentDsu base(8);
    auto current = base;
    assert(current.merge_inplace(0, 1));
    const std::size_t after_merge = current.node_count();
    assert(!current.merge_inplace(0, 1));
    assert(current.node_count() == after_merge);
    auto copy = current;
    assert(current.merge_inplace(1, 2));
    assert(!base.same(0, 1));
    assert(!copy.same(0, 2));
    assert(current.same(0, 2));

    using PotentialDsu = m1une::ds::PersistentPotentializedDsu<Add>;
    PotentialDsu potential_base(8);
    PotentialDsu potential = potential_base;
    assert(potential.merge_inplace(0, 1, 3));
    PotentialDsu potential_copy = potential;
    assert(potential.merge_inplace(1, 2, 4));
    assert(!potential.merge_inplace(0, 2, 8));
    assert(potential.diff(0, 2) == 7);
    assert(!potential_base.same(0, 1));
    assert(!potential_copy.same(0, 2));
}

void test_ordered_multiset() {
    using Multiset = m1une::ds::PersistentOrderedMultiset<int>;
    Multiset base = {1, 2, 2, 3};
    Multiset current = base;
    current.insert_inplace(2, 3);
    const std::size_t after_first_write = current.node_count();
    current.insert_inplace(2);
    assert(current.node_count() == after_first_write);
    Multiset copy = current;
    assert(current.erase_inplace(2));
    assert(base.count(2) == 2);
    assert(copy.count(2) == 6);
    assert(current.count(2) == 5);
    current.insert_inplace(4);
    assert(!base.contains(4));
    assert(current.contains(4));
    assert(current.erase_all_inplace(4));
    assert(!current.contains(4));
    assert(!current.erase_inplace(9));
}

}  // namespace

int main() {
    test_segment_trees();
    test_dynamic_segment_trees();
    test_dynamic_arrays();
    test_dsu();
    test_ordered_multiset();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    long long a, b;
    input >> a >> b;
    output << a + b << '\n';
}
