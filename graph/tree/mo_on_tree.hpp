#ifndef M1UNE_TREE_MO_ON_TREE_HPP
#define M1UNE_TREE_MO_ON_TREE_HPP 1

#include <algorithm>
#include <cassert>
#include <vector>

#include "../../algo/offline/mo.hpp"
#include "../graph.hpp"
#include "heavy_light_decomposition.hpp"

namespace m1une {
namespace tree {

// Offline Mo's algorithm for static paths in a tree.
template <class T = int>
struct MoOnTree {
    struct Query {
        int from;
        int to;
        int left;
        int right;
        int extra;
        int id;
        bool edge;
    };

    int root;
    std::vector<int> entry;
    std::vector<int> exit;
    std::vector<int> tour;

   private:
    int _n;
    HeavyLightDecomposition<T> _hld;
    m1une::algo::Mo _mo;
    std::vector<Query> _queries;

    void check_vertex(int vertex) const {
        assert(0 <= vertex && vertex < _n);
        assert(entry[vertex] != -1);
    }

    int add_path_query(int from, int to, bool edge) {
        check_vertex(from);
        check_vertex(to);
        assert(_queries.empty() || _queries.front().edge == edge);
        int original_from = from;
        int original_to = to;
        if (entry[from] > entry[to]) std::swap(from, to);

        int ancestor = _hld.lca(from, to);
        int left;
        int right = entry[to] + 1;
        int extra = -1;
        if (ancestor == from) {
            left = entry[from] + int(edge);
        } else {
            left = exit[from];
            if (!edge) extra = ancestor;
        }

        int id = _mo.add_query(left, right);
        _queries.push_back(Query{
            original_from,
            original_to,
            left,
            right,
            extra,
            id,
            edge,
        });
        return id;
    }

   public:
    MoOnTree() : root(-1), _n(0), _mo(0) {}

    explicit MoOnTree(
        const m1une::graph::Graph<T>& graph,
        int root_vertex = 0
    ) : root(-1), _n(0), _mo(0) {
        build(graph, root_vertex);
    }

    void build(
        const m1une::graph::Graph<T>& graph,
        int root_vertex = 0
    ) {
        _n = graph.size();
        root = _n == 0 ? -1 : root_vertex;
        entry.assign(_n, -1);
        exit.assign(_n, -1);
        tour.clear();
        tour.reserve(2 * _n);
        _queries.clear();
        _mo = m1une::algo::Mo(2 * _n);
        _hld.build(graph, root_vertex);
        if (_n == 0) return;

        assert(0 <= root && root < _n);
        for (int vertex = 0; vertex < _n; ++vertex) {
            assert(_hld.parent[vertex] != -2);
        }

        std::vector<std::vector<int>> children(_n);
        for (int vertex = 0; vertex < _n; ++vertex) {
            int parent = _hld.parent[vertex];
            if (parent != -1) children[parent].push_back(vertex);
        }

        struct Event {
            int vertex;
            bool leaving;
        };
        std::vector<Event> stack;
        stack.reserve(2 * _n);
        stack.push_back(Event{root, false});
        while (!stack.empty()) {
            Event event = stack.back();
            stack.pop_back();
            int vertex = event.vertex;
            if (event.leaving) {
                exit[vertex] = int(tour.size());
                tour.push_back(vertex);
                continue;
            }

            entry[vertex] = int(tour.size());
            tour.push_back(vertex);
            stack.push_back(Event{vertex, true});
            const auto& child_list = children[vertex];
            for (int index = int(child_list.size()) - 1; index >= 0; --index) {
                stack.push_back(Event{child_list[index], false});
            }
        }
        assert(int(tour.size()) == 2 * _n);
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    int query_count() const {
        return int(_queries.size());
    }

    const std::vector<Query>& queries() const {
        return _queries;
    }

    int parent(int vertex) const {
        check_vertex(vertex);
        return _hld.parent[vertex];
    }

    int parent_edge(int vertex) const {
        check_vertex(vertex);
        return _hld.parent_edge[vertex];
    }

    int depth(int vertex) const {
        check_vertex(vertex);
        return _hld.depth[vertex];
    }

    int lca(int first, int second) const {
        check_vertex(first);
        check_vertex(second);
        return _hld.lca(first, second);
    }

    void reserve(int query_capacity) {
        assert(0 <= query_capacity);
        _queries.reserve(query_capacity);
        _mo.reserve(query_capacity);
    }

    void clear() {
        _queries.clear();
        _mo.clear();
    }

    // Adds an inclusive vertex-path query and returns its insertion-order ID.
    // Vertex and edge queries cannot be mixed in one collection.
    int add_query(int from, int to) {
        return add_path_query(from, to, false);
    }

    // Adds an edge-path query. Each edge is represented by its child vertex.
    int add_edge_query(int from, int to) {
        return add_path_query(from, to, true);
    }

    std::vector<int> order(int block_size = 0) const {
        return _mo.order(block_size);
    }

    // `add(v)` and `remove(v)` maintain the current path. In edge mode, v
    // always represents the real edge parent_edge(v).
    template <class Add, class Remove, class Answer>
    void run(
        Add add,
        Remove remove,
        Answer answer,
        int block_size = 0
    ) const {
        bool edge_mode = !_queries.empty() && _queries.front().edge;
        std::vector<char> active(_n, false);
        auto toggle = [&](int tour_index) {
            int vertex = tour[tour_index];
            if (!edge_mode || vertex != root) {
                if (active[vertex]) {
                    remove(vertex);
                } else {
                    add(vertex);
                }
            }
            active[vertex] = !active[vertex];
        };

        _mo.run(
            toggle,
            toggle,
            [&](int query_id) {
                int extra = _queries[query_id].extra;
                if (extra != -1) {
                    assert(!active[extra]);
                    add(extra);
                }
                answer(query_id);
                if (extra != -1) remove(extra);
            },
            block_size
        );
    }
};

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_MO_ON_TREE_HPP
