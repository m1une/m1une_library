#ifndef M1UNE_DS_INTERVAL_MAP_HPP
#define M1UNE_DS_INTERVAL_MAP_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <iterator>
#include <limits>
#include <memory>
#include <set>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {

// A sparse piecewise-constant map. Adjacent intervals with equal values merge.
template <class Key, class T>
class IntervalMap {
   public:
    using key_type = Key;
    using value_type = T;

    struct interval_type {
        Key l;
        Key r;
        T value;
    };

   private:
    struct Compare {
        using is_transparent = void;

        bool operator()(const interval_type& a, const interval_type& b) const {
            return a.l < b.l;
        }
        bool operator()(const interval_type& a, const Key& b) const { return a.l < b; }
        bool operator()(const Key& a, const interval_type& b) const { return a < b.l; }
    };

    using Set = std::set<interval_type, Compare>;
    using iterator = typename Set::iterator;
    Set _intervals;

    static bool equal_key(const Key& a, const Key& b) {
        return !(a < b) && !(b < a);
    }

    // Creates a boundary at x if x is strictly inside a stored interval.
    // The extracted left node is reused; only the right node is allocated.
    iterator split(Key x) {
        auto right = _intervals.lower_bound(x);
        if (right != _intervals.end() && equal_key(right->l, x)) return right;
        if (right == _intervals.begin()) return right;
        auto left = std::prev(right);
        if (!(x < left->r)) return right;

        right = _intervals.emplace_hint(right, interval_type{x, left->r, left->value});
        auto node = _intervals.extract(left);
        node.value().r = std::move(x);
        _intervals.insert(right, std::move(node));
        return right;
    }

    template <class Callback>
    iterator erase_range(Key l, Key r, Callback& on_erase) {
        auto last = split(r);
        auto first = split(l);
        for (auto it = first; it != last; ++it) on_erase(it->l, it->r, it->value);
        return _intervals.erase(first, last);
    }

   public:
    using const_iterator = typename Set::const_iterator;

    IntervalMap() = default;

    IntervalMap(Key l, Key r, T value) { assign(l, r, std::move(value)); }

    // Input intervals must be nonempty, sorted, and nonoverlapping.
    explicit IntervalMap(const std::vector<interval_type>& intervals) {
        for (const auto& interval : intervals) {
            assert(interval.l < interval.r);
            if (!_intervals.empty()) {
                auto previous = std::prev(_intervals.end());
                assert(!(interval.l < previous->r));
                if (equal_key(previous->r, interval.l) && previous->value == interval.value) {
                    auto node = _intervals.extract(previous);
                    node.value().r = interval.r;
                    _intervals.insert(_intervals.end(), std::move(node));
                    continue;
                }
            }
            _intervals.insert(_intervals.end(), interval);
        }
    }

    // Dense array convenience constructor: values[i] is assigned to [i, i + 1).
    explicit IntervalMap(const std::vector<T>& values) requires std::same_as<Key, int> {
        assert(values.size() <= std::size_t(std::numeric_limits<int>::max()));
        const int n = int(values.size());
        for (int l = 0; l < n;) {
            int r = l + 1;
            while (r < n && values[l] == values[r]) ++r;
            _intervals.emplace_hint(_intervals.end(), interval_type{l, r, values[l]});
            l = r;
        }
    }

    int size() const { return int(_intervals.size()); }

    bool empty() const { return _intervals.empty(); }

    void clear() { _intervals.clear(); }

    // Returns the interval containing x, rather than requiring x to be a boundary.
    const_iterator find(Key x) const {
        auto it = _intervals.upper_bound(x);
        if (it == _intervals.begin()) return _intervals.end();
        --it;
        return x < it->r ? it : _intervals.end();
    }

    bool contains(Key x) const { return find(x) != end(); }

    const T& get(Key x) const {
        auto it = find(x);
        assert(it != end());
        return it->value;
    }

    const T* get_if(Key x) const {
        auto it = find(x);
        return it == end() ? nullptr : std::addressof(it->value);
    }

    void assign(Key l, Key r, T value) {
        assign(l, r, std::move(value), [](Key, Key, const T&) {});
    }

    // Calls on_erase(a, b, old_value) for covered parts of [l, r), even when
    // old_value == value. Gaps do not generate callbacks. The value is owned
    // before any erasure, so assign(l, r, get(x)) is safe.
    template <class Callback>
    void assign(Key l, Key r, T value, Callback&& on_erase) {
        assert(!(r < l));
        if (!(l < r)) return;
        auto right = erase_range(l, r, on_erase);

        if (right != _intervals.begin()) {
            auto left = std::prev(right);
            if (equal_key(left->r, l) && left->value == value) {
                l = left->l;
                _intervals.erase(left);
            }
        }
        if (right != _intervals.end() && equal_key(r, right->l) && right->value == value) {
            r = right->r;
            right = _intervals.erase(right);
        }
        _intervals.emplace_hint(right, interval_type{std::move(l), std::move(r), std::move(value)});
    }

    void erase(Key l, Key r) { erase(l, r, [](Key, Key, const T&) {}); }

    template <class Callback>
    void erase(Key l, Key r, Callback&& on_erase) {
        assert(!(r < l));
        if (l < r) erase_range(l, r, on_erase);
    }

    // Visits the covered parts of [l, r), clipped to the query and in order.
    // No callback may modify this map while traversal or an update is active.
    template <class Callback>
    void for_each(Key l, Key r, Callback&& callback) const {
        assert(!(r < l));
        if (!(l < r)) return;
        auto it = _intervals.lower_bound(l);
        if (it != _intervals.begin()) {
            auto previous = std::prev(it);
            if (l < previous->r) it = previous;
        }
        for (; it != _intervals.end() && it->l < r; ++it) {
            callback(std::max(l, it->l), std::min(r, it->r), it->value);
        }
    }

    std::vector<interval_type> to_vector() const {
        return std::vector<interval_type>(begin(), end());
    }

    const_iterator begin() const { return _intervals.begin(); }

    const_iterator end() const { return _intervals.end(); }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_INTERVAL_MAP_HPP
