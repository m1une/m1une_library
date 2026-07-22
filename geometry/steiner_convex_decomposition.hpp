#ifndef M1UNE_GEOMETRY_STEINER_CONVEX_DECOMPOSITION_HPP
#define M1UNE_GEOMETRY_STEINER_CONVEX_DECOMPOSITION_HPP 1

#include <algorithm>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <deque>
#include <limits>
#include <map>
#include <optional>
#include <utility>
#include <vector>

#include "polygon.hpp"

namespace m1une {
namespace geometry {

namespace steiner_convex_decomposition_detail {

using PointType = Point<long double>;

inline int scalar_sign(long double value, long double eps) {
    return (value > eps) - (value < -eps);
}

inline bool close(
    const PointType& first,
    const PointType& second,
    long double eps
) {
    return distance2(first, second) <= eps * eps;
}

template <std::floating_point T>
std::optional<std::vector<PointType>> prepare_polygon(
    const std::vector<Point<T>>& input,
    long double eps
) {
    std::vector<PointType> points;
    points.reserve(input.size());
    for (const Point<T>& point : input) {
        const PointType converted(point);
        if (points.empty() || !close(points.back(), converted, eps)) {
            points.push_back(converted);
        }
    }
    if (points.size() >= 2 && close(points.front(), points.back(), eps)) {
        points.pop_back();
    }
    if (points.size() < 3) return std::nullopt;

    const int size = static_cast<int>(points.size());
    std::vector<int> previous(size), next(size);
    std::vector<bool> removed(size, false), queued(size, true);
    std::deque<int> candidates;
    for (int index = 0; index < size; ++index) {
        previous[index] = (index + size - 1) % size;
        next[index] = (index + 1) % size;
        candidates.push_back(index);
    }

    int remaining = size;
    while (!candidates.empty() && remaining >= 3) {
        const int index = candidates.front();
        candidates.pop_front();
        queued[index] = false;
        if (removed[index]) continue;
        const int before = previous[index];
        const int after = next[index];
        if (
            orientation(points[before], points[index], points[after], eps) !=
                0 ||
            scalar_sign(
                dot(
                    points[index] - points[before],
                    points[after] - points[index]
                ),
                eps
            ) < 0
        ) {
            continue;
        }
        removed[index] = true;
        next[before] = after;
        previous[after] = before;
        --remaining;
        for (const int adjacent : {before, after}) {
            if (!queued[adjacent]) {
                queued[adjacent] = true;
                candidates.push_back(adjacent);
            }
        }
    }
    if (remaining < 3) return std::nullopt;

    std::vector<PointType> polygon;
    polygon.reserve(static_cast<std::size_t>(remaining));
    int first = 0;
    while (removed[first]) ++first;
    int index = first;
    do {
        polygon.push_back(points[index]);
        index = next[index];
    } while (index != first);

    const int area_sign = scalar_sign(polygon_area2(polygon), eps);
    if (area_sign == 0) return std::nullopt;
    if (area_sign < 0) std::reverse(polygon.begin(), polygon.end());
    return polygon;
}

class BoundaryRayShooter {
   private:
    struct Chain {
        int first_edge;
        int edge_count;
    };

   public:
    struct Hit {
        long double parameter;
        PointType point;
        std::vector<int> edges;
    };

    BoundaryRayShooter(
        const std::vector<PointType>& polygon,
        long double eps
    )
        : polygon_(polygon),
          size_(static_cast<int>(polygon.size())),
          eps_(eps) {
        build_chains();
    }

