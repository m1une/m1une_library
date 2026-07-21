#ifndef M1UNE_GEOMETRY_CONVEX_DECOMPOSITION_HPP
#define M1UNE_GEOMETRY_CONVEX_DECOMPOSITION_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <deque>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

#include "../utilities/int512.hpp"
#include "polygon.hpp"

namespace m1une {
namespace geometry {

namespace convex_decomposition_detail {

using Index = std::size_t;
using IndexPolygon = std::vector<Index>;
using ExactPredicateInteger = m1une::utilities::Int512;

template <Coordinate T>
using PredicateNumber = std::conditional_t<
    std::integral<T>, ExactPredicateInteger, long double>;

template <Coordinate T>
PredicateNumber<T> predicate_number(T value) {
    if constexpr (std::integral<T>) {
        return ExactPredicateInteger(value);
    } else {
        return static_cast<long double>(value);
    }
}

template <Coordinate T>
int predicate_sign(const PredicateNumber<T>& value, long double eps) {
    if constexpr (std::integral<T>) {
        return (value > 0) - (value < 0);
    } else {
        return (value > eps) - (value < -eps);
    }
}

template <Coordinate T>
std::optional<std::vector<Point<T>>> prepare_polygon(
    std::vector<Point<T>> polygon,
    long double eps
) {
    polygon =
        polygon_detail::clean_polygon_vertices(std::move(polygon), eps);
    if (polygon.size() < 3) return std::nullopt;
    const int area_sign = sign<T>(polygon_area2(polygon), eps);
    if (area_sign == 0 || !is_simple_polygon(polygon, eps)) {
        return std::nullopt;
    }
    if (area_sign < 0) std::reverse(polygon.begin(), polygon.end());
    return polygon;
}

template <Coordinate T>
bool is_weakly_convex(
    const std::vector<Point<T>>& polygon,
    long double eps
) {
    if (polygon.size() < 3) return false;
    for (Index index = 0; index < polygon.size(); ++index) {
        if (
            orientation(
                polygon[index],
                polygon[(index + 1) % polygon.size()],
                polygon[(index + 2) % polygon.size()],
                eps
            ) < 0
        ) {
            return false;
        }
    }
    return true;
}

template <Coordinate T>
std::optional<std::vector<IndexPolygon>> triangulate_indices(
    const std::vector<Point<T>>& polygon,
    long double eps
) {
    const Index size = polygon.size();
    std::vector<Index> previous(size), next(size);
    std::vector<bool> active(size, true);
    for (Index index = 0; index < size; ++index) {
        previous[index] = (index + size - 1) % size;
        next[index] = (index + 1) % size;
    }

    auto is_ear = [&](Index index) {
        if (!active[index]) return false;
        const Index first = previous[index];
        const Index third = next[index];
        if (
            orientation(
                polygon[first], polygon[index], polygon[third], eps
            ) <= 0
        ) {
            return false;
        }
        for (Index other = 0; other < size; ++other) {
            if (
                !active[other] || other == first || other == index ||
                other == third
            ) {
                continue;
            }
            if (
                polygon_detail::in_ccw_triangle(
                    polygon[other],
                    polygon[first],
                    polygon[index],
                    polygon[third],
                    eps
                )
            ) {
                return false;
            }
        }
        return true;
    };

    std::deque<Index> ears;
    for (Index index = 0; index < size; ++index) {
        if (is_ear(index)) ears.push_back(index);
    }

    std::vector<IndexPolygon> triangles;
    triangles.reserve(size - 2);
    Index remaining = size;
    while (remaining > 3) {
        while (!ears.empty() && !is_ear(ears.front())) {
            ears.pop_front();
        }
        if (ears.empty()) return std::nullopt;

        const Index ear = ears.front();
        ears.pop_front();
        const Index first = previous[ear];
        const Index third = next[ear];
        triangles.push_back(IndexPolygon{first, ear, third});

        active[ear] = false;
        next[first] = third;
        previous[third] = first;
        --remaining;
        if (is_ear(first)) ears.push_back(first);
        if (is_ear(third)) ears.push_back(third);
    }

    Index first = 0;
    while (first < size && !active[first]) ++first;
    if (first == size) return std::nullopt;
    const Index second = next[first];
    const Index third = next[second];
    if (
        third == first || next[third] != first ||
        orientation(
            polygon[first], polygon[second], polygon[third], eps
        ) <= 0
    ) {
        return std::nullopt;
    }
    triangles.push_back(IndexPolygon{first, second, third});
    return triangles;
}

inline Index find_root(std::vector<Index>& parent, Index index) {
    Index root = index;
    while (parent[root] != root) root = parent[root];
    while (parent[index] != index) {
        const Index next = parent[index];
        parent[index] = root;
        index = next;
    }
    return root;
}

inline std::optional<IndexPolygon> merge_across_edge(
    const IndexPolygon& first,
    const IndexPolygon& second,
    Index edge_first,
    Index edge_second
) {
    for (Index first_position = 0;
         first_position < first.size();
         ++first_position) {
        const Index first_next = (first_position + 1) % first.size();
        const Index from = first[first_position];
        const Index to = first[first_next];
        if (
            !(
                (from == edge_first && to == edge_second) ||
                (from == edge_second && to == edge_first)
            )
        ) {
            continue;
        }

        for (Index second_position = 0;
             second_position < second.size();
             ++second_position) {
            const Index second_next =
                (second_position + 1) % second.size();
            if (
                second[second_position] != to ||
                second[second_next] != from
            ) {
                continue;
            }

            IndexPolygon merged;
            merged.reserve(first.size() + second.size() - 2);
            for (Index position = first_next;
                 position != first_position;
                 position = (position + 1) % first.size()) {
                merged.push_back(first[position]);
            }
            for (Index position = second_next;
                 position != second_position;
                 position = (position + 1) % second.size()) {
                merged.push_back(second[position]);
            }
            return merged;
        }
    }
    return std::nullopt;
}

template <Coordinate T>
bool is_weakly_convex(
    const IndexPolygon& polygon,
    const std::vector<Point<T>>& points,
    long double eps
) {
    for (Index index = 0; index < polygon.size(); ++index) {
        if (
            orientation(
                points[polygon[index]],
                points[polygon[(index + 1) % polygon.size()]],
                points[polygon[(index + 2) % polygon.size()]],
                eps
            ) < 0
        ) {
            return false;
        }
    }
    return true;
}

template <Coordinate T>
std::vector<Point<T>> materialize(
    const IndexPolygon& indices,
    const std::vector<Point<T>>& points,
    long double eps
) {
    std::vector<Point<T>> polygon;
    polygon.reserve(indices.size());
    for (const Index index : indices) polygon.push_back(points[index]);
    return polygon_detail::clean_polygon_vertices(std::move(polygon), eps);
}

struct Diagonal {
    Index first;
    Index second;
};

template <Coordinate T>
std::optional<std::vector<Point<T>>> prepare_minimum_polygon(
    std::vector<Point<T>> polygon,
    long double eps
) {
    if (polygon.size() >= 2 && polygon.front() == polygon.back()) {
        polygon.pop_back();
    }
    std::vector<Point<T>> distinct;
    distinct.reserve(polygon.size());
    for (const Point<T>& point : polygon) {
        if (distinct.empty() || distinct.back() != point) {
            distinct.push_back(point);
        }
    }
    if (distinct.size() >= 2 && distinct.front() == distinct.back()) {
        distinct.pop_back();
    }
    if (distinct.size() < 3) return std::nullopt;

    const int original_size = static_cast<int>(distinct.size());
    std::vector<int> previous(original_size), next(original_size);
    std::vector<bool> removed(original_size, false);
    std::deque<int> candidates;
    for (int index = 0; index < original_size; ++index) {
        previous[index] = (index + original_size - 1) % original_size;
        next[index] = (index + 1) % original_size;
        candidates.push_back(index);
    }
    int remaining = original_size;
    while (!candidates.empty() && remaining >= 3) {
        const int index = candidates.front();
        candidates.pop_front();
        if (removed[index]) continue;
        const int before = previous[index];
        const int after = next[index];
        if (
            orientation(
                distinct[before], distinct[index], distinct[after], eps
            ) != 0 ||
            sign<T>(
                dot(
                    distinct[index] - distinct[before],
                    distinct[after] - distinct[index]
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
        candidates.push_back(before);
        candidates.push_back(after);
    }
    if (remaining < 3) return std::nullopt;

    std::vector<Point<T>> cleaned;
    cleaned.reserve(static_cast<Index>(remaining));
    int first = 0;
    while (removed[first]) ++first;
    int index = first;
    do {
        cleaned.push_back(distinct[index]);
        index = next[index];
    } while (index != first);

    const int area_sign = sign<T>(polygon_area2(cleaned), eps);
    if (area_sign == 0) return std::nullopt;
    if (area_sign < 0) std::reverse(cleaned.begin(), cleaned.end());
    return cleaned;
}

template <Coordinate T>
class BiasedPolygonReduction {
   private:
    using Number = PredicateNumber<T>;

    struct Vector {
        Number x;
        Number y;
    };

    struct Fraction {
        Number numerator;
        Number denominator;
    };

    struct Chain {
        int first_edge;
        int edge_count;
    };

   public:
    struct Result {
        std::vector<Point<T>> polygon;
        std::vector<Index> original_index;
    };

    BiasedPolygonReduction(
        const std::vector<Point<T>>& polygon,
        long double eps
    )
        : polygon_(polygon),
          eps_(eps),
          size_(static_cast<int>(polygon.size())),
          marked_edge_(polygon.size(), false) {
        for (int index = 0; index < size_; ++index) {
            if (
                orientation(
                    polygon_[(index + size_ - 1) % size_],
                    polygon_[index],
                    polygon_[(index + 1) % size_],
                    eps_
                ) < 0
            ) {
                reflex_vertices_.push_back(index);
            }
        }
        build_chains();
    }

    Result run() {
        for (const int reflex : reflex_vertices_) {
            marked_edge_[(reflex + size_ - 1) % size_] = true;
            marked_edge_[reflex] = true;
        }

        std::vector<std::vector<int>> extension_endpoints(size_);
        for (const int reflex : reflex_vertices_) {
            const Vector direction = vector_between(
                reflex, (reflex + 1) % size_
            );
            for (const int edge : ray_shoot(reflex, direction)) {
                marked_edge_[edge] = true;
                extension_endpoints[reflex].push_back(edge);
                extension_endpoints[reflex].push_back((edge + 1) % size_);
            }
        }

        for (Index first = 0; first < reflex_vertices_.size(); ++first) {
            for (Index second = first + 1;
                 second < reflex_vertices_.size();
                 ++second) {
                const int first_vertex = reflex_vertices_[first];
                const int second_vertex = reflex_vertices_[second];
                mark_ray(
                    first_vertex,
                    vector_between(first_vertex, second_vertex)
                );
                mark_ray(
                    second_vertex,
                    vector_between(second_vertex, first_vertex)
                );
            }
        }
        for (const int reflex : reflex_vertices_) {
            auto& endpoints = extension_endpoints[reflex];
            std::sort(endpoints.begin(), endpoints.end());
            endpoints.erase(
                std::unique(endpoints.begin(), endpoints.end()),
                endpoints.end()
            );
            for (const int endpoint : endpoints) {
                if (endpoint == reflex) continue;
                mark_ray(
                    reflex, vector_between(reflex, endpoint)
                );
            }
        }

        Result result;
        for (int index = 0; index < size_; ++index) {
            if (
                marked_edge_[index] ||
                marked_edge_[(index + size_ - 1) % size_]
            ) {
                result.polygon.push_back(polygon_[index]);
                result.original_index.push_back(static_cast<Index>(index));
            }
        }
        return result;
    }

   private:
    const std::vector<Point<T>>& polygon_;
    long double eps_;
    int size_;
    std::vector<int> reflex_vertices_;
    std::vector<Chain> chains_;
    std::vector<bool> marked_edge_;

    Vector vector_between(int first, int second) const {
        return {
            predicate_number<T>(polygon_[first].x) -
                predicate_number<T>(polygon_[second].x),
            predicate_number<T>(polygon_[first].y) -
                predicate_number<T>(polygon_[second].y)
        };
    }

    Number vector_cross(const Vector& first, const Vector& second) const {
        return first.x * second.y - first.y * second.x;
    }

    Number vector_dot(const Vector& first, const Vector& second) const {
        return first.x * second.x + first.y * second.y;
    }

    int vector_sign(const Number& value) const {
        return predicate_sign<T>(value, eps_);
    }

    int quadrant(const Vector& direction) const {
        const int x_sign = vector_sign(direction.x);
        const int y_sign = vector_sign(direction.y);
        if (y_sign >= 0) return x_sign >= 0 ? 0 : 1;
        return x_sign < 0 ? 2 : 3;
    }

    void build_chains() {
        // Within one quadrant, monotonically turning edge directions span at
        // most pi/2. This gives the bitonic sidedness needed by ray shooting
        // without evaluating an angle.
        int first_edge = 0;
        Vector previous_direction = vector_between(1, 0);
        int current_quadrant = quadrant(previous_direction);
        for (int edge = 1; edge < size_; ++edge) {
            const Vector direction = vector_between(
                (edge + 1) % size_, edge
            );
            const int direction_quadrant = quadrant(direction);
            if (
                vector_sign(vector_cross(previous_direction, direction)) <
                    0 ||
                direction_quadrant != current_quadrant
            ) {
                chains_.push_back(Chain{
                    first_edge, edge - first_edge
                });
                first_edge = edge;
                current_quadrant = direction_quadrant;
            }
            previous_direction = direction;
        }
        chains_.push_back(Chain{first_edge, size_ - first_edge});
    }

    int side(
        int origin,
        const Vector& direction,
        int vertex
    ) const {
        return vector_sign(
            vector_cross(
                direction,
                vector_between(vertex % size_, origin)
            )
        );
    }

    int edge_side(const Vector& direction, int edge) const {
        return vector_sign(
            vector_cross(
                direction,
                vector_between((edge + 1) % size_, edge)
            )
        );
    }

    void crossing_on_monotone_part(
        const Chain& chain,
        int origin,
        const Vector& direction,
        int first_position,
        int last_position,
        std::vector<int>& candidates
    ) const {
        if (first_position >= last_position) return;
        const int first_sign = side(
            origin,
            direction,
            chain.first_edge + first_position
        );
        const int last_sign = side(
            origin,
            direction,
            chain.first_edge + last_position
        );
        if (first_sign == 0) {
            candidates.push_back(
                chain.first_edge + first_position
            );
        }
        if (last_sign == 0) {
            candidates.push_back(
                chain.first_edge + last_position - 1
            );
        }
        if (first_sign == 0 || last_sign == 0 || first_sign == last_sign) {
            return;
        }
        int low = first_position;
        int high = last_position;
        while (high - low > 1) {
            const int middle = (low + high) / 2;
            const int middle_sign = side(
                origin,
                direction,
                chain.first_edge + middle
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
        int origin,
        const Vector& direction,
        std::vector<int>& candidates
    ) const {
        int split = 0;
        const int first_derivative =
            edge_side(direction, chain.first_edge);
        const int last_derivative = edge_side(
            direction,
            chain.first_edge + chain.edge_count - 1
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

    std::vector<int> ray_shoot(
        int origin,
        const Vector& direction
    ) const {
        std::vector<int> candidates;
        for (const Chain& chain : chains_) {
            chain_candidates(chain, origin, direction, candidates);
        }
        std::sort(candidates.begin(), candidates.end());
        candidates.erase(
            std::unique(candidates.begin(), candidates.end()),
            candidates.end()
        );

        if constexpr (std::integral<T>) {
            return exact_ray_shoot(origin, direction, candidates);
        } else {
            return floating_ray_shoot(origin, direction, candidates);
        }
    }

    std::vector<int> exact_ray_shoot(
        int origin,
        const Vector& direction,
        const std::vector<int>& candidates
    ) const {
        // Intersections are rational parameters along the ray. Keep their
        // numerators and denominators and compare them by cross products.
        std::optional<Fraction> best;
        std::vector<int> result;
        const Number direction_norm2 = vector_dot(direction, direction);
        for (int edge : candidates) {
            edge %= size_;
            const Vector first = vector_between(edge, origin);
            const Vector second = vector_between(
                (edge + 1) % size_, origin
            );
            const Vector edge_direction = vector_between(
                (edge + 1) % size_, edge
            );
            Number denominator = vector_cross(direction, edge_direction);
            Fraction parameter{0, 1};
            bool valid = false;
            if (denominator == 0) {
                if (vector_cross(direction, first) != 0) continue;
                const Number first_parameter =
                    vector_dot(first, direction);
                const Number second_parameter =
                    vector_dot(second, direction);
                if (first_parameter > 0) {
                    parameter = Fraction{
                        first_parameter, direction_norm2
                    };
                    valid = true;
                }
                if (
                    second_parameter > 0 &&
                    (!valid || second_parameter < parameter.numerator)
                ) {
                    parameter = Fraction{
                        second_parameter, direction_norm2
                    };
                    valid = true;
                }
            } else {
                Number numerator = vector_cross(first, edge_direction);
                Number segment_numerator = vector_cross(first, direction);
                if (denominator < 0) {
                    denominator = -denominator;
                    numerator = -numerator;
                    segment_numerator = -segment_numerator;
                }
                if (
                    numerator <= 0 || segment_numerator < 0 ||
                    segment_numerator > denominator
                ) {
                    continue;
                }
                parameter = Fraction{numerator, denominator};
                valid = true;
            }
            if (!valid) continue;
            if (!best.has_value()) {
                best = parameter;
                result.assign(1, edge);
                continue;
            }
            const Number left =
                parameter.numerator * best->denominator;
            const Number right =
                best->numerator * parameter.denominator;
            if (left < right) {
                best = parameter;
                result.assign(1, edge);
            } else if (left == right) {
                result.push_back(edge);
            }
        }
        return result;
    }

    std::vector<int> floating_ray_shoot(
        int origin,
        const Vector& direction,
        const std::vector<int>& candidates
    ) const {
        long double best = std::numeric_limits<long double>::infinity();
        std::vector<int> result;
        const long double direction_norm2 = vector_dot(
            direction, direction
        );
        for (int edge : candidates) {
            edge %= size_;
            const Vector first = vector_between(edge, origin);
            const Vector second = vector_between(
                (edge + 1) % size_, origin
            );
            const Vector edge_direction = vector_between(
                (edge + 1) % size_, edge
            );
            const long double denominator = vector_cross(
                direction, edge_direction
            );
            long double parameter = -1;
            if (std::fabs(denominator) <= eps_) {
                if (std::fabs(vector_cross(direction, first)) > eps_) {
                    continue;
                }
                const long double first_parameter =
                    vector_dot(first, direction) / direction_norm2;
                const long double second_parameter =
                    vector_dot(second, direction) / direction_norm2;
                if (first_parameter > eps_) parameter = first_parameter;
                if (
                    second_parameter > eps_ &&
                    (parameter < 0 || second_parameter < parameter)
                ) {
                    parameter = second_parameter;
                }
            } else {
                parameter =
                    vector_cross(first, edge_direction) / denominator;
                const long double segment_parameter =
                    vector_cross(first, direction) / denominator;
                if (
                    parameter <= eps_ || segment_parameter < -eps_ ||
                    segment_parameter > 1 + eps_
                ) {
                    continue;
                }
            }
            if (parameter < 0) continue;
            if (parameter + eps_ < best) {
                best = parameter;
                result.assign(1, edge);
            } else if (std::fabs(parameter - best) <= eps_) {
                result.push_back(edge);
            }
        }
        return result;
    }

    void mark_ray(int origin, const Vector& direction) {
        for (const int edge : ray_shoot(origin, direction)) {
            marked_edge_[edge] = true;
        }
    }
};

template <Coordinate T>
class KeilSnoeyinkDecomposition {
   private:
    static constexpr int infinity = 100000000;
    static constexpr int bad = 1000000000;

    struct SolutionNode;
    using NodePointer = std::shared_ptr<const SolutionNode>;

    struct SolutionNode {
        NodePointer first;
        NodePointer second;
        Diagonal diagonal{0, 0};
        bool is_diagonal = false;
    };

    struct NarrowPair {
        int first;
        int second;
        NodePointer solution;
    };

    // Two independently popped views of the same narrowest-pair stack.
    // Pairs are appended from back to front in the terminology of the
    // Keil--Snoeyink paper.
    struct PairDeque {
        std::vector<NarrowPair> pairs;
        int front = -1;
        int back = 0;

        bool empty_front() const { return front < 0; }
        bool more_front() const { return front > 0; }
        bool empty_back() const {
            return back >= static_cast<int>(pairs.size());
        }
        bool more_back() const {
            return back + 1 < static_cast<int>(pairs.size());
        }

        const NarrowPair& front_pair() const { return pairs[front]; }
        const NarrowPair& under_front() const {
            return pairs[front - 1];
        }
        const NarrowPair& back_pair() const { return pairs[back]; }
        const NarrowPair& under_back() const {
            return pairs[back + 1];
        }

        void pop_front() { --front; }
        void pop_back() { ++back; }
        void restore() {
            front = static_cast<int>(pairs.size()) - 1;
            back = 0;
        }
        void clear() {
            pairs.clear();
            restore();
        }
        void push(int first, int second, NodePointer solution = nullptr) {
            pairs.push_back(NarrowPair{first, second, std::move(solution)});
            restore();
        }
        void push_narrow(
            int first,
            int second,
            NodePointer solution
        ) {
            if (!empty_front() && first <= front_pair().first) return;
            while (!empty_front() && front_pair().second >= second) {
                pairs.pop_back();
                --front;
            }
            push(first, second, std::move(solution));
        }
    };

    struct State {
        int weight = bad;
        PairDeque pairs;
    };

    using ProjectiveNumber = PredicateNumber<T>;

    struct Homogeneous {
        ProjectiveNumber w;
        ProjectiveNumber x;
        ProjectiveNumber y;

        Homogeneous negated() const { return {-w, -x, -y}; }

        ProjectiveNumber side(const Point<T>& point) const {
            return w + x * predicate_number<T>(point.x) +
                   y * predicate_number<T>(point.y);
        }

        static Homogeneous line(
            const Point<T>& first,
            const Point<T>& second
        ) {
            const ProjectiveNumber ax = predicate_number<T>(first.x);
            const ProjectiveNumber ay = predicate_number<T>(first.y);
            const ProjectiveNumber bx = predicate_number<T>(second.x);
            const ProjectiveNumber by = predicate_number<T>(second.y);
            return {ax * by - ay * bx, ay - by, bx - ax};
        }

        static Homogeneous meet(
            const Homogeneous& first,
            const Homogeneous& second
        ) {
            return {
                first.x * second.y - first.y * second.x,
                second.w * first.y - first.w * second.y,
                first.w * second.x - second.w * first.x
            };
        }

        static ProjectiveNumber determinant(
            const Homogeneous& first,
            const Homogeneous& second,
            const Homogeneous& third
        ) {
            return
                first.w *
                    (second.x * third.y - second.y * third.x) -
                second.w *
                    (first.x * third.y - first.y * third.x) +
                third.w *
                    (first.x * second.y - first.y * second.x);
        }
    };

    // ElGindy--Avis visibility-polygon scan, specialized to a polygon
    // vertex. Only original polygon vertices are returned; artificial lid
    // intersections are discarded.
    class VisibilityPolygon {
       private:
        enum VertexType { right_lid, left_lid, right_wall, left_wall };

       public:
        VisibilityPolygon(
            const std::vector<Point<T>>& polygon,
            long double eps
        )
            : polygon_(polygon), eps_(eps), size_(polygon.size()) {}

        std::vector<Index> build(Index origin_index) {
            origin_ = &polygon_[origin_index];
            vertices_.clear();
            types_.clear();
            left_lid_index_ = not_saved;
            right_lid_index_ = not_saved;

            int vertex = static_cast<int>(origin_index);
            push(vertex++, right_wall);
            do {
                push(vertex++, right_wall);
                if (vertex >= static_cast<int>(size_ + origin_index)) {
                    break;
                }
                Homogeneous edge = line(vertex - 1, vertex);
                if (left(edge, *origin_)) continue;

                if (!left(edge, point(vertex - 2))) {
                    vertex = exit_right_bay(
                        vertex,
                        top(),
                        Homogeneous{1, 0, 0}
                    );
                    push(vertex++, right_lid);
                    continue;
                }

                save_lid();
                for (;;) {
                    if (
                        orientation(
                            *origin_, top(), point(vertex), eps_
                        ) > 0
                    ) {
                        if (
                            orientation(
                                point(vertex),
                                point(vertex + 1),
                                *origin_,
                                eps_
                            ) < 0
                        ) {
                            ++vertex;
                        } else if (left(edge, point(vertex + 1))) {
                            vertex = exit_left_bay(
                                vertex,
                                point(vertex),
                                line(left_lid_index_, left_lid_index_ - 1)
                            ) + 1;
                        } else {
                            restore_lid();
                            push(vertex++, left_wall);
                            break;
                        }
                        edge = line(vertex - 1, vertex);
                    } else if (!left(edge, top())) {
                        if (right_lid_index_ == not_saved) break;
                        vertex = exit_right_bay(
                            vertex, top(), edge.negated()
                        );
                        push(vertex++, right_lid);
                        break;
                    } else {
                        save_lid();
                    }
                }
            } while (vertex < static_cast<int>(size_ + origin_index));

            std::vector<Index> result;
            while (!vertices_.empty()) {
                while (
                    !vertices_.empty() &&
                    (types_.back() == right_lid ||
                     types_.back() == left_lid)
                ) {
                    vertices_.pop_back();
                    types_.pop_back();
                }
                if (vertices_.empty()) break;
                result.push_back(
                    static_cast<Index>(vertices_.back()) % size_
                );
                vertices_.pop_back();
                types_.pop_back();
            }
            return result;
        }

       private:
        static constexpr int not_saved = -1;

        const std::vector<Point<T>>& polygon_;
        long double eps_;
        Index size_;
        const Point<T>* origin_ = nullptr;
        std::vector<int> vertices_;
        std::vector<VertexType> types_;
        int left_lid_index_ = not_saved;
        int right_lid_index_ = not_saved;

        const Point<T>& point(int index) const {
            int reduced = index % static_cast<int>(size_);
            if (reduced < 0) reduced += static_cast<int>(size_);
            return polygon_[static_cast<Index>(reduced)];
        }
        const Point<T>& top() const { return point(vertices_.back()); }
        Homogeneous line(int first, int second) const {
            return Homogeneous::line(point(first), point(second));
        }
        bool left(
            const Homogeneous& line_value,
            const Point<T>& point_value
        ) const {
            return
                predicate_sign<T>(line_value.side(point_value), eps_) > 0;
        }
        bool right(
            const Homogeneous& line_value,
            const Point<T>& point_value
        ) const {
            return
                predicate_sign<T>(line_value.side(point_value), eps_) < 0;
        }
        bool clockwise(
            const Homogeneous& first,
            const Homogeneous& second,
            const Homogeneous& third
        ) const {
            return predicate_sign<T>(
                Homogeneous::determinant(first, second, third), eps_
            ) < 0;
        }
        void push(int index, VertexType type) {
            vertices_.push_back(index);
            types_.push_back(type);
        }

        void save_lid() {
            if (types_.back() == left_wall) {
                vertices_.pop_back();
                types_.pop_back();
            }
            left_lid_index_ = vertices_.back();
            vertices_.pop_back();
            types_.pop_back();
            if (types_.back() == right_lid) {
                right_lid_index_ = vertices_.back();
                vertices_.pop_back();
                types_.pop_back();
            } else {
                right_lid_index_ = not_saved;
            }
        }

        void restore_lid() {
            if (right_lid_index_ != not_saved) {
                push(right_lid_index_, right_lid);
            }
            push(left_lid_index_, left_lid);
        }

        int exit_right_bay(
            int vertex,
            const Point<T>& bottom,
            const Homogeneous& lid
        ) const {
            int winding = 0;
            const Homogeneous mouth = Homogeneous::line(*origin_, bottom);
            bool current_left = false;
            while (++vertex < 3 * static_cast<int>(size_)) {
                const bool last_left = current_left;
                current_left = left(mouth, point(vertex));
                if (
                    current_left != last_left &&
                    (orientation(
                         point(vertex - 1),
                         point(vertex),
                         *origin_,
                         eps_
                     ) > 0) == current_left
                ) {
                    if (!current_left) {
                        --winding;
                    } else if (winding++ == 0) {
                        const Homogeneous edge = line(vertex - 1, vertex);
                        if (
                            left(edge, bottom) &&
                            !clockwise(mouth, edge, lid)
                        ) {
                            return vertex - 1;
                        }
                    }
                }
            }
            return vertex;
        }

        int exit_left_bay(
            int vertex,
            const Point<T>& bottom,
            const Homogeneous& lid
        ) const {
            int winding = 0;
            const Homogeneous mouth = Homogeneous::line(*origin_, bottom);
            bool current_right = false;
            while (++vertex < 3 * static_cast<int>(size_)) {
                const bool last_right = current_right;
                current_right = right(mouth, point(vertex));
                if (
                    current_right != last_right &&
                    (orientation(
                         point(vertex - 1),
                         point(vertex),
                         *origin_,
                         eps_
                     ) < 0) == current_right
                ) {
                    if (!current_right) {
                        ++winding;
                    } else if (winding-- == 0) {
                        const Homogeneous edge = line(vertex - 1, vertex);
                        if (
                            right(edge, bottom) &&
                            !clockwise(mouth, edge, lid)
                        ) {
                            return vertex - 1;
                        }
                    }
                }
            }
            return vertex;
        }
    };

   public:
    KeilSnoeyinkDecomposition(
        const std::vector<Point<T>>& polygon,
        long double eps
    )
        : polygon_(polygon),
          eps_(eps),
          size_(polygon.size()),
          reflex_(size_, false),
          remapped_(size_) {}

    std::optional<std::vector<Diagonal>> run() {
        initialize_reflex_vertices();
        allocate_states();
        initialize_visibility();
        initialize_base_subproblems();

        for (int span = 3; span < static_cast<int>(size_); ++span) {
            for (const int first : reflex_vertices_) {
                const int last = first + span;
                if (last >= static_cast<int>(size_)) break;
                if (!visible(first, last)) continue;
                initialize_pairs(first, last);
                if (reflex_[last]) {
                    for (int middle = first + 1; middle < last; ++middle) {
                        type_a(first, middle, last);
                    }
                } else {
                    for (const int middle : reflex_vertices_) {
                        if (middle <= first) continue;
                        if (middle >= last - 1) break;
                        type_a(first, middle, last);
                    }
                    type_a(first, last - 1, last);
                }
            }

            for (const int last : reflex_vertices_) {
                if (last < span) continue;
                const int first = last - span;
                if (reflex_[first] || !visible(first, last)) continue;
                initialize_pairs(first, last);
                type_b(first, first + 1, last);
                for (const int middle : reflex_vertices_) {
                    if (middle <= first + 1) continue;
                    if (middle >= last) break;
                    type_b(first, middle, last);
                }
            }
        }

        if (weight(0, static_cast<int>(size_) - 1) >= infinity) {
            return std::nullopt;
        }
        std::vector<Diagonal> diagonals;
        const PairDeque& root = state(0, static_cast<int>(size_) - 1).pairs;
        if (root.pairs.empty()) return std::nullopt;
        flatten(root.pairs.front().solution, diagonals);
        for (Diagonal& diagonal : diagonals) {
            if (diagonal.second < diagonal.first) {
                std::swap(diagonal.first, diagonal.second);
            }
        }
        std::sort(
            diagonals.begin(),
            diagonals.end(),
            [](const Diagonal& first, const Diagonal& second) {
                return std::pair(first.first, first.second) <
                       std::pair(second.first, second.second);
            }
        );
        diagonals.erase(
            std::unique(
                diagonals.begin(),
                diagonals.end(),
                [](const Diagonal& first, const Diagonal& second) {
                    return
                        first.first == second.first &&
                        first.second == second.second;
                }
            ),
            diagonals.end()
        );
        if (
            static_cast<int>(diagonals.size()) !=
            weight(0, static_cast<int>(size_) - 1)
        ) {
            return std::nullopt;
        }
        return diagonals;
    }

   private:
    const std::vector<Point<T>>& polygon_;
    long double eps_;
    Index size_;
    std::vector<bool> reflex_;
    std::vector<int> reflex_vertices_;
    std::vector<int> remapped_;
    std::vector<std::vector<State>> states_;

    void initialize_reflex_vertices() {
        for (int index = 0; index < static_cast<int>(size_); ++index) {
            reflex_[index] = index == 0 || orientation(
                polygon_[(index + static_cast<int>(size_) - 1) % size_],
                polygon_[index],
                polygon_[(index + 1) % size_],
                eps_
            ) < 0;
            if (reflex_[index]) reflex_vertices_.push_back(index);
        }
    }

    void allocate_states() {
        int next = 0;
        for (const int index : reflex_vertices_) remapped_[index] = next++;
        for (int index = 0; index < static_cast<int>(size_); ++index) {
            if (!reflex_[index]) remapped_[index] = next++;
        }
        const int reflex_count = static_cast<int>(reflex_vertices_.size());
        states_.resize(size_);
        for (int index = 0; index < static_cast<int>(size_); ++index) {
            states_[index].resize(reflex_[index] ? size_ : reflex_count);
        }
    }

    State& state(int first, int last) {
        assert(first <= last);
        assert(reflex_[first] || reflex_[last]);
        return states_[first][remapped_[last]];
    }
    const State& state(int first, int last) const {
        assert(first <= last);
        assert(reflex_[first] || reflex_[last]);
        return states_[first][remapped_[last]];
    }
    int weight(int first, int last) const {
        return state(first, last).weight;
    }
    bool visible(int first, int last) const {
        return weight(first, last) < bad;
    }

    void initialize_visibility() {
        VisibilityPolygon visibility_polygon(polygon_, eps_);
        for (const int reflex : reflex_vertices_) {
            for (const Index visible_vertex :
                 visibility_polygon.build(static_cast<Index>(reflex))) {
                int first = reflex;
                int last = static_cast<int>(visible_vertex);
                if (last < first) std::swap(first, last);
                if (first == last) continue;
                state(first, last).weight = infinity;
            }
        }
        // The visibility scan treats the closing edge like every other
        // boundary edge, but make the DP convention explicit.
        state(0, static_cast<int>(size_) - 1).weight = infinity;
    }

    void initialize_base_subproblems() {
        const int size = static_cast<int>(size_);
        for (const int index : reflex_vertices_) {
            if (index + 1 < size) state(index, index + 1).weight = 0;
            if (index > 0) state(index - 1, index).weight = 0;
            if (index + 2 < size && visible(index, index + 2)) {
                State& base = state(index, index + 2);
                base.weight = 0;
                base.pairs.clear();
                base.pairs.push(index + 1, index + 1, nullptr);
            }
            if (index >= 2 && visible(index - 2, index)) {
                State& base = state(index - 2, index);
                base.weight = 0;
                base.pairs.clear();
                base.pairs.push(index - 1, index - 1, nullptr);
            }
        }
    }

    void initialize_pairs(int first, int last) {
        state(first, last).pairs.clear();
    }

    void update(
        int first,
        int last,
        int new_weight,
        int pair_first,
        int pair_second,
        NodePointer solution
    ) {
        State& subproblem = state(first, last);
        if (new_weight > subproblem.weight) return;
        if (new_weight < subproblem.weight) {
            subproblem.weight = new_weight;
            subproblem.pairs.clear();
        }
        subproblem.pairs.push_narrow(
            pair_first, pair_second, std::move(solution)
        );
    }

    NodePointer concatenate(NodePointer first, NodePointer second) const {
        if (!first) return second;
        if (!second) return first;
        SolutionNode node;
        node.first = std::move(first);
        node.second = std::move(second);
        return std::make_shared<const SolutionNode>(std::move(node));
    }

    NodePointer append_diagonal(
        NodePointer solution,
        int first,
        int last
    ) const {
        SolutionNode leaf;
        leaf.diagonal = Diagonal{
            static_cast<Index>(first), static_cast<Index>(last)
        };
        leaf.is_diagonal = true;
        return concatenate(
            std::move(solution),
            std::make_shared<const SolutionNode>(std::move(leaf))
        );
    }

    NodePointer any_solution(int first, int last) const {
        const PairDeque& pairs = state(first, last).pairs;
        assert(!pairs.pairs.empty());
        return pairs.pairs.front().solution;
    }

    void type_a(int first, int middle, int last) {
        if (!visible(first, middle)) return;
        int top = middle;
        int new_weight = weight(first, middle);
        NodePointer solution;
        if (last - middle > 1) {
            if (!visible(middle, last)) return;
            new_weight += weight(middle, last) + 1;
            solution = any_solution(middle, last);
            solution = append_diagonal(
                std::move(solution), middle, last
            );
        }
        bool use_first_diagonal = false;
        if (middle - first > 1) {
            PairDeque& pairs = state(first, middle).pairs;
            if (pairs.empty_back()) return;
            if (
                orientation(
                    polygon_[last],
                    polygon_[middle],
                    polygon_[pairs.back_pair().second],
                    eps_
                ) <= 0
            ) {
                while (
                    pairs.more_back() &&
                    orientation(
                        polygon_[last],
                        polygon_[middle],
                        polygon_[pairs.under_back().second],
                        eps_
                    ) <= 0
                ) {
                    pairs.pop_back();
                }
                if (
                    !pairs.empty_back() &&
                    orientation(
                        polygon_[last],
                        polygon_[first],
                        polygon_[pairs.back_pair().first],
                        eps_
                    ) >= 0
                ) {
                    top = pairs.back_pair().first;
                } else {
                    ++new_weight;
                    use_first_diagonal = true;
                }
            } else {
                ++new_weight;
                use_first_diagonal = true;
            }
            solution = concatenate(
                pairs.back_pair().solution, std::move(solution)
            );
            if (use_first_diagonal) {
                solution = append_diagonal(
                    std::move(solution), first, middle
                );
            }
        }
        update(
            first,
            last,
            new_weight,
            top,
            middle,
            std::move(solution)
        );
    }

    void type_b(int first, int middle, int last) {
        if (!visible(middle, last)) return;
        int top = middle;
        int new_weight = weight(middle, last);
        NodePointer solution;
        if (middle - first > 1) {
            if (!visible(first, middle)) return;
            new_weight += weight(first, middle) + 1;
            solution = any_solution(first, middle);
            solution = append_diagonal(
                std::move(solution), first, middle
            );
        }
        bool use_second_diagonal = false;
        if (last - middle > 1) {
            PairDeque& pairs = state(middle, last).pairs;
            if (pairs.empty_front()) return;
            if (
                orientation(
                    polygon_[first],
                    polygon_[middle],
                    polygon_[pairs.front_pair().first],
                    eps_
                ) >= 0
            ) {
                while (
                    pairs.more_front() &&
                    orientation(
                        polygon_[first],
                        polygon_[middle],
                        polygon_[pairs.under_front().first],
                        eps_
                    ) >= 0
                ) {
                    pairs.pop_front();
                }
                if (
                    !pairs.empty_front() &&
                    orientation(
                        polygon_[first],
                        polygon_[last],
                        polygon_[pairs.front_pair().second],
                        eps_
                    ) <= 0
                ) {
                    top = pairs.front_pair().second;
                } else {
                    ++new_weight;
                    use_second_diagonal = true;
                }
            } else {
                ++new_weight;
                use_second_diagonal = true;
            }
            solution = concatenate(
                std::move(solution), pairs.front_pair().solution
            );
            if (use_second_diagonal) {
                solution = append_diagonal(
                    std::move(solution), middle, last
                );
            }
        }
        update(
            first,
            last,
            new_weight,
            middle,
            top,
            std::move(solution)
        );
    }

    void flatten(
        const NodePointer& node,
        std::vector<Diagonal>& diagonals
    ) const {
        if (!node) return;
        if (node->is_diagonal) {
            diagonals.push_back(node->diagonal);
            return;
        }
        flatten(node->first, diagonals);
        flatten(node->second, diagonals);
    }

};

template <Coordinate T>
std::optional<std::vector<IndexPolygon>> faces_from_diagonals(
    const std::vector<Point<T>>& polygon,
    const std::vector<Diagonal>& diagonals,
    long double eps
) {
    const Index size = polygon.size();
    std::vector<std::vector<Index>> adjacent(size);
    auto add_edge = [&](Index first, Index second) {
        adjacent[first].push_back(second);
        adjacent[second].push_back(first);
    };
    for (Index index = 0; index < size; ++index) {
        add_edge(index, (index + 1) % size);
    }
    for (const Diagonal& diagonal : diagonals) {
        if (
            diagonal.first >= size || diagonal.second >= size ||
            diagonal.first == diagonal.second
        ) {
            return std::nullopt;
        }
        add_edge(diagonal.first, diagonal.second);
    }

    for (Index origin = 0; origin < size; ++origin) {
        auto upper_half = [&](Index target) {
            const auto direction = polygon[target] - polygon[origin];
            const int y_sign = sign<T>(direction.y, eps);
            return
                y_sign > 0 ||
                (y_sign == 0 && sign<T>(direction.x, eps) >= 0);
        };
        std::sort(
            adjacent[origin].begin(),
            adjacent[origin].end(),
            [&](Index first, Index second) {
                const bool first_upper = upper_half(first);
                const bool second_upper = upper_half(second);
                if (first_upper != second_upper) return first_upper;
                const auto first_direction =
                    polygon[first] - polygon[origin];
                const auto second_direction =
                    polygon[second] - polygon[origin];
                const int turn = sign<T>(
                    cross(first_direction, second_direction), eps
                );
                if (turn != 0) return turn > 0;
                return
                    norm2(first_direction) < norm2(second_direction);
            }
        );
        adjacent[origin].erase(
            std::unique(
                adjacent[origin].begin(), adjacent[origin].end()
            ),
            adjacent[origin].end()
        );
    }

    std::vector<std::vector<bool>> visited(size);
    Index directed_edge_count = 0;
    for (Index index = 0; index < size; ++index) {
        visited[index].assign(adjacent[index].size(), false);
        directed_edge_count += adjacent[index].size();
    }

    std::vector<IndexPolygon> result;
    for (Index start = 0; start < size; ++start) {
        for (Index start_position = 0;
             start_position < adjacent[start].size();
             ++start_position) {
            if (visited[start][start_position]) continue;
            IndexPolygon face;
            Index current = start;
            Index position = start_position;
            for (Index guard = 0;; ++guard) {
                if (guard > directed_edge_count) return std::nullopt;
                if (visited[current][position]) {
                    if (current != start || position != start_position) {
                        return std::nullopt;
                    }
                    break;
                }
                visited[current][position] = true;
                face.push_back(current);
                const Index next = adjacent[current][position];
                const auto reverse = std::find(
                    adjacent[next].begin(), adjacent[next].end(), current
                );
                if (reverse == adjacent[next].end()) return std::nullopt;
                const Index reverse_position =
                    static_cast<Index>(reverse - adjacent[next].begin());
                current = next;
                position =
                    (reverse_position + adjacent[current].size() - 1) %
                    adjacent[current].size();
            }
            if (face.size() < 3) continue;
            std::vector<Point<T>> points;
            points.reserve(face.size());
            for (const Index index : face) points.push_back(polygon[index]);
            if (sign<T>(polygon_area2(points), eps) > 0) {
                if (!is_weakly_convex(face, polygon, eps)) {
                    return std::nullopt;
                }
                result.push_back(std::move(face));
            }
        }
    }
    if (result.size() != diagonals.size() + 1) return std::nullopt;
    return result;
}

}  // namespace convex_decomposition_detail

template <Coordinate T>
std::optional<std::vector<std::vector<Point<T>>>>
approximate_convex_decomposition(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
) {
    auto prepared = convex_decomposition_detail::prepare_polygon(
        std::move(polygon), eps
    );
    if (!prepared.has_value()) return std::nullopt;
    polygon = std::move(*prepared);
    if (convex_decomposition_detail::is_weakly_convex(polygon, eps)) {
        return std::vector<std::vector<Point<T>>>{std::move(polygon)};
    }

    auto triangulation =
        convex_decomposition_detail::triangulate_indices(polygon, eps);
    if (!triangulation.has_value()) return std::nullopt;

    using convex_decomposition_detail::Index;
    using convex_decomposition_detail::IndexPolygon;
    const Index triangle_count = triangulation->size();
    const Index absent = std::numeric_limits<Index>::max();
    struct Owners {
        Index first = std::numeric_limits<Index>::max();
        Index second = std::numeric_limits<Index>::max();
    };
    std::map<std::pair<Index, Index>, Owners> edge_owners;
    for (Index triangle = 0; triangle < triangle_count; ++triangle) {
        for (Index edge = 0; edge < 3; ++edge) {
            Index first = (*triangulation)[triangle][edge];
            Index second = (*triangulation)[triangle][(edge + 1) % 3];
            if (second < first) std::swap(first, second);
            Owners& owners = edge_owners[{first, second}];
            if (owners.first == absent) {
                owners.first = triangle;
            } else {
                owners.second = triangle;
            }
        }
    }

    std::vector<Index> parent(triangle_count);
    std::vector<IndexPolygon> pieces = std::move(*triangulation);
    for (Index index = 0; index < triangle_count; ++index) {
        parent[index] = index;
    }
    for (const auto& [edge, owners] : edge_owners) {
        if (owners.second == absent) continue;
        Index first_root =
            convex_decomposition_detail::find_root(parent, owners.first);
        Index second_root =
            convex_decomposition_detail::find_root(parent, owners.second);
        if (first_root == second_root) continue;

        auto merged = convex_decomposition_detail::merge_across_edge(
            pieces[first_root],
            pieces[second_root],
            edge.first,
            edge.second
        );
        if (
            !merged.has_value() ||
            !convex_decomposition_detail::is_weakly_convex(
                *merged, polygon, eps
            )
        ) {
            continue;
        }
        pieces[first_root] = std::move(*merged);
        pieces[second_root].clear();
        parent[second_root] = first_root;
    }

    std::vector<std::vector<Point<T>>> result;
    for (Index index = 0; index < triangle_count; ++index) {
        if (convex_decomposition_detail::find_root(parent, index) != index) {
            continue;
        }
        result.push_back(convex_decomposition_detail::materialize(
            pieces[index], polygon, eps
        ));
    }
    return result;
}

template <Coordinate T>
std::optional<std::vector<std::vector<Point<T>>>>
minimum_convex_decomposition(
    std::vector<Point<T>> polygon,
    long double eps = 1e-12L
) {
    auto prepared = convex_decomposition_detail::prepare_minimum_polygon(
        std::move(polygon), eps
    );
    if (!prepared.has_value()) return std::nullopt;
    polygon = std::move(*prepared);
    if (convex_decomposition_detail::is_weakly_convex(polygon, eps)) {
        return std::vector<std::vector<Point<T>>>{std::move(polygon)};
    }

    std::size_t first_reflex = polygon.size();
    for (std::size_t index = 0; index < polygon.size(); ++index) {
        if (
            orientation(
                polygon[(index + polygon.size() - 1) % polygon.size()],
                polygon[index],
                polygon[(index + 1) % polygon.size()],
                eps
            ) < 0
        ) {
            first_reflex = index;
            break;
        }
    }
    assert(first_reflex < polygon.size());
    std::rotate(
        polygon.begin(), polygon.begin() + first_reflex, polygon.end()
    );

    std::size_t reflex_count = 0;
    for (std::size_t index = 0; index < polygon.size(); ++index) {
        if (
            orientation(
                polygon[(index + polygon.size() - 1) % polygon.size()],
                polygon[index],
                polygon[(index + 1) % polygon.size()],
                eps
            ) < 0
        ) {
            ++reflex_count;
        }
    }

    std::vector<Point<T>> dynamic_polygon = polygon;
    std::vector<convex_decomposition_detail::Index> original_index(
        polygon.size()
    );
    for (std::size_t index = 0; index < polygon.size(); ++index) {
        original_index[index] = index;
    }
    if (
        reflex_count > 0 &&
        polygon.size() / reflex_count > reflex_count
    ) {
        convex_decomposition_detail::BiasedPolygonReduction<T> reduction(
            polygon, eps
        );
        auto reduced = reduction.run();
        dynamic_polygon = std::move(reduced.polygon);
        original_index = std::move(reduced.original_index);
    }

    convex_decomposition_detail::KeilSnoeyinkDecomposition<T> solver(
        dynamic_polygon, eps
    );
    auto diagonals = solver.run();
    if (!diagonals.has_value()) return std::nullopt;
    for (auto& diagonal : *diagonals) {
        diagonal.first = original_index[diagonal.first];
        diagonal.second = original_index[diagonal.second];
    }
    auto index_decomposition =
        convex_decomposition_detail::faces_from_diagonals(
            polygon, *diagonals, eps
        );
    if (!index_decomposition.has_value()) return std::nullopt;

    std::vector<std::vector<Point<T>>> result;
    result.reserve(index_decomposition->size());
    for (const auto& indices : *index_decomposition) {
        result.push_back(convex_decomposition_detail::materialize(
            indices, polygon, eps
        ));
    }
    return result;
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_CONVEX_DECOMPOSITION_HPP
