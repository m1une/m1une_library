#ifndef M1UNE_UTILITIES_BIGINT_HPP
#define M1UNE_UTILITIES_BIGINT_HPP 1

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "../math/fps/convolution.hpp"

namespace m1une {
namespace utilities {

struct BigInt {
    static constexpr int BASE = 1000000000;
    static constexpr int BASE_DIGITS = 9;

    std::vector<int> a;
    int sign;

    BigInt() : sign(1) {}

    BigInt(long long v) {
        *this = v;
    }

    BigInt(const std::string& s) {
        read(s);
    }

    BigInt& operator=(long long v) {
        sign = 1;
        unsigned long long magnitude = static_cast<unsigned long long>(v);
        if (v < 0) {
            sign = -1;
            magnitude = 0 - magnitude;
        }
        a.clear();
        for (; magnitude > 0; magnitude /= BASE) {
            a.push_back(int(magnitude % BASE));
        }
        return *this;
    }

    BigInt& operator=(const std::string& s) {
        read(s);
        return *this;
    }

    void trim() {
        while (!a.empty() && a.back() == 0) {
            a.pop_back();
        }
        if (a.empty()) sign = 1;
    }

    void read(const std::string& s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-') sign = -1;
            ++pos;
        }
        for (int i = int(s.size()) - 1; i >= pos; i -= BASE_DIGITS) {
            int x = 0;
            for (int j = std::max(pos, i - BASE_DIGITS + 1); j <= i; ++j) {
                x = x * 10 + (s[j] - '0');
            }
            a.push_back(x);
        }
        trim();
    }

    std::string to_string() const {
        if (a.empty()) return "0";
        std::string res = "";
        if (sign == -1) res += '-';
        res += std::to_string(a.back());
        for (int i = (int)a.size() - 2; i >= 0; --i) {
            std::string block = std::to_string(a[i]);
            res += std::string(BASE_DIGITS - block.length(), '0') + block;
        }
        return res;
    }

    bool is_zero() const {
        return a.empty() || (a.size() == 1 && a[0] == 0);
    }

    BigInt operator-() const {
        BigInt res = *this;
        if (!is_zero()) res.sign = -sign;
        return res;
    }

    BigInt abs() const {
        BigInt res = *this;
        res.sign = 1;
        return res;
    }

    friend bool operator<(const BigInt& x, const BigInt& y) {
        if (x.sign != y.sign) return x.sign < y.sign;
        if (x.a.size() != y.a.size()) {
            return (x.sign == 1) ? (x.a.size() < y.a.size()) : (x.a.size() > y.a.size());
        }
        for (int i = (int)x.a.size() - 1; i >= 0; --i) {
            if (x.a[i] != y.a[i]) {
                return (x.sign == 1) ? (x.a[i] < y.a[i]) : (x.a[i] > y.a[i]);
            }
        }
        return false;
    }

    friend bool operator>(const BigInt& x, const BigInt& y) {
        return y < x;
    }
    friend bool operator<=(const BigInt& x, const BigInt& y) {
        return !(y < x);
    }
    friend bool operator>=(const BigInt& x, const BigInt& y) {
        return !(x < y);
    }
    friend bool operator==(const BigInt& x, const BigInt& y) {
        return !(x < y) && !(y < x);
    }
    friend bool operator!=(const BigInt& x, const BigInt& y) {
        return x < y || y < x;
    }

    BigInt& operator+=(const BigInt& other) {
        if (other.is_zero()) return *this;
        if (is_zero()) return *this = other;
        if (sign != other.sign) return *this -= (-other);
        for (int i = 0, carry = 0; i < (int)std::max(a.size(), other.a.size()) || carry; ++i) {
            if (i == (int)a.size()) a.push_back(0);
            a[i] += carry + (i < (int)other.a.size() ? other.a[i] : 0);
            carry = a[i] >= BASE;
            if (carry) a[i] -= BASE;
        }
        return *this;
    }

