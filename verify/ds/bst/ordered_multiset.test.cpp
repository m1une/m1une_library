#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "../../../ds/bst/ordered_multiset.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>
#include <vector>

void split_merge_test() {
    m1une::ds::OrderedMultiset<int> tree = {1, 2, 2, 4, 7};
    auto copy = tree;
    auto [left, right] = std::move(tree).split(4);
    std::vector<int> expected_left = {1, 2, 2};
    std::vector<int> expected_right = {4, 7};
    std::vector<int> expected_all = {1, 2, 2, 4, 7};
    assert(left.to_vector() == expected_left);
    assert(right.to_vector() == expected_right);
    tree = std::move(left).merge(std::move(right));
    assert(tree.to_vector() == expected_all);
    assert(copy.to_vector() == expected_all);
}

void randomized_test() {
    m1une::ds::OrderedMultiset<int> tree;
    std::multiset<int> expected;
    std::uint64_t state = 123456789;
    for (int query = 0; query < 10000; ++query) {
        state = state * 6364136223846793005ULL + 1442695040888963407ULL;
        const int key = int(state >> 32) % 500;
        const int type = int(state % 6);
        if (type <= 1) {
            const int multiplicity = int(state % 3) + 1;
            tree.insert(key, multiplicity);
            for (int i = 0; i < multiplicity; ++i) expected.insert(key);
        } else if (type == 2) {
            const bool erased = tree.erase_one(key);
            auto it = expected.find(key);
            assert(erased == (it != expected.end()));
            if (it != expected.end()) expected.erase(it);
        } else if (type == 3) {
            assert(tree.erase_all(key) == int(expected.count(key)));
            expected.erase(key);
        } else if (type == 4) {
            assert(tree.count(key) == int(expected.count(key)));
            assert(tree.order_of_key(key) == int(std::distance(expected.begin(), expected.lower_bound(key))));
        } else {
            auto copy = tree;
            auto [left, right] = std::move(tree).split(key);
            std::vector<int> expected_left(expected.begin(), expected.lower_bound(key));
            std::vector<int> expected_right(expected.lower_bound(key), expected.end());
            assert(left.to_vector() == expected_left);
            assert(right.to_vector() == expected_right);
            tree = std::move(left).merge(std::move(right));
            assert(copy.to_vector() == tree.to_vector());
        }
        assert(tree.size() == int(expected.size()));
        assert(tree.to_vector() == std::vector<int>(expected.begin(), expected.end()));
    }
}

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    fast_io();
    split_merge_test();
    randomized_test();

    int N, Q;
    std::cin >> N >> Q;

    m1une::ds::OrderedMultiset<int> ms;
    for (int i = 0; i < N; i++) {
        int a;
        std::cin >> a;
        ms.insert(a);
    }

    while (Q--) {
        int type, x;
        std::cin >> type >> x;

        if (type == 0) {
            if (!ms.contains(x)) ms.insert(x);
        } else if (type == 1) {
            if (ms.contains(x)) ms.erase_one(x);
        } else if (type == 2) {
            if (ms.size() < x) {
                std::cout << -1 << '\n';
            } else {
                std::cout << ms.kth(x - 1) << '\n';
            }
        } else if (type == 3) {
            std::cout << ms.count_less_equal(x) << '\n';
        } else if (type == 4) {
            const int* ans = ms.max_le(x);
            std::cout << (ans ? *ans : -1) << '\n';
        } else {
            const int* ans = ms.min_ge(x);
            std::cout << (ans ? *ans : -1) << '\n';
        }
    }
}
