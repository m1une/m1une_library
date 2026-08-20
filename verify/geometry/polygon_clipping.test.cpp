#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../geometry/polygon.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <limits>
#include <numbers>
#include <vector>

#include "../../utilities/fast_io.hpp"

namespace {

using namespace m1une::geometry;
using P = Point<long long>;

bool close(long double first, long double second) {
    return std::fabs(first - second) <=
        1e-9L * std::max({1.0L, std::fabs(first), std::fabs(second)});
}

Polygon<long long> rectangle(
    long long left,
    long long bottom,
    long long right,
    long long top,
    bool filled = true
) {
    Polygon<long long> result;
    result.vertices.emplace_back(left, bottom);
    result.vertices.emplace_back(right, bottom);
    result.vertices.emplace_back(right, top);
    result.vertices.emplace_back(left, top);
    result.filled = filled;
    return result;
}

bool covered(
    const std::vector<ParameterInterval>& intervals,
    long double parameter
) {
    for (const ParameterInterval& interval : intervals) {
        if (
            interval.begin - 1e-9L <= parameter &&
            parameter <= interval.end + 1e-9L
        ) {
            return true;
        }
    }
    return false;
}

bool covered(
    const std::vector<AngularCoverage>& coverages,
    long double argument
) {
    const long double full = 2.0L * std::numbers::pi_v<long double>;
    argument = normalize_circle_argument(argument);
    for (const AngularCoverage& coverage : coverages) {
        if (coverage.kind == AngularCoverageKind::Full) return true;
        if (coverage.kind == AngularCoverageKind::Point) {
            long double difference = std::fabs(argument - coverage.begin);
            difference = std::min(difference, full - difference);
            if (difference <= 1e-9L) return true;
            continue;
        }
        assert(coverage.kind == AngularCoverageKind::Arc);
        long double lifted = argument;
        if (lifted < coverage.begin) lifted += full;
        if (lifted <= coverage.end + 1e-9L) return true;
    }
    return false;
}

void validate_intervals(const std::vector<ParameterInterval>& intervals) {
    for (std::size_t index = 0; index < intervals.size(); ++index) {
        assert(intervals[index].begin <= intervals[index].end);
        if (index > 0) {
            assert(intervals[index - 1].end < intervals[index].begin);
        }
    }
}

void validate_coverages(const std::vector<AngularCoverage>& coverages) {
    const long double full = 2.0L * std::numbers::pi_v<long double>;
    for (std::size_t index = 0; index < coverages.size(); ++index) {
        const AngularCoverage& coverage = coverages[index];
        assert(0.0L <= coverage.begin && coverage.begin < full);
        assert(coverage.begin <= coverage.end);
        assert(coverage.end <= coverage.begin + full + 1e-9L);
        if (index > 0) {
            assert(coverages[index - 1].begin < coverage.begin);
        }
    }
}

void test_linear_clipping() {
    const Polygon<long long> square = rectangle(0, 0, 4, 4);
    const Line<long long> line{P(-2, 2), P(-1, 2)};
    const std::vector<ParameterInterval> line_parts = clip(line, square);
    assert(line_parts.size() == 1);
    assert(close(line_parts[0].begin, 2));
    assert(close(line_parts[0].end, 6));

    const Ray<long long> ray{P(-2, 2), P(-1, 2)};
    const std::vector<ParameterInterval> ray_parts = clip(ray, square);
    assert(ray_parts.size() == 1);
    assert(close(ray_parts[0].begin, 2));
    assert(close(ray_parts[0].end, 6));

    const Segment<long long> segment{P(-2, 2), P(6, 2)};
    const std::vector<ParameterInterval> segment_parts =
        clip(segment, square);
    assert(segment_parts.size() == 1);
    assert(close(segment_parts[0].begin, 0.25L));
    assert(close(segment_parts[0].end, 0.75L));

    const Segment<long long> inside{P(1, 2), P(3, 2)};
    const std::vector<ParameterInterval> whole = clip(inside, square);
    assert(whole.size() == 1);
    assert(close(whole[0].begin, 0));
    assert(close(whole[0].end, 1));

    const Segment<long long> inside_point{P(2, 2), P(2, 2)};
    const Segment<long long> outside_point{P(7, 2), P(7, 2)};
    assert(clip(inside_point, square).size() == 1);
    assert(clip(outside_point, square).empty());

    const Line<long long> boundary_line{P(-2, 0), P(-1, 0)};
    const std::vector<ParameterInterval> boundary =
        clip(boundary_line, square);
    assert(boundary.size() == 1);
    assert(close(boundary[0].begin, 2));
    assert(close(boundary[0].end, 6));

    const Line<long long> tangent{P(-1, 1), P(0, 0)};
    const std::vector<ParameterInterval> tangent_part =
        clip(tangent, square);
    assert(tangent_part.size() == 1);
    assert(close(tangent_part[0].begin, 1));
    assert(close(tangent_part[0].end, 1));

    Polygon<long long> concave;
    concave.vertices.emplace_back(0, 0);
    concave.vertices.emplace_back(6, 0);
    concave.vertices.emplace_back(6, 6);
    concave.vertices.emplace_back(4, 6);
    concave.vertices.emplace_back(4, 2);
    concave.vertices.emplace_back(2, 2);
    concave.vertices.emplace_back(2, 6);
    concave.vertices.emplace_back(0, 6);
    const Line<long long> through_arms{P(-1, 4), P(0, 4)};
    const std::vector<ParameterInterval> arms =
        clip(through_arms, concave);
    assert(arms.size() == 2);
    assert(close(arms[0].begin, 1));
    assert(close(arms[0].end, 3));
    assert(close(arms[1].begin, 5));
    assert(close(arms[1].end, 7));

    const Polygon<long long> square_boundary = rectangle(0, 0, 4, 4, false);
    const std::vector<ParameterInterval> crossing_boundary =
        clip(line, square_boundary);
    assert(crossing_boundary.size() == 2);
    assert(close(crossing_boundary[0].begin, 2));
    assert(close(crossing_boundary[0].end, 2));
    assert(close(crossing_boundary[1].begin, 6));
    assert(close(crossing_boundary[1].end, 6));
    const std::vector<ParameterInterval> overlapping_boundary =
        clip(boundary_line, square_boundary);
    assert(overlapping_boundary.size() == 1);
    assert(close(overlapping_boundary[0].begin, 2));
    assert(close(overlapping_boundary[0].end, 6));
    assert(clip(inside, square_boundary).empty());
}

void test_circle_clipping() {
    const Polygon<long long> square = rectangle(-2, -2, 2, 2);
    const Circle<long long> inside{P(0, 0), 1, false};
    const std::vector<AngularCoverage> full = clip(inside, square);
    assert(full.size() == 1);
    assert(full[0].kind == AngularCoverageKind::Full);

    const Circle<long double> crossing{
        Point<long double>(0, 0),
        2.5L,
        false
    };
    const std::vector<AngularCoverage> arcs = clip(crossing, square);
    assert(arcs.size() == 4);
    validate_coverages(arcs);
    for (const AngularCoverage& arc : arcs) {
        assert(arc.kind == AngularCoverageKind::Arc);
        const long double middle = (arc.begin + arc.end) / 2.0L;
        assert(contains(square, circle_point_at(crossing, middle), 1e-9L));
    }

    const Circle<long long> outside{P(0, 0), 5, false};
    assert(clip(outside, square).empty());

    const Circle<long long> tangent{P(5, 0), 3, false};
    const std::vector<AngularCoverage> point = clip(tangent, square);
    assert(point.size() == 1);
    assert(point[0].kind == AngularCoverageKind::Point);
    assert(close(point[0].begin, std::numbers::pi_v<long double>));

    const Polygon<long long> boundary = rectangle(-2, -2, 2, 2, false);
    const std::vector<AngularCoverage> contacts = clip(crossing, boundary);
    assert(contacts.size() == 8);
    for (const AngularCoverage& contact : contacts) {
        assert(contact.kind == AngularCoverageKind::Point);
    }

    const Circle<long long> point_inside{P(0, 0), 0, false};
    const Circle<long long> point_outside{P(8, 0), 0, false};
    assert(clip(point_inside, square).size() == 1);
    assert(clip(point_outside, square).empty());
    assert(clip(point_inside, boundary).empty());
}

void test_random_rectangles() {
    std::uint64_t state = 0x70b5b1bc21a2f3d7ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 3000; ++trial) {
        const long long left = static_cast<long long>(random() % 21) - 10;
        const long long bottom = static_cast<long long>(random() % 21) - 10;
        const long long width = 1 + static_cast<long long>(random() % 10);
        const long long height = 1 + static_cast<long long>(random() % 10);
        const Polygon<long long> polygon =
            rectangle(left, bottom, left + width, bottom + height);
        P origin(
            static_cast<long long>(random() % 41) - 20,
            static_cast<long long>(random() % 41) - 20
        );
        P direction(
            static_cast<long long>(random() % 13) - 6,
            static_cast<long long>(random() % 13) - 6
        );
        if (direction == P()) direction.x = 1;
        const Line<long long> line{origin, origin + direction};
        const std::vector<ParameterInterval> intervals = clip(line, polygon);
        validate_intervals(intervals);
        for (int sample = 0; sample < 80; ++sample) {
            const long double parameter = -20.0L + (sample + 0.37L) / 2.0L;
            const Point<long double> point =
                Point<long double>(origin) +
                Point<long double>(direction) * parameter;
            assert(
                covered(intervals, parameter) ==
                contains(polygon, point, 1e-9L)
            );
        }

        const Circle<long double> circle{
            Point<long double>(
                static_cast<long double>(
                    static_cast<long long>(random() % 31) - 15
                ),
                static_cast<long double>(
                    static_cast<long long>(random() % 31) - 15
                )
            ),
            0.25L + static_cast<long double>(random() % 40) / 4.0L,
            false
        };
        const std::vector<AngularCoverage> coverages = clip(circle, polygon);
        validate_coverages(coverages);
        const long double full = 2.0L * std::numbers::pi_v<long double>;
        for (int sample = 0; sample < 80; ++sample) {
            const long double argument =
                full * (sample + 0.371L) / 80.0L;
            assert(
                covered(coverages, argument) ==
                contains(
                    polygon,
                    circle_point_at(circle, argument),
                    1e-9L
                )
            );
        }
    }
}

