#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "../../../ds/segtree/segtree_beats.hpp"

#include <cassert>
#include "../../../utilities/fast_io.hpp"
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
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int n, q;
    fast_input >> n >> q;
    std::vector<long long> values(n);
    for (long long& value : values) fast_input >> value;

    m1une::ds::SegtreeBeats<RangeAffineRangeSumBeats> seg(values);
    assert(seg.size() == n);
    assert(seg.empty() == (n == 0));

    while (q--) {
        int type, left, right;
        fast_input >> type >> left >> right;
        if (type == 0) {
            long long b, c;
            fast_input >> b >> c;
            seg.apply(left, right, std::pair<mint, mint>(b, c));
        } else {
            fast_output << seg.prod(left, right).sum << '\n';
        }
    }
}
