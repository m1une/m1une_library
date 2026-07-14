#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_triangles"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <vector>

#include "../../graph/enumerate_triangles.hpp"
#include "../../graph/graph.hpp"

namespace {

void test_randomized() {
    std::uint64_t state = 0x123456789abcdef0ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int test = 0; test < 300; test++) {
        const int n = 1 + int(random() % 16);
        m1une::graph::Graph<> graph(n);
        std::vector<std::vector<char>> adjacent(n, std::vector<char>(n, false));
        for (int first = 0; first < n; first++) {
            for (int second = first + 1; second < n; second++) {
                if (random() % 4 != 0) continue;
                const int edge = random() % 2 == 0
                                     ? graph.add_edge(first, second)
                                     : graph.add_directed_edge(first, second);
                if (random() % 7 == 0) {
                    graph.erase_edge(edge);
                } else {
                    adjacent[first][second] = true;
                    adjacent[second][first] = true;
                }
            }
        }

        std::vector<std::array<int, 3>> actual;
        m1une::graph::enumerate_triangles(
            graph,
            [&](int first, int second, int third) {
                assert(first < second && second < third);
                std::array<int, 3> triangle;
                triangle[0] = first;
                triangle[1] = second;
                triangle[2] = third;
                actual.push_back(triangle);
            }
        );
        std::sort(actual.begin(), actual.end());

        std::vector<std::array<int, 3>> expected;
        for (int first = 0; first < n; first++) {
            for (int second = first + 1; second < n; second++) {
                for (int third = second + 1; third < n; third++) {
                    if (!adjacent[first][second] ||
                        !adjacent[first][third] ||
                        !adjacent[second][third]) {
                        continue;
                    }
                    std::array<int, 3> triangle;
                    triangle[0] = first;
                    triangle[1] = second;
                    triangle[2] = third;
                    expected.push_back(triangle);
                }
            }
        }
        assert(actual == expected);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_randomized();
    int vertex_count, edge_count;
    fast_input >> vertex_count >> edge_count;
    std::vector<long long> value(vertex_count);
    for (long long& x : value) fast_input >> x;

    m1une::graph::Graph<> graph(vertex_count);
    for (int i = 0; i < edge_count; i++) {
        int first, second;
        fast_input >> first >> second;
        graph.add_edge(first, second);
    }

    constexpr long long modulus = 998'244'353;
    long long answer = 0;
    m1une::graph::enumerate_triangles(
        graph,
        [&](int first, int second, int third) {
            const long long product =
                value[first] * value[second] % modulus * value[third] % modulus;
            answer += product;
            if (answer >= modulus) answer -= modulus;
        }
    );
    fast_output << answer << '\n';
}
