#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include "../../../utilities/fast_io.hpp"

#include <bits/stdc++.h>
using namespace std;

#include "../../../ds/dsu/persistent_dsu.hpp"
using namespace m1une::ds;

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int N, Q;
    fast_input >> N >> Q;
    vector<PersistentDsu> dsus;
    dsus.push_back(PersistentDsu(N));
    while (Q--) {
        int t, k, u, v;
        fast_input >> t >> k >> u >> v;
        if (t == 0) {
            dsus.push_back(dsus[k + 1].merge(u, v));
        } else {
            fast_output << int(dsus[k + 1].same(u, v)) << '\n';
            dsus.push_back(PersistentDsu(0));
        }
    }
}
