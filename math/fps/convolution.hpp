#ifndef M1UNE_FPS_CONVOLUTION_HPP
#define M1UNE_FPS_CONVOLUTION_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <new>
#include <utility>
#include <vector>

#if defined(__GNUC__) && !defined(__clang__) && (defined(__x86_64__) || defined(__i386__))
#include <immintrin.h>
#define M1UNE_FPS_HAS_X86_SIMD 1
#pragma GCC push_options
#pragma GCC target("avx2,bmi")
#include "internal/ntt998_fast.hpp"
#pragma GCC pop_options
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

template <class Mint>
__attribute__((target("avx2,bmi"), hot))
std::vector<Mint> convolution_998244353_simd(const std::vector<Mint>& a,
                                             const std::vector<Mint>& b) {
    const int result_size = int(a.size() + b.size() - 1);
    int n = 1;
    while (n < result_size) n <<= 1;
    auto* transformed_a = static_cast<uint32_t*>(
        ::operator new[](sizeof(uint32_t) * n, std::align_val_t(32)));
    auto* transformed_b = static_cast<uint32_t*>(
        ::operator new[](sizeof(uint32_t) * n, std::align_val_t(32)));
    std::memset(transformed_a, 0, sizeof(uint32_t) * n);
    std::memset(transformed_b, 0, sizeof(uint32_t) * n);
    for (int i = 0; i < int(a.size()); i++) transformed_a[i] = a[i].val();
    for (int i = 0; i < int(b.size()); i++) transformed_b[i] = b[i].val();

    static const fast998::NTT transform(998244353);
    transform.convolve_cyclic(two_adic_order(uint32_t(n)), transformed_a, transformed_b);

    std::vector<Mint> result(result_size);
    for (int j = 0; j < result_size; j++) result[j] = Mint::raw(transformed_a[j]);
    ::operator delete[](transformed_a, std::align_val_t(32));
    ::operator delete[](transformed_b, std::align_val_t(32));
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
