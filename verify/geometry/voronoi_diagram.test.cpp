#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2160"
#define ERROR "1e-4"

#include "../../geometry/voronoi_diagram.hpp"
#include "../../geometry/half_plane_intersection.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <utility>
#include <vector>

namespace {

using m1une::geometry::Point;
using m1une::geometry::VoronoiDiagram;
using m1une::geometry::VoronoiEdge;
using m1une::geometry::VoronoiEdgeKind;
using Site = Point<long long>;
using RealPoint = Point<long double>;

long double squared_distance(const RealPoint& first, const RealPoint& second) {
    long double x = first.x - second.x;
    long double y = first.y - second.y;
    return x * x + y * y;
}

bool close(long double first, long double second, long double eps = 1e-8L) {
    return std::fabs(first - second) <=
           eps * std::max(
               1.0L,
               std::max(std::fabs(first), std::fabs(second))
           );
}

void check_boundary_point(
    const std::vector<Site>& sites,
    const VoronoiEdge& edge,
    const RealPoint& point
) {
    RealPoint first(sites[edge.first_site]);
    RealPoint second(sites[edge.second_site]);
    long double first_distance = squared_distance(point, first);
    long double second_distance = squared_distance(point, second);
    assert(close(first_distance, second_distance, 1e-7L));
    for (const Site& site : sites) {
        long double candidate = squared_distance(point, RealPoint(site));
        long double tolerance =
            1e-7L * std::max(1.0L, std::max(first_distance, candidate));
        assert(first_distance <= candidate + tolerance);
    }
}

bool naive_has_voronoi_edge(
    const std::vector<Site>& sites,
    int first_site,
    int second_site
) {
    RealPoint first(sites[first_site]);
    RealPoint second(sites[second_site]);
    RealPoint midpoint = (first + second) / 2.0L;
    RealPoint difference = second - first;
    RealPoint direction(difference.y, -difference.x);
    long double lower = -std::numeric_limits<long double>::infinity();
    long double upper = std::numeric_limits<long double>::infinity();

    for (const Site& integer_site : sites) {
        RealPoint site(integer_site);
        long double constant =
            squared_distance(midpoint, first) - squared_distance(midpoint, site);
        RealPoint shifted = midpoint + direction;
        long double coefficient =
            squared_distance(shifted, first) - squared_distance(shifted, site) -
            constant;
        if (std::fabs(coefficient) <= 1e-14L) {
            if (constant > 1e-12L) return false;
        } else {
            long double bound = -constant / coefficient;
            if (coefficient > 0) {
                upper = std::min(upper, bound);
            } else {
                lower = std::max(lower, bound);
            }
        }
    }
    return lower + 1e-10L < upper;
}

void check_diagram(const std::vector<Site>& sites) {
    VoronoiDiagram diagram = m1une::geometry::voronoi_diagram(sites);
    assert(diagram.cell_edges.size() == sites.size());

    std::set<std::pair<int, int>> actual_pairs;
    std::vector<int> cell_occurrences(diagram.edges.size(), 0);
    for (int site = 0; site < int(sites.size()); ++site) {
        for (int edge_index : diagram.cell_edges[site]) {
            assert(0 <= edge_index && edge_index < int(diagram.edges.size()));
            const VoronoiEdge& edge = diagram.edges[edge_index];
            assert(edge.first_site == site || edge.second_site == site);
            ++cell_occurrences[edge_index];
        }
    }

    for (int edge_index = 0; edge_index < int(diagram.edges.size()); ++edge_index) {
        const VoronoiEdge& edge = diagram.edges[edge_index];
        assert(cell_occurrences[edge_index] == 2);
        assert(0 <= edge.first_site && edge.first_site < int(sites.size()));
        assert(0 <= edge.second_site && edge.second_site < int(sites.size()));
        assert(edge.first_site < edge.second_site);
        assert(actual_pairs.emplace(edge.first_site, edge.second_site).second);

        if (edge.kind == VoronoiEdgeKind::Segment) {
            assert(0 <= edge.first_vertex);
            assert(edge.first_vertex < int(diagram.vertices.size()));
            assert(0 <= edge.second_vertex);
            assert(edge.second_vertex < int(diagram.vertices.size()));
            assert(edge.first_vertex < edge.second_vertex);
            assert(close(edge.point.x, diagram.vertices[edge.first_vertex].x));
            assert(close(edge.point.y, diagram.vertices[edge.first_vertex].y));
            RealPoint expected_direction =
                diagram.vertices[edge.second_vertex] -
                diagram.vertices[edge.first_vertex];
            assert(close(edge.direction.x, expected_direction.x));
            assert(close(edge.direction.y, expected_direction.y));
            for (long double parameter : std::array<long double, 3>{0, 0.5L, 1}) {
                check_boundary_point(
                    sites,
                    edge,
                    edge.point + edge.direction * parameter
                );
            }
        } else if (edge.kind == VoronoiEdgeKind::Ray) {
            assert(0 <= edge.first_vertex);
            assert(edge.first_vertex < int(diagram.vertices.size()));
            assert(edge.second_vertex == -1);
            assert(close(edge.point.x, diagram.vertices[edge.first_vertex].x));
            assert(close(edge.point.y, diagram.vertices[edge.first_vertex].y));
            assert(close(m1une::geometry::norm(edge.direction), 1));
            for (long double parameter : std::array<long double, 3>{0, 1, 100}) {
                check_boundary_point(
                    sites,
                    edge,
                    edge.point + edge.direction * parameter
                );
            }
        } else {
            assert(edge.kind == VoronoiEdgeKind::Line);
            assert(edge.first_vertex == -1);
            assert(edge.second_vertex == -1);
            assert(close(m1une::geometry::norm(edge.direction), 1));
            for (long double parameter : std::array<long double, 3>{-100, 0, 100}) {
                check_boundary_point(
                    sites,
                    edge,
                    edge.point + edge.direction * parameter
                );
            }
        }
    }

    for (int first = 0; first < int(sites.size()); ++first) {
        for (int second = first + 1; second < int(sites.size()); ++second) {
            bool actual = actual_pairs.contains(std::pair(first, second));
            bool expected = naive_has_voronoi_edge(sites, first, second);
            assert(actual == expected);
        }
    }
}

int count_kind(const VoronoiDiagram& diagram, VoronoiEdgeKind kind) {
    return int(std::count_if(
        diagram.edges.begin(),
        diagram.edges.end(),
        [&](const VoronoiEdge& edge) { return edge.kind == kind; }
    ));
}

void test_fixed() {
    check_diagram({});
    check_diagram(std::vector<Site>{Site(4, -2)});

    std::vector<Site> two_sites{Site(0, 0), Site(4, 0)};
    check_diagram(two_sites);
    VoronoiDiagram two = m1une::geometry::voronoi_diagram(two_sites);
    assert(two.vertices.empty());
    assert(two.edges.size() == 1);
    assert(two.edges[0].kind == VoronoiEdgeKind::Line);
    assert(close(two.edges[0].point.x, 2));
    assert(close(two.edges[0].point.y, 0));

    std::vector<Site> triangle{
        Site(0, 0),
        Site(6, 0),
        Site(0, 8),
    };
    check_diagram(triangle);
    VoronoiDiagram three = m1une::geometry::voronoi_diagram(triangle);
    assert(three.vertices.size() == 1);
    assert(three.edges.size() == 3);
    assert(count_kind(three, VoronoiEdgeKind::Ray) == 3);
    assert(close(three.vertices[0].x, 3));
    assert(close(three.vertices[0].y, 4));

    std::vector<Site> square{
        Site(0, 0),
        Site(2, 0),
        Site(2, 2),
        Site(0, 2),
    };
    check_diagram(square);
    VoronoiDiagram four = m1une::geometry::voronoi_diagram(square);
    assert(four.vertices.size() == 1);
    assert(four.edges.size() == 4);
    assert(count_kind(four, VoronoiEdgeKind::Ray) == 4);

    std::vector<Site> cocircular{
        Site(5, 0),
        Site(3, 4),
        Site(0, 5),
        Site(-3, 4),
        Site(-5, 0),
        Site(-3, -4),
        Site(0, -5),
        Site(3, -4),
    };
    check_diagram(cocircular);
    VoronoiDiagram eight = m1une::geometry::voronoi_diagram(cocircular);
    assert(eight.vertices.size() == 1);
    assert(eight.edges.size() == 8);
    assert(count_kind(eight, VoronoiEdgeKind::Ray) == 8);

    std::vector<Site> square_with_center = square;
    square_with_center.emplace_back(1, 1);
    check_diagram(square_with_center);
    VoronoiDiagram five =
        m1une::geometry::voronoi_diagram(square_with_center);
    assert(five.vertices.size() == 4);
    assert(five.edges.size() == 8);
    assert(count_kind(five, VoronoiEdgeKind::Segment) == 4);
    assert(count_kind(five, VoronoiEdgeKind::Ray) == 4);

    std::vector<Site> collinear{
        Site(-5, 3),
        Site(-1, 3),
        Site(2, 3),
        Site(9, 3),
    };
    check_diagram(collinear);
    VoronoiDiagram line = m1une::geometry::voronoi_diagram(collinear);
    assert(line.vertices.empty());
    assert(line.edges.size() == 3);
    assert(count_kind(line, VoronoiEdgeKind::Line) == 3);
}

void test_randomized() {
    std::uint64_t state = 0x243f6a8885a308d3ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1500; ++trial) {
        int size = int(random() % 11);
        std::set<std::pair<long long, long long>> used;
        std::vector<Site> sites;
        sites.reserve(size);
        while (int(sites.size()) < size) {
            long long x = static_cast<long long>(random() % 21) - 10;
            long long y = static_cast<long long>(random() % 21) - 10;
            if (used.emplace(x, y).second) sites.emplace_back(x, y);
        }
        check_diagram(sites);
    }
}

