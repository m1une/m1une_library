#ifndef M1UNE_PERSISTENT_LAZY_SEGTREE_HPP
#define M1UNE_PERSISTENT_LAZY_SEGTREE_HPP 1

#include <cassert>
#include <concepts>
#include <memory>
#include <utility>
#include <vector>

#include "../../acted_monoid/concept.hpp"
#include "persistent_node_pool.hpp"

namespace m1une {
namespace ds {

template <m1une::acted_monoid::IsActedMonoid ActedMonoid>
struct PersistentLazySegtree {
    using T = typename ActedMonoid::value_type;
    using F = typename ActedMonoid::operator_type;

   private:
    struct Node {
        T val;
        F lazy;
        int left, right;
        int references;
        bool has_lazy;

        Node()
            : val(ActedMonoid::id()), lazy(ActedMonoid::op_id()), left(0), right(0), references(0), has_lazy(false) {}
        explicit Node(T value)
            : val(std::move(value)), lazy(ActedMonoid::op_id()), left(0), right(0), references(0), has_lazy(false) {}
        Node(T value, int left_child, int right_child)
            : val(std::move(value)),
              lazy(ActedMonoid::op_id()),
              left(left_child),
              right(right_child),
              references(0),
              has_lazy(false) {}
    };

    using Pool = detail::PersistentNodePool<Node>;

    int _n;
    int _root;
    std::shared_ptr<Pool> _pool;

    explicit PersistentLazySegtree(int n, int root, std::shared_ptr<Pool> pool)
        : _n(n), _root(root), _pool(std::move(pool)) {
        _pool->retain(_root);
    }

    int new_node(const Node& node) const { return _pool->emplace(node); }

    int new_node(Node&& node) const { return _pool->emplace(std::move(node)); }

    int clone_node(int t) const { return _pool->clone(t); }

    template <typename U>
    static T make_value(const U& value, int index) {
        if constexpr (requires(U x) { ActedMonoid::make(x); }) {
            return ActedMonoid::make(value);
        } else if constexpr (requires(U x, int i) { ActedMonoid::make(x, i); }) {
            return ActedMonoid::make(value, index);
        } else {
            return static_cast<T>(value);
        }
    }

    static T mapping_at(const F& f, const T& value, long long ord) {
        if constexpr (requires(F g, T x, long long i) { ActedMonoid::mapping(g, x, i); }) {
            return ActedMonoid::mapping(f, value, ord);
        } else {
            return ActedMonoid::mapping(f, value);
        }
    }

    static F shift_operator(const F& f, long long ord) {
        if constexpr (requires(F g, long long i) { ActedMonoid::op_shift(g, i); }) {
            return ActedMonoid::op_shift(f, ord);
        } else {
            return f;
        }
    }

    F compose_for_child(const F& inherited, const Node& node, long long ord) const {
        F shifted = shift_operator(inherited, ord);
        if (!node.has_lazy) return shifted;
        return ActedMonoid::op_comp(shifted, shift_operator(node.lazy, ord));
    }

    int build(int l, int r, const std::vector<T>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(v[l]));
        int m = (l + r) >> 1;
        int left = build(l, m, v);
        int right = build(m, r, v);
        return new_node(Node(ActedMonoid::op((*_pool)[left].val, (*_pool)[right].val), left, right));
    }

    int build(int l, int r, std::vector<T>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(std::move(v[l])));
        int m = (l + r) >> 1;
        int left = build(l, m, v);
        int right = build(m, r, v);
        return new_node(Node(ActedMonoid::op((*_pool)[left].val, (*_pool)[right].val), left, right));
    }

