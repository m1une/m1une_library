#define PROBLEM "https://judge.yosupo.jp/problem/chromatic_number"

#include <iostream>

#include "../../graph/chromatic_number.hpp"
#include "../../graph/graph.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;
    m1une::graph::Graph<> g(n);
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }
    std::cout << m1une::graph::chromatic_number(g) << '\n';
}
