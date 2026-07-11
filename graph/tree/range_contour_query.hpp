#ifndef M1UNE_TREE_RANGE_CONTOUR_QUERY_HPP
#define M1UNE_TREE_RANGE_CONTOUR_QUERY_HPP 1

#include <algorithm>
#include <cassert>
#include <vector>

#include "../../monoid/add.hpp"
#include "../../monoid/concept.hpp"
#include "../graph.hpp"
#include "centroid_decomposition.hpp"
#include "rooted_tree.hpp"

namespace m1une {
namespace tree {

namespace internal {

struct RangeContourPathEntry {
    int centroid;
    int distance;
    int subtree;
};

struct RangeContourLayout {
    int n = 0;
    std::vector<std::vector<RangeContourPathEntry>> path;
    std::vector<int> all_size;
    std::vector<int> subtree_size;

    template <class EdgeCost>
    void build(const m1une::graph::Graph<EdgeCost>& graph) {
        n = graph.size();
        path.assign(n, {});
        all_size.assign(n, 0);
        subtree_size.assign(n, 0);
        if (n == 0) return;

#ifndef NDEBUG
        std::vector<int> incidence(graph.edge_count(), 0);
        for (int vertex = 0; vertex < n; vertex++) {
            for (const auto& edge : graph[vertex]) {
                if (!edge.alive) continue;
                assert(0 <= edge.id && edge.id < graph.edge_count());
                incidence[edge.id]++;
            }
        }
        int active_edges = 0;
        for (int count : incidence) {
            if (count == 0) continue;
            assert(count == 2);
            active_edges++;
        }
        assert(active_edges == n - 1);
#endif

        RootedTree<EdgeCost> rooted(graph, 0);
        assert(int(rooted.order.size()) == n);
        CentroidDecomposition<EdgeCost> decomposition(graph);

        for (int vertex = 0; vertex < n; vertex++) {
            int previous = -1;
            for (
                int centroid = vertex;
                centroid != -1;
                centroid = decomposition.parent[centroid]
            ) {
                int distance = rooted.dist_edges(vertex, centroid);
                path[vertex].push_back(
                    RangeContourPathEntry{centroid, distance, previous}
                );
                all_size[centroid] = std::max(
                    all_size[centroid],
                    distance + 1
                );
                if (previous != -1) {
                    subtree_size[previous] = std::max(
                        subtree_size[previous],
                        distance + 1
                    );
                }
                previous = centroid;
            }
        }
    }
};

template <m1une::monoid::IsCommutativeGroup Group>
class RangeContourFenwick {
   public:
    using T = typename Group::value_type;

   private:
    int _n = 0;
    std::vector<T> _data;

    T prefix_product(int right) const {
        T result = Group::id();
        while (right > 0) {
            result = Group::op(result, _data[right]);
            right -= right & -right;
        }
        return result;
    }

   public:
    RangeContourFenwick() : _data(1, Group::id()) {}

    explicit RangeContourFenwick(int n)
        : _n(n), _data(n + 1, Group::id()) {
        assert(0 <= n);
    }

    int size() const {
        return _n;
    }

    void apply(int index, const T& value) {
        assert(0 <= index && index < _n);
        for (index++; index <= _n; index += index & -index) {
            _data[index] = Group::op(_data[index], value);
        }
    }

    T product(int left, int right) const {
        left = std::max(left, 0);
        right = std::min(right, _n);
        if (right <= left) return Group::id();
        return Group::op(
            Group::inv(prefix_product(left)),
            prefix_product(right)
        );
    }

    void range_apply(int left, int right, const T& value) {
        left = std::max(left, 0);
        right = std::min(right, _n);
        if (right <= left) return;
        apply(left, value);
        if (right < _n) apply(right, Group::inv(value));
    }

    T get(int index) const {
        assert(0 <= index && index < _n);
        return prefix_product(index + 1);
    }
};

}  // namespace internal

template <m1une::monoid::IsCommutativeGroup Group>
class VertexApplyRangeContourProduct {
   public:
    using T = typename Group::value_type;

   private:
    internal::RangeContourLayout _layout;
    std::vector<T> _value;
    std::vector<internal::RangeContourFenwick<Group>> _all;
    std::vector<internal::RangeContourFenwick<Group>> _subtree;

    void check_vertex(int vertex) const {
        assert(0 <= vertex && vertex < size());
    }

   public:
    VertexApplyRangeContourProduct() = default;

    template <class EdgeCost>
    explicit VertexApplyRangeContourProduct(
        const m1une::graph::Graph<EdgeCost>& graph,
        const std::vector<T>& initial = {}
    ) {
        build(graph, initial);
    }

    template <class EdgeCost>
    void build(
        const m1une::graph::Graph<EdgeCost>& graph,
        const std::vector<T>& initial = {}
    ) {
        assert(initial.empty() || int(initial.size()) == graph.size());
        _layout.build(graph);
        const int n = _layout.n;
        _value.assign(n, Group::id());
        _all.assign(n, internal::RangeContourFenwick<Group>());
        _subtree.assign(n, internal::RangeContourFenwick<Group>());
        for (int index = 0; index < n; index++) {
            _all[index] =
                internal::RangeContourFenwick<Group>(_layout.all_size[index]);
            _subtree[index] =
                internal::RangeContourFenwick<Group>(
                    _layout.subtree_size[index]
                );
        }
        if (!initial.empty()) {
            for (int vertex = 0; vertex < n; vertex++) {
                apply(vertex, initial[vertex]);
            }
        }
    }

