#define PROBLEM "https://judge.yosupo.jp/problem/division_of_big_integers"

#include <boost/multiprecision/cpp_int.hpp>

#include <cassert>
#include <random>
#include <string>
#include <utility>

#include "../../utilities/bigint.hpp"
#include "../../utilities/fast_io.hpp"

namespace {

using boost::multiprecision::cpp_int;
using m1une::utilities::BigInt;

std::string random_integer(std::mt19937_64& random, int digits, bool allow_negative) {
    std::string result;
    if (allow_negative && (random() & 1)) result.push_back('-');
    result.push_back(char('1' + random() % 9));
    for (int i = 1; i < digits; ++i) result.push_back(char('0' + random() % 10));
    return result;
}

void check_division(const std::string& dividend, const std::string& divisor) {
    const cpp_int expected_dividend(dividend);
    const cpp_int expected_divisor(divisor);
    const std::pair<BigInt, BigInt> actual = divmod(BigInt(dividend), BigInt(divisor));
    assert(actual.first.to_string() ==
           (expected_dividend / expected_divisor).convert_to<std::string>());
    assert(actual.second.to_string() ==
           (expected_dividend % expected_divisor).convert_to<std::string>());
}

void test_division() {
    check_division("0", "12345678901234567890");
    check_division("7", "3");
    check_division("-7", "3");
    check_division("7", "-3");
    check_division("-7", "-3");

    std::mt19937_64 random(0xe871b3526f194ad0ULL);
    for (int iteration = 0; iteration < 100; ++iteration) {
        const std::string dividend = random_integer(random, 1 + random() % 250, true);
        const std::string divisor = random_integer(random, 1 + random() % 150, true);
        check_division(dividend, divisor);
    }

    for (int iteration = 0; iteration < 2; ++iteration) {
        const std::string dividend = random_integer(random, 1400, true);
        const std::string divisor = random_integer(random, 650, true);
        check_division(dividend, divisor);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    test_division();

    int test_count;
    input >> test_count;
    while (test_count--) {
        std::string dividend, divisor;
        input >> dividend >> divisor;
        const std::pair<BigInt, BigInt> result = divmod(BigInt(dividend), BigInt(divisor));
        output << result.first.to_string() << ' ' << result.second.to_string() << '\n';
    }
}
