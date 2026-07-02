#ifndef M1UNE_SEQUENCE_SUBSET_SUM_HPP
#define M1UNE_SEQUENCE_SUBSET_SUM_HPP 1

#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

namespace m1une {
namespace sequence {

namespace internal {

template <typename T>
std::vector<T> enumerate_sorted_subset_sums(
    const std::vector<T>& values,
    int left,
    int right
) {
    std::vector<T> sums(1, T{});
    std::vector<T> merged;

    for (int i = left; i < right; ++i) {
        const std::size_t size = sums.size();
        merged.clear();
        merged.reserve(size * 2);

        std::size_t without = 0;
        std::size_t with = 0;
        while (without < size && with < size) {
            const T with_current = sums[with] + values[i];
            if (with_current < sums[without]) {
                merged.push_back(with_current);
                ++with;
            } else {
                merged.push_back(sums[without]);
                ++without;
            }
        }
        while (without < size) {
            merged.push_back(sums[without]);
            ++without;
        }
        while (with < size) {
            merged.push_back(sums[with] + values[i]);
            ++with;
        }
        sums.swap(merged);
    }

    return sums;
}

}  // namespace internal

// Returns the sorted subset sums of values[0, n / 2) and values[n / 2, n).
template <typename T>
std::pair<std::vector<T>, std::vector<T>> enumerate_half_subset_sums(
    const std::vector<T>& values
) {
    const int n = int(values.size());
    const int middle = n / 2;
    return {
        internal::enumerate_sorted_subset_sums(values, 0, middle),
        internal::enumerate_sorted_subset_sums(values, middle, n)
    };
}

// Returns the maximum subset sum not exceeding limit.
template <typename T>
T maximum_subset_sum(const std::vector<T>& values, const T& limit) {
    assert(!(limit < T{}));
    auto [left_sums, right_sums] = enumerate_half_subset_sums(values);

    T answer{};
    std::size_t right_count = right_sums.size();
    for (const T& left : left_sums) {
        while (
            right_count > 0 &&
            limit < left + right_sums[right_count - 1]
        ) {
            --right_count;
        }
        if (right_count == 0) break;

        const T candidate = left + right_sums[right_count - 1];
        if (answer < candidate) answer = candidate;
    }
    return answer;
}

}  // namespace sequence
}  // namespace m1une

#endif  // M1UNE_SEQUENCE_SUBSET_SUM_HPP