long double polygon_area(const std::vector<RealPoint>& polygon) {
    long double twice_area = 0;
    for (int index = 0; index < int(polygon.size()); ++index) {
        twice_area += m1une::geometry::cross(
            polygon[index],
            polygon[(index + 1) % polygon.size()]
        );
    }
    return std::fabs(twice_area) / 2;
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();

    std::cout << std::fixed << std::setprecision(10);
    while (true) {
        int island_size, site_count;
        std::cin >> island_size >> site_count;
        if (island_size == 0 && site_count == 0) break;

        std::vector<Site> island(island_size);
        for (Site& point : island) std::cin >> point.x >> point.y;
        std::vector<Site> sites(site_count);
        for (Site& point : sites) std::cin >> point.x >> point.y;

        VoronoiDiagram diagram = m1une::geometry::voronoi_diagram(sites);
        for (int site = 0; site < site_count; ++site) {
            std::vector<m1une::geometry::Line<long double>> half_planes;
            half_planes.reserve(island_size + diagram.cell_edges[site].size());
            for (int index = 0; index < island_size; ++index) {
                half_planes.push_back(m1une::geometry::Line<long double>{
                    RealPoint(island[index]),
                    RealPoint(island[(index + 1) % island_size]),
                });
            }
            for (int edge_index : diagram.cell_edges[site]) {
                const VoronoiEdge& edge = diagram.edges[edge_index];
                int other = edge.first_site == site
                    ? edge.second_site
                    : edge.first_site;
                RealPoint first(sites[site]);
                RealPoint second(sites[other]);
                RealPoint midpoint = (first + second) / 2.0L;
                RealPoint difference = second - first;
                RealPoint direction(-difference.y, difference.x);
                half_planes.push_back(m1une::geometry::Line<long double>{
                    midpoint,
                    midpoint + direction,
                });
            }

            auto intersection =
                m1une::geometry::half_plane_intersection(half_planes);
            long double area = 0;
            if (
                intersection.status ==
                m1une::geometry::HalfPlaneIntersectionStatus::Bounded
            ) {
                area = polygon_area(intersection.polygon);
            }
            std::cout << area << '\n';
        }
    }
}
