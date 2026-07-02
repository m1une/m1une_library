#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "../../../ds/segtree/segtree_beats.hpp"

#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

#include "../../../acted_monoid/range_affine_range_sum.hpp"
#include "../../../math/modint.hpp"

using mint = m1une::math::modint998244353;

struct RangeAffineRangeSumBeats
    : m1une::acted_monoid::RangeAffineRangeSum<mint> {
    static bool can_apply(
        const operator_type&,
        const value_type&
    ) {
        return true;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<long long> values(n);
    for (long long& value : values) std::cin >> value;

    m1une::ds::SegtreeBeats<RangeAffineRangeSumBeats> seg(values);
    assert(seg.size() == n);
    assert(seg.empty() == (n == 0));

    while (q--) {
        int type, left, right;
        std::cin >> type >> left >> right;
        if (type == 0) {
            long long b, c;
            std::cin >> b >> c;
            seg.apply(left, right, std::pair<mint, mint>(b, c));
        } else {
            std::cout << seg.prod(left, right).sum << '\n';
        }
    }
}
