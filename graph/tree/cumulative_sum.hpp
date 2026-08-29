#ifndef M1UNE_TREE_CUMULATIVE_SUM_HPP
#define M1UNE_TREE_CUMULATIVE_SUM_HPP 1

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "../../monoid/add.hpp"
#include "../../monoid/concept.hpp"
#include "../graph.hpp"

namespace m1une {
namespace tree {

// Static cumulative products on root paths. Values are attached to vertices by
// default; set EdgeValues to true to index them by graph edge id instead.
template <m1une::monoid::IsCommutativeGroup Group, bool EdgeValues = false>
class TreeCumulativeProduct {
   public:
    using value_type = typename Group::value_type;

   private:
    int _n = 0;
    int _root = -1;
    std::vector<int> _parent;
    std::vector<int> _depth;
    std::vector<int> _head;
    std::vector<value_type> _prefix;

    void check_vertex(int vertex) const {
        assert(0 <= vertex && vertex < _n);
    }

   public:
    TreeCumulativeProduct() = default;

    template <class EdgeCost>
    explicit TreeCumulativeProduct(
        const m1une::graph::Graph<EdgeCost>& graph,
        const std::vector<value_type>& values,
        int root = 0
    ) {
        build(graph, values, root);
    }

    template <class EdgeCost>
    void build(
        const m1une::graph::Graph<EdgeCost>& graph,
        const std::vector<value_type>& values,
        int root = 0
    ) {
        _n = graph.size();
        _root = _n == 0 ? -1 : root;
        assert(
            int(values.size())
            == (EdgeValues ? graph.edge_count() : graph.size())
        );

        _parent.assign(_n, -2);
        _depth.assign(_n, 0);
        _head.assign(_n, -1);
        _prefix.assign(_n, Group::id());
        if (_n == 0) return;
        assert(0 <= root && root < _n);

        std::vector<int> parent_edge(_n, -1);
        std::vector<int> order;
        order.reserve(_n);
        std::vector<int> stack = {root};
        _parent[root] = -1;
        while (!stack.empty()) {
            int vertex = stack.back();
            stack.pop_back();
            order.push_back(vertex);
            for (const auto& edge : graph[vertex]) {
                if (!edge.alive || _parent[edge.to] != -2) continue;
                _parent[edge.to] = vertex;
                parent_edge[edge.to] = edge.id;
                _depth[edge.to] = _depth[vertex] + 1;
                stack.push_back(edge.to);
            }
        }
        assert(int(order.size()) == _n);

        std::vector<int> subtree_size(_n, 1);
        std::vector<int> heavy(_n, -1);
        for (int index = _n - 1; index > 0; index--) {
            int vertex = order[index];
            int parent = _parent[vertex];
            subtree_size[parent] += subtree_size[vertex];
            if (
                heavy[parent] == -1
                || subtree_size[heavy[parent]] < subtree_size[vertex]
            ) {
                heavy[parent] = vertex;
            }
        }

        std::vector<std::pair<int, int>> starts;
        starts.emplace_back(root, root);
        while (!starts.empty()) {
            auto [start, head] = starts.back();
            starts.pop_back();
            for (
                int vertex = start;
                vertex != -1;
                vertex = heavy[vertex]
            ) {
                _head[vertex] = head;
                for (const auto& edge : graph[vertex]) {
                    if (
                        edge.alive && _parent[edge.to] == vertex
                        && edge.to != heavy[vertex]
                    ) {
                        starts.emplace_back(edge.to, edge.to);
                    }
                }
            }
        }

        if constexpr (!EdgeValues) _prefix[root] = values[root];
        for (int vertex : order) {
            if (vertex == root) continue;
            if constexpr (EdgeValues) {
                assert(0 <= parent_edge[vertex]);
                _prefix[vertex] = Group::op(
                    _prefix[_parent[vertex]],
                    values[parent_edge[vertex]]
                );
            } else {
                _prefix[vertex] = Group::op(
                    _prefix[_parent[vertex]],
                    values[vertex]
                );
            }
        }
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    int root() const {
        return _root;
    }

    int lca(int first, int second) const {
        check_vertex(first);
        check_vertex(second);
        while (_head[first] != _head[second]) {
            if (_depth[_head[first]] < _depth[_head[second]]) {
                std::swap(first, second);
            }
            first = _parent[_head[first]];
        }
        return _depth[first] < _depth[second] ? first : second;
    }

    // Product on the root-to-vertex path. The root vertex is included for
    // vertex values; no edge lies above it in edge-value mode.
    value_type prod(int vertex) const {
        check_vertex(vertex);
        return _prefix[vertex];
    }

    // Product on the simple path from first to second. Both endpoints are
    // included for vertex values.
    value_type prod(int first, int second) const {
        int ancestor = lca(first, second);
        value_type result = Group::op(_prefix[first], _prefix[second]);
        result = Group::op(result, Group::inv(_prefix[ancestor]));
        if constexpr (EdgeValues) {
            result = Group::op(result, Group::inv(_prefix[ancestor]));
        } else if (_parent[ancestor] != -1) {
            result = Group::op(
                result,
                Group::inv(_prefix[_parent[ancestor]])
            );
        }
        return result;
    }
};

template <m1une::monoid::IsCommutativeGroup Group>
using TreeEdgeCumulativeProduct = TreeCumulativeProduct<Group, true>;

template <class T, bool EdgeValues = false>
class TreeCumulativeSum
    : public TreeCumulativeProduct<m1une::monoid::Add<T>, EdgeValues> {
   private:
    using Base =
        TreeCumulativeProduct<m1une::monoid::Add<T>, EdgeValues>;

   public:
    using Base::Base;

    T sum(int vertex) const {
        return Base::prod(vertex);
    }

    T sum(int first, int second) const {
        return Base::prod(first, second);
    }
};

template <class T>
using TreeEdgeCumulativeSum = TreeCumulativeSum<T, true>;

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_CUMULATIVE_SUM_HPP
