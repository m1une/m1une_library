#define PROBLEM "https://judge.yosupo.jp/problem/closest_pair"

#include "../../geometry/closest_pair.hpp"

#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <optional>
#include <utility>
#include <vector>

namespace {

using Point = m1une::geometry::Point<long long>;
using Result = m1une::geometry::ClosestPair<long long>;

std::optional<Result> brute_force(const std::vector<Point>& points) {
    std::optional<Result> result;
    for (int first = 0; first < int(points.size()); first++) {
        for (int second = first + 1; second < int(points.size()); second++) {
            __int128_t squared =
                m1une::geometry::distance2(points[first], points[second]);
            if (
                !result ||
                squared < result->distance_squared ||
                (
                    squared == result->distance_squared &&
                    std::pair(first, second) <
                        std::pair(result->first, result->second)
                )
            ) {
                result = Result{first, second, squared};
            }
        }
    }
    return result;
}

void check(const std::vector<Point>& points) {
    auto expected = brute_force(points);
    auto actual = m1une::geometry::closest_pair(points);
    assert(expected.has_value() == actual.has_value());
    if (!actual) return;
    assert(actual->first == expected->first);
    assert(actual->second == expected->second);
    assert(actual->distance_squared == expected->distance_squared);
}

void fixed_test() {
    check({});
    check({Point(3, 4)});
    check({Point(0, 0), Point(10, 0)});
    check({Point(2, 3), Point(2, 3), Point(2, 3)});
    check({
        Point(0, 0),
        Point(1, 0),
        Point(1, 1),
        Point(0, 1),
    });
    check({
        Point(-8, 0),
        Point(-3, 0),
        Point(4, 0),
        Point(5, 0),
        Point(20, 0),
    });

    using FloatingPoint = m1une::geometry::Point<long double>;
    std::vector<FloatingPoint> floating_points;
    floating_points.emplace_back(0.0L, 0.0L);
    floating_points.emplace_back(0.5L, 0.0L);
    floating_points.emplace_back(4.0L, 4.0L);
    auto floating_answer = m1une::geometry::closest_pair(floating_points);
    assert(floating_answer.has_value());
    assert(floating_answer->first == 0);
    assert(floating_answer->second == 1);
    assert(floating_answer->distance_squared == 0.25L);
}

void randomized_test() {
    std::uint64_t state = 119;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 800; trial++) {
        int size = int(random() % 31);
        std::vector<Point> points;
        points.reserve(size);
        for (int index = 0; index < size; index++) {
            points.emplace_back(
                static_cast<long long>(random() % 41) - 20,
                static_cast<long long>(random() % 41) - 20
            );
        }
        check(points);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    fixed_test();
    randomized_test();
    int test_count;
    fast_input >> test_count;
    while (test_count--) {
        int n;
        fast_input >> n;
        std::vector<Point> points(n);
        for (Point& point : points) fast_input >> point.x >> point.y;

        auto answer = m1une::geometry::closest_pair(points);
        assert(answer.has_value());
        fast_output << answer->first << ' ' << answer->second << '\n';
    }
}
