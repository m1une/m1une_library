---
title: Finalized-Layer Matrix Transitions
documentation_of: ../../convex/monge_transition.hpp
---

Compute the **offline** rectangular recurrence
$g[j]=\min_i(f[i]+C(i,j))$, where every `f[i]` is already finalized.
All source-target pairs exist and have finite costs. `cost(source,target)`
returns only `C`; the helper adds `previous[source]`. Rows are targets and
columns are sources. Source constants preserve Monge but do not necessarily
preserve mere argmin monotonicity.

All APIs use `m1une::convex`. `R` below denotes
`std::decay_t<decltype(previous[0] + cost(0,0))>`. The actual return signatures
use `auto`, deduced as `MatrixTransitionResult<R>`. `R` must be default
constructible and support comparison; addition must be defined with `T` and
the cost type. Values are ordinary finite values, without sentinel semantics;
intermediate sums must fit. Callbacks must be fixed and may be evaluated in
any order. Inputs are not modified.

## Interface

Let `H` be the target count and `W` the source count.

| Exact signature (deduced return type as above) | Required property | Time |
| --- | --- | --- |
| `template<class T, class Cost> auto monotone_transition(const std::vector<T>& previous, int state_count, Cost cost)` | Leftmost minimizing sources of the **full matrix including previous** are nondecreasing. | $O(H+W\log(H+1))$ |
| `template<class T, class Cost> auto monotone_transition(const std::vector<T>& previous, std::span<const int> targets, std::span<const int> sources, Cost cost)` | Same property in supplied target/source orders. | $O(H+W\log(H+1))$ |
| `template<class T, class Cost> auto monge_transition(const std::vector<T>& previous, int state_count, Cost cost)` | `cost(source,target)` is Monge in natural orders. | $O(H+W)$ |
| `template<class T, class Cost> auto monge_transition(const std::vector<T>& previous, std::span<const int> targets, std::span<const int> sources, Cost cost)` | `cost(sources[c],targets[r])` is Monge in those orders. | $O(H+W)$ |
| `template<class T, class Cost> auto anti_monge_transition(const std::vector<T>& previous, int state_count, Cost cost)` | Anti-Monge in natural orders; reverses sources internally. | $O(H+W)$ |

Total monotonicity of the full matrix is a weaker sufficient condition for
either SMAWK-based function. `monotone_transition` needs only whole-matrix
argmin monotonicity and uses monotone minima internally. `state_count >= 0`.
When the cost is known to be Monge or anti-Monge, prefer `monge_transition`
or `anti_monge_transition` for the linear bound. Use `monotone_transition`
when only monotonicity of the full transition matrix's minimizing sources is
established; it does not infer a stronger property or automatically use SMAWK.
Ordered lists contain distinct nonnegative IDs, with every source indexing
`previous`; source bounds and target nonnegativity are asserted. Subsets and
permutations are both allowed. No ordering is inferred or sorted.

SMAWK versions use $O(H+W)$ memory including results. The monotone versions
use $O(H+\log(H+1))$ memory. Ordered argument validation adds $O(H+W)$ time,
including the degenerate empty-target case. All times assume constant-time
costs, addition, and comparison.

`MatrixTransitionResult<R>` has `std::vector<R> value` and
`std::vector<int> argmin`. Results are compact in target order; `argmin` holds
original source IDs. Ties choose the first supplied source, the smallest
natural source for the count-based Monge/monotone calls, and the largest
natural source for the anti-Monge call. Empty source lists yield `argmin=-1`
and `value=R()` (a placeholder, **not** an optimum or infinity). Empty target
lists return empty vectors. Always inspect `argmin` before using a value when
sources may be empty.

## Example

```cpp
#include "convex/monge_transition.hpp"
#include <cassert>
#include <vector>

int main() {
    std::vector<long long> previous = {7, 1, 9};
    auto result = m1une::convex::monge_transition(previous, 4, [](int i, int j) {
        return (i-j)*1LL*(i-j);
    });
    assert(result.value == std::vector<long long>({2, 1, 2, 5}));
    auto anti = m1une::convex::anti_monge_transition(previous, 4, [](int i, int j) {
        return -(i-j)*1LL*(i-j);
    });
    assert(anti.value == std::vector<long long>({0, 1, 0, -3}));

    std::vector<int> targets = {0, 1, 2, 3};
    std::vector<int> sources = {2, 1, 0};
    auto ordered = m1une::convex::monge_transition(previous, targets, sources,
        [](int i, int j) { return -(i-j)*1LL*(i-j); });
    assert(ordered.value == anti.value && ordered.argmin == anti.argmin);
}
```

The direct anti-Monge call requires no user permutation. The ordered example
shows its relationship to the general abstraction. More complicated known
orders use the same list overload. Arbitrary partial or triangular validity
masks are not accepted; for `dp[j]` depending on its own earlier entries use
[Monge shortest paths](https://m1une.github.io/m1une_library/convex/monge_shortest_path.hpp).
