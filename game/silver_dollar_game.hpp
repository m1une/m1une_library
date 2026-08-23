#ifndef M1UNE_GAME_SILVER_DOLLAR_GAME_HPP
#define M1UNE_GAME_SILVER_DOLLAR_GAME_HPP 1

#include <cassert>
#include <type_traits>
#include <vector>

namespace m1une {
namespace game {

template <typename T>
T silver_dollar_grundy(const std::vector<T>& coins) {
    for (int index = 0; index < int(coins.size()); ++index) {
        if constexpr (std::is_signed_v<T>) assert(coins[index] >= 0);
        if (index != 0) assert(coins[index - 1] < coins[index]);
    }

    T result{};
    int index = int(coins.size()) % 2;
    if (index == 1) result ^= coins[0];
    for (; index + 1 < int(coins.size()); index += 2) {
        result ^= coins[index + 1] - coins[index] - 1;
    }
    return result;
}

template <typename T>
bool silver_dollar_first_player_wins(const std::vector<T>& coins) {
    return silver_dollar_grundy(coins) != 0;
}

}  // namespace game
}  // namespace m1une

#endif  // M1UNE_GAME_SILVER_DOLLAR_GAME_HPP
