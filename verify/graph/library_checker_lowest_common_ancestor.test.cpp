#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../../utilities/fast_io.hpp"

#include <bits/stdc++.h>
using namespace std;

#include "../../graph/graph.hpp"
#include "../../graph/tree/sparse_table_lca.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int N, Q;
    fast_input >> N >> Q;
    m1une::graph::Graph<> g(N);
    for (int i = 1; i < N; ++i) {
        int p;
        fast_input >> p;
        g.add_edge(p, i);
    }
    m1une::tree::SparseTableLca<> lca(g, 0);
    while (Q--) {
        int u, v;
        fast_input >> u >> v;
        fast_output << lca.lca(u, v) << '\n';
    }
}
