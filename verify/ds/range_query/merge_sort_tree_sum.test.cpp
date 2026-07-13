#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound"

#include "../../../ds/range_query/merge_sort_tree.hpp"

#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, query_count;
    std::cin >> n >> query_count;
    std::vector<int> values(n);
    for (int& value : values) std::cin >> value;

    m1une::ds::MergeSortTree<int, long long> tree(values);
    while (query_count--) {
        int left, right, upper;
        std::cin >> left >> right >> upper;
        std::cout << tree.count_less_equal(left, right, upper) << ' '
                  << tree.sum_less_equal(left, right, upper) << '\n';
    }
}
