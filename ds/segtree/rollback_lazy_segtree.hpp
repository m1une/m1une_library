#ifndef M1UNE_DS_SEGTREE_ROLLBACK_LAZY_SEGTREE_HPP
#define M1UNE_DS_SEGTREE_ROLLBACK_LAZY_SEGTREE_HPP 1

#include <bit>
#include <cassert>
#include <concepts>
#include <utility>
#include <vector>

#include "../../acted_monoid/concept.hpp"
#include "../../math/bit_ceil.hpp"
#include "../detail/rollback_journal.hpp"

namespace m1une {
namespace ds {

template <m1une::acted_monoid::IsActedMonoid ActedMonoid>
struct RollbackLazySegtree {
    using T = typename ActedMonoid::value_type;
    using F = typename ActedMonoid::operator_type;

   private:
    struct Node {
        T value = ActedMonoid::id();
        F lazy = ActedMonoid::op_id();
        bool has_lazy = false;
    };

    int _n = 0;
    int _size = 1;
    int _log = 0;
    detail::RollbackJournal<Node> _journal;

    static T mapping_at(const F& f, const T& value, long long ordinal) {
        if constexpr (requires(F g, T x, long long i) { ActedMonoid::mapping(g, x, i); }) {
            return ActedMonoid::mapping(f, value, ordinal);
        } else {
            return ActedMonoid::mapping(f, value);
        }
    }

    static F shift_operator(const F& f, long long ordinal) {
        if constexpr (requires(F g, long long i) { ActedMonoid::op_shift(g, i); }) {
            return ActedMonoid::op_shift(f, ordinal);
        } else {
            return f;
        }
    }

    template <class U>
    static T make_value(const U& value, int index) {
        if constexpr (requires(U x) { ActedMonoid::make(x); }) {
            return ActedMonoid::make(value);
        } else if constexpr (requires(U x, int i) { ActedMonoid::make(x, i); }) {
            return ActedMonoid::make(value, index);
        } else {
            return static_cast<T>(value);
        }
    }

    int node_length(int node) const {
        int level = std::bit_width(static_cast<unsigned int>(node)) - 1;
        return _size >> level;
    }

    int node_left(int node) const {
        int level = std::bit_width(static_cast<unsigned int>(node)) - 1;
        int length = _size >> level;
        return (node - (1 << level)) * length;
    }

    void update(int node) {
        _journal.touch(node);
        _journal[node].value = ActedMonoid::op(
            _journal[node << 1].value,
            _journal[node << 1 | 1].value
        );
    }

    void all_apply(int node, const F& f) {
        _journal.touch(node);
        _journal[node].value = mapping_at(f, _journal[node].value, 0);
        if (node < _size) {
            _journal[node].lazy = ActedMonoid::op_comp(f, _journal[node].lazy);
            _journal[node].has_lazy = true;
        }
    }

    void push(int node) {
        if (!_journal[node].has_lazy) return;
        F lazy = _journal[node].lazy;
        all_apply(node << 1, lazy);
        all_apply(node << 1 | 1, shift_operator(lazy, node_length(node) / 2));
        _journal.touch(node);
        _journal[node].lazy = ActedMonoid::op_id();
        _journal[node].has_lazy = false;
    }

    template <class U>
    void build(const std::vector<U>& values) {
        _n = int(values.size());
        _size = int(m1une::math::bit_ceil(static_cast<unsigned int>(_n)));
        _log = 0;
        while ((1U << _log) < static_cast<unsigned int>(_size)) ++_log;
        _journal.nodes.assign(2 * _size, Node());
        _journal.saved_epoch.assign(_journal.nodes.size(), 0);
        for (int index = 0; index < _n; ++index) {
            _journal[_size + index].value = make_value(values[index], index);
        }
        for (int node = _size - 1; node > 0; --node) {
            _journal[node].value = ActedMonoid::op(
                _journal[node << 1].value,
                _journal[node << 1 | 1].value
            );
        }
    }

   public:
    RollbackLazySegtree() { build(std::vector<T>()); }
    explicit RollbackLazySegtree(int n) {
        assert(0 <= n);
        build(std::vector<T>(n, ActedMonoid::id()));
    }
    explicit RollbackLazySegtree(const std::vector<T>& values) { build(values); }
    explicit RollbackLazySegtree(std::vector<T>&& values) { build(values); }

    template <class U>
        requires(!std::same_as<U, T>)
    explicit RollbackLazySegtree(const std::vector<U>& values) { build(values); }

    int size() const { return _n; }
    bool empty() const { return _n == 0; }
    std::size_t node_count() const { return _journal.nodes.size(); }

    void set(int pos, T value) {
        assert(0 <= pos && pos < _n);
        int node = pos + _size;
        for (int level = _log; level >= 1; --level) push(node >> level);
        _journal.touch(node);
        _journal[node].value = std::move(value);
        for (int level = 1; level <= _log; ++level) update(node >> level);
    }

    void set_inplace(int pos, T value) { set(pos, std::move(value)); }

    T get(int pos) {
        assert(0 <= pos && pos < _n);
        int node = pos + _size;
        for (int level = _log; level >= 1; --level) push(node >> level);
        return _journal[node].value;
    }

