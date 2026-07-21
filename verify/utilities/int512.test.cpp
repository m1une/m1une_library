#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <cassert>
#include <limits>
#include <random>
#include <string>

#include "../../utilities/fast_io.hpp"
#include "../../utilities/int128.hpp"
#include "../../utilities/int512.hpp"

namespace {

using m1une::utilities::i128;
using m1une::utilities::Int512;
using m1une::utilities::to_string;

void test_small_arithmetic() {
    constexpr Int512 six = Int512(2) * Int512(3);
    static_assert(six == Int512(6));
    static_assert(Int512(-7) < Int512(2));
    static_assert((-Int512(-9)).sign() == 1);

    assert(Int512().is_zero());
    assert(Int512(-123456789).to_string() == "-123456789");
    assert(
        Int512(std::numeric_limits<long long>::min()).to_string() ==
        std::to_string(std::numeric_limits<long long>::min())
    );
    assert(
        Int512(std::numeric_limits<unsigned long long>::max()).to_string() ==
        std::to_string(std::numeric_limits<unsigned long long>::max())
    );

    std::mt19937_64 random(0x73c90a4e9182bd65ULL);
    for (int iteration = 0; iteration < 10000; ++iteration) {
        const long long first =
            static_cast<long long>(random() % 2000000001ULL) - 1000000000;
        const long long second =
            static_cast<long long>(random() % 2000000001ULL) - 1000000000;
        const long long third =
            static_cast<long long>(random() % 2000000001ULL) - 1000000000;
        const i128 expected =
            i128(first) * i128(second) + i128(third);
        const Int512 actual = Int512(first) * Int512(second) + third;
        assert(actual.to_string() == to_string(expected));
    }
}

void test_high_limbs_and_wraparound() {
    Int512 power = 1;
    for (int exponent = 0; exponent < 250; ++exponent) power *= 2;
    const Int512 power_500 = power * power;
    assert(
        power_500.to_string() ==
        "327339060789614187001318969682759915221664204604306478948329136809"
        "613379640467455488327009232590415715088668412756007100921725654588"
        "5393053328527589376"
    );
    assert((-power_500).to_string() == "-" + power_500.to_string());

    Int512 minimum = 1;
    for (int exponent = 0; exponent < 511; ++exponent) minimum *= 2;
    assert(minimum.is_negative());
    assert(-minimum == minimum);
    const Int512 maximum = minimum - 1;
    assert(maximum.sign() == 1);
    assert(maximum + 1 == minimum);
}

}  // namespace

int main() {
    test_small_arithmetic();
    test_high_limbs_and_wraparound();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    int test_count;
    input >> test_count;
    while (test_count--) {
        long long first, second;
        input >> first >> second;
        output << (Int512(first) + Int512(second)).to_string() << '\n';
    }
}
