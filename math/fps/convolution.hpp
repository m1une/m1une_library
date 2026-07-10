#ifndef M1UNE_FPS_CONVOLUTION_HPP
#define M1UNE_FPS_CONVOLUTION_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

#if defined(__GNUC__) && !defined(__clang__) && (defined(__x86_64__) || defined(__i386__))
#include <immintrin.h>
#define M1UNE_FPS_HAS_X86_SIMD 1
#endif

#include "../modint.hpp"

namespace m1une {
namespace fps {

namespace internal {

constexpr uint32_t primitive_root_constexpr(uint32_t mod) {
    if (mod == 2) return 1;
    if (mod == 167772161) return 3;
    if (mod == 469762049) return 3;
    if (mod == 754974721) return 11;
    if (mod == 998244353) return 3;
    if (mod == 1224736769) return 3;

    uint32_t divisors[32] = {};
    int count = 0;
    uint32_t x = mod - 1;
    for (uint32_t p = 2; uint64_t(p) * p <= x; p++) {
        if (x % p != 0) continue;
        divisors[count++] = p;
        while (x % p == 0) x /= p;
    }
    if (x > 1) divisors[count++] = x;

    for (uint32_t g = 2;; g++) {
        bool ok = true;
        for (int i = 0; i < count; i++) {
            uint64_t value = 1;
            uint64_t base = g;
            uint32_t exponent = (mod - 1) / divisors[i];
            while (exponent > 0) {
                if (exponent & 1) value = value * base % mod;
                base = base * base % mod;
                exponent >>= 1;
            }
            if (value == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}

constexpr int two_adic_order(uint32_t x) {
    int result = 0;
    while ((x & 1) == 0) {
        x >>= 1;
        result++;
    }
    return result;
}

template <class Mint>
struct NttRoots {
    static constexpr int max_base = two_adic_order(Mint::mod() - 1);
    std::array<Mint, max_base + 1> root;
    std::array<Mint, max_base + 1> inverse_root;
    std::array<Mint, max_base> rate;
    std::array<Mint, max_base> inverse_rate;
    std::array<Mint, max_base> rate_radix4;
    std::array<Mint, max_base> inverse_rate_radix4;

    NttRoots() {
        constexpr uint32_t primitive_root = primitive_root_constexpr(Mint::mod());
        for (int level = 1; level <= max_base; level++) {
            root[level] = Mint(primitive_root).pow((Mint::mod() - 1) >> level);
            inverse_root[level] = root[level].inv();
        }
        Mint product = 1;
        Mint inverse_product = 1;
        for (int i = 0; i + 1 < max_base; i++) {
            rate[i] = root[i + 2] * product;
            inverse_rate[i] = inverse_root[i + 2] * inverse_product;
            product *= inverse_root[i + 2];
            inverse_product *= root[i + 2];
        }
        product = 1;
        inverse_product = 1;
        for (int i = 0; i + 2 < max_base; i++) {
            rate_radix4[i] = root[i + 3] * product;
            inverse_rate_radix4[i] = inverse_root[i + 3] * inverse_product;
            product *= inverse_root[i + 3];
            inverse_product *= root[i + 3];
        }
    }
};

template <class Mint>
const NttRoots<Mint>& ntt_roots() {
    static const NttRoots<Mint> roots;
    return roots;
}

template <class Mint>
void ntt(std::vector<Mint>& a, bool inverse, bool normalize = true) {
    const int n = int(a.size());
    assert(n > 0 && (n & (n - 1)) == 0);
    assert((Mint::mod() - 1) % uint32_t(n) == 0);

    const auto& roots = ntt_roots<Mint>();
    const int height = two_adic_order(uint32_t(n));
    if (!inverse) {
        int phase = 0;
        while (phase < height) {
            if (height - phase == 1) {
                const int width = 1 << (height - phase - 1);
                Mint twiddle = 1;
                for (int block = 0; block < (1 << phase); block++) {
                    const int offset = block << (height - phase);
                    for (int i = 0; i < width; i++) {
                        const Mint left = a[offset + i];
                        const Mint right = a[offset + i + width] * twiddle;
                        a[offset + i] = left + right;
                        a[offset + i + width] = left - right;
                    }
                    if (block + 1 != (1 << phase))
                        twiddle *= roots.rate[__builtin_ctz(~uint32_t(block))];
                }
                phase++;
                continue;
            }

            const int width = 1 << (height - phase - 2);
            Mint twiddle = 1;
            const Mint imaginary = roots.root[2];
            for (int block = 0; block < (1 << phase); block++) {
                const Mint twiddle2 = twiddle * twiddle;
                const Mint twiddle3 = twiddle2 * twiddle;
                const int offset = block << (height - phase);
                for (int i = 0; i < width; i++) {
                    const uint64_t mod2 = uint64_t(Mint::mod()) * Mint::mod();
                    const uint64_t a0 = a[offset + i].val();
                    const uint64_t a1 = uint64_t(a[offset + i + width].val()) * twiddle.val();
                    const uint64_t a2 =
                        uint64_t(a[offset + i + 2 * width].val()) * twiddle2.val();
                    const uint64_t a3 =
                        uint64_t(a[offset + i + 3 * width].val()) * twiddle3.val();
                    const uint64_t a1na3i =
                        uint64_t(Mint(a1 + mod2 - a3).val()) * imaginary.val();
                    const uint64_t negative_a2 = mod2 - a2;
                    a[offset + i] = Mint(a0 + a2 + a1 + a3);
                    a[offset + i + width] = Mint(a0 + a2 + 2 * mod2 - a1 - a3);
                    a[offset + i + 2 * width] = Mint(a0 + negative_a2 + a1na3i);
                    a[offset + i + 3 * width] = Mint(a0 + negative_a2 + mod2 - a1na3i);
                }
                if (block + 1 != (1 << phase))
                    twiddle *= roots.rate_radix4[__builtin_ctz(~uint32_t(block))];
            }
            phase += 2;
        }
    } else {
        int phase = height;
        while (phase > 0) {
            if (phase == 1) {
                const int width = 1 << (height - phase);
                Mint twiddle = 1;
                for (int block = 0; block < (1 << (phase - 1)); block++) {
                    const int offset = block << (height - phase + 1);
                    for (int i = 0; i < width; i++) {
                        const Mint left = a[offset + i];
                        const Mint right = a[offset + i + width];
                        a[offset + i] = left + right;
                        a[offset + i + width] = (left - right) * twiddle;
                    }
                    if (block + 1 != (1 << (phase - 1)))
                        twiddle *= roots.inverse_rate[__builtin_ctz(~uint32_t(block))];
                }
                phase--;
                continue;
            }

            const int width = 1 << (height - phase);
            Mint twiddle = 1;
            const Mint inverse_imaginary = roots.inverse_root[2];
            for (int block = 0; block < (1 << (phase - 2)); block++) {
                const Mint twiddle2 = twiddle * twiddle;
                const Mint twiddle3 = twiddle2 * twiddle;
                const int offset = block << (height - phase + 2);
                for (int i = 0; i < width; i++) {
                    const uint64_t a0 = a[offset + i].val();
                    const uint64_t a1 = a[offset + i + width].val();
                    const uint64_t a2 = a[offset + i + 2 * width].val();
                    const uint64_t a3 = a[offset + i + 3 * width].val();
                    const uint64_t a2na3i =
                        uint64_t(Mint((Mint::mod() + a2 - a3) * inverse_imaginary.val()).val());
                    a[offset + i] = Mint(a0 + a1 + a2 + a3);
                    a[offset + i + width] =
                        Mint((a0 + Mint::mod() - a1 + a2na3i) * twiddle.val());
                    a[offset + i + 2 * width] = Mint(
                        (a0 + a1 + 2ULL * Mint::mod() - a2 - a3) * twiddle2.val());
                    a[offset + i + 3 * width] = Mint(
                        (a0 + Mint::mod() - a1 + Mint::mod() - a2na3i) * twiddle3.val());
                }
                if (block + 1 != (1 << (phase - 2)))
                    twiddle *= roots.inverse_rate_radix4[__builtin_ctz(~uint32_t(block))];
            }
            phase -= 2;
        }
        if (normalize) {
            const Mint inverse_n = Mint(n).inv();
            for (Mint& value : a) value *= inverse_n;
        }
    }
}

#ifdef M1UNE_FPS_HAS_X86_SIMD

#pragma GCC push_options
#pragma GCC target("avx2,bmi")

struct Montgomery998Simd {
    static constexpr uint32_t mod = 998244353;
    static constexpr uint32_t mod2 = 2 * mod;
    uint32_t negative_inverse;
    uint32_t r;
    uint32_t r2;
    __m256i modulus;
    __m256i inverse;

    Montgomery998Simd()
        : negative_inverse(1),
          r(uint32_t((uint64_t(1) << 32) % mod)),
          r2(uint32_t(uint64_t(r) * r % mod)) {
        for (int i = 0; i < 5; i++) negative_inverse *= 2 + negative_inverse * mod;
        modulus = _mm256_set1_epi32(int(mod));
        inverse = _mm256_set1_epi32(int(negative_inverse));
    }

    uint32_t shrink(uint32_t value) const {
        return std::min(value, value - mod);
    }

    uint32_t reduce(uint64_t value) const {
        return uint32_t((value + uint64_t(uint32_t(value) * negative_inverse) * mod) >> 32);
    }

    uint32_t multiply(uint32_t lhs, uint32_t rhs) const {
        return shrink(reduce(uint64_t(lhs) * rhs));
    }

    uint32_t encode(uint32_t value) const {
        return multiply(value, r2);
    }

    __m256i shrink(__m256i value) const {
        return _mm256_min_epu32(value, _mm256_sub_epi32(value, modulus));
    }

    __m256i multiply(__m256i lhs, __m256i rhs) const {
        const __m256i lhs_odd = _mm256_bsrli_epi128(lhs, 4);
        const __m256i rhs_odd = _mm256_bsrli_epi128(rhs, 4);
        __m256i even = _mm256_mul_epu32(lhs, rhs);
        __m256i odd = _mm256_mul_epu32(lhs_odd, rhs_odd);
        __m256i even_correction = _mm256_mul_epu32(even, inverse);
        __m256i odd_correction = _mm256_mul_epu32(odd, inverse);
        even_correction = _mm256_mul_epu32(even_correction, modulus);
        odd_correction = _mm256_mul_epu32(odd_correction, modulus);
        even = _mm256_add_epi64(even, even_correction);
        odd = _mm256_add_epi64(odd, odd_correction);
        return shrink(_mm256_or_si256(_mm256_bsrli_epi128(even, 4), odd));
    }

    __m256i add(__m256i lhs, __m256i rhs) const {
        return shrink(_mm256_add_epi32(lhs, rhs));
    }

    __m256i subtract(__m256i lhs, __m256i rhs) const {
        const __m256i difference = _mm256_sub_epi32(lhs, rhs);
        return _mm256_min_epu32(difference, _mm256_add_epi32(difference, modulus));
    }
};

template <class Mint>
__attribute__((target("avx2,bmi"), hot))
void ntt_998244353_simd(uint32_t* data, int n, bool inverse, bool normalize = true) {
    static const Montgomery998Simd montgomery;
    const auto& roots = ntt_roots<Mint>();
    const int height = two_adic_order(uint32_t(n));

    if (!inverse) {
        for (int phase = 1; phase <= height; phase++) {
            const int blocks = 1 << (phase - 1);
            const int width = 1 << (height - phase);
            uint32_t twiddle = montgomery.r;
            for (int block = 0; block < blocks; block++) {
                const int offset = block << (height - phase + 1);
                const __m256i vector_twiddle = _mm256_set1_epi32(int(twiddle));
                int i = 0;
                for (; i + 8 <= width; i += 8) {
                    const __m256i lhs = _mm256_loadu_si256(
                        reinterpret_cast<const __m256i*>(data + offset + i));
                    const __m256i rhs = _mm256_loadu_si256(
                        reinterpret_cast<const __m256i*>(data + offset + width + i));
                    const __m256i weighted_rhs = montgomery.multiply(rhs, vector_twiddle);
                    _mm256_storeu_si256(reinterpret_cast<__m256i*>(data + offset + i),
                                       montgomery.add(lhs, weighted_rhs));
                    _mm256_storeu_si256(reinterpret_cast<__m256i*>(data + offset + width + i),
                                       montgomery.subtract(lhs, weighted_rhs));
                }
                for (; i < width; i++) {
                    const uint32_t lhs = data[offset + i];
                    const uint32_t rhs = data[offset + width + i];
                    const uint32_t weighted_rhs = montgomery.multiply(rhs, twiddle);
                    uint32_t sum = lhs + weighted_rhs;
                    if (sum >= Montgomery998Simd::mod) sum -= Montgomery998Simd::mod;
                    uint32_t difference = lhs >= weighted_rhs
                                              ? lhs - weighted_rhs
                                              : lhs + Montgomery998Simd::mod - weighted_rhs;
                    data[offset + i] = sum;
                    data[offset + width + i] = difference;
                }
                if (block + 1 != blocks) {
                    const uint32_t rate = montgomery.encode(
                        roots.rate[__builtin_ctz(~uint32_t(block))].val());
                    twiddle = montgomery.multiply(twiddle, rate);
                }
            }
        }
    } else {
        for (int phase = height; phase >= 1; phase--) {
            const int blocks = 1 << (phase - 1);
            const int width = 1 << (height - phase);
            uint32_t twiddle = montgomery.r;
            for (int block = 0; block < blocks; block++) {
                const int offset = block << (height - phase + 1);
                const __m256i vector_twiddle = _mm256_set1_epi32(int(twiddle));
                int i = 0;
                for (; i + 8 <= width; i += 8) {
                    const __m256i lhs = _mm256_loadu_si256(
                        reinterpret_cast<const __m256i*>(data + offset + i));
                    const __m256i rhs = _mm256_loadu_si256(
                        reinterpret_cast<const __m256i*>(data + offset + width + i));
                    _mm256_storeu_si256(reinterpret_cast<__m256i*>(data + offset + i),
                                       montgomery.add(lhs, rhs));
                    _mm256_storeu_si256(reinterpret_cast<__m256i*>(data + offset + width + i),
                                       montgomery.multiply(montgomery.subtract(lhs, rhs),
                                                           vector_twiddle));
                }
                for (; i < width; i++) {
                    const uint32_t lhs = data[offset + i];
                    const uint32_t rhs = data[offset + width + i];
                    uint32_t sum = lhs + rhs;
                    if (sum >= Montgomery998Simd::mod) sum -= Montgomery998Simd::mod;
                    uint32_t difference = lhs >= rhs ? lhs - rhs : lhs + Montgomery998Simd::mod - rhs;
                    data[offset + i] = sum;
                    data[offset + width + i] = montgomery.multiply(difference, twiddle);
                }
                if (block + 1 != blocks) {
                    const uint32_t rate = montgomery.encode(
                        roots.inverse_rate[__builtin_ctz(~uint32_t(block))].val());
                    twiddle = montgomery.multiply(twiddle, rate);
                }
            }
        }
        if (normalize) {
            const uint32_t scale = montgomery.encode(Mint(n).inv().val());
            const __m256i vector_scale = _mm256_set1_epi32(int(scale));
            int i = 0;
            for (; i + 8 <= n; i += 8) {
                __m256i values =
                    _mm256_loadu_si256(reinterpret_cast<const __m256i*>(data + i));
                _mm256_storeu_si256(reinterpret_cast<__m256i*>(data + i),
                                   montgomery.multiply(values, vector_scale));
            }
            for (; i < n; i++) data[i] = montgomery.multiply(data[i], scale);
        }
    }
}

template <class Mint>
__attribute__((target("avx2,bmi"), hot))
std::vector<Mint> convolution_998244353_simd(const std::vector<Mint>& a,
                                             const std::vector<Mint>& b) {
    const int result_size = int(a.size() + b.size() - 1);
    int n = 1;
    while (n < result_size) n <<= 1;
    std::vector<uint32_t> transformed_a(n);
    std::vector<uint32_t> transformed_b(n);
    for (int i = 0; i < int(a.size()); i++) transformed_a[i] = a[i].val();
    for (int i = 0; i < int(b.size()); i++) transformed_b[i] = b[i].val();
    ntt_998244353_simd<Mint>(transformed_a.data(), n, false);
    ntt_998244353_simd<Mint>(transformed_b.data(), n, false);

    static const Montgomery998Simd montgomery;
    // A normal-by-normal Montgomery product is off by R^-1.  Scaling the
    // inverse transform by n^-1 R compensates for it without another pass.
    const uint32_t inverse_n_montgomery = montgomery.encode(Mint(n).inv().val());
    const uint32_t inverse_n_r2 = montgomery.multiply(inverse_n_montgomery, montgomery.r2);
    const __m256i vector_scale = _mm256_set1_epi32(int(inverse_n_r2));
    int i = 0;
    for (; i + 8 <= n; i += 8) {
        const __m256i lhs =
            _mm256_loadu_si256(reinterpret_cast<const __m256i*>(transformed_a.data() + i));
        const __m256i rhs =
            _mm256_loadu_si256(reinterpret_cast<const __m256i*>(transformed_b.data() + i));
        __m256i product = montgomery.multiply(lhs, rhs);
        product = montgomery.multiply(product, vector_scale);
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(transformed_a.data() + i), product);
    }
    for (; i < n; i++) {
        uint32_t product = montgomery.multiply(transformed_a[i], transformed_b[i]);
        transformed_a[i] = montgomery.multiply(product, inverse_n_r2);
    }
    ntt_998244353_simd<Mint>(transformed_a.data(), n, true, false);

    std::vector<Mint> result(result_size);
    for (int j = 0; j < result_size; j++) result[j] = Mint::raw(transformed_a[j]);
    return result;
}

#pragma GCC pop_options

#endif

}  // namespace internal

template <class Mint>
std::vector<Mint> convolution_naive(const std::vector<Mint>& a, const std::vector<Mint>& b) {
    if (a.empty() || b.empty()) return {};
    std::vector<Mint> result(a.size() + b.size() - 1);
    if (a.size() < b.size()) {
        for (int i = 0; i < int(a.size()); i++) {
            for (int j = 0; j < int(b.size()); j++) result[i + j] += a[i] * b[j];
        }
    } else {
        for (int j = 0; j < int(b.size()); j++) {
            for (int i = 0; i < int(a.size()); i++) result[i + j] += a[i] * b[j];
        }
    }
    return result;
}

template <class Mint>
std::vector<Mint> convolution_ntt(const std::vector<Mint>& a, const std::vector<Mint>& b) {
    const int result_size = int(a.size() + b.size() - 1);
    int n = 1;
    while (n < result_size) n <<= 1;
    assert((Mint::mod() - 1) % uint32_t(n) == 0);

#ifdef M1UNE_FPS_HAS_X86_SIMD
    if constexpr (Mint::mod() == 998244353) {
        if (n >= 64 && __builtin_cpu_supports("avx2"))
            return internal::convolution_998244353_simd(a, b);
    }
#endif

    // Allocate the padded buffers directly.  Constructing from the inputs and
    // then resizing used to allocate and copy both large operands twice.
    std::vector<Mint> fa(n);
    std::vector<Mint> fb(n);
    std::copy(a.begin(), a.end(), fa.begin());
    std::copy(b.begin(), b.end(), fb.begin());
    internal::ntt(fa, false);
    internal::ntt(fb, false);
    const Mint inverse_n = Mint(n).inv();
    for (int i = 0; i < n; i++) fa[i] *= fb[i] * inverse_n;
    internal::ntt(fa, true, false);
    fa.resize(result_size);
    return fa;
}

template <class Mint>
std::vector<Mint> convolution(const std::vector<Mint>& a, const std::vector<Mint>& b) {
    if (a.empty() || b.empty()) return {};
    if (std::min(a.size(), b.size()) <= 32) return convolution_naive(a, b);

    const int result_size = int(a.size() + b.size() - 1);
    int n = 1;
    while (n < result_size) n <<= 1;
    if ((Mint::mod() - 1) % uint32_t(n) == 0) return convolution_ntt(a, b);

    using Mint1 = math::ModInt<167772161>;
    using Mint2 = math::ModInt<469762049>;
    using Mint3 = math::ModInt<754974721>;
    assert(n <= (1 << 24));

    [[maybe_unused]] const unsigned __int128 coefficient_bound =
        static_cast<unsigned __int128>(std::min(a.size(), b.size())) * (Mint::mod() - 1) *
        (Mint::mod() - 1);
    [[maybe_unused]] const unsigned __int128 crt_modulus =
        static_cast<unsigned __int128>(Mint1::mod()) * Mint2::mod() * Mint3::mod();
    assert(coefficient_bound < crt_modulus);

    auto converted_convolution = [&]<class OtherMint>() {
        std::vector<OtherMint> converted_a(a.size());
        std::vector<OtherMint> converted_b(b.size());
        for (int i = 0; i < int(a.size()); i++) converted_a[i] = OtherMint(a[i].val());
        for (int i = 0; i < int(b.size()); i++) converted_b[i] = OtherMint(b[i].val());
        return convolution_ntt(converted_a, converted_b);
    };
    std::vector<Mint1> c1 = converted_convolution.template operator()<Mint1>();
    std::vector<Mint2> c2 = converted_convolution.template operator()<Mint2>();
    std::vector<Mint3> c3 = converted_convolution.template operator()<Mint3>();
    static const uint64_t inverse_mod1_mod2 = Mint2(Mint1::mod()).inv().val();
    static const uint64_t mod1_mod3 = Mint1::mod() % Mint3::mod();
    static const uint64_t mod1_mod2_mod3 =
        mod1_mod3 * (Mint2::mod() % Mint3::mod()) % Mint3::mod();
    static const uint64_t inverse_mod1_mod2_mod3 = Mint3(uint32_t(mod1_mod2_mod3)).inv().val();

    const uint64_t target_mod = Mint::mod();
    const uint64_t mod1_target = Mint1::mod() % target_mod;
    const uint64_t mod1_mod2_target = mod1_target * (Mint2::mod() % target_mod) % target_mod;
    std::vector<Mint> result(result_size);
    for (int i = 0; i < result_size; i++) {
        const uint64_t r1 = c1[i].val();
        const uint64_t r2 = c2[i].val();
        const uint64_t r3 = c3[i].val();
        const uint64_t first =
            (r2 + Mint2::mod() - r1 % Mint2::mod()) % Mint2::mod() * inverse_mod1_mod2 %
            Mint2::mod();
        const uint64_t combined_mod3 =
            (r1 % Mint3::mod() + mod1_mod3 * (first % Mint3::mod())) % Mint3::mod();
        const uint64_t second =
            (r3 + Mint3::mod() - combined_mod3) % Mint3::mod() * inverse_mod1_mod2_mod3 %
            Mint3::mod();

        uint64_t value = r1 % target_mod;
        value = (value + mod1_target * (first % target_mod)) % target_mod;
        value = (value + mod1_mod2_target * (second % target_mod)) % target_mod;
        result[i] = Mint::raw(uint32_t(value));
    }
    return result;
}

}  // namespace fps
}  // namespace m1une

#ifdef M1UNE_FPS_HAS_X86_SIMD
#undef M1UNE_FPS_HAS_X86_SIMD
#endif

#endif  // M1UNE_FPS_CONVOLUTION_HPP
