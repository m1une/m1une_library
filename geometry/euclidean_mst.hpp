#ifndef M1UNE_GEOMETRY_EUCLIDEAN_MST_HPP
#define M1UNE_GEOMETRY_EUCLIDEAN_MST_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <limits>
#include <tuple>
#include <utility>
#include <vector>

#include "../ds/dsu/dsu.hpp"
#include "point.hpp"

namespace m1une {
namespace geometry {

template <class T>
struct EuclideanMstEdge {
    int from;
    int to;
    T squared_distance;
};

template <class T>
struct EuclideanMst {
    long double cost;
    std::vector<EuclideanMstEdge<T>> edges;
};

namespace detail {

template <std::integral T>
class EuclideanDelaunay {
   private:
    using W = wide_type<T>;

    struct InternalPoint {
        W x;
        W y;

        friend bool operator==(const InternalPoint&, const InternalPoint&) = default;
    };

    struct Edge {
        int to;
        int ccw;
        int cw;
        int reverse;
        bool enabled = false;
    };

    std::vector<int> open_addresses;
    std::vector<InternalPoint> points;
    std::vector<Edge> edges;
    std::vector<int> duplicate_representative;

    static InternalPoint subtract(const InternalPoint& a, const InternalPoint& b) {
        return InternalPoint{a.x - b.x, a.y - b.y};
    }

    static W cross_product(const InternalPoint& a, const InternalPoint& b) {
        return a.x * b.y - a.y * b.x;
    }

    static W squared_norm(const InternalPoint& point) {
        return point.x * point.x + point.y * point.y;
    }

    static bool inside_circumcircle(
        InternalPoint a,
        InternalPoint b,
        InternalPoint c,
        const InternalPoint& d
    ) {
        a = subtract(a, d);
        b = subtract(b, d);
        c = subtract(c, d);
        W determinant = cross_product(b, c) * squared_norm(a)
                      + cross_product(c, a) * squared_norm(b)
                      + cross_product(a, b) * squared_norm(c);
        return determinant > 0;
    }

    int get_open_address() {
        if (open_addresses.empty()) {
            edges.push_back(Edge());
            return int(edges.size()) - 1;
        }
        int result = open_addresses.back();
        open_addresses.pop_back();
        return result;
    }

    std::pair<int, int> add_edge(int from, int to) {
        int forward = get_open_address();
        int backward = get_open_address();
        edges[forward].to = to;
        edges[forward].ccw = forward;
        edges[forward].cw = forward;
        edges[forward].reverse = backward;
        edges[forward].enabled = true;
        edges[backward].to = from;
        edges[backward].ccw = backward;
        edges[backward].cw = backward;
        edges[backward].reverse = forward;
        edges[backward].enabled = true;
        return {forward, backward};
    }

    void erase_directed_edge(int edge) {
        int ccw = edges[edge].ccw;
        int cw = edges[edge].cw;
        edges[ccw].cw = cw;
        edges[cw].ccw = ccw;
        edges[edge].enabled = false;
    }

    void erase_edge(int edge) {
        int reverse = edges[edge].reverse;
        erase_directed_edge(edge);
        erase_directed_edge(reverse);
        open_addresses.push_back(edge);
        open_addresses.push_back(reverse);
    }

    void insert_ccw_after(int edge, int position) {
        int next = edges[position].ccw;
        edges[edge].ccw = next;
        edges[next].cw = edge;
        edges[edge].cw = position;
        edges[position].ccw = edge;
    }

    void insert_cw_after(int edge, int position) {
        int next = edges[position].cw;
        edges[edge].cw = next;
        edges[next].ccw = edge;
        edges[edge].ccw = position;
        edges[position].cw = edge;
    }

    int orientation(int a, int b, int c) const {
        InternalPoint ab = subtract(points[b], points[a]);
        InternalPoint ac = subtract(points[c], points[a]);
        W value = cross_product(ab, ac);
        return (value > 0) - (value < 0);
    }

    std::pair<int, int> go_next(int edge) const {
        int vertex = edges[edge].to;
        int next_edge = edges[edges[edge].reverse].ccw;
        return {vertex, next_edge};
    }

    std::pair<int, int> go_previous(int edge) const {
        int vertex = edges[edges[edge].cw].to;
        int next_edge = edges[edges[edge].cw].reverse;
        return {vertex, next_edge};
    }

    std::tuple<int, int, int, int> lower_tangent(
        int left_vertex,
        int left_edge,
        int right_vertex,
        int right_edge
    ) const {
        while (true) {
            auto [next_left_vertex, next_left_edge] = go_previous(left_edge);
            if (orientation(right_vertex, left_vertex, next_left_vertex) > 0) {
                left_vertex = next_left_vertex;
                left_edge = next_left_edge;
                continue;
            }
            auto [next_right_vertex, next_right_edge] = go_next(right_edge);
            if (orientation(left_vertex, right_vertex, next_right_vertex) < 0) {
                right_vertex = next_right_vertex;
                right_edge = next_right_edge;
                continue;
            }
            break;
        }
        return {left_vertex, left_edge, right_vertex, right_edge};
    }

