#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <cassert>
#include <random>
#include <stdexcept>
#include <string>

#include "../../utilities/fast_io.hpp"
#include "../../utilities/int1024.hpp"

namespace {

using m1une::utilities::Int1024;
using m1une::utilities::parse_int1024;

void test_arithmetic_and_parsing() {
    static_assert(Int1024::bit_width == 1024);
    static_assert(sizeof(Int1024) == 128);
    static_assert(Int1024(91) / Int1024(10) == Int1024(9));
    static_assert(Int1024(-91) % Int1024(10) == Int1024(-1));

    const std::string ten_to_300 = "1" + std::string(300, '0');
    assert(Int1024(ten_to_300).to_string() == ten_to_300);
    assert(parse_int1024("+00042") == 42);

    Int1024 wrapped = 1;
    for (int exponent = 0; exponent < 1024; ++exponent) wrapped *= 2;
    assert(wrapped == 0);

    Int1024 minimum = 1;
    for (int exponent = 0; exponent < 1023; ++exponent) minimum *= 2;
    assert(minimum.is_negative());
    assert(-minimum == minimum);

    bool invalid_threw = false;
    try {
        static_cast<void>(parse_int1024("--1"));
    } catch (const std::invalid_argument&) {
        invalid_threw = true;
    }
    assert(invalid_threw);
}

void test_division() {
    std::mt19937_64 random(0x692fedbd3ef279cdULL);
    for (int iteration = 0; iteration < 3000; ++iteration) {
        const long long dividend =
            static_cast<long long>(random() % 2000000000001ULL) -
            1000000000000LL;
        long long divisor =
            static_cast<long long>(random() % 2000001ULL) - 1000000;
        if (divisor == 0) divisor = 1;
        const auto [quotient, remainder] =
            divmod(Int1024(dividend), Int1024(divisor));
        assert(quotient.to_string() == std::to_string(dividend / divisor));
        assert(remainder.to_string() == std::to_string(dividend % divisor));
    }

    const std::string large_text = "1" + std::string(300, '0');
    const Int1024 dividend = Int1024(large_text) - 987654321;
    const Int1024 divisor(
        "3141592653589793238462643383279502884197169399375105820974944592"
    );
    const auto [quotient, remainder] = divmod(dividend, divisor);
    assert(quotient * divisor + remainder == dividend);
    assert(remainder >= 0 && remainder < divisor);

    const Int1024 negative_dividend = -dividend;
    const auto [negative_quotient, negative_remainder] =
        divmod(negative_dividend, divisor);
    assert(negative_quotient == -quotient);
    assert(negative_remainder == -remainder);
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
        output << (Int1024(first) + Int1024(second)).to_string() << '\n';
    }
}
