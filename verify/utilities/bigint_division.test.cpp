#define PROBLEM "https://judge.yosupo.jp/problem/division_of_big_integers"

#include <cassert>
#include <random>
#include <string>
#include <utility>

#include "../../utilities/bigint.hpp"
#include "../../utilities/fast_io.hpp"

namespace {

using m1une::utilities::BigInt;

std::string normalize_unsigned(const std::string& value) {
    int begin = 0;
    while (begin + 1 < int(value.size()) && value[begin] == '0') ++begin;
    return value.empty() ? "0" : value.substr(begin);
}

std::string absolute_decimal(const std::string& value) {
    const int begin = !value.empty() && (value[0] == '-' || value[0] == '+');
    return normalize_unsigned(value.substr(begin));
}

int compare_unsigned(const std::string& lhs, const std::string& rhs) {
    if (lhs.size() != rhs.size()) return lhs.size() < rhs.size() ? -1 : 1;
    if (lhs == rhs) return 0;
    return lhs < rhs ? -1 : 1;
}

std::string multiply_digit(const std::string& value, int digit) {
    assert(0 <= digit && digit <= 9);
    if (digit == 0 || value == "0") return "0";
    std::string result(value.size() + 1, '0');
    int carry = 0;
    for (int i = int(value.size()) - 1; i >= 0; --i) {
        const int current = (value[i] - '0') * digit + carry;
        result[i + 1] = char('0' + current % 10);
        carry = current / 10;
    }
    result[0] = char('0' + carry);
    return normalize_unsigned(result);
}

std::string subtract_unsigned(const std::string& lhs, const std::string& rhs) {
    assert(compare_unsigned(lhs, rhs) >= 0);
    std::string result = lhs;
    int borrow = 0;
    for (int i = int(lhs.size()) - 1, j = int(rhs.size()) - 1; i >= 0; --i, --j) {
        int current = lhs[i] - '0' - borrow - (j >= 0 ? rhs[j] - '0' : 0);
        if (current < 0) {
            current += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[i] = char('0' + current);
    }
    assert(borrow == 0);
    return normalize_unsigned(result);
}

std::pair<std::string, std::string> divide_naive(const std::string& dividend_text,
                                                 const std::string& divisor_text) {
    const std::string dividend = absolute_decimal(dividend_text);
    const std::string divisor = absolute_decimal(divisor_text);
    assert(divisor != "0");

    std::string quotient;
    std::string remainder = "0";
    for (char digit : dividend) {
        remainder.push_back(digit);
        remainder = normalize_unsigned(remainder);

        int lower = 0, upper = 9;
        while (lower < upper) {
            const int middle = (lower + upper + 1) / 2;
            if (compare_unsigned(multiply_digit(divisor, middle), remainder) <= 0) {
                lower = middle;
            } else {
                upper = middle - 1;
            }
        }
        quotient.push_back(char('0' + lower));
        remainder = subtract_unsigned(remainder, multiply_digit(divisor, lower));
    }

    quotient = normalize_unsigned(quotient);
    remainder = normalize_unsigned(remainder);
    const bool dividend_negative = !dividend_text.empty() && dividend_text[0] == '-';
    const bool divisor_negative = !divisor_text.empty() && divisor_text[0] == '-';
    if (quotient != "0" && dividend_negative != divisor_negative) {
        quotient.insert(quotient.begin(), '-');
    }
    if (remainder != "0" && dividend_negative) remainder.insert(remainder.begin(), '-');
    return std::make_pair(std::move(quotient), std::move(remainder));
}

std::string random_integer(std::mt19937_64& random, int digits, bool allow_negative) {
    std::string result;
    if (allow_negative && (random() & 1)) result.push_back('-');
    result.push_back(char('1' + random() % 9));
    for (int i = 1; i < digits; ++i) result.push_back(char('0' + random() % 10));
    return result;
}

void check_division(const std::string& dividend, const std::string& divisor) {
    const std::pair<std::string, std::string> expected = divide_naive(dividend, divisor);
    const std::pair<BigInt, BigInt> actual = divmod(BigInt(dividend), BigInt(divisor));
    assert(actual.first.to_string() == expected.first);
    assert(actual.second.to_string() == expected.second);
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
