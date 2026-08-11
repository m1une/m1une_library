#ifndef M1UNE_PERSISTENT_SEGTREE_HPP
#define M1UNE_PERSISTENT_SEGTREE_HPP 1

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
struct PersistentSegtree {
    using T = typename Monoid::value_type;

   private:
    struct Node {
        T val;
        int left, right;
        int references;

        Node() : val(Monoid::id()), left(0), right(0), references(0) {}
        explicit Node(T value) : val(std::move(value)), left(0), right(0), references(0) {}
        Node(T value, int left_child, int right_child)
            : val(std::move(value)), left(left_child), right(right_child), references(0) {}
    };

    using Pool = detail::PersistentNodePool<Node>;

    int _n;
    int _root;
    std::shared_ptr<Pool> _pool;

    explicit PersistentSegtree(int n, int root, std::shared_ptr<Pool> pool)
        : _n(n), _root(root), _pool(std::move(pool)) {
        _pool->retain(_root);
    }

    int new_node(const Node& node) const { return _pool->emplace(node); }

    int new_node(Node&& node) const { return _pool->emplace(std::move(node)); }

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

    int build(int l, int r, const std::vector<T>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(v[l]));
        int m = (l + r) >> 1;
        int left = build(l, m, v);
        int right = build(m, r, v);
        return new_node(Node(Monoid::op(_pool->nodes[left].val, _pool->nodes[right].val), left, right));
    }

    int build(int l, int r, std::vector<T>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(std::move(v[l])));
        int m = (l + r) >> 1;
        int left = build(l, m, v);
        int right = build(m, r, v);
        return new_node(Node(Monoid::op(_pool->nodes[left].val, _pool->nodes[right].val), left, right));
    }

    template <typename U>
    int build_from_values(int l, int r, const std::vector<U>& v) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(make_value(v[l], l)));
        int m = (l + r) >> 1;
        int left = build_from_values(l, m, v);
        int right = build_from_values(m, r, v);
        return new_node(Node(Monoid::op(_pool->nodes[left].val, _pool->nodes[right].val), left, right));
    }

    int set_node(int t, int l, int r, int p, T value, bool copy_on_write = false) const {
        if (copy_on_write) t = _pool->clone_if_shared(t);
        if (r - l == 1) {
            if (copy_on_write) {
                _pool->nodes[t].val = std::move(value);
                return t;
            }
            return new_node(Node(std::move(value)));
        }
        int m = (l + r) >> 1;
        int left = _pool->nodes[t].left;
        int right = _pool->nodes[t].right;
        if (p < m) {
            left = set_node(left, l, m, p, std::move(value), copy_on_write);
        } else {
            right = set_node(right, m, r, p, std::move(value), copy_on_write);
        }
        T product = Monoid::op(_pool->nodes[left].val, _pool->nodes[right].val);
        if (copy_on_write) {
            _pool->replace(_pool->nodes[t].left, left);
            _pool->replace(_pool->nodes[t].right, right);
            _pool->nodes[t].val = std::move(product);
            return t;
        }
        return new_node(Node(std::move(product), left, right));
    }

    T prod_node(int t, int l, int r, int ql, int qr) const {
        if (!t || qr <= l || r <= ql) return Monoid::id();
        if (ql <= l && r <= qr) return _pool->nodes[t].val;
        int m = (l + r) >> 1;
        return Monoid::op(prod_node(_pool->nodes[t].left, l, m, ql, qr),
                          prod_node(_pool->nodes[t].right, m, r, ql, qr));
    }

    void collect_node(int t, int l, int r, int ql, int qr, std::vector<T>& res) const {
        if (!t || qr <= l || r <= ql) return;
        if (r - l == 1) {
            res.push_back(_pool->nodes[t].val);
            return;
        }
        int m = (l + r) >> 1;
        collect_node(_pool->nodes[t].left, l, m, ql, qr, res);
        collect_node(_pool->nodes[t].right, m, r, ql, qr, res);
    }

    template <class F>
    int max_right_node(int t, int l, int r, int ql, T& sm, F& f) const {
        if (r <= ql) return r;
        if (ql <= l) {
            T nxt = Monoid::op(sm, _pool->nodes[t].val);
            if (f(nxt)) {
                sm = std::move(nxt);
                return r;
            }
            if (r - l == 1) return l;
        }
        int m = (l + r) >> 1;
        int res = max_right_node(_pool->nodes[t].left, l, m, ql, sm, f);
        if (res < m) return res;
        return max_right_node(_pool->nodes[t].right, m, r, ql, sm, f);
    }

    template <class F>
    int min_left_node(int t, int l, int r, int qr, T& sm, F& f) const {
        if (qr <= l) return l;
        if (r <= qr) {
            T nxt = Monoid::op(_pool->nodes[t].val, sm);
            if (f(nxt)) {
                sm = std::move(nxt);
                return l;
            }
            if (r - l == 1) return r;
        }
        int m = (l + r) >> 1;
        int res = min_left_node(_pool->nodes[t].right, m, r, qr, sm, f);
        if (m < res) return res;
        return min_left_node(_pool->nodes[t].left, l, m, qr, sm, f);
    }

   public:
    PersistentSegtree() : PersistentSegtree(0) {}

    explicit PersistentSegtree(int n) : _n(n), _root(0), _pool(std::make_shared<Pool>()) {
        assert(0 <= n);
        if (_n > 0) _root = build(0, _n, std::vector<T>(_n, Monoid::id()));
        _pool->retain(_root);
    }

    explicit PersistentSegtree(const std::vector<T>& v) : _n(int(v.size())), _root(0), _pool(std::make_shared<Pool>()) {
        _pool->reserve(v.size() * 2);
        if (_n > 0) _root = build(0, _n, v);
        _pool->retain(_root);
    }

    explicit PersistentSegtree(std::vector<T>&& v) : _n(int(v.size())), _root(0), _pool(std::make_shared<Pool>()) {
        _pool->reserve(v.size() * 2);
        if (_n > 0) _root = build(0, _n, v);
        _pool->retain(_root);
    }

    template <typename U>
        requires(!std::same_as<U, T>) &&
                (requires(U x) { Monoid::make(x); } || requires(U x, int i) { Monoid::make(x, i); } ||
                 std::convertible_to<U, T>)
    explicit PersistentSegtree(const std::vector<U>& v)
        : _n(int(v.size())), _root(0), _pool(std::make_shared<Pool>()) {
        _pool->reserve(v.size() * 2);
        if (_n > 0) _root = build_from_values(0, _n, v);
        _pool->retain(_root);
    }

    PersistentSegtree(const PersistentSegtree& other) : _n(other._n), _root(other._root), _pool(other._pool) {
        if (_pool) _pool->retain(_root);
    }

    PersistentSegtree(PersistentSegtree&& other) noexcept
        : _n(other._n), _root(other._root), _pool(std::move(other._pool)) {
        other._n = 0;
        other._root = 0;
    }

    PersistentSegtree& operator=(const PersistentSegtree& other) {
        if (this == &other) return *this;
        if (other._pool) other._pool->retain(other._root);
        if (_pool) _pool->release(_root);
        _n = other._n;
        _root = other._root;
        _pool = other._pool;
        return *this;
    }

    PersistentSegtree& operator=(PersistentSegtree&& other) noexcept {
        if (this == &other) return *this;
        if (_pool) _pool->release(_root);
        _n = other._n;
        _root = other._root;
        _pool = std::move(other._pool);
        other._n = 0;
        other._root = 0;
        return *this;
    }

    ~PersistentSegtree() {
        if (_pool) _pool->release(_root);
    }

    int size() const { return _n; }

    bool empty() const { return _n == 0; }

    // Drops this version immediately. Other versions and shared nodes stay valid.
    void release() {
        if (_pool) _pool->release(_root);
        _pool = std::make_shared<Pool>();
        _root = 0;
        _n = 0;
    }

    std::size_t node_count() const { return _pool ? _pool->size() : 0; }

    PersistentSegtree set(int p, T x) const {
        assert(0 <= p && p < _n);
        return PersistentSegtree(_n, set_node(_root, 0, _n, p, std::move(x)), _pool);
    }

    void set_inplace(int p, T x) {
        assert(0 <= p && p < _n);
        int root = set_node(_root, 0, _n, p, std::move(x), true);
        _pool->replace(_root, root);
    }

    T get(int p) const {
        assert(0 <= p && p < _n);
        int t = _root;
        int l = 0, r = _n;
        while (r - l > 1) {
            int m = (l + r) >> 1;
            if (p < m) {
                t = _pool->nodes[t].left;
                r = m;
            } else {
                t = _pool->nodes[t].right;
                l = m;
            }
        }
        return _pool->nodes[t].val;
    }

    T operator[](int p) const { return get(p); }

    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return Monoid::id();
        return prod_node(_root, 0, _n, l, r);
    }

    T all_prod() const { return _root ? _pool->nodes[_root].val : Monoid::id(); }

    std::vector<T> to_vector() const { return to_vector(0, _n); }

    std::vector<T> to_vector(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        std::vector<T> res;
        res.reserve(r - l);
        collect_node(_root, 0, _n, l, r, res);
        return res;
    }

    template <class F>
    int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(Monoid::id()));
        if (l == _n) return _n;
        T sm = Monoid::id();
        return max_right_node(_root, 0, _n, l, sm, f);
    }

    template <class F>
    int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(Monoid::id()));
        if (r == 0) return 0;
        T sm = Monoid::id();
        return min_left_node(_root, 0, _n, r, sm, f);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_SEGTREE_HPP