    std::optional<Hit> shoot(
        int origin_index,
        const PointType& direction
    ) const {
        std::vector<int> candidates;
        for (const Chain& chain : chains_) {
            chain_candidates(
                chain, polygon_[origin_index], direction, candidates
            );
        }
        // Adjacent chains may report the same edge. Testing that constant
        // duplication directly keeps the query linear in the chain count.

        long double best = std::numeric_limits<long double>::infinity();
        std::vector<int> best_edges;
        for (int edge : candidates) {
            edge %= size_;
            const PointType offset = polygon_[edge] - polygon_[origin_index];
            const PointType edge_direction =
                polygon_[(edge + 1) % size_] - polygon_[edge];
            const long double denominator = cross(direction, edge_direction);
            long double parameter = -1;
            if (std::fabs(denominator) <= eps_) {
                if (std::fabs(cross(direction, offset)) > eps_) continue;
                const long double norm2 = dot(direction, direction);
                const long double first = dot(offset, direction) / norm2;
                const long double second = dot(
                    polygon_[(edge + 1) % size_] - polygon_[origin_index],
                    direction
                ) / norm2;
                if (first > eps_) parameter = first;
                if (
                    second > eps_ &&
                    (parameter < 0 || second < parameter)
                ) {
                    parameter = second;
                }
            } else {
                parameter = cross(offset, edge_direction) / denominator;
                const long double edge_parameter =
                    cross(offset, direction) / denominator;
                if (
                    parameter <= eps_ || edge_parameter < -eps_ ||
                    edge_parameter > 1 + eps_
                ) {
                    continue;
                }
            }
            if (parameter < 0) continue;
            if (parameter + eps_ < best) {
                best = parameter;
                best_edges.assign(1, edge);
            } else if (std::fabs(parameter - best) <= eps_) {
                best_edges.push_back(edge);
            }
        }
        if (best_edges.empty()) return std::nullopt;
        return Hit{
            best,
            polygon_[origin_index] + direction * best,
            std::move(best_edges)
        };
    }

   private:
    const std::vector<PointType>& polygon_;
    int size_;
    long double eps_;
    std::vector<Chain> chains_;

    int quadrant(const PointType& direction) const {
        const int x_sign = scalar_sign(direction.x, eps_);
        const int y_sign = scalar_sign(direction.y, eps_);
        if (y_sign >= 0) return x_sign >= 0 ? 0 : 1;
        return x_sign < 0 ? 2 : 3;
    }

    void build_chains() {
        int first_edge = 0;
        PointType previous_direction = polygon_[1] - polygon_[0];
        int current_quadrant = quadrant(previous_direction);
        for (int edge = 1; edge < size_; ++edge) {
            const PointType direction =
                polygon_[(edge + 1) % size_] - polygon_[edge];
            const int direction_quadrant = quadrant(direction);
            if (
                scalar_sign(cross(previous_direction, direction), eps_) < 0 ||
                direction_quadrant != current_quadrant
            ) {
                chains_.push_back(Chain{first_edge, edge - first_edge});
                first_edge = edge;
                current_quadrant = direction_quadrant;
            }
            previous_direction = direction;
        }
        chains_.push_back(Chain{first_edge, size_ - first_edge});
    }

    int vertex_side(
        const PointType& origin,
        const PointType& direction,
        int vertex
    ) const {
        return scalar_sign(
            cross(direction, polygon_[vertex % size_] - origin), eps_
        );
    }

    int edge_side(const PointType& direction, int edge) const {
        return scalar_sign(
            cross(
                direction,
                polygon_[(edge + 1) % size_] - polygon_[edge]
            ),
            eps_
        );
    }

    void crossing_on_monotone_part(
        const Chain& chain,
        const PointType& origin,
        const PointType& direction,
        int first_position,
        int last_position,
        std::vector<int>& candidates
    ) const {
        if (first_position >= last_position) return;
        const int first_sign = vertex_side(
            origin, direction, chain.first_edge + first_position
        );
        const int last_sign = vertex_side(
            origin, direction, chain.first_edge + last_position
        );
        if (first_sign == 0) {
            candidates.push_back(chain.first_edge + first_position);
        }
        if (last_sign == 0) {
            candidates.push_back(chain.first_edge + last_position - 1);
        }
        if (
            first_sign == 0 || last_sign == 0 ||
            first_sign == last_sign
        ) {
            return;
        }
        int low = first_position;
        int high = last_position;
        while (high - low > 1) {
            const int middle = (low + high) / 2;
            const int middle_sign = vertex_side(
                origin, direction, chain.first_edge + middle
            );
            if (middle_sign == 0 || middle_sign != first_sign) {
                high = middle;
            } else {
                low = middle;
            }
        }
        candidates.push_back(chain.first_edge + high - 1);
    }

