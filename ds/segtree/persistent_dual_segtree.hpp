#ifndef M1UNE_PERSISTENT_DUAL_SEGTREE_HPP
#define M1UNE_PERSISTENT_DUAL_SEGTREE_HPP 1

#include <cassert>
#include <concepts>
#include <memory>
#include <utility>
#include <vector>

#include "../../monoid/concept.hpp"
#include "persistent_node_pool.hpp"

namespace m1une {
namespace ds {

template <m1une::monoid::IsMonoid Monoid>
struct PersistentDualSegtree {
    using T = typename Monoid::value_type;

   private:
    struct Node {
        T val;
        int left, right;
        int references;
        bool has_lazy;

        Node() : val(Monoid::id()), left(0), right(0), references(0), has_lazy(false) {}
        explicit Node(T value) : val(std::move(value)), left(0), right(0), references(0), has_lazy(false) {}
        Node(int left_child, int right_child)
            : val(Monoid::id()), left(left_child), right(right_child), references(0), has_lazy(false) {}
    };

    using Pool = detail::PersistentNodePool<Node>;

    int _n;
    int _root;
    std::shared_ptr<Pool> _pool;

    explicit PersistentDualSegtree(int n, int root, std::shared_ptr<Pool> pool)
        : _n(n), _root(root), _pool(std::move(pool)) {
        _pool->retain(_root);
    }

    int new_node(const Node& node) const { return _pool->emplace(node); }

    int new_node(Node&& node) const { return _pool->emplace(std::move(node)); }

    int clone_node(int t) const { return _pool->clone(t); }

    template <typename U>
    static T make_value(const U& value, int index) {
        if constexpr (requires(U x) { Monoid::make(x); }) {
            return Monoid::make(value);
        } else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {
            return Monoid::make(value, index);
        } else {
            return static_cast<T>(value);
        }
    }

    T compose_for_child(const T& inherited, const Node& node) const {
        if (!node.has_lazy) return inherited;
        return Monoid::op(inherited, node.val);
    }

    int build(int l, int r, const std::vector<T>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(v[l]));
        int m = (l + r) >> 1;
        return new_node(Node(build(l, m, v), build(m, r, v)));
    }

    int build(int l, int r, std::vector<T>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(std::move(v[l])));
        int m = (l + r) >> 1;
        return new_node(Node(build(l, m, v), build(m, r, v)));
    }

