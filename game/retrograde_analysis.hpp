#ifndef M1UNE_GAME_RETROGRADE_ANALYSIS_HPP
#define M1UNE_GAME_RETROGRADE_ANALYSIS_HPP 1

#include <algorithm>
#include <cassert>
#include <queue>
#include <utility>
#include <vector>

namespace m1une {
namespace game {

enum class GameOutcome { Win, Lose, Draw };

struct RetrogradeResult {
    std::vector<GameOutcome> outcome;
    std::vector<int> distance;
};

// graph[v] contains the states reachable from v in one move.
inline RetrogradeResult retrograde_analysis(
    const std::vector<std::vector<int>>& graph
) {
    const int size = int(graph.size());
    std::vector<std::vector<int>> reverse_graph(size);
    std::vector<int> remaining(size);
    for (int vertex = 0; vertex < size; ++vertex) {
        remaining[vertex] = int(graph[vertex].size());
        for (int next : graph[vertex]) {
            assert(0 <= next && next < size);
            reverse_graph[next].push_back(vertex);
        }
    }

    std::vector<GameOutcome> outcome(size, GameOutcome::Draw);
    std::vector<int> distance(size, -1);
    std::vector<int> longest_win_successor(size);
    std::vector<bool> decided(size);
    std::queue<int> queue;
    for (int vertex = 0; vertex < size; ++vertex) {
        if (remaining[vertex] == 0) {
            outcome[vertex] = GameOutcome::Lose;
            distance[vertex] = 0;
            decided[vertex] = true;
            queue.push(vertex);
        }
    }

    while (!queue.empty()) {
        const int vertex = queue.front();
        queue.pop();
        for (int previous : reverse_graph[vertex]) {
            if (decided[previous]) continue;
            if (outcome[vertex] == GameOutcome::Lose) {
                outcome[previous] = GameOutcome::Win;
                distance[previous] = distance[vertex] + 1;
                decided[previous] = true;
                queue.push(previous);
            } else {
                longest_win_successor[previous] = std::max(
                    longest_win_successor[previous],
                    distance[vertex]
                );
                if (--remaining[previous] == 0) {
                    outcome[previous] = GameOutcome::Lose;
                    distance[previous] = longest_win_successor[previous] + 1;
                    decided[previous] = true;
                    queue.push(previous);
                }
            }
        }
    }
    return {std::move(outcome), std::move(distance)};
}

}  // namespace game
}  // namespace m1une

#endif  // M1UNE_GAME_RETROGRADE_ANALYSIS_HPP