    void chain_candidates(
        const Chain& chain,
        const PointType& origin,
        const PointType& direction,
        std::vector<int>& candidates
    ) const {
        int split = 0;
        const int first_derivative =
            edge_side(direction, chain.first_edge);
        const int last_derivative = edge_side(
            direction, chain.first_edge + chain.edge_count - 1
        );
        if (
            first_derivative != 0 && last_derivative != 0 &&
            first_derivative != last_derivative
        ) {
            int low = 0;
            int high = chain.edge_count - 1;
            while (high - low > 1) {
                const int middle = (low + high) / 2;
                const int middle_sign = edge_side(
                    direction, chain.first_edge + middle
                );
                if (
                    middle_sign == 0 ||
                    middle_sign != first_derivative
                ) {
                    high = middle;
                } else {
                    low = middle;
                }
            }
            split = high;
        }
        if (split == 0) {
            crossing_on_monotone_part(
                chain,
                origin,
                direction,
                0,
                chain.edge_count,
                candidates
            );
        } else {
            crossing_on_monotone_part(
                chain, origin, direction, 0, split, candidates
            );
            crossing_on_monotone_part(
                chain,
                origin,
                direction,
                split,
                chain.edge_count,
                candidates
            );
        }
    }
};

class DecompositionGraph {
   private:
    struct Edge {
        int first;
        int second;
        int boundary_source;
        bool active;
    };

    struct CutHit {
        long double parameter;
        PointType point;
        int edge;
        long double edge_parameter;
    };

   public:
    DecompositionGraph(
        const std::vector<PointType>& polygon,
        const std::vector<int>& reflex_vertices,
        long double eps
    )
        : original_size_(static_cast<int>(polygon.size())),
          eps_(eps),
          vertices_(polygon),
          boundary_splits_(polygon.size()),
          special_(polygon.size(), false) {
        for (int index = 0; index + 1 < original_size_; ++index) {
            const int edge = static_cast<int>(edges_.size());
            edges_.push_back(Edge{index, index + 1, index, true});
            active_edges_.emplace_hint(
                active_edges_.end(), edge_key(index, index + 1), edge
            );
        }
        const int closing_edge = static_cast<int>(edges_.size());
        edges_.push_back(Edge{
            original_size_ - 1, 0, original_size_ - 1, true
        });
        active_edges_.emplace(
            edge_key(original_size_ - 1, 0), closing_edge
        );
        for (int index = 0; index < original_size_; ++index) {
            boundary_splits_[index].emplace(0, index);
            boundary_splits_[index].emplace(
                1, (index + 1) % original_size_
            );
        }
        for (const int reflex : reflex_vertices) {
            special_[reflex] = true;
            special_vertices_.push_back(reflex);
        }
    }

