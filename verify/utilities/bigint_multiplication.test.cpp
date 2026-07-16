#define PROBLEM "https://judge.yosupo.jp/problem/multiplication_of_big_integers"

#include <cassert>
#include <random>
#include <string>
#include <vector>

#include "../../utilities/bigint.hpp"
#include "../../utilities/fast_io.hpp"

namespace {

using m1une::utilities::BigInt;

std::string absolute_decimal(const std::string& value) {
    int begin = !value.empty() && (value[0] == '-' || value[0] == '+');
    while (begin + 1 < int(value.size()) && value[begin] == '0') ++begin;
    return value.substr(begin);
}

std::string multiply_naive(const std::string& lhs_text, const std::string& rhs_text) {
    const std::string lhs = absolute_decimal(lhs_text);
    const std::string rhs = absolute_decimal(rhs_text);
    if (lhs == "0" || rhs == "0") return "0";

    std::vector<int> coefficients(lhs.size() + rhs.size());
    for (int i = int(lhs.size()) - 1; i >= 0; --i) {
        for (int j = int(rhs.size()) - 1; j >= 0; --j) {
            coefficients[i + j + 1] += (lhs[i] - '0') * (rhs[j] - '0');
        }
    }
    for (int i = int(coefficients.size()) - 1; i > 0; --i) {
        coefficients[i - 1] += coefficients[i] / 10;
        coefficients[i] %= 10;
    }

    int begin = 0;
    while (begin + 1 < int(coefficients.size()) && coefficients[begin] == 0) ++begin;
    std::string result;
    if ((lhs_text[0] == '-') != (rhs_text[0] == '-')) result.push_back('-');
    for (int i = begin; i < int(coefficients.size()); ++i) {
        result.push_back(char('0' + coefficients[i]));
    }
    return result;
}

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
        assert((BigInt(lhs) * BigInt(rhs)).to_string() == multiply_naive(lhs, rhs));
    }

    for (int iteration = 0; iteration < 2; ++iteration) {
        const std::string lhs = random_integer(random, 1300, true);
        const std::string rhs = random_integer(random, 1250, true);
        assert((BigInt(lhs) * BigInt(rhs)).to_string() == multiply_naive(lhs, rhs));
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
