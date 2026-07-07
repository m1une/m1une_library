#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

#include "../../graph/counting.hpp"
#include "../../math/modint.hpp"

using mint = m1une::math::modint998244353;

void assert_prefix(const std::vector<mint>& actual, const std::vector<long long>& expected) {
    assert(int(actual.size()) >= int(expected.size()));
    for (int i = 0; i < int(expected.size()); i++) {
        assert(actual[i] == mint(expected[i]));
    }
}

struct Dsu {
    std::vector<int> parent;

    explicit Dsu(int n) : parent(n) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int leader(int v) {
        if (parent[v] == v) return v;
        return parent[v] = leader(parent[v]);
    }

    bool merge(int a, int b) {
        a = leader(a);
        b = leader(b);
        if (a == b) return false;
        parent[b] = a;
        return true;
    }
};

struct UndirectedBrute {
    long long all = 0;
    long long connected = 0;
    long long tree = 0;
    long long forest = 0;
    long long unicyclic_connected = 0;
    long long connected_eulerian = 0;
    long long bipartite = 0;
    long long connected_bipartite = 0;
};

bool is_bipartite(int n, const std::vector<std::vector<int>>& adjacency) {
    std::vector<int> color(n, -1);
    for (int start = 0; start < n; start++) {
        if (color[start] != -1) continue;
        color[start] = 0;
        std::vector<int> stack;
        stack.push_back(start);
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            for (int to : adjacency[v]) {
                if (color[to] == -1) {
                    color[to] = color[v] ^ 1;
                    stack.push_back(to);
                } else if (color[to] == color[v]) {
                    return false;
                }
            }
        }
    }
    return true;
}

UndirectedBrute brute_undirected(int n) {
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) edges.emplace_back(i, j);
    }

    UndirectedBrute result;
    const int total = 1 << int(edges.size());
    for (int mask = 0; mask < total; mask++) {
        result.all++;

        Dsu dsu(n);
        std::vector<int> degree(n);
        std::vector<std::vector<int>> adjacency(n);
        bool acyclic = true;
        int edge_count = 0;
        for (int bit = 0; bit < int(edges.size()); bit++) {
            if (((mask >> bit) & 1) == 0) continue;
            const auto [u, v] = edges[bit];
            edge_count++;
            degree[u]++;
            degree[v]++;
            adjacency[u].push_back(v);
            adjacency[v].push_back(u);
            if (!dsu.merge(u, v)) acyclic = false;
        }

        int components = n;
        for (int i = 0; i < n; i++) {
            if (dsu.leader(i) != i) components--;
        }
        const bool connected = n > 0 && components == 1;
        const bool bipartite = is_bipartite(n, adjacency);
        const bool all_even =
            std::all_of(degree.begin(), degree.end(), [](int x) { return x % 2 == 0; });

        if (connected) result.connected++;
        if (n > 0 && connected && edge_count == n - 1) result.tree++;
        if (acyclic) result.forest++;
        if (connected && edge_count == n) result.unicyclic_connected++;
        if (connected && all_even) result.connected_eulerian++;
        if (bipartite) result.bipartite++;
        if (connected && bipartite) result.connected_bipartite++;
    }
    return result;
}

struct DirectedBrute {
    long long all = 0;
    long long dag = 0;
    long long strongly_connected = 0;
};

DirectedBrute brute_directed(int n) {
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) edges.emplace_back(i, j);
        }
    }

    DirectedBrute result;
    const int total = 1 << int(edges.size());
    for (int mask = 0; mask < total; mask++) {
        result.all++;
        std::vector<std::vector<int>> reach(n, std::vector<int>(n));
        for (int bit = 0; bit < int(edges.size()); bit++) {
            if (((mask >> bit) & 1) == 0) continue;
            const auto [from, to] = edges[bit];
            reach[from][to] = 1;
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                if (!reach[i][k]) continue;
                for (int j = 0; j < n; j++) reach[i][j] = reach[i][j] || reach[k][j];
            }
        }

        bool dag = true;
        for (int i = 0; i < n; i++) dag = dag && !reach[i][i];

        bool strongly_connected = n > 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && !reach[i][j]) strongly_connected = false;
            }
        }

        if (dag) result.dag++;
        if (strongly_connected) result.strongly_connected++;
    }
    return result;
}

struct TournamentBrute {
    long long all = 0;
    long long strongly_connected = 0;
};

