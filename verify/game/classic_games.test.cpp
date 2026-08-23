#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../game/green_hackenbush.hpp"
#include "../../game/silver_dollar_game.hpp"
#include "../../game/subtraction_game.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <functional>
#include <random>
#include <vector>

namespace {

void test_subtraction_games() {
    std::mt19937 random(314159265);
    for (int move_mask = 0; move_mask < (1 << 7); ++move_mask) {
        std::vector<int> moves;
        for (int move = 1; move <= 7; ++move) {
            if (move_mask >> (move - 1) & 1) moves.push_back(move);
        }

        constexpr int max_heap = 80;
        std::vector<int> expected(max_heap + 1);
        for (int heap = 1; heap <= max_heap; ++heap) {
            std::vector<bool> appears(moves.size() + 1);
            for (int move : moves) {
                if (move <= heap) appears[expected[heap - move]] = true;
            }
            while (appears[expected[heap]]) expected[heap]++;
        }
        assert(m1une::game::subtraction_game_grundy(max_heap, moves) == expected);

        for (int trial = 0; trial < 30; ++trial) {
            std::vector<int> heaps(10);
            int expected_sum = 0;
            for (int& heap : heaps) {
                heap = int(random() % (max_heap + 1));
                expected_sum ^= expected[heap];
            }
            assert(m1une::game::subtraction_game_nim_sum(heaps, moves) == expected_sum);
            assert(
                m1une::game::subtraction_game_first_player_wins(heaps, moves)
                == (expected_sum != 0)
            );
        }
    }
}

uint64_t brute_hackenbush(const std::vector<int>& parent) {
    const int size = int(parent.size());
    std::vector<unsigned> subtree(size);
    for (int edge = size - 1; edge >= 0; --edge) {
        subtree[edge] |= 1U << edge;
        if (parent[edge] != -1) subtree[parent[edge]] |= subtree[edge];
    }

    std::vector<int> memo(1U << size, -1);
    std::function<int(unsigned)> solve = [&](unsigned state) {
        int& result = memo[state];
        if (result != -1) return result;
        std::vector<bool> appears(size + 1);
        for (int edge = 0; edge < size; ++edge) {
            if (state >> edge & 1U) {
                appears[solve(state & ~subtree[edge])] = true;
            }
        }
        result = 0;
        while (appears[result]) result++;
        return result;
    };
    return uint64_t(solve((1U << size) - 1));
}

void test_hackenbush_forests() {
    for (int size = 0; size <= 8; ++size) {
        std::vector<int> parent(size);
        std::function<void(int)> enumerate = [&](int edge) {
            if (edge == size) {
                const uint64_t expected = brute_hackenbush(parent);
                assert(m1une::game::green_hackenbush_grundy(parent) == expected);
                assert(
                    m1une::game::green_hackenbush_first_player_wins(parent)
                    == (expected != 0)
                );
                return;
            }
            for (int value = -1; value < edge; ++value) {
                parent[edge] = value;
                enumerate(edge + 1);
            }
        };
        enumerate(0);
    }
}

int brute_silver_dollar(unsigned state, int board_size, std::vector<int>& memo) {
    int& result = memo[state];
    if (result != -1) return result;
    std::vector<int> coins;
    for (int position = 0; position < board_size; ++position) {
        if (state >> position & 1U) coins.push_back(position);
    }

    std::vector<bool> appears(board_size + 1);
    for (int index = 0; index < int(coins.size()); ++index) {
        const int lower = index == 0 ? 0 : coins[index - 1] + 1;
        for (int destination = lower; destination < coins[index]; ++destination) {
            const unsigned next = state ^ (1U << coins[index]) ^ (1U << destination);
            appears[brute_silver_dollar(next, board_size, memo)] = true;
        }
    }
    result = 0;
    while (appears[result]) result++;
    return result;
}

void test_silver_dollar_positions() {
    constexpr int board_size = 10;
    std::vector<int> memo(1 << board_size, -1);
    for (unsigned state = 0; state < (1U << board_size); ++state) {
        std::vector<int> coins;
        for (int position = 0; position < board_size; ++position) {
            if (state >> position & 1U) coins.push_back(position);
        }
        const int expected = brute_silver_dollar(state, board_size, memo);
        assert(m1une::game::silver_dollar_grundy(coins) == expected);
        assert(
            m1une::game::silver_dollar_first_player_wins(coins)
            == (expected != 0)
        );
    }

    std::vector<unsigned long long> unsigned_coins = {1, 3, 7};
    assert(m1une::game::silver_dollar_grundy(unsigned_coins) == 2);
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_subtraction_games();
    test_hackenbush_forests();
    test_silver_dollar_positions();

    long long first, second;
    fast_input >> first >> second;
    fast_output << first + second << '\n';
}
