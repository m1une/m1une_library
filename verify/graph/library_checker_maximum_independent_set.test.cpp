#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"

#include "../../utilities/fast_io.hpp"

#include <bits/stdc++.h>
using namespace std;

#include "../../graph/graph.hpp"
#include "../../graph/maximum_clique.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int N, M;
    fast_input >> N >> M;
    m1une::graph::Graph<> g(N);
    while (M--) {
        int u, v;
        fast_input >> u >> v;
        g.add_edge(u, v);
    }
    auto independent = m1une::graph::maximum_independent_set(g);
    fast_output << independent.size() << '\n';
    for (int x : independent.vertices) {
        fast_output << x << ' ';
    }
    fast_output << '\n';
}