    BigInt& operator-=(const BigInt& other) {
        if (other.is_zero()) return *this;
        if (is_zero()) return *this = -other;
        if (sign != other.sign) return *this += (-other);
        if (abs() < other.abs()) {
            BigInt tmp = other;
            tmp -= *this;
            *this = tmp;
            sign = -sign;
            return *this;
        }
        for (int i = 0, carry = 0; i < (int)other.a.size() || carry; ++i) {
            a[i] -= carry + (i < (int)other.a.size() ? other.a[i] : 0);
            carry = a[i] < 0;
            if (carry) a[i] += BASE;
        }
        trim();
        return *this;
    }

    BigInt& operator*=(int v) {
        long long multiplier = v;
        if (multiplier < 0) {
            sign = -sign;
            multiplier = -multiplier;
        }
        long long carry = 0;
        for (int i = 0; i < (int)a.size() || carry; ++i) {
            if (i == (int)a.size()) a.push_back(0);
            const long long cur = a[i] * multiplier + carry;
            carry = cur / BASE;
            a[i] = (int)(cur % BASE);
        }
        trim();
        return *this;
    }

   private:
    static constexpr int MULTIPLICATION_THRESHOLD = 128;
    static constexpr int DIVISION_THRESHOLD = 64;
    static constexpr int CONVOLUTION_BASE = 1000;

    static void trim_magnitude(std::vector<int>& value) {
        while (!value.empty() && value.back() == 0) value.pop_back();
    }

    static bool magnitude_less(const std::vector<int>& lhs, const std::vector<int>& rhs) {
        if (lhs.size() != rhs.size()) return lhs.size() < rhs.size();
        for (int i = int(lhs.size()) - 1; i >= 0; --i) {
            if (lhs[i] != rhs[i]) return lhs[i] < rhs[i];
        }
        return false;
    }

    static bool magnitude_less_equal(const std::vector<int>& lhs,
                                     const std::vector<int>& rhs) {
        return !magnitude_less(rhs, lhs);
    }

    static std::vector<int> add_magnitude(const std::vector<int>& lhs,
                                          const std::vector<int>& rhs) {
        std::vector<int> result(std::max(lhs.size(), rhs.size()) + 1);
        for (int i = 0; i < int(result.size()) - 1; ++i) {
            if (i < int(lhs.size())) result[i] += lhs[i];
            if (i < int(rhs.size())) result[i] += rhs[i];
            if (result[i] >= BASE) {
                result[i] -= BASE;
                result[i + 1]++;
            }
        }
        trim_magnitude(result);
        return result;
    }

    static std::vector<int> subtract_magnitude(const std::vector<int>& lhs,
                                               const std::vector<int>& rhs) {
        assert(!magnitude_less(lhs, rhs));
        std::vector<int> result = lhs;
        int borrow = 0;
        for (int i = 0; i < int(result.size()); ++i) {
            const long long current =
                (long long)result[i] - borrow - (i < int(rhs.size()) ? rhs[i] : 0);
            if (current < 0) {
                result[i] = int(current + BASE);
                borrow = 1;
            } else {
                result[i] = int(current);
                borrow = 0;
            }
        }
        assert(borrow == 0);
        trim_magnitude(result);
        return result;
    }

    static std::vector<int> multiply_naive(const std::vector<int>& lhs,
                                           const std::vector<int>& rhs) {
        if (lhs.empty() || rhs.empty()) return std::vector<int>();
        std::vector<long long> product(lhs.size() + rhs.size());
        constexpr long long REDUCTION = 4LL * BASE * BASE;
        for (int i = 0; i < int(lhs.size()); ++i) {
            for (int j = 0; j < int(rhs.size()); ++j) {
                product[i + j] += (long long)lhs[i] * rhs[j];
                if (product[i + j] >= REDUCTION) {
                    product[i + j] -= REDUCTION;
                    product[i + j + 1] += 4LL * BASE;
                }
            }
        }

        std::vector<int> result;
        result.reserve(product.size() + 1);
        long long carry = 0;
        for (int i = 0; i < int(product.size()) || carry > 0; ++i) {
            if (i < int(product.size())) carry += product[i];
            result.push_back(int(carry % BASE));
            carry /= BASE;
        }
        trim_magnitude(result);
        return result;
    }

