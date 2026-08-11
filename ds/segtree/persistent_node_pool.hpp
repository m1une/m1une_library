#ifndef M1UNE_PERSISTENT_NODE_POOL_HPP
#define M1UNE_PERSISTENT_NODE_POOL_HPP 1

#include <cassert>
#include <cstddef>
#include <limits>
#include <utility>
#include <vector>

namespace m1une {
namespace ds {
namespace detail {

// Node must have integer `left`, `right`, and `references` members.
template <class Node>
struct PersistentNodePool {
    std::vector<Node> nodes;
    int first_free = 0;
    std::size_t live_nodes = 0;

   private:
    void release_zero(int node) {
        int left = nodes[node].left;
        int right = nodes[node].right;
        nodes[node] = Node();
        nodes[node].left = first_free;
        first_free = node;
        --live_nodes;
        if (left && --nodes[left].references == 0) release_zero(left);
        if (right && --nodes[right].references == 0) release_zero(right);
    }

   public:
    PersistentNodePool() { nodes.emplace_back(); }

    void reserve(std::size_t capacity) { nodes.reserve(capacity + 1); }

    Node& operator[](int node) { return nodes[node]; }

    const Node& operator[](int node) const { return nodes[node]; }

    void retain(int node) {
        if (node) ++nodes[node].references;
    }

    void release(int node) {
        if (!node) return;
        assert(nodes[node].references > 0);
        if (--nodes[node].references == 0) release_zero(node);
    }

    template <class... Args>
    int emplace(Args&&... args) {
        int result;
        if (!first_free) {
            assert(nodes.size() < std::size_t(std::numeric_limits<int>::max()));
            nodes.emplace_back(std::forward<Args>(args)...);
            result = int(nodes.size()) - 1;
        } else {
            result = first_free;
            first_free = nodes[result].left;
            nodes[result] = Node(std::forward<Args>(args)...);
        }
        Node& node = nodes[result];
        node.references = 0;
        retain(node.left);
        retain(node.right);
        ++live_nodes;
        return result;
    }

    int clone(int node) {
        assert(node);
        Node copy = nodes[node];
        return emplace(std::move(copy));
    }

    bool unique(int node) const {
        return !node || nodes[node].references == 1;
    }

    // Returns node itself when it has one owner, otherwise an unowned clone.
    // The caller must attach a returned clone with replace() before it can be
    // released or exposed as a root.
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

    std::size_t size() const { return live_nodes; }
};

}  // namespace detail
}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_NODE_POOL_HPP