    std::vector<long double> candidate_alphas(int origin) const {
        const int previous = (origin + original_size_ - 1) % original_size_;
        const int next = (origin + 1) % original_size_;
        const PointType left = normalized(
            vertices_[origin] - vertices_[previous]
        );
        const PointType right = normalized(
            vertices_[origin] - vertices_[next]
        );
        const PointType difference = left - right;

        std::vector<long double> forbidden;
        for (const int vertex : special_vertices_) {
            if (vertex == origin) continue;
            const PointType offset = vertices_[vertex] - vertices_[origin];
            const long double coefficient = cross(difference, offset);
            if (std::fabs(coefficient) <= eps_) continue;
            const long double alpha = -cross(right, offset) / coefficient;
            if (eps_ < alpha && alpha < 1 - eps_) forbidden.push_back(alpha);
        }
        const int candidate_count =
            static_cast<int>(forbidden.size()) + 5;
        const long double denominator = candidate_count + 1;
        std::vector<int> blocked_delta(candidate_count + 1, 0);
        for (const long double value : forbidden) {
            int first = static_cast<int>(std::ceil(
                (value - eps_) * denominator - 1
            ));
            int last = static_cast<int>(std::floor(
                (value + eps_) * denominator - 1
            ));
            first = std::max(first, 0);
            last = std::min(last, candidate_count - 1);
            if (first > last) continue;
            ++blocked_delta[first];
            --blocked_delta[last + 1];
        }
        std::vector<bool> blocked(candidate_count, false);
        int active_blocks = 0;
        for (int index = 0; index < candidate_count; ++index) {
            active_blocks += blocked_delta[index];
            blocked[index] = active_blocks > 0;
        }

        std::vector<long double> result;
        result.reserve(4);
        const int middle = (candidate_count - 1) / 2;
        for (int distance = 0;
             distance < candidate_count && result.size() < 4;
             ++distance) {
            for (const int index : {middle - distance, middle + distance}) {
                if (
                    index < 0 || index >= candidate_count ||
                    blocked[index]
                ) {
                    continue;
                }
                const long double candidate = (index + 1) / denominator;
                if (
                    result.empty() ||
                    std::fabs(candidate - result.back()) > eps_
                ) {
                    result.push_back(candidate);
                }
                if (result.size() == 4) break;
            }
        }
        return result;
    }

    PointType direction(int origin, long double alpha) const {
        const int previous = (origin + original_size_ - 1) % original_size_;
        const int next = (origin + 1) % original_size_;
        const PointType left = normalized(
            vertices_[origin] - vertices_[previous]
        );
        const PointType right = normalized(
            vertices_[origin] - vertices_[next]
        );
        return left * alpha + right * (1 - alpha);
    }

    bool add_cut(
        int origin,
        const PointType& direction,
        const BoundaryRayShooter::Hit& boundary_hit
    ) {
        const std::optional<CutHit> cut_hit = closest_cut_hit(
            vertices_[origin], direction
        );
        if (
            cut_hit.has_value() &&
            cut_hit->parameter + eps_ < boundary_hit.parameter
        ) {
            const int target = split_cut_edge(*cut_hit);
            if (
                target < 0 || target == origin || special_[target]
            ) {
                return false;
            }
            special_[target] = true;
            special_vertices_.push_back(target);
            add_edge(origin, target, -1);
            return true;
        }

        const int target = boundary_target(boundary_hit);
        if (target < 0 || target == origin || special_[target]) return false;
        special_[target] = true;
        special_vertices_.push_back(target);
        add_edge(origin, target, -1);
        return true;
    }

