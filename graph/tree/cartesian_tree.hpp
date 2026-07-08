#ifndef M1UNE_TREE_CARTESIAN_TREE_HPP
#define M1UNE_TREE_CARTESIAN_TREE_HPP 1

#include <cassert>
#include <cstddef>
#include <functional>
#include <limits>
#include <utility>
#include <vector>

#include "../graph.hpp"

namespace m1une {
namespace tree {

struct CartesianTree {
    int root;
    std::vector<int> parent;
    std::vector<int> left;
    std::vector<int> right;

   private:
    int _n;

    void check_vertex(int v) const {
        assert(0 <= v && v < _n);
    }

   public:
    CartesianTree() : root(-1), _n(0) {}

    template <class T, class Compare = std::less<T>>
    explicit CartesianTree(const std::vector<T>& a, Compare comp = Compare()) : root(-1), _n(0) {
        build(a, comp);
    }

    template <class T, class Compare = std::less<T>>
    void build(const std::vector<T>& a, Compare comp = Compare()) {
        assert(a.size() <= static_cast<std::size_t>(std::numeric_limits<int>::max()));
        _n = int(a.size());
        root = -1;
        parent.assign(_n, -1);
        left.assign(_n, -1);
        right.assign(_n, -1);

        std::vector<int> stack;
        stack.reserve(_n);
        for (int i = 0; i < _n; i++) {
            int last = -1;
            while (!stack.empty() && comp(a[i], a[stack.back()])) {
                last = stack.back();
                stack.pop_back();
            }
            if (last != -1) {
                left[i] = last;
                parent[last] = i;
            }
            if (!stack.empty()) {
                right[stack.back()] = i;
                parent[i] = stack.back();
            }
            stack.push_back(i);
        }

        if (!stack.empty()) root = stack.front();
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    int parent_or_self(int v) const {
        check_vertex(v);
        return parent[v] == -1 ? v : parent[v];
    }

    std::vector<int> parent_with_root_self() const {
        std::vector<int> result = parent;
        if (root != -1) result[root] = root;
        return result;
    }

    std::vector<std::pair<int, int>> edges() const {
        std::vector<std::pair<int, int>> result;
        if (_n == 0) return result;
        result.reserve(_n - 1);
        for (int v = 0; v < _n; v++) {
            if (parent[v] != -1) result.emplace_back(parent[v], v);
        }
        return result;
    }

    m1une::graph::Graph<int> to_graph() const {
        m1une::graph::Graph<int> g(_n);
        for (int v = 0; v < _n; v++) {
            if (parent[v] != -1) g.add_edge(parent[v], v);
        }
        return g;
    }
};

template <class T, class Compare = std::less<T>>
CartesianTree cartesian_tree(const std::vector<T>& a, Compare comp = Compare()) {
    CartesianTree result;
    result.build(a, comp);
    return result;
}

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_CARTESIAN_TREE_HPP