    static std::vector<int> split_for_convolution(const std::vector<int>& value) {
        std::vector<int> result(3 * value.size());
        for (int i = 0; i < int(value.size()); ++i) {
            int limb = value[i];
            result[3 * i] = limb % CONVOLUTION_BASE;
            limb /= CONVOLUTION_BASE;
            result[3 * i + 1] = limb % CONVOLUTION_BASE;
            result[3 * i + 2] = limb / CONVOLUTION_BASE;
        }
        trim_magnitude(result);
        return result;
    }

    static std::vector<int> multiply_convolution(const std::vector<int>& lhs,
                                                 const std::vector<int>& rhs) {
        using Mint1 = math::ModInt<998244353>;
        using Mint2 = math::ModInt<754974721>;

        const std::vector<int> lhs_digits = split_for_convolution(lhs);
        const std::vector<int> rhs_digits = split_for_convolution(rhs);
        const int result_size = int(lhs_digits.size() + rhs_digits.size() - 1);
        assert(result_size <= (1 << 24));

        std::vector<Mint1> residues1;
        {
            std::vector<Mint1> x(lhs_digits.begin(), lhs_digits.end());
            std::vector<Mint1> y(rhs_digits.begin(), rhs_digits.end());
            residues1 = fps::convolution(x, y);
        }
        std::vector<Mint2> residues2;
        {
            std::vector<Mint2> x(lhs_digits.begin(), lhs_digits.end());
            std::vector<Mint2> y(rhs_digits.begin(), rhs_digits.end());
            residues2 = fps::convolution(x, y);
        }

        constexpr uint64_t MOD1 = Mint1::mod();
        constexpr uint64_t MOD2 = Mint2::mod();
        const uint64_t inverse_mod1 = Mint2(MOD1).inv().val();
        std::vector<int> digits;
        digits.reserve(result_size + 8);
        uint64_t carry = 0;
        for (int i = 0; i < result_size || carry > 0; ++i) {
            if (i < result_size) {
                const uint64_t first = residues1[i].val();
                const uint64_t second = residues2[i].val();
                const uint64_t difference = (second + MOD2 - first % MOD2) % MOD2;
                const uint64_t quotient = difference * inverse_mod1 % MOD2;
                carry += first + MOD1 * quotient;
            }
            digits.push_back(int(carry % CONVOLUTION_BASE));
            carry /= CONVOLUTION_BASE;
        }

        std::vector<int> result((digits.size() + 2) / 3);
        constexpr int POWER[3] = {1, CONVOLUTION_BASE,
                                  CONVOLUTION_BASE * CONVOLUTION_BASE};
        for (int i = 0; i < int(digits.size()); ++i) {
            result[i / 3] += digits[i] * POWER[i % 3];
        }
        trim_magnitude(result);
        return result;
    }

    static std::vector<int> multiply_magnitude(const std::vector<int>& lhs,
                                               const std::vector<int>& rhs) {
        if (lhs.empty() || rhs.empty()) return std::vector<int>();
        if (std::min(lhs.size(), rhs.size()) <= MULTIPLICATION_THRESHOLD) {
            return multiply_naive(lhs, rhs);
        }
        return multiply_convolution(lhs, rhs);
    }

    static std::pair<std::vector<int>, std::vector<int>> divide_by_limb(
        const std::vector<int>& dividend, int divisor) {
        assert(0 < divisor && divisor < BASE);
        if (divisor == 1) {
            return std::make_pair(dividend, std::vector<int>());
        }
        std::vector<int> quotient(dividend.size());
        long long remainder = 0;
        for (int i = int(dividend.size()) - 1; i >= 0; --i) {
            const long long current = remainder * BASE + dividend[i];
            quotient[i] = int(current / divisor);
            remainder = current % divisor;
        }
        trim_magnitude(quotient);
        std::vector<int> remainder_digits;
        if (remainder != 0) remainder_digits.push_back(int(remainder));
        return std::make_pair(std::move(quotient), std::move(remainder_digits));
    }

