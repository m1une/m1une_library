#define PROBLEM "https://judge.yosupo.jp/problem/general_matching"

#include "../../utilities/fast_io.hpp"

#include <bits/stdc++.h>
using namespace std;

#include "../../graph/graph.hpp"
#include "../../graph/general_matching.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int N, M;
    fast_input >> N >> M;
    m1une::graph::GeneralMatching gm(N);
    while (M--) {
        int u, v;
        fast_input >> u >> v;
        gm.add_edge(u, v);
    }
    fast_output << gm.max_matching() << '\n';
    for (auto p : gm.matching()) {
        fast_output << p.from << ' ' << p.to << '\n';
    }
}
