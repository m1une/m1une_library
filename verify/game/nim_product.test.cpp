#define PROBLEM "https://judge.yosupo.jp/problem/nim_product_64"

#include "../../game/nim_product.hpp"

#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <vector>

namespace {

void test_small_values() {
    constexpr int limit = 16;
    std::vector<std::vector<int>> expected(limit, std::vector<int>(limit));
    for (int x = 0; x < limit; ++x) {
        for (int y = 0; y < limit; ++y) {
            std::vector<bool> appears(256);
            for (int smaller_x = 0; smaller_x < x; ++smaller_x) {
                for (int smaller_y = 0; smaller_y < y; ++smaller_y) {
                    const int value = expected[smaller_x][y]
                                      ^ expected[x][smaller_y]
                                      ^ expected[smaller_x][smaller_y];
                    appears[value] = true;
                }
            }
            while (appears[expected[x][y]]) expected[x][y]++;
            assert(
                m1une::game::nim_product(uint64_t(x), uint64_t(y))
                == uint64_t(expected[x][y])
            );
        }
    }
}

void test_field_operations() {
    uint64_t state = 0x243f6a8885a308d3ULL;
    for (int iteration = 0; iteration < 20; ++iteration) {
        state ^= state << 7;
        state ^= state >> 9;
        state ^= state << 8;
        const uint64_t value = state | 1;
        const uint64_t inverse = m1une::game::nim_inverse(value);
        assert(m1une::game::nim_product(value, inverse) == 1);
        assert(m1une::game::nim_quotient(value, value) == 1);
        assert(m1une::game::nim_power(value, 0) == 1);
        assert(m1une::game::nim_power(value, 2) == m1une::game::nim_product(value, value));
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_small_values();
    test_field_operations();

    int test_cases;
    fast_input >> test_cases;
    while (test_cases--) {
        uint64_t first, second;
        fast_input >> first >> second;
        fast_output << m1une::game::nim_product(first, second) << '\n';
    }
}
