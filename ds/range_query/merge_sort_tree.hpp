#ifndef M1UNE_DS_RANGE_QUERY_MERGE_SORT_TREE_HPP
#define M1UNE_DS_RANGE_QUERY_MERGE_SORT_TREE_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <iterator>
#include <limits>
#include <optional>
#include <utility>
#include <vector>

#include "../../math/bit_ceil.hpp"

namespace m1une {
namespace ds {

// Static range counting, sums, and order statistics for arbitrary ordered values.
template <class T, class Sum = T>
class MergeSortTree {
   private:
    struct Node {
        std::vector<T> values;
        std::vector<Sum> prefix_sum;
    };

    static constexpr bool supports_sum = requires(Sum left, Sum right, const T& value) {
        Sum{};
        static_cast<Sum>(value);
        { left + right } -> std::convertible_to<Sum>;
        { left - right } -> std::convertible_to<Sum>;
    };

    int _n;
    int _size;
    std::vector<T> _values;
    std::vector<T> _sorted_values;
    std::vector<Node> _tree;
    std::vector<Sum> _original_prefix_sum;

    template <class Callback>
    void visit(int left, int right, Callback&& callback) const {
        left += _size;
        right += _size;
        while (left < right) {
            if (left & 1) callback(_tree[left++]);
            if (right & 1) callback(_tree[--right]);
            left >>= 1;
            right >>= 1;
        }
    }

    static bool equivalent(const T& left, const T& right) {
        return !(left < right) && !(right < left);
    }

   public:
    MergeSortTree()
        : _n(0),
          _size(1),
          _tree(2) {
        if constexpr (supports_sum) _original_prefix_sum.push_back(Sum{});
    }

