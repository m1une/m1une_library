#define PROBLEM "https://judge.yosupo.jp/problem/multiplication_of_big_integers"

#include <boost/multiprecision/cpp_int.hpp>

#include <cassert>
#include <random>
#include <string>

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

void test_multiplication() {
    assert((BigInt(0) * BigInt("999999999999999999")).to_string() == "0");
    assert((BigInt(-12) * BigInt(34)).to_string() == "-408");
    assert((BigInt(-12) * BigInt(-34)).to_string() == "408");

    std::mt19937_64 random(0x38b54fd917a3c2e1ULL);
    for (int iteration = 0; iteration < 100; ++iteration) {
        const std::string lhs = random_integer(random, 1 + random() % 250, true);
        const std::string rhs = random_integer(random, 1 + random() % 250, true);
        const cpp_int expected = cpp_int(lhs) * cpp_int(rhs);
        assert((BigInt(lhs) * BigInt(rhs)).to_string() == expected.convert_to<std::string>());
    }

    for (int iteration = 0; iteration < 2; ++iteration) {
        const std::string lhs = random_integer(random, 1300, true);
        const std::string rhs = random_integer(random, 1250, true);
        const cpp_int expected = cpp_int(lhs) * cpp_int(rhs);
        assert((BigInt(lhs) * BigInt(rhs)).to_string() == expected.convert_to<std::string>());
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    test_multiplication();

    int test_count;
    input >> test_count;
    while (test_count--) {
        std::string lhs, rhs;
        input >> lhs >> rhs;
        output << (BigInt(lhs) * BigInt(rhs)).to_string() << '\n';
    }
}
