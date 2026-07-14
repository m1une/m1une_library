#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "../../utilities/fast_io.hpp"

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#include "math/prime_factorization.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int Q;
    fast_input >> Q;
    while (Q--) {
        ll a;
        fast_input >> a;
        auto pf = m1une::math::prime_factors(a);
        fast_output << pf.size();
        for (ll p : pf) {
            fast_output << ' ' << p;
        }
        fast_output << '\n';
    }
}
