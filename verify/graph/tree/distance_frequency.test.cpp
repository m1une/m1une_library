#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"

#include "../../../graph/graph.hpp"
#include "../../../graph/tree/distance_frequency.hpp"

#include <cassert>
#include <cstdint>
#include "../../../utilities/fast_io.hpp"
#include <queue>
#include <vector>

namespace {

using Graph = m1une::graph::Graph<int>;

std::vector<long long> naive_distance_frequency(const Graph& tree) {
    const int size = tree.size();
    std::vector<long long> result(static_cast<std::size_t>(size));
    if (size == 0) return result;
    result[0] = size;
    for (int source = 0; source < size; source++) {
        std::vector<int> distance(static_cast<std::size_t>(size), -1);
        std::queue<int> queue;
        distance[static_cast<std::size_t>(source)] = 0;
        queue.push(source);
        while (!queue.empty()) {
            const int vertex = queue.front();
            queue.pop();
            for (const auto& edge : tree[vertex]) {
                if (!edge.alive || distance[static_cast<std::size_t>(edge.to)] != -1) {
                    continue;
                }
                distance[static_cast<std::size_t>(edge.to)] =
                    distance[static_cast<std::size_t>(vertex)] + 1;
                queue.push(edge.to);
            }
        }
        for (int target = source + 1; target < size; target++) {
            result[static_cast<std::size_t>(
                distance[static_cast<std::size_t>(target)]
            )]++;
        }
    }
    return result;
}

void test_edge_cases() {
    Graph empty;
    assert(m1une::tree::tree_distance_frequency(empty).empty());

    Graph single(1);
    std::vector<long long> one{1};
    assert(m1une::tree::tree_distance_frequency(single) == one);

    Graph path(100);
    for (int vertex = 1; vertex < 100; vertex++) {
        path.add_edge(vertex - 1, vertex);
    }
    const std::vector<long long> path_frequency =
        m1une::tree::tree_distance_frequency(path);
    for (int distance = 0; distance < 100; distance++) {
        assert(path_frequency[static_cast<std::size_t>(distance)] == 100 - distance);
    }

    Graph star(100);
    for (int vertex = 1; vertex < 100; vertex++) star.add_edge(0, vertex);
    const std::vector<long long> star_frequency =
        m1une::tree::tree_distance_frequency(star);
    assert(star_frequency[0] == 100);
    assert(star_frequency[1] == 99);
    assert(star_frequency[2] == 99LL * 98 / 2);
    for (int distance = 3; distance < 100; distance++) {
        assert(star_frequency[static_cast<std::size_t>(distance)] == 0);
    }
}

void test_randomized() {
    std::uint64_t state = 0xa93e72c16b40d5f8ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 500; trial++) {
        const int size = int(random() % 40) + 1;
        Graph tree(size);
        for (int vertex = 1; vertex < size; vertex++) {
            tree.add_edge(vertex, int(random() % std::uint64_t(vertex)));
        }
        assert(
            m1une::tree::tree_distance_frequency(tree) ==
            naive_distance_frequency(tree)
        );
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_edge_cases();
    test_randomized();

    int size;
    fast_input >> size;
    Graph tree(size);
    for (int edge = 0; edge + 1 < size; edge++) {
        int first, second;
        fast_input >> first >> second;
        tree.add_edge(first, second);
    }

    const std::vector<long long> frequency =
        m1une::tree::tree_distance_frequency(tree);
    for (int distance = 1; distance < size; distance++) {
        if (distance != 1) fast_output << ' ';
        fast_output << frequency[static_cast<std::size_t>(distance)];
    }
    fast_output << '\n';
}
