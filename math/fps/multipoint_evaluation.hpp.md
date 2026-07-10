---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/formal_power_series.hpp
    title: Formal Power Series
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  - icon: ':heavy_check_mark:'
    path: math/fps/all.hpp
    title: Formal Power Series All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/fps_algorithms.test.cpp
    title: verify/math/fps/fps_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/multipoint_evaluation.test.cpp
    title: verify/math/fps/multipoint_evaluation.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/fps/polynomial_interpolation.test.cpp
    title: verify/math/fps/polynomial_interpolation.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
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
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "#ifndef M1UNE_FPS_MULTIPOINT_EVALUATION_HPP\n#define M1UNE_FPS_MULTIPOINT_EVALUATION_HPP\
    \ 1\n\n#include <cassert>\n#include <vector>\n\n#include \"formal_power_series.hpp\"\
    \n\nnamespace m1une {\nnamespace fps {\n\ntemplate <class Mint>\nstruct SubproductTree\
    \ {\n    using Fps = FormalPowerSeries<Mint>;\n\n   private:\n    int point_count_;\n\
    \    int leaf_count_;\n    std::vector<Mint> points_;\n    std::vector<Fps> product_;\n\
    \n   public:\n    explicit SubproductTree(const std::vector<Mint>& points)\n \
    \       : point_count_(points.size()), leaf_count_(1), points_(points) {\n   \
    \     while (leaf_count_ < point_count_) leaf_count_ <<= 1;\n        product_.resize(leaf_count_\
    \ << 1);\n        for (int i = 0; i < leaf_count_; i++) {\n            if (i <\
    \ point_count_) {\n                product_[leaf_count_ + i].resize(2);\n    \
    \            product_[leaf_count_ + i][0] = Mint(0) - points_[i];\n          \
    \      product_[leaf_count_ + i][1] = Mint(1);\n            } else {\n       \
    \         product_[leaf_count_ + i].resize(1, Mint(1));\n            }\n     \
    \   }\n        for (int node = leaf_count_ - 1; node > 0; node--) {\n        \
    \    product_[node] = product_[node << 1] * product_[node << 1 | 1];\n       \
    \ }\n    }\n\n    int size() const {\n        return point_count_;\n    }\n\n\
    \    const Fps& product() const {\n        return product_[1];\n    }\n\n    std::vector<Mint>\
    \ evaluate(const Fps& polynomial) const {\n        std::vector<Mint> result(point_count_);\n\
    \        if (point_count_ == 0) return result;\n\n        std::vector<Fps> remainder(leaf_count_\
    \ << 1);\n        remainder[1] = polynomial % product_[1];\n        for (int node\
    \ = 1; node < leaf_count_; node++) {\n            remainder[node << 1] = remainder[node]\
    \ % product_[node << 1];\n            remainder[node << 1 | 1] = remainder[node]\
    \ % product_[node << 1 | 1];\n        }\n        for (int i = 0; i < point_count_;\
    \ i++) {\n            const Fps& value = remainder[leaf_count_ + i];\n       \
    \     result[i] = value.empty() ? Mint(0) : value[0];\n        }\n        return\
    \ result;\n    }\n\n    Fps interpolate(const std::vector<Mint>& values) const\
    \ {\n        assert(int(values.size()) == point_count_);\n        if (point_count_\
    \ == 0) return {};\n\n        std::vector<Mint> derivative_values = evaluate(product_[1].derivative());\n\
    \        std::vector<Fps> polynomial(leaf_count_ << 1);\n        for (int i =\
    \ 0; i < leaf_count_; i++) {\n            polynomial[leaf_count_ + i].resize(1);\n\
    \            if (i < point_count_) {\n                assert(derivative_values[i]\
    \ != Mint(0));\n                polynomial[leaf_count_ + i][0] = values[i] / derivative_values[i];\n\
    \            }\n        }\n        for (int node = leaf_count_ - 1; node > 0;\
    \ node--) {\n            polynomial[node] = polynomial[node << 1] * product_[node\
    \ << 1 | 1] +\n                               polynomial[node << 1 | 1] * product_[node\
    \ << 1];\n        }\n        polynomial[1].resize(point_count_);\n        return\
    \ polynomial[1];\n    }\n};\n\ntemplate <class Mint>\nstd::vector<Mint> multipoint_evaluate(const\
    \ FormalPowerSeries<Mint>& polynomial,\n                                     \
    \ const std::vector<Mint>& points) {\n    return SubproductTree<Mint>(points).evaluate(polynomial);\n\
    }\n\ntemplate <class Mint>\nFormalPowerSeries<Mint> polynomial_interpolate(const\
    \ std::vector<Mint>& points,\n                                               const\
    \ std::vector<Mint>& values) {\n    return SubproductTree<Mint>(points).interpolate(values);\n\
    }\n\n}  // namespace fps\n}  // namespace m1une\n\n#endif  // M1UNE_FPS_MULTIPOINT_EVALUATION_HPP\n"
  dependsOn:
  - math/fps/formal_power_series.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  isVerificationFile: false
  path: math/fps/multipoint_evaluation.hpp
  requiredBy:
  - math/all.hpp
  - math/fps/all.hpp
  timestamp: '2026-07-11 03:31:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
  - verify/math/fps/polynomial_interpolation.test.cpp
  - verify/math/fps/multipoint_evaluation.test.cpp
  - verify/math/fps/fps_algorithms.test.cpp
