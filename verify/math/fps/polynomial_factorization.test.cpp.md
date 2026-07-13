---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':question:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':question:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':question:'
    path: math/fps/polynomial_factorization.hpp
    title: Polynomial Factorization
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':question:'
    path: math/modular_square_root.hpp
    title: Modular Square Root
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/factorization_of_polynomials
    links:
    - https://judge.yosupo.jp/problem/factorization_of_polynomials
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/factorization_of_polynomials\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <type_traits>\n\
    #include <vector>\n\n#include \"../../../math/fps/polynomial_factorization.hpp\"\
    \n#include \"../../../math/modint.hpp\"\n\nnamespace {\n\nstruct DynamicModInt\
    \ {\n   private:\n    inline static uint32_t modulus_ = 2;\n    uint32_t value_\
    \ = 0;\n\n   public:\n    static void set_mod(uint32_t modulus) {\n        modulus_\
    \ = modulus;\n    }\n\n    static uint32_t mod() {\n        return modulus_;\n\
    \    }\n\n    DynamicModInt() = default;\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
    \ int> = 0>\n    DynamicModInt(Integer value) {\n        if constexpr (std::is_signed_v<Integer>)\
    \ {\n            int64_t reduced = int64_t(value) % int64_t(modulus_);\n     \
    \       if (reduced < 0) reduced += modulus_;\n            value_ = uint32_t(reduced);\n\
    \        } else {\n            value_ = uint32_t(uint64_t(value) % modulus_);\n\
    \        }\n    }\n\n    uint32_t val() const {\n        return value_;\n    }\n\
    \n    DynamicModInt& operator+=(DynamicModInt rhs) {\n        value_ += rhs.value_;\n\
    \        if (value_ >= modulus_) value_ -= modulus_;\n        return *this;\n\
    \    }\n\n    DynamicModInt& operator-=(DynamicModInt rhs) {\n        value_ -=\
    \ rhs.value_;\n        if (value_ >= modulus_) value_ += modulus_;\n        return\
    \ *this;\n    }\n\n    DynamicModInt& operator*=(DynamicModInt rhs) {\n      \
    \  value_ = uint32_t(uint64_t(value_) * rhs.value_ % modulus_);\n        return\
    \ *this;\n    }\n\n    DynamicModInt& operator/=(DynamicModInt rhs) {\n      \
    \  return *this *= rhs.inv();\n    }\n\n    DynamicModInt pow(uint64_t exponent)\
    \ const {\n        DynamicModInt result = 1;\n        DynamicModInt base = *this;\n\
    \        while (exponent > 0) {\n            if (exponent & 1) result *= base;\n\
    \            base *= base;\n            exponent >>= 1;\n        }\n        return\
    \ result;\n    }\n\n    DynamicModInt inv() const {\n        assert(value_ !=\
    \ 0);\n        return pow(modulus_ - 2);\n    }\n\n    friend DynamicModInt operator+(DynamicModInt\
    \ lhs, DynamicModInt rhs) {\n        return lhs += rhs;\n    }\n\n    friend DynamicModInt\
    \ operator-(DynamicModInt lhs, DynamicModInt rhs) {\n        return lhs -= rhs;\n\
    \    }\n\n    friend DynamicModInt operator*(DynamicModInt lhs, DynamicModInt\
    \ rhs) {\n        return lhs *= rhs;\n    }\n\n    friend DynamicModInt operator/(DynamicModInt\
    \ lhs, DynamicModInt rhs) {\n        return lhs /= rhs;\n    }\n\n    friend bool\
    \ operator==(DynamicModInt lhs, DynamicModInt rhs) {\n        return lhs.value_\
    \ == rhs.value_;\n    }\n\n    friend bool operator!=(DynamicModInt lhs, DynamicModInt\
    \ rhs) {\n        return !(lhs == rhs);\n    }\n};\n\ntemplate <class Mint>\n\
    using Fps = m1une::fps::FormalPowerSeries<Mint>;\n\ntemplate <class Mint>\nFps<Mint>\
    \ multiply(const Fps<Mint>& first, const Fps<Mint>& second) {\n    if (first.empty()\
    \ || second.empty()) return {};\n    Fps<Mint> result(first.size() + second.size()\
    \ - 1);\n    for (int i = 0; i < int(first.size()); i++) {\n        for (int j\
    \ = 0; j < int(second.size()); j++) {\n            result[i + j] += first[i] *\
    \ second[j];\n        }\n    }\n    result.shrink();\n    return result;\n}\n\n\
    #ifndef NDEBUG\nvoid focused_tests() {\n    using Mint = m1une::math::ModInt<17>;\n\
    \    const Fps<Mint> linear_a({Mint(14), Mint(1)});\n    const Fps<Mint> linear_b({Mint(12),\
    \ Mint(1)});\n    const Fps<Mint> quadratic({Mint(3), Mint(0), Mint(1)});\n\n\
    \    Fps<Mint> polynomial(1, Mint(7));\n    for (int i = 0; i < 3; i++) polynomial\
    \ = multiply(polynomial, linear_a);\n    for (int i = 0; i < 2; i++) polynomial\
    \ = multiply(polynomial, linear_b);\n    polynomial = multiply(polynomial, quadratic);\n\
    \n    auto result = m1une::fps::polynomial_factorize(polynomial);\n    assert(result.leading_coefficient\
    \ == Mint(7));\n    assert(result.factors.size() == 3);\n\n    Fps<Mint> restored(1,\
    \ result.leading_coefficient);\n    for (const auto& factor : result.factors)\
    \ {\n        assert(factor.polynomial.back() == Mint(1));\n        for (int copy\
    \ = 0; copy < factor.multiplicity; copy++) {\n            restored = multiply(restored,\
    \ factor.polynomial);\n        }\n    }\n    assert(restored == polynomial);\n\
    \n    auto constant = m1une::fps::polynomial_factorize(Fps<Mint>(1, Mint(11)));\n\
    \    assert(constant.leading_coefficient == Mint(11));\n    assert(constant.factors.empty());\n\
    \n    DynamicModInt::set_mod(2);\n    Fps<DynamicModInt> repeated({DynamicModInt(1),\
    \ DynamicModInt(0),\n                                 DynamicModInt(1), DynamicModInt(0),\n\
    \                                 DynamicModInt(1)});\n    auto characteristic_two\
    \ = m1une::fps::polynomial_factorize(repeated);\n    Fps<DynamicModInt> restored_two(1,\
    \ characteristic_two.leading_coefficient);\n    for (const auto& factor : characteristic_two.factors)\
    \ {\n        for (int copy = 0; copy < factor.multiplicity; copy++) {\n      \
    \      restored_two = multiply(restored_two, factor.polynomial);\n        }\n\
    \    }\n    assert(restored_two == repeated);\n}\n#endif\n\n}  // namespace\n\n\
    int main() {\n#ifndef NDEBUG\n    focused_tests();\n#endif\n\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int degree;\n    uint32_t prime;\n    std::cin\
    \ >> degree >> prime;\n    DynamicModInt::set_mod(prime);\n\n    Fps<DynamicModInt>\
    \ polynomial(degree + 1);\n    for (DynamicModInt& coefficient : polynomial) {\n\
    \        uint32_t value;\n        std::cin >> value;\n        coefficient = DynamicModInt(value);\n\
    \    }\n\n    auto result = m1une::fps::polynomial_factorize(std::move(polynomial));\n\
    \    std::cout << result.factors.size() << '\\n';\n    for (const auto& factor\
    \ : result.factors) {\n        std::cout << factor.multiplicity << ' ' << factor.polynomial.size()\
    \ - 1;\n        for (DynamicModInt coefficient : factor.polynomial) {\n      \
    \      std::cout << ' ' << coefficient.val();\n        }\n        std::cout <<\
    \ '\\n';\n    }\n}\n"
  dependsOn:
  - math/fps/polynomial_factorization.hpp
  - math/fps/formal_power_series.hpp
  - math/modular_square_root.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/fps/polynomial_factorization.test.cpp
  requiredBy: []
  timestamp: '2026-07-13 21:13:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/fps/polynomial_factorization.test.cpp
layout: document
redirect_from:
- /verify/verify/math/fps/polynomial_factorization.test.cpp
- /verify/verify/math/fps/polynomial_factorization.test.cpp.html
title: verify/math/fps/polynomial_factorization.test.cpp
---
