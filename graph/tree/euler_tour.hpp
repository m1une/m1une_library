#ifndef M1UNE_TREE_EULER_TOUR_HPP
#define M1UNE_TREE_EULER_TOUR_HPP 1

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "../graph.hpp"

namespace m1une {
namespace tree {

template <class T = int>
struct EulerTour {
    using cost_type = T;
    using edge_type = m1une::graph::Edge<T>;

    int root;
    std::vector<int> parent;
    std::vector<int> parent_edge;
    std::vector<int> depth;
    std::vector<T> dist;
    std::vector<int> subtree_size;
    std::vector<int> tin;
    std::vector<int> tout;
    std::vector<int> order;
    std::vector<std::vector<int>> children;

   private:
    int _n;

    void check_vertex(int v) const {
        assert(0 <= v && v < _n);
        assert(tin[v] != -1);
    }

   public:
    EulerTour() : root(-1), _n(0) {}
    explicit EulerTour(const m1une::graph::Graph<T>& g, int root_ = 0) {
        build(g, root_);
    }

    void build(const m1une::graph::Graph<T>& g, int root_ = 0) {
        _n = g.size();
        root = _n == 0 ? -1 : root_;
        parent.assign(_n, -2);
        parent_edge.assign(_n, -1);
        depth.assign(_n, 0);
        dist.assign(_n, T(0));
        subtree_size.assign(_n, 0);
        tin.assign(_n, -1);
        tout.assign(_n, -1);
        order.clear();
        order.reserve(_n);
        children.assign(_n, {});

        if (_n == 0) return;
        assert(0 <= root && root < _n);

        struct Frame {
            int v;
            int state;
        };

        std::vector<Frame> stack;
        stack.push_back({root, 0});
        parent[root] = -1;

        while (!stack.empty()) {
            Frame frame = stack.back();
            stack.pop_back();
            int v = frame.v;
            if (frame.state == 0) {
                tin[v] = int(order.size());
                order.push_back(v);
                stack.push_back({v, 1});
                const auto& adj = g[v];
                for (int i = int(adj.size()) - 1; i >= 0; --i) {
                    const auto& e = adj[i];
                    if (!e.alive) continue;
                    if (parent[e.to] != -2) continue;
                    parent[e.to] = v;
                    parent_edge[e.to] = e.id;
                    depth[e.to] = depth[v] + 1;
                    dist[e.to] = dist[v] + e.cost;
                    children[v].push_back(e.to);
                    stack.push_back({e.to, 0});
                }
                std::reverse(children[v].begin(), children[v].end());
            } else {
                subtree_size[v] = 1;
                for (int child : children[v]) subtree_size[v] += subtree_size[child];
                tout[v] = int(order.size());
            }
        }
    }

    int size() const {
        return _n;
    }

    int visited_size() const {
        return int(order.size());
    }

    bool empty() const {
        return _n == 0;
    }

    bool is_ancestor(int u, int v) const {
        check_vertex(u);
        check_vertex(v);
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    bool in_subtree(int v, int u) const {
        return is_ancestor(u, v);
    }

    std::pair<int, int> subtree_range(int v, bool edge = false) const {
        check_vertex(v);
        return {tin[v] + (edge ? 1 : 0), tout[v]};
    }

    std::vector<int> subtree_vertices(int v) const {
        check_vertex(v);
        return std::vector<int>(order.begin() + tin[v], order.begin() + tout[v]);
    }

    template <class F>
    void for_each_subtree(int v, F f) const {
        auto [l, r] = subtree_range(v);
        for (int i = l; i < r; ++i) f(order[i]);
    }
};

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_EULER_TOUR_HPP
