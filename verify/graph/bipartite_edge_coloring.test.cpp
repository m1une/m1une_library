#define PROBLEM "https://judge.yosupo.jp/problem/bipartite_edge_coloring"

#include "../../graph/bipartite.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <utility>
#include <vector>

namespace {

void check(
    int left_size,
    int right_size,
    const std::vector<std::pair<int, int>>& edges
) {
    std::vector<int> left_degree(left_size, 0);
    std::vector<int> right_degree(right_size, 0);
    int maximum_degree = 0;
    for (auto [left, right] : edges) {
        left_degree[left]++;
        right_degree[right]++;
        maximum_degree = std::max(maximum_degree, left_degree[left]);
        maximum_degree = std::max(maximum_degree, right_degree[right]);
    }

    auto result = m1une::graph::bipartite_edge_coloring(left_size, right_size, edges);
    assert(result.color_count == maximum_degree);
    assert(result.color.size() == edges.size());
    std::vector<std::vector<char>> left_used(
        left_size,
        std::vector<char>(maximum_degree, false)
    );
    std::vector<std::vector<char>> right_used(
        right_size,
        std::vector<char>(maximum_degree, false)
    );
    for (int edge = 0; edge < int(edges.size()); edge++) {
        auto [left, right] = edges[edge];
        int color = result.color[edge];
        assert(0 <= color && color < maximum_degree);
        assert(!left_used[left][color]);
        assert(!right_used[right][color]);
        left_used[left][color] = true;
        right_used[right][color] = true;
    }
}

void test_fixed() {
    check(0, 0, std::vector<std::pair<int, int>>());

    std::vector<std::pair<int, int>> star;
    for (int right = 0; right < 20; right++) star.emplace_back(0, right);
    check(1, 20, star);

    std::vector<std::pair<int, int>> parallel;
    for (int edge = 0; edge < 15; edge++) parallel.emplace_back(0, 0);
    check(1, 1, parallel);

    std::vector<std::pair<int, int>> complete;
    for (int left = 0; left < 7; left++) {
        for (int right = 0; right < 7; right++) complete.emplace_back(left, right);
    }
    check(7, 7, complete);
}

void test_randomized() {
    std::uint64_t state = 393393;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 3000; trial++) {
        int left_size = 1 + int(random() % 10);
        int right_size = 1 + int(random() % 10);
        int edge_count = int(random() % 50);
        std::vector<std::pair<int, int>> edges;
        edges.reserve(edge_count);
        for (int edge = 0; edge < edge_count; edge++) {
            edges.emplace_back(
                int(random() % left_size),
                int(random() % right_size)
            );
        }
        check(left_size, right_size, edges);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_fixed();
    test_randomized();
    int left_size, right_size, edge_count;
    fast_input >> left_size >> right_size >> edge_count;
    std::vector<std::pair<int, int>> edges(edge_count);
    for (auto& [left, right] : edges) fast_input >> left >> right;

    auto result = m1une::graph::bipartite_edge_coloring(left_size, right_size, edges);
    fast_output << result.color_count << '\n';
    for (int color : result.color) fast_output << color << '\n';
}
