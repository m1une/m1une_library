#ifndef M1UNE_GRAPH_DIRECTED_MST_HPP
#define M1UNE_GRAPH_DIRECTED_MST_HPP 1

#include <cassert>
#include <optional>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

template <class T>
struct DirectedMinimumSpanningTree {
    T cost;
    std::vector<int> parent;
    std::vector<int> parent_edge;
    std::vector<Edge<T>> edges;
    int root;
};

namespace internal {

template <class T>
struct DirectedMstEdge {
    int from = -1;
    int to = -1;
    T cost = T(0);
    int id = -1;
};

template <class T>
struct DirectedMstHeapPool {
    using StoredEdge = DirectedMstEdge<T>;

    struct Node {
        StoredEdge edge;
        T offset = T(0);
        int child = -1;
        int sibling = -1;
    };

    struct Heap {
        int root = -1;
        int size = 0;
    };

    std::vector<Node> nodes;

    explicit DirectedMstHeapPool(int capacity = 0) {
        nodes.reserve(capacity);
    }

    T key(int node) const {
        return nodes[node].edge.cost + nodes[node].offset;
    }

    int meld_roots(int first, int second) {
        if (first == -1) return second;
        if (second == -1) return first;
        if (key(second) < key(first)) std::swap(first, second);
        nodes[second].offset -= nodes[first].offset;
        nodes[second].sibling = nodes[first].child;
        nodes[first].child = second;
        return first;
    }

    void push(Heap& heap, const StoredEdge& edge) {
        const int node = int(nodes.size());
        nodes.push_back(Node{edge, T(0), -1, -1});
        heap.root = meld_roots(heap.root, node);
        heap.size++;
    }

    void meld(Heap& destination, Heap& source) {
        destination.root = meld_roots(destination.root, source.root);
        destination.size += source.size;
        source.root = -1;
        source.size = 0;
    }

    const StoredEdge& top(const Heap& heap) const {
        assert(heap.root != -1);
        return nodes[heap.root].edge;
    }

    T top_key(const Heap& heap) const {
        assert(heap.root != -1);
        return key(heap.root);
    }

    void add_all(Heap& heap, const T& delta) {
        assert(heap.root != -1);
        nodes[heap.root].offset += delta;
    }

    void pop(Heap& heap) {
        assert(heap.root != -1 && heap.size > 0);
        const int old_root = heap.root;
        int child = nodes[old_root].child;
        std::vector<int> pairs;
        while (child != -1) {
            int first = child;
            child = nodes[first].sibling;
            nodes[first].sibling = -1;
            nodes[first].offset += nodes[old_root].offset;

            if (child != -1) {
                int second = child;
                child = nodes[second].sibling;
                nodes[second].sibling = -1;
                nodes[second].offset += nodes[old_root].offset;
                first = meld_roots(first, second);
            }
            pairs.push_back(first);
        }

        heap.root = -1;
        for (auto it = pairs.rbegin(); it != pairs.rend(); ++it) {
            heap.root = meld_roots(*it, heap.root);
        }
        heap.size--;
    }
};

struct DirectedMstDsu {
    std::vector<int> parent;

    explicit DirectedMstDsu(int n) : parent(n, -1) {}

    int leader(int vertex) {
        int root = vertex;
        while (parent[root] != -1) root = parent[root];
        while (vertex != root) {
            int next = parent[vertex];
            parent[vertex] = root;
            vertex = next;
        }
        return root;
    }
};

template <class T>
struct DirectedMstRootlessCost {
    int artificial_edges;
    T original_cost;

    DirectedMstRootlessCost() : artificial_edges(0), original_cost(T(0)) {}
    explicit DirectedMstRootlessCost(int zero)
        : artificial_edges(zero), original_cost(T(0)) {
        assert(zero == 0);
    }
    DirectedMstRootlessCost(int artificial_edges_, const T& original_cost_)
        : artificial_edges(artificial_edges_), original_cost(original_cost_) {}

