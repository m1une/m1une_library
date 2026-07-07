#ifndef M1UNE_ALGO_OFFLINE_CDQ_DIVIDE_AND_CONQUER_HPP
#define M1UNE_ALGO_OFFLINE_CDQ_DIVIDE_AND_CONQUER_HPP 1

#include <cassert>

namespace m1une {
namespace algo {

template <class SolveCross>
void cdq_divide_and_conquer(int left, int right, SolveCross solve_cross) {
    assert(left <= right);

    auto dfs = [&](auto& self, int l, int r) -> void {
        if (r - l <= 1) return;
        const int middle = l + (r - l) / 2;
        self(self, l, middle);
        self(self, middle, r);
        solve_cross(l, middle, r);
    };
    dfs(dfs, left, right);
}

template <class SolveCross>
void cdq_divide_and_conquer(int n, SolveCross solve_cross) {
    assert(0 <= n);
    cdq_divide_and_conquer(0, n, solve_cross);
}

}  // namespace algo
}  // namespace m1une

#endif  // M1UNE_ALGO_OFFLINE_CDQ_DIVIDE_AND_CONQUER_HPP
