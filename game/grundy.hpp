#ifndef M1UNE_GAME_GRUNDY_HPP
#define M1UNE_GAME_GRUNDY_HPP 1

#include <cassert>
#include <queue>
#include <vector>

namespace m1une {
namespace game {

// graph[v] contains the states reachable from v in one move.
// The graph must be a DAG.
template <typename Graph>
std::vector<int> grundy_numbers(const Graph& graph) {
    const int size = int(graph.size());
    std::vector<int> indegree(size);
    for (int vertex = 0; vertex < size; ++vertex) {
        for (int next : graph[vertex]) {
            assert(0 <= next && next < size);
            indegree[next]++;
        }
    }

    std::queue<int> queue;
    for (int vertex = 0; vertex < size; ++vertex) {
        if (indegree[vertex] == 0) queue.push(vertex);
    }
    std::vector<int> order;
    order.reserve(size);
    while (!queue.empty()) {
        const int vertex = queue.front();
        queue.pop();
        order.push_back(vertex);
        for (int next : graph[vertex]) {
            if (--indegree[next] == 0) queue.push(next);
        }
    }
    assert(int(order.size()) == size);

    std::vector<int> grundy(size);
    std::vector<int> seen(size + 1, -1);
    for (int position = size - 1; position >= 0; --position) {
        const int vertex = order[position];
        for (int next : graph[vertex]) {
            const int value = grundy[next];
            if (value <= size) seen[value] = vertex;
        }
        while (grundy[vertex] <= size && seen[grundy[vertex]] == vertex) {
            grundy[vertex]++;
        }
    }
    return grundy;
}

}  // namespace game
}  // namespace m1une

#endif  // M1UNE_GAME_GRUNDY_HPP
