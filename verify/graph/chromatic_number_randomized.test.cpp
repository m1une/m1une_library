#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include "../../utilities/fast_io.hpp"
#include <random>
#include <vector>

#include "../../graph/chromatic_number.hpp"
#include "../../graph/graph.hpp"

int naive_chromatic_number(const std::vector<std::vector<char>>& adjacent) {
    int n = int(adjacent.size());
    if (n == 0) return 0;
    std::vector<int> color(n, -1);
    auto colorable = [&](auto&& self, int v, int colors) -> bool {
        if (v == n) return true;
        for (int c = 0; c < colors; c++) {
            bool ok = true;
            for (int u = 0; u < v; u++) {
                if (adjacent[v][u] && color[u] == c) ok = false;
            }
            if (!ok) continue;
            color[v] = c;
            if (self(self, v + 1, colors)) return true;
            color[v] = -1;
        }
        return false;
    };
    for (int colors = 1; colors <= n; colors++) {
        if (colorable(colorable, 0, colors)) return colors;
    }
    return n;
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    {
        m1une::graph::Graph<> cycle(5);
        for (int v = 0; v < 5; v++) cycle.add_directed_edge(v, (v + 1) % 5);
        int removed = cycle.add_edge(0, 2);
        cycle.erase_edge(removed);
        cycle.add_edge(3, 3);
        assert(m1une::graph::chromatic_number(cycle) == 3);
    }

    std::mt19937 rng(123456789);
    for (int n = 0; n <= 9; n++) {
        for (int iteration = 0; iteration < 300; iteration++) {
            m1une::graph::Graph<> g(n);
            std::vector<std::vector<char>> adjacent(n, std::vector<char>(n, false));
            for (int u = 0; u < n; u++) {
                for (int v = u + 1; v < n; v++) {
                    if ((rng() & 3) == 0) {
                        g.add_edge(u, v);
                        adjacent[u][v] = adjacent[v][u] = true;
                    }
                }
            }
            assert(m1une::graph::chromatic_number(g) == naive_chromatic_number(adjacent));
        }
    }

    int a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