    explicit MergeSortTree(const std::vector<T>& values)
        : _n(0),
          _size(1) {
        assert(values.size() <= std::size_t(std::numeric_limits<int>::max()));
        _n = int(values.size());
        _size = m1une::math::bit_ceil(std::max(1, _n));
        _values = values;
        _sorted_values = values;
        std::sort(_sorted_values.begin(), _sorted_values.end());
        _sorted_values.erase(
            std::unique(
                _sorted_values.begin(),
                _sorted_values.end(),
                [](const T& left, const T& right) {
                    return equivalent(left, right);
                }
            ),
            _sorted_values.end()
        );

        _tree.resize(2 * _size);
        for (int index = 0; index < _n; index++) {
            _tree[_size + index].values.push_back(values[index]);
        }
        for (int node = _size - 1; node >= 1; node--) {
            const auto& left = _tree[2 * node].values;
            const auto& right = _tree[2 * node + 1].values;
            _tree[node].values.reserve(left.size() + right.size());
            std::merge(
                left.begin(),
                left.end(),
                right.begin(),
                right.end(),
                std::back_inserter(_tree[node].values)
            );
        }

        if constexpr (supports_sum) {
            _original_prefix_sum.reserve(_n + 1);
            _original_prefix_sum.push_back(Sum{});
            for (const T& value : values) {
                _original_prefix_sum.push_back(
                    _original_prefix_sum.back() + static_cast<Sum>(value)
                );
            }
            for (Node& node : _tree) {
                if (node.values.empty()) continue;
                node.prefix_sum.reserve(node.values.size() + 1);
                node.prefix_sum.push_back(Sum{});
                for (const T& value : node.values) {
                    node.prefix_sum.push_back(
                        node.prefix_sum.back() + static_cast<Sum>(value)
                    );
                }
            }
        }
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    const T& get(int position) const {
        assert(0 <= position && position < _n);
        return _values[position];
    }

    const T& operator[](int position) const {
        return get(position);
    }

    int count_less(int left, int right, const T& upper) const {
        assert(0 <= left && left <= right && right <= _n);
        int result = 0;
        visit(left, right, [&](const Node& node) {
            const auto& values = node.values;
            result += int(std::lower_bound(values.begin(), values.end(), upper) - values.begin());
        });
        return result;
    }

    int count_less_equal(int left, int right, const T& upper) const {
        assert(0 <= left && left <= right && right <= _n);
        int result = 0;
        visit(left, right, [&](const Node& node) {
            const auto& values = node.values;
            result += int(std::upper_bound(values.begin(), values.end(), upper) - values.begin());
        });
        return result;
    }

    int count(int left, int right, const T& value) const {
        assert(0 <= left && left <= right && right <= _n);
        int result = 0;
        visit(left, right, [&](const Node& node) {
            const auto& values = node.values;
            auto range = std::equal_range(values.begin(), values.end(), value);
            result += int(range.second - range.first);
        });
        return result;
    }

    int count(int left, int right, const T& lower, const T& upper) const {
        assert(0 <= left && left <= right && right <= _n);
        if (!(lower < upper)) return 0;
        int result = 0;
        visit(left, right, [&](const Node& node) {
            const auto& values = node.values;
            auto first = std::lower_bound(values.begin(), values.end(), lower);
            auto last = std::lower_bound(values.begin(), values.end(), upper);
            result += int(last - first);
        });
        return result;
    }

    Sum range_sum(int left, int right) const requires(supports_sum) {
        assert(0 <= left && left <= right && right <= _n);
        return _original_prefix_sum[right] - _original_prefix_sum[left];
    }

    Sum sum_less(int left, int right, const T& upper) const requires(supports_sum) {
        assert(0 <= left && left <= right && right <= _n);
        Sum result{};
        visit(left, right, [&](const Node& node) {
            auto iterator = std::lower_bound(node.values.begin(), node.values.end(), upper);
            int position = int(iterator - node.values.begin());
            result = result + node.prefix_sum[position];
        });
        return result;
    }

    Sum sum_less_equal(int left, int right, const T& upper) const requires(supports_sum) {
        assert(0 <= left && left <= right && right <= _n);
        Sum result{};
        visit(left, right, [&](const Node& node) {
            auto iterator = std::upper_bound(node.values.begin(), node.values.end(), upper);
            int position = int(iterator - node.values.begin());
            result = result + node.prefix_sum[position];
        });
        return result;
    }

    Sum sum(int left, int right, const T& value) const requires(supports_sum) {
        assert(0 <= left && left <= right && right <= _n);
        Sum result{};
        visit(left, right, [&](const Node& node) {
            auto range = std::equal_range(node.values.begin(), node.values.end(), value);
            int first = int(range.first - node.values.begin());
            int last = int(range.second - node.values.begin());
            result = result + node.prefix_sum[last] - node.prefix_sum[first];
        });
        return result;
    }

    Sum sum(int left, int right, const T& lower, const T& upper) const
        requires(supports_sum) {
        assert(0 <= left && left <= right && right <= _n);
        if (!(lower < upper)) return Sum{};
        Sum result{};
        visit(left, right, [&](const Node& node) {
            auto first_iterator = std::lower_bound(node.values.begin(), node.values.end(), lower);
            auto last_iterator = std::lower_bound(node.values.begin(), node.values.end(), upper);
            int first = int(first_iterator - node.values.begin());
            int last = int(last_iterator - node.values.begin());
            result = result + node.prefix_sum[last] - node.prefix_sum[first];
        });
        return result;
    }

    T kth_smallest(int left, int right, int k) const {
        assert(0 <= left && left <= right && right <= _n);
        assert(0 <= k && k < right - left);
        int low = 0;
        int high = int(_sorted_values.size()) - 1;
        while (low < high) {
            int middle = (low + high) / 2;
            if (count_less_equal(left, right, _sorted_values[middle]) > k) {
                high = middle;
            } else {
                low = middle + 1;
            }
        }
        return _sorted_values[low];
    }

    T kth_largest(int left, int right, int k) const {
        assert(0 <= left && left <= right && right <= _n);
        assert(0 <= k && k < right - left);
        return kth_smallest(left, right, right - left - 1 - k);
    }

    std::optional<T> prev_value(int left, int right, const T& upper) const {
        assert(0 <= left && left <= right && right <= _n);
        std::optional<T> result;
        visit(left, right, [&](const Node& node) {
            const auto& values = node.values;
            auto iterator = std::lower_bound(values.begin(), values.end(), upper);
            if (iterator == values.begin()) return;
            --iterator;
            if (!result || *result < *iterator) result = *iterator;
        });
        return result;
    }

    std::optional<T> next_value(int left, int right, const T& lower) const {
        assert(0 <= left && left <= right && right <= _n);
        std::optional<T> result;
        visit(left, right, [&](const Node& node) {
            const auto& values = node.values;
            auto iterator = std::lower_bound(values.begin(), values.end(), lower);
            if (iterator == values.end()) return;
            if (!result || *iterator < *result) result = *iterator;
        });
        return result;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_RANGE_QUERY_MERGE_SORT_TREE_HPP
