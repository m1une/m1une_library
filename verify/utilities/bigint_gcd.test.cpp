#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#pragma GCC optimize("O3")

#include <cassert>
#include <numeric>
#include <random>
#include <string>
#include <utility>

#include "../../utilities/bigint.hpp"
#include "../../utilities/fast_io.hpp"

namespace {

using m1une::utilities::BigInt;

std::string random_positive_integer(std::mt19937_64& random, int digits) {
    std::string result;
    result.push_back(char('1' + random() % 9));
    for (int i = 1; i < digits; ++i) {
        result.push_back(char('0' + random() % 10));
    }
    return result;
}

void test_gcd() {
    assert(gcd(BigInt(0), BigInt(0)) == 0);
    assert(gcd(BigInt(0), BigInt(-42)) == 42);
    assert(gcd(BigInt(-24), BigInt(18)) == 6);
    assert(gcd(BigInt(-24), BigInt(-18)) == 6);

    std::mt19937_64 random(0x36c15d2f217a4017ULL);
    for (int iteration = 0; iteration < 3000; ++iteration) {
        const long long first = static_cast<long long>(random() % 2000000000001ULL) -
                                1000000000000LL;
        const long long second =
            static_cast<long long>(random() % 2000000000001ULL) - 1000000000000LL;
        assert(gcd(BigInt(first), BigInt(second)) == std::gcd(first, second));
    }

    for (int iteration = 0; iteration < 20; ++iteration) {
        const BigInt common(random_positive_integer(random, 100 + random() % 400));
        const BigInt factor(random_positive_integer(random, 100 + random() % 300));
        const BigInt first = common * factor;
        const BigInt second = common * (factor + 1);
        assert(gcd(first, second) == common);
        assert(gcd(-first, second) == common);
    }

    BigInt previous = 0;
    BigInt current = 1;
    for (int iteration = 0; iteration < 2000; ++iteration) {
        BigInt next = previous + current;
        previous = std::move(current);
        current = std::move(next);
    }
    assert(gcd(previous, current) == 1);
}

}  // namespace

int main() {
    test_gcd();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    long long first, second;
    input >> first >> second;
    output << first + second << '\n';
}