void test_concave_sampling() {
    Polygon<long long> polygon;
    polygon.vertices.emplace_back(0, 0);
    polygon.vertices.emplace_back(7, 0);
    polygon.vertices.emplace_back(7, 7);
    polygon.vertices.emplace_back(5, 7);
    polygon.vertices.emplace_back(5, 2);
    polygon.vertices.emplace_back(2, 2);
    polygon.vertices.emplace_back(2, 7);
    polygon.vertices.emplace_back(0, 7);

    for (long long origin_x = -2; origin_x <= 8; ++origin_x) {
        for (long long origin_y = -2; origin_y <= 8; ++origin_y) {
            for (long long dx = -2; dx <= 2; ++dx) {
                for (long long dy = -2; dy <= 2; ++dy) {
                    if (dx == 0 && dy == 0) continue;
                    const P origin(origin_x, origin_y);
                    const P direction(dx, dy);
                    const Line<long long> line{
                        origin,
                        origin + direction
                    };
                    const std::vector<ParameterInterval> intervals =
                        clip(line, polygon);
                    validate_intervals(intervals);
                    for (int sample = 0; sample < 50; ++sample) {
                        const long double parameter =
                            -8.0L + (sample + 0.314L) / 3.0L;
                        const Point<long double> point =
                            Point<long double>(origin) +
                            Point<long double>(direction) * parameter;
                        assert(
                            covered(intervals, parameter) ==
                            contains(polygon, point, 1e-9L)
                        );
                    }
                }
            }
        }
    }

    const long double full = 2.0L * std::numbers::pi_v<long double>;
    for (long long center_x = -1; center_x <= 8; ++center_x) {
        for (long long center_y = -1; center_y <= 8; ++center_y) {
            for (int radius_index = 1; radius_index <= 12; ++radius_index) {
                const Circle<long double> circle{
                    Point<long double>(center_x, center_y),
                    radius_index / 2.0L,
                    false
                };
                const std::vector<AngularCoverage> coverages =
                    clip(circle, polygon);
                validate_coverages(coverages);
                for (int sample = 0; sample < 80; ++sample) {
                    const long double argument =
                        full * (sample + 0.271L) / 80.0L;
                    assert(
                        covered(coverages, argument) ==
                        contains(
                            polygon,
                            circle_point_at(circle, argument),
                            1e-9L
                        )
                    );
                }
            }
        }
    }
}

}  // namespace

int main() {
    test_linear_clipping();
    test_circle_clipping();
    test_random_rectangles();
    test_concave_sampling();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    long long first, second;
    input >> first >> second;
    output << first + second << '\n';
}
