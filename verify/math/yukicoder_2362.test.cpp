#define PROBLEM "https://yukicoder.me/problems/no/2362"

#include "../../math/generalized_floor_sum.hpp"

#include <cstdint>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int test_count;
    std::cin >> test_count;
    while (test_count--) {
        long long n, mod, x, y;
        std::cin >> n >> mod >> x >> y;

        auto without_offset =
            m1une::math::generalized_floor_sum_table<std::uint64_t, 1, 1>(
                n,
                mod,
                x,
                0LL
            );
        auto with_offset =
            m1une::math::generalized_floor_sum_table<std::uint64_t, 1, 1>(
                n,
                mod,
                x,
                y
            );

        std::uint64_t answer = 0;
        answer -= without_offset[0][1] * static_cast<std::uint64_t>(n) -
                  without_offset[1][1];
        answer -= with_offset[0][1] * static_cast<std::uint64_t>(n - 1) -
                  2 * with_offset[1][1];
        std::cout << answer << '\n';
    }
}
