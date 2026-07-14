#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../../../ds/segtree/segtree.hpp"
#include "../../../monoid/add.hpp"
#include <cassert>
#include "../../../utilities/fast_io.hpp"
#include <vector>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int n, q;
    fast_input >> n >> q;

    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        fast_input >> a[i];
    }

    m1une::ds::Segtree<m1une::monoid::Add<long long>> seg(a);
    assert(seg.size() == n);
    assert(seg.empty() == (n == 0));
    assert(seg.to_vector() == a);
    for (int i = 0; i < n; i++) assert(seg[i] == a[i]);

    for (int i = 0; i < q; i++) {
        int type;
        fast_input >> type;
        if (type == 0) {
            int p;
            long long x;
            fast_input >> p >> x;
            seg.set(p, seg.get(p) + x);
        } else {
            int l, r;
            fast_input >> l >> r;
            fast_output << seg.prod(l, r) << "\n";
        }
    }

    return 0;
}
