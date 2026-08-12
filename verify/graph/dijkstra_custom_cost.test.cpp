#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <vector>

#include "../../graph/dijkstra.hpp"
#include "../../graph/graph.hpp"

struct Cost {
    long long value = 0;

    Cost operator+(const Cost& other) const {
        return Cost{value + other.value};
    }

    friend bool operator<(const Cost& first, const Cost& second) {
        return first.value < second.value;
    }
};

void test_custom_cost() {
    m1une::graph::Graph<Cost> graph(6);
    graph.add_directed_edge(0, 1, Cost{8});
    graph.add_directed_edge(0, 2, Cost{2});
    graph.add_directed_edge(2, 1, Cost{3});
    graph.add_directed_edge(1, 3, Cost{4});
    graph.add_directed_edge(2, 3, Cost{20});
    graph.add_directed_edge(4, 3, Cost{1});

    auto result = m1une::graph::dijkstra(graph, 0);
    assert(result.reachable(0));
    assert(result.reachable(3));
    assert(!result.reachable(4));
    assert(!result.reachable(5));
    assert(result.dist[0].value == 0);
    assert(result.dist[1].value == 5);
    assert(result.dist[3].value == 9);
    assert((result.path(3) == std::vector<int>{0, 2, 1, 3}));

    auto multi = m1une::graph::dijkstra(
        graph, std::vector<int>{0, 4, 0});
    assert(multi.reachable(4));
    assert(multi.dist[3].value == 1);
    assert((multi.path(3) == std::vector<int>{4, 3}));
}

void test_explicit_sentinel_is_not_reachability() {
    m1une::graph::Graph<Cost> graph(3);
    graph.add_directed_edge(0, 1, Cost{99});

    auto result = m1une::graph::dijkstra(graph, 0, Cost{99});
    assert(result.inf.value == 99);
    assert(result.reachable(1));
    assert(result.dist[1].value == 99);
    assert(!result.reachable(2));
    assert(result.dist[2].value == 99);
}

int main() {
    test_custom_cost();
    test_explicit_sentinel_is_not_reachability();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
