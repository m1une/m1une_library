#ifndef M1UNE_GAME_SUBTRACTION_GAME_HPP
#define M1UNE_GAME_SUBTRACTION_GAME_HPP 1

#include <algorithm>
#include <cassert>
#include <vector>

namespace m1une {
namespace game {

inline std::vector<int> subtraction_game_grundy(
    int max_heap,
    const std::vector<int>& moves
) {
    assert(max_heap >= 0);
    for (int move : moves) assert(move > 0);

    std::vector<int> grundy(max_heap + 1);
    std::vector<int> seen(moves.size() + 1, -1);
    for (int heap = 1; heap <= max_heap; ++heap) {
        for (int move : moves) {
            if (move > heap) continue;
            const int value = grundy[heap - move];
            if (value < int(seen.size())) seen[value] = heap;
        }
        while (
            grundy[heap] < int(seen.size())
            && seen[grundy[heap]] == heap
        ) {
            grundy[heap]++;
        }
    }
    return grundy;
}

inline int subtraction_game_nim_sum(
    const std::vector<int>& heaps,
    const std::vector<int>& moves
) {
    int max_heap = 0;
    for (int heap : heaps) {
        assert(heap >= 0);
        max_heap = std::max(max_heap, heap);
    }
    const std::vector<int> grundy = subtraction_game_grundy(max_heap, moves);
    int result = 0;
    for (int heap : heaps) result ^= grundy[heap];
    return result;
}

inline bool subtraction_game_first_player_wins(
    const std::vector<int>& heaps,
    const std::vector<int>& moves
) {
    return subtraction_game_nim_sum(heaps, moves) != 0;
}

}  // namespace game
}  // namespace m1une

#endif  // M1UNE_GAME_SUBTRACTION_GAME_HPP
