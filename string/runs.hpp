#ifndef M1UNE_STRING_RUNS_HPP
#define M1UNE_STRING_RUNS_HPP 1

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

namespace m1une {
namespace string {

struct Run {
    int period;
    int left;
    int right;

    bool operator==(const Run&) const = default;
};

namespace internal {

template <class Sequence>
class RunEnumerator {
   private:
    const Sequence& _sequence;
    int _size;
    std::vector<std::vector<std::pair<int, int>>> _candidates;

    template <class Access>
    static std::vector<int> z_algorithm(int length, Access access) {
        std::vector<int> z(length + 1, 0);
        if (length == 0) return z;
        z[0] = length;
        int left = 0;
        int right = 0;
        for (int i = 1; i < length; i++) {
            if (i < right) z[i] = std::min(right - i, z[i - left]);
            while (
                i + z[i] < length &&
                access(z[i]) == access(i + z[i])
            ) {
                z[i]++;
            }
            if (right < i + z[i]) {
                left = i;
                right = i + z[i];
            }
        }
        return z;
    }

    decltype(auto) element(int index, bool reversed) const {
        int original_index = reversed ? _size - 1 - index : index;
        return _sequence[original_index];
    }

    void add_candidate(int period, int left, int right, bool reversed) {
        if (reversed) {
            left = _size - left;
            right = _size - right;
            std::swap(left, right);
        }
        _candidates[period].emplace_back(left, right);
    }

    void collect(int range_left, int range_right, int phase, bool reversed) {
        if (range_right - range_left <= 1) return;
        int middle = (range_left + range_right + phase) / 2;
        collect(range_left, middle, phase, reversed);
        collect(middle, range_right, phase, reversed);

        int left_length = middle - range_left;
        int right_length = range_right - middle;
        std::vector<int> left_z = z_algorithm(left_length, [&](int index) -> decltype(auto) {
            return element(middle - 1 - index, reversed);
        });

        int combined_length = right_length + range_right - range_left;
        std::vector<int> right_z = z_algorithm(combined_length, [&](int index) -> decltype(auto) {
            if (index < right_length) return element(middle + index, reversed);
            return element(range_left + index - right_length, reversed);
        });

        for (int start = middle - 1; start >= range_left; start--) {
            int period = middle - start;
            int extend_left = std::min(start - range_left, left_z[period]);
            int extend_right = std::min(
                range_right - middle,
                right_z[range_right - range_left - period]
            );
            int left = start - extend_left;
            int right = middle + extend_right;
            if (right - left >= 2 * period) {
                add_candidate(period, left, right, reversed);
            }
        }
    }

   public:
    explicit RunEnumerator(const Sequence& sequence)
        : _sequence(sequence),
          _size(int(sequence.size())),
          _candidates(_size / 2 + 1) {}

    std::vector<Run> enumerate() {
        collect(0, _size, 0, true);
        collect(0, _size, 1, false);

        std::set<std::pair<int, int>> used_intervals;
        std::vector<Run> result;
        for (int period = 1; period <= _size / 2; period++) {
            std::vector<std::pair<int, int>>& candidates = _candidates[period];
            std::sort(
                candidates.begin(),
                candidates.end(),
                [](const auto& first, const auto& second) {
                    if (first.first != second.first) {
                        return first.first < second.first;
                    }
                    return first.second > second.second;
                }
            );

            int farthest_right = -1;
            for (const auto& interval : candidates) {
                if (interval.second <= farthest_right) continue;
                farthest_right = interval.second;
                if (!used_intervals.insert(interval).second) continue;
                result.push_back(Run{period, interval.first, interval.second});
            }
        }
        return result;
    }
};

}  // namespace internal

// Returns all runs as (minimum period, maximal half-open interval),
// sorted lexicographically by (period, left, right).
template <class Sequence>
std::vector<Run> enumerate_runs(const Sequence& sequence) {
    return internal::RunEnumerator<Sequence>(sequence).enumerate();
}

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_RUNS_HPP
