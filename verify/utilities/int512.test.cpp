#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <cassert>
#include <limits>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "../../utilities/fast_io.hpp"
#include "../../utilities/int128.hpp"
#include "../../utilities/int512.hpp"

namespace {

using m1une::utilities::i128;
using m1une::utilities::Int512;
using m1une::utilities::parse_int512;
using m1une::utilities::to_string;

void test_small_arithmetic() {
    static_assert(Int512::bit_width == 512);
    static_assert(sizeof(Int512) == 64);
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

void test_parsing() {
    const std::string positive =
        "327339060789614187001318969682759915221664204604306478948329136809"
        "613379640467455488327009232590415715088668412756007100921725654588"
        "5393053328527589376";
    assert(Int512(positive).to_string() == positive);
    assert(parse_int512("+0000012345") == Int512(12345));

    Int512 value = 7;
    value = "-987654321098765432109876543210";
    assert(value.to_string() == "-987654321098765432109876543210");

    std::istringstream input("123456789012345678901234567890");
    input >> value;
    assert(value.to_string() == "123456789012345678901234567890");

    for (const std::string& invalid : {
             std::string(), std::string("+"), std::string("-"),
             std::string("12x3")
         }) {
        bool threw = false;
        try {
            value.read(invalid);
        } catch (const std::invalid_argument&) {
            threw = true;
        }
        assert(threw);
    }
}

void test_division() {
    static_assert(Int512(7) / Int512(3) == Int512(2));
    static_assert(Int512(-7) / Int512(3) == Int512(-2));
    static_assert(Int512(-7) % Int512(3) == Int512(-1));

    std::mt19937_64 random(0x685113e57a4a94f1ULL);
    for (int iteration = 0; iteration < 4000; ++iteration) {
        const long long dividend =
            static_cast<long long>(random() % 2000000000001ULL) -
            1000000000000LL;
        long long divisor =
            static_cast<long long>(random() % 2000001ULL) - 1000000;
        if (divisor == 0) divisor = 1;
        const std::pair<Int512, Int512> result =
            divmod(Int512(dividend), Int512(divisor));
        assert(result.first.to_string() == std::to_string(dividend / divisor));
        assert(result.second.to_string() == std::to_string(dividend % divisor));
        assert(result.first * divisor + result.second == dividend);
    }

    const Int512 dividend(
        "100000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000000000000000001"
    );
    const Int512 divisor("123456789012345678901234567890123456789");
    const auto [quotient, remainder] = divmod(dividend, divisor);
    assert(quotient * divisor + remainder == dividend);
    assert(remainder >= 0 && remainder < divisor);

    Int512 minimum = 1;
    for (int exponent = 0; exponent < 511; ++exponent) minimum *= 2;
    assert(minimum / -1 == minimum);
    assert(minimum % -1 == 0);

    bool threw = false;
    try {
        static_cast<void>(dividend / 0);
    } catch (const std::domain_error&) {
        threw = true;
    }
    assert(threw);
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
    test_parsing();
    test_division();
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
