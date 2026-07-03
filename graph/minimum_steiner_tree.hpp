#ifndef M1UNE_GRAPH_MINIMUM_STEINER_TREE_HPP
#define M1UNE_GRAPH_MINIMUM_STEINER_TREE_HPP 1

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstddef>
#include <functional>
#include <limits>
#include <optional>
#include <queue>
#include <type_traits>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

template <class Cost>
struct MinimumSteinerTreeResult {
    Cost cost;
    std::vector<int> edge_ids;
    std::vector<int> vertices;
};

namespace internal {

inline std::vector<int> steiner_terminals(int n, std::vector<int> terminals) {
    for (int v : terminals) assert(0 <= v && v < n);
    std::sort(terminals.begin(), terminals.end());
    terminals.erase(std::unique(terminals.begin(), terminals.end()), terminals.end());
    assert(terminals.size() < std::numeric_limits<std::size_t>::digits);
    return terminals;
}

template <class Cost>
struct MinimumSteinerTreeDp {
    Cost cost;
    Cost inf;
    std::size_t states;
    std::size_t width;
    std::vector<Cost> dp;
    std::vector<int> terminals;
};

template <class Cost, class GraphCost, class EdgeCost>
std::optional<MinimumSteinerTreeDp<Cost>> minimum_steiner_tree_dp(
    const Graph<GraphCost>& g,
    std::vector<int> terminals,
    const std::vector<Cost>& vertex_cost,
    EdgeCost edge_cost,
    Cost inf
) {
    const int n = g.size();
    assert(vertex_cost.size() == std::size_t(n));
    for (Cost cost : vertex_cost) assert(Cost(0) <= cost);
    terminals = steiner_terminals(n, std::move(terminals));
    const int k = int(terminals.size());
    if (k == 0) return MinimumSteinerTreeDp<Cost>{Cost(0), inf, 1, std::size_t(n), {}, {}};

    assert(Cost(0) < inf);
    for (int v = 0; v < n; v++) {
        for (const auto& edge : g[v]) {
            if (edge.alive) assert(Cost(0) <= edge_cost(edge));
        }
    }

    const std::size_t states = std::size_t(1) << k;
    const std::size_t width = std::size_t(n);
    assert(width <= std::numeric_limits<std::size_t>::max() / states);
    std::vector<Cost> dp(states * width, inf);
    for (int i = 0; i < k; i++) {
        const int terminal = terminals[i];
        if (vertex_cost[terminal] < inf) {
            dp[(std::size_t(1) << i) * width + std::size_t(terminal)] = vertex_cost[terminal];
        }
    }

    using QueueEntry = std::pair<Cost, int>;
    for (std::size_t mask = 1; mask < states; mask++) {
        const std::size_t mask_offset = mask * width;
        for (std::size_t sub = (mask - 1) & mask; sub != 0; sub = (sub - 1) & mask) {
            const std::size_t other = mask ^ sub;
            if (sub > other) continue;
            const std::size_t sub_offset = sub * width;
            const std::size_t other_offset = other * width;
            for (int v = 0; v < n; v++) {
                const std::size_t vertex = std::size_t(v);
                const Cost left = dp[sub_offset + vertex];
                const Cost right = dp[other_offset + vertex];
                if (left == inf || right == inf) continue;
                assert(vertex_cost[v] <= right);
                const Cost extra = right - vertex_cost[v];
                if (left > inf - extra) continue;
                const Cost candidate = left + extra;
                Cost& current = dp[mask_offset + vertex];
                if (candidate < current) current = candidate;
            }
        }

        std::priority_queue<QueueEntry, std::vector<QueueEntry>, std::greater<QueueEntry>> queue;
        for (int v = 0; v < n; v++) {
            const Cost distance = dp[mask_offset + std::size_t(v)];
            if (distance != inf) queue.emplace(distance, v);
        }
        while (!queue.empty()) {
            auto [distance, v] = queue.top();
            queue.pop();
            if (distance != dp[mask_offset + std::size_t(v)]) continue;
            for (const auto& edge : g[v]) {
                if (!edge.alive) continue;
                const Cost cost = edge_cost(edge);
                if (cost >= inf || vertex_cost[edge.to] > inf - cost) continue;
                const Cost extra = cost + vertex_cost[edge.to];
                if (distance > inf - extra) continue;
                const Cost candidate = distance + extra;
                Cost& current = dp[mask_offset + std::size_t(edge.to)];
                if (current <= candidate) continue;
                current = candidate;
                queue.emplace(candidate, edge.to);
            }
        }
    }

    const auto answer_begin = dp.begin() + (states - 1) * width;
    const Cost answer = *std::min_element(answer_begin, dp.end());
    if (answer == inf) return std::nullopt;
    return MinimumSteinerTreeDp<Cost>{
        answer,
        inf,
        states,
        width,
        std::move(dp),
        std::move(terminals)
    };
}

template <class T>
std::optional<MinimumSteinerTreeDp<int>> minimum_steiner_tree_unweighted_dp(
    const Graph<T>& g,
    std::vector<int> terminals
) {
    const int n = g.size();
    terminals = steiner_terminals(n, std::move(terminals));
    const int k = int(terminals.size());
    if (k == 0) return MinimumSteinerTreeDp<int>{0, n, 1, std::size_t(n), {}, {}};

    const std::size_t states = std::size_t(1) << k;
    const std::size_t width = std::size_t(n);
    assert(width <= std::numeric_limits<std::size_t>::max() / states);
    const int inf = n;
    std::vector<int> dp(states * width, inf);
    for (int i = 0; i < k; i++) {
        dp[(std::size_t(1) << i) * width + std::size_t(terminals[i])] = 0;
    }

    for (std::size_t mask = 1; mask < states; mask++) {
        const std::size_t mask_offset = mask * width;
        for (std::size_t sub = (mask - 1) & mask; sub != 0; sub = (sub - 1) & mask) {
            const std::size_t other = mask ^ sub;
            if (sub > other) continue;
            const std::size_t sub_offset = sub * width;
            const std::size_t other_offset = other * width;
            for (int v = 0; v < n; v++) {
                const std::size_t vertex = std::size_t(v);
                const int candidate = dp[sub_offset + vertex] + dp[other_offset + vertex];
                int& current = dp[mask_offset + vertex];
                if (candidate < current) current = candidate;
            }
        }

        std::vector<int> bucket_head(n, -1);
        std::vector<int> entry_vertex;
        std::vector<int> entry_next;
        entry_vertex.reserve(2 * width);
        entry_next.reserve(2 * width);
        auto push = [&](int distance, int v) {
            entry_vertex.push_back(v);
            entry_next.push_back(bucket_head[distance]);
            bucket_head[distance] = int(entry_vertex.size()) - 1;
        };
        for (int v = 0; v < n; v++) {
            const int distance = dp[mask_offset + std::size_t(v)];
            if (distance != inf) push(distance, v);
        }
        for (int distance = 0; distance < n; distance++) {
            for (int entry = bucket_head[distance]; entry != -1; entry = entry_next[entry]) {
                const int v = entry_vertex[entry];
                if (dp[mask_offset + std::size_t(v)] != distance) continue;
                for (const auto& edge : g[v]) {
                    if (!edge.alive) continue;
                    int& current = dp[mask_offset + std::size_t(edge.to)];
                    if (distance + 1 >= current) continue;
                    current = distance + 1;
                    push(current, edge.to);
                }
            }
        }
    }

    const auto answer_begin = dp.begin() + (states - 1) * width;
    const int answer = *std::min_element(answer_begin, dp.end());
    if (answer == inf) return std::nullopt;
    return MinimumSteinerTreeDp<int>{
        answer,
        inf,
        states,
        width,
        std::move(dp),
        std::move(terminals)
    };
}

template <class Cost, class GraphCost, class EdgeCost>
MinimumSteinerTreeResult<Cost> restore_minimum_steiner_tree(
    const Graph<GraphCost>& g,
    const MinimumSteinerTreeDp<Cost>& data,
    const std::vector<Cost>& vertex_cost,
    EdgeCost edge_cost
) {
    MinimumSteinerTreeResult<Cost> result;
    result.cost = data.cost;
    if (data.terminals.empty()) return result;

    const int n = g.size();
    const std::size_t cells = data.states * data.width;
    std::vector<char> state(cells, 0);
    std::vector<char> selected_edge(g.edge_count(), false);

    std::function<bool(std::size_t, int)> restore = [&](std::size_t mask, int start) {
        const std::size_t position = mask * data.width + std::size_t(start);
        if (state[position] == 2) return true;
        if (state[position] == 1) return false;
        state[position] = 1;

        std::vector<int> search_parent(n, -2), search_edge(n, -1), stack;
        search_parent[start] = -1;
        stack.push_back(start);
        int seed = -1;
        std::size_t seed_split = 0;

        while (!stack.empty() && seed == -1) {
            const int v = stack.back();
            stack.pop_back();
            const std::size_t vertex_position = mask * data.width + std::size_t(v);
            const Cost current = data.dp[vertex_position];

            if (v != start && state[vertex_position] == 2) {
                seed = v;
                break;
            }
            if ((mask & (mask - 1)) == 0) {
                const int terminal_index = int(std::countr_zero(mask));
                if (v == data.terminals[terminal_index] && current == vertex_cost[v]) {
                    seed = v;
                    break;
                }
            }
            for (std::size_t sub = (mask - 1) & mask; sub != 0; sub = (sub - 1) & mask) {
                const std::size_t other = mask ^ sub;
                if (sub > other) continue;
                const Cost left = data.dp[sub * data.width + std::size_t(v)];
                const Cost right = data.dp[other * data.width + std::size_t(v)];
                if (left == data.inf || right == data.inf || right < vertex_cost[v]) continue;
                const Cost extra = right - vertex_cost[v];
                if (left > data.inf - extra || left + extra != current) continue;
                seed = v;
                seed_split = sub;
                break;
            }
            if (seed != -1) break;

            for (const auto& edge : g[v]) {
                if (!edge.alive || search_parent[edge.to] != -2) continue;
                const Cost cost = edge_cost(edge);
                if (cost >= data.inf || vertex_cost[v] > data.inf - cost) continue;
                const Cost extra = cost + vertex_cost[v];
                const Cost previous = data.dp[mask * data.width + std::size_t(edge.to)];
                if (previous == data.inf || previous > data.inf - extra) continue;
                if (previous + extra != current) continue;
                search_parent[edge.to] = v;
                search_edge[edge.to] = edge.id;
                stack.push_back(edge.to);
            }
        }

        if (seed == -1) {
            state[position] = 0;
            return false;
        }
        if (seed_split != 0) {
            const bool restored_left = restore(seed_split, seed);
            const bool restored_right = restore(mask ^ seed_split, seed);
            assert(restored_left && restored_right);
            if (!restored_left || !restored_right) {
                state[position] = 0;
                return false;
            }
        }

        for (int v = seed; v != -1; v = search_parent[v]) {
            state[mask * data.width + std::size_t(v)] = 2;
            if (search_parent[v] == -1) continue;
            const int id = search_edge[v];
            assert(0 <= id && id < g.edge_count());
            selected_edge[id] = true;
        }
        return true;
    };

    int root = -1;
    const std::size_t full_mask = data.states - 1;
    for (int v = 0; v < n; v++) {
        if (data.dp[full_mask * data.width + std::size_t(v)] == data.cost) {
            root = v;
            break;
        }
    }
    assert(root != -1);
    const bool restored = restore(full_mask, root);
    assert(restored);
    (void)restored;

    std::vector<Edge<GraphCost>> edge_by_id(g.edge_count());
    std::vector<char> has_edge(g.edge_count(), false);
    for (const auto& edge : g.edges()) {
        edge_by_id[edge.id] = edge;
        has_edge[edge.id] = true;
    }

    std::vector<int> parent(n), component_size(n, 1);
    for (int v = 0; v < n; v++) parent[v] = v;
    auto leader = [&](auto&& self, int v) -> int {
        if (parent[v] == v) return v;
        return parent[v] = self(self, parent[v]);
    };

    std::vector<char> tree_edge(g.edge_count(), false);
    for (int id = 0; id < g.edge_count(); id++) {
        if (!selected_edge[id]) continue;
        assert(has_edge[id]);
        const auto& edge = edge_by_id[id];
        int u = leader(leader, edge.from);
        int v = leader(leader, edge.to);
        if (u == v) continue;
        if (component_size[u] < component_size[v]) std::swap(u, v);
        parent[v] = u;
        component_size[u] += component_size[v];
        tree_edge[id] = true;
    }

    std::vector<std::vector<std::pair<int, int>>> tree(n);
    std::vector<int> degree(n, 0);
    std::vector<char> in_tree(n, false), is_terminal(n, false);
    for (int terminal : data.terminals) {
        in_tree[terminal] = true;
        is_terminal[terminal] = true;
    }
    for (int id = 0; id < g.edge_count(); id++) {
        if (!tree_edge[id]) continue;
        const auto& edge = edge_by_id[id];
        tree[edge.from].emplace_back(edge.to, id);
        tree[edge.to].emplace_back(edge.from, id);
        degree[edge.from]++;
        degree[edge.to]++;
        in_tree[edge.from] = true;
        in_tree[edge.to] = true;
    }

    std::queue<int> leaves;
    for (int v = 0; v < n; v++) {
        if (in_tree[v] && !is_terminal[v] && degree[v] <= 1) leaves.push(v);
    }
    std::vector<char> removed_vertex(n, false), removed_edge(g.edge_count(), false);
    while (!leaves.empty()) {
        const int v = leaves.front();
        leaves.pop();
        if (removed_vertex[v] || is_terminal[v] || degree[v] > 1) continue;
        removed_vertex[v] = true;
        for (auto [to, id] : tree[v]) {
            if (removed_edge[id]) continue;
            removed_edge[id] = true;
            degree[v]--;
            degree[to]--;
            if (!is_terminal[to] && degree[to] <= 1) leaves.push(to);
            break;
        }
    }

    Cost restored_cost = Cost(0);
    for (int id = 0; id < g.edge_count(); id++) {
        if (!tree_edge[id] || removed_edge[id]) continue;
        result.edge_ids.push_back(id);
        restored_cost += edge_cost(edge_by_id[id]);
    }
    for (int v = 0; v < n; v++) {
        if (!in_tree[v] || removed_vertex[v]) continue;
        result.vertices.push_back(v);
        restored_cost += vertex_cost[v];
    }
    if constexpr (std::is_integral_v<Cost>) assert(restored_cost == result.cost);
    result.cost = restored_cost;
    return result;
}

}  // namespace internal

