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

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "../../acted_monoid/range_add_range_sum.hpp"
#include "../../beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp"
#include "../../monoid/add.hpp"

namespace {

using Add = m1une::monoid::Add<long long>;
using RangeAddSum = m1une::acted_monoid::RangeAddRangeSum<long long>;

void assert_lazy_array(
    m1une::ds::RollbackDynamicLazyMonoidArray<RangeAddSum>& array,
    const std::vector<long long>& expected
) {
    std::vector<RangeAddSum::value_type> values = array.to_vector();
    assert(values.size() == expected.size());
    for (int index = 0; index < int(values.size()); ++index) {
        assert(values[index].sum == expected[index]);
        assert(values[index].size == 1);
    }
}

void test_sequence_containers() {
    m1une::ds::RollbackStack<int> stack;
    stack.push(1);
    int outer = stack.snapshot();
    stack.emplace(2);
    int inner = stack.snapshot();
    stack.push(3);
    stack.rollback(inner);
    assert(stack.top() == 2 && stack.snapshot_count() == inner);
    stack.pop();
    stack.rollback(outer);
    assert(stack.top() == 1 && stack.snapshot_count() == outer);
    stack.push(4);
    stack.rollback(outer);
    assert(stack.top() == 1);

    m1une::ds::RollbackQueue<int> queue;
    queue.push(1);
    outer = queue.snapshot();
    queue.push_back(2);
    queue.pop_front();
    assert(queue.front() == 2);
    queue.rollback(outer);
    assert(queue.front() == 1 && queue.back() == 1);

    m1une::ds::RollbackDeque<int> deque;
    deque.push_back(2);
    outer = deque.snapshot();
    deque.emplace_front(1);
    deque.emplace_back(3);
    deque.pop_front();
    assert(deque.front() == 2 && deque.back() == 3);
    deque.rollback(outer);
    assert(deque.front() == 2 && deque.back() == 2);
}

void test_ordered_containers() {
    m1une::ds::RollbackOrderedSet<int> set({2, 1});
    int outer = set.snapshot();
    assert(set.insert(3));
    assert(!set.insert(3));
    assert(set.erase(1));
    int inner = set.snapshot();
    set.clear();
    set.rollback(inner);
    assert(set.to_vector() == std::vector<int>({2, 3}));
    set.rollback(outer);
    assert(set.to_vector() == std::vector<int>({1, 2}));

    m1une::ds::RollbackOrderedMultiset<int> multiset({2, 2, 3});
    outer = multiset.snapshot();
    assert(multiset.erase_one(2));
    multiset.insert(1, 3);
    assert(multiset.erase_all(3) == 1);
    assert(multiset.count(1) == 3 && multiset.count(2) == 1);
    multiset.rollback(outer);
    assert(multiset.to_vector() == std::vector<int>({2, 2, 3}));
}

void test_dynamic_arrays() {
    m1une::ds::RollbackDynamicArray<int> array(std::vector<int>{1, 2, 3});
    int outer = array.snapshot();
    array.insert(1, 5);
    array.reverse(0, 4);
    array.erase(1, 3);
    assert(array.to_vector() == std::vector<int>({3, 1}));
    array.rollback(outer);
    assert(array.to_vector() == std::vector<int>({1, 2, 3}));

    m1une::ds::RollbackDynamicMonoidArray<Add> monoid_array(
        std::vector<long long>{1, 2, 3}
    );
    outer = monoid_array.snapshot();
    monoid_array.set(1, 7);
    monoid_array.push_back(4);
    assert(monoid_array.all_prod() == 15);
    monoid_array.rollback(outer);
    assert(monoid_array.to_vector() == std::vector<long long>({1, 2, 3}));

    m1une::ds::RollbackDynamicLazyMonoidArray<RangeAddSum> lazy_array(
        std::vector<long long>{1, 2, 3, 4}
    );
    outer = lazy_array.snapshot();
    lazy_array.apply(0, 3, 4);
    lazy_array.reverse(1, 4);
    lazy_array.insert(2, RangeAddSum::make(10));
    lazy_array.erase(0);
    assert(lazy_array.all_prod().sum == 27);
    int inner = lazy_array.snapshot();
    lazy_array.clear();
    assert(lazy_array.empty());
    lazy_array.rollback(inner);
    assert(lazy_array.all_prod().sum == 27);
    lazy_array.rollback(outer);
    std::vector<RangeAddSum::value_type> restored = lazy_array.to_vector();
    assert(restored.size() == 4);
    for (int index = 0; index < 4; ++index) {
        assert(restored[index].sum == index + 1);
        assert(restored[index].size == 1);
    }
}

void randomized_lazy_array_test() {
    std::mt19937 random(0);
    std::vector<long long> naive = {0, 1, 2, 3, 4, 5};
    m1une::ds::RollbackDynamicLazyMonoidArray<RangeAddSum> array(naive);
    for (int round = 0; round < 80; ++round) {
        int state = array.snapshot();
        std::vector<long long> saved = naive;
        for (int step = 0; step < 35; ++step) {
            int type = int(random() % 5);
            if (type == 0 && !naive.empty()) {
                int pos = int(random() % naive.size());
                long long value = int(random() % 31) - 15;
                array.set(pos, RangeAddSum::make(value));
                naive[pos] = value;
            } else if (type == 1) {
                int left = int(random() % (naive.size() + 1));
                int right = left + int(random() % (naive.size() - left + 1));
                long long add = int(random() % 11) - 5;
                array.apply(left, right, add);
                for (int index = left; index < right; ++index) naive[index] += add;
            } else if (type == 2) {
                int left = int(random() % (naive.size() + 1));
                int right = left + int(random() % (naive.size() - left + 1));
                array.reverse(left, right);
                std::reverse(naive.begin() + left, naive.begin() + right);
            } else if (type == 3) {
                int pos = int(random() % (naive.size() + 1));
                std::vector<long long> raw_values = {
                    int(random() % 21) - 10,
                    int(random() % 21) - 10
                };
                std::vector<RangeAddSum::value_type> values;
                for (long long value : raw_values) {
                    values.push_back(RangeAddSum::make(value));
                }
                array.insert(pos, std::move(values));
                naive.insert(
                    naive.begin() + pos, raw_values.begin(), raw_values.end()
                );
            } else if (!naive.empty()) {
                int pos = int(random() % naive.size());
                array.erase(pos);
                naive.erase(naive.begin() + pos);
            }
            assert_lazy_array(array, naive);
        }
        array.rollback(state);
        naive = std::move(saved);
        assert_lazy_array(array, naive);
        array.clear_history();
    }
}

void test_segment_trees() {
    m1une::ds::RollbackSegtree<Add> seg(std::vector<long long>{1, 2, 3, 4});
    int outer = seg.snapshot();
    seg.set(1, 10);
    seg.set(1, 12);
    assert(seg.all_prod() == 20);
    int inner = seg.snapshot();
    seg.set(0, 8);
    seg.rollback(inner);
    assert(seg.all_prod() == 20);
    seg.rollback(outer);
    assert(seg.all_prod() == 10);

    m1une::ds::RollbackLazySegtree<RangeAddSum> lazy(
        std::vector<long long>{1, 2, 3, 4}
    );
    outer = lazy.snapshot();
    lazy.apply(1, 4, 5);
    lazy.set(0, RangeAddSum::make(9));
    assert(lazy.all_prod().sum == 33);
    assert(lazy.prod(1, 3).sum == 15);
    lazy.rollback(outer);
    assert(lazy.all_prod().sum == 10);

    m1une::ds::RollbackDualSegtree<Add> dual(4);
    outer = dual.snapshot();
    dual.apply(0, 3, 4);
    dual.set(1, 2);
    assert(dual.get(0) == 4 && dual.get(1) == 2);
    dual.rollback(outer);
    assert(dual.get(0) == 0 && dual.get(1) == 0);

    m1une::ds::RollbackDynamicSegtree<Add> dynamic(-10, 10);
    outer = dynamic.snapshot();
    dynamic.set(-4, 7);
    dynamic.set(8, 3);
    assert(dynamic.all_prod() == 10);
    dynamic.rollback(outer);
    assert(dynamic.all_prod() == 0 && dynamic.node_count() == 0);

    m1une::ds::RollbackDynamicLazySegtree<RangeAddSum> dynamic_lazy(
        -10, 10, RangeAddSum::id()
    );
    outer = dynamic_lazy.snapshot();
    dynamic_lazy.set(-2, RangeAddSum::make(3));
    dynamic_lazy.apply(-3, 2, 4);
    assert(dynamic_lazy.get(-2).sum == 7);
    assert(dynamic_lazy.prod(-3, 2).sum == 7);
    dynamic_lazy.rollback(outer);
    assert(dynamic_lazy.get(-2).sum == 0 && dynamic_lazy.node_count() == 0);

    m1une::ds::RollbackDynamicDualSegtree<Add> dynamic_dual(-10, 10, 0);
    outer = dynamic_dual.snapshot();
    dynamic_dual.apply(-3, 5, 7);
    dynamic_dual.set(0, 2);
    assert(dynamic_dual.get(-1) == 7 && dynamic_dual.get(0) == 2);
    dynamic_dual.rollback(outer);
    assert(dynamic_dual.get(-1) == 0 && dynamic_dual.get(0) == 0);

    using Beats = m1une::beats_acted_monoid::RangeChminChmaxAddRangeSum<long long>;
    m1une::ds::RollbackSegtreeBeats<Beats> beats(
        std::vector<long long>{1, 5, 3, 7}
    );
    outer = beats.snapshot();
    Beats::operator_type chmin;
    chmin.add = 0;
    chmin.lower = Beats::negative_infinity;
    chmin.upper = 4;
    beats.apply(0, 4, chmin);
    assert(beats.all_prod().sum == 12);
    assert(beats.prod(1, 4).sum == 11);
    beats.rollback(outer);
    assert(beats.all_prod().sum == 16);
}

void randomized_segment_tree_test() {
    using Beats = m1une::beats_acted_monoid::RangeChminChmaxAddRangeSum<long long>;
    std::mt19937 random(1);
    constexpr int size = 24;
    std::vector<long long> naive(size);
    std::vector<long long> lazy_naive(size);
    m1une::ds::RollbackLazySegtree<RangeAddSum> lazy(lazy_naive);
    m1une::ds::RollbackSegtreeBeats<Beats> beats(naive);

    for (int round = 0; round < 70; ++round) {
        int lazy_state = lazy.snapshot();
        int beats_state = beats.snapshot();
        std::vector<long long> saved = naive;
        std::vector<long long> lazy_saved = lazy_naive;
        for (int step = 0; step < 45; ++step) {
            int type = int(random() % 3);
            int left = int(random() % size);
            int right = left + 1 + int(random() % (size - left));
            if (type == 0) {
                long long add = int(random() % 17) - 8;
                lazy.apply(left, right, add);
                Beats::operator_type action;
                action.add = add;
                action.lower = Beats::negative_infinity;
                action.upper = Beats::positive_infinity;
                beats.apply(left, right, action);
                for (int index = left; index < right; ++index) naive[index] += add;
                for (int index = left; index < right; ++index) lazy_naive[index] += add;
            } else if (type == 1) {
                long long value = int(random() % 41) - 20;
                lazy.set(left, RangeAddSum::make(value));
                beats.set(left, Beats::make(value));
                naive[left] = value;
                lazy_naive[left] = value;
            } else {
                long long upper = int(random() % 31) - 15;
                Beats::operator_type action;
                action.add = 0;
                action.lower = Beats::negative_infinity;
                action.upper = upper;
                beats.apply(left, right, action);
                for (int index = left; index < right; ++index) {
                    naive[index] = std::min(naive[index], upper);
                }
            }

            long long sum = 0;
            for (long long value : naive) sum += value;
            assert(beats.all_prod().sum == sum);
            long long lazy_sum = 0;
            for (long long value : lazy_naive) lazy_sum += value;
            assert(lazy.all_prod().sum == lazy_sum);
        }
        beats.rollback(beats_state);
        lazy.rollback(lazy_state);
        naive = std::move(saved);
        lazy_naive = std::move(lazy_saved);
        long long sum = 0;
        for (long long value : naive) sum += value;
        assert(beats.all_prod().sum == sum);
        long long lazy_sum = 0;
        for (long long value : lazy_naive) lazy_sum += value;
        assert(lazy.all_prod().sum == lazy_sum);
        beats.clear_history();
        lazy.clear_history();
    }
}

void test_potentialized_dsu() {
    m1une::ds::RollbackPotentializedDsu<Add> dsu(5);
    assert(dsu.merge(0, 1, 3));
    int outer = dsu.snapshot();
    assert(dsu.merge(1, 2, 4));
    assert(dsu.diff(0, 2) == 7);
    assert(!dsu.merge(0, 2, 8));
    int inner = dsu.snapshot();
    assert(dsu.merge(3, 4, -2));
    dsu.rollback(inner);
    assert(!dsu.same(3, 4));
    dsu.rollback(outer);
    assert(!dsu.same(0, 2));
    assert(dsu.diff(0, 1) == 3);
    assert(dsu.component_count() == 4);
}

}  // namespace

int main() {
    test_sequence_containers();
    test_ordered_containers();
    test_dynamic_arrays();
    randomized_lazy_array_test();
    test_segment_trees();
    randomized_segment_tree_test();
    test_potentialized_dsu();

    long long first, second;
    std::cin >> first >> second;
    std::cout << first + second << '\n';
}
