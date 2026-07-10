---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/counting.hpp
    title: Graph Counting
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  - icon: ':heavy_check_mark:'
    path: math/bernoulli.hpp
    title: Bernoulli Numbers and Power Sums
  - icon: ':heavy_check_mark:'
    path: math/combinatorial_sequences.hpp
    title: Combinatorial Sequences
  - icon: ':heavy_check_mark:'
    path: math/fps/all.hpp
    title: Formal Power Series All
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution_ll.hpp
    title: Long Long Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':heavy_check_mark:'
    path: math/fps/half_gcd.hpp
    title: Polynomial Half-GCD
  - icon: ':heavy_check_mark:'
    path: math/fps/lagrange_inversion.hpp
    title: Lagrange Inversion Formula
  - icon: ':heavy_check_mark:'
    path: math/fps/linear_recurrence.hpp
    title: Linear Recurrence and Bostan-Mori
  - icon: ':heavy_check_mark:'
    path: math/fps/multipoint_evaluation.hpp
    title: Multipoint Evaluation and Interpolation
  - icon: ':heavy_check_mark:'
    path: math/partition_function.hpp
    title: Partition Function
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_counting.test.cpp
    title: verify/graph/graph_counting.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/bell_number.test.cpp
    title: verify/math/bell_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/bernoulli_number.test.cpp
    title: verify/math/bernoulli_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/bernoulli_utilities.test.cpp
    title: verify/math/bernoulli_utilities.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/convolution_ll.test.cpp
    title: verify/math/fps/convolution_ll.test.cpp
  - icon: ':x:'
    path: verify/math/fps/convolution_mod.test.cpp
    title: verify/math/fps/convolution_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/exp_of_formal_power_series.test.cpp
    title: verify/math/fps/exp_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/fps_algorithms.test.cpp
    title: verify/math/fps/fps_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/half_gcd.test.cpp
    title: verify/math/fps/half_gcd.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/inv_of_formal_power_series.test.cpp
    title: verify/math/fps/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
    title: verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/lagrange_inversion.test.cpp
    title: verify/math/fps/lagrange_inversion.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/multipoint_evaluation.test.cpp
    title: verify/math/fps/multipoint_evaluation.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/polynomial_interpolation.test.cpp
    title: verify/math/fps/polynomial_interpolation.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/polynomial_taylor_shift.test.cpp
    title: verify/math/fps/polynomial_taylor_shift.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/pow_of_formal_power_series.test.cpp
    title: verify/math/fps/pow_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/partition_function.test.cpp
    title: verify/math/partition_function.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/stirling_number_of_the_second_kind.test.cpp
    title: verify/math/stirling_number_of_the_second_kind.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/fps/internal/ntt998_fast.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <cstdint>\n#include <cstring>\n\
    #include <vector>\n\n#include <immintrin.h>\n\nnamespace m1une {\nnamespace fps\
    \ {\nnamespace internal {\nnamespace fast998 {\n\n// Fixed-modulus AVX2 kernel.\
    \  It evaluates only the upper radix-4 NTT layers\n// and multiplies the remaining\
    \ degree-8/16 residues directly modulo x^k-w.\n\nusing u32 = uint32_t;\nusing\
    \ u64 = uint64_t;\n\nstruct Montgomery {\n    u32 mod;    // mod\n    u32 mod2;\
    \   // 2 * mod\n    u32 n_inv;  // n_inv * mod == -1 (mod 2^32)\n    u32 r;  \
    \    // 2^32 % mod\n    u32 r2;     // (2^32)^2 % mod\n\n    Montgomery() = default;\n\
    \    Montgomery(u32 mod) : mod(mod) {\n        assert(mod % 2 == 1);\n       \
    \ assert(mod < (1 << 30));\n        mod2 = 2 * mod;\n        n_inv = 1;\n    \
    \    for (int i = 0; i < 5; i++) {\n            n_inv *= 2 + n_inv * mod;\n  \
    \      }\n        r = (u64(1) << 32) % mod;\n        r2 = u64(r) * r % mod;\n\
    \    }\n\n    u32 shrink(u32 val) const {\n        return std::min(val, val -\
    \ mod);\n    }\n    u32 shrink2(u32 val) const {\n        return std::min(val,\
    \ val - mod2);\n    }\n\n    template <bool strict = true>\n    u32 reduce(u64\
    \ val) const {\n        u32 res = (val + u32(val) * n_inv * u64(mod)) >> 32;\n\
    \        if constexpr (strict)\n            res = shrink(res);\n        return\
    \ res;\n    }\n\n    template <bool strict = true>\n    u32 mul(u32 a, u32 b)\
    \ const {\n        return reduce<strict>(u64(a) * b);\n    }\n\n    template <bool\
    \ input_in_space = false, bool output_in_space = false>\n    u32 power(u32 b,\
    \ u32 e) const {\n        if (!input_in_space)\n            b = mul<false>(b,\
    \ r2);\n        u32 r = output_in_space ? this->r : 1;\n        for (; e > 0;\
    \ e >>= 1) {\n            if (e & 1)\n                r = mul<false>(r, b);\n\
    \            b = mul<false>(b, b);\n        }\n        return shrink(r);\n   \
    \ }\n};\n\nusing i256 = __m256i;\nusing u32x8 = u32 __attribute__((vector_size(32)));\n\
    using u64x4 = u64 __attribute__((vector_size(32)));\n\nu32x8 load_u32x8(const\
    \ u32* ptr) {\n    return (u32x8)_mm256_load_si256((const i256*)ptr);\n}\nvoid\
    \ store_u32x8(u32* ptr, u32x8 vec) {\n    _mm256_store_si256((i256*)ptr, (i256)vec);\n\
    }\n\nstruct Montgomery_simd {\n    u32x8 mod;    // mod\n    u32x8 mod2;   //\
    \ 2 * mod\n    u32x8 n_inv;  // n_inv * mod == -1 (mod 2^32)\n    u32x8 r;   \
    \   // 2^32 % mod\n    u32x8 r2;     // (2^32)^2 % mod\n\n    Montgomery_simd()\
    \ = default;\n    Montgomery_simd(u32 mod) {\n        Montgomery mt(mod);\n  \
    \      this->mod = (u32x8)_mm256_set1_epi32(mt.mod);\n        this->mod2 = (u32x8)_mm256_set1_epi32(mt.mod2);\n\
    \        this->n_inv = (u32x8)_mm256_set1_epi32(mt.n_inv);\n        this->r =\
    \ (u32x8)_mm256_set1_epi32(mt.r);\n        this->r2 = (u32x8)_mm256_set1_epi32(mt.r2);\n\
    \    }\n\n    u32x8 shrink(u32x8 vec) const {\n        return (u32x8)_mm256_min_epu32((i256)vec,\
    \ _mm256_sub_epi32((i256)vec, (i256)mod));\n    }\n    u32x8 shrink2(u32x8 vec)\
    \ const {\n        return (u32x8)_mm256_min_epu32((i256)vec, _mm256_sub_epi32((i256)vec,\
    \ (i256)mod2));\n    }\n    u32x8 shrink_n(u32x8 vec) const {\n        return\
    \ (u32x8)_mm256_min_epu32((i256)vec, _mm256_add_epi32((i256)vec, (i256)mod));\n\
    \    }\n    u32x8 shrink2_n(u32x8 vec) const {\n        return (u32x8)_mm256_min_epu32((i256)vec,\
    \ _mm256_add_epi32((i256)vec, (i256)mod2));\n    }\n\n    template <bool strict\
    \ = true>\n    u32x8 reduce(u64x4 x0246, u64x4 x1357) const {\n        u64x4 x0246_ninv\
    \ = (u64x4)_mm256_mul_epu32((i256)x0246, (i256)n_inv);\n        u64x4 x1357_ninv\
    \ = (u64x4)_mm256_mul_epu32((i256)x1357, (i256)n_inv);\n        u64x4 x0246_res\
    \ = (u64x4)_mm256_add_epi64((i256)x0246, _mm256_mul_epu32((i256)x0246_ninv, (i256)mod));\n\
    \        u64x4 x1357_res = (u64x4)_mm256_add_epi64((i256)x1357, _mm256_mul_epu32((i256)x1357_ninv,\
    \ (i256)mod));\n        u32x8 res = (u32x8)_mm256_or_si256(_mm256_bsrli_epi128((i256)x0246_res,\
    \ 4), (i256)x1357_res);\n        if (strict)\n            res = shrink(res);\n\
    \        return res;\n    }\n\n    template <bool strict = true, bool b_use_only_even\
    \ = false>\n    u32x8 mul_u32x8(u32x8 a, u32x8 b) const {\n        u32x8 a_sh\
    \ = (u32x8)_mm256_bsrli_epi128((i256)a, 4);\n        u32x8 b_sh = b_use_only_even\
    \ ? b : (u32x8)_mm256_bsrli_epi128((i256)b, 4);\n        u64x4 x0246 = (u64x4)_mm256_mul_epu32((i256)a,\
    \ (i256)b);\n        u64x4 x1357 = (u64x4)_mm256_mul_epu32((i256)a_sh, (i256)b_sh);\n\
    \        return reduce<strict>(x0246, x1357);\n    }\n\n    template <bool strict\
    \ = true>\n    u64x4 mul_u64x4(u64x4 a, u64x4 b) const {\n        u64x4 pr = (u64x4)_mm256_mul_epu32((i256)a,\
    \ (i256)b);\n        u64x4 pr2 = (u64x4)_mm256_mul_epu32(_mm256_mul_epu32((i256)pr,\
    \ (i256)n_inv), (i256)mod);\n        u64x4 res = (u64x4)_mm256_bsrli_epi128(_mm256_add_epi64((i256)pr,\
    \ (i256)pr2), 4);\n        if (strict)\n            res = (u64x4)shrink((u32x8)res);\n\
    \        return res;\n    }\n};\n\nclass NTT {\n   public:\n    u32 mod, pr_root;\n\
    \n   private:\n    static constexpr int LG = 32;  // more than enough for u32\n\
    \n    Montgomery mt;\n    Montgomery_simd mts;\n\n    u32 w[4], wr[4];\n    u32\
    \ wd[LG], wrd[LG];\n\n    u64x4 wt_init, wrt_init;\n    u64x4 wd_x4[LG], wrd_x4[LG];\n\
    \n    u64x4 wl_init;\n    u64x4 wld_x4[LG];\n\n    static u32 find_pr_root(u32\
    \ mod, const Montgomery& mt) {\n        std::vector<u32> factors;\n        u32\
    \ n = mod - 1;\n        for (u32 i = 2; u64(i) * i <= n; i++) {\n            if\
    \ (n % i == 0) {\n                factors.push_back(i);\n                do {\n\
    \                    n /= i;\n                } while (n % i == 0);\n        \
    \    }\n        }\n        if (n > 1) {\n            factors.push_back(n);\n \
    \       }\n        for (u32 i = 2; i < mod; i++) {\n            if (std::all_of(factors.begin(),\
    \ factors.end(), [&](u32 f) { return mt.power<false, false>(i, (mod - 1) / f)\
    \ != 1; })) {\n                return i;\n            }\n        }\n        assert(false\
    \ && \"primitive root not found\");\n        return 0;\n    }\n\n   public:\n\
    \    NTT() = default;\n    NTT(u32 mod) : mod(mod), mt(mod), mts(mod) {\n    \
    \    const Montgomery mt = this->mt;\n        const Montgomery_simd mts = this->mts;\n\
    \n        pr_root = find_pr_root(mod, mt);\n\n        int lg = __builtin_ctz(mod\
    \ - 1);\n        assert(lg <= LG);\n\n        memset(w, 0, sizeof(w));\n     \
    \   memset(wr, 0, sizeof(wr));\n        memset(wd_x4, 0, sizeof(wd_x4));\n   \
    \     memset(wrd_x4, 0, sizeof(wrd_x4));\n        memset(wld_x4, 0, sizeof(wld_x4));\n\
    \n        std::vector<u32> vec(lg + 1), vecr(lg + 1);\n        vec[lg] = mt.power<false,\
    \ true>(pr_root, (mod - 1) >> lg);\n        vecr[lg] = mt.power<true, true>(vec[lg],\
    \ mod - 2);\n        for (int i = lg - 1; i >= 0; i--) {\n            vec[i] =\
    \ mt.mul<true>(vec[i + 1], vec[i + 1]);\n            vecr[i] = mt.mul<true>(vecr[i\
    \ + 1], vecr[i + 1]);\n        }\n\n        w[0] = wr[0] = mt.r;\n        if (lg\
    \ >= 2) {\n            w[1] = vec[2], wr[1] = vecr[2];\n            if (lg >=\
    \ 3) {\n                w[2] = vec[3], wr[2] = vecr[3];\n                w[3]\
    \ = mt.mul<true>(w[1], w[2]);\n                wr[3] = mt.mul<true>(wr[1], wr[2]);\n\
    \            }\n        }\n        wt_init = (u64x4)_mm256_setr_epi64x(w[0], w[0],\
    \ w[0], w[1]);\n        wrt_init = (u64x4)_mm256_setr_epi64x(wr[0], wr[0], wr[0],\
    \ wr[1]);\n\n        wl_init = (u64x4)_mm256_setr_epi64x(w[0], w[1], w[2], w[3]);\n\
    \n        u32 prf = mt.r, prf_r = mt.r;\n        for (int i = 0; i < lg - 2; i++)\
    \ {\n            u32 f = mt.mul<true>(prf, vec[i + 3]), fr = mt.mul<true>(prf_r,\
    \ vecr[i + 3]);\n            prf = mt.mul<true>(prf, vecr[i + 3]), prf_r = mt.mul<true>(prf_r,\
    \ vec[i + 3]);\n            u32 f2 = mt.mul<true>(f, f), f2r = mt.mul<true>(fr,\
    \ fr);\n\n            wd_x4[i] = (u64x4)_mm256_setr_epi64x(f2, f, f2, f);\n  \
    \          wrd_x4[i] = (u64x4)_mm256_setr_epi64x(f2r, fr, f2r, fr);\n        }\n\
    \n        prf = mt.r;\n        for (int i = 0; i < lg - 3; i++) {\n          \
    \  u32 f = mt.mul<true>(prf, vec[i + 4]);\n            prf = mt.mul<true>(prf,\
    \ vecr[i + 4]);\n            wld_x4[i] = (u64x4)_mm256_set1_epi64x(f);\n     \
    \   }\n    }\n\n   private:\n    static constexpr int L0 = 3;\n    int get_low_lg(int\
    \ lg) const {\n        return lg % 2 == L0 % 2 ? L0 : L0 + 1;\n    }\n\n    //\
    \    public:\n    //     bool lg_available(int lg) {\n    //         return L0\
    \ <= lg && lg <= __builtin_ctz(mod - 1) + get_low_lg(lg);\n    //     }\n\n  \
    \ private:\n    template <bool transposed, bool trivial = false>\n    static void\
    \ butterfly_x2(u32* ptr_a, u32* ptr_b, u32x8 w, const Montgomery_simd& mts) {\n\
    \        u32x8 a = load_u32x8(ptr_a), b = load_u32x8(ptr_b);\n        u32x8 a2,\
    \ b2;\n        if (!transposed) {\n            a = mts.shrink2(a), b = trivial\
    \ ? mts.shrink2(b) : mts.mul_u32x8<false, true>(b, w);\n            a2 = a + b,\
    \ b2 = a + mts.mod2 - b;\n        } else {\n            a2 = mts.shrink2(a + b),\
    \ b2 = trivial ? mts.shrink2_n(a - b) : mts.mul_u32x8<false, true>(a + mts.mod2\
    \ - b, w);\n        }\n        store_u32x8(ptr_a, a2), store_u32x8(ptr_b, b2);\n\
    \    }\n\n    template <bool transposed, bool trivial = false>\n    static void\
    \ butterfly_x4(u32* ptr_a, u32* ptr_b, u32* ptr_c, u32* ptr_d, u32x8 w1, u32x8\
    \ w2, u32x8 w3, const Montgomery_simd& mts) {\n        u32x8 a = load_u32x8(ptr_a),\
    \ b = load_u32x8(ptr_b), c = load_u32x8(ptr_c), d = load_u32x8(ptr_d);\n     \
    \   if (!transposed) {\n            butterfly_x2<false, trivial>((u32*)&a, (u32*)&c,\
    \ w1, mts);\n            butterfly_x2<false, trivial>((u32*)&b, (u32*)&d, w1,\
    \ mts);\n            butterfly_x2<false, trivial>((u32*)&a, (u32*)&b, w2, mts);\n\
    \            butterfly_x2<false, false>((u32*)&c, (u32*)&d, w3, mts);\n      \
    \  } else {\n            butterfly_x2<true, trivial>((u32*)&a, (u32*)&b, w2, mts);\n\
    \            butterfly_x2<true, false>((u32*)&c, (u32*)&d, w3, mts);\n       \
    \     butterfly_x2<true, trivial>((u32*)&a, (u32*)&c, w1, mts);\n            butterfly_x2<true,\
    \ trivial>((u32*)&b, (u32*)&d, w1, mts);\n        }\n        store_u32x8(ptr_a,\
    \ a), store_u32x8(ptr_b, b), store_u32x8(ptr_c, c), store_u32x8(ptr_d, d);\n \
    \   }\n\n    template <bool inverse, bool trivial = false>\n    void transform_aux(int\
    \ k, int i, u32* data, u64x4& wi, const Montgomery_simd& mts) const {\n      \
    \  u32x8 w1 = (u32x8)_mm256_shuffle_epi32((i256)wi, 0b00'00'00'00);\n        u32x8\
    \ w2 = (u32x8)_mm256_permute4x64_epi64((i256)wi, 0b01'01'01'01);  // only even\
    \ indices will be used\n        u32x8 w3 = (u32x8)_mm256_permute4x64_epi64((i256)wi,\
    \ 0b11'11'11'11);  // only even indices will be used\n        for (int j = 0;\
    \ j < (1 << k); j += 8) {\n            butterfly_x4<inverse, trivial>(data + i\
    \ + (1 << k) * 0 + j, data + i + (1 << k) * 1 + j,\n                         \
    \                  data + i + (1 << k) * 2 + j, data + i + (1 << k) * 3 + j,\n\
    \                                           w1, w2, w3, mts);\n        }\n   \
    \     wi = mts.mul_u64x4<true>(\n            wi, (inverse ? wrd_x4 : wd_x4)[__builtin_ctz(~i\
    \ >> (k + 2))]);\n    }\n\n   public:\n    // input in [0, 4 * mod)\n    // output\
    \ in [0, 4 * mod)\n    // data must be 32-byte aligned\n    void transform_forward(int\
    \ lg, u32* data) const {\n        const Montgomery_simd mts = this->mts;\n   \
    \     const int L = get_low_lg(lg);\n\n        // for (int k = lg - 2; k >= L;\
    \ k -= 2) {\n        //     u64x4 wi = wt_init;\n        //     transform_aux<false,\
    \ true>(k, 0, data, wi, mts);\n        //     for (int i = (1 << k + 2); i < (1\
    \ << lg); i += (1 << k + 2)) {\n        //         transform_aux<false>(k, i,\
    \ data, wi, mts);\n        //     }\n        // }\n\n        if (L < lg) {\n \
    \           const int lc = (lg - L) / 2;\n            u64x4 wi_data[LG / 2];\n\
    \            std::fill(wi_data, wi_data + lc, wt_init);\n\n            for (int\
    \ k = lg - 2; k >= L; k -= 2) {\n                transform_aux<false, true>(k,\
    \ 0, data, wi_data[(k - L) >> 1], mts);\n            }\n            for (int i\
    \ = 1; i < (1 << (lc * 2 - 2)); i++) {\n                int s = __builtin_ctz(i)\
    \ >> 1;\n                for (int k = s; k >= 0; k--) {\n                    transform_aux<false>(2\
    \ * k + L, i * (1 << (L + 2)), data,\n                                       \
    \  wi_data[k], mts);\n                }\n            }\n        }\n    }\n\n \
    \   // input in [0, 2 * mod)\n    // output in [0, mod)\n    // data must be 32-byte\
    \ aligned\n    template <bool mul_by_sc = false>\n    void transform_inverse(int\
    \ lg, u32* data, /* as normal number */ u32 sc = u32()) const {\n        const\
    \ Montgomery_simd mts = this->mts;\n        const int L = get_low_lg(lg);\n\n\
    \        // for (int k = L; k + 2 <= lg; k += 2) {\n        //     u64x4 wi =\
    \ wrt_init;\n        //     transform_aux<true, true>(k, 0, data, wi, mts);\n\
    \        //     for (int i = (1 << k + 2); i < (1 << lg); i += (1 << k + 2)) {\n\
    \        //         transform_aux<true>(k, i, data, wi, mts);\n        //    \
    \ }\n        // }\n\n        if (L < lg) {\n            const int lc = (lg - L)\
    \ / 2;\n            u64x4 wi_data[LG / 2];\n            std::fill(wi_data, wi_data\
    \ + lc, wrt_init);\n\n            for (int i = 0; i < (1 << (lc * 2 - 2)); i++)\
    \ {\n                int s = __builtin_ctz(~i) >> 1;\n                if (i +\
    \ 1 == (1 << 2 * s)) {\n                    s--;\n                }\n        \
    \        for (int k = 0; k <= s; k++) {\n                    transform_aux<true>(2\
    \ * k + L,\n                                        (i + 1 - (1 << (2 * k))) *\
    \ (1 << (L + 2)),\n                                        data, wi_data[k], mts);\n\
    \                }\n                if (i + 1 == (1 << (2 * (s + 1)))) {\n   \
    \                 s++;\n                    transform_aux<true, true>(\n     \
    \                   2 * s + L, (i + 1 - (1 << (2 * s))) * (1 << (L + 2)), data,\n\
    \                        wi_data[s], mts);\n                }\n            }\n\
    \        }\n\n        const Montgomery mt = this->mt;\n        u32 f = mt.power<false,\
    \ true>((mod + 1) >> 1, lg - L);\n        if constexpr (mul_by_sc)\n         \
    \   f = mt.mul<true>(f, mt.mul<false>(mt.r2, sc));\n        u32x8 f_x8 = (u32x8)_mm256_set1_epi32(f);\n\
    \        for (int i = 0; i < (1 << lg); i += 8) {\n            store_u32x8(data\
    \ + i, mts.mul_u32x8<true, true>(load_u32x8(data + i), f_x8));\n        }\n  \
    \  }\n\n   private:\n    // input in [0, 4 * mod)\n    // output in [0, 2 * mod)\n\
    \    // multiplies mod (x^2^L - w)\n    template <int L, int K, bool remove_montgomery_reduction_factor\
    \ = true>\n    /* !!! O3 is crucial here !!! */ __attribute__((optimize(\"O3\"\
    ))) static void aux_mul_mod_x2L(const u32* a, const u32* b, u32* c, const std::array<u32x8,\
    \ K>& ar_w, const Montgomery_simd& mts) {\n        static_assert(L >= 3);\n  \
    \      // static_assert(L == L0 || L == L0 + 1);\n\n        constexpr int n =\
    \ 1 << L;\n        alignas(64) u32 aux_a[K][n];\n        alignas(64) u64 aux_b[K][n\
    \ * 2];\n        for (int k = 0; k < K; k++) {\n            for (int i = 0; i\
    \ < n; i += 8) {\n                u32x8 ai = load_u32x8(a + n * k + i);\n    \
    \            if constexpr (remove_montgomery_reduction_factor) {\n           \
    \         ai = mts.mul_u32x8<true, true>(ai, mts.r2);\n                } else\
    \ {\n                    ai = mts.shrink(mts.shrink2(ai));\n                }\n\
    \                store_u32x8(aux_a[k] + i, ai);\n\n                u32x8 bi =\
    \ load_u32x8(b + n * k + i);\n                u32x8 bi_0 = mts.shrink(mts.shrink2(bi));\n\
    \                u32x8 bi_w = mts.mul_u32x8<true, true>(bi, ar_w[k]);\n\n    \
    \            store_u32x8((u32*)(aux_b[k] + i + 0), (u32x8)_mm256_permutevar8x32_epi32((i256)bi_w,\
    \ _mm256_setr_epi64x(0, 1, 2, 3)));\n                store_u32x8((u32*)(aux_b[k]\
    \ + i + 4), (u32x8)_mm256_permutevar8x32_epi32((i256)bi_w, _mm256_setr_epi64x(4,\
    \ 5, 6, 7)));\n                store_u32x8((u32*)(aux_b[k] + n + i + 0), (u32x8)_mm256_permutevar8x32_epi32((i256)bi_0,\
    \ _mm256_setr_epi64x(0, 1, 2, 3)));\n                store_u32x8((u32*)(aux_b[k]\
    \ + n + i + 4), (u32x8)_mm256_permutevar8x32_epi32((i256)bi_0, _mm256_setr_epi64x(4,\
    \ 5, 6, 7)));\n            }\n        }\n\n        u64x4 aux_ans[K][n / 4];\n\
    \        memset(aux_ans, 0, sizeof(aux_ans));\n        for (int i = 0; i < n;\
    \ i++) {\n            for (int k = 0; k < K; k++) {\n                u64x4 ai\
    \ = (u64x4)_mm256_set1_epi32(aux_a[k][i]);\n                for (int j = 0; j\
    \ < n; j += 4) {\n                    u64x4 bi = (u64x4)_mm256_loadu_si256((i256*)(aux_b[k]\
    \ + n - i + j));\n                    aux_ans[k][j / 4] += /* 64-bit addition\
    \ */ (u64x4)_mm256_mul_epu32((i256)ai, (i256)bi);\n                }\n       \
    \     }\n            if (i >= 8 && (i & 7) == 7) {\n                for (int k\
    \ = 0; k < K; k++) {\n                    for (int j = 0; j < n; j += 4) {\n \
    \                       aux_ans[k][j / 4] = (u64x4)mts.shrink2((u32x8)aux_ans[k][j\
    \ / 4]);\n                    }\n                }\n            }\n        }\n\
    \n        for (int k = 0; k < K; k++) {\n            for (int i = 0; i < n; i\
    \ += 8) {\n                u64x4 c0 = aux_ans[k][i / 4], c1 = aux_ans[k][i / 4\
    \ + 1];\n                u32x8 res = (u32x8)_mm256_permutevar8x32_epi32((i256)mts.reduce<false>(c0,\
    \ c1), _mm256_setr_epi32(0, 2, 4, 6, 1, 3, 5, 7));\n                store_u32x8(c\
    \ + k * n + i, mts.shrink2(res));\n            }\n        }\n    }\n\n    template\
    \ <int L, bool remove_montgomery_reduction_factor = true>\n    void aux_mul_mod_full(int\
    \ lg, const u32* a, const u32* b, u32* c) const {\n        constexpr int sz =\
    \ 1 << L;\n        const Montgomery_simd mts = this->mts;\n        int cnt = 1\
    \ << (lg - L);\n        if (cnt == 1) {\n            aux_mul_mod_x2L<L, 1, remove_montgomery_reduction_factor>(a,\
    \ b, c, {mts.r}, mts);\n            return;\n        }\n        if (cnt <= 8)\
    \ {\n            for (int i = 0; i < cnt; i += 2) {\n                u32x8 wi\
    \ = (u32x8)_mm256_set1_epi32(w[i / 2]);\n                aux_mul_mod_x2L<L, 2,\
    \ remove_montgomery_reduction_factor>(a + i * sz, b + i * sz, c + i * sz, {wi,\
    \ (mts.mod - wi)}, mts);\n            }\n            return;\n        }\n    \
    \    u64x4 wi = wl_init;\n        for (int i = 0; i < cnt; i += 8) {\n       \
    \     u32x8 w_ar[4] = {\n                (u32x8)_mm256_permute4x64_epi64((i256)wi,\
    \ 0b00'00'00'00),\n                (u32x8)_mm256_permute4x64_epi64((i256)wi, 0b01'01'01'01),\n\
    \                (u32x8)_mm256_permute4x64_epi64((i256)wi, 0b10'10'10'10),\n \
    \               (u32x8)_mm256_permute4x64_epi64((i256)wi, 0b11'11'11'11),\n  \
    \          };\n            if constexpr (L == L0) {\n                for (int\
    \ j = 0; j < 8; j += 4) {\n                    aux_mul_mod_x2L<L, 4, remove_montgomery_reduction_factor>(a\
    \ + (i + j) * sz, b + (i + j) * sz, c + (i + j) * sz,\n                      \
    \                                                        {w_ar[j / 2], mts.mod\
    \ - w_ar[j / 2], w_ar[j / 2 + 1], mts.mod - w_ar[j / 2 + 1]}, mts);\n        \
    \        }\n            } else {\n                for (int j = 0; j < 8; j +=\
    \ 2) {\n                    aux_mul_mod_x2L<L, 2, remove_montgomery_reduction_factor>(a\
    \ + (i + j) * sz, b + (i + j) * sz, c + (i + j) * sz,\n                      \
    \                                                        {w_ar[j / 2], mts.mod\
    \ - w_ar[j / 2]}, mts);\n                }\n            }\n            wi = mts.mul_u64x4<true>(wi,\
    \ wld_x4[__builtin_ctz(~i >> 3)]);\n        }\n    }\n\n   public:\n    // input\
    \ in [0, 4 * mod)\n    // output in [0, 2 * mod)\n    template <bool remove_montgomery_reduction_factor\
    \ = true>\n    void aux_dot_mod(int lg, const u32* a, const u32* b, u32* c) const\
    \ {\n        int L = get_low_lg(lg);\n        if (L == L0) {\n            aux_mul_mod_full<L0,\
    \ remove_montgomery_reduction_factor>(lg, a, b, c);\n        } else {\n      \
    \      aux_mul_mod_full<L0 + 1, remove_montgomery_reduction_factor>(lg, a, b,\
    \ c);\n        }\n    }\n\n    // lg must be greater than or equal to 3\n    //\
    \ a, b must be 32-byte aligned\n    void convolve_cyclic(int lg, u32* a, u32*\
    \ b) const {\n        transform_forward(lg, a);\n        transform_forward(lg,\
    \ b);\n        aux_dot_mod<false>(lg, a, b, a);\n        transform_inverse<true>(lg,\
    \ a, mt.r);\n    }\n};\n\n}  // namespace fast998\n}  // namespace internal\n\
    }  // namespace fps\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_FPS_INTERNAL_NTT998_FAST_HPP\n#define M1UNE_FPS_INTERNAL_NTT998_FAST_HPP\
    \ 1\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cstdint>\n\
    #include <cstring>\n#include <vector>\n\n#include <immintrin.h>\n\nnamespace m1une\
    \ {\nnamespace fps {\nnamespace internal {\nnamespace fast998 {\n\n// Fixed-modulus\
    \ AVX2 kernel.  It evaluates only the upper radix-4 NTT layers\n// and multiplies\
    \ the remaining degree-8/16 residues directly modulo x^k-w.\n\nusing u32 = uint32_t;\n\
    using u64 = uint64_t;\n\nstruct Montgomery {\n    u32 mod;    // mod\n    u32\
    \ mod2;   // 2 * mod\n    u32 n_inv;  // n_inv * mod == -1 (mod 2^32)\n    u32\
    \ r;      // 2^32 % mod\n    u32 r2;     // (2^32)^2 % mod\n\n    Montgomery()\
    \ = default;\n    Montgomery(u32 mod) : mod(mod) {\n        assert(mod % 2 ==\
    \ 1);\n        assert(mod < (1 << 30));\n        mod2 = 2 * mod;\n        n_inv\
    \ = 1;\n        for (int i = 0; i < 5; i++) {\n            n_inv *= 2 + n_inv\
    \ * mod;\n        }\n        r = (u64(1) << 32) % mod;\n        r2 = u64(r) *\
    \ r % mod;\n    }\n\n    u32 shrink(u32 val) const {\n        return std::min(val,\
    \ val - mod);\n    }\n    u32 shrink2(u32 val) const {\n        return std::min(val,\
    \ val - mod2);\n    }\n\n    template <bool strict = true>\n    u32 reduce(u64\
    \ val) const {\n        u32 res = (val + u32(val) * n_inv * u64(mod)) >> 32;\n\
    \        if constexpr (strict)\n            res = shrink(res);\n        return\
    \ res;\n    }\n\n    template <bool strict = true>\n    u32 mul(u32 a, u32 b)\
    \ const {\n        return reduce<strict>(u64(a) * b);\n    }\n\n    template <bool\
    \ input_in_space = false, bool output_in_space = false>\n    u32 power(u32 b,\
    \ u32 e) const {\n        if (!input_in_space)\n            b = mul<false>(b,\
    \ r2);\n        u32 r = output_in_space ? this->r : 1;\n        for (; e > 0;\
    \ e >>= 1) {\n            if (e & 1)\n                r = mul<false>(r, b);\n\
    \            b = mul<false>(b, b);\n        }\n        return shrink(r);\n   \
    \ }\n};\n\nusing i256 = __m256i;\nusing u32x8 = u32 __attribute__((vector_size(32)));\n\
    using u64x4 = u64 __attribute__((vector_size(32)));\n\nu32x8 load_u32x8(const\
    \ u32* ptr) {\n    return (u32x8)_mm256_load_si256((const i256*)ptr);\n}\nvoid\
    \ store_u32x8(u32* ptr, u32x8 vec) {\n    _mm256_store_si256((i256*)ptr, (i256)vec);\n\
    }\n\nstruct Montgomery_simd {\n    u32x8 mod;    // mod\n    u32x8 mod2;   //\
    \ 2 * mod\n    u32x8 n_inv;  // n_inv * mod == -1 (mod 2^32)\n    u32x8 r;   \
    \   // 2^32 % mod\n    u32x8 r2;     // (2^32)^2 % mod\n\n    Montgomery_simd()\
    \ = default;\n    Montgomery_simd(u32 mod) {\n        Montgomery mt(mod);\n  \
    \      this->mod = (u32x8)_mm256_set1_epi32(mt.mod);\n        this->mod2 = (u32x8)_mm256_set1_epi32(mt.mod2);\n\
    \        this->n_inv = (u32x8)_mm256_set1_epi32(mt.n_inv);\n        this->r =\
    \ (u32x8)_mm256_set1_epi32(mt.r);\n        this->r2 = (u32x8)_mm256_set1_epi32(mt.r2);\n\
    \    }\n\n    u32x8 shrink(u32x8 vec) const {\n        return (u32x8)_mm256_min_epu32((i256)vec,\
    \ _mm256_sub_epi32((i256)vec, (i256)mod));\n    }\n    u32x8 shrink2(u32x8 vec)\
    \ const {\n        return (u32x8)_mm256_min_epu32((i256)vec, _mm256_sub_epi32((i256)vec,\
    \ (i256)mod2));\n    }\n    u32x8 shrink_n(u32x8 vec) const {\n        return\
    \ (u32x8)_mm256_min_epu32((i256)vec, _mm256_add_epi32((i256)vec, (i256)mod));\n\
    \    }\n    u32x8 shrink2_n(u32x8 vec) const {\n        return (u32x8)_mm256_min_epu32((i256)vec,\
    \ _mm256_add_epi32((i256)vec, (i256)mod2));\n    }\n\n    template <bool strict\
    \ = true>\n    u32x8 reduce(u64x4 x0246, u64x4 x1357) const {\n        u64x4 x0246_ninv\
    \ = (u64x4)_mm256_mul_epu32((i256)x0246, (i256)n_inv);\n        u64x4 x1357_ninv\
    \ = (u64x4)_mm256_mul_epu32((i256)x1357, (i256)n_inv);\n        u64x4 x0246_res\
    \ = (u64x4)_mm256_add_epi64((i256)x0246, _mm256_mul_epu32((i256)x0246_ninv, (i256)mod));\n\
    \        u64x4 x1357_res = (u64x4)_mm256_add_epi64((i256)x1357, _mm256_mul_epu32((i256)x1357_ninv,\
    \ (i256)mod));\n        u32x8 res = (u32x8)_mm256_or_si256(_mm256_bsrli_epi128((i256)x0246_res,\
    \ 4), (i256)x1357_res);\n        if (strict)\n            res = shrink(res);\n\
    \        return res;\n    }\n\n    template <bool strict = true, bool b_use_only_even\
    \ = false>\n    u32x8 mul_u32x8(u32x8 a, u32x8 b) const {\n        u32x8 a_sh\
    \ = (u32x8)_mm256_bsrli_epi128((i256)a, 4);\n        u32x8 b_sh = b_use_only_even\
    \ ? b : (u32x8)_mm256_bsrli_epi128((i256)b, 4);\n        u64x4 x0246 = (u64x4)_mm256_mul_epu32((i256)a,\
    \ (i256)b);\n        u64x4 x1357 = (u64x4)_mm256_mul_epu32((i256)a_sh, (i256)b_sh);\n\
    \        return reduce<strict>(x0246, x1357);\n    }\n\n    template <bool strict\
    \ = true>\n    u64x4 mul_u64x4(u64x4 a, u64x4 b) const {\n        u64x4 pr = (u64x4)_mm256_mul_epu32((i256)a,\
    \ (i256)b);\n        u64x4 pr2 = (u64x4)_mm256_mul_epu32(_mm256_mul_epu32((i256)pr,\
    \ (i256)n_inv), (i256)mod);\n        u64x4 res = (u64x4)_mm256_bsrli_epi128(_mm256_add_epi64((i256)pr,\
    \ (i256)pr2), 4);\n        if (strict)\n            res = (u64x4)shrink((u32x8)res);\n\
    \        return res;\n    }\n};\n\nclass NTT {\n   public:\n    u32 mod, pr_root;\n\
    \n   private:\n    static constexpr int LG = 32;  // more than enough for u32\n\
    \n    Montgomery mt;\n    Montgomery_simd mts;\n\n    u32 w[4], wr[4];\n    u32\
    \ wd[LG], wrd[LG];\n\n    u64x4 wt_init, wrt_init;\n    u64x4 wd_x4[LG], wrd_x4[LG];\n\
    \n    u64x4 wl_init;\n    u64x4 wld_x4[LG];\n\n    static u32 find_pr_root(u32\
    \ mod, const Montgomery& mt) {\n        std::vector<u32> factors;\n        u32\
    \ n = mod - 1;\n        for (u32 i = 2; u64(i) * i <= n; i++) {\n            if\
    \ (n % i == 0) {\n                factors.push_back(i);\n                do {\n\
    \                    n /= i;\n                } while (n % i == 0);\n        \
    \    }\n        }\n        if (n > 1) {\n            factors.push_back(n);\n \
    \       }\n        for (u32 i = 2; i < mod; i++) {\n            if (std::all_of(factors.begin(),\
    \ factors.end(), [&](u32 f) { return mt.power<false, false>(i, (mod - 1) / f)\
    \ != 1; })) {\n                return i;\n            }\n        }\n        assert(false\
    \ && \"primitive root not found\");\n        return 0;\n    }\n\n   public:\n\
    \    NTT() = default;\n    NTT(u32 mod) : mod(mod), mt(mod), mts(mod) {\n    \
    \    const Montgomery mt = this->mt;\n        const Montgomery_simd mts = this->mts;\n\
    \n        pr_root = find_pr_root(mod, mt);\n\n        int lg = __builtin_ctz(mod\
    \ - 1);\n        assert(lg <= LG);\n\n        memset(w, 0, sizeof(w));\n     \
    \   memset(wr, 0, sizeof(wr));\n        memset(wd_x4, 0, sizeof(wd_x4));\n   \
    \     memset(wrd_x4, 0, sizeof(wrd_x4));\n        memset(wld_x4, 0, sizeof(wld_x4));\n\
    \n        std::vector<u32> vec(lg + 1), vecr(lg + 1);\n        vec[lg] = mt.power<false,\
    \ true>(pr_root, (mod - 1) >> lg);\n        vecr[lg] = mt.power<true, true>(vec[lg],\
    \ mod - 2);\n        for (int i = lg - 1; i >= 0; i--) {\n            vec[i] =\
    \ mt.mul<true>(vec[i + 1], vec[i + 1]);\n            vecr[i] = mt.mul<true>(vecr[i\
    \ + 1], vecr[i + 1]);\n        }\n\n        w[0] = wr[0] = mt.r;\n        if (lg\
    \ >= 2) {\n            w[1] = vec[2], wr[1] = vecr[2];\n            if (lg >=\
    \ 3) {\n                w[2] = vec[3], wr[2] = vecr[3];\n                w[3]\
    \ = mt.mul<true>(w[1], w[2]);\n                wr[3] = mt.mul<true>(wr[1], wr[2]);\n\
    \            }\n        }\n        wt_init = (u64x4)_mm256_setr_epi64x(w[0], w[0],\
    \ w[0], w[1]);\n        wrt_init = (u64x4)_mm256_setr_epi64x(wr[0], wr[0], wr[0],\
    \ wr[1]);\n\n        wl_init = (u64x4)_mm256_setr_epi64x(w[0], w[1], w[2], w[3]);\n\
    \n        u32 prf = mt.r, prf_r = mt.r;\n        for (int i = 0; i < lg - 2; i++)\
    \ {\n            u32 f = mt.mul<true>(prf, vec[i + 3]), fr = mt.mul<true>(prf_r,\
    \ vecr[i + 3]);\n            prf = mt.mul<true>(prf, vecr[i + 3]), prf_r = mt.mul<true>(prf_r,\
    \ vec[i + 3]);\n            u32 f2 = mt.mul<true>(f, f), f2r = mt.mul<true>(fr,\
    \ fr);\n\n            wd_x4[i] = (u64x4)_mm256_setr_epi64x(f2, f, f2, f);\n  \
    \          wrd_x4[i] = (u64x4)_mm256_setr_epi64x(f2r, fr, f2r, fr);\n        }\n\
    \n        prf = mt.r;\n        for (int i = 0; i < lg - 3; i++) {\n          \
    \  u32 f = mt.mul<true>(prf, vec[i + 4]);\n            prf = mt.mul<true>(prf,\
    \ vecr[i + 4]);\n            wld_x4[i] = (u64x4)_mm256_set1_epi64x(f);\n     \
    \   }\n    }\n\n   private:\n    static constexpr int L0 = 3;\n    int get_low_lg(int\
    \ lg) const {\n        return lg % 2 == L0 % 2 ? L0 : L0 + 1;\n    }\n\n    //\
    \    public:\n    //     bool lg_available(int lg) {\n    //         return L0\
    \ <= lg && lg <= __builtin_ctz(mod - 1) + get_low_lg(lg);\n    //     }\n\n  \
    \ private:\n    template <bool transposed, bool trivial = false>\n    static void\
    \ butterfly_x2(u32* ptr_a, u32* ptr_b, u32x8 w, const Montgomery_simd& mts) {\n\
    \        u32x8 a = load_u32x8(ptr_a), b = load_u32x8(ptr_b);\n        u32x8 a2,\
    \ b2;\n        if (!transposed) {\n            a = mts.shrink2(a), b = trivial\
    \ ? mts.shrink2(b) : mts.mul_u32x8<false, true>(b, w);\n            a2 = a + b,\
    \ b2 = a + mts.mod2 - b;\n        } else {\n            a2 = mts.shrink2(a + b),\
    \ b2 = trivial ? mts.shrink2_n(a - b) : mts.mul_u32x8<false, true>(a + mts.mod2\
    \ - b, w);\n        }\n        store_u32x8(ptr_a, a2), store_u32x8(ptr_b, b2);\n\
    \    }\n\n    template <bool transposed, bool trivial = false>\n    static void\
    \ butterfly_x4(u32* ptr_a, u32* ptr_b, u32* ptr_c, u32* ptr_d, u32x8 w1, u32x8\
    \ w2, u32x8 w3, const Montgomery_simd& mts) {\n        u32x8 a = load_u32x8(ptr_a),\
    \ b = load_u32x8(ptr_b), c = load_u32x8(ptr_c), d = load_u32x8(ptr_d);\n     \
    \   if (!transposed) {\n            butterfly_x2<false, trivial>((u32*)&a, (u32*)&c,\
    \ w1, mts);\n            butterfly_x2<false, trivial>((u32*)&b, (u32*)&d, w1,\
    \ mts);\n            butterfly_x2<false, trivial>((u32*)&a, (u32*)&b, w2, mts);\n\
    \            butterfly_x2<false, false>((u32*)&c, (u32*)&d, w3, mts);\n      \
    \  } else {\n            butterfly_x2<true, trivial>((u32*)&a, (u32*)&b, w2, mts);\n\
    \            butterfly_x2<true, false>((u32*)&c, (u32*)&d, w3, mts);\n       \
    \     butterfly_x2<true, trivial>((u32*)&a, (u32*)&c, w1, mts);\n            butterfly_x2<true,\
    \ trivial>((u32*)&b, (u32*)&d, w1, mts);\n        }\n        store_u32x8(ptr_a,\
    \ a), store_u32x8(ptr_b, b), store_u32x8(ptr_c, c), store_u32x8(ptr_d, d);\n \
    \   }\n\n    template <bool inverse, bool trivial = false>\n    void transform_aux(int\
    \ k, int i, u32* data, u64x4& wi, const Montgomery_simd& mts) const {\n      \
    \  u32x8 w1 = (u32x8)_mm256_shuffle_epi32((i256)wi, 0b00'00'00'00);\n        u32x8\
    \ w2 = (u32x8)_mm256_permute4x64_epi64((i256)wi, 0b01'01'01'01);  // only even\
    \ indices will be used\n        u32x8 w3 = (u32x8)_mm256_permute4x64_epi64((i256)wi,\
    \ 0b11'11'11'11);  // only even indices will be used\n        for (int j = 0;\
    \ j < (1 << k); j += 8) {\n            butterfly_x4<inverse, trivial>(data + i\
    \ + (1 << k) * 0 + j, data + i + (1 << k) * 1 + j,\n                         \
    \                  data + i + (1 << k) * 2 + j, data + i + (1 << k) * 3 + j,\n\
    \                                           w1, w2, w3, mts);\n        }\n   \
    \     wi = mts.mul_u64x4<true>(\n            wi, (inverse ? wrd_x4 : wd_x4)[__builtin_ctz(~i\
    \ >> (k + 2))]);\n    }\n\n   public:\n    // input in [0, 4 * mod)\n    // output\
    \ in [0, 4 * mod)\n    // data must be 32-byte aligned\n    void transform_forward(int\
    \ lg, u32* data) const {\n        const Montgomery_simd mts = this->mts;\n   \
    \     const int L = get_low_lg(lg);\n\n        // for (int k = lg - 2; k >= L;\
    \ k -= 2) {\n        //     u64x4 wi = wt_init;\n        //     transform_aux<false,\
    \ true>(k, 0, data, wi, mts);\n        //     for (int i = (1 << k + 2); i < (1\
    \ << lg); i += (1 << k + 2)) {\n        //         transform_aux<false>(k, i,\
    \ data, wi, mts);\n        //     }\n        // }\n\n        if (L < lg) {\n \
    \           const int lc = (lg - L) / 2;\n            u64x4 wi_data[LG / 2];\n\
    \            std::fill(wi_data, wi_data + lc, wt_init);\n\n            for (int\
    \ k = lg - 2; k >= L; k -= 2) {\n                transform_aux<false, true>(k,\
    \ 0, data, wi_data[(k - L) >> 1], mts);\n            }\n            for (int i\
    \ = 1; i < (1 << (lc * 2 - 2)); i++) {\n                int s = __builtin_ctz(i)\
    \ >> 1;\n                for (int k = s; k >= 0; k--) {\n                    transform_aux<false>(2\
    \ * k + L, i * (1 << (L + 2)), data,\n                                       \
    \  wi_data[k], mts);\n                }\n            }\n        }\n    }\n\n \
    \   // input in [0, 2 * mod)\n    // output in [0, mod)\n    // data must be 32-byte\
    \ aligned\n    template <bool mul_by_sc = false>\n    void transform_inverse(int\
    \ lg, u32* data, /* as normal number */ u32 sc = u32()) const {\n        const\
    \ Montgomery_simd mts = this->mts;\n        const int L = get_low_lg(lg);\n\n\
    \        // for (int k = L; k + 2 <= lg; k += 2) {\n        //     u64x4 wi =\
    \ wrt_init;\n        //     transform_aux<true, true>(k, 0, data, wi, mts);\n\
    \        //     for (int i = (1 << k + 2); i < (1 << lg); i += (1 << k + 2)) {\n\
    \        //         transform_aux<true>(k, i, data, wi, mts);\n        //    \
    \ }\n        // }\n\n        if (L < lg) {\n            const int lc = (lg - L)\
    \ / 2;\n            u64x4 wi_data[LG / 2];\n            std::fill(wi_data, wi_data\
    \ + lc, wrt_init);\n\n            for (int i = 0; i < (1 << (lc * 2 - 2)); i++)\
    \ {\n                int s = __builtin_ctz(~i) >> 1;\n                if (i +\
    \ 1 == (1 << 2 * s)) {\n                    s--;\n                }\n        \
    \        for (int k = 0; k <= s; k++) {\n                    transform_aux<true>(2\
    \ * k + L,\n                                        (i + 1 - (1 << (2 * k))) *\
    \ (1 << (L + 2)),\n                                        data, wi_data[k], mts);\n\
    \                }\n                if (i + 1 == (1 << (2 * (s + 1)))) {\n   \
    \                 s++;\n                    transform_aux<true, true>(\n     \
    \                   2 * s + L, (i + 1 - (1 << (2 * s))) * (1 << (L + 2)), data,\n\
    \                        wi_data[s], mts);\n                }\n            }\n\
    \        }\n\n        const Montgomery mt = this->mt;\n        u32 f = mt.power<false,\
    \ true>((mod + 1) >> 1, lg - L);\n        if constexpr (mul_by_sc)\n         \
    \   f = mt.mul<true>(f, mt.mul<false>(mt.r2, sc));\n        u32x8 f_x8 = (u32x8)_mm256_set1_epi32(f);\n\
    \        for (int i = 0; i < (1 << lg); i += 8) {\n            store_u32x8(data\
    \ + i, mts.mul_u32x8<true, true>(load_u32x8(data + i), f_x8));\n        }\n  \
    \  }\n\n   private:\n    // input in [0, 4 * mod)\n    // output in [0, 2 * mod)\n\
    \    // multiplies mod (x^2^L - w)\n    template <int L, int K, bool remove_montgomery_reduction_factor\
    \ = true>\n    /* !!! O3 is crucial here !!! */ __attribute__((optimize(\"O3\"\
    ))) static void aux_mul_mod_x2L(const u32* a, const u32* b, u32* c, const std::array<u32x8,\
    \ K>& ar_w, const Montgomery_simd& mts) {\n        static_assert(L >= 3);\n  \
    \      // static_assert(L == L0 || L == L0 + 1);\n\n        constexpr int n =\
    \ 1 << L;\n        alignas(64) u32 aux_a[K][n];\n        alignas(64) u64 aux_b[K][n\
    \ * 2];\n        for (int k = 0; k < K; k++) {\n            for (int i = 0; i\
    \ < n; i += 8) {\n                u32x8 ai = load_u32x8(a + n * k + i);\n    \
    \            if constexpr (remove_montgomery_reduction_factor) {\n           \
    \         ai = mts.mul_u32x8<true, true>(ai, mts.r2);\n                } else\
    \ {\n                    ai = mts.shrink(mts.shrink2(ai));\n                }\n\
    \                store_u32x8(aux_a[k] + i, ai);\n\n                u32x8 bi =\
    \ load_u32x8(b + n * k + i);\n                u32x8 bi_0 = mts.shrink(mts.shrink2(bi));\n\
    \                u32x8 bi_w = mts.mul_u32x8<true, true>(bi, ar_w[k]);\n\n    \
    \            store_u32x8((u32*)(aux_b[k] + i + 0), (u32x8)_mm256_permutevar8x32_epi32((i256)bi_w,\
    \ _mm256_setr_epi64x(0, 1, 2, 3)));\n                store_u32x8((u32*)(aux_b[k]\
    \ + i + 4), (u32x8)_mm256_permutevar8x32_epi32((i256)bi_w, _mm256_setr_epi64x(4,\
    \ 5, 6, 7)));\n                store_u32x8((u32*)(aux_b[k] + n + i + 0), (u32x8)_mm256_permutevar8x32_epi32((i256)bi_0,\
    \ _mm256_setr_epi64x(0, 1, 2, 3)));\n                store_u32x8((u32*)(aux_b[k]\
    \ + n + i + 4), (u32x8)_mm256_permutevar8x32_epi32((i256)bi_0, _mm256_setr_epi64x(4,\
    \ 5, 6, 7)));\n            }\n        }\n\n        u64x4 aux_ans[K][n / 4];\n\
    \        memset(aux_ans, 0, sizeof(aux_ans));\n        for (int i = 0; i < n;\
    \ i++) {\n            for (int k = 0; k < K; k++) {\n                u64x4 ai\
    \ = (u64x4)_mm256_set1_epi32(aux_a[k][i]);\n                for (int j = 0; j\
    \ < n; j += 4) {\n                    u64x4 bi = (u64x4)_mm256_loadu_si256((i256*)(aux_b[k]\
    \ + n - i + j));\n                    aux_ans[k][j / 4] += /* 64-bit addition\
    \ */ (u64x4)_mm256_mul_epu32((i256)ai, (i256)bi);\n                }\n       \
    \     }\n            if (i >= 8 && (i & 7) == 7) {\n                for (int k\
    \ = 0; k < K; k++) {\n                    for (int j = 0; j < n; j += 4) {\n \
    \                       aux_ans[k][j / 4] = (u64x4)mts.shrink2((u32x8)aux_ans[k][j\
    \ / 4]);\n                    }\n                }\n            }\n        }\n\
    \n        for (int k = 0; k < K; k++) {\n            for (int i = 0; i < n; i\
    \ += 8) {\n                u64x4 c0 = aux_ans[k][i / 4], c1 = aux_ans[k][i / 4\
    \ + 1];\n                u32x8 res = (u32x8)_mm256_permutevar8x32_epi32((i256)mts.reduce<false>(c0,\
    \ c1), _mm256_setr_epi32(0, 2, 4, 6, 1, 3, 5, 7));\n                store_u32x8(c\
    \ + k * n + i, mts.shrink2(res));\n            }\n        }\n    }\n\n    template\
    \ <int L, bool remove_montgomery_reduction_factor = true>\n    void aux_mul_mod_full(int\
    \ lg, const u32* a, const u32* b, u32* c) const {\n        constexpr int sz =\
    \ 1 << L;\n        const Montgomery_simd mts = this->mts;\n        int cnt = 1\
    \ << (lg - L);\n        if (cnt == 1) {\n            aux_mul_mod_x2L<L, 1, remove_montgomery_reduction_factor>(a,\
    \ b, c, {mts.r}, mts);\n            return;\n        }\n        if (cnt <= 8)\
    \ {\n            for (int i = 0; i < cnt; i += 2) {\n                u32x8 wi\
    \ = (u32x8)_mm256_set1_epi32(w[i / 2]);\n                aux_mul_mod_x2L<L, 2,\
    \ remove_montgomery_reduction_factor>(a + i * sz, b + i * sz, c + i * sz, {wi,\
    \ (mts.mod - wi)}, mts);\n            }\n            return;\n        }\n    \
    \    u64x4 wi = wl_init;\n        for (int i = 0; i < cnt; i += 8) {\n       \
    \     u32x8 w_ar[4] = {\n                (u32x8)_mm256_permute4x64_epi64((i256)wi,\
    \ 0b00'00'00'00),\n                (u32x8)_mm256_permute4x64_epi64((i256)wi, 0b01'01'01'01),\n\
    \                (u32x8)_mm256_permute4x64_epi64((i256)wi, 0b10'10'10'10),\n \
    \               (u32x8)_mm256_permute4x64_epi64((i256)wi, 0b11'11'11'11),\n  \
    \          };\n            if constexpr (L == L0) {\n                for (int\
    \ j = 0; j < 8; j += 4) {\n                    aux_mul_mod_x2L<L, 4, remove_montgomery_reduction_factor>(a\
    \ + (i + j) * sz, b + (i + j) * sz, c + (i + j) * sz,\n                      \
    \                                                        {w_ar[j / 2], mts.mod\
    \ - w_ar[j / 2], w_ar[j / 2 + 1], mts.mod - w_ar[j / 2 + 1]}, mts);\n        \
    \        }\n            } else {\n                for (int j = 0; j < 8; j +=\
    \ 2) {\n                    aux_mul_mod_x2L<L, 2, remove_montgomery_reduction_factor>(a\
    \ + (i + j) * sz, b + (i + j) * sz, c + (i + j) * sz,\n                      \
    \                                                        {w_ar[j / 2], mts.mod\
    \ - w_ar[j / 2]}, mts);\n                }\n            }\n            wi = mts.mul_u64x4<true>(wi,\
    \ wld_x4[__builtin_ctz(~i >> 3)]);\n        }\n    }\n\n   public:\n    // input\
    \ in [0, 4 * mod)\n    // output in [0, 2 * mod)\n    template <bool remove_montgomery_reduction_factor\
    \ = true>\n    void aux_dot_mod(int lg, const u32* a, const u32* b, u32* c) const\
    \ {\n        int L = get_low_lg(lg);\n        if (L == L0) {\n            aux_mul_mod_full<L0,\
    \ remove_montgomery_reduction_factor>(lg, a, b, c);\n        } else {\n      \
    \      aux_mul_mod_full<L0 + 1, remove_montgomery_reduction_factor>(lg, a, b,\
    \ c);\n        }\n    }\n\n    // lg must be greater than or equal to 3\n    //\
    \ a, b must be 32-byte aligned\n    void convolve_cyclic(int lg, u32* a, u32*\
    \ b) const {\n        transform_forward(lg, a);\n        transform_forward(lg,\
    \ b);\n        aux_dot_mod<false>(lg, a, b, a);\n        transform_inverse<true>(lg,\
    \ a, mt.r);\n    }\n};\n\n}  // namespace fast998\n}  // namespace internal\n\
    }  // namespace fps\n}  // namespace m1une\n\n#endif  // M1UNE_FPS_INTERNAL_NTT998_FAST_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/fps/internal/ntt998_fast.hpp
  requiredBy:
  - math/partition_function.hpp
  - math/combinatorial_sequences.hpp
  - math/all.hpp
  - math/bernoulli.hpp
  - math/fps/half_gcd.hpp
  - math/fps/formal_power_series.hpp
  - math/fps/convolution_ll.hpp
  - math/fps/all.hpp
  - math/fps/lagrange_inversion.hpp
  - math/fps/multipoint_evaluation.hpp
  - math/fps/linear_recurrence.hpp
  - math/fps/convolution.hpp
  - graph/all.hpp
  - graph/counting.hpp
  timestamp: '2026-07-11 02:52:00+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/math/bernoulli_utilities.test.cpp
  - verify/math/bell_number.test.cpp
  - verify/math/partition_function.test.cpp
  - verify/math/math_algorithms.test.cpp
  - verify/math/fps/inv_of_formal_power_series.test.cpp
  - verify/math/fps/half_gcd.test.cpp
  - verify/math/fps/pow_of_formal_power_series.test.cpp
  - verify/math/fps/polynomial_interpolation.test.cpp
  - verify/math/fps/convolution_ll.test.cpp
  - verify/math/fps/exp_of_formal_power_series.test.cpp
  - verify/math/fps/multipoint_evaluation.test.cpp
  - verify/math/fps/kth_term_of_linearly_recurrent_sequence.test.cpp
  - verify/math/fps/convolution_mod.test.cpp
  - verify/math/fps/polynomial_taylor_shift.test.cpp
  - verify/math/fps/lagrange_inversion.test.cpp
  - verify/math/fps/fps_algorithms.test.cpp
  - verify/math/stirling_number_of_the_second_kind.test.cpp
  - verify/math/bernoulli_number.test.cpp
  - verify/graph/cow_game.test.cpp
  - verify/graph/graph_counting.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: math/fps/internal/ntt998_fast.hpp
layout: document
redirect_from:
- /library/math/fps/internal/ntt998_fast.hpp
- /library/math/fps/internal/ntt998_fast.hpp.html
title: math/fps/internal/ntt998_fast.hpp
---