    std::optional<std::vector<std::vector<PointType>>> faces(
        std::size_t expected_faces
    ) const {
        std::vector<std::vector<int>> adjacency(vertices_.size());
        for (const Edge& edge : edges_) {
            if (!edge.active) continue;
            adjacency[edge.first].push_back(edge.second);
            adjacency[edge.second].push_back(edge.first);
        }
        for (int vertex = 0;
             vertex < static_cast<int>(vertices_.size());
             ++vertex) {
            auto angle = [&](int neighbor) {
                const PointType offset =
                    vertices_[neighbor] - vertices_[vertex];
                return std::atan2(offset.y, offset.x);
            };
            std::sort(
                adjacency[vertex].begin(),
                adjacency[vertex].end(),
                [&](int first, int second) {
                    return angle(first) < angle(second);
                }
            );
        }

        std::vector<std::vector<bool>> visited(vertices_.size());
        for (std::size_t vertex = 0; vertex < adjacency.size(); ++vertex) {
            visited[vertex].assign(adjacency[vertex].size(), false);
        }
        std::vector<std::vector<PointType>> result;
        for (int first = 0;
             first < static_cast<int>(vertices_.size());
             ++first) {
            for (int first_position = 0;
                 first_position < static_cast<int>(adjacency[first].size());
                 ++first_position) {
                if (visited[first][first_position]) continue;
                const int second = adjacency[first][first_position];
                std::vector<PointType> face;
                int from = first;
                int to = second;
                int from_position = first_position;
                while (!visited[from][from_position]) {
                    visited[from][from_position] = true;
                    face.push_back(vertices_[from]);
                    const auto found = std::find(
                        adjacency[to].begin(), adjacency[to].end(), from
                    );
                    if (found == adjacency[to].end()) return std::nullopt;
                    const int position = static_cast<int>(
                        found - adjacency[to].begin()
                    );
                    const int degree =
                        static_cast<int>(adjacency[to].size());
                    const int next_position =
                        (position + degree - 1) % degree;
                    const int next = adjacency[to][next_position];
                    from = to;
                    to = next;
                    from_position = next_position;
                }
                if (from != first || to != second) return std::nullopt;
                if (scalar_sign(polygon_area2(face), eps_) <= 0) continue;
                if (!weakly_convex(face)) return std::nullopt;
                result.push_back(std::move(face));
            }
        }
        if (result.size() != expected_faces) return std::nullopt;
        return result;
    }

   private:
    int original_size_;
    long double eps_;
    std::vector<PointType> vertices_;
    std::vector<Edge> edges_;
    std::map<std::pair<int, int>, int> active_edges_;
    std::vector<std::map<long double, int>> boundary_splits_;
    std::vector<bool> special_;
    std::vector<int> special_vertices_;

    static std::pair<int, int> edge_key(int first, int second) {
        if (first > second) std::swap(first, second);
        return {first, second};
    }

    int add_edge(int first, int second, int boundary_source) {
        const int index = static_cast<int>(edges_.size());
        edges_.push_back(Edge{first, second, boundary_source, true});
        active_edges_[edge_key(first, second)] = index;
        return index;
    }

    bool remove_edge(int first, int second) {
        const auto found = active_edges_.find(edge_key(first, second));
        if (found == active_edges_.end()) return false;
        edges_[found->second].active = false;
        active_edges_.erase(found);
        return true;
    }

    int add_vertex(const PointType& point) {
        const int index = static_cast<int>(vertices_.size());
        vertices_.push_back(point);
        special_.push_back(false);
        return index;
    }

    std::optional<CutHit> closest_cut_hit(
        const PointType& origin,
        const PointType& direction
    ) const {
        std::optional<CutHit> result;
        for (int index = 0; index < static_cast<int>(edges_.size()); ++index) {
            const Edge& edge = edges_[index];
            if (!edge.active || edge.boundary_source >= 0) continue;
            const PointType offset = vertices_[edge.first] - origin;
            const PointType edge_direction =
                vertices_[edge.second] - vertices_[edge.first];
            const long double denominator = cross(direction, edge_direction);
            if (std::fabs(denominator) <= eps_) continue;
            const long double parameter =
                cross(offset, edge_direction) / denominator;
            const long double edge_parameter =
                cross(offset, direction) / denominator;
            if (
                parameter <= eps_ || edge_parameter < -eps_ ||
                edge_parameter > 1 + eps_
            ) {
                continue;
            }
            if (
                !result.has_value() ||
                parameter + eps_ < result->parameter
            ) {
                result = CutHit{
                    parameter,
                    origin + direction * parameter,
                    index,
                    edge_parameter
                };
            } else if (
                std::fabs(parameter - result->parameter) <= eps_ &&
                !close(result->point, origin + direction * parameter, eps_)
            ) {
                return std::nullopt;
            }
        }
        return result;
    }

