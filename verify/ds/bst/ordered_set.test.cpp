#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "../../../ds/bst/ordered_set.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>
#include <vector>

void randomized_test() {
    m1une::ds::OrderedSet<int> tree;
    std::set<int> expected;
    std::uint64_t state = 123456789;
    for (int query = 0; query < 10000; ++query) {
        state = state * 6364136223846793005ULL + 1442695040888963407ULL;
        const int key = int(state >> 32) % 1000;
        const int type = int(state % 5);
        if (type <= 1) {
            assert(tree.insert(key) == expected.insert(key).second);
        } else if (type == 2) {
            assert(tree.erase(key) == (expected.erase(key) != 0));
        } else if (type == 3) {
            assert(tree.contains(key) == expected.contains(key));
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
    randomized_test();

    m1une::ds::OrderedSet<int> split_test = {1, 3, 5};
    auto [small, large] = std::move(split_test).split(3);
    split_test = std::move(small).merge(std::move(large));
    assert(split_test.size() == 3 && split_test.kth(1) == 3);

    int N, Q;
    std::cin >> N >> Q;

    m1une::ds::OrderedSet<int> st;
    for (int i = 0; i < N; i++) {
        int a;
        std::cin >> a;
        st.insert(a);
    }

    while (Q--) {
        int type, x;
        std::cin >> type >> x;

        if (type == 0) {
            st.insert(x);
        } else if (type == 1) {
            st.erase(x);
        } else if (type == 2) {
            if (st.size() < x) {
                std::cout << -1 << '\n';
            } else {
                std::cout << st.kth(x - 1) << '\n';
            }
        } else if (type == 3) {
            std::cout << st.count_less_equal(x) << '\n';
        } else if (type == 4) {
            const int* ans = st.max_le(x);
            std::cout << (ans ? *ans : -1) << '\n';
        } else {
            const int* ans = st.min_ge(x);
            std::cout << (ans ? *ans : -1) << '\n';
        }
    }
}
