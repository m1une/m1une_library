#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <cassert>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>

#include "../../utilities/fast_io.hpp"
#include "../../utilities/int256.hpp"

namespace {

using m1une::utilities::Int256;
using m1une::utilities::parse_int256;

void test_arithmetic_and_parsing() {
    static_assert(Int256::bit_width == 256);
    static_assert(sizeof(Int256) == 32);
    static_assert(Int256(12) * Int256(-7) == Int256(-84));
    static_assert(Int256(-17) / Int256(5) == Int256(-3));
    static_assert(Int256(-17) % Int256(5) == Int256(-2));

    assert(parse_int256("+000123456789") == Int256(123456789));
    assert(Int256("-98765432109876543210").to_string() ==
           "-98765432109876543210");

    const std::string two_to_256 =
        "115792089237316195423570985008687907853269984665640564039457584007"
        "913129639936";
    assert(Int256(two_to_256) == 0);

    Int256 minimum = 1;
    for (int exponent = 0; exponent < 255; ++exponent) minimum *= 2;
    assert(minimum.is_negative());
    assert(minimum / -1 == minimum);

    bool invalid_threw = false;
    try {
        static_cast<void>(parse_int256("8z8"));
    } catch (const std::invalid_argument&) {
        invalid_threw = true;
    }
    assert(invalid_threw);
}

void test_division() {
    std::mt19937_64 random(0xa0a26f12ccb593edULL);
    for (int iteration = 0; iteration < 3000; ++iteration) {
        const long long dividend =
            static_cast<long long>(random() % 2000000000001ULL) -
            1000000000000LL;
        long long divisor =
            static_cast<long long>(random() % 2000001ULL) - 1000000;
        if (divisor == 0) divisor = -1;
        const auto [quotient, remainder] =
            divmod(Int256(dividend), Int256(divisor));
        assert(quotient.to_string() == std::to_string(dividend / divisor));
        assert(remainder.to_string() == std::to_string(dividend % divisor));
    }

    Int256 dividend = 1;
    for (int exponent = 0; exponent < 240; ++exponent) dividend *= 2;
    dividend -= 12345;
    const Int256 divisor("12345678901234567890123456789");
    const std::pair<Int256, Int256> result = divmod(dividend, divisor);
    assert(result.first * divisor + result.second == dividend);
    assert(result.second >= 0 && result.second < divisor);

    bool zero_threw = false;
    try {
        static_cast<void>(dividend / 0);
    } catch (const std::domain_error&) {
        zero_threw = true;
    }
    assert(zero_threw);
}

}  // namespace

int main() {
    test_arithmetic_and_parsing();
    test_division();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    int test_count;
    input >> test_count;
    while (test_count--) {
        long long first, second;
        input >> first >> second;
        output << (Int256(first) + Int256(second)).to_string() << '\n';
    }
}