documentation_of: math/fps/multipoint_evaluation.hpp
layout: document
title: Multipoint Evaluation and Interpolation
---

## Overview

This header provides a subproduct tree for two related polynomial operations:

* multipoint evaluation computes $f(x_i)$ for many points $x_i$;
* interpolation constructs the unique polynomial $f$ of degree less than $N$
  such that $f(x_i) = y_i$ for every point-value pair.

Building `SubproductTree` once is useful when several polynomials are evaluated
at the same points. The free functions provide the same operations when the
tree is needed only once.

## Complexity Notation

* `N` is the number of points.
* `D` is the number of coefficients in the polynomial being evaluated.

Polynomial multiplication uses the NTT-based convolution from
`math/fps/convolution.hpp`.

## Subproduct Tree

For each point $x_i$, a leaf stores the polynomial

$$
P_i(x) = x - x_i.
$$

Each internal node stores the product of its two children. Therefore, the root
contains

$$
P(x) = \prod_{i=0}^{N-1}(x - x_i).
$$

The tree stores $O(N \log N)$ coefficients in total.

### Multipoint Evaluation

Evaluation propagates polynomial remainders from the root toward the leaves.
If a node represents polynomial $P_v(x)$, it receives

$$
f(x) \bmod P_v(x).
$$

The remainder is reduced modulo each child polynomial and passed downward. At
leaf $i$, the modulus is $x - x_i$, so the constant remainder is exactly
$f(x_i)$.

This evaluates all points together instead of applying Horner's method
independently at every point.

### Interpolation

Interpolation requires the points to be distinct. Let

$$
P(x) = \prod_{i=0}^{N-1}(x - x_i).
$$

The tree first evaluates $P'(x)$ at every point and computes the leaf weights