    int split_cut_edge(const CutHit& hit) {
        Edge& edge = edges_[hit.edge];
        if (!edge.active) return -1;
        if (hit.edge_parameter <= eps_) return edge.first;
        if (hit.edge_parameter >= 1 - eps_) return edge.second;
        const int first = edge.first;
        const int second = edge.second;
        const int source = edge.boundary_source;
        if (!remove_edge(first, second)) return -1;
        const int vertex = add_vertex(hit.point);
        add_edge(first, vertex, source);
        add_edge(vertex, second, source);
        return vertex;
    }

    int boundary_target(const BoundaryRayShooter::Hit& hit) {
        int vertex_target = -1;
        for (const int source : hit.edges) {
            const PointType edge =
                vertices_[(source + 1) % original_size_] - vertices_[source];
            const long double parameter = dot(
                hit.point - vertices_[source], edge
            ) / dot(edge, edge);
            int candidate = -1;
            if (parameter <= eps_) candidate = source;
            if (parameter >= 1 - eps_) {
                candidate = (source + 1) % original_size_;
            }
            if (candidate < 0) continue;
            if (vertex_target >= 0 && vertex_target != candidate) return -1;
            vertex_target = candidate;
        }
        if (vertex_target >= 0) return vertex_target;
        if (hit.edges.size() != 1) return -1;

        const int source = hit.edges.front();
        const PointType edge =
            vertices_[(source + 1) % original_size_] - vertices_[source];
        const long double parameter = dot(
            hit.point - vertices_[source], edge
        ) / dot(edge, edge);
        auto& splits = boundary_splits_[source];
        auto after = splits.lower_bound(parameter);
        if (
            after != splits.end() &&
            std::fabs(after->first - parameter) <= eps_
        ) {
            return after->second;
        }
        if (after == splits.begin() || after == splits.end()) return -1;
        const auto before = std::prev(after);
        if (!remove_edge(before->second, after->second)) return -1;
        const int vertex = add_vertex(hit.point);
        add_edge(before->second, vertex, source);
        add_edge(vertex, after->second, source);
        splits.emplace(parameter, vertex);
        return vertex;
    }

    bool weakly_convex(const std::vector<PointType>& polygon) const {
        for (std::size_t index = 0; index < polygon.size(); ++index) {
            if (
                orientation(
                    polygon[index],
                    polygon[(index + 1) % polygon.size()],
                    polygon[(index + 2) % polygon.size()],
                    eps_
                ) < 0
            ) {
                return false;
            }
        }
        return true;
    }
};

}  // namespace steiner_convex_decomposition_detail

template <std::floating_point T>
std::optional<std::vector<std::vector<Point<long double>>>>
steiner_convex_decomposition(
    const std::vector<Point<T>>& input,
    long double eps = 1e-12L
) {
    using namespace steiner_convex_decomposition_detail;
    auto prepared = prepare_polygon(input, eps);
    if (!prepared.has_value()) return std::nullopt;
    const std::vector<PointType>& polygon = *prepared;
    const int size = static_cast<int>(polygon.size());

    std::vector<int> reflex_vertices;
    for (int index = 0; index < size; ++index) {
        if (
            orientation(
                polygon[(index + size - 1) % size],
                polygon[index],
                polygon[(index + 1) % size],
                eps
            ) < 0
        ) {
            reflex_vertices.push_back(index);
        }
    }
    if (reflex_vertices.empty()) {
        return std::vector<std::vector<PointType>>(1, polygon);
    }

    BoundaryRayShooter boundary(polygon, eps);
    DecompositionGraph graph(polygon, reflex_vertices, eps);
    for (const int reflex : reflex_vertices) {
        bool added = false;
        for (const long double alpha : graph.candidate_alphas(reflex)) {
            const PointType direction = graph.direction(reflex, alpha);
            const auto hit = boundary.shoot(reflex, direction);
            if (!hit.has_value()) continue;
            if (graph.add_cut(reflex, direction, *hit)) {
                added = true;
                break;
            }
        }
        if (!added) return std::nullopt;
    }
    return graph.faces(reflex_vertices.size() + 1);
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_STEINER_CONVEX_DECOMPOSITION_HPP
