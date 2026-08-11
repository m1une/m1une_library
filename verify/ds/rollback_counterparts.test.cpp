#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../ds/bst/rollback_ordered_multiset.hpp"
#include "../../ds/bst/rollback_ordered_set.hpp"
#include "../../ds/deque/rollback_deque.hpp"
#include "../../ds/dsu/rollback_potentialized_dsu.hpp"
#include "../../ds/dynamic_array/rollback_dynamic_array.hpp"
#include "../../ds/dynamic_array/rollback_dynamic_lazy_monoid_array.hpp"
#include "../../ds/dynamic_array/rollback_dynamic_monoid_array.hpp"
#include "../../ds/queue/rollback_queue.hpp"
#include "../../ds/segtree/rollback_dual_segtree.hpp"
#include "../../ds/segtree/rollback_dynamic_dual_segtree.hpp"
#include "../../ds/segtree/rollback_dynamic_lazy_segtree.hpp"
#include "../../ds/segtree/rollback_dynamic_segtree.hpp"
#include "../../ds/segtree/rollback_lazy_segtree.hpp"
#include "../../ds/segtree/rollback_segtree.hpp"
#include "../../ds/segtree/rollback_segtree_beats.hpp"
#include "../../ds/stack/rollback_stack.hpp"

#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

#include "../../acted_monoid/range_add_range_sum.hpp"
#include "../../beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp"
#include "../../monoid/add.hpp"

