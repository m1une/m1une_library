#ifndef M1UNE_DS_RANGE_QUERY_RANGE_LIS_QUERY_HPP
#define M1UNE_DS_RANGE_QUERY_RANGE_LIS_QUERY_HPP 1

#include "wavelet_matrix.hpp"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

namespace range_lis_query_internal {

constexpr int none = -1;
using Permutation = std::vector<int>;
using Iterator = Permutation::iterator;

inline Permutation inverse(const Permutation& permutation) {
    int n = int(permutation.size());
    Permutation result(n, none);
    for (int i = 0; i < n; i++) {
        if (permutation[i] != none) result[permutation[i]] = i;
    }
    return result;
}

// Distance multiplication of two unit-Monge matrices, represented by their
// permutations. `workspace` must have the size used by subunit_monge_product.
inline void unit_monge_product(
    int n,
    Iterator workspace,
    Iterator first,
    Iterator second
) {
    if (n == 1) {
        workspace[0] = 0;
        return;
    }

    Iterator result_row = workspace;
    workspace += n;
    Iterator result_column = workspace;
    workspace += n;

    auto map_half = [=](int length, const auto& belongs, const auto& map) {
        Iterator first_half = workspace;
        Iterator first_position = workspace + length;
        Iterator second_half = workspace + 2 * length;
        Iterator second_position = workspace + 3 * length;

        auto split = [=](Iterator source, Iterator half, Iterator position) {
            for (int i = 0; i < n; i++) {
                if (belongs(source[i])) {
                    *half++ = map(source[i]);
                    *position++ = i;
                }
            }
        };
        split(first, first_half, first_position);
        split(second, second_half, second_position);

        Iterator product = workspace + 4 * length;
        unit_monge_product(
            length,
            product,
            first_half,
            second_half
        );
        for (int i = 0; i < length; i++) {
            int row = first_position[i];
            int column = second_position[product[i]];
            result_row[row] = column;
            result_column[column] = row;
        }
    };

    int middle = n / 2;
    map_half(
        middle,
        [middle](int value) { return value < middle; },
        [](int value) { return value; }
    );
    map_half(
        n - middle,
        [middle](int value) { return value >= middle; },
        [middle](int value) { return value - middle; }
    );

    struct DiagonalIterator {
        int delta = 0;
        int column = 0;
    };

    int row = n;
    auto move_right = [&](DiagonalIterator& iterator) {
        if (second[iterator.column] < middle) {
            if (result_column[iterator.column] >= row) iterator.delta++;
        } else {
            if (result_column[iterator.column] < row) iterator.delta++;
        }
        iterator.column++;
    };
    auto move_up = [&](DiagonalIterator& iterator) {
        if (first[row] < middle) {
            if (result_row[row] >= iterator.column) iterator.delta--;
        } else {
            if (result_row[row] < iterator.column) iterator.delta--;
        }
    };

    DiagonalIterator negative;
    DiagonalIterator positive;
    while (row != 0) {
        while (positive.column != n) {
            DiagonalIterator next = positive;
            move_right(next);
            if (next.delta != 0) break;
            positive = next;
        }
        row--;
        move_up(negative);
        move_up(positive);
        while (negative.delta != 0) move_right(negative);
        if (negative.column > positive.column) {
            result_row[row] = positive.column;
        }
    }
}

inline int workspace_size(int n) {
    int result = 1;
    while (n > 1) {
        result += 2 * n;
        n = (n + 1) / 2;
        result += 4 * n;
    }
    return result;
}

inline Permutation subunit_monge_product(
    Permutation first,
    Permutation second
) {
    int n = int(first.size());
    Permutation first_inverse = inverse(first);
    Permutation second_inverse = inverse(second);
    std::swap(second, second_inverse);

    Permutation first_map;
    Permutation second_map;
    for (int i = n - 1; i >= 0; i--) {
        if (first[i] != none) {
            first_map.push_back(i);
            first[n - int(first_map.size())] = first[i];
        }
    }
    std::reverse(first_map.begin(), first_map.end());

    int missing = 0;
    for (int i = 0; i < n; i++) {
        if (first_inverse[i] == none) first[missing++] = i;
    }
    for (int i = 0; i < n; i++) {
        if (second[i] != none) {
            second[int(second_map.size())] = second[i];
            second_map.push_back(i);
        }
    }
    missing = int(second_map.size());
    for (int i = 0; i < n; i++) {
        if (second_inverse[i] == none) second[missing++] = i;
    }

    Permutation workspace(workspace_size(n));
    unit_monge_product(
        n,
        workspace.begin(),
        first.begin(),
        second.begin()
    );

    Permutation result(n, none);
    int first_count = int(first_map.size());
    int second_count = int(second_map.size());
    for (int i = 0; i < first_count; i++) {
        int mapped = workspace[n - first_count + i];
        if (mapped < second_count) {
            result[first_map[i]] = second_map[mapped];
        }
    }
    return result;
}

inline Permutation seaweed_doubling(const Permutation& permutation) {
    int n = int(permutation.size());
    if (n == 1) return Permutation(1, none);

    int middle = n / 2;
    Permutation lower;
    Permutation upper;
    Permutation lower_map;
    Permutation upper_map;
    for (int i = 0; i < n; i++) {
        int value = permutation[i];
        if (value < middle) {
            lower.push_back(value);
            lower_map.push_back(i);
        } else {
            upper.push_back(value - middle);
            upper_map.push_back(i);
        }
    }

    lower = seaweed_doubling(lower);
    upper = seaweed_doubling(upper);
    Permutation lower_padded(n);
    Permutation upper_padded(n);
    std::iota(lower_padded.begin(), lower_padded.end(), 0);
    std::iota(upper_padded.begin(), upper_padded.end(), 0);

    for (int i = 0; i < middle; i++) {
        lower_padded[lower_map[i]] =
            lower[i] == none ? none : lower_map[lower[i]];
    }
    for (int i = 0; middle + i < n; i++) {
        upper_padded[upper_map[i]] =
            upper[i] == none ? none : upper_map[upper[i]];
    }
    return subunit_monge_product(
        std::move(lower_padded),
        std::move(upper_padded)
    );
}

template <class T>
Permutation make_permutation(const std::vector<T>& values) {
    int n = int(values.size());
    Permutation order(n);
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](int first, int second) {
        if (values[first] < values[second]) return true;
        if (values[second] < values[first]) return false;
        return first > second;
    });

    Permutation permutation(n);
    for (int rank = 0; rank < n; rank++) {
        permutation[order[rank]] = rank;
    }
    return permutation;
}

}  // namespace range_lis_query_internal

// Static strict-LIS lengths for arbitrary subarrays.
template <class T>
struct RangeLisQuery {
   private:
    int _n;
    WaveletMatrix<int> _seaweed;

   public:
    RangeLisQuery() : _n(0), _seaweed() {}

    explicit RangeLisQuery(const std::vector<T>& values)
        : _n(int(values.size())), _seaweed() {
        if (_n == 0) return;
        std::vector<int> row = range_lis_query_internal::seaweed_doubling(
            range_lis_query_internal::make_permutation(values)
        );
        for (int& value : row) {
            if (value == range_lis_query_internal::none) value = _n;
        }
        _seaweed = WaveletMatrix<int>(row);
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    // Returns the strict LIS length of values[left, right).
    int query(int left, int right) const {
        assert(0 <= left && left <= right && right <= _n);
        if (left == right) return 0;
        return right - left - _seaweed.range_freq(left, _n, right);
    }

    int lis_length(int left, int right) const {
        return query(left, right);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_RANGE_QUERY_RANGE_LIS_QUERY_HPP
