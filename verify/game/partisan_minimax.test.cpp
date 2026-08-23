#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../game/minimax.hpp"
#include "../../game/partisan_game.hpp"

#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <random>
#include <vector>

namespace {

using m1une::game::PartisanOutcome;

std::vector<PartisanOutcome> naive_partisan(
    const std::vector<std::vector<int>>& left_moves,
    const std::vector<std::vector<int>>& right_moves
) {
    const int size = int(left_moves.size());
    std::vector<bool> left_starts(size);
    std::vector<bool> right_starts(size);
    std::vector<PartisanOutcome> result(size);
    for (int vertex = size - 1; vertex >= 0; --vertex) {
        for (int next : left_moves[vertex]) left_starts[vertex] = left_starts[vertex]
                                                               || right_starts[next];
        right_starts[vertex] = true;
        for (int next : right_moves[vertex]) right_starts[vertex] = right_starts[vertex]
                                                                && left_starts[next];

        if (left_starts[vertex] && right_starts[vertex]) {
            result[vertex] = PartisanOutcome::Left;
        } else if (!left_starts[vertex] && !right_starts[vertex]) {
            result[vertex] = PartisanOutcome::Right;
        } else if (left_starts[vertex]) {
            result[vertex] = PartisanOutcome::Next;
        } else {
            result[vertex] = PartisanOutcome::Previous;
        }
    }
    return result;
}

void test_partisan_games() {
    std::vector<std::vector<int>> left(4), right(4);
    left[1].push_back(0);
    right[2].push_back(0);
    left[3].push_back(0);
    right[3].push_back(0);
    auto fixed = m1une::game::partisan_outcomes(left, right);
    assert(fixed[0] == PartisanOutcome::Previous);
    assert(fixed[1] == PartisanOutcome::Left);
    assert(fixed[2] == PartisanOutcome::Right);
    assert(fixed[3] == PartisanOutcome::Next);

    std::mt19937 random(271828182);
    for (int size = 0; size <= 50; ++size) {
        for (int trial = 0; trial < 100; ++trial) {
            left.assign(size, {});
            right.assign(size, {});
            for (int from = 0; from < size; ++from) {
                for (int to = from + 1; to < size; ++to) {
                    if (random() % 7 == 0) left[from].push_back(to);
                    if (random() % 7 == 0) right[from].push_back(to);
                }
            }
            assert(
                m1une::game::partisan_outcomes(left, right)
                == naive_partisan(left, right)
            );
        }
    }
}

void test_minimax() {
    std::mt19937 random(161803398);
    for (int size = 0; size <= 60; ++size) {
        for (int trial = 0; trial < 100; ++trial) {
            std::vector<std::vector<int>> graph(size);
            std::vector<long long> terminal_value(size);
            std::vector<bool> maximize(size);
            for (int vertex = 0; vertex < size; ++vertex) {
                terminal_value[vertex] = int(random() % 2001) - 1000;
                maximize[vertex] = random() & 1;
                for (int next = vertex + 1; next < size; ++next) {
                    if (random() % 8 == 0) graph[vertex].push_back(next);
                }
            }

            std::vector<long long> expected = terminal_value;
            std::vector<int> expected_move(size, -1);
            for (int vertex = size - 1; vertex >= 0; --vertex) {
                if (graph[vertex].empty()) continue;
                expected_move[vertex] = graph[vertex][0];
                expected[vertex] = expected[expected_move[vertex]];
                for (int next : graph[vertex]) {
                    const bool improves = maximize[vertex]
                                              ? expected[vertex] < expected[next]
                                              : expected[next] < expected[vertex];
                    if (improves) {
                        expected[vertex] = expected[next];
                        expected_move[vertex] = next;
                    }
                }
            }

            auto actual = m1une::game::dag_minimax(
                graph,
                terminal_value,
                maximize
            );
            assert(actual.value == expected);
            assert(actual.move == expected_move);
        }
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_partisan_games();
    test_minimax();

    long long first, second;
    fast_input >> first >> second;
    fast_output << first + second << '\n';
}
