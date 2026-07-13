#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <iostream>
#include <vector>

#include "../../graph/bipartite.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int left_size, right_size, edge_count;
    std::cin >> left_size >> right_size >> edge_count;
    m1une::graph::BipartiteMatching matching(left_size, right_size);
    for (int i = 0; i < edge_count; i++) {
        int left, right;
        std::cin >> left >> right;
        matching.add_edge(left, right);
    }

    std::vector<m1une::graph::BipartiteMatching::Pair> result =
        matching.matching();
    std::cout << result.size() << '\n';
    for (const auto& pair : result) {
        std::cout << pair.left << ' ' << pair.right << '\n';
    }
}