    int size() const {
        return _layout.n;
    }

    bool empty() const {
        return size() == 0;
    }

    T get(int vertex) const {
        check_vertex(vertex);
        return _value[vertex];
    }

    void apply(int vertex, const T& value) {
        check_vertex(vertex);
        _value[vertex] = Group::op(_value[vertex], value);
        for (const auto& entry : _layout.path[vertex]) {
            _all[entry.centroid].apply(entry.distance, value);
            if (entry.subtree != -1) {
                _subtree[entry.subtree].apply(entry.distance, value);
            }
        }
    }

    void set(int vertex, const T& value) {
        check_vertex(vertex);
        apply(vertex, Group::op(Group::inv(_value[vertex]), value));
    }

    T prod(int vertex, int left_distance, int right_distance) const {
        check_vertex(vertex);
        assert(0 <= left_distance && left_distance <= right_distance);
        T result = Group::id();
        for (const auto& entry : _layout.path[vertex]) {
            int left = left_distance - entry.distance;
            int right = right_distance - entry.distance;
            result = Group::op(
                result,
                _all[entry.centroid].product(left, right)
            );
            if (entry.subtree != -1) {
                result = Group::op(
                    result,
                    Group::inv(
                        _subtree[entry.subtree].product(left, right)
                    )
                );
            }
        }
        return result;
    }
};

template <m1une::monoid::IsCommutativeGroup Group>
class VertexGetRangeContourApply {
   public:
    using T = typename Group::value_type;

   private:
    internal::RangeContourLayout _layout;
    std::vector<T> _base;
    std::vector<internal::RangeContourFenwick<Group>> _all;
    std::vector<internal::RangeContourFenwick<Group>> _subtree;

    void check_vertex(int vertex) const {
        assert(0 <= vertex && vertex < size());
    }

   public:
    VertexGetRangeContourApply() = default;

    template <class EdgeCost>
    explicit VertexGetRangeContourApply(
        const m1une::graph::Graph<EdgeCost>& graph,
        const std::vector<T>& initial = {}
    ) {
        build(graph, initial);
    }

    template <class EdgeCost>
    void build(
        const m1une::graph::Graph<EdgeCost>& graph,
        const std::vector<T>& initial = {}
    ) {
        assert(initial.empty() || int(initial.size()) == graph.size());
        _layout.build(graph);
        const int n = _layout.n;
        _base = initial.empty() ? std::vector<T>(n, Group::id()) : initial;
        _all.assign(n, internal::RangeContourFenwick<Group>());
        _subtree.assign(n, internal::RangeContourFenwick<Group>());
        for (int index = 0; index < n; index++) {
            _all[index] =
                internal::RangeContourFenwick<Group>(_layout.all_size[index]);
            _subtree[index] =
                internal::RangeContourFenwick<Group>(
                    _layout.subtree_size[index]
                );
        }
    }

    int size() const {
        return _layout.n;
    }

    bool empty() const {
        return size() == 0;
    }

    T get(int vertex) const {
        check_vertex(vertex);
        T result = _base[vertex];
        for (const auto& entry : _layout.path[vertex]) {
            result = Group::op(
                result,
                _all[entry.centroid].get(entry.distance)
            );
            if (entry.subtree != -1) {
                result = Group::op(
                    result,
                    Group::inv(
                        _subtree[entry.subtree].get(entry.distance)
                    )
                );
            }
        }
        return result;
    }

    void point_apply(int vertex, const T& value) {
        check_vertex(vertex);
        _base[vertex] = Group::op(_base[vertex], value);
    }

    void set(int vertex, const T& value) {
        check_vertex(vertex);
        _base[vertex] = Group::op(
            _base[vertex],
            Group::op(Group::inv(get(vertex)), value)
        );
    }

    void apply(
        int vertex,
        int left_distance,
        int right_distance,
        const T& value
    ) {
        check_vertex(vertex);
        assert(0 <= left_distance && left_distance <= right_distance);
        for (const auto& entry : _layout.path[vertex]) {
            int left = left_distance - entry.distance;
            int right = right_distance - entry.distance;
            _all[entry.centroid].range_apply(left, right, value);
            if (entry.subtree != -1) {
                _subtree[entry.subtree].range_apply(left, right, value);
            }
        }
    }
};

template <class T>
class VertexAddRangeContourSum
    : public VertexApplyRangeContourProduct<m1une::monoid::Add<T>> {
   private:
    using Base = VertexApplyRangeContourProduct<m1une::monoid::Add<T>>;

   public:
    using Base::Base;

    void add(int vertex, const T& delta) {
        Base::apply(vertex, delta);
    }

    T sum(int vertex, int left_distance, int right_distance) const {
        return Base::prod(vertex, left_distance, right_distance);
    }
};

template <class T>
class VertexGetRangeContourAdd
    : public VertexGetRangeContourApply<m1une::monoid::Add<T>> {
   private:
    using Base = VertexGetRangeContourApply<m1une::monoid::Add<T>>;

   public:
    using Base::Base;

    void add(int vertex, const T& delta) {
        Base::point_apply(vertex, delta);
    }
};

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_RANGE_CONTOUR_QUERY_HPP