    template <typename U>
    int build_from_values(int l, int r, const std::vector<U>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(make_value(v[l], l)));
        int m = (l + r) >> 1;
        return new_node(Node(build_from_values(l, m, v), build_from_values(m, r, v)));
    }

    void all_apply_to_node(int t, const T& x, int l, int r) const {
        Node& node = (*_pool)[t];
        if (r - l == 1) {
            node.val = Monoid::op(x, node.val);
        } else {
            node.val = node.has_lazy ? Monoid::op(x, node.val) : x;
            node.has_lazy = true;
        }
    }

    int all_apply_clone(int t, const T& x, int l, int r, bool copy_on_write = false) const {
        int res = copy_on_write ? _pool->clone_if_shared(t) : clone_node(t);
        all_apply_to_node(res, x, l, r);
        return res;
    }

    void push(int t, int l, int r, bool copy_on_write = false) const {
        Node node = (*_pool)[t];
        if (!node.has_lazy || r - l == 1) return;
        int m = (l + r) >> 1;
        int left = all_apply_clone(node.left, node.val, l, m, copy_on_write);
        int right = all_apply_clone(node.right, node.val, m, r, copy_on_write);
        Node& target = (*_pool)[t];
        _pool->replace(target.left, left);
        _pool->replace(target.right, right);
        target.val = Monoid::id();
        target.has_lazy = false;
    }

    int set_node(int t, int l, int r, int p, T value, bool copy_on_write = false) const {
        t = copy_on_write ? _pool->clone_if_shared(t) : clone_node(t);
        if (r - l == 1) {
            Node& node = (*_pool)[t];
            node.val = std::move(value);
            node.has_lazy = false;
            return t;
        }
        push(t, l, r, copy_on_write);
        int m = (l + r) >> 1;
        if (p < m) {
            int child = set_node((*_pool)[t].left, l, m, p, std::move(value), copy_on_write);
            _pool->replace((*_pool)[t].left, child);
        } else {
            int child = set_node((*_pool)[t].right, m, r, p, std::move(value), copy_on_write);
            _pool->replace((*_pool)[t].right, child);
        }
        return t;
    }

    int apply_node(int t, int l, int r, int ql, int qr, const T& x, bool copy_on_write = false) const {
        if (qr <= l || r <= ql) return t;
        t = copy_on_write ? _pool->clone_if_shared(t) : clone_node(t);
        if (ql <= l && r <= qr) {
            all_apply_to_node(t, x, l, r);
            return t;
        }
        push(t, l, r, copy_on_write);
        int m = (l + r) >> 1;
        int left = apply_node((*_pool)[t].left, l, m, ql, qr, x, copy_on_write);
        int right = apply_node((*_pool)[t].right, m, r, ql, qr, x, copy_on_write);
        _pool->replace((*_pool)[t].left, left);
        _pool->replace((*_pool)[t].right, right);
        return t;
    }

    T get_node(int t, int l, int r, int p, const T& inherited) const {
        const Node& node = (*_pool)[t];
        if (r - l == 1) return Monoid::op(inherited, node.val);
        int m = (l + r) >> 1;
        if (p < m) return get_node(node.left, l, m, p, compose_for_child(inherited, node));
        return get_node(node.right, m, r, p, compose_for_child(inherited, node));
    }

    void collect_node(int t, int l, int r, int ql, int qr, const T& inherited, std::vector<T>& res) const {
        if (!t || qr <= l || r <= ql) return;
        const Node& node = (*_pool)[t];
        if (r - l == 1) {
            res.push_back(Monoid::op(inherited, node.val));
            return;
        }
        int m = (l + r) >> 1;
        T next = compose_for_child(inherited, node);
        collect_node(node.left, l, m, ql, qr, next, res);
        collect_node(node.right, m, r, ql, qr, next, res);
    }

   public:
    PersistentDualSegtree() : PersistentDualSegtree(0) {}

    explicit PersistentDualSegtree(int n) : _n(n), _root(0), _pool(std::make_shared<Pool>()) {
        assert(0 <= n);
        if (_n > 0) _root = build(0, _n, std::vector<T>(_n, Monoid::id()));
        _pool->retain(_root);
    }

    explicit PersistentDualSegtree(const std::vector<T>& v)
        : _n(int(v.size())), _root(0), _pool(std::make_shared<Pool>()) {
        _pool->reserve(v.size() * 2);
        if (_n > 0) _root = build(0, _n, v);
        _pool->retain(_root);
    }

    explicit PersistentDualSegtree(std::vector<T>&& v) : _n(int(v.size())), _root(0), _pool(std::make_shared<Pool>()) {
        _pool->reserve(v.size() * 2);
        if (_n > 0) _root = build(0, _n, v);
        _pool->retain(_root);
    }

    template <typename U>
        requires(!std::same_as<U, T>) &&
                (requires(U x) { Monoid::make(x); } || requires(U x, int i) { Monoid::make(x, i); } ||
                 std::convertible_to<U, T>)
    explicit PersistentDualSegtree(const std::vector<U>& v)
        : _n(int(v.size())), _root(0), _pool(std::make_shared<Pool>()) {
        _pool->reserve(v.size() * 2);
        if (_n > 0) _root = build_from_values(0, _n, v);
        _pool->retain(_root);
    }

    PersistentDualSegtree(const PersistentDualSegtree& other) : _n(other._n), _root(other._root), _pool(other._pool) {
        if (_pool) _pool->retain(_root);
    }
    PersistentDualSegtree(PersistentDualSegtree&& other) noexcept
        : _n(other._n), _root(other._root), _pool(std::move(other._pool)) {
        other._n = 0;
        other._root = 0;
    }
    PersistentDualSegtree& operator=(const PersistentDualSegtree& other) {
        if (this == &other) return *this;
        if (other._pool) other._pool->retain(other._root);
        if (_pool) _pool->release(_root);
        _n = other._n;
        _root = other._root;
        _pool = other._pool;
        return *this;
    }
    PersistentDualSegtree& operator=(PersistentDualSegtree&& other) noexcept {
        if (this == &other) return *this;
        if (_pool) _pool->release(_root);
        _n = other._n;
        _root = other._root;
        _pool = std::move(other._pool);
        other._n = 0;
        other._root = 0;
        return *this;
    }
    ~PersistentDualSegtree() {
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

    PersistentDualSegtree set(int p, T x) const {
        assert(0 <= p && p < _n);
        return PersistentDualSegtree(_n, set_node(_root, 0, _n, p, std::move(x)), _pool);
    }

    void set_inplace(int p, T x) {
        assert(0 <= p && p < _n);
        int root = set_node(_root, 0, _n, p, std::move(x), true);
        _pool->replace(_root, root);
    }

    T get(int p) const {
        assert(0 <= p && p < _n);
        return get_node(_root, 0, _n, p, Monoid::id());
    }

    T operator[](int p) const { return get(p); }

    PersistentDualSegtree apply(int p, const T& x) const {
        assert(0 <= p && p < _n);
        return apply(p, p + 1, x);
    }

    PersistentDualSegtree apply(int l, int r, const T& x) const {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return *this;
        return PersistentDualSegtree(_n, apply_node(_root, 0, _n, l, r, x), _pool);
    }

    void apply_inplace(int p, const T& x) {
        assert(0 <= p && p < _n);
        apply_inplace(p, p + 1, x);
    }

    void apply_inplace(int l, int r, const T& x) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;
        int root = apply_node(_root, 0, _n, l, r, x, true);
        _pool->replace(_root, root);
    }

    std::vector<T> to_vector() const { return to_vector(0, _n); }

    std::vector<T> to_vector(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        std::vector<T> res;
        res.reserve(r - l);
        collect_node(_root, 0, _n, l, r, Monoid::id(), res);
        return res;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_DUAL_SEGTREE_HPP
