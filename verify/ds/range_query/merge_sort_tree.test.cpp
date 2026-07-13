#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"

#include "../../../ds/range_query/merge_sort_tree.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace {

void test_fixed() {
    m1une::ds::MergeSortTree<int> empty;
    assert(empty.empty());
    assert(empty.size() == 0);
    assert(empty.count(0, 0, 7) == 0);
    assert(empty.count_less(0, 0, 7) == 0);
    assert(empty.range_sum(0, 0) == 0);
    assert(empty.sum_less_equal(0, 0, 7) == 0);
    assert(!empty.prev_value(0, 0, 7));
    assert(!empty.next_value(0, 0, 7));

    std::vector<std::string> words = {"pear", "apple", "pear", "plum"};
    m1une::ds::MergeSortTree<std::string> strings(words);
    assert(strings.count(0, 4, std::string("pear")) == 2);
    assert(strings.count(0, 4, std::string("a"), std::string("q")) == 4);
    assert(strings.kth_smallest(0, 4, 0) == "apple");
    assert(strings.prev_value(0, 4, std::string("pear")).value() == "apple");
    assert(strings.next_value(0, 4, std::string("pebble")).value() == "plum");

    std::vector<int> large = {1'000'000'000, 1'000'000'000, -1'000'000'000};
    m1une::ds::MergeSortTree<int, long long> wide(large);
    assert(wide.range_sum(0, 3) == 1'000'000'000LL);
    assert(wide.sum_less_equal(0, 3, 1'000'000'000) == 1'000'000'000LL);
}

void test_randomized() {
    std::uint64_t state = 123456789;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 500; trial++) {
        int size = int(random() % 60);
        std::vector<int> values(size);
        for (int& value : values) value = int(random() % 41) - 20;
        m1une::ds::MergeSortTree<int> tree(values);
        assert(tree.size() == size);
        assert(tree.empty() == values.empty());
        for (int i = 0; i < size; i++) assert(tree[i] == values[i]);

        for (int query = 0; query < 300; query++) {
            int left = int(random() % (size + 1));
            int right = int(random() % (size + 1));
            if (left > right) std::swap(left, right);
            int lower = int(random() % 51) - 25;
            int upper = int(random() % 51) - 25;
            if (lower > upper) std::swap(lower, upper);

            int less = 0;
            int less_equal = 0;
            int equal = 0;
            int between = 0;
            int total_sum = 0;
            int less_sum = 0;
            int less_equal_sum = 0;
            int equal_sum = 0;
            int between_sum = 0;
            std::optional<int> previous;
            std::optional<int> next;
            std::vector<int> sorted;
            for (int i = left; i < right; i++) {
                sorted.push_back(values[i]);
                less += values[i] < lower;
                less_equal += values[i] <= lower;
                equal += values[i] == lower;
                between += lower <= values[i] && values[i] < upper;
                total_sum += values[i];
                if (values[i] < lower) less_sum += values[i];
                if (values[i] <= lower) less_equal_sum += values[i];
                if (values[i] == lower) equal_sum += values[i];
                if (lower <= values[i] && values[i] < upper) between_sum += values[i];
                if (values[i] < lower && (!previous || *previous < values[i])) {
                    previous = values[i];
                }
                if (lower <= values[i] && (!next || values[i] < *next)) {
                    next = values[i];
                }
            }
            std::sort(sorted.begin(), sorted.end());

            assert(tree.count_less(left, right, lower) == less);
            assert(tree.count_less_equal(left, right, lower) == less_equal);
            assert(tree.count(left, right, lower) == equal);
            assert(tree.count(left, right, lower, upper) == between);
            assert(tree.range_sum(left, right) == total_sum);
            assert(tree.sum_less(left, right, lower) == less_sum);
            assert(tree.sum_less_equal(left, right, lower) == less_equal_sum);
            assert(tree.sum(left, right, lower) == equal_sum);
            assert(tree.sum(left, right, lower, upper) == between_sum);
            assert(tree.prev_value(left, right, lower) == previous);
            assert(tree.next_value(left, right, lower) == next);
            if (!sorted.empty()) {
                int k = int(random() % sorted.size());
                assert(tree.kth_smallest(left, right, k) == sorted[k]);
                assert(tree.kth_largest(left, right, k) == sorted[sorted.size() - 1 - k]);
            }
        }
    }
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, query_count;
    std::cin >> n >> query_count;
    std::vector<int> values(n);
    for (int& value : values) std::cin >> value;

    m1une::ds::MergeSortTree<int> tree(values);
    while (query_count--) {
        int left, right, value;
        std::cin >> left >> right >> value;
        std::cout << tree.count(left, right, value) << '\n';
    }
}
