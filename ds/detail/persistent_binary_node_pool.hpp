#ifndef M1UNE_DS_DETAIL_PERSISTENT_BINARY_NODE_POOL_HPP
#define M1UNE_DS_DETAIL_PERSISTENT_BINARY_NODE_POOL_HPP 1

#include <cassert>
#include <cstddef>
#include <deque>
#include <limits>
#include <optional>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {
namespace detail {

// Node must have integer `l` and `r` members. New nodes initially have no
// owner; discard_unreferenced() removes temporary path-copy nodes after the
// result roots have been retained.
template <class Node, int null_node = -1>
struct PersistentBinaryNodePool {
   private:
    std::deque<std::optional<Node>> _nodes;
    std::vector<int> _references;
    std::vector<int> _next_free;
    std::vector<int> _unowned;
    int _first_free = -1;
    std::size_t _live_nodes = 0;

    void release_zero(int node) {
        assert(node != null_node && _nodes[node].has_value());
        int left = (*_nodes[node]).l;
        int right = (*_nodes[node]).r;
        _nodes[node].reset();
        _next_free[node] = _first_free;
        _first_free = node;
        --_live_nodes;
        if (left != null_node && --_references[left] == 0) release_zero(left);
        if (right != null_node && --_references[right] == 0) release_zero(right);
    }

   public:
    PersistentBinaryNodePool() {
        if constexpr (null_node == 0) {
            _nodes.emplace_back();
            _references.push_back(0);
            _next_free.push_back(-1);
        }
    }

    Node& operator[](int node) {
        assert(node != null_node && _nodes[node].has_value());
        return *_nodes[node];
    }

    const Node& operator[](int node) const {
        assert(node != null_node && _nodes[node].has_value());
        return *_nodes[node];
    }

    template <class... Args>
    int emplace(Args&&... args) {
        int result;
        if (_first_free == -1) {
            assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));
            result = int(_nodes.size());
            _nodes.emplace_back(std::in_place, std::forward<Args>(args)...);
            _references.push_back(0);
            _next_free.push_back(-1);
        } else {
            result = _first_free;
            _first_free = _next_free[result];
            _nodes[result].emplace(std::forward<Args>(args)...);
            _references[result] = 0;
        }
        retain((*_nodes[result]).l);
        retain((*_nodes[result]).r);
        _unowned.push_back(result);
        ++_live_nodes;
        return result;
    }

    void retain(int node) {
        if (node != null_node) {
            assert(_nodes[node].has_value());
            ++_references[node];
        }
    }

    void release(int node) {
        if (node == null_node) return;
        assert(_nodes[node].has_value() && _references[node] > 0);
        if (--_references[node] == 0) release_zero(node);
    }

    bool unique(int node) const {
        return node == null_node || _references[node] == 1;
    }

    int clone(int node) {
        assert(node != null_node && _nodes[node].has_value());
        return emplace(*_nodes[node]);
    }

    // Returns node itself when it has one owner, otherwise an unowned clone.
    // A returned clone becomes owned when a root or parent edge retains it.
    int clone_if_shared(int node) {
        if (unique(node)) return node;
        return clone(node);
    }

    void replace(int& edge, int node) {
        if (edge == node) return;
        retain(node);
        int old = edge;
        edge = node;
        release(old);
    }

    void discard_unreferenced() {
        while (!_unowned.empty()) {
            int node = _unowned.back();
            _unowned.pop_back();
            if (_nodes[node].has_value() && _references[node] == 0) release_zero(node);
        }
    }

    void reserve(std::size_t) {}

    int next_index() const { return _first_free == -1 ? int(_nodes.size()) : _first_free; }

    std::size_t size() const { return _live_nodes; }
};

}  // namespace detail
}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_DETAIL_PERSISTENT_BINARY_NODE_POOL_HPP
