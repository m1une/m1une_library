#ifndef M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_SEGTREE_HPP
#define M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_SEGTREE_HPP 1

#include <array>
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
struct RollbackDynamicSegtree {
    using T = typename Monoid::value_type;
    using index_type = Index;
    using size_type = detail::dynamic_size_type<Index>;

   private:
    struct Node {
        T value = Monoid::id();
        int left = 0;
        int right = 0;
    };

    static constexpr int path_capacity = std::numeric_limits<size_type>::digits + 1;
    detail::UniformMonoidDomain<Monoid, Index> _domain;
    detail::RollbackJournal<Node> _journal;

    int root() const { return _journal[0].left; }

    int new_node() { return _journal.emplace(); }

    const T& value(int node, Index left, Index right, int depth) const {
        if (node) return _journal[node].value;
        return _domain.default_product(depth, left, right);
    }

    void update(int node, Index left, Index right, int depth) {
        Index middle = std::midpoint(left, right);
        _journal.touch(node);
        _journal[node].value = Monoid::op(
            value(_journal[node].left, left, middle, depth + 1),
            value(_journal[node].right, middle, right, depth + 1)
        );
    }

    T prod_node(int node, Index left, Index right, int depth, Index query_left, Index query_right) const {
        if (query_right <= left || right <= query_left) return Monoid::id();
        if (query_left <= left && right <= query_right) return value(node, left, right, depth);
        Index middle = std::midpoint(left, right);
        return Monoid::op(
            prod_node(node ? _journal[node].left : 0, left, middle, depth + 1, query_left, query_right),
            prod_node(node ? _journal[node].right : 0, middle, right, depth + 1, query_left, query_right)
        );
    }

    template <class Predicate>
    Index max_right_node(int node, Index left, Index right, int depth, Index query_left, T& product,
                         Predicate& predicate) const {
        if (right <= query_left) return right;
        if (query_left <= left) {
            T next = Monoid::op(product, value(node, left, right, depth));
            if (predicate(next)) {
                product = std::move(next);
                return right;
            }
            Index middle = std::midpoint(left, right);
            if (middle == left) return left;
        }
        Index middle = std::midpoint(left, right);
        Index result = max_right_node(node ? _journal[node].left : 0, left, middle, depth + 1,
                                      query_left, product, predicate);
        if (result < middle) return result;
        return max_right_node(node ? _journal[node].right : 0, middle, right, depth + 1,
                              query_left, product, predicate);
    }

    template <class Predicate>
    Index min_left_node(int node, Index left, Index right, int depth, Index query_right, T& product,
                        Predicate& predicate) const {
        if (query_right <= left) return left;
        if (right <= query_right) {
            T next = Monoid::op(value(node, left, right, depth), product);
            if (predicate(next)) {
                product = std::move(next);
                return left;
            }
            Index middle = std::midpoint(left, right);
            if (middle == left) return right;
        }
        Index middle = std::midpoint(left, right);
        Index result = min_left_node(node ? _journal[node].right : 0, middle, right, depth + 1,
                                     query_right, product, predicate);
        if (middle < result) return result;
        return min_left_node(node ? _journal[node].left : 0, left, middle, depth + 1,
                             query_right, product, predicate);
    }

   public:
    RollbackDynamicSegtree() : RollbackDynamicSegtree(Index(0), Index(0)) {}
    explicit RollbackDynamicSegtree(Index n) : RollbackDynamicSegtree(Index(0), n) {
        if constexpr (std::signed_integral<Index>) assert(Index(0) <= n);
    }
    RollbackDynamicSegtree(Index left, Index right)
        : RollbackDynamicSegtree(left, right, Monoid::id()) {}
    RollbackDynamicSegtree(Index left, Index right, T initial_value)
        : _domain(left, right, std::move(initial_value)) {
        _journal.emplace();
    }

    size_type size() const { return _domain.size(); }
    bool empty() const { return _domain.empty(); }
    Index left_bound() const { return _domain.left_bound(); }
    Index right_bound() const { return _domain.right_bound(); }
    const T& initial_value() const { return _domain.initial_value(); }

    void reserve(std::size_t node_capacity) {
        _journal.nodes.reserve(node_capacity + 1);
        _journal.saved_epoch.reserve(node_capacity + 1);
    }

    std::size_t node_count() const { return _journal.nodes.size() - 1; }

    void set(Index pos, T x) {
        assert(left_bound() <= pos && pos < right_bound());
        if (!root()) {
            int node = new_node();
            _journal.touch(0);
            _journal[0].left = node;
        }

        std::array<int, path_capacity> path;
        std::array<Index, path_capacity> path_left;
        std::array<Index, path_capacity> path_right;
        int depth = 0;
        int node = root();
        Index left = left_bound();
        Index right = right_bound();

        while (true) {
            path[depth] = node;
            path_left[depth] = left;
            path_right[depth] = right;
            ++depth;
            Index middle = std::midpoint(left, right);
            if (middle == left) break;
            if (pos < middle) {
                if (!_journal[node].left) {
                    int child = new_node();
                    _journal.touch(node);
                    _journal[node].left = child;
                }
                node = _journal[node].left;
                right = middle;
            } else {
                if (!_journal[node].right) {
                    int child = new_node();
                    _journal.touch(node);
                    _journal[node].right = child;
                }
                node = _journal[node].right;
                left = middle;
            }
        }
        _journal.touch(node);
        _journal[node].value = std::move(x);
        for (int index = depth - 2; index >= 0; --index) {
            update(path[index], path_left[index], path_right[index], index);
        }
    }

    void set_inplace(Index pos, T x) { set(pos, std::move(x)); }

    T get(Index pos) const {
        assert(left_bound() <= pos && pos < right_bound());
        int node = root();
        Index left = left_bound();
        Index right = right_bound();
        int depth = 0;
        while (node) {
            Index middle = std::midpoint(left, right);
            if (middle == left) return value(node, left, right, depth);
            if (pos < middle) {
                node = _journal[node].left;
                right = middle;
            } else {
                node = _journal[node].right;
                left = middle;
            }
            ++depth;
        }
        return initial_value();
    }

    T operator[](Index pos) const { return get(pos); }
    T prod(Index left, Index right) const {
        assert(left_bound() <= left && left <= right && right <= right_bound());
        if (left == right) return Monoid::id();
        return prod_node(root(), left_bound(), right_bound(), 0, left, right);
    }
    T all_prod() const { return value(root(), left_bound(), right_bound(), 0); }

    template <class Predicate>
    Index max_right(Index left, Predicate predicate) const {
        assert(left_bound() <= left && left <= right_bound());
        assert(predicate(Monoid::id()));
        if (left == right_bound()) return right_bound();
        T product = Monoid::id();
        return max_right_node(root(), left_bound(), right_bound(), 0, left, product, predicate);
    }

    template <class Predicate>
    Index min_left(Index right, Predicate predicate) const {
        assert(left_bound() <= right && right <= right_bound());
        assert(predicate(Monoid::id()));
        if (right == left_bound()) return left_bound();
        T product = Monoid::id();
        return min_left_node(root(), left_bound(), right_bound(), 0, right, product, predicate);
    }

    int snapshot() { return _journal.snapshot(); }
    int snapshot_count() const { return _journal.snapshot_count(); }
    void reserve_snapshots(int count) { _journal.reserve_snapshots(count); }
    void rollback(int state) { _journal.rollback(state); }
    void clear_history() { _journal.clear_history(); }
    void release() { _journal.clear(); _journal.emplace(); }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_SEGTREE_ROLLBACK_DYNAMIC_SEGTREE_HPP
