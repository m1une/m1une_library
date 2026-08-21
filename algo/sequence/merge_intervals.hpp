#ifndef M1UNE_ALGO_SEQUENCE_MERGE_INTERVALS_HPP
#define M1UNE_ALGO_SEQUENCE_MERGE_INTERVALS_HPP 1

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

namespace m1une {
namespace algo {

// Returns the union of half-open intervals as sorted, disjoint intervals.
template <typename T>
std::vector<std::pair<T, T>> merge_intervals(
    std::vector<std::pair<T, T>> intervals
) {
    for (const auto& [left, right] : intervals) {
        if (right < left) assert(false);
    }

    std::sort(
        intervals.begin(),
        intervals.end(),
        [](const auto& lhs, const auto& rhs) {
            if (lhs.first < rhs.first) return true;
            if (rhs.first < lhs.first) return false;
            return lhs.second < rhs.second;
        }
    );

    std::size_t result_size = 0;
    for (std::size_t index = 0; index < intervals.size(); ++index) {
        auto& [left, right] = intervals[index];
        if (!(left < right)) continue;
        if (result_size == 0 || intervals[result_size - 1].second < left) {
            if (result_size != index) {
                intervals[result_size] = std::move(intervals[index]);
            }
            ++result_size;
        } else if (intervals[result_size - 1].second < right) {
            intervals[result_size - 1].second = std::move(right);
        }
    }
    intervals.erase(intervals.begin() + result_size, intervals.end());
    return intervals;
}

}  // namespace algo
}  // namespace m1une

#endif  // M1UNE_ALGO_SEQUENCE_MERGE_INTERVALS_HPP