    template <typename U>
    int build_from_values(int l, int r, const std::vector<U>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(make_value(v[l], l)));
        int m = (l + r) >> 1;
        int left = build_from_values(l, m, v);
        int right = build_from_values(m, r, v);
        return new_node(Node(ActedMonoid::op((*_pool)[left].val, (*_pool)[right].val), left, right));
    }

    void all_apply_to_node(int t, const F& f) const {
        Node& node = (*_pool)[t];
        node.val = mapping_at(f, node.val, 0);
        node.lazy = ActedMonoid::op_comp(f, node.lazy);
        node.has_lazy = true;
    }

    int all_apply_clone(int t, const F& f) const {
        int res = clone_node(t);
        all_apply_to_node(res, f);
        return res;
    }

    void push(int t, int l, int r) const {
        if (!(*_pool)[t].has_lazy) return;
        F lazy = (*_pool)[t].lazy;
        int left = (*_pool)[t].left;
        int right = (*_pool)[t].right;
        int m = (l + r) >> 1;
        left = all_apply_clone(left, lazy);
        right = all_apply_clone(right, shift_operator(lazy, m - l));
        Node& node = (*_pool)[t];
        _pool->replace(node.left, left);
        _pool->replace(node.right, right);
        node.lazy = ActedMonoid::op_id();
        node.has_lazy = false;
    }

    void update(int t) const {
        Node& node = (*_pool)[t];
        node.val = ActedMonoid::op((*_pool)[node.left].val, (*_pool)[node.right].val);
    }

    int set_node(int t, int l, int r, int p, T value) const {
        t = clone_node(t);
        if (r - l == 1) {
            Node& node = (*_pool)[t];
            node.val = std::move(value);
            node.lazy = ActedMonoid::op_id();
            node.has_lazy = false;
            return t;
        }
        push(t, l, r);
        int m = (l + r) >> 1;
        if (p < m) {
            int child = set_node((*_pool)[t].left, l, m, p, std::move(value));
            _pool->replace((*_pool)[t].left, child);
        } else {
            int child = set_node((*_pool)[t].right, m, r, p, std::move(value));
            _pool->replace((*_pool)[t].right, child);
        }
        update(t);
        return t;
    }

    int apply_node(int t, int l, int r, int ql, int qr, const F& f) const {
        if (qr <= l || r <= ql) return t;
        t = clone_node(t);
        if (ql <= l && r <= qr) {
            all_apply_to_node(t, shift_operator(f, l - ql));
            return t;
        }
        push(t, l, r);
        int m = (l + r) >> 1;
        int left = apply_node((*_pool)[t].left, l, m, ql, qr, f);
        int right = apply_node((*_pool)[t].right, m, r, ql, qr, f);
        _pool->replace((*_pool)[t].left, left);
        _pool->replace((*_pool)[t].right, right);
        update(t);
        return t;
    }

    int copy_range_node(int target, int source, int l, int r, int ql, int qr) const {
        if (qr <= l || r <= ql) return target;
        if (ql <= l && r <= qr) return source;

        target = clone_node(target);
        source = clone_node(source);
        _pool->retain(source);
        push(target, l, r);
        push(source, l, r);

        int m = (l + r) >> 1;
        int left = copy_range_node((*_pool)[target].left, (*_pool)[source].left, l, m, ql, qr);
        int right = copy_range_node((*_pool)[target].right, (*_pool)[source].right, m, r, ql, qr);
        _pool->replace((*_pool)[target].left, left);
        _pool->replace((*_pool)[target].right, right);
        update(target);
        _pool->release(source);
        return target;
    }

    T prod_node(int t, int l, int r, int ql, int qr, const F& inherited) const {
        if (!t || qr <= l || r <= ql) return ActedMonoid::id();
        const Node& node = (*_pool)[t];
        if (ql <= l && r <= qr) return mapping_at(inherited, node.val, 0);
        int m = (l + r) >> 1;
        return ActedMonoid::op(prod_node(node.left, l, m, ql, qr, compose_for_child(inherited, node, 0)),
                               prod_node(node.right, m, r, ql, qr, compose_for_child(inherited, node, m - l)));
    }

    void collect_node(int t, int l, int r, int ql, int qr, const F& inherited, std::vector<T>& res) const {
        if (!t || qr <= l || r <= ql) return;
        const Node& node = (*_pool)[t];
        if (r - l == 1) {
            res.push_back(mapping_at(inherited, node.val, 0));
            return;
        }
        int m = (l + r) >> 1;
        collect_node(node.left, l, m, ql, qr, compose_for_child(inherited, node, 0), res);
        collect_node(node.right, m, r, ql, qr, compose_for_child(inherited, node, m - l), res);
    }

    template <class G>
    int max_right_node(int t, int l, int r, int ql, T& sm, const F& inherited, G& g) const {
        if (r <= ql) return r;
        const Node& node = (*_pool)[t];
        if (ql <= l) {
            T nxt = ActedMonoid::op(sm, mapping_at(inherited, node.val, 0));
            if (g(nxt)) {
                sm = std::move(nxt);
                return r;
            }
            if (r - l == 1) return l;
        }
        int m = (l + r) >> 1;
        int res = max_right_node(node.left, l, m, ql, sm, compose_for_child(inherited, node, 0), g);
        if (res < m) return res;
        return max_right_node(node.right, m, r, ql, sm, compose_for_child(inherited, node, m - l), g);
    }

    template <class G>
    int min_left_node(int t, int l, int r, int qr, T& sm, const F& inherited, G& g) const {
        if (qr <= l) return l;
        const Node& node = (*_pool)[t];
        if (r <= qr) {
            T nxt = ActedMonoid::op(mapping_at(inherited, node.val, 0), sm);
            if (g(nxt)) {
                sm = std::move(nxt);
                return l;
            }
            if (r - l == 1) return r;
        }
        int m = (l + r) >> 1;
        int res = min_left_node(node.right, m, r, qr, sm, compose_for_child(inherited, node, m - l), g);
        if (m < res) return res;
        return min_left_node(node.left, l, m, qr, sm, compose_for_child(inherited, node, 0), g);
    }

   public:
    PersistentLazySegtree() : PersistentLazySegtree(0) {}

    explicit PersistentLazySegtree(int n) : _n(n), _root(0), _pool(std::make_shared<Pool>()) {
        assert(0 <= n);
        if (_n > 0) _root = build(0, _n, std::vector<T>(_n, ActedMonoid::id()));
        _pool->retain(_root);
    }

    explicit PersistentLazySegtree(const std::vector<T>& v)
        : _n(int(v.size())), _root(0), _pool(std::make_shared<Pool>()) {
        _pool->reserve(v.size() * 2);
        if (_n > 0) _root = build(0, _n, v);
        _pool->retain(_root);
    }

    explicit PersistentLazySegtree(std::vector<T>&& v) : _n(int(v.size())), _root(0), _pool(std::make_shared<Pool>()) {
        _pool->reserve(v.size() * 2);
        if (_n > 0) _root = build(0, _n, v);
        _pool->retain(_root);
    }

    template <typename U>
        requires(!std::same_as<U, T>) &&
                (requires(U x) { ActedMonoid::make(x); } || requires(U x, int i) { ActedMonoid::make(x, i); } ||
                 std::convertible_to<U, T>)
    explicit PersistentLazySegtree(const std::vector<U>& v)
        : _n(int(v.size())), _root(0), _pool(std::make_shared<Pool>()) {
        _pool->reserve(v.size() * 2);
        if (_n > 0) _root = build_from_values(0, _n, v);
        _pool->retain(_root);
    }

    PersistentLazySegtree(const PersistentLazySegtree& other) : _n(other._n), _root(other._root), _pool(other._pool) {
        if (_pool) _pool->retain(_root);
    }

    PersistentLazySegtree(PersistentLazySegtree&& other) noexcept
        : _n(other._n), _root(other._root), _pool(std::move(other._pool)) {
        other._n = 0;
        other._root = 0;
    }

    PersistentLazySegtree& operator=(const PersistentLazySegtree& other) {
        if (this == &other) return *this;
        if (other._pool) other._pool->retain(other._root);
        if (_pool) _pool->release(_root);
        _n = other._n;
        _root = other._root;
        _pool = other._pool;
        return *this;
    }

    PersistentLazySegtree& operator=(PersistentLazySegtree&& other) noexcept {
        if (this == &other) return *this;
        if (_pool) _pool->release(_root);
        _n = other._n;
        _root = other._root;
        _pool = std::move(other._pool);
        other._n = 0;
        other._root = 0;
        return *this;
    }

    ~PersistentLazySegtree() {
        if (_pool) _pool->release(_root);
    }

    int size() const { return _n; }

    bool empty() const { return _n == 0; }

    void release() {
        if (_pool) _pool->release(_root);
        _pool = std::make_shared<Pool>();
        _root = 0;
        _n = 0;
    }

    std::size_t node_count() const { return _pool ? _pool->size() : 0; }

    PersistentLazySegtree set(int p, T x) const {
        assert(0 <= p && p < _n);
        return PersistentLazySegtree(_n, set_node(_root, 0, _n, p, std::move(x)), _pool);
    }

    T get(int p) const {
        assert(0 <= p && p < _n);
        return prod(p, p + 1);
    }

    T operator[](int p) const { return get(p); }

    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return ActedMonoid::id();
        return prod_node(_root, 0, _n, l, r, ActedMonoid::op_id());
    }

    T all_prod() const { return _root ? (*_pool)[_root].val : ActedMonoid::id(); }

    std::vector<T> to_vector() const { return to_vector(0, _n); }

    std::vector<T> to_vector(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        std::vector<T> res;
        res.reserve(r - l);
        collect_node(_root, 0, _n, l, r, ActedMonoid::op_id(), res);
        return res;
    }

    PersistentLazySegtree apply(int p, const F& f) const {
        assert(0 <= p && p < _n);
        return apply(p, p + 1, f);
    }

    PersistentLazySegtree apply(int l, int r, const F& f) const {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return *this;
        return PersistentLazySegtree(_n, apply_node(_root, 0, _n, l, r, f), _pool);
    }

    PersistentLazySegtree copy_range_from(const PersistentLazySegtree& source, int l, int r) const {
        assert(_n == source._n);
        assert(_pool == source._pool);
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return *this;
        int root = copy_range_node(_root, source._root, 0, _n, l, r);
        return PersistentLazySegtree(_n, root, _pool);
    }

    template <class G>
    int max_right(int l, G g) const {
        assert(0 <= l && l <= _n);
        assert(g(ActedMonoid::id()));
        if (l == _n) return _n;
        T sm = ActedMonoid::id();
        return max_right_node(_root, 0, _n, l, sm, ActedMonoid::op_id(), g);
    }

    template <class G>
    int min_left(int r, G g) const {
        assert(0 <= r && r <= _n);
        assert(g(ActedMonoid::id()));
        if (r == 0) return 0;
        T sm = ActedMonoid::id();
        return min_left_node(_root, 0, _n, r, sm, ActedMonoid::op_id(), g);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_LAZY_SEGTREE_HPP
