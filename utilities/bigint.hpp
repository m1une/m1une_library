#ifndef M1UNE_UTILITIES_BIGINT_HPP
#define M1UNE_UTILITIES_BIGINT_HPP 1

#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <charconv>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <numbers>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#if (defined(__GNUC__) || defined(__clang__)) && \
    (defined(__x86_64__) || defined(__i386__))
#include <immintrin.h>
#define M1UNE_BIGINT_HAS_X86_SIMD 1
#endif

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
        static const auto digit_quads = [] {
            std::array<char, 40000> digits{};
            for (int value = 0; value < 10000; ++value) {
                int current = value;
                for (int index = 3; index >= 0; --index) {
                    digits[4 * value + index] = char('0' + current % 10);
                    current /= 10;
                }
            }
            return digits;
        }();
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
            const unsigned value = unsigned(a[i]);
            const unsigned leading_digit = value / 100000000;
            const unsigned remaining = value - leading_digit * 100000000;
            const unsigned middle = remaining / 10000;
            const unsigned trailing = remaining - middle * 10000;
            res[offset] = char('0' + leading_digit);
            std::memcpy(res.data() + offset + 1, digit_quads.data() + 4 * middle, 4);
            std::memcpy(res.data() + offset + 5, digit_quads.data() + 4 * trailing, 4);
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

