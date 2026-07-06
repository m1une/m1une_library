---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/generalized_floor_sum.hpp
    title: Generalized Floor Sum
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/2362
    links:
    - https://yukicoder.me/problems/no/2362
  bundledCode: "#line 1 \"verify/math/yukicoder_2362.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/2362\"\n\n#line 1 \"math/generalized_floor_sum.hpp\"\
    \n\n\n\n#include <array>\n#include <cassert>\n#include <cstdint>\n#include <type_traits>\n\
    #include <utility>\n\nnamespace m1une {\nnamespace math {\n\ntemplate <class T,\
    \ int MaxPower, int MaxFloorPower>\nusing GeneralizedFloorSumTable =\n    std::array<std::array<T,\
    \ MaxFloorPower + 1>, MaxPower + 1>;\n\nnamespace generalized_floor_sum_detail\
    \ {\n\nusing SignedWide = __int128_t;\nusing UnsignedWide = __uint128_t;\n\ntemplate\
    \ <class T>\nT from_wide(SignedWide value) {\n    bool negative = value < 0;\n\
    \    UnsignedWide magnitude;\n    if (negative) {\n        magnitude = static_cast<UnsignedWide>(-(value\
    \ + 1));\n        ++magnitude;\n    } else {\n        magnitude = static_cast<UnsignedWide>(value);\n\
    \    }\n\n    T result = T();\n    T binary_place = T(1);\n    while (magnitude\
    \ > 0) {\n        if ((magnitude & 1) != 0) result += binary_place;\n        magnitude\
    \ >>= 1;\n        if (magnitude > 0) binary_place += binary_place;\n    }\n  \
    \  return negative ? T() - result : result;\n}\n\ninline SignedWide floor_div(SignedWide\
    \ numerator, SignedWide denominator) {\n    assert(denominator > 0);\n    SignedWide\
    \ quotient = numerator / denominator;\n    if (numerator % denominator < 0) --quotient;\n\
    \    return quotient;\n}\n\ntemplate <class T, int MaxPower, int MaxFloorPower>\n\
    class MomentMonoid {\n   public:\n    using Table = GeneralizedFloorSumTable<T,\
    \ MaxPower, MaxFloorPower>;\n\n    struct Data {\n        Table sums{};\n    \
    \    T delta_x = T();\n        T delta_y = T();\n    };\n\n    static constexpr\
    \ int MaximumDegree =\n        MaxPower > MaxFloorPower ? MaxPower : MaxFloorPower;\n\
    \n    MomentMonoid() {\n        binomial_[0][0] = T(1);\n        for (int degree\
    \ = 0; degree < MaximumDegree; ++degree) {\n            for (int index = 0; index\
    \ <= degree; ++index) {\n                binomial_[degree + 1][index] += binomial_[degree][index];\n\
    \                binomial_[degree + 1][index + 1] +=\n                    binomial_[degree][index];\n\
    \            }\n        }\n    }\n\n    const T& binomial(int n, int k) const\
    \ {\n        assert(0 <= k && k <= n && n <= MaximumDegree);\n        return binomial_[n][k];\n\
    \    }\n\n    Data unit() const {\n        return Data();\n    }\n\n    Data x_step()\
    \ const {\n        Data result;\n        result.sums[0][0] = T(1);\n        result.delta_x\
    \ = T(1);\n        return result;\n    }\n\n    Data y_step() const {\n      \
    \  Data result;\n        result.delta_y = T(1);\n        return result;\n    }\n\
    \n    Data concatenate(Data left, Data right) const {\n        std::array<T, MaxPower\
    \ + 1> x_powers{};\n        std::array<T, MaxFloorPower + 1> y_powers{};\n   \
    \     x_powers[0] = T(1);\n        y_powers[0] = T(1);\n        for (int power\
    \ = 0; power < MaxPower; ++power) {\n            x_powers[power + 1] = x_powers[power]\
    \ * left.delta_x;\n        }\n        for (int power = 0; power < MaxFloorPower;\
    \ ++power) {\n            y_powers[power + 1] = y_powers[power] * left.delta_y;\n\
    \        }\n\n        // Shift the y-coordinate of every sampled x-step in the\
    \ right path.\n        for (int x_power = 0; x_power <= MaxPower; ++x_power) {\n\
    \            for (int old_power = MaxFloorPower; old_power >= 0; --old_power)\
    \ {\n                T source = right.sums[x_power][old_power];\n            \
    \    for (int new_power = old_power + 1;\n                     new_power <= MaxFloorPower;\n\
    \                     ++new_power) {\n                    right.sums[x_power][new_power]\
    \ +=\n                        binomial_[new_power][old_power] *\n            \
    \            y_powers[new_power - old_power] * source;\n                }\n  \
    \          }\n        }\n\n        // Shift x, then append all samples from the\
    \ right path.\n        for (int y_power = 0; y_power <= MaxFloorPower; ++y_power)\
    \ {\n            for (int old_power = 0; old_power <= MaxPower; ++old_power) {\n\
    \                T source = right.sums[old_power][y_power];\n                for\
    \ (int new_power = old_power;\n                     new_power <= MaxPower;\n \
    \                    ++new_power) {\n                    left.sums[new_power][y_power]\
    \ +=\n                        binomial_[new_power][old_power] *\n            \
    \            x_powers[new_power - old_power] * source;\n                }\n  \
    \          }\n        }\n\n        left.delta_x += right.delta_x;\n        left.delta_y\
    \ += right.delta_y;\n        return left;\n    }\n\n   private:\n    std::array<std::array<T,\
    \ MaximumDegree + 1>, MaximumDegree + 1>\n        binomial_{};\n};\n\ntemplate\
    \ <class Monoid>\ntypename Monoid::Data monoid_power(\n    const Monoid& monoid,\n\
    \    typename Monoid::Data base,\n    UnsignedWide exponent\n) {\n    typename\
    \ Monoid::Data result = monoid.unit();\n    while (exponent > 0) {\n        if\
    \ ((exponent & 1) != 0) {\n            result = monoid.concatenate(std::move(result),\
    \ base);\n        }\n        exponent >>= 1;\n        if (exponent > 0) {\n  \
    \          base = monoid.concatenate(base, base);\n        }\n    }\n    return\
    \ result;\n}\n\ntemplate <class Monoid>\ntypename Monoid::Data floor_path_product(\n\
    \    const Monoid& monoid,\n    UnsignedWide n,\n    UnsignedWide a,\n    UnsignedWide\
    \ b,\n    UnsignedWide modulus\n) {\n    assert(modulus > 0);\n    UnsignedWide\
    \ height = (a * n + b) / modulus;\n    typename Monoid::Data x = monoid.x_step();\n\
    \    typename Monoid::Data y = monoid.y_step();\n    typename Monoid::Data prefix\
    \ = monoid.unit();\n    typename Monoid::Data suffix = monoid.unit();\n\n    while\
    \ (true) {\n        UnsignedWide slope_quotient = a / modulus;\n        UnsignedWide\
    \ intercept_quotient = b / modulus;\n        a %= modulus;\n        b %= modulus;\n\
    \n        x = monoid.concatenate(\n            std::move(x),\n            monoid_power(monoid,\
    \ y, slope_quotient)\n        );\n        prefix = monoid.concatenate(\n     \
    \       std::move(prefix),\n            monoid_power(monoid, y, intercept_quotient)\n\
    \        );\n        height -= slope_quotient * n + intercept_quotient;\n    \
    \    if (height == 0) break;\n\n        assert(a > 0);\n        UnsignedWide boundary\
    \ =\n            (modulus * height - b - 1) / a + 1;\n        suffix = monoid.concatenate(\n\
    \            y,\n            monoid.concatenate(\n                monoid_power(monoid,\
    \ x, n - boundary),\n                std::move(suffix)\n            )\n      \
    \  );\n        b = modulus - b - 1 + a;\n        n = height - 1;\n        height\
    \ = boundary;\n        std::swap(modulus, a);\n        std::swap(x, y);\n    }\n\
    \n    x = monoid_power(monoid, x, n);\n    return monoid.concatenate(\n      \
    \  monoid.concatenate(std::move(prefix), std::move(x)),\n        std::move(suffix)\n\
    \    );\n}\n\ntemplate <class T, int MaxPower, int MaxFloorPower>\nGeneralizedFloorSumTable<T,\
    \ MaxPower, MaxFloorPower>\nnonnegative_slope_table(\n    const MomentMonoid<T,\
    \ MaxPower, MaxFloorPower>& monoid,\n    SignedWide n,\n    SignedWide modulus,\n\
    \    SignedWide a,\n    SignedWide b\n) {\n    assert(n >= 0 && modulus > 0 &&\
    \ a >= 0);\n    SignedWide y_offset = floor_div(b, modulus);\n    SignedWide normalized_b\
    \ = b - y_offset * modulus;\n\n    auto path = floor_path_product(\n        monoid,\n\
    \        static_cast<UnsignedWide>(n),\n        static_cast<UnsignedWide>(a),\n\
    \        static_cast<UnsignedWide>(normalized_b),\n        static_cast<UnsignedWide>(modulus)\n\
    \    );\n\n    std::array<T, MaxFloorPower + 1> offset_powers{};\n    offset_powers[0]\
    \ = T(1);\n    T offset = from_wide<T>(y_offset);\n    for (int power = 0; power\
    \ < MaxFloorPower; ++power) {\n        offset_powers[power + 1] = offset_powers[power]\
    \ * offset;\n    }\n\n    GeneralizedFloorSumTable<T, MaxPower, MaxFloorPower>\
    \ result{};\n    for (int x_power = 0; x_power <= MaxPower; ++x_power) {\n   \
    \     for (int y_power = 0; y_power <= MaxFloorPower; ++y_power) {\n         \
    \   for (int inner_power = 0;\n                 inner_power <= y_power;\n    \
    \             ++inner_power) {\n                result[x_power][y_power] +=\n\
    \                    monoid.binomial(y_power, inner_power) *\n               \
    \     offset_powers[y_power - inner_power] *\n                    path.sums[x_power][inner_power];\n\
    \            }\n        }\n    }\n    return result;\n}\n\n}  // namespace generalized_floor_sum_detail\n\
    \n// Returns every sum of x^p * floor((a*x+b)/mod)^q for 0 <= x < n,\n// 0 <=\
    \ p <= MaxPower, and 0 <= q <= MaxFloorPower.\ntemplate <class T, int MaxPower,\
    \ int MaxFloorPower, class I>\nGeneralizedFloorSumTable<T, MaxPower, MaxFloorPower>\n\
    generalized_floor_sum_table(I n, I mod, I a, I b) {\n    static_assert(MaxPower\
    \ >= 0 && MaxFloorPower >= 0);\n    static_assert(\n        std::is_integral_v<I>\
    \ && std::is_signed_v<I> && sizeof(I) <= 8,\n        \"generalized_floor_sum_table\
    \ requires signed integer arguments\"\n    );\n    assert(n >= 0);\n    assert(mod\
    \ > 0);\n\n    namespace detail = generalized_floor_sum_detail;\n    using Monoid\
    \ = detail::MomentMonoid<T, MaxPower, MaxFloorPower>;\n    static const Monoid\
    \ monoid;\n\n    detail::SignedWide wide_n = n;\n    detail::SignedWide wide_mod\
    \ = mod;\n    detail::SignedWide wide_a = a;\n    detail::SignedWide wide_b =\
    \ b;\n    if (wide_n == 0) {\n        return GeneralizedFloorSumTable<T, MaxPower,\
    \ MaxFloorPower>();\n    }\n    if (wide_a >= 0) {\n        return detail::nonnegative_slope_table(\n\
    \            monoid,\n            wide_n,\n            wide_mod,\n           \
    \ wide_a,\n            wide_b\n        );\n    }\n\n    // Substitute x = n -\
    \ 1 - t to make the slope nonnegative.\n    auto reflected = detail::nonnegative_slope_table(\n\
    \        monoid,\n        wide_n,\n        wide_mod,\n        -wide_a,\n     \
    \   wide_a * (wide_n - 1) + wide_b\n    );\n    std::array<T, MaxPower + 1> offset_powers{};\n\
    \    offset_powers[0] = T(1);\n    T offset = detail::from_wide<T>(wide_n - 1);\n\
    \    for (int power = 0; power < MaxPower; ++power) {\n        offset_powers[power\
    \ + 1] = offset_powers[power] * offset;\n    }\n\n    GeneralizedFloorSumTable<T,\
    \ MaxPower, MaxFloorPower> result{};\n    for (int x_power = 0; x_power <= MaxPower;\
    \ ++x_power) {\n        for (int y_power = 0; y_power <= MaxFloorPower; ++y_power)\
    \ {\n            for (int inner_power = 0;\n                 inner_power <= x_power;\n\
    \                 ++inner_power) {\n                T coefficient =\n        \
    \            monoid.binomial(x_power, inner_power) *\n                    offset_powers[x_power\
    \ - inner_power];\n                if ((inner_power & 1) != 0) coefficient = T()\
    \ - coefficient;\n                result[x_power][y_power] +=\n              \
    \      coefficient * reflected[inner_power][y_power];\n            }\n       \
    \ }\n    }\n    return result;\n}\n\ntemplate <class T, int Power, int FloorPower,\
    \ class I>\nT generalized_floor_sum(I n, I mod, I a, I b) {\n    return generalized_floor_sum_table<T,\
    \ Power, FloorPower>(n, mod, a, b)\n        [Power][FloorPower];\n}\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 4 \"verify/math/yukicoder_2362.test.cpp\"\
    \n\n#line 6 \"verify/math/yukicoder_2362.test.cpp\"\n#include <iostream>\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int test_count;\n    std::cin >> test_count;\n    while (test_count--) {\n\
    \        long long n, mod, x, y;\n        std::cin >> n >> mod >> x >> y;\n\n\
    \        auto without_offset =\n            m1une::math::generalized_floor_sum_table<std::uint64_t,\
    \ 1, 1>(\n                n,\n                mod,\n                x,\n     \
    \           0LL\n            );\n        auto with_offset =\n            m1une::math::generalized_floor_sum_table<std::uint64_t,\
    \ 1, 1>(\n                n,\n                mod,\n                x,\n     \
    \           y\n            );\n\n        std::uint64_t answer = 0;\n        answer\
    \ -= without_offset[0][1] * static_cast<std::uint64_t>(n) -\n                \
    \  without_offset[1][1];\n        answer -= with_offset[0][1] * static_cast<std::uint64_t>(n\
    \ - 1) -\n                  2 * with_offset[1][1];\n        std::cout << answer\
    \ << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/2362\"\n\n#include \"\
    ../../math/generalized_floor_sum.hpp\"\n\n#include <cstdint>\n#include <iostream>\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    int test_count;\n    std::cin >> test_count;\n    while (test_count--) {\n\
    \        long long n, mod, x, y;\n        std::cin >> n >> mod >> x >> y;\n\n\
    \        auto without_offset =\n            m1une::math::generalized_floor_sum_table<std::uint64_t,\
    \ 1, 1>(\n                n,\n                mod,\n                x,\n     \
    \           0LL\n            );\n        auto with_offset =\n            m1une::math::generalized_floor_sum_table<std::uint64_t,\
    \ 1, 1>(\n                n,\n                mod,\n                x,\n     \
    \           y\n            );\n\n        std::uint64_t answer = 0;\n        answer\
    \ -= without_offset[0][1] * static_cast<std::uint64_t>(n) -\n                \
    \  without_offset[1][1];\n        answer -= with_offset[0][1] * static_cast<std::uint64_t>(n\
    \ - 1) -\n                  2 * with_offset[1][1];\n        std::cout << answer\
    \ << '\\n';\n    }\n}\n"
  dependsOn:
  - math/generalized_floor_sum.hpp
  isVerificationFile: true
  path: verify/math/yukicoder_2362.test.cpp
  requiredBy: []
  timestamp: '2026-07-07 02:47:56+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/yukicoder_2362.test.cpp
layout: document
redirect_from:
- /verify/verify/math/yukicoder_2362.test.cpp
- /verify/verify/math/yukicoder_2362.test.cpp.html
title: verify/math/yukicoder_2362.test.cpp
---
