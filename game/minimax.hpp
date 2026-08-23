#ifndef M1UNE_GAME_MINIMAX_HPP
#define M1UNE_GAME_MINIMAX_HPP 1

#include <cassert>
#include <queue>
#include <utility>
#include <vector>

namespace m1une {
namespace game {

template <typename T>
struct MinimaxResult {
    std::vector<T> value;
    std::vector<int> move;
};

template <typename T>
MinimaxResult<T> dag_minimax(
    const std::vector<std::vector<int>>& graph,
    const std::vector<T>& terminal_value,
    const std::vector<bool>& maximize
) {
    const int size = int(graph.size());
    assert(int(terminal_value.size()) == size);
    assert(int(maximize.size()) == size);

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

    std::vector<T> value = terminal_value;
    std::vector<int> move(size, -1);
    for (int position = size - 1; position >= 0; --position) {
        const int vertex = order[position];
        if (graph[vertex].empty()) {
            value[vertex] = terminal_value[vertex];
            continue;
        }

        move[vertex] = graph[vertex][0];
        value[vertex] = value[move[vertex]];
        for (int next : graph[vertex]) {
            const bool improves = maximize[vertex]
                                      ? value[vertex] < value[next]
                                      : value[next] < value[vertex];
            if (improves) {
                value[vertex] = value[next];
                move[vertex] = next;
            }
        }
    }
    return {std::move(value), std::move(move)};
}

}  // namespace game
}  // namespace m1une

#endif  // M1UNE_GAME_MINIMAX_HPP
