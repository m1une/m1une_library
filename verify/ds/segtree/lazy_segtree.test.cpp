#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "../../../utilities/fast_io.hpp"

#include "../../../ds/segtree/lazy_segtree.hpp"

#include <bits/stdc++.h>

#include "../../../acted_monoid/range_affine_range_sum.hpp"
#include "../../../math/modint.hpp"

using mint = m1une::math::modint998244353;

using AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;

using namespace std;
using ll = long long;

void solve(
    m1une::utilities::FastInput& fast_input,
    m1une::utilities::FastOutput& fast_output
) {
    ll N, Q;
    fast_input >> N >> Q;
    vector<ll> a(N);
    for (int i = 0; i < N; ++i) fast_input >> a[i];

    m1une::ds::LazySegtree<AM> seg(a);
    assert(seg.size() == N);
    assert(seg.empty() == (N == 0));
    auto values = seg.to_vector();
    assert(int(values.size()) == N);
    for (int i = 0; i < N; i++) {
        assert(values[i].sum == mint(a[i]));
        assert(seg[i].sum == mint(a[i]));
    }
    for (int q = 0; q < Q; ++q) {
        ll t;
        fast_input >> t;
        if (t == 0) {
            ll l, r, b, c;
            fast_input >> l >> r >> b >> c;
            seg.apply(l, r, {b, c});
        } else {
            ll l, r;
            fast_input >> l >> r;
            auto prd = seg.prod(l, r);
            fast_output << prd.sum << '\n';
        }
    }
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    solve(fast_input, fast_output);
    return 0;
}
