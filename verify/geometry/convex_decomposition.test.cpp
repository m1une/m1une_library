#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B"

#include "../../geometry/convex_decomposition.hpp"
#include "../../geometry/convex_polygon.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
#include <map>
#include <numeric>
#include <vector>

#include "../../utilities/fast_io.hpp"

namespace {

using namespace m1une::geometry;
using P = Point<long long>;

std::vector<P> points_from_indices(
    const std::vector<P>& polygon,
    const std::vector<int>& indices
) {
    std::vector<P> result;
    result.reserve(indices.size());
    for (const int index : indices) result.push_back(polygon[index]);
    return result;
}

std::vector<int> canonical_cycle(std::vector<int> cycle) {
    const auto start = std::min_element(cycle.begin(), cycle.end());
    std::rotate(cycle.begin(), start, cycle.end());
    return cycle;
}

int brute_minimum_decomposition(
    const std::vector<P>& polygon,
    std::vector<int> region,
    std::map<std::vector<int>, int>& memo
) {
    region = canonical_cycle(std::move(region));
    const auto found = memo.find(region);
    if (found != memo.end()) return found->second;

    const std::vector<P> points = points_from_indices(polygon, region);
    if (is_convex_polygon(points)) return memo[region] = 1;

    const int size = static_cast<int>(region.size());
    int answer = std::numeric_limits<int>::max() / 4;
    for (int first = 0; first < size; ++first) {
        for (int last = first + 2; last < size; ++last) {
            if (first == 0 && last + 1 == size) continue;

            std::vector<int> left;
            for (int index = first; index <= last; ++index) {
                left.push_back(region[index]);
            }
            std::vector<int> right;
            for (int index = last; index < size; ++index) {
                right.push_back(region[index]);
            }
            for (int index = 0; index <= first; ++index) {
                right.push_back(region[index]);
            }

            const std::vector<P> left_points =
                points_from_indices(polygon, left);
            const std::vector<P> right_points =
                points_from_indices(polygon, right);
            if (
                polygon_area2(left_points) <= 0 ||
                polygon_area2(right_points) <= 0 ||
                !is_simple_polygon(left_points) ||
                !is_simple_polygon(right_points)
            ) {
                continue;
            }
            answer = std::min(
                answer,
                brute_minimum_decomposition(polygon, left, memo) +
                    brute_minimum_decomposition(polygon, right, memo)
            );
        }
    }
    assert(answer < std::numeric_limits<int>::max() / 4);
    return memo[region] = answer;
}

int brute_minimum_decomposition(const std::vector<P>& polygon) {
    std::vector<int> indices(polygon.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::map<std::vector<int>, int> memo;
    return brute_minimum_decomposition(polygon, indices, memo);
}

void assert_valid_decomposition(
    const std::vector<P>& polygon,
    const std::vector<std::vector<P>>& decomposition
) {
    assert(!decomposition.empty());
    long double area_sum = 0;
    std::vector<Point<long double>> floating_polygon;
    floating_polygon.reserve(polygon.size());
    for (const P& point : polygon) floating_polygon.emplace_back(point);

    for (const auto& part : decomposition) {
        assert(part.size() >= 3);
        assert(polygon_area2(part) > 0);
        assert(is_convex_polygon(part));
        area_sum += polygon_area(part);
        for (const P& point : part) {
            assert(
                point_in_polygon(polygon, point) != PointInPolygon::Outside
            );
        }
        for (std::size_t index = 0; index < part.size(); ++index) {
            const P& first = part[index];
            const P& second = part[(index + 1) % part.size()];
            const Point<long double> midpoint(
                (
                    static_cast<long double>(first.x) +
                    static_cast<long double>(second.x)
                ) / 2,
                (
                    static_cast<long double>(first.y) +
                    static_cast<long double>(second.y)
                ) / 2
            );
            assert(
                point_in_polygon(floating_polygon, midpoint) !=
                PointInPolygon::Outside
            );
        }
    }
    assert(std::fabs(area_sum - polygon_area(polygon)) <= 1e-9L);
}

void test_predicate_width_selection() {
    using PredicateWidth =
        convex_decomposition_detail::ExactPredicateWidth;
    auto selected_for = [](long long coordinate) {
        std::vector<P> points;
        points.emplace_back(coordinate, 0);
        return convex_decomposition_detail::select_exact_predicate_width(
            points
        );
    };

    assert(selected_for(1LL << 29) == PredicateWidth::Int128);
    assert(selected_for(1LL << 30) == PredicateWidth::Int256);
    assert(selected_for(1LL << 61) == PredicateWidth::Int256);
    assert(selected_for(1LL << 62) == PredicateWidth::Int512);
    assert(
        selected_for(std::numeric_limits<long long>::min()) ==
        PredicateWidth::Int512
    );
}

void test_fixed() {
    std::vector<P> convex;
    convex.emplace_back(0, 0);
    convex.emplace_back(5, 0);
    convex.emplace_back(6, 3);
    convex.emplace_back(2, 5);
    convex.emplace_back(-1, 2);
    const auto convex_fast = convex_decomposition(convex);
    const auto convex_exact = minimum_convex_decomposition(convex);
    assert(convex_fast.has_value() && convex_fast->size() == 1);
    assert(convex_exact.has_value() && convex_exact->size() == 1);

    std::vector<P> l_shape;
    l_shape.emplace_back(0, 0);
    l_shape.emplace_back(5, 0);
    l_shape.emplace_back(5, 2);
    l_shape.emplace_back(2, 2);
    l_shape.emplace_back(2, 5);
    l_shape.emplace_back(0, 5);
    const auto l_fast = convex_decomposition(l_shape);
    const auto l_exact = minimum_convex_decomposition(l_shape);
    assert(l_fast.has_value());
    assert(l_exact.has_value() && l_exact->size() == 2);
    assert_valid_decomposition(l_shape, *l_fast);
    assert_valid_decomposition(l_shape, *l_exact);

    std::vector<P> reconstruction_regression;
    reconstruction_regression.emplace_back(50, 0);
    reconstruction_regression.emplace_back(12, 16);
    reconstruction_regression.emplace_back(-2, 10);
    reconstruction_regression.emplace_back(-45, 20);
    reconstruction_regression.emplace_back(-9, -5);
    reconstruction_regression.emplace_back(-8, -40);
    reconstruction_regression.emplace_back(14, -14);
    const auto reconstructed =
        minimum_convex_decomposition(reconstruction_regression);
    assert(reconstructed.has_value() && reconstructed->size() == 3);
    assert_valid_decomposition(reconstruction_regression, *reconstructed);
    using PredicateWidth =
        convex_decomposition_detail::ExactPredicateWidth;
    assert(
        convex_decomposition_detail::select_exact_predicate_width(
            reconstruction_regression
        ) == PredicateWidth::Int128
    );

    std::reverse(l_shape.begin(), l_shape.end());
    l_shape.push_back(l_shape.front());
    const auto clockwise = minimum_convex_decomposition(l_shape);
    assert(clockwise.has_value() && clockwise->size() == 2);

    std::vector<P> redundant;
    redundant.emplace_back(0, 0);
    redundant.emplace_back(2, 0);
    redundant.emplace_back(4, 0);
    redundant.emplace_back(4, 3);
    redundant.emplace_back(0, 3);
    redundant.emplace_back(0, 0);
    const auto cleaned = minimum_convex_decomposition(redundant);
    assert(cleaned.has_value() && cleaned->size() == 1);

    std::vector<P> bow_tie;
    bow_tie.emplace_back(0, 0);
    bow_tie.emplace_back(4, 4);
    bow_tie.emplace_back(0, 4);
    bow_tie.emplace_back(4, 0);
    assert(!convex_decomposition(bow_tie).has_value());
    assert(!minimum_convex_decomposition(bow_tie).has_value());

    std::vector<Point<double>> floating;
    floating.emplace_back(0.0, 0.0);
    floating.emplace_back(5.0, 0.0);
    floating.emplace_back(5.0, 2.0);
    floating.emplace_back(2.0, 2.0);
    floating.emplace_back(2.0, 5.0);
    floating.emplace_back(0.0, 5.0);
    const auto floating_exact = minimum_convex_decomposition(floating);
    assert(floating_exact.has_value() && floating_exact->size() == 2);

    constexpr long long medium_shift = 1'000'000'000'000'000'000LL;
    std::vector<P> medium_translated = reconstruction_regression;
    for (P& point : medium_translated) {
        point.x += medium_shift;
        point.y += medium_shift;
    }
    assert(
        convex_decomposition_detail::select_exact_predicate_width(
            medium_translated
        ) == PredicateWidth::Int256
    );
    const auto medium_exact =
        minimum_convex_decomposition(medium_translated);
    assert(medium_exact.has_value());
    assert(medium_exact->size() == reconstructed->size());
    assert_valid_decomposition(medium_translated, *medium_exact);

    constexpr long long shift = 8'000'000'000'000'000'000LL;
    std::vector<P> translated = reconstruction_regression;
    for (P& point : translated) {
        point.x += shift;
        point.y += shift;
    }
    const auto translated_exact = minimum_convex_decomposition(translated);
    assert(
        convex_decomposition_detail::select_exact_predicate_width(
            translated
        ) == PredicateWidth::Int512
    );
    assert(translated_exact.has_value());
    assert(translated_exact->size() == reconstructed->size());
    assert_valid_decomposition(translated, *translated_exact);
}

void test_exhaustive_small_polygons() {
    std::vector<P> point_set;
    point_set.emplace_back(-5, -1);
    point_set.emplace_back(-3, 5);
    point_set.emplace_back(-1, 1);
    point_set.emplace_back(1, -5);
    point_set.emplace_back(2, 3);
    point_set.emplace_back(5, 1);

    std::vector<int> permutation(point_set.size());
    std::iota(permutation.begin(), permutation.end(), 0);
    int checked = 0;
    do {
        if (permutation.front() != 0) continue;
        std::vector<P> polygon;
        polygon.reserve(point_set.size());
        for (const int index : permutation) {
            polygon.push_back(point_set[index]);
        }
        if (polygon_area2(polygon) <= 0 || !is_simple_polygon(polygon)) {
            continue;
        }

        const int expected = brute_minimum_decomposition(polygon);
        const auto exact = minimum_convex_decomposition(polygon);
        const auto fast = convex_decomposition(polygon);
        assert(exact.has_value());
        assert(fast.has_value());
        assert(static_cast<int>(exact->size()) == expected);
        assert(fast->size() <= 4 * exact->size());
        assert_valid_decomposition(polygon, *exact);
        assert_valid_decomposition(polygon, *fast);
        ++checked;
    } while (std::next_permutation(permutation.begin(), permutation.end()));
    assert(checked >= 1);
}

void test_random_radial_polygons() {
    std::vector<P> directions;
    directions.emplace_back(10, 0);
    directions.emplace_back(6, 8);
    directions.emplace_back(-2, 10);
    directions.emplace_back(-9, 4);
    directions.emplace_back(-9, -5);
    directions.emplace_back(-2, -10);

    unsigned long long state = 0x9e3779b97f4a7c15ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    for (int trial = 0; trial < 500; ++trial) {
        std::vector<P> polygon;
        for (const P& direction : directions) {
            const long long radius =
                1 + static_cast<long long>(random() % 5);
            polygon.emplace_back(
                direction.x * radius,
                direction.y * radius
            );
        }
        assert(polygon_area2(polygon) > 0);
        assert(is_simple_polygon(polygon));

        const int expected = brute_minimum_decomposition(polygon);
        const auto exact = minimum_convex_decomposition(polygon);
        const auto fast = convex_decomposition(polygon);
        assert(exact.has_value());
        assert(fast.has_value());
        assert(static_cast<int>(exact->size()) == expected);
        assert(fast->size() <= 4 * exact->size());
        assert_valid_decomposition(polygon, *exact);
        assert_valid_decomposition(polygon, *fast);
    }
}

void test_reflex_sensitive_reduction() {
    std::vector<P> polygon;
    polygon.emplace_back(10, 0);
    polygon.emplace_back(8, 6);
    polygon.emplace_back(3, 10);
    polygon.emplace_back(0, 0);
    polygon.emplace_back(-8, 6);
    polygon.emplace_back(-10, 0);
    polygon.emplace_back(-8, -6);
    polygon.emplace_back(-3, -10);
    polygon.emplace_back(3, -10);
    polygon.emplace_back(8, -6);
    assert(polygon_area2(polygon) > 0);
    assert(is_simple_polygon(polygon));

    int reflex_count = 0;
    for (std::size_t index = 0; index < polygon.size(); ++index) {
        if (
            orientation(
                polygon[(index + polygon.size() - 1) % polygon.size()],
                polygon[index],
                polygon[(index + 1) % polygon.size()]
            ) < 0
        ) {
            ++reflex_count;
        }
    }
    assert(reflex_count == 1);
    assert(
        polygon.size() >
        static_cast<std::size_t>(reflex_count * reflex_count)
    );

    const auto exact = minimum_convex_decomposition(polygon);
    assert(exact.has_value() && exact->size() == 2);
    assert_valid_decomposition(polygon, *exact);

    std::vector<P> two_reflex;
    two_reflex.emplace_back(10, 0);
    two_reflex.emplace_back(8, 5);
    two_reflex.emplace_back(1, 2);
    two_reflex.emplace_back(0, 10);
    two_reflex.emplace_back(-5, 8);
    two_reflex.emplace_back(-8, 5);
    two_reflex.emplace_back(-10, 0);
    two_reflex.emplace_back(-8, -5);
    two_reflex.emplace_back(-1, -2);
    two_reflex.emplace_back(0, -10);
    two_reflex.emplace_back(5, -8);
    two_reflex.emplace_back(8, -5);
    assert(is_simple_polygon(two_reflex));
    int second_reflex_count = 0;
    for (std::size_t index = 0; index < two_reflex.size(); ++index) {
        if (
            orientation(
                two_reflex[
                    (index + two_reflex.size() - 1) % two_reflex.size()
                ],
                two_reflex[index],
                two_reflex[(index + 1) % two_reflex.size()]
            ) < 0
        ) {
            ++second_reflex_count;
        }
    }
    assert(second_reflex_count == 2);
    assert(
        two_reflex.size() >
        static_cast<std::size_t>(
            second_reflex_count * second_reflex_count
        )
    );

    convex_decomposition_detail::KeilSnoeyinkDecomposition<
        long long, __int128_t
    > direct_solver(two_reflex, 1e-12L);
    const auto direct_diagonals = direct_solver.run();
    const auto reduced_solution =
        minimum_convex_decomposition(two_reflex);
    assert(direct_diagonals.has_value());
    assert(reduced_solution.has_value());
    assert(reduced_solution->size() == direct_diagonals->size() + 1);
    assert_valid_decomposition(two_reflex, *reduced_solution);
}

}  // namespace

int main() {
    test_predicate_width_selection();
    test_fixed();
    test_exhaustive_small_polygons();
    test_random_radial_polygons();
    test_reflex_sensitive_reduction();

    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;
    int size;
    fast_input >> size;
    std::vector<P> polygon(size);
    for (P& point : polygon) fast_input >> point.x >> point.y;
    fast_output << (is_convex_polygon(polygon) ? 1 : 0) << '\n';
}