    static std::pair<std::vector<int>, std::vector<int>> divide_naive(
        const std::vector<int>& dividend, const std::vector<int>& divisor) {
        assert(!divisor.empty());
        if (divisor.size() == 1) return divide_by_limb(dividend, divisor[0]);
        if (magnitude_less(dividend, divisor)) {
            return std::make_pair(std::vector<int>(), dividend);
        }

        const int normalization = BASE / (divisor.back() + 1);
        const std::vector<int> normalized_dividend =
            multiply_magnitude(dividend, std::vector<int>(1, normalization));
        const std::vector<int> normalized_divisor =
            multiply_magnitude(divisor, std::vector<int>(1, normalization));
        const long long leading_divisor = normalized_divisor.back();
        std::vector<int> quotient(normalized_dividend.size() - normalized_divisor.size() + 1);
        std::vector<int> remainder(normalized_dividend.end() - normalized_divisor.size(),
                                   normalized_dividend.end());

        for (int i = int(quotient.size()) - 1; i >= 0; --i) {
            if (remainder.size() < normalized_divisor.size()) {
                quotient[i] = 0;
            } else if (remainder.size() == normalized_divisor.size()) {
                if (magnitude_less_equal(normalized_divisor, remainder)) {
                    quotient[i] = 1;
                    remainder = subtract_magnitude(remainder, normalized_divisor);
                }
            } else {
                assert(remainder.size() == normalized_divisor.size() + 1);
                const long long leading_remainder =
                    (long long)remainder.back() * BASE + remainder[remainder.size() - 2];
                int digit = int(leading_remainder / leading_divisor);
                if (digit >= BASE) digit = BASE - 1;
                std::vector<int> product = multiply_magnitude(
                    normalized_divisor, std::vector<int>(1, digit));
                while (magnitude_less(remainder, product)) {
                    --digit;
                    product = subtract_magnitude(product, normalized_divisor);
                }
                remainder = subtract_magnitude(remainder, product);
                while (magnitude_less_equal(normalized_divisor, remainder)) {
                    ++digit;
                    remainder = subtract_magnitude(remainder, normalized_divisor);
                }
                quotient[i] = digit;
            }
            if (i > 0) remainder.insert(remainder.begin(), normalized_dividend[i - 1]);
        }

        trim_magnitude(quotient);
        trim_magnitude(remainder);
        std::pair<std::vector<int>, std::vector<int>> denormalized =
            divide_by_limb(remainder, normalization);
        assert(denormalized.second.empty());
        return std::make_pair(std::move(quotient), std::move(denormalized.first));
    }

    static std::vector<int> reciprocal(const std::vector<int>& value, int degree) {
        assert(!value.empty());
        assert(BASE / 2 <= value.back() && value.back() < BASE);
        assert(degree >= 0);

        int precision = degree;
        const int value_size = int(value.size());
        while (precision > DIVISION_THRESHOLD) precision = (precision + 1) / 2;

        std::vector<int> inverse(value_size + precision + 1);
        inverse.back() = 1;
        inverse = divide_naive(inverse, value).first;

        while (precision < degree) {
            std::vector<int> square = multiply_magnitude(inverse, inverse);
            square.insert(square.begin(), 0);

            std::vector<int> leading(2 * precision + 1);
            const int copied = std::min(value_size, int(leading.size()));
            std::copy(value.end() - copied, value.end(), leading.end() - copied);

            std::vector<int> correction = multiply_magnitude(square, leading);
            assert(int(correction.size()) >= 2 * precision + 1);
            correction.erase(correction.begin(), correction.begin() + 2 * precision + 1);

            std::vector<int> shifted(precision + 1);
            const std::vector<int> doubled = add_magnitude(inverse, inverse);
            shifted.insert(shifted.end(), doubled.begin(), doubled.end());
            inverse = subtract_magnitude(shifted, correction);
            assert(!inverse.empty());
            inverse.erase(inverse.begin());
            precision *= 2;
        }

        assert(precision >= degree);
        inverse.erase(inverse.begin(), inverse.begin() + precision - degree);
        trim_magnitude(inverse);
        return inverse;
    }

