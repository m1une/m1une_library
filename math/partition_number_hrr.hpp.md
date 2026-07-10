---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/partition_number_hrr.hpp\"\n\n\n\n#line 1 \"utilities/bigint.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <iomanip>\n#include <iostream>\n#include\
    \ <stdexcept>\n#include <string>\n#include <tuple>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace utilities {\n\nstruct BigInt {\n    static constexpr int\
    \ BASE = 1000000000;\n    static constexpr int BASE_DIGITS = 9;\n\n    std::vector<int>\
    \ a;\n    int sign;\n\n    BigInt() : sign(1) {}\n\n    BigInt(long long v) {\n\
    \        *this = v;\n    }\n\n    BigInt(const std::string& s) {\n        read(s);\n\
    \    }\n\n    BigInt& operator=(long long v) {\n        sign = 1;\n        unsigned\
    \ long long magnitude = static_cast<unsigned long long>(v);\n        if (v < 0)\
    \ {\n            sign = -1;\n            magnitude = 0 - magnitude;\n        }\n\
    \        a.clear();\n        for (; magnitude > 0; magnitude /= BASE) {\n    \
    \        a.push_back(int(magnitude % BASE));\n        }\n        return *this;\n\
    \    }\n\n    BigInt& operator=(const std::string& s) {\n        read(s);\n  \
    \      return *this;\n    }\n\n    void trim() {\n        while (!a.empty() &&\
    \ a.back() == 0) {\n            a.pop_back();\n        }\n        if (a.empty())\
    \ sign = 1;\n    }\n\n    void read(const std::string& s) {\n        sign = 1;\n\
    \        a.clear();\n        int pos = 0;\n        while (pos < (int)s.size()\
    \ && (s[pos] == '-' || s[pos] == '+')) {\n            if (s[pos] == '-') sign\
    \ = -1;\n            ++pos;\n        }\n        for (int i = int(s.size()) - 1;\
    \ i >= pos; i -= BASE_DIGITS) {\n            int x = 0;\n            for (int\
    \ j = std::max(pos, i - BASE_DIGITS + 1); j <= i; ++j) {\n                x =\
    \ x * 10 + (s[j] - '0');\n            }\n            a.push_back(x);\n       \
    \ }\n        trim();\n    }\n\n    std::string to_string() const {\n        if\
    \ (a.empty()) return \"0\";\n        std::string res = \"\";\n        if (sign\
    \ == -1) res += '-';\n        res += std::to_string(a.back());\n        for (int\
    \ i = (int)a.size() - 2; i >= 0; --i) {\n            std::string block = std::to_string(a[i]);\n\
    \            res += std::string(BASE_DIGITS - block.length(), '0') + block;\n\
    \        }\n        return res;\n    }\n\n    bool is_zero() const {\n       \
    \ return a.empty() || (a.size() == 1 && a[0] == 0);\n    }\n\n    BigInt operator-()\
    \ const {\n        BigInt res = *this;\n        if (!is_zero()) res.sign = -sign;\n\
    \        return res;\n    }\n\n    BigInt abs() const {\n        BigInt res =\
    \ *this;\n        res.sign = 1;\n        return res;\n    }\n\n    friend bool\
    \ operator<(const BigInt& x, const BigInt& y) {\n        if (x.sign != y.sign)\
    \ return x.sign < y.sign;\n        if (x.a.size() != y.a.size()) {\n         \
    \   return (x.sign == 1) ? (x.a.size() < y.a.size()) : (x.a.size() > y.a.size());\n\
    \        }\n        for (int i = (int)x.a.size() - 1; i >= 0; --i) {\n       \
    \     if (x.a[i] != y.a[i]) {\n                return (x.sign == 1) ? (x.a[i]\
    \ < y.a[i]) : (x.a[i] > y.a[i]);\n            }\n        }\n        return false;\n\
    \    }\n\n    friend bool operator>(const BigInt& x, const BigInt& y) {\n    \
    \    return y < x;\n    }\n    friend bool operator<=(const BigInt& x, const BigInt&\
    \ y) {\n        return !(y < x);\n    }\n    friend bool operator>=(const BigInt&\
    \ x, const BigInt& y) {\n        return !(x < y);\n    }\n    friend bool operator==(const\
    \ BigInt& x, const BigInt& y) {\n        return !(x < y) && !(y < x);\n    }\n\
    \    friend bool operator!=(const BigInt& x, const BigInt& y) {\n        return\
    \ x < y || y < x;\n    }\n\n    BigInt& operator+=(const BigInt& other) {\n  \
    \      if (other.is_zero()) return *this;\n        if (is_zero()) return *this\
    \ = other;\n        if (sign != other.sign) return *this -= (-other);\n      \
    \  for (int i = 0, carry = 0; i < (int)std::max(a.size(), other.a.size()) || carry;\
    \ ++i) {\n            if (i == (int)a.size()) a.push_back(0);\n            a[i]\
    \ += carry + (i < (int)other.a.size() ? other.a[i] : 0);\n            carry =\
    \ a[i] >= BASE;\n            if (carry) a[i] -= BASE;\n        }\n        return\
    \ *this;\n    }\n\n    BigInt& operator-=(const BigInt& other) {\n        if (other.is_zero())\
    \ return *this;\n        if (is_zero()) return *this = -other;\n        if (sign\
    \ != other.sign) return *this += (-other);\n        if (abs() < other.abs()) {\n\
    \            BigInt tmp = other;\n            tmp -= *this;\n            *this\
    \ = tmp;\n            sign = -sign;\n            return *this;\n        }\n  \
    \      for (int i = 0, carry = 0; i < (int)other.a.size() || carry; ++i) {\n \
    \           a[i] -= carry + (i < (int)other.a.size() ? other.a[i] : 0);\n    \
    \        carry = a[i] < 0;\n            if (carry) a[i] += BASE;\n        }\n\
    \        trim();\n        return *this;\n    }\n\n    BigInt& operator*=(int v)\
    \ {\n        long long multiplier = v;\n        if (multiplier < 0) {\n      \
    \      sign = -sign;\n            multiplier = -multiplier;\n        }\n     \
    \   long long carry = 0;\n        for (int i = 0; i < (int)a.size() || carry;\
    \ ++i) {\n            if (i == (int)a.size()) a.push_back(0);\n            const\
    \ long long cur = a[i] * multiplier + carry;\n            carry = cur / BASE;\n\
    \            a[i] = (int)(cur % BASE);\n        }\n        trim();\n        return\
    \ *this;\n    }\n\n    BigInt& operator*=(const BigInt& other) {\n        if (is_zero()\
    \ || other.is_zero()) return *this = 0;\n        std::vector<int> res(a.size()\
    \ + other.a.size());\n        for (int i = 0; i < (int)a.size(); ++i) {\n    \
    \        for (int j = 0, carry = 0; j < (int)other.a.size() || carry; ++j) {\n\
    \                long long cur = res[i + j] + a[i] * (long long)(j < (int)other.a.size()\
    \ ? other.a[j] : 0) + carry;\n                carry = (int)(cur / BASE);\n   \
    \             res[i + j] = (int)(cur % BASE);\n            }\n        }\n    \
    \    a = res;\n        sign *= other.sign;\n        trim();\n        return *this;\n\
    \    }\n\n    friend std::pair<BigInt, BigInt> divmod(const BigInt& a1, const\
    \ BigInt& b1) {\n        if (b1.is_zero()) {\n            throw std::domain_error(\"\
    BigInt division by zero\");\n        }\n        BigInt a = a1.abs(), b = b1.abs(),\
    \ q, r;\n        q.a.resize(a.a.size());\n        for (int i = (int)a.a.size()\
    \ - 1; i >= 0; --i) {\n            r *= BASE;\n            r += a.a[i];\n    \
    \        int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];\n          \
    \  int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];\n        \
    \    int d = ((long long)BASE * s1 + s2) / b.a.back();\n            r -= b * d;\n\
    \            while (r < 0) {\n                r += b;\n                --d;\n\
    \            }\n            q.a[i] = d;\n        }\n        q.sign = a1.sign *\
    \ b1.sign;\n        r.sign = a1.sign;\n        q.trim();\n        r.trim();\n\
    \        return {q, r};\n    }\n\n    BigInt& operator/=(const BigInt& other)\
    \ {\n        return *this = divmod(*this, other).first;\n    }\n    BigInt& operator%=(const\
    \ BigInt& other) {\n        return *this = divmod(*this, other).second;\n    }\n\
    \n    friend BigInt operator+(BigInt x, const BigInt& y) {\n        return x +=\
    \ y;\n    }\n    friend BigInt operator-(BigInt x, const BigInt& y) {\n      \
    \  return x -= y;\n    }\n    friend BigInt operator*(BigInt x, const BigInt&\
    \ y) {\n        return x *= y;\n    }\n    friend BigInt operator/(BigInt x, const\
    \ BigInt& y) {\n        return x /= y;\n    }\n    friend BigInt operator%(BigInt\
    \ x, const BigInt& y) {\n        return x %= y;\n    }\n\n    friend std::ostream&\
    \ operator<<(std::ostream& os, const BigInt& b) {\n        return os << b.to_string();\n\
    \    }\n\n    friend std::istream& operator>>(std::istream& is, BigInt& b) {\n\
    \        std::string s;\n        if (is >> s) b.read(s);\n        return is;\n\
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 5 \"\
    math/partition_number_hrr.hpp\"\n\n#if !__has_include(<flint/partitions.h>)\n\
    #error \"partition_number_hrr.hpp requires FLINT 3 (libflint-dev or brew install\
    \ flint)\"\n#endif\n\n#include <flint/flint.h>\n#include <flint/fmpz.h>\n#include\
    \ <flint/partitions.h>\n\n#line 16 \"math/partition_number_hrr.hpp\"\n\nnamespace\
    \ m1une {\nnamespace math {\n\n// Computes one exact partition number through\
    \ FLINT's rigorous\n// Hardy-Ramanujan-Rademacher implementation.\ninline utilities::BigInt\
    \ partition_number_hrr(unsigned long n) {\n    fmpz_t value;\n    fmpz_init(value);\n\
    \    partitions_fmpz_ui(value, n);\n\n    char* digits = fmpz_get_str(nullptr,\
    \ 10, value);\n    fmpz_clear(value);\n    if (digits == nullptr) {\n        throw\
    \ std::runtime_error(\"FLINT failed to format the partition number\");\n    }\n\
    \n    std::string text(digits);\n    flint_free(digits);\n    return utilities::BigInt(text);\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_PARTITION_NUMBER_HRR_HPP\n#define M1UNE_MATH_PARTITION_NUMBER_HRR_HPP\
    \ 1\n\n#include \"../utilities/bigint.hpp\"\n\n#if !__has_include(<flint/partitions.h>)\n\
    #error \"partition_number_hrr.hpp requires FLINT 3 (libflint-dev or brew install\
    \ flint)\"\n#endif\n\n#include <flint/flint.h>\n#include <flint/fmpz.h>\n#include\
    \ <flint/partitions.h>\n\n#include <stdexcept>\n#include <string>\n\nnamespace\
    \ m1une {\nnamespace math {\n\n// Computes one exact partition number through\
    \ FLINT's rigorous\n// Hardy-Ramanujan-Rademacher implementation.\ninline utilities::BigInt\
    \ partition_number_hrr(unsigned long n) {\n    fmpz_t value;\n    fmpz_init(value);\n\
    \    partitions_fmpz_ui(value, n);\n\n    char* digits = fmpz_get_str(nullptr,\
    \ 10, value);\n    fmpz_clear(value);\n    if (digits == nullptr) {\n        throw\
    \ std::runtime_error(\"FLINT failed to format the partition number\");\n    }\n\
    \n    std::string text(digits);\n    flint_free(digits);\n    return utilities::BigInt(text);\n\
    }\n\n}  // namespace math\n}  // namespace m1une\n\n#endif  // M1UNE_MATH_PARTITION_NUMBER_HRR_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/partition_number_hrr.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/partition_number_hrr.hpp
