#ifndef M1UNE_GAME_PARTISAN_GAME_HPP
#define M1UNE_GAME_PARTISAN_GAME_HPP 1

#include <cassert>
#include <queue>
#include <vector>

namespace m1une {
namespace game {

enum class PartisanOutcome { Left, Right, Next, Previous };

inline std::vector<PartisanOutcome> partisan_outcomes(
    const std::vector<std::vector<int>>& left_moves,
    const std::vector<std::vector<int>>& right_moves
) {
    const int size = int(left_moves.size());
    assert(int(right_moves.size()) == size);

    std::vector<int> indegree(size);
    for (int vertex = 0; vertex < size; ++vertex) {
        for (int next : left_moves[vertex]) {
            assert(0 <= next && next < size);
            indegree[next]++;
        }
        for (int next : right_moves[vertex]) {
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
        for (int next : left_moves[vertex]) {
            if (--indegree[next] == 0) queue.push(next);
        }
        for (int next : right_moves[vertex]) {
            if (--indegree[next] == 0) queue.push(next);
        }
    }
    assert(int(order.size()) == size);

    std::vector<bool> left_wins_moving(size);
    std::vector<bool> left_wins_waiting(size);
    std::vector<PartisanOutcome> outcome(size);
    for (int position = size - 1; position >= 0; --position) {
        const int vertex = order[position];
        for (int next : left_moves[vertex]) {
            if (left_wins_waiting[next]) left_wins_moving[vertex] = true;
        }
        left_wins_waiting[vertex] = true;
        for (int next : right_moves[vertex]) {
            if (!left_wins_moving[next]) left_wins_waiting[vertex] = false;
        }

        if (left_wins_moving[vertex] && left_wins_waiting[vertex]) {
            outcome[vertex] = PartisanOutcome::Left;
        } else if (!left_wins_moving[vertex] && !left_wins_waiting[vertex]) {
            outcome[vertex] = PartisanOutcome::Right;
        } else if (left_wins_moving[vertex]) {
            outcome[vertex] = PartisanOutcome::Next;
        } else {
            outcome[vertex] = PartisanOutcome::Previous;
        }
    }
    return outcome;
}

}  // namespace game
}  // namespace m1une

#endif  // M1UNE_GAME_PARTISAN_GAME_HPP
