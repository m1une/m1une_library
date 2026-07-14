#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <cstdint>
#include "../../../utilities/fast_io.hpp"
#include <vector>

#include "../../../algo/enumeration/combination.hpp"

void test_combination_masks() {
    assert(m1une::algo::first_combination_mask<std::uint64_t>(5, 3) == 0b00111ULL);

    std::uint64_t mask = 0b00111ULL;
    assert(m1une::algo::next_combination_mask(mask, 5));
    assert(mask == 0b01011ULL);

    std::vector<std::uint64_t> masks;
    m1une::algo::for_each_combination_mask(5, 3, [&](std::uint64_t current) {
        masks.push_back(current);
    });
    std::vector<std::uint64_t> expected = {
        0b00111ULL, 0b01011ULL, 0b01101ULL, 0b01110ULL, 0b10011ULL,
        0b10101ULL, 0b10110ULL, 0b11001ULL, 0b11010ULL, 0b11100ULL
    };
    assert(masks == expected);

    masks.clear();
    m1une::algo::for_each_combination_mask(4, 0, [&](std::uint64_t current) {
        masks.push_back(current);
    });
    assert(masks == std::vector<std::uint64_t>{0});

    masks.clear();
    m1une::algo::for_each_combination_mask(4, 4, [&](std::uint64_t current) {
        masks.push_back(current);
    });
    assert(masks == std::vector<std::uint64_t>{0b1111ULL});
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_combination_masks();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