$$
w_i = \frac{y_i}{P'(x_i)}.
$$

For an internal node with left and right product polynomials $P_L$ and $P_R$,
the corresponding interpolation polynomials are combined as

$$
F = F_L P_R + F_R P_L.
$$

At the root, this is the Lagrange interpolation polynomial through all
$(x_i, y_i)$. Distinct points guarantee that every $P'(x_i)$ is nonzero and
invertible.

## API

```cpp
template <class Mint>
struct SubproductTree {
    explicit SubproductTree(const std::vector<Mint>& points);

    int size() const;
    const FormalPowerSeries<Mint>& product() const;
    std::vector<Mint> evaluate(
        const FormalPowerSeries<Mint>& polynomial) const;
    FormalPowerSeries<Mint> interpolate(
        const std::vector<Mint>& values) const;
};
```

| Method | Description | Complexity |
| --- | --- | --- |
| `SubproductTree(points)` | Builds the product tree for `points`. | $O(N \log^2 N)$ |
| `int size() const` | Returns the number of points. | $O(1)$ |
| `const Fps& product() const` | Returns $\prod_i (x - x_i)$. For no points, returns the constant polynomial $1$. | $O(1)$ |
| `evaluate(polynomial) const` | Returns `polynomial(points[i])` for every point. | $O(D \log D + N \log^2 N)$ |
| `interpolate(values) const` | Returns the polynomial of degree less than `N` whose value at `points[i]` is `values[i]`. | $O(N \log^2 N)$ |

If `D <= N`, evaluation simplifies to $O(N \log^2 N)$. The tree itself uses
$O(N \log N)$ memory. Evaluation and interpolation use
$O(N \log N + D)$ auxiliary memory.

`interpolate` requires `values.size() == size()` and pairwise distinct points.
For an empty point set, evaluation returns an empty vector and interpolation
returns an empty polynomial.

## Free Functions

```cpp
template <class Mint>
std::vector<Mint> multipoint_evaluate(
    const FormalPowerSeries<Mint>& polynomial,
    const std::vector<Mint>& points);

template <class Mint>
FormalPowerSeries<Mint> polynomial_interpolate(
    const std::vector<Mint>& points,
    const std::vector<Mint>& values);
```

Each free function constructs a temporary `SubproductTree` and performs the
corresponding operation. Their bounds are therefore:

| Function | Complexity |
| --- | --- |
| `multipoint_evaluate` | $O(D \log D + N \log^2 N)$ |
| `polynomial_interpolate` | $O(N \log^2 N)$ |

## Reusing a Subproduct Tree

```cpp
#include "math/fps/multipoint_evaluation.hpp"
#include "math/modint.hpp"

#include <cassert>
#include <vector>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    Fps f = {3, 1, 4};
    std::vector<mint> points = {0, 2, 5};

    m1une::fps::SubproductTree<mint> tree(points);
    std::vector<mint> values = tree.evaluate(f);

    assert(values[0] == mint(3));
    assert(values[1] == mint(21));
    assert(values[2] == mint(108));

    Fps restored = tree.interpolate(values);
    assert(restored == f);
}
```

## One-Shot Multipoint Evaluation

Use `multipoint_evaluate` when the points are needed for only one polynomial.

```cpp
#include "math/fps/multipoint_evaluation.hpp"
#include "math/modint.hpp"

#include <cassert>
#include <vector>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    // f(x) = 2x^3 - x + 5
    Fps f = {5, -1, 0, 2};
    std::vector<mint> points = {-2, 0, 3};

    std::vector<mint> values =
        m1une::fps::multipoint_evaluate(f, points);

    assert(values[0] == mint(-9));
    assert(values[1] == mint(5));
    assert(values[2] == mint(56));
}
```

## One-Shot Polynomial Interpolation

Use `polynomial_interpolate` to recover the unique polynomial of degree less
than the number of distinct points.

```cpp
#include "math/fps/multipoint_evaluation.hpp"
#include "math/modint.hpp"

#include <cassert>
#include <vector>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    // The points lie on f(x) = x^2 + 2x + 3.
    std::vector<mint> points = {-1, 0, 2};
    std::vector<mint> values = {2, 3, 11};

    Fps f = m1une::fps::polynomial_interpolate(points, values);

    Fps expected = {3, 2, 1};
    assert(f == expected);
}
```

## Empty Inputs

Both free functions accept an empty point set.

```cpp
#include "math/fps/multipoint_evaluation.hpp"
#include "math/modint.hpp"

#include <cassert>
#include <vector>

using mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<mint>;

int main() {
    Fps f = {1, 2, 3};
    std::vector<mint> points;
    std::vector<mint> values;

    assert(m1une::fps::multipoint_evaluate(f, points).empty());
    assert(m1une::fps::polynomial_interpolate(points, values).empty());
}
```