template <class T>
std::optional<T> minimum_steiner_tree(
    const Graph<T>& g,
    std::vector<int> terminals,
    const std::vector<T>& vertex_cost,
    T inf = std::numeric_limits<T>::max() / T(4)
) {
    auto result = internal::minimum_steiner_tree_dp(
        g,
        std::move(terminals),
        vertex_cost,
        [](const Edge<T>& edge) { return edge.cost; },
        inf
    );
    if (!result) return std::nullopt;
    return result->cost;
}

template <class T>
std::optional<T> minimum_steiner_tree(
    const Graph<T>& g,
    std::vector<int> terminals,
    T inf = std::numeric_limits<T>::max() / T(4)
) {
    return minimum_steiner_tree(g, std::move(terminals), std::vector<T>(g.size(), T(0)), inf);
}

template <class GraphCost, class Cost>
std::optional<Cost> minimum_steiner_tree_unweighted(
    const Graph<GraphCost>& g,
    std::vector<int> terminals,
    const std::vector<Cost>& vertex_cost,
    Cost inf = std::numeric_limits<Cost>::max() / Cost(4)
) {
    auto result = internal::minimum_steiner_tree_dp(
        g,
        std::move(terminals),
        vertex_cost,
        [](const Edge<GraphCost>&) { return Cost(1); },
        inf
    );
    if (!result) return std::nullopt;
    return result->cost;
}

