#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../geometry/circle.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <numbers>

#include "../../utilities/fast_io.hpp"

namespace {

using namespace m1une::geometry;
using P = Point<long long>;

bool close(long double first, long double second) {
    return std::fabs(first - second) <=
        1e-9L * std::max({1.0L, std::fabs(first), std::fabs(second)});
}

bool close(
    const Point<long double>& first,
    const Point<long double>& second
) {
    return close(distance(first, second), 0.0L);
}

template <Coordinate T>
void validate_coverage(
    const Circle<T>& circle,
    const Circle<T>& enclosure,
    const AngularCoverage& coverage
) {
    const long double full = 2.0L * std::numbers::pi_v<long double>;
    if (coverage.kind == AngularCoverageKind::Empty) return;
    assert(0.0L <= coverage.begin && coverage.begin < full);
    assert(coverage.begin <= coverage.end);
    assert(coverage.end <= coverage.begin + full + 1e-9L);
    if (coverage.kind == AngularCoverageKind::Point) {
        assert(close(coverage.begin, coverage.end));
        assert(
            point_in_circle(
                enclosure,
                circle_point_at(circle, coverage.begin),
                1e-8L
            ) != PointInCircle::Outside
        );
        return;
    }
    if (coverage.kind == AngularCoverageKind::Full) {
        assert(close(angular_measure(coverage), full));
        for (int index = 0; index < 8; ++index) {
            const long double argument = full * index / 8.0L;
            assert(
                point_in_circle(
                    enclosure,
                    circle_point_at(circle, argument),
                    1e-8L
                ) != PointInCircle::Outside
            );
        }
        return;
    }

    assert(coverage.kind == AngularCoverageKind::Arc);
    assert(coverage.begin < coverage.end);
    const long double middle = (coverage.begin + coverage.end) / 2.0L;
    const long double opposite = middle + std::numbers::pi_v<long double>;
    assert(
        point_in_circle(
            enclosure,
            circle_point_at(circle, middle),
            1e-8L
        ) != PointInCircle::Outside
    );
    assert(
        point_in_circle(
            enclosure,
            circle_point_at(circle, opposite),
            1e-8L
        ) == PointInCircle::Outside
    );
}

void test_fixed_circle_pairs() {
    const Circle<long long> first{P(0, 0), 5, false};
    const Circle<long long> second{P(6, 0), 5};
    const CircleCircleIntersection crossing =
        circle_boundary_intersection(first, second);
    assert(crossing.relation == CircleRelation::Intersecting);
    assert(crossing.contact_kind == CircleContactKind::TwoPoints);
    assert(crossing.contact_count() == 2);
    assert(crossing.contacts[0].point == Point<long double>(3, -4));
    assert(crossing.contacts[1].point == Point<long double>(3, 4));
    assert(close(
        circle_point_at(first, crossing.first_inside_second.begin),
        crossing.contacts[0].point
    ));
    assert(close(
        circle_point_at(first, crossing.first_inside_second.end),
        crossing.contacts[1].point
    ));
    validate_coverage(first, second, crossing.first_inside_second);
    validate_coverage(second, first, crossing.second_inside_first);
    assert(close(
        circle_arc_length(first, crossing.first_inside_second),
        first.radius * angular_measure(crossing.first_inside_second)
    ));

    const auto reversed = circle_boundary_intersection(second, first);
    assert(close(
        angular_measure(crossing.first_inside_second),
        angular_measure(reversed.second_inside_first)
    ));
    assert(close(
        angular_measure(crossing.second_inside_first),
        angular_measure(reversed.first_inside_second)
    ));

    const Circle<long long> separate{P(20, 0), 2};
    const auto empty = circle_boundary_intersection(first, separate);
    assert(empty.contact_kind == CircleContactKind::Empty);
    assert(empty.first_inside_second.kind == AngularCoverageKind::Empty);
    assert(empty.second_inside_first.kind == AngularCoverageKind::Empty);

    const Circle<long long> external{P(10, 0), 5};
    const auto external_tangent =
        circle_boundary_intersection(first, external);
    assert(external_tangent.contact_kind == CircleContactKind::Point);
    assert(
        external_tangent.first_inside_second.kind ==
        AngularCoverageKind::Point
    );

    const Circle<long long> small{P(0, 0), 2};
    const auto contained = circle_boundary_intersection(small, first);
    assert(contained.relation == CircleRelation::Contained);
    assert(contained.first_inside_second.kind == AngularCoverageKind::Full);
    assert(contained.second_inside_first.kind == AngularCoverageKind::Empty);

    const Circle<long long> internally_tangent{P(3, 0), 2};
    const auto internal =
        circle_boundary_intersection(internally_tangent, first);
    assert(internal.relation == CircleRelation::InternallyTangent);
    assert(internal.contact_kind == CircleContactKind::Point);
    assert(internal.first_inside_second.kind == AngularCoverageKind::Full);
    assert(internal.second_inside_first.kind == AngularCoverageKind::Point);

    const auto coincident = circle_boundary_intersection(first, first);
    assert(coincident.contact_kind == CircleContactKind::Coincident);
    assert(coincident.first_inside_second.kind == AngularCoverageKind::Full);
    assert(coincident.second_inside_first.kind == AngularCoverageKind::Full);

    const Circle<long long> point_circle{P(2, -3), 0};
    const auto coincident_point =
        circle_boundary_intersection(point_circle, point_circle);
    assert(coincident_point.contact_kind == CircleContactKind::Point);
    assert(coincident_point.contact_count() == 1);
    assert(
        coincident_point.first_inside_second.kind ==
        AngularCoverageKind::Point
    );
}

void test_linear_parameters() {
    const Circle<long long> circle{P(0, 0), 5, false};
    const Line<long long> line{P(-10, 0), P(-9, 0)};
    const auto line_result = circle_boundary_intersection(circle, line);
    assert(line_result.contact_count == 2);
    assert(close(line_result.contacts[0].linear_parameter, 5));
    assert(close(line_result.contacts[1].linear_parameter, 15));
    assert(line_result.contacts[0].point == Point<long double>(-5, 0));
    assert(line_result.contacts[1].point == Point<long double>(5, 0));

    const Ray<long long> ray{P(0, 0), P(1, 0)};
    const auto ray_result = circle_boundary_intersection(circle, ray);
    assert(ray_result.contact_count == 1);
    assert(close(ray_result.contacts[0].linear_parameter, 5));

    const Segment<long long> segment{P(10, 0), P(-10, 0)};
    const auto segment_result =
        circle_boundary_intersection(circle, segment);
    assert(segment_result.contact_count == 2);
    assert(close(segment_result.contacts[0].linear_parameter, 0.25L));
    assert(close(segment_result.contacts[1].linear_parameter, 0.75L));
    assert(segment_result.contacts[0].point == Point<long double>(5, 0));
    assert(segment_result.contacts[1].point == Point<long double>(-5, 0));
}

void test_random_circle_pairs() {
    std::uint64_t state = 0x243f6a8885a308d3ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 20000; ++trial) {
        const Circle<long long> first{
            P(
                static_cast<long long>(random() % 41) - 20,
                static_cast<long long>(random() % 41) - 20
            ),
            static_cast<long long>(random() % 11),
            static_cast<bool>(random() & 1)
        };
        const Circle<long long> second{
            P(
                static_cast<long long>(random() % 41) - 20,
                static_cast<long long>(random() % 41) - 20
            ),
            static_cast<long long>(random() % 11),
            static_cast<bool>(random() & 1)
        };
        const auto result = circle_boundary_intersection(first, second);
        assert(result.relation == circle_relation(first, second));
        assert(result.contact_count() <= 2);
        for (int index = 0; index < result.contact_count(); ++index) {
            const CircleContact& contact = result.contacts[index];
            assert(on_circle(first, contact.point, 1e-8L));
            assert(on_circle(second, contact.point, 1e-8L));
            assert(close(
                circle_point_at(first, contact.first_argument),
                contact.point
            ));
            assert(close(
                circle_point_at(second, contact.second_argument),
                contact.point
            ));
        }
        validate_coverage(first, second, result.first_inside_second);
        validate_coverage(second, first, result.second_inside_first);
    }
}

}  // namespace

int main() {
    test_fixed_circle_pairs();
    test_linear_parameters();
    test_random_circle_pairs();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    long long first, second;
    input >> first >> second;
    output << first + second << '\n';
}
