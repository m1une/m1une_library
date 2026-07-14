#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include "../../../algo/enumeration/segtree_range.hpp"

#include <bit>
#include <cassert>
#include <cstdint>
#include "../../../utilities/fast_io.hpp"
#include <limits>
#include <random>
#include <utility>
#include <vector>

namespace {

void naive_split_impl(
    int query_left, int query_right, int left, int right,
    std::vector<std::pair<int, int>>& result
) {
    if (query_right <= left || right <= query_left) return;
    if (query_left <= left && right <= query_right) {
        result.emplace_back(left, right);
        return;
    }
    const int middle = (left + right) / 2;
    naive_split_impl(query_left, query_right, left, middle, result);
    naive_split_impl(query_left, query_right, middle, right, result);
}

std::vector<std::pair<int, int>> naive_split(int left, int right) {
    std::vector<std::pair<int, int>> result;
    if (left == right) return result;
    int size = 1;
    while (size < right) size *= 2;
    naive_split_impl(left, right, 0, size, result);
    return result;
}

void check_range(int left, int right) {
    const auto ranges = m1une::algo::split_segtree_range(left, right);
    int position = left;
    for (auto [range_left, range_right] : ranges) {
        assert(range_left == position);
        assert(range_left < range_right);
        const unsigned length = unsigned(range_right - range_left);
        assert(std::has_single_bit(length));
        assert(range_left % int(length) == 0);

        const int parent_length = 2 * int(length);
        const int parent_left = range_left / parent_length * parent_length;
        assert(!(left <= parent_left &&
                 parent_left + parent_length <= right));
        position = range_right;
    }
    assert(position == right);
    assert(ranges == naive_split(left, right));
}

void fixed_tests() {
    std::vector<std::pair<int, int>> expected;
    expected.emplace_back(3, 4);
    expected.emplace_back(4, 8);
    expected.emplace_back(8, 12);
    expected.emplace_back(12, 13);
    assert(m1une::algo::split_segtree_range(3, 13) == expected);
    assert(m1une::algo::split_segtree_range(5, 5).empty());

    const auto whole = m1une::algo::split_segtree_range(0, 16);
    assert(whole.size() == 1);
    assert(whole.front().first == 0);
    assert(whole.front().second == 16);

    const auto wide = m1une::algo::split_segtree_range(
        std::uint64_t(0), std::numeric_limits<std::uint64_t>::max()
    );
    assert(wide.size() == 64);
    assert(wide.front().first == 0);
    assert(wide.front().second == (std::uint64_t(1) << 63));
    assert(wide.back().first ==
           std::numeric_limits<std::uint64_t>::max() - 1);
    assert(wide.back().second == std::numeric_limits<std::uint64_t>::max());
}

void exhaustive_tests() {
    for (int right = 0; right <= 256; ++right) {
        for (int left = 0; left <= right; ++left) {
            check_range(left, right);
        }
    }
}

void randomized_tests() {
    std::mt19937 random(0x243f6a88U);
    for (int trial = 0; trial < 20000; ++trial) {
        int left = int(random() % (1U << 20));
        int right = int(random() % (1U << 20));
        if (left > right) std::swap(left, right);
        check_range(left, right);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    fixed_tests();
    exhaustive_tests();
    randomized_tests();
    int n, query_count;
    if (!fast_input.read(n, query_count)) return 0;
    std::vector<long long> prefix_sum(n + 1);
    for (int i = 0; i < n; ++i) {
        long long value;
        fast_input >> value;
        prefix_sum[i + 1] = prefix_sum[i] + value;
    }

    while (query_count--) {
        int left, right;
        fast_input >> left >> right;
        long long answer = 0;
        for (auto [range_left, range_right] :
             m1une::algo::split_segtree_range(left, right)) {
            answer += prefix_sum[range_right] - prefix_sum[range_left];
        }
        fast_output << answer << '\n';
    }
}
