#ifndef M1UNE_STRING_LCE_HPP
#define M1UNE_STRING_LCE_HPP 1

#include <algorithm>
#include <cassert>
#include <string>
#include <utility>
#include <vector>

#include "suffix_array.hpp"

namespace m1une {
namespace string {

template <class Sequence = std::string>
struct LCE {
   private:
    Sequence _sequence;
    std::vector<int> _suffix_array;
    std::vector<int> _rank;
    std::vector<int> _lcp;
    std::vector<int> _log;
    std::vector<std::vector<int>> _table;

    int range_min(int left, int right) const {
        assert(0 <= left && left < right && right <= int(_lcp.size()));
        int k = _log[right - left];
        return std::min(_table[k][left], _table[k][right - (1 << k)]);
    }

    void build() {
        int n = int(_sequence.size());
        _suffix_array = m1une::string::suffix_array(_sequence);
        _rank.assign(n, 0);
        for (int i = 0; i < n; i++) {
            _rank[_suffix_array[i]] = i;
        }

        _lcp = m1une::string::lcp_array(_sequence, _suffix_array);
        int m = int(_lcp.size());
        _log.assign(m + 1, 0);
        for (int i = 2; i <= m; i++) {
            _log[i] = _log[i >> 1] + 1;
        }

        _table.clear();
        if (m == 0) return;
        _table.assign(_log[m] + 1, std::vector<int>());
        _table[0] = _lcp;
        for (int k = 1; k < int(_table.size()); k++) {
            int width = 1 << k;
            int half = width >> 1;
            _table[k].resize(m - width + 1);
            for (int i = 0; i + width <= m; i++) {
                _table[k][i] = std::min(_table[k - 1][i], _table[k - 1][i + half]);
            }
        }
    }

   public:
    LCE() = default;

    explicit LCE(const Sequence& sequence) : _sequence(sequence) {
        build();
    }

    explicit LCE(Sequence&& sequence) : _sequence(std::move(sequence)) {
        build();
    }

    int size() const {
        return int(_sequence.size());
    }

    bool empty() const {
        return _sequence.empty();
    }

    const Sequence& sequence() const {
        return _sequence;
    }

    const std::vector<int>& suffix_array() const {
        return _suffix_array;
    }

    const std::vector<int>& rank() const {
        return _rank;
    }

    const std::vector<int>& lcp_array() const {
        return _lcp;
    }

    int lce(int i, int j) const {
        int n = size();
        assert(0 <= i && i <= n);
        assert(0 <= j && j <= n);
        if (i == j) return n - i;
        if (i == n || j == n) return 0;

        int left = _rank[i];
        int right = _rank[j];
        if (left > right) std::swap(left, right);
        return range_min(left, right);
    }

    int lce(int i, int j, int limit) const {
        assert(0 <= limit);
        return std::min(lce(i, j), limit);
    }

    int lcp(int i, int j) const {
        return lce(i, j);
    }

    int operator()(int i, int j) const {
        return lce(i, j);
    }

    int compare_suffix(int i, int j) const {
        int n = size();
        assert(0 <= i && i <= n);
        assert(0 <= j && j <= n);
        if (i == j) return 0;
        int common = lce(i, j);
        if (i + common == n && j + common == n) return 0;
        if (i + common == n) return -1;
        if (j + common == n) return 1;
        return _sequence[i + common] < _sequence[j + common] ? -1 : 1;
    }

    int compare(int l1, int r1, int l2, int r2) const {
        int n = size();
        assert(0 <= l1 && l1 <= r1 && r1 <= n);
        assert(0 <= l2 && l2 <= r2 && r2 <= n);
        int len1 = r1 - l1;
        int len2 = r2 - l2;
        int common = lce(l1, l2, std::min(len1, len2));
        if (common == len1 && common == len2) return 0;
        if (common == len1) return -1;
        if (common == len2) return 1;
        return _sequence[l1 + common] < _sequence[l2 + common] ? -1 : 1;
    }
};

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_LCE_HPP