namespace {

using Add = m1une::monoid::Add<long long>;
using RangeAddSum = m1une::acted_monoid::RangeAddRangeSum<long long>;

void test_sequence_containers() {
    m1une::ds::RollbackStack<int> stack;
    stack.push(1);
    int stack_state = stack.snapshot();
    stack.emplace(2);
    assert(stack.top() == 2);
    stack.rollback(stack_state);
    assert(stack.top() == 1);

    m1une::ds::RollbackQueue<int> queue;
    queue.push(1);
    int queue_state = queue.snapshot();
    queue.push_back(2);
    queue.pop_front();
    assert(queue.front() == 2);
    queue.rollback(queue_state);
    assert(queue.front() == 1 && queue.back() == 1);

    m1une::ds::RollbackDeque<int> deque;
    deque.push_back(2);
    int deque_state = deque.snapshot();
    deque.emplace_front(1);
    deque.emplace_back(3);
    assert(deque.front() == 1 && deque.back() == 3);
    deque.rollback(deque_state);
    assert(deque.front() == 2 && deque.back() == 2);
}

void test_ordered_containers() {
    m1une::ds::RollbackOrderedSet<int> initialized_set({2, 1});
    assert(initialized_set.to_vector() == std::vector<int>({1, 2}));

    m1une::ds::RollbackOrderedSet<int> set;
    assert(set.insert(3));
    int state = set.snapshot();
    assert(set.insert(1));
    assert(!set.insert(1));
    assert(set.erase(3));
    assert(set.to_vector() == std::vector<int>({1}));
    set.rollback(state);
    assert(set.to_vector() == std::vector<int>({3}));

    m1une::ds::RollbackOrderedMultiset<int> multiset;
    multiset.insert(2, 3);
    state = multiset.snapshot();
    assert(multiset.erase_one(2));
    multiset.insert(1);
    assert(multiset.count(2) == 2);
    multiset.rollback(state);
    assert(multiset.count(2) == 3 && !multiset.contains(1));
    assert(multiset.erase_all(2) == 3);
    assert(multiset.undo());

    m1une::ds::PersistentOrderedMultiset<int> persistent({4, 4});
    m1une::ds::RollbackOrderedMultiset<int> from_persistent(
        std::move(persistent)
    );
    assert(from_persistent.count(4) == 2);
}

void test_dynamic_arrays() {
    m1une::ds::RollbackDynamicArray<int> array(std::vector<int>{1, 2, 3});
    int state = array.snapshot();
    array.insert(1, 5);
    array.reverse(0, 4);
    array.erase(1, 3);
    assert(array.to_vector() == std::vector<int>({3, 1}));
    array.rollback(state);
    assert(array.to_vector() == std::vector<int>({1, 2, 3}));

    m1une::ds::RollbackDynamicMonoidArray<Add> monoid_array(
        std::vector<long long>{1, 2, 3}
    );
    state = monoid_array.snapshot();
    monoid_array.set(1, 7);
    monoid_array.push_back(4);
    assert(monoid_array.all_prod() == 15);
    monoid_array.rollback(state);
    assert(monoid_array.all_prod() == 6);

    m1une::ds::RollbackDynamicLazyMonoidArray<RangeAddSum> lazy_array(
        std::vector<long long>{1, 2, 3}
    );
    state = lazy_array.snapshot();
    lazy_array.apply(0, 2, 4);
    lazy_array.reverse();
    assert(lazy_array.all_prod().sum == 14);
    lazy_array.rollback(state);
    assert(lazy_array.all_prod().sum == 6);
}

void test_segment_trees() {
    m1une::ds::RollbackSegtree<Add> seg(std::vector<long long>{1, 2, 3, 4});
    int state = seg.snapshot();
    std::size_t initial_nodes = seg.node_count();
    seg.set(1, 10);
    assert(seg.all_prod() == 18);
    assert(seg.node_count() > initial_nodes);
    assert(seg.undo());
    assert(seg.all_prod() == 10 && seg.snapshot() == state);
    assert(seg.node_count() == initial_nodes);

    m1une::ds::RollbackLazySegtree<RangeAddSum> lazy(
        std::vector<long long>{1, 2, 3, 4}
    );
    state = lazy.snapshot();
    lazy.apply(1, 4, 5);
    lazy.set(0, RangeAddSum::make(9));
    assert(lazy.all_prod().sum == 33);
    lazy.rollback(state);
    assert(lazy.all_prod().sum == 10);
    auto lazy_source = lazy;
    lazy_source.set(2, RangeAddSum::make(20));
    lazy.copy_range_from(lazy_source, 2, 3);
    assert(lazy.all_prod().sum == 27);
    assert(lazy.undo());
    assert(lazy.all_prod().sum == 10);

    m1une::ds::RollbackDualSegtree<Add> dual(4);
    state = dual.snapshot();
    dual.apply(0, 3, 4);
    dual.set(1, 2);
    assert(dual.get(0) == 4 && dual.get(1) == 2);
    dual.rollback(state);
    assert(dual.get(0) == 0 && dual.get(1) == 0);

    m1une::ds::RollbackDynamicSegtree<Add> dynamic(-10, 10);
    state = dynamic.snapshot();
    dynamic.set(-4, 7);
    dynamic.set(8, 3);
    assert(dynamic.all_prod() == 10);
    dynamic.rollback(state);
    assert(dynamic.all_prod() == 0);

    m1une::ds::RollbackDynamicLazySegtree<RangeAddSum> dynamic_lazy(
        -10, 10, RangeAddSum::id()
    );
    state = dynamic_lazy.snapshot();
    dynamic_lazy.set(-2, RangeAddSum::make(3));
    dynamic_lazy.apply(-2, -1, 4);
    assert(dynamic_lazy.get(-2).sum == 7);
    dynamic_lazy.rollback(state);
    assert(dynamic_lazy.get(-2).sum == 0);

    m1une::ds::RollbackDynamicDualSegtree<Add> dynamic_dual(-10, 10, 0);
    state = dynamic_dual.snapshot();
    dynamic_dual.apply(-3, 5, 7);
    dynamic_dual.set(0, 2);
    assert(dynamic_dual.get(-1) == 7 && dynamic_dual.get(0) == 2);
    dynamic_dual.rollback(state);
    assert(dynamic_dual.get(-1) == 0 && dynamic_dual.get(0) == 0);

    using Beats = m1une::beats_acted_monoid::RangeChminChmaxAddRangeSum<long long>;
    m1une::ds::RollbackSegtreeBeats<Beats> beats(
        std::vector<long long>{1, 5, 3, 7}
    );
    state = beats.snapshot();
    Beats::operator_type chmin;
    chmin.add = 0;
    chmin.lower = Beats::negative_infinity;
    chmin.upper = 4;
    beats.apply(0, 4, chmin);
    assert(beats.all_prod().sum == 12);
    beats.rollback(state);
    assert(beats.all_prod().sum == 16);
    auto beats_source = beats;
    beats_source.set(1, Beats::make(2));
    beats.copy_range_from(beats_source, 1, 2);
    assert(beats.all_prod().sum == 13);
    assert(beats.undo());
    assert(beats.all_prod().sum == 16);
}

void test_potentialized_dsu() {
    m1une::ds::RollbackPotentializedDsu<Add> dsu(5);
    assert(dsu.merge(0, 1, 3));
    int state = dsu.snapshot();
    assert(dsu.merge(1, 2, 4));
    assert(dsu.diff(0, 2) == 7);
    assert(!dsu.merge(0, 2, 8));
    assert(dsu.history_size() == state + 2);
    dsu.rollback(state);
    assert(!dsu.same(0, 2));
    assert(dsu.diff(0, 1) == 3);
    assert(dsu.component_count() == 4);
}

}  // namespace

int main() {
    test_sequence_containers();
    test_ordered_containers();
    test_dynamic_arrays();
    test_segment_trees();
    test_potentialized_dsu();

    long long first, second;
    std::cin >> first >> second;
    std::cout << first + second << '\n';
}
