#ifndef M1UNE_TREE_ZERO_ONE_ON_TREE_HPP
#define M1UNE_TREE_ZERO_ONE_ON_TREE_HPP 1

#include <cassert>
#include <set>
#include <vector>

#include "rooted_tree.hpp"

namespace m1une {
namespace tree {

inline long long zero_one_on_tree(const std::vector<int>& parent,
                                  const std::vector<int>& value) {
    const int n = int(parent.size());
    assert(int(value.size()) == n);
    if (n == 0) return 0;

    int root = -1;
    std::vector<std::vector<int>> children(n);
    for (int v = 0; v < n; v++) {
        assert(value[v] == 0 || value[v] == 1);
        if (parent[v] == -1) {
            assert(root == -1);
            root = v;
        } else {
            assert(0 <= parent[v] && parent[v] < n && parent[v] != v);
            children[parent[v]].push_back(v);
        }
    }
    assert(root != -1);

    std::vector<int> stack(1, root);
    std::vector<char> visited(n, false);
    visited[root] = true;
    int visited_count = 0;
    while (!stack.empty()) {
        const int v = stack.back();
        stack.pop_back();
        visited_count++;
        for (int child : children[v]) {
            assert(!visited[child]);
            visited[child] = true;
            stack.push_back(child);
        }
    }
    assert(visited_count == n);

    struct Component {
        long long zeros;
        long long ones;
        int vertex;
    };
    struct Compare {
        bool operator()(const Component& lhs, const Component& rhs) const {
            const long long lhs_product = lhs.zeros * rhs.ones;
            const long long rhs_product = rhs.zeros * lhs.ones;
            if (lhs_product != rhs_product) return lhs_product < rhs_product;
            return lhs.vertex < rhs.vertex;
        }
    };

    std::vector<long long> zeros(n), ones(n);
    std::vector<int> dsu(n);
    std::set<Component, Compare> components;
    for (int v = 0; v < n; v++) {
        zeros[v] = value[v] == 0;
        ones[v] = value[v] == 1;
        dsu[v] = v;
        if (v != root) components.insert(Component{zeros[v], ones[v], v});
    }

    auto leader = [&](int v) {
        int result = v;
        while (dsu[result] != result) result = dsu[result];
        while (dsu[v] != v) {
            const int next = dsu[v];
            dsu[v] = result;
            v = next;
        }
        return result;
    };

    long long answer = 0;
    while (!components.empty()) {
        auto it = components.end();
        --it;
        const Component child = *it;
        components.erase(it);

        const int p = leader(parent[child.vertex]);
        if (p != root) {
            const int erased = int(components.erase(Component{zeros[p], ones[p], p}));
            assert(erased == 1);
        }

        answer += ones[p] * zeros[child.vertex];
        zeros[p] += zeros[child.vertex];
        ones[p] += ones[child.vertex];
        dsu[child.vertex] = p;

        if (p != root) components.insert(Component{zeros[p], ones[p], p});
    }
    return answer;
}

template <class T>
long long zero_one_on_tree(const m1une::graph::Graph<T>& graph,
                           const std::vector<int>& value, int root = 0) {
    const int n = graph.size();
    assert(int(value.size()) == n);
    if (n == 0) return 0;
    assert(0 <= root && root < n);
    assert(int(graph.edges().size()) == n - 1);

    RootedTree<T> rooted_tree(graph, root);
    assert(int(rooted_tree.order.size()) == n);
    return zero_one_on_tree(rooted_tree.parent, value);
}

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_ZERO_ONE_ON_TREE_HPP