    std::pair<int, int> extreme_vertex(int vertex, int edge, bool minimum) const {
        std::pair<int, int> result = {vertex, edge};
        int current_vertex = vertex;
        int current_edge = edge;
        do {
            std::tie(current_vertex, current_edge) = go_next(current_edge);
            std::pair<int, int> candidate = {current_vertex, current_edge};
            if ((minimum && candidate < result) || (!minimum && result < candidate)) {
                result = candidate;
            }
        } while (current_edge != edge);
        return result;
    }

    bool inside_circumcircle(int a, int b, int c, int d) const {
        return inside_circumcircle(points[a], points[b], points[c], points[d]);
    }

    std::pair<int, int> merge_triangulations(
        int left_vertex,
        int left_edge,
        int right_vertex,
        int right_edge
    ) {
        std::tie(left_vertex, left_edge) = extreme_vertex(left_vertex, left_edge, false);
        std::tie(right_vertex, right_edge) = extreme_vertex(right_vertex, right_edge, true);

        auto [lower_left, lower_left_edge, lower_right, lower_right_edge]
            = lower_tangent(left_vertex, left_edge, right_vertex, right_edge);
        auto [upper_right, upper_right_edge, upper_left, upper_left_edge]
            = lower_tangent(right_vertex, right_edge, left_vertex, left_edge);
        lower_right_edge = edges[lower_right_edge].cw;
        upper_right_edge = edges[upper_right_edge].cw;

        auto [base, reverse_base] = add_edge(lower_left, lower_right);
        insert_cw_after(base, lower_left_edge);
        insert_ccw_after(reverse_base, lower_right_edge);
        if (lower_left == upper_left) upper_left_edge = base;
        if (lower_right == upper_right) upper_right_edge = reverse_base;

        int left = lower_left;
        int left_candidate = lower_left_edge;
        int right = lower_right;
        int right_candidate = lower_right_edge;
        while (left != upper_left || right != upper_right) {
            int next_left = edges[left_candidate].to;
            int next_right = edges[right_candidate].to;
            int next_left_candidate = edges[left_candidate].ccw;
            int next_right_candidate = edges[right_candidate].cw;

            if (left_candidate != upper_left_edge && next_left_candidate != base) {
                int second_left = edges[next_left_candidate].to;
                if (inside_circumcircle(left, right, next_left, second_left)) {
                    erase_edge(left_candidate);
                    left_candidate = next_left_candidate;
                    continue;
                }
            }

            if (right_candidate != upper_right_edge && next_right_candidate != reverse_base) {
                int second_right = edges[next_right_candidate].to;
                if (inside_circumcircle(next_right, left, right, second_right)) {
                    erase_edge(right_candidate);
                    right_candidate = next_right_candidate;
                    continue;
                }
            }

            bool choose_left = right_candidate == upper_right_edge;
            if (left_candidate != upper_left_edge && right_candidate != upper_right_edge) {
                if (orientation(left, right, next_right) < 0) {
                    choose_left = true;
                } else if (orientation(next_left, left, right) < 0) {
                    choose_left = false;
                } else {
                    choose_left = inside_circumcircle(left, right, next_right, next_left);
                }
            }

            if (choose_left) {
                next_left_candidate = edges[edges[left_candidate].reverse].ccw;
                auto [new_base, new_reverse_base] = add_edge(next_left, right);
                insert_cw_after(new_base, next_left_candidate);
                insert_ccw_after(new_reverse_base, right_candidate);
                left_candidate = next_left_candidate;
                left = next_left;
            } else {
                next_right_candidate = edges[edges[right_candidate].reverse].cw;
                auto [new_reverse_base, new_base] = add_edge(next_right, left);
                insert_ccw_after(new_reverse_base, next_right_candidate);
                insert_cw_after(new_base, left_candidate);
                right_candidate = next_right_candidate;
                right = next_right;
            }
        }
        return {lower_left, base};
    }

