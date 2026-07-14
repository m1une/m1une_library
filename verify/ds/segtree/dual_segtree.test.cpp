#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_point_get"

#include "../../../utilities/fast_io.hpp"

#include "../../../ds/segtree/dual_segtree.hpp"

#include <bits/stdc++.h>

#include "../../../math/modint.hpp"
#include "../../../monoid/affine.hpp"

using mint = m1une::math::modint998244353;
using Affine = m1une::monoid::Affine<mint>;

using namespace std;
using ll = long long;

void solve(
    m1une::utilities::FastInput& fast_input,
    m1une::utilities::FastOutput& fast_output
) {
    ll N, Q;
    fast_input >> N >> Q;
    vector<Affine::value_type> a(N);
    for (int i = 0; i < N; ++i) {
        ll x;
        fast_input >> x;
        a[i] = {0, x};
    }

    m1une::ds::DualSegtree<Affine> seg(a);
    assert(seg.size() == N);
    assert(seg.empty() == (N == 0));
    auto values = seg.to_vector();
    assert(int(values.size()) == N);
    for (int i = 0; i < N; i++) {
        assert(values[i].second == a[i].second);
    }
    for (int q = 0; q < Q; ++q) {
        ll t;
        fast_input >> t;
        if (t == 0) {
            ll l, r, b, c;
            fast_input >> l >> r >> b >> c;
            seg.apply(l, r, {b, c});
        } else {
            ll i;
            fast_input >> i;
            fast_output << seg.get(i).second << '\n';
        }
    }
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    solve(fast_input, fast_output);
    return 0;
}
