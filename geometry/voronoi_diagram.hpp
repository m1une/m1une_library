#ifndef M1UNE_GEOMETRY_VORONOI_DIAGRAM_HPP
#define M1UNE_GEOMETRY_VORONOI_DIAGRAM_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <limits>
#include <numeric>
#include <utility>
#include <vector>

#include "euclidean_mst.hpp"

namespace m1une {
namespace geometry {

enum class VoronoiEdgeKind {
    Segment,
    Ray,
    Line,
};

struct VoronoiEdge {
    VoronoiEdgeKind kind;
    int first_site;
    int second_site;
    int first_vertex;
    int second_vertex;
    Point<long double> point;
    Point<long double> direction;
};

struct VoronoiDiagram {
    std::vector<Point<long double>> vertices;
    std::vector<VoronoiEdge> edges;
    std::vector<std::vector<int>> cell_edges;
};

namespace voronoi_diagram_detail {

template <std::integral T>
int direction_half(
    const Point<T>& origin,
    const Point<T>& destination
) {
    using W = wide_type<T>;
    W x = W(destination.x) - W(origin.x);
    W y = W(destination.y) - W(origin.y);
    return y > 0 || (y == 0 && x >= 0) ? 0 : 1;
}

template <std::integral T>
bool direction_less(
    const std::vector<Point<T>>& sites,
    int origin,
    int first,
    int second
) {
    int first_half = direction_half(sites[origin], sites[first]);
    int second_half = direction_half(sites[origin], sites[second]);
    if (first_half != second_half) return first_half < second_half;

    using W = wide_type<T>;
    W first_x = W(sites[first].x) - W(sites[origin].x);
    W first_y = W(sites[first].y) - W(sites[origin].y);
    W second_x = W(sites[second].x) - W(sites[origin].x);
    W second_y = W(sites[second].y) - W(sites[origin].y);
    W product = first_x * second_y - first_y * second_x;
    if (product != 0) return product > 0;

    W first_norm = first_x * first_x + first_y * first_y;
    W second_norm = second_x * second_x + second_y * second_y;
    if (first_norm != second_norm) return first_norm < second_norm;
    return first < second;
}

template <std::integral T>
bool cocircular(
    const Point<T>& first,
    const Point<T>& second,
    const Point<T>& third,
    const Point<T>& fourth
) {
    using W = wide_type<T>;
    W ax = W(first.x) - W(fourth.x);
    W ay = W(first.y) - W(fourth.y);
    W bx = W(second.x) - W(fourth.x);
    W by = W(second.y) - W(fourth.y);
    W cx = W(third.x) - W(fourth.x);
    W cy = W(third.y) - W(fourth.y);
    W a_norm = ax * ax + ay * ay;
    W b_norm = bx * bx + by * by;
    W c_norm = cx * cx + cy * cy;
    W determinant =
        (bx * cy - by * cx) * a_norm +
        (cx * ay - cy * ax) * b_norm +
        (ax * by - ay * bx) * c_norm;
    return determinant == 0;
}

template <std::integral T>
Point<long double> circumcenter(
    const Point<T>& first,
    const Point<T>& second,
    const Point<T>& third
) {
    long double ax = static_cast<long double>(first.x);
    long double ay = static_cast<long double>(first.y);
    long double bx = static_cast<long double>(second.x);
    long double by = static_cast<long double>(second.y);
    long double cx = static_cast<long double>(third.x);
    long double cy = static_cast<long double>(third.y);
    long double denominator = 2 * (
        ax * (by - cy) +
        bx * (cy - ay) +
        cx * (ay - by)
    );
    assert(denominator != 0);
    long double first_norm = ax * ax + ay * ay;
    long double second_norm = bx * bx + by * by;
    long double third_norm = cx * cx + cy * cy;
    return Point<long double>(
        (first_norm * (by - cy) +
         second_norm * (cy - ay) +
         third_norm * (ay - by)) /
            denominator,
        (first_norm * (cx - bx) +
         second_norm * (ax - cx) +
         third_norm * (bx - ax)) /
            denominator
    );
}

inline Point<long double> unit(Point<long double> direction) {
    long double length = norm(direction);
    assert(length != 0);
    return direction / length;
}

inline int other_site(const VoronoiEdge& edge, int site) {
    assert(edge.first_site == site || edge.second_site == site);
    return edge.first_site == site ? edge.second_site : edge.first_site;
}

}  // namespace voronoi_diagram_detail

// Constructs the ordinary Euclidean Voronoi diagram of distinct integral sites.
template <std::integral T>
VoronoiDiagram voronoi_diagram(const std::vector<Point<T>>& sites) {
    namespace detail = voronoi_diagram_detail;
    assert(sites.size() <= std::size_t(std::numeric_limits<int>::max()));

    const int size = int(sites.size());
    std::vector<int> site_order(size);
    std::iota(site_order.begin(), site_order.end(), 0);
    std::sort(site_order.begin(), site_order.end(), [&](int first, int second) {
        return sites[first] < sites[second];
    });
    for (int index = 1; index < size; ++index) {
        assert(sites[site_order[index - 1]] != sites[site_order[index]]);
    }

    std::vector<std::pair<int, int>> delaunay_edges =
        geometry::detail::EuclideanDelaunay<T>(sites).get_edges();
    for (auto& [first, second] : delaunay_edges) {
        if (first > second) std::swap(first, second);
    }
    std::sort(delaunay_edges.begin(), delaunay_edges.end());
    delaunay_edges.erase(
        std::unique(delaunay_edges.begin(), delaunay_edges.end()),
        delaunay_edges.end()
    );

    auto find_edge_index = [&](int first, int second) {
        if (first > second) std::swap(first, second);
        auto iterator = std::lower_bound(
            delaunay_edges.begin(),
            delaunay_edges.end(),
            std::pair(first, second)
        );
        if (
            iterator == delaunay_edges.end() ||
            *iterator != std::pair(first, second)
        ) {
            return -1;
        }
        return int(iterator - delaunay_edges.begin());
    };
    std::vector<std::vector<int>> neighbors(size);
    for (int index = 0; index < int(delaunay_edges.size()); ++index) {
        auto [first, second] = delaunay_edges[index];
        neighbors[first].push_back(second);
        neighbors[second].push_back(first);
    }
    for (int site = 0; site < size; ++site) {
        std::sort(
            neighbors[site].begin(),
            neighbors[site].end(),
            [&](int first, int second) {
                return detail::direction_less(sites, site, first, second);
            }
        );
    }

    std::vector<std::array<int, 3>> triangles;
    for (int site = 0; site < size; ++site) {
        int degree = int(neighbors[site].size());
        for (int index = 0; index < degree; ++index) {
            int first = neighbors[site][index];
            int second = neighbors[site][(index + 1) % degree];
            if (orientation(sites[site], sites[first], sites[second]) <= 0) {
                continue;
            }
            if (find_edge_index(first, second) == -1) continue;
            std::array<int, 3> triangle{site, first, second};
            std::sort(triangle.begin(), triangle.end());
            triangles.push_back(triangle);
        }
    }
    std::sort(triangles.begin(), triangles.end());
    triangles.erase(
        std::unique(triangles.begin(), triangles.end()),
        triangles.end()
    );
    for (auto& triangle : triangles) {
        if (orientation(
                sites[triangle[0]],
                sites[triangle[1]],
                sites[triangle[2]]
            ) < 0) {
            std::swap(triangle[1], triangle[2]);
        }
    }

    std::vector<std::array<int, 2>> incident_triangles(
        delaunay_edges.size(),
        std::array<int, 2>{-1, -1}
    );
    std::vector<int> incident_count(delaunay_edges.size(), 0);
    for (int triangle = 0; triangle < int(triangles.size()); ++triangle) {
        for (int side = 0; side < 3; ++side) {
            int first = triangles[triangle][side];
            int second = triangles[triangle][(side + 1) % 3];
            int edge = find_edge_index(first, second);
            assert(edge != -1);
            assert(incident_count[edge] < 2);
            incident_triangles[edge][incident_count[edge]++] = triangle;
        }
    }

    std::vector<int> parent(triangles.size());
    std::vector<int> component_size(triangles.size(), 1);
    std::iota(parent.begin(), parent.end(), 0);
    auto find_root = [&](auto&& self, int vertex) -> int {
        if (parent[vertex] == vertex) return vertex;
        return parent[vertex] = self(self, parent[vertex]);
    };
    auto merge = [&](int first, int second) {
        first = find_root(find_root, first);
        second = find_root(find_root, second);
        if (first == second) return;
        if (component_size[first] < component_size[second]) {
            std::swap(first, second);
        }
        parent[second] = first;
        component_size[first] += component_size[second];
    };
    for (int edge = 0; edge < int(delaunay_edges.size()); ++edge) {
        if (incident_count[edge] != 2) continue;
        int first_triangle = incident_triangles[edge][0];
        int second_triangle = incident_triangles[edge][1];
        const auto& first = triangles[first_triangle];
        const auto& second = triangles[second_triangle];
        int fourth = second[0];
        if (fourth == first[0] || fourth == first[1] || fourth == first[2]) {
            fourth = second[1];
        }
        if (fourth == first[0] || fourth == first[1] || fourth == first[2]) {
            fourth = second[2];
        }
        assert(
            fourth != first[0] &&
            fourth != first[1] &&
            fourth != first[2]
        );
        if (detail::cocircular(
                sites[first[0]],
                sites[first[1]],
                sites[first[2]],
                sites[fourth]
            )) {
            merge(first_triangle, second_triangle);
        }
    }

    VoronoiDiagram result;
    result.cell_edges.resize(size);
    std::vector<int> root_vertex(triangles.size(), -1);
    std::vector<int> triangle_vertex(triangles.size(), -1);
    for (int triangle = 0; triangle < int(triangles.size()); ++triangle) {
        int root = find_root(find_root, triangle);
        if (root_vertex[root] == -1) {
            const auto& sites_on_circle = triangles[triangle];
            root_vertex[root] = int(result.vertices.size());
            result.vertices.push_back(detail::circumcenter(
                sites[sites_on_circle[0]],
                sites[sites_on_circle[1]],
                sites[sites_on_circle[2]]
            ));
        }
        triangle_vertex[triangle] = root_vertex[root];
    }

    result.edges.reserve(delaunay_edges.size());
    for (int edge = 0; edge < int(delaunay_edges.size()); ++edge) {
        auto [first_site, second_site] = delaunay_edges[edge];
        VoronoiEdge voronoi_edge;
        voronoi_edge.first_site = first_site;
        voronoi_edge.second_site = second_site;
        voronoi_edge.first_vertex = -1;
        voronoi_edge.second_vertex = -1;

        if (incident_count[edge] == 2) {
            int first_vertex =
                triangle_vertex[incident_triangles[edge][0]];
            int second_vertex =
                triangle_vertex[incident_triangles[edge][1]];
            if (first_vertex == second_vertex) continue;
            if (first_vertex > second_vertex) {
                std::swap(first_vertex, second_vertex);
            }
            voronoi_edge.kind = VoronoiEdgeKind::Segment;
            voronoi_edge.first_vertex = first_vertex;
            voronoi_edge.second_vertex = second_vertex;
            voronoi_edge.point = result.vertices[first_vertex];
            voronoi_edge.direction =
                result.vertices[second_vertex] - result.vertices[first_vertex];
        } else if (incident_count[edge] == 1) {
            int triangle = incident_triangles[edge][0];
            int third_site = triangles[triangle][0];
            if (third_site == first_site || third_site == second_site) {
                third_site = triangles[triangle][1];
            }
            if (third_site == first_site || third_site == second_site) {
                third_site = triangles[triangle][2];
            }
            assert(third_site != first_site && third_site != second_site);

            Point<long double> first(sites[first_site]);
            Point<long double> second(sites[second_site]);
            Point<long double> edge_direction = second - first;
            Point<long double> outward;
            if (orientation(
                    sites[first_site],
                    sites[second_site],
                    sites[third_site]
                ) > 0) {
                outward = Point<long double>(
                    edge_direction.y,
                    -edge_direction.x
                );
            } else {
                outward = Point<long double>(
                    -edge_direction.y,
                    edge_direction.x
                );
            }
            voronoi_edge.kind = VoronoiEdgeKind::Ray;
            voronoi_edge.first_vertex = triangle_vertex[triangle];
            voronoi_edge.point = result.vertices[voronoi_edge.first_vertex];
            voronoi_edge.direction = detail::unit(outward);
        } else {
            assert(incident_count[edge] == 0);
            Point<long double> first(sites[first_site]);
            Point<long double> second(sites[second_site]);
            Point<long double> edge_direction = second - first;
            voronoi_edge.kind = VoronoiEdgeKind::Line;
            voronoi_edge.point = (first + second) / 2.0L;
            voronoi_edge.direction = detail::unit(Point<long double>(
                edge_direction.y,
                -edge_direction.x
            ));
        }

        int voronoi_edge_index = int(result.edges.size());
        result.edges.push_back(voronoi_edge);
        result.cell_edges[first_site].push_back(voronoi_edge_index);
        result.cell_edges[second_site].push_back(voronoi_edge_index);
    }

    for (int site = 0; site < size; ++site) {
        std::sort(
            result.cell_edges[site].begin(),
            result.cell_edges[site].end(),
            [&](int first_edge, int second_edge) {
                int first_other =
                    detail::other_site(result.edges[first_edge], site);
                int second_other =
                    detail::other_site(result.edges[second_edge], site);
                return detail::direction_less(
                    sites,
                    site,
                    first_other,
                    second_other
                );
            }
        );
    }
    return result;
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_VORONOI_DIAGRAM_HPP
