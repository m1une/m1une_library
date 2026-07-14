#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_B"

#include "../../../utilities/fast_io.hpp"

#include <bits/stdc++.h>
using namespace std;

#include "../../../ds/dynamic_array/dynamic_monoid_array.hpp"
#include "../../../monoid/add.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int n, q;
    fast_input >> n >> q;
    using Monoid = m1une::monoid::Add<int>;
    using Array = m1une::ds::DynamicMonoidArray<Monoid>;
    Array a(n);
    while (q--) {
        int com, x, y;
        fast_input >> com >> x >> y;
        if (com == 0) {
            --x;
            a.set(x, a.get(x) + y);
        } else {
            --x;
            fast_output << a.prod(x, y) << '\n';
        }
    }
}
