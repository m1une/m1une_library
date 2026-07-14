#define PROBLEM "https://judge.yosupo.jp/problem/chromatic_number"

#include "../../utilities/fast_io.hpp"

#include "../../graph/chromatic_number.hpp"
#include "../../graph/graph.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int n, m;
    fast_input >> n >> m;
    m1une::graph::Graph<> g(n);
    while (m--) {
        int u, v;
        fast_input >> u >> v;
        g.add_edge(u, v);
    }
    fast_output << m1une::graph::chromatic_number(g) << '\n';
}
