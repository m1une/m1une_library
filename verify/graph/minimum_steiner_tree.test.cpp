#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1040"

#include "../../graph/minimum_steiner_tree.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <optional>
#include <utility>
#include <vector>

namespace {

struct NaiveDsu {
    std::vector<int> parent;

    explicit NaiveDsu(int n) : parent(n) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int leader(int v) {
        if (parent[v] == v) return v;
        return parent[v] = leader(parent[v]);
    }

    void merge(int u, int v) {
        u = leader(u);
        v = leader(v);
        if (u != v) parent[u] = v;
    }
};

template <class T>
std::pair<std::optional<T>, std::optional<int>> naive(
    const m1une::graph::Graph<T>& graph,
    std::vector<int> terminals
) {
    std::sort(terminals.begin(), terminals.end());
    terminals.erase(std::unique(terminals.begin(), terminals.end()), terminals.end());
    if (terminals.empty()) return {T(0), 0};

    const auto edges = graph.edges();
    assert(edges.size() < std::numeric_limits<std::uint64_t>::digits);
    std::optional<T> weighted;
    std::optional<int> unweighted;
    for (std::uint64_t mask = 0; mask < (std::uint64_t(1) << edges.size()); mask++) {
        NaiveDsu dsu(graph.size());
        T cost = T(0);
        int count = 0;
        for (int i = 0; i < int(edges.size()); i++) {
            if ((mask >> i & 1) == 0) continue;
            dsu.merge(edges[i].from, edges[i].to);
            cost += edges[i].cost;
            count++;
        }

        bool connected = true;
        for (int v : terminals) {
            if (dsu.leader(v) != dsu.leader(terminals[0])) connected = false;
        }
        if (!connected) continue;
        if (!weighted || cost < *weighted) weighted = cost;
        if (!unweighted || count < *unweighted) unweighted = count;
    }
    return {weighted, unweighted};
}

template <class Cost, class GraphCost, class EdgeCost>
std::optional<Cost> naive_with_vertex_cost(
    const m1une::graph::Graph<GraphCost>& graph,
    std::vector<int> terminals,
    const std::vector<Cost>& vertex_cost,
    EdgeCost edge_cost
) {
    std::sort(terminals.begin(), terminals.end());
    terminals.erase(std::unique(terminals.begin(), terminals.end()), terminals.end());
    if (terminals.empty()) return Cost(0);

    const auto edges = graph.edges();
    std::optional<Cost> answer;
    for (std::uint64_t mask = 0; mask < (std::uint64_t(1) << edges.size()); mask++) {
        NaiveDsu dsu(graph.size());
        std::vector<char> used(graph.size(), false);
        for (int terminal : terminals) used[terminal] = true;
        Cost cost = Cost(0);
        for (int i = 0; i < int(edges.size()); i++) {
            if ((mask >> i & 1) == 0) continue;
            dsu.merge(edges[i].from, edges[i].to);
            used[edges[i].from] = true;
            used[edges[i].to] = true;
            cost += edge_cost(edges[i]);
        }
        for (int v = 0; v < graph.size(); v++) {
            if (used[v]) cost += vertex_cost[v];
        }

        bool connected = true;
        for (int v : terminals) {
            if (dsu.leader(v) != dsu.leader(terminals[0])) connected = false;
        }
        if (connected && (!answer || cost < *answer)) answer = cost;
    }
    return answer;
}

template <class Cost, class GraphCost, class EdgeCost>
void validate_built_tree(
    const m1une::graph::Graph<GraphCost>& graph,
    const m1une::graph::MinimumSteinerTreeResult<Cost>& result,
    const std::vector<int>& terminals,
    const std::vector<Cost>& vertex_cost,
    EdgeCost edge_cost
) {
    assert(std::is_sorted(result.edge_ids.begin(), result.edge_ids.end()));
    assert(std::adjacent_find(result.edge_ids.begin(), result.edge_ids.end()) == result.edge_ids.end());
    assert(std::is_sorted(result.vertices.begin(), result.vertices.end()));
    assert(std::adjacent_find(result.vertices.begin(), result.vertices.end()) == result.vertices.end());

    std::vector<m1une::graph::Edge<GraphCost>> edge_by_id(graph.edge_count());
    for (const auto& edge : graph.edges()) edge_by_id[edge.id] = edge;
    NaiveDsu dsu(graph.size());
    Cost cost = Cost(0);
    for (int id : result.edge_ids) {
        assert(0 <= id && id < graph.edge_count());
        assert(graph.is_edge_alive(id));
        const auto& edge = edge_by_id[id];
        assert(std::binary_search(result.vertices.begin(), result.vertices.end(), edge.from));
        assert(std::binary_search(result.vertices.begin(), result.vertices.end(), edge.to));
        assert(dsu.leader(edge.from) != dsu.leader(edge.to));
        dsu.merge(edge.from, edge.to);
        cost += edge_cost(edge);
    }
    for (int v : result.vertices) cost += vertex_cost[v];
    for (int terminal : terminals) {
        assert(std::binary_search(result.vertices.begin(), result.vertices.end(), terminal));
    }
    if (result.vertices.empty()) {
        assert(terminals.empty() && result.edge_ids.empty());
    } else {
        assert(result.edge_ids.size() + 1 == result.vertices.size());
        for (int v : result.vertices) assert(dsu.leader(v) == dsu.leader(result.vertices[0]));
    }
    assert(cost == result.cost);
}

void test_examples_and_failures() {
    m1une::graph::Graph<long long> graph(6);
    graph.add_edge(0, 1, 4);
    graph.add_edge(1, 2, 1);
    graph.add_edge(1, 3, 2);
    graph.add_edge(3, 4, 3);
    graph.add_edge(0, 4, 20);

    auto weighted = m1une::graph::minimum_steiner_tree(graph, std::vector<int>{0, 2, 4});
    auto unweighted = m1une::graph::minimum_steiner_tree_unweighted(
        graph,
        std::vector<int>{0, 2, 4}
    );
    assert(weighted && *weighted == 10);
    assert(unweighted && *unweighted == 3);
    assert(!m1une::graph::minimum_steiner_tree(graph, std::vector<int>{0, 5}));
    assert(!m1une::graph::minimum_steiner_tree_unweighted(graph, std::vector<int>{0, 5}));
    assert(*m1une::graph::minimum_steiner_tree(graph, std::vector<int>{2, 2}) == 0);
    assert(*m1une::graph::minimum_steiner_tree_unweighted(graph, std::vector<int>()) == 0);

    const std::vector<long long> vertex_cost = {2, 3, 7, 5, 11, 13};
    auto vertex_weighted = m1une::graph::minimum_steiner_tree(
        graph,
        std::vector<int>{0, 2, 4},
        vertex_cost
    );
    auto vertex_weighted_unit_edges = m1une::graph::minimum_steiner_tree_unweighted(
        graph,
        std::vector<int>{0, 2, 4},
        vertex_cost
    );
    assert(vertex_weighted && *vertex_weighted == 38);
    assert(vertex_weighted_unit_edges && *vertex_weighted_unit_edges == 26);
    assert(*m1une::graph::minimum_steiner_tree(graph, std::vector<int>{2}, vertex_cost) == 7);
    assert(*m1une::graph::minimum_steiner_tree(graph, std::vector<int>(), vertex_cost) == 0);

    m1une::graph::Graph<int> unit_graph(2);
    unit_graph.add_edge(0, 1, 100);
    const std::vector<long long> large_vertex_cost = {3'000'000'000LL, 4'000'000'000LL};
    auto independent_cost_type = m1une::graph::minimum_steiner_tree_unweighted(
        unit_graph,
        std::vector<int>{0, 1},
        large_vertex_cost
    );
    assert(independent_cost_type && *independent_cost_type == 7'000'000'001LL);

    auto built = m1une::graph::build_minimum_steiner_tree(
        graph,
        std::vector<int>{0, 2, 4},
        vertex_cost
    );
    assert(built && built->cost == 38);
    validate_built_tree(
        graph,
        *built,
        std::vector<int>{0, 2, 4},
        vertex_cost,
        [](const auto& edge) { return edge.cost; }
    );
    auto built_unit = m1une::graph::build_minimum_steiner_tree_unweighted(
        graph,
        std::vector<int>{0, 2, 4},
        vertex_cost
    );
    assert(built_unit && built_unit->cost == 26);
    validate_built_tree(
        graph,
        *built_unit,
        std::vector<int>{0, 2, 4},
        vertex_cost,
        [](const auto&) { return 1LL; }
    );

    m1une::graph::Graph<long long> zero_cycle(3);
    zero_cycle.add_edge(0, 1, 0);
    zero_cycle.add_edge(1, 2, 0);
    zero_cycle.add_edge(2, 0, 0);
    auto zero_cycle_tree = m1une::graph::build_minimum_steiner_tree(
        zero_cycle,
        std::vector<int>{0, 1, 2}
    );
    assert(zero_cycle_tree && zero_cycle_tree->cost == 0);
    assert(zero_cycle_tree->edge_ids.size() == 2);
    validate_built_tree(
        zero_cycle,
        *zero_cycle_tree,
        std::vector<int>{0, 1, 2},
        std::vector<long long>(3, 0),
        [](const auto& edge) { return edge.cost; }
    );

    auto single_vertex_tree = m1une::graph::build_minimum_steiner_tree(
        graph,
        std::vector<int>{2},
        vertex_cost
    );
    assert(single_vertex_tree && single_vertex_tree->vertices == std::vector<int>{2});
    assert(single_vertex_tree->edge_ids.empty() && single_vertex_tree->cost == 7);
    auto empty_tree = m1une::graph::build_minimum_steiner_tree(
        graph,
        std::vector<int>(),
        vertex_cost
    );
    assert(empty_tree && empty_tree->vertices.empty() && empty_tree->edge_ids.empty());

    int removed = graph.add_edge(4, 5, 1);
    graph.erase_edge(removed);
    assert(!m1une::graph::minimum_steiner_tree(graph, std::vector<int>{0, 5}));
    assert(!m1une::graph::build_minimum_steiner_tree(graph, std::vector<int>{0, 5}));
}

void test_randomized() {
    std::uint64_t state = 0x243f6a8885a308d3ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 100; trial++) {
        const int n = 1 + int(random() % 7);
        std::vector<std::pair<int, int>> pairs;
        for (int u = 0; u < n; u++) {
            for (int v = u + 1; v < n; v++) pairs.emplace_back(u, v);
        }
        for (int i = int(pairs.size()) - 1; i > 0; i--) {
            std::swap(pairs[i], pairs[random() % (i + 1)]);
        }

        m1une::graph::Graph<long long> graph(n);
        const int m = int(random() % (std::min<int>(10, pairs.size()) + 1));
        for (int i = 0; i < m; i++) {
            graph.add_edge(pairs[i].first, pairs[i].second, random() % 10);
        }
        if (m > 0 && trial % 7 == 0) graph.erase_edge(int(random() % m));

        std::vector<int> terminals;
        for (int v = 0; v < n; v++) {
            if (random() % 3 == 0) terminals.push_back(v);
        }
        if (!terminals.empty() && trial % 5 == 0) terminals.push_back(terminals.back());

        std::vector<long long> vertex_cost(n);
        for (long long& cost : vertex_cost) cost = random() % 8;

        auto expected = naive(graph, terminals);
        auto weighted = m1une::graph::minimum_steiner_tree(graph, terminals);
        auto unweighted = m1une::graph::minimum_steiner_tree_unweighted(graph, terminals);
        assert(weighted == expected.first);
        assert(unweighted == expected.second);

        auto expected_vertex_weighted = naive_with_vertex_cost<long long>(
            graph,
            terminals,
            vertex_cost,
            [](const auto& edge) { return edge.cost; }
        );
        auto expected_vertex_weighted_unit_edges = naive_with_vertex_cost<long long>(
            graph,
            terminals,
            vertex_cost,
            [](const auto&) { return 1LL; }
        );
        auto vertex_weighted = m1une::graph::minimum_steiner_tree(
            graph,
            terminals,
            vertex_cost
        );
        auto vertex_weighted_unit_edges = m1une::graph::minimum_steiner_tree_unweighted(
            graph,
            terminals,
            vertex_cost
        );
        assert(vertex_weighted == expected_vertex_weighted);
        assert(vertex_weighted_unit_edges == expected_vertex_weighted_unit_edges);

        const std::vector<long long> zero_vertex_cost(n, 0);
        auto built_weighted = m1une::graph::build_minimum_steiner_tree(graph, terminals);
        auto built_unweighted = m1une::graph::build_minimum_steiner_tree_unweighted(
            graph,
            terminals
        );
        auto built_vertex_weighted = m1une::graph::build_minimum_steiner_tree(
            graph,
            terminals,
            vertex_cost
        );
        auto built_vertex_weighted_unit_edges =
            m1une::graph::build_minimum_steiner_tree_unweighted(graph, terminals, vertex_cost);
        assert(bool(built_weighted) == bool(expected.first));
        assert(bool(built_unweighted) == bool(expected.second));
        assert(bool(built_vertex_weighted) == bool(expected_vertex_weighted));
        assert(
            bool(built_vertex_weighted_unit_edges) == bool(expected_vertex_weighted_unit_edges)
        );
        if (built_weighted) {
            assert(built_weighted->cost == *expected.first);
            validate_built_tree(
                graph,
                *built_weighted,
                terminals,
                zero_vertex_cost,
                [](const auto& edge) { return edge.cost; }
            );
        }
        if (built_unweighted) {
            assert(built_unweighted->cost == *expected.second);
            validate_built_tree(
                graph,
                *built_unweighted,
                terminals,
                std::vector<int>(n, 0),
                [](const auto&) { return 1; }
            );
        }
        if (built_vertex_weighted) {
            assert(built_vertex_weighted->cost == *expected_vertex_weighted);
            validate_built_tree(
                graph,
                *built_vertex_weighted,
                terminals,
                vertex_cost,
                [](const auto& edge) { return edge.cost; }
            );
        }
        if (built_vertex_weighted_unit_edges) {
            assert(built_vertex_weighted_unit_edges->cost == *expected_vertex_weighted_unit_edges);
            validate_built_tree(
                graph,
                *built_vertex_weighted_unit_edges,
                terminals,
                vertex_cost,
                [](const auto&) { return 1LL; }
            );
        }
    }
}

}  // namespace

int main() {
    test_examples_and_failures();
    test_randomized();

    int height, width;
    while (std::cin >> height >> width, height != 0) {
        m1une::graph::Graph<int> graph(height * width);
        std::vector<int> terminals;
        for (int row = 0; row < height; row++) {
            for (int column = 0; column < width; column++) {
                int required;
                std::cin >> required;
                const int vertex = row * width + column;
                if (row > 0) graph.add_edge(vertex, vertex - width);
                if (column > 0) graph.add_edge(vertex, vertex - 1);
                if (required == 1) terminals.push_back(vertex);
            }
        }

        auto weighted = m1une::graph::minimum_steiner_tree(graph, terminals);
        auto unweighted = m1une::graph::minimum_steiner_tree_unweighted(graph, terminals);
        assert(weighted && unweighted && *weighted == *unweighted);
        std::cout << height * width - *unweighted - 1 << '\n';
    }
}