    T operator[](int pos) { return get(pos); }

    T prod(int left, int right) {
        assert(0 <= left && left <= right && right <= _n);
        if (left == right) return ActedMonoid::id();
        left += _size;
        right += _size;
        for (int level = _log; level >= 1; --level) {
            if (((left >> level) << level) != left) push(left >> level);
            if (((right >> level) << level) != right) push((right - 1) >> level);
        }
        T left_product = ActedMonoid::id();
        T right_product = ActedMonoid::id();
        while (left < right) {
            if (left & 1) left_product = ActedMonoid::op(left_product, _journal[left++].value);
            if (right & 1) right_product = ActedMonoid::op(_journal[--right].value, right_product);
            left >>= 1;
            right >>= 1;
        }
        return ActedMonoid::op(left_product, right_product);
    }

    T all_prod() const { return _journal[1].value; }

    std::vector<T> to_vector() {
        for (int node = 1; node < _size; ++node) push(node);
        std::vector<T> result;
        result.reserve(_n);
        for (int index = 0; index < _n; ++index) result.push_back(_journal[_size + index].value);
        return result;
    }

    std::vector<T> to_vector(int left, int right) {
        assert(0 <= left && left <= right && right <= _n);
        std::vector<T> result;
        result.reserve(right - left);
        for (int index = left; index < right; ++index) result.push_back(get(index));
        return result;
    }

    void apply(int pos, const F& f) {
        assert(0 <= pos && pos < _n);
        int node = pos + _size;
        for (int level = _log; level >= 1; --level) push(node >> level);
        _journal.touch(node);
        _journal[node].value = mapping_at(f, _journal[node].value, 0);
        for (int level = 1; level <= _log; ++level) update(node >> level);
    }

    void apply(int left, int right, const F& f) {
        assert(0 <= left && left <= right && right <= _n);
        if (left == right) return;
        int base_left = left;
        left += _size;
        right += _size;
        for (int level = _log; level >= 1; --level) {
            if (((left >> level) << level) != left) push(left >> level);
            if (((right >> level) << level) != right) push((right - 1) >> level);
        }
        int saved_left = left;
        int saved_right = right;
        while (left < right) {
            if (left & 1) {
                all_apply(left, shift_operator(f, node_left(left) - base_left));
                ++left;
            }
            if (right & 1) {
                --right;
                all_apply(right, shift_operator(f, node_left(right) - base_left));
            }
            left >>= 1;
            right >>= 1;
        }
        left = saved_left;
        right = saved_right;
        for (int level = 1; level <= _log; ++level) {
            if (((left >> level) << level) != left) update(left >> level);
            if (((right >> level) << level) != right) update((right - 1) >> level);
        }
    }

    void apply_inplace(int pos, const F& f) { apply(pos, f); }
    void apply_inplace(int left, int right, const F& f) { apply(left, right, f); }

    template <class Predicate>
    int max_right(int left, Predicate predicate) {
        assert(0 <= left && left <= _n);
        assert(predicate(ActedMonoid::id()));
        if (left == _n) return _n;
        int node = left + _size;
        for (int level = _log; level >= 1; --level) push(node >> level);
        T product = ActedMonoid::id();
        do {
            while ((node & 1) == 0) node >>= 1;
            T next = ActedMonoid::op(product, _journal[node].value);
            if (!predicate(next)) {
                while (node < _size) {
                    push(node);
                    node <<= 1;
                    next = ActedMonoid::op(product, _journal[node].value);
                    if (predicate(next)) {
                        product = std::move(next);
                        ++node;
                    }
                }
                return node - _size;
            }
            product = std::move(next);
            ++node;
        } while ((node & -node) != node);
        return _n;
    }

    template <class Predicate>
    int min_left(int right, Predicate predicate) {
        assert(0 <= right && right <= _n);
        assert(predicate(ActedMonoid::id()));
        if (right == 0) return 0;
        int node = right + _size;
        for (int level = _log; level >= 1; --level) push((node - 1) >> level);
        T product = ActedMonoid::id();
        do {
            --node;
            while (node > 1 && (node & 1)) node >>= 1;
            T next = ActedMonoid::op(_journal[node].value, product);
            if (!predicate(next)) {
                while (node < _size) {
                    push(node);
                    node = node << 1 | 1;
                    next = ActedMonoid::op(_journal[node].value, product);
                    if (predicate(next)) {
                        product = std::move(next);
                        --node;
                    }
                }
                return node + 1 - _size;
            }
            product = std::move(next);
        } while ((node & -node) != node);
        return 0;
    }

    int snapshot() { return _journal.snapshot(); }
    int snapshot_count() const { return _journal.snapshot_count(); }
    void reserve_snapshots(int count) { _journal.reserve_snapshots(count); }
    void rollback(int state) { _journal.rollback(state); }
    void clear_history() { _journal.clear_history(); }
    void release() { _n = 0; _size = 1; _log = 0; _journal.clear(); }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_SEGTREE_ROLLBACK_LAZY_SEGTREE_HPP
