#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

#include "../../graph/doubling.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>

#include "../../monoid/add.hpp"
#include "../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    int n, q;
    if (!input.read(n, q)) return 0;
    std::vector<std::vector<int>> graph(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        input >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    std::vector<int> parent(n, -1), depth(n, 0), value(n, 1), order;
    value[0] = 0;
    order.reserve(n);
    order.push_back(0);
    for (int i = 0; i < n; ++i) {
        int vertex = order[i];
        for (int to : graph[vertex]) {
            if (to == parent[vertex]) continue;
            parent[to] = vertex;
            depth[to] = depth[vertex] + 1;
            order.push_back(to);
        }
    }
    using Sum = m1une::monoid::Add<int>;
    const m1une::graph::Doubling<Sum> doubling(parent, value, n);
    auto lca = [&](int first, int second) {
        if (depth[first] < depth[second]) std::swap(first, second);
        first = doubling.jump(first, depth[first] - depth[second]);
        if (first == second) return first;
        for (int bit = doubling.levels() - 1; bit >= 0; --bit) {
            const std::uint64_t steps = std::uint64_t(1) << bit;
            int a = doubling.jump(first, steps);
            int b = doubling.jump(second, steps);
            if (a != b) {
                first = a;
                second = b;
            }
        }
        return doubling.jump(first, 1);
    };
    while (q--) {
        int from, to, distance;
        input >> from >> to >> distance;
        int ancestor = lca(from, to);
        int up = depth[from] - depth[ancestor];
        int length = up + depth[to] - depth[ancestor];
        if (distance > length) {
            output << -1 << '\n';
        } else {
            int start = distance <= up ? from : to;
            int steps = distance <= up ? distance : length - distance;
            auto result = doubling.walk(start, steps);
            assert(result.product == steps);
            output << result.vertex << '\n';
        }
    }
}
