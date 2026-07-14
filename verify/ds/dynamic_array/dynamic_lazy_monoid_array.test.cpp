#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

#include "../../../utilities/fast_io.hpp"

#include <bits/stdc++.h>
using namespace std;

#include "../../../acted_monoid/range_affine_range_sum.hpp"
#include "../../../ds/dynamic_array/dynamic_lazy_monoid_array.hpp"
#include "../../../math/modint.hpp"

using mint = m1une::math::modint998244353;
using AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;
using Array = m1une::ds::DynamicLazyMonoidArray<AM>;

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int N, Q;
    fast_input >> N >> Q;
    vector<int> a(N);
    for (int i = 0; i < N; ++i) fast_input >> a[i];
    Array ary(a);
    while (Q--) {
        int t;
        fast_input >> t;
        if (t == 0) {
            int i, x;
            fast_input >> i >> x;
            ary.insert(i, AM::make(x));
        } else if (t == 1) {
            int i;
            fast_input >> i;
            ary.erase(i);
        } else if (t == 2) {
            int l, r;
            fast_input >> l >> r;
            ary.reverse(l, r);
        } else if (t == 3) {
            int l, r, b, c;
            fast_input >> l >> r >> b >> c;
            ary.apply(l, r, {b, c});
        } else {
            int l, r;
            fast_input >> l >> r;
            fast_output << ary.prod(l, r).sum << '\n';
        }
    }
}
