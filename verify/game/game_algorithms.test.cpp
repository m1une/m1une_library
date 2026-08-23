#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../game/all.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <random>
#include <vector>

namespace {

using m1une::game::GameOutcome;

void test_nim() {
    std::vector<int> empty;
    assert(m1une::game::nim_sum(empty) == 0);
    assert(!m1une::game::nim_first_player_wins(empty));
    assert(m1une::game::misere_nim_first_player_wins(empty));

    std::vector<int> ordinary = {1, 4, 5};
    assert(m1une::game::nim_sum(ordinary) == 0);
    assert(!m1une::game::nim_first_player_wins(ordinary));

    std::vector<int> one_one = {1, 1};
    std::vector<int> one_one_one = {1, 1, 1};
    assert(m1une::game::misere_nim_first_player_wins(one_one));
    assert(!m1une::game::misere_nim_first_player_wins(one_one_one));

    std::vector<int> general = {1, 2, 3};
    assert(!m1une::game::misere_nim_first_player_wins(general));

    for (int code = 0; code < 625; ++code) {
        int remaining = code;
        std::vector<int> heaps(4);
        for (int& heap : heaps) {
            heap = remaining % 5;
            remaining /= 5;
        }

        auto ordinary_move = m1une::game::nim_winning_move(heaps);
        assert(bool(ordinary_move) == m1une::game::nim_first_player_wins(heaps));
        if (ordinary_move) {
            assert(0 <= ordinary_move->heap && ordinary_move->heap < 4);
            assert(ordinary_move->new_size < heaps[ordinary_move->heap]);
            heaps[ordinary_move->heap] = ordinary_move->new_size;
            assert(!m1une::game::nim_first_player_wins(heaps));
        }

        remaining = code;
        for (int& heap : heaps) {
            heap = remaining % 5;
            remaining /= 5;
        }
        const bool has_stone = std::any_of(
            heaps.begin(),
            heaps.end(),
            [](int heap) { return heap != 0; }
        );
        auto misere_move = m1une::game::misere_nim_winning_move(heaps);
        assert(
            bool(misere_move)
            == (has_stone && m1une::game::misere_nim_first_player_wins(heaps))
        );
        if (misere_move) {
            assert(0 <= misere_move->heap && misere_move->heap < 4);
            assert(misere_move->new_size < heaps[misere_move->heap]);
            heaps[misere_move->heap] = misere_move->new_size;
            assert(!m1une::game::misere_nim_first_player_wins(heaps));
        }
    }
}

std::vector<int> naive_grundy(const std::vector<std::vector<int>>& graph) {
    const int size = int(graph.size());
    std::vector<int> result(size);
    for (int vertex = size - 1; vertex >= 0; --vertex) {
        std::vector<bool> appears(size + 1);
        for (int next : graph[vertex]) appears[result[next]] = true;
        while (appears[result[vertex]]) result[vertex]++;
    }
    return result;
}

void test_grundy_random() {
    std::mt19937 random(123456789);
    for (int size = 0; size <= 40; ++size) {
        for (int trial = 0; trial < 100; ++trial) {
            std::vector<std::vector<int>> graph(size);
            for (int from = 0; from < size; ++from) {
                for (int to = from + 1; to < size; ++to) {
                    if (random() % 5 == 0) graph[from].push_back(to);
                }
            }
            assert(m1une::game::grundy_numbers(graph) == naive_grundy(graph));
        }
    }
}

std::vector<GameOutcome> naive_outcomes(
    const std::vector<std::vector<int>>& graph
) {
    const int size = int(graph.size());
    std::vector<GameOutcome> result(size, GameOutcome::Draw);
    std::vector<bool> decided(size);
    for (int vertex = 0; vertex < size; ++vertex) {
        if (graph[vertex].empty()) {
            result[vertex] = GameOutcome::Lose;
            decided[vertex] = true;
        }
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (int vertex = 0; vertex < size; ++vertex) {
            if (decided[vertex]) continue;
            bool has_losing_move = false;
            bool all_moves_win = true;
            for (int next : graph[vertex]) {
                has_losing_move |= decided[next] && result[next] == GameOutcome::Lose;
                all_moves_win &= decided[next] && result[next] == GameOutcome::Win;
            }
            if (has_losing_move || all_moves_win) {
                result[vertex] = has_losing_move ? GameOutcome::Win : GameOutcome::Lose;
                decided[vertex] = true;
                changed = true;
            }
        }
    }
    return result;
}

void test_retrograde_random() {
    std::mt19937 random(987654321);
    for (int size = 0; size <= 30; ++size) {
        for (int trial = 0; trial < 100; ++trial) {
            std::vector<std::vector<int>> graph(size);
            for (int from = 0; from < size; ++from) {
                for (int to = 0; to < size; ++to) {
                    if (random() % 8 == 0) graph[from].push_back(to);
                }
            }
            auto actual = m1une::game::retrograde_analysis(graph);
            assert(actual.outcome == naive_outcomes(graph));
            for (int vertex = 0; vertex < size; ++vertex) {
                assert((actual.distance[vertex] == -1)
                       == (actual.outcome[vertex] == GameOutcome::Draw));
                if (actual.outcome[vertex] == GameOutcome::Draw) {
                    assert(actual.move[vertex] != -1);
                    assert(actual.outcome[actual.move[vertex]] == GameOutcome::Draw);
                } else if (graph[vertex].empty()) {
                    assert(actual.outcome[vertex] == GameOutcome::Lose);
                    assert(actual.distance[vertex] == 0);
                    assert(actual.move[vertex] == -1);
                } else {
                    assert(
                        std::find(
                            graph[vertex].begin(),
                            graph[vertex].end(),
                            actual.move[vertex]
                        ) != graph[vertex].end()
                    );
                    if (actual.outcome[vertex] == GameOutcome::Win) {
                        assert(
                            actual.outcome[actual.move[vertex]]
                            == GameOutcome::Lose
                        );
                        int best = size + 1;
                        for (int next : graph[vertex]) {
                            if (actual.outcome[next] == GameOutcome::Lose) {
                                best = std::min(best, actual.distance[next] + 1);
                            }
                        }
                        assert(actual.distance[vertex] == best);
                    } else {
                        assert(
                            actual.outcome[actual.move[vertex]]
                            == GameOutcome::Win
                        );
                        int best = 0;
                        for (int next : graph[vertex]) {
                            best = std::max(best, actual.distance[next] + 1);
                        }
                        assert(actual.distance[vertex] == best);
                    }
                    assert(
                        actual.distance[vertex]
                        == actual.distance[actual.move[vertex]] + 1
                    );
                }
            }
        }
    }

    std::vector<std::vector<int>> chain(5);
    chain[0].push_back(1);
    chain[1].push_back(2);
    chain[2].push_back(3);
    chain[3].push_back(4);
    auto result = m1une::game::retrograde_analysis(chain);
    for (int vertex = 0; vertex < 5; ++vertex) {
        assert(result.distance[vertex] == 4 - vertex);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_nim();
    test_grundy_random();
    test_retrograde_random();

    long long first, second;
    fast_input >> first >> second;
    fast_output << first + second << '\n';
}
