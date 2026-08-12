#ifndef M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_HPP
#define M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <utility>
#include <vector>

#include "../../monoid/concept.hpp"

namespace m1une {
namespace ds {

template <m1une::monoid::IsMonoid Monoid>
struct RollbackSegtree {
    using T = typename Monoid::value_type;

   private:
    struct Entry {
        int pos;
        T value;
    };
    struct Checkpoint {
        std::size_t change_size;
        std::uint64_t epoch;
    };

    int _n = 0;
    int _size = 1;
    std::vector<T> _data = std::vector<T>(2, Monoid::id());
    std::vector<Entry> _history;
    std::vector<Checkpoint> _checkpoints;
    std::vector<std::uint64_t> _saved_epoch;
    std::uint64_t _next_epoch = 1;

    std::uint64_t new_epoch() {
        if (_next_epoch == 0) {
            std::fill(_saved_epoch.begin(), _saved_epoch.end(), 0);
            _next_epoch = 1;
        }
        return _next_epoch++;
    }

    template <class U>
    static T make_value(const U& value, int index) {
        if constexpr (requires(U x) { Monoid::make(x); }) {
            return Monoid::make(value);
        } else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {
            return Monoid::make(value, index);
        } else {
            return static_cast<T>(value);
        }
    }

    void assign(int pos, T value) {
        int node = pos + _size;
        _data[node] = std::move(value);
        while (node >>= 1) {
            _data[node] = Monoid::op(_data[node << 1], _data[node << 1 | 1]);
        }
    }

    template <class U>
    void build(const std::vector<U>& values) {
        _n = int(values.size());
        _size = 1;
        while (_size < _n) _size <<= 1;
        _data.assign(2 * _size, Monoid::id());
        _saved_epoch.assign(_n, 0);
        for (int index = 0; index < _n; ++index) {
            _data[_size + index] = make_value(values[index], index);
        }
        for (int node = _size - 1; node > 0; --node) {
            _data[node] = Monoid::op(_data[node << 1], _data[node << 1 | 1]);
        }
    }

   public:
    RollbackSegtree() = default;
    explicit RollbackSegtree(int n) { assert(0 <= n); build(std::vector<T>(n, Monoid::id())); }
    explicit RollbackSegtree(const std::vector<T>& values) { build(values); }
    explicit RollbackSegtree(std::vector<T>&& values) { build(values); }

    template <class U>
        requires(!std::same_as<U, T>)
    explicit RollbackSegtree(const std::vector<U>& values) { build(values); }

    int size() const { return _n; }
    bool empty() const { return _n == 0; }
    std::size_t node_count() const { return _data.size(); }

    void set(int pos, T value) {
        assert(0 <= pos && pos < _n);
        if (!_checkpoints.empty() && _saved_epoch[pos] != _checkpoints.back().epoch) {
            _saved_epoch[pos] = _checkpoints.back().epoch;
            _history.push_back(Entry{pos, get(pos)});
        }
        assign(pos, std::move(value));
    }

    void set_inplace(int pos, T value) { set(pos, std::move(value)); }

    T get(int pos) const {
        assert(0 <= pos && pos < _n);
        return _data[_size + pos];
    }

    T operator[](int pos) const { return get(pos); }

    T prod(int left, int right) const {
        assert(0 <= left && left <= right && right <= _n);
        T left_product = Monoid::id();
        T right_product = Monoid::id();
        for (left += _size, right += _size; left < right; left >>= 1, right >>= 1) {
            if (left & 1) left_product = Monoid::op(left_product, _data[left++]);
            if (right & 1) right_product = Monoid::op(_data[--right], right_product);
        }
        return Monoid::op(left_product, right_product);
    }

    T all_prod() const { return _data[1]; }

    std::vector<T> to_vector() const { return to_vector(0, _n); }
    std::vector<T> to_vector(int left, int right) const {
        assert(0 <= left && left <= right && right <= _n);
        return std::vector<T>(_data.begin() + _size + left, _data.begin() + _size + right);
    }

    template <class Predicate>
    int max_right(int left, Predicate predicate) const {
        assert(0 <= left && left <= _n);
        assert(predicate(Monoid::id()));
        if (left == _n) return _n;
        int node = left + _size;
        T product = Monoid::id();
        do {
            while ((node & 1) == 0) node >>= 1;
            T next = Monoid::op(product, _data[node]);
            if (!predicate(next)) {
                while (node < _size) {
                    node <<= 1;
                    next = Monoid::op(product, _data[node]);
                    if (predicate(next)) {
                        product = std::move(next);
                        ++node;
                    }
                }
                return std::min(_n, node - _size);
            }
            product = std::move(next);
            ++node;
        } while ((node & -node) != node);
        return _n;
    }

    template <class Predicate>
    int min_left(int right, Predicate predicate) const {
        assert(0 <= right && right <= _n);
        assert(predicate(Monoid::id()));
        if (right == 0) return 0;
        int node = right + _size;
        T product = Monoid::id();
        do {
            --node;
            while (node > 1 && (node & 1)) node >>= 1;
            T next = Monoid::op(_data[node], product);
            if (!predicate(next)) {
                while (node < _size) {
                    node = node << 1 | 1;
                    next = Monoid::op(_data[node], product);
                    if (predicate(next)) {
                        product = std::move(next);
                        --node;
                    }
                }
                return std::max(0, node + 1 - _size);
            }
            product = std::move(next);
        } while ((node & -node) != node);
        return 0;
    }

    int snapshot() {
        _checkpoints.push_back(Checkpoint{_history.size(), new_epoch()});
        return int(_checkpoints.size());
    }
    int snapshot_count() const { return int(_checkpoints.size()); }
    void reserve_snapshots(int count) { assert(0 <= count); _checkpoints.reserve(count); }

    void rollback(int state) {
        assert(1 <= state && state <= snapshot_count());
        while (_history.size() > _checkpoints[state - 1].change_size) {
            Entry entry = std::move(_history.back());
            _history.pop_back();
            assign(entry.pos, std::move(entry.value));
        }
        _checkpoints.resize(state);
        _checkpoints.back().epoch = new_epoch();
    }
    void clear_history() {
        _history.clear();
        _checkpoints.clear();
        std::fill(_saved_epoch.begin(), _saved_epoch.end(), 0);
    }
    void release() {
        _n = 0;
        _size = 1;
        _data.assign(2, Monoid::id());
        _history.clear();
        _checkpoints.clear();
        _saved_epoch.clear();
        _next_epoch = 1;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_SEGTREE_ROLLBACK_SEGTREE_HPP
