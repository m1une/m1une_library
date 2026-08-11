#ifndef M1UNE_PERSISTENT_DSU_HPP
#define M1UNE_PERSISTENT_DSU_HPP 1

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

#include "../detail/persistent_binary_node_pool.hpp"

namespace m1une {
namespace ds {

struct PersistentDsu {
   private:
    struct Node {
        int val;
        int l, r;

        Node() : val(0), l(0), r(0) {}
        explicit Node(int value) : val(value), l(0), r(0) {}
        Node(int value, int left, int right) : val(value), l(left), r(right) {}
    };

    int _n;
    int _root;
    using Pool = detail::PersistentBinaryNodePool<Node, 0>;

    std::shared_ptr<Pool> _pool;

    explicit PersistentDsu(int n, int root, std::shared_ptr<Pool> pool)
        : _n(n), _root(root), _pool(std::move(pool)) {
        _pool->retain(_root);
    }

    int new_node(const Node& node) const {
        return _pool->emplace(node);
    }

    int new_node(Node&& node) const {
        return _pool->emplace(std::move(node));
    }

    int build(int l, int r) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(-1));
        int m = (l + r) >> 1;
        int left = build(l, m);
        int right = build(m, r);
        return new_node(Node(0, left, right));
    }

    int set_node(int t, int l, int r, int p, int value, bool copy_on_write = false) const {
        if (copy_on_write) t = _pool->clone_if_shared(t);
        if (r - l == 1) {
            if (copy_on_write) {
                (*_pool)[t].val = value;
                return t;
            }
            return new_node(Node(value));
        }
        int m = (l + r) >> 1;
        int left = (*_pool)[t].l;
        int right = (*_pool)[t].r;
        if (p < m) {
            left = set_node(left, l, m, p, value, copy_on_write);
        } else {
            right = set_node(right, m, r, p, value, copy_on_write);
        }
        if (copy_on_write) {
            _pool->replace((*_pool)[t].l, left);
            _pool->replace((*_pool)[t].r, right);
            return t;
        }
        return new_node(Node(0, left, right));
    }

    PersistentDsu make_version(int root) const {
        PersistentDsu result(_n, root, _pool);
        _pool->discard_unreferenced();
        return result;
    }

    int get_node(int t, int l, int r, int p) const {
        while (r - l > 1) {
            int m = (l + r) >> 1;
            if (p < m) {
                t = (*_pool)[t].l;
                r = m;
            } else {
                t = (*_pool)[t].r;
                l = m;
            }
        }
        return (*_pool)[t].val;
    }

   public:
    PersistentDsu() : PersistentDsu(0) {}

    explicit PersistentDsu(int n) : _n(n), _root(0), _pool(std::make_shared<Pool>()) {
        assert(0 <= n);
        _pool->reserve(n * 2 + 1);
        if (_n > 0) _root = build(0, _n);
        _pool->retain(_root);
        _pool->discard_unreferenced();
    }

    PersistentDsu(const PersistentDsu& other) : _n(other._n), _root(other._root), _pool(other._pool) {
        if (_pool) _pool->retain(_root);
    }

    PersistentDsu(PersistentDsu&& other) noexcept
        : _n(other._n), _root(other._root), _pool(std::move(other._pool)) {
        other._n = 0;
        other._root = 0;
    }

    PersistentDsu& operator=(const PersistentDsu& other) {
        if (this == &other) return *this;
        if (other._pool) other._pool->retain(other._root);
        if (_pool) _pool->release(_root);
        _n = other._n;
        _root = other._root;
        _pool = other._pool;
        return *this;
    }

    PersistentDsu& operator=(PersistentDsu&& other) noexcept {
        if (this == &other) return *this;
        if (_pool) _pool->release(_root);
        _n = other._n;
        _root = other._root;
        _pool = std::move(other._pool);
        other._n = 0;
        other._root = 0;
        return *this;
    }

    ~PersistentDsu() {
        if (_pool) _pool->release(_root);
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    void release() {
        if (_pool) _pool->release(_root);
        _n = 0;
        _root = 0;
        _pool = std::make_shared<Pool>();
    }

    std::size_t node_count() const { return _pool ? _pool->size() : 0; }

    int leader(int a) const {
        assert(0 <= a && a < _n);
        int x = a;
        int p = get(x);
        while (p >= 0) {
            x = p;
            p = get(x);
        }
        return x;
    }

    bool same(int a, int b) const {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int group_size(int a) const {
        assert(0 <= a && a < _n);
        return -get(leader(a));
    }

    int size(int a) const {
        return group_size(a);
    }

    int get(int p) const {
        assert(0 <= p && p < _n);
        return get_node(_root, 0, _n, p);
    }

    PersistentDsu merge(int a, int b) const {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return *this;
        int sx = -get(x), sy = -get(y);
        if (sx < sy) {
            std::swap(x, y);
            std::swap(sx, sy);
        }
        int root = set_node(_root, 0, _n, x, -(sx + sy));
        root = set_node(root, 0, _n, y, x);
        return make_version(root);
    }

    bool merge_inplace(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return false;
        int sx = -get(x), sy = -get(y);
        if (sx < sy) {
            std::swap(x, y);
            std::swap(sx, sy);
        }
        int root = set_node(_root, 0, _n, x, -(sx + sy), true);
        _pool->replace(_root, root);
        root = set_node(_root, 0, _n, y, x, true);
        _pool->replace(_root, root);
        _pool->discard_unreferenced();
        return true;
    }

    std::vector<std::vector<int>> groups() const {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(std::remove_if(result.begin(), result.end(), [&](const std::vector<int>& v) { return v.empty(); }),
                     result.end());
        return result;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_DSU_HPP
