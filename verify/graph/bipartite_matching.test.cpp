#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include "../../utilities/fast_io.hpp"
#include <vector>

#include "../../graph/bipartite.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int left_size, right_size, edge_count;
    fast_input >> left_size >> right_size >> edge_count;
    m1une::graph::BipartiteMatching matching(left_size, right_size);
    for (int i = 0; i < edge_count; i++) {
        int left, right;
        fast_input >> left >> right;
        matching.add_edge(left, right);
    }

    std::vector<m1une::graph::BipartiteMatching::Pair> result =
        matching.matching();
    fast_output << result.size() << '\n';
    for (const auto& pair : result) {
        fast_output << pair.left << ' ' << pair.right << '\n';
    }
}
