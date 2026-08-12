#ifndef M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_DUAL_SEGTREE_HPP
#define M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_DUAL_SEGTREE_HPP 1

#include <cassert>
#include <concepts>
#include <limits>
#include <numeric>
#include <type_traits>
#include <utility>

#include "../../monoid/concept.hpp"
#include "../detail/rollback_journal.hpp"
#include "dynamic_segtree_common.hpp"

namespace m1une {
namespace ds {

template <m1une::monoid::IsMonoid Monoid, std::integral Index = long long>
    requires(!std::same_as<std::remove_cv_t<Index>, bool>)
struct RollbackDynamicDualSegtree {
    using T = typename Monoid::value_type;
    using index_type = Index;
    using size_type = detail::dynamic_size_type<Index>;

   private:
    struct Node {
        T value = Monoid::id();
        int left = 0;
        int right = 0;
        bool has_value = false;
    };

    Index _left;
    Index _right;
    T _initial_value;
    detail::RollbackJournal<Node> _journal;

    int root() const { return _journal[0].left; }
    int new_node() { return _journal.emplace(); }

    int ensure(int node) { return node ? node : new_node(); }

    void all_apply(int node, Index left, Index right, const T& value) {
        _journal.touch(node);
        Node& current = _journal[node];
        if (std::midpoint(left, right) == left) {
            T old = current.has_value ? current.value : _initial_value;
            current.value = Monoid::op(value, old);
        } else {
            current.value = current.has_value ? Monoid::op(value, current.value) : value;
        }
        current.has_value = true;
    }

    void push(int node, Index left, Index right) {
        if (!_journal[node].has_value) return;
        Index middle = std::midpoint(left, right);
        if (middle == left) return;
        T lazy = _journal[node].value;
        int left_child = ensure(_journal[node].left);
        int right_child = ensure(_journal[node].right);
        all_apply(left_child, left, middle, lazy);
        all_apply(right_child, middle, right, lazy);
        _journal.touch(node);
        _journal[node].left = left_child;
        _journal[node].right = right_child;
        _journal[node].value = Monoid::id();
        _journal[node].has_value = false;
    }

    int set_node(int node, Index left, Index right, Index pos, T value) {
        node = ensure(node);
        Index middle = std::midpoint(left, right);
        if (middle == left) {
            _journal.touch(node);
            _journal[node].value = std::move(value);
            _journal[node].has_value = true;
            return node;
        }
        push(node, left, right);
        if (pos < middle) {
            int child = set_node(_journal[node].left, left, middle, pos, std::move(value));
            _journal.touch(node);
            _journal[node].left = child;
        } else {
            int child = set_node(_journal[node].right, middle, right, pos, std::move(value));
            _journal.touch(node);
            _journal[node].right = child;
        }
        return node;
    }

    int apply_node(int node, Index left, Index right, Index query_left, Index query_right, const T& value) {
        if (query_right <= left || right <= query_left) return node;
        node = ensure(node);
        if (query_left <= left && right <= query_right) {
            all_apply(node, left, right, value);
            return node;
        }
        push(node, left, right);
        Index middle = std::midpoint(left, right);
        int left_child = apply_node(_journal[node].left, left, middle, query_left, query_right, value);
        int right_child = apply_node(_journal[node].right, middle, right, query_left, query_right, value);
        _journal.touch(node);
        _journal[node].left = left_child;
        _journal[node].right = right_child;
        return node;
    }

   public:
    RollbackDynamicDualSegtree()
        : RollbackDynamicDualSegtree(Index(0), Index(0), Monoid::id()) {}
    explicit RollbackDynamicDualSegtree(Index n)
        : RollbackDynamicDualSegtree(Index(0), n, Monoid::id()) {
        if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);
    }
    RollbackDynamicDualSegtree(Index left, Index right)
        : RollbackDynamicDualSegtree(left, right, Monoid::id()) {}
    RollbackDynamicDualSegtree(Index left, Index right, T initial_value)
        : _left(left), _right(right), _initial_value(std::move(initial_value)) {
        assert(left <= right);
        _journal.emplace();
    }

    size_type size() const { return detail::dynamic_distance(_left, _right); }
    bool empty() const { return _left == _right; }
    Index left_bound() const { return _left; }
    Index right_bound() const { return _right; }
    const T& initial_value() const { return _initial_value; }
    std::size_t node_count() const { return _journal.nodes.size() - 1; }

    void reserve(std::size_t node_capacity) {
        _journal.nodes.reserve(node_capacity + 1);
        _journal.saved_epoch.reserve(node_capacity + 1);
    }

    void set(Index pos, T value) {
        assert(_left <= pos && pos < _right);
        int next_root = set_node(root(), _left, _right, pos, std::move(value));
        if (next_root != root()) {
            _journal.touch(0);
            _journal[0].left = next_root;
        }
    }
    void set_inplace(Index pos, T value) { set(pos, std::move(value)); }

    T get(Index pos) const {
        assert(_left <= pos && pos < _right);
        int node = root();
        Index left = _left;
        Index right = _right;
        T inherited = Monoid::id();
        while (node) {
            Index middle = std::midpoint(left, right);
            if (middle == left) {
                T value = _journal[node].has_value ? _journal[node].value : _initial_value;
                return Monoid::op(inherited, value);
            }
            if (_journal[node].has_value) inherited = Monoid::op(inherited, _journal[node].value);
            if (pos < middle) {
                node = _journal[node].left;
                right = middle;
            } else {
                node = _journal[node].right;
                left = middle;
            }
        }
        return Monoid::op(inherited, _initial_value);
    }
    T operator[](Index pos) const { return get(pos); }

    void apply(Index pos, const T& value) { apply(pos, pos + 1, value); }
    void apply(Index left, Index right, const T& value) {
        assert(_left <= left && left <= right && right <= _right);
        if (left == right) return;
        int next_root = apply_node(root(), _left, _right, left, right, value);
        if (next_root != root()) {
            _journal.touch(0);
            _journal[0].left = next_root;
        }
    }
    void apply_inplace(Index pos, const T& value) { apply(pos, value); }
    void apply_inplace(Index left, Index right, const T& value) { apply(left, right, value); }

    int snapshot() { return _journal.snapshot(); }
    int snapshot_count() const { return _journal.snapshot_count(); }
    void reserve_snapshots(int count) { _journal.reserve_snapshots(count); }
    void rollback(int state) { _journal.rollback(state); }
    void clear_history() { _journal.clear_history(); }
    void release() { _journal.clear(); _journal.emplace(); }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_DUAL_SEGTREE_HPP