template <class T>
std::optional<MinimumSteinerTreeResult<T>> build_minimum_steiner_tree(
    const Graph<T>& g,
    std::vector<int> terminals,
    const std::vector<T>& vertex_cost,
    T inf = std::numeric_limits<T>::max() / T(4)
) {
    auto data = internal::minimum_steiner_tree_dp(
        g,
        std::move(terminals),
        vertex_cost,
        [](const Edge<T>& edge) { return edge.cost; },
        inf
    );
    if (!data) return std::nullopt;
    return internal::restore_minimum_steiner_tree(
        g,
        *data,
        vertex_cost,
        [](const Edge<T>& edge) { return edge.cost; }
    );
}

template <class T>
std::optional<MinimumSteinerTreeResult<T>> build_minimum_steiner_tree(
    const Graph<T>& g,
    std::vector<int> terminals,
    T inf = std::numeric_limits<T>::max() / T(4)
) {
    std::vector<T> vertex_cost(g.size(), T(0));
    return build_minimum_steiner_tree(g, std::move(terminals), vertex_cost, inf);
}

template <class GraphCost, class Cost>
std::optional<MinimumSteinerTreeResult<Cost>> build_minimum_steiner_tree_unweighted(
    const Graph<GraphCost>& g,
    std::vector<int> terminals,
    const std::vector<Cost>& vertex_cost,
    Cost inf = std::numeric_limits<Cost>::max() / Cost(4)
) {
    auto data = internal::minimum_steiner_tree_dp(
        g,
        std::move(terminals),
        vertex_cost,
        [](const Edge<GraphCost>&) { return Cost(1); },
        inf
    );
    if (!data) return std::nullopt;
    return internal::restore_minimum_steiner_tree(
        g,
        *data,
        vertex_cost,
        [](const Edge<GraphCost>&) { return Cost(1); }
    );
}

template <class T>
std::optional<MinimumSteinerTreeResult<int>> build_minimum_steiner_tree_unweighted(
    const Graph<T>& g,
    std::vector<int> terminals
) {
    auto data = internal::minimum_steiner_tree_unweighted_dp(g, std::move(terminals));
    if (!data) return std::nullopt;
    std::vector<int> vertex_cost(g.size(), 0);
    return internal::restore_minimum_steiner_tree(
        g,
        *data,
        vertex_cost,
        [](const Edge<T>&) { return 1; }
    );
}

template <class T>
std::optional<int> minimum_steiner_tree_unweighted(
    const Graph<T>& g,
    std::vector<int> terminals
) {
    auto result = internal::minimum_steiner_tree_unweighted_dp(g, std::move(terminals));
    if (!result) return std::nullopt;
    return result->cost;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_MINIMUM_STEINER_TREE_HPP
