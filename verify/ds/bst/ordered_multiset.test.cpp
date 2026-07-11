#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "../../../ds/bst/ordered_multiset.hpp"

#include <cassert>
#include <iostream>
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

void fast_io() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int main() {
    fast_io();
    split_merge_test();

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
