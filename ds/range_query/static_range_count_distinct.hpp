#ifndef M1UNE_DS_RANGE_QUERY_STATIC_RANGE_COUNT_DISTINCT_HPP
#define M1UNE_DS_RANGE_QUERY_STATIC_RANGE_COUNT_DISTINCT_HPP 1

#include "wavelet_matrix.hpp"

#include <algorithm>
#include <cassert>
#include <vector>

namespace m1une {
namespace ds {

// Counts distinct values in static half-open ranges.
template <class T>
struct StaticRangeCountDistinct {
   private:
    int _n;
    WaveletMatrix<int> _previous;

   public:
    StaticRangeCountDistinct() : _n(0), _previous() {}

    explicit StaticRangeCountDistinct(const std::vector<T>& values)
        : _n(int(values.size())), _previous() {
        if (_n == 0) return;

        std::vector<T> compressed = values;
        std::sort(compressed.begin(), compressed.end());
        compressed.erase(
            std::unique(compressed.begin(), compressed.end()),
            compressed.end()
        );

        std::vector<int> last(compressed.size(), -1);
        std::vector<int> previous(_n);
        for (int i = 0; i < _n; i++) {
            int rank = int(
                std::lower_bound(
                    compressed.begin(),
                    compressed.end(),
                    values[i]
                ) - compressed.begin()
            );
            previous[i] = last[rank];
            last[rank] = i;
        }
        _previous = WaveletMatrix<int>(previous);
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    int query(int left, int right) const {
        assert(0 <= left && left <= right && right <= _n);
        if (left == right) return 0;
        return _previous.range_freq(left, right, left);
    }

    int count_distinct(int left, int right) const {
        return query(left, right);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_RANGE_QUERY_STATIC_RANGE_COUNT_DISTINCT_HPP
