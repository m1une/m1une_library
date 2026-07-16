#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_cliques"

#include "../../graph/enumerate_cliques.hpp"
#include "../../graph/graph.hpp"
#include "../../utilities/fast_io.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

namespace {

void test_randomized() {
    std::uint64_t state = 0x6a09e667f3bcc909ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 400; trial++) {
        int vertex_count = int(random() % 13);
        m1une::graph::Graph<> graph(vertex_count);
        std::vector<std::vector<char>> adjacent(
            vertex_count,
            std::vector<char>(vertex_count, false)
        );
        for (int first = 0; first < vertex_count; first++) {
            for (int second = first + 1; second < vertex_count; second++) {
                if (random() % 3 != 0) continue;
                int edge_id;
                if (random() % 2 == 0) {
                    edge_id = graph.add_edge(first, second);
                } else if (random() % 2 == 0) {
                    edge_id = graph.add_directed_edge(first, second);
                } else {
                    edge_id = graph.add_directed_edge(second, first);
                }
                if (random() % 7 == 0) {
                    graph.erase_edge(edge_id);
                } else {
                    adjacent[first][second] = true;
                    adjacent[second][first] = true;
                }
            }
        }

        std::vector<std::vector<int>> actual;
        m1une::graph::enumerate_cliques(
            graph,
            [&](const std::vector<int>& clique) {
                assert(!clique.empty());
                std::vector<int> canonical = clique;
                std::sort(canonical.begin(), canonical.end());
                assert(
                    std::adjacent_find(canonical.begin(), canonical.end()) ==
                    canonical.end()
                );
                actual.push_back(std::move(canonical));
            }
        );
        std::sort(actual.begin(), actual.end());

        std::vector<std::vector<int>> expected;
        for (int mask = 1; mask < (1 << vertex_count); mask++) {
            std::vector<int> clique;
            bool valid = true;
            for (int first = 0; first < vertex_count; first++) {
                if (((mask >> first) & 1) == 0) continue;
                clique.push_back(first);
                for (int second = first + 1; second < vertex_count; second++) {
                    if (((mask >> second) & 1) != 0 &&
                        !adjacent[first][second]) {
                        valid = false;
                    }
                }
            }
            if (valid) expected.push_back(std::move(clique));
        }
        std::sort(expected.begin(), expected.end());
        assert(actual == expected);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_randomized();

    int vertex_count = 0;
    int edge_count = 0;
    fast_input >> vertex_count >> edge_count;
    constexpr long long modulus = 998'244'353;
    std::vector<long long> value(vertex_count);
    for (long long& x : value) fast_input >> x;

    m1une::graph::Graph<> graph(vertex_count);
    for (int edge = 0; edge < edge_count; edge++) {
        int first = 0;
        int second = 0;
        fast_input >> first >> second;
        graph.add_edge(first, second);
    }

    long long answer = 0;
    m1une::graph::enumerate_cliques(
        graph,
        [&](const std::vector<int>& clique) {
            long long product = 1;
            for (int vertex : clique) {
                product = product * value[vertex] % modulus;
            }
            answer += product;
            if (answer >= modulus) answer -= modulus;
        }
    );
    fast_output << answer << '\n';
}
