#ifndef M1UNE_DS_RANGE_QUERY_STATIC_RANGE_MODE_QUERY_HPP
#define M1UNE_DS_RANGE_QUERY_STATIC_RANGE_MODE_QUERY_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

// Static range modes with O(N sqrt N) preprocessing and O(sqrt N) queries.
template <class T>
struct StaticRangeModeQuery {
    using result_type = std::pair<T, int>;

   private:
    int _n;
    int _block_size;
    int _block_count;
    std::vector<T> _values;
    std::vector<int> _rank;
    std::vector<std::vector<int>> _boundary_frequency;
    std::vector<std::vector<int>> _mode;
    std::vector<std::vector<int>> _mode_frequency;
    std::vector<int> _extra_frequency;
    std::vector<unsigned int> _seen_at;
    unsigned int _query_time;

    int block_start(int block) const {
        return std::min(_n, block * _block_size);
    }

    void build_boundary_frequency() {
        int value_count = int(_values.size());
        _boundary_frequency.assign(
            _block_count + 1,
            std::vector<int>(value_count, 0)
        );
        for (int block = 0; block < _block_count; block++) {
            _boundary_frequency[block + 1] = _boundary_frequency[block];
            for (
                int i = block_start(block);
                i < block_start(block + 1);
                i++
            ) {
                _boundary_frequency[block + 1][_rank[i]]++;
            }
        }
    }

    void build_block_modes() {
        int value_count = int(_values.size());
        _mode.assign(
            _block_count,
            std::vector<int>(_block_count + 1, -1)
        );
        _mode_frequency.assign(
            _block_count,
            std::vector<int>(_block_count + 1, 0)
        );

        std::vector<int> frequency(value_count, 0);
        for (int first = 0; first < _block_count; first++) {
            std::fill(frequency.begin(), frequency.end(), 0);
            int best = -1;
            int best_frequency = 0;
            for (int last = first; last < _block_count; last++) {
                for (
                    int i = block_start(last);
                    i < block_start(last + 1);
                    i++
                ) {
                    int value = _rank[i];
                    frequency[value]++;
                    if (frequency[value] > best_frequency) {
                        best = value;
                        best_frequency = frequency[value];
                    }
                }
                _mode[first][last + 1] = best;
                _mode_frequency[first][last + 1] = best_frequency;
            }
        }
    }

   public:
    StaticRangeModeQuery()
        : _n(0),
          _block_size(1),
          _block_count(0),
          _query_time(0) {}

    explicit StaticRangeModeQuery(const std::vector<T>& values)
        : _n(int(values.size())),
          _block_size(1),
          _block_count(0),
          _values(values),
          _query_time(0) {
        if (_n == 0) return;

        _block_size = std::max(
            1,
            int(std::sqrt(static_cast<long double>(_n)))
        );
        while (1LL * _block_size * _block_size < _n) _block_size++;
        _block_count = (_n + _block_size - 1) / _block_size;

        std::sort(_values.begin(), _values.end());
        _values.erase(
            std::unique(_values.begin(), _values.end()),
            _values.end()
        );
        _rank.resize(_n);
        for (int i = 0; i < _n; i++) {
            _rank[i] = int(
                std::lower_bound(_values.begin(), _values.end(), values[i])
                - _values.begin()
            );
        }

        build_boundary_frequency();
        build_block_modes();
        _extra_frequency.assign(_values.size(), 0);
        _seen_at.assign(_values.size(), 0);
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    int block_size() const {
        return _block_size;
    }

    // Returns {a mode, its frequency} for the nonempty range [left, right).
    // The method reuses internal scratch arrays and is therefore non-const.
    result_type query(int left, int right) {
        assert(0 <= left && left < right && right <= _n);

        int first_full = (left + _block_size - 1) / _block_size;
        int last_full = right / _block_size;
        int left_end = std::min(right, block_start(first_full));
        int right_start = std::max(left_end, block_start(last_full));

        int answer = -1;
        int answer_frequency = 0;
        if (first_full < last_full) {
            answer = _mode[first_full][last_full];
            answer_frequency = _mode_frequency[first_full][last_full];
        }

        _query_time++;
        if (_query_time == 0) {
            std::fill(_seen_at.begin(), _seen_at.end(), 0);
            _query_time = 1;
        }
        std::vector<int> touched;
        touched.reserve(left_end - left + right - right_start);
        auto add = [&](int index) {
            int value = _rank[index];
            if (_seen_at[value] != _query_time) {
                _seen_at[value] = _query_time;
                _extra_frequency[value] = 0;
                touched.push_back(value);
            }
            _extra_frequency[value]++;
        };
        for (int i = left; i < left_end; i++) add(i);
        for (int i = right_start; i < right; i++) add(i);

        for (int value : touched) {
            int frequency = _extra_frequency[value];
            if (first_full < last_full) {
                frequency +=
                    _boundary_frequency[last_full][value]
                    - _boundary_frequency[first_full][value];
            }
            if (frequency > answer_frequency) {
                answer = value;
                answer_frequency = frequency;
            }
        }
        assert(answer != -1);
        return {_values[answer], answer_frequency};
    }

    result_type mode(int left, int right) {
        return query(left, right);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_RANGE_QUERY_STATIC_RANGE_MODE_QUERY_HPP