    std::pair<int, int> solve_range(int left, int right) {
        if (right - left == 2) {
            auto [forward, backward] = add_edge(left, left + 1);
            (void)backward;
            return {left, forward};
        }
        if (right - left == 3) {
            int middle = left + 1;
            int last = left + 2;
            auto [first_middle, middle_first] = add_edge(left, middle);
            auto [middle_last, last_middle] = add_edge(middle, last);
            int direction = orientation(left, middle, last);
            if (direction == 0) {
                insert_ccw_after(middle_first, middle_last);
                return {left, first_middle};
            }

            auto [first_last, last_first] = add_edge(left, last);
            if (direction > 0) {
                insert_cw_after(first_middle, first_last);
                insert_cw_after(middle_last, middle_first);
                insert_cw_after(last_first, last_middle);
                return {left, first_middle};
            }
            insert_ccw_after(first_middle, first_last);
            insert_ccw_after(middle_last, middle_first);
            insert_ccw_after(last_first, last_middle);
            return {middle, middle_first};
        }

        int middle = (left + right) / 2;
        auto [left_vertex, left_edge] = solve_range(left, middle);
        auto [right_vertex, right_edge] = solve_range(middle, right);
        return merge_triangulations(left_vertex, left_edge, right_vertex, right_edge);
    }

    void solve() {
        int size = int(points.size());
        if (size <= 1) return;

        std::vector<int> order(size);
        for (int i = 0; i < size; i++) order[i] = i;
        std::stable_sort(order.begin(), order.end(), [&](int left, int right) {
            if (points[left].x != points[right].x) {
                return points[left].x < points[right].x;
            }
            return points[left].y < points[right].y;
        });

        std::vector<InternalPoint> original_points = points;
        duplicate_representative.assign(size, 0);
        int unique_size = 0;
        for (int i = 0; i < size; i++) {
            int vertex = order[i];
            if (i == 0 || !(original_points[order[unique_size - 1]] == original_points[vertex])) {
                order[unique_size] = vertex;
                points[unique_size] = original_points[vertex];
                unique_size++;
                duplicate_representative[vertex] = vertex;
            } else {
                duplicate_representative[vertex] = order[unique_size - 1];
            }
        }

        if (unique_size >= 2) solve_range(0, unique_size);
        points.swap(original_points);
        for (auto& edge : edges) edge.to = order[edge.to];
    }

   public:
    explicit EuclideanDelaunay(const std::vector<Point<T>>& input_points) {
        assert(input_points.size() <= std::size_t(std::numeric_limits<int>::max()));
        points.reserve(input_points.size());
        edges.reserve(std::size_t(6) * input_points.size());
        for (const auto& point : input_points) {
            points.push_back(InternalPoint{W(point.x), W(point.y)});
        }
        solve();
    }

    std::vector<std::pair<int, int>> get_edges() const {
        std::vector<std::pair<int, int>> result;
        result.reserve(edges.size() / 2 + duplicate_representative.size());
        for (int edge = 0; edge < int(edges.size()); edge++) {
            if (!edges[edge].enabled) continue;
            int reverse = edges[edge].reverse;
            if (edge < reverse) continue;
            result.emplace_back(edges[edge].to, edges[reverse].to);
        }
        for (int vertex = 0; vertex < int(duplicate_representative.size()); vertex++) {
            if (duplicate_representative[vertex] != vertex) {
                result.emplace_back(vertex, duplicate_representative[vertex]);
            }
        }
        return result;
    }
};

}  // namespace detail

// Returns O(n) Delaunay edges containing a Euclidean minimum spanning tree.
template <std::integral T>
std::vector<EuclideanMstEdge<wide_type<T>>> euclidean_mst_edges(
    const std::vector<Point<T>>& points
) {
    using W = wide_type<T>;
    auto delaunay_edges = detail::EuclideanDelaunay<T>(points).get_edges();
    std::vector<EuclideanMstEdge<W>> result;
    result.reserve(delaunay_edges.size());
    for (auto [from, to] : delaunay_edges) {
        result.push_back(EuclideanMstEdge<W>{from, to, distance2(points[from], points[to])});
    }
    return result;
}

// Returns a Euclidean minimum spanning tree.
template <std::integral T>
EuclideanMst<wide_type<T>> euclidean_mst(const std::vector<Point<T>>& points) {
    using W = wide_type<T>;
    auto candidates = euclidean_mst_edges(points);
    std::sort(candidates.begin(), candidates.end(), [](const auto& left, const auto& right) {
        if (left.squared_distance != right.squared_distance) {
            return left.squared_distance < right.squared_distance;
        }
        if (left.from != right.from) return left.from < right.from;
        return left.to < right.to;
    });

    m1une::ds::Dsu dsu(int(points.size()));
    EuclideanMst<W> result;
    result.cost = 0;
    result.edges.reserve(points.empty() ? 0 : points.size() - 1);
    for (const auto& edge : candidates) {
        if (dsu.same(edge.from, edge.to)) continue;
        dsu.merge(edge.from, edge.to);
        result.cost += std::sqrt(static_cast<long double>(edge.squared_distance));
        result.edges.push_back(edge);
        if (result.edges.size() + 1 == points.size()) break;
    }
    assert(points.empty() || result.edges.size() + 1 == points.size());
    return result;
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_EUCLIDEAN_MST_HPP