    DirectedMstRootlessCost& operator+=(const DirectedMstRootlessCost& other) {
        artificial_edges += other.artificial_edges;
        original_cost += other.original_cost;
        return *this;
    }

    DirectedMstRootlessCost& operator-=(const DirectedMstRootlessCost& other) {
        artificial_edges -= other.artificial_edges;
        original_cost -= other.original_cost;
        return *this;
    }

    friend DirectedMstRootlessCost operator+(
        DirectedMstRootlessCost first,
        const DirectedMstRootlessCost& second
    ) {
        return first += second;
    }

    friend DirectedMstRootlessCost operator-(
        DirectedMstRootlessCost first,
        const DirectedMstRootlessCost& second
    ) {
        return first -= second;
    }

    friend bool operator<(
        const DirectedMstRootlessCost& first,
        const DirectedMstRootlessCost& second
    ) {
        if (first.artificial_edges != second.artificial_edges) {
            return first.artificial_edges < second.artificial_edges;
        }
        return first.original_cost < second.original_cost;
    }
};

}  // namespace internal

// Returns a minimum-cost spanning arborescence rooted at root, or nullopt when
// some vertex is unreachable from the root using active directed edges.
template <class T>
std::optional<DirectedMinimumSpanningTree<T>> directed_mst(
    const Graph<T>& graph,
    int root
) {
    const int n = graph.size();
    assert(0 <= root && root < n);
    const int maximum_node_count = 2 * n;

    int active_edge_count = 0;
#ifndef NDEBUG
    std::vector<int> incidence(graph.edge_count(), 0);
#endif
    for (int vertex = 0; vertex < n; vertex++) {
        for (const Edge<T>& edge : graph[vertex]) {
            if (!edge.alive) continue;
            assert(0 <= edge.id && edge.id < graph.edge_count());
#ifndef NDEBUG
            incidence[edge.id]++;
#endif
            active_edge_count++;
        }
    }
#ifndef NDEBUG
    for (int count : incidence) {
        if (count != 0) assert(count == 1);
    }
#endif

    using StoredEdge = internal::DirectedMstEdge<T>;
    using HeapPool = internal::DirectedMstHeapPool<T>;
    HeapPool pool(active_edge_count);
    std::vector<typename HeapPool::Heap> heaps(maximum_node_count);
    for (int vertex = 0; vertex < n; vertex++) {
        for (const Edge<T>& edge : graph[vertex]) {
            if (!edge.alive) continue;
            pool.push(heaps[edge.to], StoredEdge{edge.from, edge.to, edge.cost, edge.id});
        }
    }

    internal::DirectedMstDsu dsu(maximum_node_count);
    std::vector<int> contraction_parent(maximum_node_count, -1);
    std::vector<int> visited(maximum_node_count, 0);
    std::vector<StoredEdge> selected(maximum_node_count);
    int node_count = n;
    int visit_token = 1;
    visited[root] = 1;

    for (int start = 0; start < n; start++) {
        if (visited[start] != 0) continue;
        visit_token++;
        int component = start;
        while (visited[component] == 0 || visited[component] == visit_token) {
            if (visited[component] == visit_token) {
                if (node_count == maximum_node_count) return std::nullopt;
                const int contracted = node_count++;
                int current = component;
                do {
                    const T reduction = T(0) - pool.top_key(heaps[current]);
                    pool.add_all(heaps[current], reduction);
                    pool.meld(heaps[contracted], heaps[current]);
                    contraction_parent[current] = contracted;
                    dsu.parent[current] = contracted;
                    current = dsu.leader(selected[current].from);
                } while (current != contracted);
                component = contracted;
            }

            assert(visited[component] == 0);
            visited[component] = visit_token;
            while (heaps[component].size > 0 &&
                   dsu.leader(pool.top(heaps[component]).from) == component) {
                pool.pop(heaps[component]);
            }
            if (heaps[component].size == 0) return std::nullopt;
            selected[component] = pool.top(heaps[component]);
            component = dsu.leader(selected[component].from);
        }
    }

    DirectedMinimumSpanningTree<T> result;
    result.cost = T(0);
    result.parent.assign(n, -1);
    result.parent_edge.assign(n, -1);
    result.root = root;
    result.parent[root] = root;

    std::vector<char> expanded(node_count, false);
    std::vector<StoredEdge> chosen(n);
    for (int component = node_count - 1; component >= 0; component--) {
        if (component == root || expanded[component]) continue;
        const StoredEdge& edge = selected[component];
        if (edge.id == -1) return std::nullopt;
        int vertex = edge.to;
        while (vertex != -1 && !expanded[vertex]) {
            expanded[vertex] = true;
            vertex = contraction_parent[vertex];
        }
        result.cost += edge.cost;
        result.parent[edge.to] = edge.from;
        result.parent_edge[edge.to] = edge.id;
        chosen[edge.to] = edge;
    }

    result.edges.reserve(n - 1);
    for (int vertex = 0; vertex < n; vertex++) {
        if (vertex == root) continue;
        if (result.parent[vertex] == -1) return std::nullopt;
        const StoredEdge& edge = chosen[vertex];
        result.edges.emplace_back(edge.from, edge.to, edge.cost, edge.id, true);
    }
    return result;
}

