#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../utilities/base64.hpp"

#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <limits>
#include <optional>
#include <random>
#include <string>
#include <vector>

namespace {

using m1une::utilities::checked_from_base64;
using m1une::utilities::from_base64;
using m1une::utilities::to_base64;

void fixed_tests() {
    std::vector<int> digits(64);
    for (int value = 0; value < 64; ++value) digits[value] = value;
    assert(to_base64(digits, 6) == m1une::utilities::base64_alphabet);
    assert(from_base64<int>(m1une::utilities::base64_alphabet, 64, 6) == digits);

    std::vector<unsigned char> man = {'M', 'a', 'n'};
    assert(to_base64(man, 8) == "TWFu");
    assert(from_base64<unsigned char>("TWFu", 3, 8) == man);

    std::vector<unsigned char> one_byte = {'M'};
    assert(to_base64(one_byte, 8) == "TQ");
    assert(from_base64<unsigned char>("TQ", 1, 8) == one_byte);

    std::vector<unsigned char> foobar = {'f', 'o', 'o', 'b', 'a', 'r'};
    assert(to_base64(foobar, 8) == "Zm9vYmFy");
    assert(from_base64<unsigned char>("Zm9vYmFy", 6, 8) == foobar);

    std::vector<int> two_bit_values = {1, 2, 3};
    assert(to_base64(two_bit_values, 2) == "b");
    assert(from_base64<int>("b", 3, 2) == two_bit_values);

    assert(to_base64(std::vector<int>(), 1).empty());
    assert(from_base64<int>("", 0, 1).empty());
    assert(!checked_from_base64<int>("A", 0, 1).has_value());
    assert(!checked_from_base64<int>("!", 1, 6).has_value());
    assert(!checked_from_base64<int>("AA", 1, 6).has_value());
    assert(!checked_from_base64<int>("B", 1, 1).has_value());
    assert(!checked_from_base64<int>("A", 1, 0).has_value());
    assert(!checked_from_base64<int>("A", 1, 32).has_value());
}

template <class Integer>
void randomized_type_tests(std::mt19937_64& random) {
    constexpr int digits = std::numeric_limits<Integer>::digits;
    for (int bit_width = 1; bit_width <= digits; ++bit_width) {
        for (int trial = 0; trial < 200; ++trial) {
            std::size_t count = static_cast<std::size_t>(random() % 100);
            std::vector<Integer> values(count);
            for (Integer& value : values) {
                std::uint64_t generated = random();
                if (bit_width < 64) generated &= (std::uint64_t(1) << bit_width) - 1;
                value = static_cast<Integer>(generated);
            }

            std::string encoded = to_base64(values, bit_width);
            assert(encoded.size() == (count * bit_width + 5) / 6);
            assert(from_base64<Integer>(encoded, count, bit_width) == values);
        }
    }
}

void randomized_tests() {
    std::mt19937_64 random(0x81f42c957a6d3e10ULL);
    randomized_type_tests<std::uint8_t>(random);
    randomized_type_tests<std::uint16_t>(random);
    randomized_type_tests<std::uint32_t>(random);
    randomized_type_tests<std::uint64_t>(random);
    randomized_type_tests<int>(random);
    randomized_type_tests<long long>(random);
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    fixed_tests();
    randomized_tests();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