    static std::pair<std::vector<int>, std::vector<int>> divide_magnitude(
        const std::vector<int>& dividend, const std::vector<int>& divisor) {
        assert(!divisor.empty());
        if (divisor.size() <= DIVISION_THRESHOLD ||
            int(dividend.size()) - int(divisor.size()) <= DIVISION_THRESHOLD) {
            return divide_naive(dividend, divisor);
        }

        const int normalization = BASE / (divisor.back() + 1);
        const std::vector<int> normalized_dividend =
            multiply_magnitude(dividend, std::vector<int>(1, normalization));
        const std::vector<int> normalized_divisor =
            multiply_magnitude(divisor, std::vector<int>(1, normalization));
        const int dividend_size = int(normalized_dividend.size());
        const int divisor_size = int(normalized_divisor.size());
        const int degree = dividend_size - divisor_size + 2;
        const std::vector<int> inverse = reciprocal(normalized_divisor, degree);

        std::vector<int> quotient = multiply_magnitude(normalized_dividend, inverse);
        const int discarded = divisor_size + degree;
        assert(discarded <= int(quotient.size()));
        quotient.erase(quotient.begin(), quotient.begin() + discarded);

        std::vector<int> product = multiply_magnitude(normalized_divisor, quotient);
        while (magnitude_less(normalized_dividend, product)) {
            quotient = subtract_magnitude(quotient, std::vector<int>(1, 1));
            product = subtract_magnitude(product, normalized_divisor);
        }
        std::vector<int> remainder = subtract_magnitude(normalized_dividend, product);
        while (magnitude_less_equal(normalized_divisor, remainder)) {
            quotient = add_magnitude(quotient, std::vector<int>(1, 1));
            remainder = subtract_magnitude(remainder, normalized_divisor);
        }
        trim_magnitude(quotient);
        trim_magnitude(remainder);

        std::pair<std::vector<int>, std::vector<int>> denormalized =
            divide_by_limb(remainder, normalization);
        assert(denormalized.second.empty());
        return std::make_pair(std::move(quotient), std::move(denormalized.first));
    }

   public:
    BigInt& operator*=(const BigInt& other) {
        if (is_zero() || other.is_zero()) return *this = 0;
        const int result_sign = sign * other.sign;
        a = multiply_magnitude(a, other.a);
        sign = result_sign;
        trim();
        return *this;
    }

    friend std::pair<BigInt, BigInt> divmod(const BigInt& a1, const BigInt& b1) {
        if (b1.is_zero()) {
            throw std::domain_error("BigInt division by zero");
        }
        std::pair<std::vector<int>, std::vector<int>> result =
            divide_magnitude(a1.a, b1.a);
        BigInt q, r;
        q.a = std::move(result.first);
        r.a = std::move(result.second);
        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return {q, r};
    }

    BigInt& operator/=(const BigInt& other) {
        return *this = divmod(*this, other).first;
    }
    BigInt& operator%=(const BigInt& other) {
        return *this = divmod(*this, other).second;
    }

    friend BigInt operator+(BigInt x, const BigInt& y) {
        return x += y;
    }
    friend BigInt operator-(BigInt x, const BigInt& y) {
        return x -= y;
    }
    friend BigInt operator*(BigInt x, const BigInt& y) {
        return x *= y;
    }
    friend BigInt operator/(BigInt x, const BigInt& y) {
        return x /= y;
    }
    friend BigInt operator%(BigInt x, const BigInt& y) {
        return x %= y;
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInt& b) {
        return os << b.to_string();
    }

    friend std::istream& operator>>(std::istream& is, BigInt& b) {
        std::string s;
        if (is >> s) b.read(s);
        return is;
    }
};

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_UTILITIES_BIGINT_HPP
