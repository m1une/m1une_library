#ifndef M1UNE_UTILITIES_BIGINT_HPP
#define M1UNE_UTILITIES_BIGINT_HPP 1

#include <algorithm>
#include <bit>
#include <cassert>
#include <charconv>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <numbers>
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
        a.reserve((int(s.size()) - pos + BASE_DIGITS - 1) / BASE_DIGITS);
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
        char leading[BASE_DIGITS];
        const std::to_chars_result converted =
            std::to_chars(leading, leading + BASE_DIGITS, a.back());
        assert(converted.ec == std::errc());
        const int leading_size = int(converted.ptr - leading);
        std::string res((sign == -1) + leading_size +
                            (a.size() - 1) * BASE_DIGITS,
                        '0');
        int offset = 0;
        if (sign == -1) res[offset++] = '-';
        std::copy(leading, converted.ptr, res.begin() + offset);
        offset += leading_size;
        for (int i = (int)a.size() - 2; i >= 0; --i) {
            char block[BASE_DIGITS];
            const std::to_chars_result block_converted =
                std::to_chars(block, block + BASE_DIGITS, a[i]);
            assert(block_converted.ec == std::errc());
            const int block_size = int(block_converted.ptr - block);
            std::copy(block, block_converted.ptr,
                      res.begin() + offset + BASE_DIGITS - block_size);
            offset += BASE_DIGITS;
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
        return x.sign == y.sign && x.a == y.a;
    }
    friend bool operator!=(const BigInt& x, const BigInt& y) {
        return !(x == y);
    }

    BigInt& operator+=(const BigInt& other) {
        if (other.is_zero()) return *this;
        if (is_zero()) return *this = other;
        if (sign != other.sign) {
            const int comparison = magnitude_compare(a, other.a);
            if (comparison == 0) {
                a.clear();
                sign = 1;
            } else if (comparison > 0) {
                subtract_magnitude_inplace(a, other.a);
            } else {
                std::vector<int> result = other.a;
                subtract_magnitude_inplace(result, a);
                a = std::move(result);
                sign = other.sign;
            }
            return *this;
        }
        add_magnitude_inplace(a, other.a);
        return *this;
    }

    BigInt& operator-=(const BigInt& other) {
        if (other.is_zero()) return *this;
        if (is_zero()) return *this = -other;
        if (sign != other.sign) {
            add_magnitude_inplace(a, other.a);
            return *this;
        }
        const int comparison = magnitude_compare(a, other.a);
        if (comparison == 0) {
            a.clear();
            sign = 1;
        } else if (comparison > 0) {
            subtract_magnitude_inplace(a, other.a);
        } else {
            std::vector<int> result = other.a;
            subtract_magnitude_inplace(result, a);
            a = std::move(result);
            sign = -sign;
        }
        return *this;
    }

    BigInt& operator*=(int v) {
        if (v == 0 || is_zero()) return *this = 0;
        long long multiplier = v;
        if (multiplier < 0) {
            sign = -sign;
            multiplier = -multiplier;
        }
        a.reserve(a.size() + 2);
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
    static constexpr int SQUARE_THRESHOLD = 224;
    static constexpr int DIVISION_THRESHOLD = 64;
    static constexpr int FFT_SPLIT = 1 << 15;

    struct FftComplex {
        double real;
        double imaginary;

        FftComplex operator+(const FftComplex& other) const {
            return {real + other.real, imaginary + other.imaginary};
        }

        FftComplex operator-(const FftComplex& other) const {
            return {real - other.real, imaginary - other.imaginary};
        }

        FftComplex operator*(const FftComplex& other) const {
            return {real * other.real - imaginary * other.imaginary,
                    real * other.imaginary + imaginary * other.real};
        }

        FftComplex operator*(double scalar) const {
            return {real * scalar, imaginary * scalar};
        }

        FftComplex conjugate() const {
            return {real, -imaginary};
        }
    };

    struct FftProducts {
        FftComplex diagonal;
        FftComplex cross;
    };

    static const std::vector<FftComplex>& fft_roots(int size) {
        static std::vector<FftComplex> roots(2, FftComplex{1, 0});
        if (int(roots.size()) < size) {
            int length = int(roots.size());
            roots.resize(size);
            while (length < size) {
                const long double angle = std::numbers::pi_v<long double> / length;
                const long double step_real = std::cos(angle);
                const long double step_imaginary = std::sin(angle);
                for (int i = length; i < 2 * length; ++i) {
                    roots[i] = roots[i / 2];
                    if (i & 1) {
                        const long double real = roots[i].real;
                        const long double imaginary = roots[i].imaginary;
                        roots[i] = {
                            double(real * step_real - imaginary * step_imaginary),
                            double(real * step_imaginary + imaginary * step_real)};
                    }
                }
                length *= 2;
            }
        }
        return roots;
    }

    static void fft(std::vector<FftComplex>& values) {
        const int size = int(values.size());
        assert(size > 0 && (size & (size - 1)) == 0);
        const std::vector<FftComplex>& roots = fft_roots(size);

        // Decimation in frequency leaves the spectrum bit-reversed. The inverse
        // transform consumes that order directly, avoiding permutation passes.
        for (int length = size / 2; length > 0; length /= 2) {
            for (int offset = 0; offset < size; offset += 2 * length) {
                for (int i = 0; i < length; ++i) {
                    const FftComplex even = values[offset + i];
                    const FftComplex odd = values[offset + i + length];
                    values[offset + i] = even + odd;
                    values[offset + i + length] =
                        (even - odd) * roots[length + i];
                }
            }
        }
    }

    static void inverse_fft(std::vector<FftComplex>& values) {
        const int size = int(values.size());
        assert(size > 0 && (size & (size - 1)) == 0);
        const std::vector<FftComplex>& roots = fft_roots(size);

        for (int length = 1; length < size; length *= 2) {
            for (int offset = 0; offset < size; offset += 2 * length) {
                for (int i = 0; i < length; ++i) {
                    const FftComplex even = values[offset + i];
                    const FftComplex value = values[offset + i + length];
                    const FftComplex root = roots[length + i];
                    const FftComplex odd = {
                        value.real * root.real + value.imaginary * root.imaginary,
                        value.imaginary * root.real - value.real * root.imaginary};
                    values[offset + i] = even + odd;
                    values[offset + i + length] = even - odd;
                }
            }
        }
        const double inverse_size = 1.0 / double(size);
        for (FftComplex& value : values) {
            value.real *= inverse_size;
            value.imaginary *= inverse_size;
        }
    }

    static FftComplex fft_low(const FftComplex& value,
                              const FftComplex& reflected) {
        return (value + reflected) * 0.5;
    }

    static FftComplex fft_high(const FftComplex& value,
                               const FftComplex& reflected) {
        const FftComplex difference = value - reflected;
        return {difference.imaginary * 0.5, -difference.real * 0.5};
    }

    static void trim_magnitude(std::vector<int>& value) {
        while (!value.empty() && value.back() == 0) value.pop_back();
    }

    static bool magnitude_less(const std::vector<int>& lhs, const std::vector<int>& rhs) {
        return magnitude_compare(lhs, rhs) < 0;
    }

    static int magnitude_compare(const std::vector<int>& lhs,
                                 const std::vector<int>& rhs) {
        if (lhs.size() != rhs.size()) return lhs.size() < rhs.size() ? -1 : 1;
        for (int i = int(lhs.size()) - 1; i >= 0; --i) {
            if (lhs[i] != rhs[i]) return lhs[i] < rhs[i] ? -1 : 1;
        }
        return 0;
    }

    static void add_magnitude_inplace(std::vector<int>& lhs,
                                      const std::vector<int>& rhs) {
        const int lhs_size = int(lhs.size());
        const int rhs_size = int(rhs.size());
        const int size = std::max(lhs_size, rhs_size);
        if (lhs_size < rhs_size) lhs.resize(rhs_size);
        int carry = 0;
        int i = 0;
        for (; i < rhs_size; ++i) {
            const long long current = (long long)lhs[i] + rhs[i] + carry;
            lhs[i] = int(current >= BASE ? current - BASE : current);
            carry = current >= BASE;
        }
        while (i < size && carry) {
            ++lhs[i];
            carry = lhs[i] == BASE;
            if (carry) lhs[i] = 0;
            ++i;
        }
        if (carry) lhs.push_back(1);
    }

    static void subtract_magnitude_inplace(std::vector<int>& lhs,
                                           const std::vector<int>& rhs) {
        assert(!magnitude_less(lhs, rhs));
        int borrow = 0;
        for (int i = 0; i < int(rhs.size()) || borrow; ++i) {
            int current = lhs[i] - borrow - (i < int(rhs.size()) ? rhs[i] : 0);
            borrow = current < 0;
            if (borrow) current += BASE;
            lhs[i] = current;
        }
        assert(borrow == 0);
        trim_magnitude(lhs);
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

    static std::vector<int> square_naive(const std::vector<int>& value) {
        if (value.empty()) return std::vector<int>();
        std::vector<long long> product(2 * value.size());
        constexpr long long REDUCTION = 4LL * BASE * BASE;
        for (int i = 0; i < int(value.size()); ++i) {
            product[2 * i] += (long long)value[i] * value[i];
            if (product[2 * i] >= REDUCTION) {
                product[2 * i] -= REDUCTION;
                product[2 * i + 1] += 4LL * BASE;
            }
            for (int j = i + 1; j < int(value.size()); ++j) {
                product[i + j] += 2LL * value[i] * value[j];
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

    static std::vector<int> multiply_by_limb(const std::vector<int>& value,
                                             int multiplier) {
        assert(0 <= multiplier && multiplier < BASE);
        if (value.empty() || multiplier == 0) return std::vector<int>();
        std::vector<int> result;
        result.reserve(value.size() + 1);
        uint64_t carry = 0;
        for (int limb : value) {
            const uint64_t current = uint64_t(limb) * multiplier + carry;
            result.push_back(int(current % BASE));
            carry = current / BASE;
        }
        if (carry) result.push_back(int(carry));
        return result;
    }

    static std::vector<int> multiply_ntt(const std::vector<int>& lhs,
                                         const std::vector<int>& rhs) {
        using Mint1 = math::ModInt<998244353>;
        using Mint2 = math::ModInt<754974721>;
        using Mint3 = math::ModInt<469762049>;

        const int result_size = int(lhs.size() + rhs.size() - 1);
        assert(result_size <= (1 << 24));

        auto convolve = [&]<class Mint>() {
            std::vector<Mint> x(lhs.begin(), lhs.end());
            if (&lhs == &rhs) return fps::convolution(x, x);
            std::vector<Mint> y(rhs.begin(), rhs.end());
            return fps::convolution(x, y);
        };
        const std::vector<Mint1> residues1 = convolve.template operator()<Mint1>();
        const std::vector<Mint2> residues2 = convolve.template operator()<Mint2>();
        const std::vector<Mint3> residues3 = convolve.template operator()<Mint3>();

        constexpr uint64_t MOD1 = Mint1::mod();
        constexpr uint64_t MOD2 = Mint2::mod();
        constexpr uint64_t MOD3 = Mint3::mod();
        constexpr uint64_t MOD12 = MOD1 * MOD2;
        const static uint64_t inverse_mod1_mod2 = Mint2(MOD1).inv().val();
        const static uint64_t inverse_mod12_mod3 = Mint3(MOD12 % MOD3).inv().val();
        [[maybe_unused]] const unsigned __int128 coefficient_bound =
            static_cast<unsigned __int128>(std::min(lhs.size(), rhs.size())) *
            (BASE - 1) * (BASE - 1);
        [[maybe_unused]] constexpr unsigned __int128 CRT_MODULUS =
            static_cast<unsigned __int128>(MOD12) * MOD3;
        assert(coefficient_bound < CRT_MODULUS);

        std::vector<int> result;
        result.reserve(result_size + 2);
        unsigned __int128 carry = 0;
        for (int i = 0; i < result_size || carry > 0; ++i) {
            if (i < result_size) {
                const uint64_t first = residues1[i].val();
                const uint64_t second = residues2[i].val();
                const uint64_t third = residues3[i].val();
                const uint64_t difference12 =
                    (second + MOD2 - first % MOD2) % MOD2;
                const uint64_t quotient12 =
                    difference12 * inverse_mod1_mod2 % MOD2;
                const uint64_t combined12 = first + MOD1 * quotient12;
                const uint64_t difference3 =
                    (third + MOD3 - combined12 % MOD3) % MOD3;
                const uint64_t quotient3 =
                    difference3 * inverse_mod12_mod3 % MOD3;
                carry += combined12 +
                         static_cast<unsigned __int128>(MOD12) * quotient3;
            }
            result.push_back(int(carry % BASE));
            carry /= BASE;
        }
        trim_magnitude(result);
        return result;
    }

    static uint64_t mersenne_reduce(unsigned __int128 value) {
        constexpr uint64_t MODULUS = (uint64_t(1) << 61) - 1;
        value = (value & MODULUS) + (value >> 61);
        uint64_t result = uint64_t(value & MODULUS) + uint64_t(value >> 61);
        if (result >= MODULUS) result -= MODULUS;
        return result;
    }

    static uint64_t magnitude_mod(const std::vector<int>& value) {
        uint64_t result = 0;
        for (int i = int(value.size()) - 1; i >= 0; --i) {
            result = mersenne_reduce(static_cast<unsigned __int128>(result) * BASE +
                                     value[i]);
        }
        return result;
    }

    static bool product_matches(const std::vector<int>& lhs, const std::vector<int>& rhs,
                                const std::vector<int>& product) {
        const uint64_t expected = mersenne_reduce(
            static_cast<unsigned __int128>(magnitude_mod(lhs)) * magnitude_mod(rhs));
        return magnitude_mod(product) == expected;
    }

    static std::vector<int> multiply_fft(const std::vector<int>& lhs,
                                         const std::vector<int>& rhs) {
        const int result_size = int(lhs.size() + rhs.size() - 1);
        const int transform_size = int(std::bit_ceil(unsigned(result_size)));
        const unsigned __int128 coefficient_bound =
            static_cast<unsigned __int128>(std::min(lhs.size(), rhs.size())) *
            2 * (FFT_SPLIT - 1) * ((BASE - 1) / FFT_SPLIT);
        if (transform_size > (1 << 20) || coefficient_bound >= (uint64_t(1) << 48)) {
            return multiply_ntt(lhs, rhs);
        }

        std::vector<FftComplex> transformed_lhs(transform_size, FftComplex{0, 0});
        for (int i = 0; i < int(lhs.size()); ++i) {
            transformed_lhs[i] = {double(lhs[i] % FFT_SPLIT),
                                  double(lhs[i] / FFT_SPLIT)};
        }
        fft(transformed_lhs);

        const bool squaring = &lhs == &rhs;
        std::vector<FftComplex> transformed_rhs;
        if (!squaring) {
            transformed_rhs.assign(transform_size, FftComplex{0, 0});
            for (int i = 0; i < int(rhs.size()); ++i) {
                transformed_rhs[i] = {double(rhs[i] % FFT_SPLIT),
                                      double(rhs[i] / FFT_SPLIT)};
            }
            fft(transformed_rhs);
        }

        std::vector<FftComplex> square_cross_product;
        if (squaring) square_cross_product.resize(transform_size);
        static std::vector<int> reflected_indices;
        if (int(reflected_indices.size()) != transform_size) {
            reflected_indices.resize(transform_size);
            reflected_indices[0] = 0;
            for (int i = 1; i < transform_size; ++i) {
                // Negating a frequency complements the bits below the highest
                // set bit of its bit-reversed index.
                reflected_indices[i] =
                    i ^ int(std::bit_floor(unsigned(i)) - 1);
            }
        }
        auto calculate_products = [&](int index) {
            const int opposite = reflected_indices[index];
            const FftComplex lhs_reflected =
                transformed_lhs[opposite].conjugate();
            const FftComplex lhs_low =
                fft_low(transformed_lhs[index], lhs_reflected);
            const FftComplex lhs_high =
                fft_high(transformed_lhs[index], lhs_reflected);

            FftComplex rhs_low = lhs_low;
            FftComplex rhs_high = lhs_high;
            if (!squaring) {
                const FftComplex rhs_reflected =
                    transformed_rhs[opposite].conjugate();
                rhs_low = fft_low(transformed_rhs[index], rhs_reflected);
                rhs_high = fft_high(transformed_rhs[index], rhs_reflected);
            }

            const FftComplex low_product = lhs_low * rhs_low;
            const FftComplex high_product = lhs_high * rhs_high;
            const FftComplex diagonal =
                low_product + FftComplex{-high_product.imaginary,
                                         high_product.real};
            const FftComplex cross =
                lhs_low * rhs_high + lhs_high * rhs_low;
            return FftProducts{diagonal, cross};
        };

        for (int i = 0; i < transform_size; ++i) {
            const int opposite = reflected_indices[i];
            if (i > opposite) continue;
            const FftProducts products = calculate_products(i);
            FftProducts opposite_products = products;
            if (i != opposite) opposite_products = calculate_products(opposite);

            transformed_lhs[i] = products.diagonal;
            transformed_lhs[opposite] = opposite_products.diagonal;
            if (squaring) {
                square_cross_product[i] = products.cross;
                square_cross_product[opposite] = opposite_products.cross;
            } else {
                transformed_rhs[i] = products.cross;
                transformed_rhs[opposite] = opposite_products.cross;
            }
        }
        std::vector<FftComplex>& cross_product =
            squaring ? square_cross_product : transformed_rhs;
        inverse_fft(transformed_lhs);
        inverse_fft(cross_product);

        std::vector<int> result;
        result.reserve(result_size + 2);
        unsigned __int128 carry = 0;
        for (int i = 0; i < result_size || carry > 0; ++i) {
            if (i < result_size) {
                const long long low = std::llround(transformed_lhs[i].real);
                const long long high = std::llround(transformed_lhs[i].imaginary);
                const long long cross = std::llround(cross_product[i].real);
                if (low < 0 || high < 0 || cross < 0) return multiply_ntt(lhs, rhs);
                carry += low + static_cast<unsigned __int128>(cross) * FFT_SPLIT +
                         static_cast<unsigned __int128>(high) * FFT_SPLIT * FFT_SPLIT;
            }
            result.push_back(int(carry % BASE));
            carry /= BASE;
        }
        trim_magnitude(result);
        if (result.empty() || !product_matches(lhs, rhs, result)) {
            return multiply_ntt(lhs, rhs);
        }
        return result;
    }

    static std::vector<int> multiply_magnitude(const std::vector<int>& lhs,
                                               const std::vector<int>& rhs) {
        if (lhs.empty() || rhs.empty()) return std::vector<int>();
        if (lhs.size() == 1) return multiply_by_limb(rhs, lhs[0]);
        if (rhs.size() == 1) return multiply_by_limb(lhs, rhs[0]);
        if (&lhs == &rhs && lhs.size() <= SQUARE_THRESHOLD) {
            return square_naive(lhs);
        }
        if (std::min(lhs.size(), rhs.size()) <= MULTIPLICATION_THRESHOLD) {
            return multiply_naive(lhs, rhs);
        }
        return multiply_fft(lhs, rhs);
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

    static std::pair<std::vector<int>, std::vector<int>> divide_classical(
        const std::vector<int>& dividend, const std::vector<int>& divisor) {
        assert(!divisor.empty());
        if (divisor.size() == 1) return divide_by_limb(dividend, divisor[0]);
        if (magnitude_less(dividend, divisor)) {
            return std::make_pair(std::vector<int>(), dividend);
        }

        const int normalization = BASE / (divisor.back() + 1);
        std::vector<int> normalized_divisor(divisor.size());
        uint64_t carry = 0;
        for (int i = 0; i < int(divisor.size()); ++i) {
            const uint64_t current = uint64_t(divisor[i]) * normalization + carry;
            normalized_divisor[i] = int(current % BASE);
            carry = current / BASE;
        }
        assert(carry == 0);

        std::vector<int> normalized_dividend(dividend.size() + 1);
        carry = 0;
        for (int i = 0; i < int(dividend.size()); ++i) {
            const uint64_t current = uint64_t(dividend[i]) * normalization + carry;
            normalized_dividend[i] = int(current % BASE);
            carry = current / BASE;
        }
        normalized_dividend[dividend.size()] = int(carry);

        const int divisor_size = int(normalized_divisor.size());
        const int quotient_size = int(dividend.size()) - divisor_size + 1;
        const uint64_t leading_divisor = normalized_divisor.back();
        const uint64_t second_divisor = normalized_divisor[divisor_size - 2];
        std::vector<int> quotient(quotient_size);

        for (int position = quotient_size - 1; position >= 0; --position) {
            const uint64_t leading_dividend =
                uint64_t(normalized_dividend[position + divisor_size]) * BASE +
                normalized_dividend[position + divisor_size - 1];
            uint64_t digit = leading_dividend / leading_divisor;
            uint64_t remainder = leading_dividend % leading_divisor;
            if (digit >= BASE) {
                digit = BASE - 1;
                remainder = leading_dividend - digit * leading_divisor;
            }
            while (remainder < BASE &&
                   digit * second_divisor >
                       remainder * BASE +
                           normalized_dividend[position + divisor_size - 2]) {
                --digit;
                remainder += leading_divisor;
            }

            uint64_t borrow = 0;
            for (int i = 0; i < divisor_size; ++i) {
                const uint64_t product =
                    digit * uint64_t(normalized_divisor[i]) + borrow;
                const uint64_t low = product % BASE;
                borrow = product / BASE;
                if (uint64_t(normalized_dividend[position + i]) < low) {
                    normalized_dividend[position + i] =
                        int(uint64_t(normalized_dividend[position + i]) + BASE - low);
                    ++borrow;
                } else {
                    normalized_dividend[position + i] -= int(low);
                }
            }

            long long top =
                (long long)normalized_dividend[position + divisor_size] -
                static_cast<long long>(borrow);
            if (top < 0) {
                --digit;
                uint64_t add_carry = 0;
                for (int i = 0; i < divisor_size; ++i) {
                    const uint64_t current =
                        uint64_t(normalized_dividend[position + i]) +
                        normalized_divisor[i] + add_carry;
                    normalized_dividend[position + i] = int(current % BASE);
                    add_carry = current / BASE;
                }
                top += add_carry;
            }
            assert(0 <= top && top < BASE);
            normalized_dividend[position + divisor_size] = int(top);
            quotient[position] = int(digit);
        }

        trim_magnitude(quotient);
        std::vector<int> remainder(normalized_dividend.begin(),
                                   normalized_dividend.begin() + divisor_size);
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
        inverse = divide_classical(inverse, value).first;

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
            return divide_classical(dividend, divisor);
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