TournamentBrute brute_tournament(int n) {
    std::vector<std::pair<int, int>> pairs;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) pairs.emplace_back(i, j);
    }

    TournamentBrute result;
    const int total = 1 << int(pairs.size());
    for (int mask = 0; mask < total; mask++) {
        result.all++;
        std::vector<std::vector<int>> reach(n, std::vector<int>(n));
        for (int bit = 0; bit < int(pairs.size()); bit++) {
            const auto [u, v] = pairs[bit];
            if ((mask >> bit) & 1) {
                reach[u][v] = 1;
            } else {
                reach[v][u] = 1;
            }
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                if (!reach[i][k]) continue;
                for (int j = 0; j < n; j++) reach[i][j] = reach[i][j] || reach[k][j];
            }
        }

        bool strongly_connected = n > 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && !reach[i][j]) strongly_connected = false;
            }
        }
        if (strongly_connected) result.strongly_connected++;
    }
    return result;
}

void test_undirected_counts() {
    const int maximum = 5;
    const auto all = m1une::graph::count_labeled_undirected_graphs<mint>(maximum);
    const auto connected = m1une::graph::count_labeled_connected_graphs<mint>(maximum);
    const auto trees = m1une::graph::count_labeled_trees<mint>(maximum);
    const auto forests = m1une::graph::count_labeled_forests<mint>(maximum);
    const auto unicyclic =
        m1une::graph::count_labeled_unicyclic_connected_graphs<mint>(maximum);
    const auto eulerian =
        m1une::graph::count_labeled_connected_eulerian_graphs<mint>(maximum);
    const auto bipartite = m1une::graph::count_labeled_bipartite_graphs<mint>(maximum);
    const auto connected_bipartite =
        m1une::graph::count_labeled_connected_bipartite_graphs<mint>(maximum);

    for (int n = 0; n <= maximum; n++) {
        const UndirectedBrute brute = brute_undirected(n);
        assert(all[n] == mint(brute.all));
        assert(connected[n] == mint(brute.connected));
        assert(trees[n] == mint(brute.tree));
        assert(forests[n] == mint(brute.forest));
        assert(unicyclic[n] == mint(brute.unicyclic_connected));
        assert(eulerian[n] == mint(brute.connected_eulerian));
        assert(bipartite[n] == mint(brute.bipartite));
        assert(connected_bipartite[n] == mint(brute.connected_bipartite));
    }

    assert_prefix(connected, std::vector<long long>{0, 1, 1, 4, 38, 728});
    assert_prefix(forests, std::vector<long long>{1, 1, 2, 7, 38, 291});
    assert_prefix(unicyclic, std::vector<long long>{0, 0, 0, 1, 15, 222});
    assert_prefix(eulerian, std::vector<long long>{0, 1, 0, 1, 3, 38});
    assert_prefix(bipartite, std::vector<long long>{1, 1, 2, 7, 41, 376});
    assert_prefix(connected_bipartite, std::vector<long long>{0, 1, 1, 3, 19, 195});
}

void test_directed_counts() {
    const int maximum = 4;
    const auto all = m1une::graph::count_labeled_directed_graphs<mint>(maximum);
    const auto dags = m1une::graph::count_labeled_dags<mint>(maximum);
    const auto strongly_connected =
        m1une::graph::count_labeled_strongly_connected_digraphs<mint>(maximum);

    for (int n = 0; n <= maximum; n++) {
        const DirectedBrute brute = brute_directed(n);
        assert(all[n] == mint(brute.all));
        assert(dags[n] == mint(brute.dag));
        assert(strongly_connected[n] == mint(brute.strongly_connected));
    }

    assert_prefix(all, std::vector<long long>{1, 1, 4, 64, 4096});
    assert_prefix(dags, std::vector<long long>{1, 1, 3, 25, 543});
    assert_prefix(strongly_connected, std::vector<long long>{0, 1, 1, 18, 1606});
}

void test_tournament_counts() {
    const int maximum = 5;
    const auto all = m1une::graph::count_labeled_tournaments<mint>(maximum);
    const auto strongly_connected =
        m1une::graph::count_labeled_strongly_connected_tournaments<mint>(maximum);

    for (int n = 0; n <= maximum; n++) {
        const TournamentBrute brute = brute_tournament(n);
        assert(all[n] == mint(brute.all));
        assert(strongly_connected[n] == mint(brute.strongly_connected));
    }

    assert_prefix(all, std::vector<long long>{1, 1, 2, 8, 64, 1024});
    assert_prefix(strongly_connected, std::vector<long long>{0, 1, 0, 2, 24, 544});
}

void test_unlabeled_trees() {
    const auto rooted = m1une::graph::count_unlabeled_rooted_trees<mint>(12);
    const auto unrooted = m1une::graph::count_unlabeled_trees<mint>(12);

    assert_prefix(rooted, std::vector<long long>{0, 1, 1, 2, 4, 9, 20, 48, 115});
    assert_prefix(unrooted, std::vector<long long>{0, 1, 1, 1, 2, 3, 6, 11, 23, 47, 106});
}

int main() {
    test_undirected_counts();
    test_directed_counts();
    test_tournament_counts();
    test_unlabeled_trees();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
    return 0;
}