#ifdef M1UNE_BIGINT_HAS_X86_SIMD
    __attribute__((target("avx2,fma"), always_inline)) static inline __m256d
    multiply_complex(__m256d value, __m256d root) {
        const __m256d real = _mm256_movedup_pd(value);
        const __m256d imaginary = _mm256_permute_pd(value, 0xf);
        const __m256d swapped_root = _mm256_permute_pd(root, 0x5);
        return _mm256_fmaddsub_pd(real, root,
                                  _mm256_mul_pd(imaginary, swapped_root));
    }

    __attribute__((target("avx2,fma"), hot)) static void fft_simd(
        FftComplex* values, int size) {
        const std::vector<FftComplex>& roots = fft_roots(size);
        for (int length = size / 2; length > 0; length /= 2) {
            for (int offset = 0; offset < size; offset += 2 * length) {
                int i = 0;
                for (; i + 1 < length; i += 2) {
                    const __m256d even = _mm256_loadu_pd(reinterpret_cast<const double*>(
                        values + offset + i));
                    const __m256d odd = _mm256_loadu_pd(reinterpret_cast<const double*>(
                        values + offset + i + length));
                    const __m256d root = _mm256_loadu_pd(reinterpret_cast<const double*>(
                        roots.data() + length + i));
                    _mm256_storeu_pd(reinterpret_cast<double*>(values + offset + i),
                                     _mm256_add_pd(even, odd));
                    _mm256_storeu_pd(
                        reinterpret_cast<double*>(values + offset + i + length),
                        multiply_complex(_mm256_sub_pd(even, odd), root));
                }
                for (; i < length; ++i) {
                    const FftComplex even = values[offset + i];
                    const FftComplex odd = values[offset + i + length];
                    values[offset + i] = even + odd;
                    values[offset + i + length] =
                        (even - odd) * roots[length + i];
                }
            }
        }
    }

    __attribute__((target("avx2,fma"), hot)) static void inverse_fft_simd(
        FftComplex* values, int size) {
        const std::vector<FftComplex>& roots = fft_roots(size);
        const __m256d conjugate_mask = _mm256_setr_pd(0.0, -0.0, 0.0, -0.0);
        for (int length = 1; length < size; length *= 2) {
            for (int offset = 0; offset < size; offset += 2 * length) {
                int i = 0;
                for (; i + 1 < length; i += 2) {
                    const __m256d even = _mm256_loadu_pd(reinterpret_cast<const double*>(
                        values + offset + i));
                    const __m256d value = _mm256_loadu_pd(reinterpret_cast<const double*>(
                        values + offset + i + length));
                    __m256d root = _mm256_loadu_pd(reinterpret_cast<const double*>(
                        roots.data() + length + i));
                    root = _mm256_xor_pd(root, conjugate_mask);
                    const __m256d odd = multiply_complex(value, root);
                    _mm256_storeu_pd(reinterpret_cast<double*>(values + offset + i),
                                     _mm256_add_pd(even, odd));
                    _mm256_storeu_pd(
                        reinterpret_cast<double*>(values + offset + i + length),
                        _mm256_sub_pd(even, odd));
                }
                for (; i < length; ++i) {
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
        const __m256d inverse_size = _mm256_set1_pd(1.0 / double(size));
        int i = 0;
        for (; i + 1 < size; i += 2) {
            const __m256d value = _mm256_loadu_pd(
                reinterpret_cast<const double*>(values + i));
            _mm256_storeu_pd(reinterpret_cast<double*>(values + i),
                             _mm256_mul_pd(value, inverse_size));
        }
        for (; i < size; ++i) {
            values[i].real /= size;
            values[i].imaginary /= size;
        }
    }
#endif

    static void fft(FftComplex* values, int size) {
        assert(size > 0 && (size & (size - 1)) == 0);
#ifdef M1UNE_BIGINT_HAS_X86_SIMD
        fft_simd(values, size);
        return;
#endif
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

    static void inverse_fft(FftComplex* values, int size) {
        assert(size > 0 && (size & (size - 1)) == 0);
#ifdef M1UNE_BIGINT_HAS_X86_SIMD
        inverse_fft_simd(values, size);
        return;
#endif
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
        for (int i = 0; i < size; ++i) {
            values[i].real *= inverse_size;
            values[i].imaginary *= inverse_size;
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

    static void inverse_real_fft(FftComplex* values, int size) {
        assert(size >= 2 && (size & (size - 1)) == 0);
        const int half_size = size / 2;
        const std::vector<FftComplex>& roots = fft_roots(size);
        static std::vector<FftComplex> bit_reversed_roots;
        static int cached_size = 0;
        if (cached_size != size) {
            bit_reversed_roots.resize(half_size);
            std::vector<int> reversed(half_size);
            const int shift = std::countr_zero(unsigned(half_size));
            for (int i = 1; i < half_size; ++i) {
                reversed[i] =
                    (reversed[i / 2] >> 1) | ((i & 1) << (shift - 1));
            }
            for (int i = 0; i < half_size; ++i) {
                bit_reversed_roots[i] = roots[half_size + reversed[i]];
            }
            cached_size = size;
        }

        for (int i = 0; i < half_size; ++i) {
            const FftComplex first = values[2 * i];
            const FftComplex second = values[2 * i + 1];
            const FftComplex even = (first + second) * 0.5;
            const FftComplex odd =
                ((first - second) * 0.5) * bit_reversed_roots[i].conjugate();
            values[i] = {even.real - odd.imaginary,
                         even.imaginary + odd.real};
        }
        inverse_fft(values, half_size);
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

    struct ProductFingerprint {
        uint32_t mod31;
        uint32_t mod29;
    };

    template <int bits>
    static uint32_t mersenne_reduce(uint64_t value) {
        constexpr uint64_t MODULUS = (uint64_t(1) << bits) - 1;
        value = (value & MODULUS) + (value >> bits);
        value = (value & MODULUS) + (value >> bits);
        if (value >= MODULUS) value -= MODULUS;
        return uint32_t(value);
    }

    static ProductFingerprint magnitude_fingerprint(const std::vector<int>& value) {
        ProductFingerprint result{0, 0};
        for (int i = int(value.size()) - 1; i >= 0; --i) {
            result.mod31 = mersenne_reduce<31>(uint64_t(result.mod31) * BASE + value[i]);
            result.mod29 = mersenne_reduce<29>(uint64_t(result.mod29) * BASE + value[i]);
        }
        return result;
    }

    static bool product_matches(const std::vector<int>& lhs, const std::vector<int>& rhs,
                                const std::vector<int>& product) {
        const ProductFingerprint lhs_value = magnitude_fingerprint(lhs);
        const ProductFingerprint rhs_value = magnitude_fingerprint(rhs);
        const ProductFingerprint actual = magnitude_fingerprint(product);
        return actual.mod31 ==
                   mersenne_reduce<31>(uint64_t(lhs_value.mod31) * rhs_value.mod31) &&
               actual.mod29 ==
                   mersenne_reduce<29>(uint64_t(lhs_value.mod29) * rhs_value.mod29);
    }

    static std::vector<int> multiply_fft(const std::vector<int>& lhs,
                                         const std::vector<int>& rhs) {
        const int result_size = int(lhs.size() + rhs.size() - 1);
        const int transform_size = int(std::bit_ceil(unsigned(result_size)));
        const unsigned __int128 coefficient_bound =
            static_cast<unsigned __int128>(std::min(lhs.size(), rhs.size())) *
            2 * (FFT_SPLIT - 1) * ((BASE - 1) / FFT_SPLIT);
        if (transform_size > (1 << 20) || coefficient_bound >= (uint64_t(1) << 50)) {
            return multiply_ntt(lhs, rhs);
        }

        std::unique_ptr<FftComplex[]> transformed_lhs(
            new FftComplex[transform_size]);
        for (int i = 0; i < int(lhs.size()); ++i) {
            transformed_lhs[i] = {double(lhs[i] % FFT_SPLIT),
                                  double(lhs[i] / FFT_SPLIT)};
        }
        std::fill(transformed_lhs.get() + lhs.size(),
                  transformed_lhs.get() + transform_size, FftComplex{0, 0});
        fft(transformed_lhs.get(), transform_size);

        const bool squaring = &lhs == &rhs;
        std::unique_ptr<FftComplex[]> transformed_rhs(
            new FftComplex[transform_size]);
        if (!squaring) {
            for (int i = 0; i < int(rhs.size()); ++i) {
                transformed_rhs[i] = {double(rhs[i] % FFT_SPLIT),
                                      double(rhs[i] / FFT_SPLIT)};
            }
            std::fill(transformed_rhs.get() + rhs.size(),
                      transformed_rhs.get() + transform_size, FftComplex{0, 0});
            fft(transformed_rhs.get(), transform_size);
        }

        static std::vector<int> reflected_indices;
        if (int(reflected_indices.size()) < transform_size) {
            const int previous_size = int(reflected_indices.size());
            reflected_indices.resize(transform_size);
            for (int i = std::max(1, previous_size); i < transform_size; ++i) {
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
            transformed_rhs[i] = products.cross;
            transformed_rhs[opposite] = opposite_products.cross;
        }
        inverse_fft(transformed_lhs.get(), transform_size);
        inverse_real_fft(transformed_rhs.get(), transform_size);

        std::vector<int> result;
        result.reserve(result_size + 2);
        unsigned __int128 carry = 0;
        for (int i = 0; i < result_size || carry > 0; ++i) {
            if (i < result_size) {
                const long long low = std::llround(transformed_lhs[i].real);
                const long long high = std::llround(transformed_lhs[i].imaginary);
                const FftComplex packed_cross = transformed_rhs[i / 2];
                const long long cross = std::llround(
                    (i & 1) ? packed_cross.imaginary : packed_cross.real);
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

            const int copied = std::min(value_size, 2 * precision + 1);
            const std::vector<int> leading(value.end() - copied, value.end());

            // The original Newton formula right-aligns `leading` in 2p + 1
            // limbs, then discards the same 2p + 1 low limbs of the product.
            // Cancelling that shift avoids convolving a long zero prefix.
            std::vector<int> correction = multiply_magnitude(square, leading);
            assert(int(correction.size()) >= copied);
            correction.erase(correction.begin(), correction.begin() + copied);

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

        if (dividend.size() > 2 * divisor.size()) {
            const int size_ratio = int(dividend.size() / divisor.size());
            const int block_multiplier = size_ratio >= 16 ? 3 : size_ratio >= 7 ? 2 : 1;
            const int block_size = block_multiplier * int(divisor.size());
            const int block_count =
                (int(dividend.size()) + block_size - 1) / block_size;
            const int normalization = BASE / (divisor.back() + 1);
            const std::vector<int> normalized_divisor =
                multiply_by_limb(divisor, normalization);
            const int degree = block_size + 3;
            const std::vector<int> inverse = reciprocal(normalized_divisor, degree);
            const int discarded = int(divisor.size()) + degree;

            auto divide_block = [&](const std::vector<int>& current) {
                const std::vector<int> normalized_current =
                    multiply_by_limb(current, normalization);
                std::vector<int> quotient_product =
                    multiply_magnitude(normalized_current, inverse);
                std::vector<int> partial_quotient;
                if (int(quotient_product.size()) > discarded) {
                    partial_quotient.assign(quotient_product.begin() + discarded,
                                            quotient_product.end());
                }

                std::vector<int> product =
                    multiply_magnitude(normalized_divisor, partial_quotient);
                while (magnitude_less(normalized_current, product)) {
                    partial_quotient =
                        subtract_magnitude(partial_quotient, std::vector<int>(1, 1));
                    product = subtract_magnitude(product, normalized_divisor);
                }
                std::vector<int> partial_remainder =
                    subtract_magnitude(normalized_current, product);
                while (magnitude_less_equal(normalized_divisor, partial_remainder)) {
                    partial_quotient =
                        add_magnitude(partial_quotient, std::vector<int>(1, 1));
                    partial_remainder =
                        subtract_magnitude(partial_remainder, normalized_divisor);
                }
                trim_magnitude(partial_quotient);
                trim_magnitude(partial_remainder);
                std::pair<std::vector<int>, std::vector<int>> denormalized =
                    divide_by_limb(partial_remainder, normalization);
                assert(denormalized.second.empty());
                return std::make_pair(std::move(partial_quotient),
                                      std::move(denormalized.first));
            };

            std::vector<int> quotient(dividend.size());
            std::vector<int> remainder;
            for (int block = block_count - 1; block >= 0; --block) {
                const int begin = block * block_size;
                const int end = std::min(begin + block_size, int(dividend.size()));
                std::vector<int> current(dividend.begin() + begin,
                                         dividend.begin() + end);
                current.insert(current.end(), remainder.begin(), remainder.end());
                trim_magnitude(current);

                std::pair<std::vector<int>, std::vector<int>> partial =
                    divide_block(current);
                assert(int(partial.first.size()) <= end - begin);
                std::copy(partial.first.begin(), partial.first.end(),
                          quotient.begin() + begin);
                remainder = std::move(partial.second);
            }
            trim_magnitude(quotient);
            trim_magnitude(remainder);
            return std::make_pair(std::move(quotient), std::move(remainder));
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

#ifdef M1UNE_BIGINT_HAS_X86_SIMD
#undef M1UNE_BIGINT_HAS_X86_SIMD
#endif

#endif  // M1UNE_UTILITIES_BIGINT_HPP