// Chooses the root that gives a minimum-cost spanning arborescence.
template <class T>
std::optional<DirectedMinimumSpanningTree<T>> directed_mst(
    const Graph<T>& graph
) {
    const int n = graph.size();
    if (n == 0) return std::nullopt;

    using Cost = internal::DirectedMstRootlessCost<T>;
    Graph<Cost> augmented(n + 1);
    std::vector<int> original_edge_id;
    original_edge_id.reserve(graph.edge_count() + n);

#ifndef NDEBUG
    std::vector<int> incidence(graph.edge_count(), 0);
#endif
    for (int vertex = 0; vertex < n; vertex++) {
        for (const Edge<T>& edge : graph[vertex]) {
            if (!edge.alive) continue;
#ifndef NDEBUG
            assert(0 <= edge.id && edge.id < graph.edge_count());
            incidence[edge.id]++;
#endif
            augmented.add_directed_edge(
                edge.from,
                edge.to,
                Cost(0, edge.cost)
            );
            original_edge_id.push_back(edge.id);
        }
    }
#ifndef NDEBUG
    for (int count : incidence) {
        if (count != 0) assert(count == 1);
    }
#endif

    const int artificial_root = n;
    for (int vertex = 0; vertex < n; vertex++) {
        augmented.add_directed_edge(
            artificial_root,
            vertex,
            Cost(1, T(0))
        );
        original_edge_id.push_back(-1);
    }

    auto augmented_result = directed_mst(augmented, artificial_root);
    if (!augmented_result || augmented_result->cost.artificial_edges != 1) {
        return std::nullopt;
    }

    DirectedMinimumSpanningTree<T> result;
    result.cost = augmented_result->cost.original_cost;
    result.parent.assign(n, -1);
    result.parent_edge.assign(n, -1);
    result.root = -1;
    result.edges.reserve(n - 1);

    for (int vertex = 0; vertex < n; vertex++) {
        int augmented_edge_id = augmented_result->parent_edge[vertex];
        assert(0 <= augmented_edge_id &&
               augmented_edge_id < int(original_edge_id.size()));
        int edge_id = original_edge_id[augmented_edge_id];
        if (edge_id == -1) {
            assert(result.root == -1);
            result.root = vertex;
            result.parent[vertex] = vertex;
            continue;
        }

        result.parent[vertex] = augmented_result->parent[vertex];
        result.parent_edge[vertex] = edge_id;
        result.edges.emplace_back(
            result.parent[vertex],
            vertex,
            augmented_result->edges[vertex].cost.original_cost,
            edge_id,
            true
        );
    }
    assert(result.root != -1);
    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_DIRECTED_MST_HPP
