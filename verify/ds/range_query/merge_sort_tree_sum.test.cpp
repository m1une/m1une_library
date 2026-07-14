#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound"

#include "../../../ds/range_query/merge_sort_tree.hpp"

#include "../../../utilities/fast_io.hpp"
#include <vector>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int n, query_count;
    fast_input >> n >> query_count;
    std::vector<int> values(n);
    for (int& value : values) fast_input >> value;

    m1une::ds::MergeSortTree<int, long long> tree(values);
    while (query_count--) {
        int left, right, upper;
        fast_input >> left >> right >> upper;
        fast_output << tree.count_less_equal(left, right, upper) << ' '
                  << tree.sum_less_equal(left, right, upper) << '\n';
    }
}