layout: document
title: Isolated Partition Number (HRR)
---

## Overview

`partition_number_hrr(n)` computes one exact integer partition number $p(n)$.
It is intended for an isolated, potentially very large index. This differs
from `partition_function<Mint>(maximum)`, which efficiently computes every
coefficient from `p(0)` through `p(maximum)` modulo `Mint::mod()`.

The function uses FLINT's implementation of the
Hardy-Ramanujan-Rademacher formula. FLINT evaluates $O(\sqrt n)$ terms using
factored exponential sums and Arb variable-precision ball arithmetic. A
Rademacher remainder bound is added to the numerical enclosure, and the result
is accepted only when the ball contains one unique integer.

For small indices, FLINT uses lookup and Euler-recurrence shortcuts. Its HRR
path is used for sufficiently large indices.

## Dependency

This optional header requires FLINT 3 and links against FLINT, GMP, and MPFR.
It is deliberately not included by `math/all.hpp`, so the rest of the library
remains dependency-free and header-only.

On common systems, install FLINT with one of:

```sh
brew install flint
sudo apt-get install libflint-dev
```

Use `pkg-config` when compiling:

```sh
g++ -std=c++20 -O2 -I. program.cpp $(pkg-config --cflags --libs flint)
```

## Interface

| Function | Complexity | Description |
| --- | --- | --- |
| `utilities::BigInt partition_number_hrr(unsigned long n)` | $O(n^{1/2+o(1)})$ bit operations plus output conversion | Returns the exact integer $p(n)$. |

The returned value has $\Theta(\sqrt n)$ bits, so merely writing it requires
$\Omega(\sqrt n)$ work and memory. The index must fit `unsigned long`.

## Example

```cpp
#include "math/partition_number_hrr.hpp"

#include <iostream>

int main() {
    m1une::utilities::BigInt answer =
        m1une::math::partition_number_hrr(1000);
    std::cout << answer << "\n";
}
```

## Verification

The external-dependency test is intentionally ignored by
`online-judge-verify-helper`. Run it manually with:

```sh
g++ -std=c++20 -O2 -Wall -Wextra -I. \
    verify/math/partition_number_hrr.test.cpp \
    $(pkg-config --cflags --libs flint) \
    -o partition_number_hrr.test
./partition_number_hrr.test
```

The test checks known exact values, compares every result through 5000 with
the independent FPS implementation modulo $10^9+7$, and exercises the HRR
path at $n=10^6$.

## References

* Fredrik Johansson, [Efficient implementation of the
  Hardy-Ramanujan-Rademacher formula](https://arxiv.org/abs/1205.5991).
* [FLINT partition-function interface](https://flintlib.org/doc/partitions.html).
