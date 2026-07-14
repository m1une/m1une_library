#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"

#include <algorithm>
#include <cassert>
#include <functional>
#include "../../../utilities/fast_io.hpp"
#include <random>
#include <vector>

#include "../../../graph/tree/cartesian_tree.hpp"

struct ExpectedCartesianTree {
    int root;
    std::vector<int> parent;
    std::vector<int> left;
    std::vector<int> right;
};

template <class T, class Compare>
int build_naive_cartesian_tree(
    const std::vector<T>& a,
    int l,
    int r,
    int p,
    Compare comp,
    ExpectedCartesianTree& result
) {
    if (l == r) return -1;
    int best = l;
    for (int i = l + 1; i < r; i++) {
        if (comp(a[i], a[best])) best = i;
    }
    result.parent[best] = p;
    result.left[best] = build_naive_cartesian_tree(a, l, best, best, comp, result);
    result.right[best] = build_naive_cartesian_tree(a, best + 1, r, best, comp, result);
    return best;
}

template <class T, class Compare>
ExpectedCartesianTree naive_cartesian_tree(const std::vector<T>& a, Compare comp) {
    ExpectedCartesianTree result;
    int n = int(a.size());
    result.root = -1;
    result.parent.assign(n, -1);
    result.left.assign(n, -1);
    result.right.assign(n, -1);
    result.root = build_naive_cartesian_tree(a, 0, n, -1, comp, result);
    return result;
}

void collect_inorder(const m1une::tree::CartesianTree& tree, int v, std::vector<int>& order) {
    if (v == -1) return;
    collect_inorder(tree, tree.left[v], order);
    order.push_back(v);
    collect_inorder(tree, tree.right[v], order);
}

template <class T, class Compare>
void assert_cartesian_tree(const std::vector<T>& a, Compare comp) {
    const int n = int(a.size());
    m1une::tree::CartesianTree tree(a, comp);
    ExpectedCartesianTree expected = naive_cartesian_tree(a, comp);

    assert(tree.size() == n);
    assert(tree.empty() == (n == 0));
    assert(tree.root == expected.root);
    assert(tree.parent == expected.parent);
    assert(tree.left == expected.left);
    assert(tree.right == expected.right);

    std::vector<int> inorder;
    inorder.reserve(n);
    collect_inorder(tree, tree.root, inorder);
    assert(int(inorder.size()) == n);
    for (int i = 0; i < n; i++) assert(inorder[i] == i);

    std::vector<int> parent_self = tree.parent_with_root_self();
    assert(int(parent_self.size()) == n);
    for (int v = 0; v < n; v++) {
        if (tree.parent[v] == -1) {
            assert(v == tree.root);
            assert(parent_self[v] == v);
            assert(tree.parent_or_self(v) == v);
        } else {
            assert(parent_self[v] == tree.parent[v]);
            assert(tree.parent_or_self(v) == tree.parent[v]);
            assert(!comp(a[v], a[tree.parent[v]]));
        }
        if (tree.left[v] != -1) {
            assert(tree.left[v] < v);
            assert(tree.parent[tree.left[v]] == v);
        }
        if (tree.right[v] != -1) {
            assert(v < tree.right[v]);
            assert(tree.parent[tree.right[v]] == v);
        }
    }

    std::vector<std::pair<int, int>> edges = tree.edges();
    assert(int(edges.size()) == std::max(0, n - 1));
    auto graph = tree.to_graph();
    assert(graph.size() == n);
    assert(graph.edge_count() == std::max(0, n - 1));
}

void run_local_tests() {
    assert_cartesian_tree(std::vector<int>(), std::less<int>());
    assert_cartesian_tree(std::vector<int>{3, 1, 4, 0, 2}, std::less<int>());
    assert_cartesian_tree(std::vector<int>{3, 1, 4, 0, 2}, std::greater<int>());
    assert_cartesian_tree(std::vector<int>{2, 2, 2, 1, 1, 3}, std::less<int>());

    std::mt19937 rng(123456789);
    for (int n = 0; n <= 60; n++) {
        for (int test = 0; test < 100; test++) {
            std::vector<int> values(n);
            for (int& x : values) x = int(rng() % 11) - 5;
            assert_cartesian_tree(values, std::less<int>());
            assert_cartesian_tree(values, std::greater<int>());
        }
    }
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    run_local_tests();

    int n;
    fast_input >> n;
    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) fast_input >> a[i];

    m1une::tree::CartesianTree tree(a);
    std::vector<int> parent = tree.parent_with_root_self();
    for (int i = 0; i < n; i++) {
        if (i) fast_output << ' ';
        fast_output << parent[i];
    }
    fast_output << '\n';
}
