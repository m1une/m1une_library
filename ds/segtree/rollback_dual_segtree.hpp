#ifndef M1UNE_DS_SEGTREE_ROLLBACK_DUAL_SEGTREE_HPP
#define M1UNE_DS_SEGTREE_ROLLBACK_DUAL_SEGTREE_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <utility>
#include <vector>

#include "../../monoid/concept.hpp"
#include "../detail/rollback_journal.hpp"

namespace m1une {
namespace ds {

template <m1une::monoid::IsMonoid Monoid>
struct RollbackDualSegtree {
    using T = typename Monoid::value_type;

   private:
    struct Node {
        T value = Monoid::id();
        bool has_value = false;
    };

    int _n = 0;
    detail::RollbackJournal<Node> _journal;

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

    void initialize(int n) {
        assert(0 <= n);
        _n = n;
        _journal.nodes.assign(std::max(1, 4 * n), Node());
        _journal.saved_epoch.assign(_journal.nodes.size(), 0);
    }

    template <class U>
    void build(int node, int left, int right, const std::vector<U>& values) {
        if (right - left == 1) {
            _journal[node].value = make_value(values[left], left);
            _journal[node].has_value = true;
            return;
        }
        int middle = (left + right) >> 1;
        build(node << 1, left, middle, values);
        build(node << 1 | 1, middle, right, values);
    }

    void all_apply(int node, const T& value) {
        _journal.touch(node);
        Node& current = _journal[node];
        current.value = current.has_value
            ? Monoid::op(value, current.value)
            : value;
        current.has_value = true;
    }

    void push(int node) {
        if (!_journal[node].has_value) return;
        T value = _journal[node].value;
        all_apply(node << 1, value);
        all_apply(node << 1 | 1, value);
        _journal.touch(node);
        _journal[node].value = Monoid::id();
        _journal[node].has_value = false;
    }

    void set_node(int node, int left, int right, int pos, T value) {
        if (right - left == 1) {
            _journal.touch(node);
            _journal[node].value = std::move(value);
            _journal[node].has_value = true;
            return;
        }
        push(node);
        int middle = (left + right) >> 1;
        if (pos < middle) set_node(node << 1, left, middle, pos, std::move(value));
        else set_node(node << 1 | 1, middle, right, pos, std::move(value));
    }

    void apply_node(int node, int left, int right, int query_left, int query_right, const T& value) {
        if (query_right <= left || right <= query_left) return;
        if (query_left <= left && right <= query_right) {
            all_apply(node, value);
            return;
        }
        push(node);
        int middle = (left + right) >> 1;
        apply_node(node << 1, left, middle, query_left, query_right, value);
        apply_node(node << 1 | 1, middle, right, query_left, query_right, value);
    }

    T get_node(int node, int left, int right, int pos, T inherited) const {
        const Node& current = _journal[node];
        if (right - left == 1) {
            assert(current.has_value);
            return Monoid::op(inherited, current.value);
        }
        if (current.has_value) inherited = Monoid::op(inherited, current.value);
        int middle = (left + right) >> 1;
        if (pos < middle) return get_node(node << 1, left, middle, pos, std::move(inherited));
        return get_node(node << 1 | 1, middle, right, pos, std::move(inherited));
    }

   public:
    RollbackDualSegtree() { initialize(0); }
    explicit RollbackDualSegtree(int n) {
        initialize(n);
        if (n > 0) {
            std::vector<T> values(n, Monoid::id());
            build(1, 0, n, values);
        }
    }

    explicit RollbackDualSegtree(const std::vector<T>& values) {
        initialize(int(values.size()));
        if (_n > 0) build(1, 0, _n, values);
    }

    template <class U>
        requires(!std::same_as<U, T>)
    explicit RollbackDualSegtree(const std::vector<U>& values) {
        initialize(int(values.size()));
        if (_n > 0) build(1, 0, _n, values);
    }

    int size() const { return _n; }
    bool empty() const { return _n == 0; }
    std::size_t node_count() const { return _journal.nodes.size(); }

    void set(int pos, T value) {
        assert(0 <= pos && pos < _n);
        set_node(1, 0, _n, pos, std::move(value));
    }
    void set_inplace(int pos, T value) { set(pos, std::move(value)); }

    T get(int pos) const {
        assert(0 <= pos && pos < _n);
        return get_node(1, 0, _n, pos, Monoid::id());
    }
    T operator[](int pos) const { return get(pos); }

    void apply(int pos, const T& value) { apply(pos, pos + 1, value); }
    void apply(int left, int right, const T& value) {
        assert(0 <= left && left <= right && right <= _n);
        if (left != right) apply_node(1, 0, _n, left, right, value);
    }
    void apply_inplace(int pos, const T& value) { apply(pos, value); }
    void apply_inplace(int left, int right, const T& value) { apply(left, right, value); }

    int snapshot() { return _journal.snapshot(); }
    int snapshot_count() const { return _journal.snapshot_count(); }
    void reserve_snapshots(int count) { _journal.reserve_snapshots(count); }
    void rollback(int state) { _journal.rollback(state); }
    void clear_history() { _journal.clear_history(); }
    void release() { _n = 0; _journal.clear(); }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_SEGTREE_ROLLBACK_DUAL_SEGTREE_HPP
