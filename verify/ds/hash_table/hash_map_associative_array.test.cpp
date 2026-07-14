#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include "../../../utilities/fast_io.hpp"

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include "../../../ds/hash_table/hash_map.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int Q;
    fast_input >> Q;
    m1une::ds::HashMap<ll, ll> mp;
    while (Q--) {
        int t;
        fast_input >> t;
        if (t == 0) {
            ll k, v;
            fast_input >> k >> v;
            mp[k] = v;
        } else {
            ll k;
            fast_input >> k;
            fast_output << mp[k] << '\n';
        }
    }
}
