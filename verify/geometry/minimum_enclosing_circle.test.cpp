#define PROBLEM "https://judge.yosupo.jp/problem/minimum_enclosing_circle"

#include "../../geometry/minimum_enclosing_circle.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <optional>
#include <vector>

namespace {

using Point = m1une::geometry::Point<long long>;
using Circle = m1une::geometry::Circle<long double>;

bool contains(const Circle& circle, const Point& point) {
    long double squared = m1une::geometry::distance2(
        circle.center,
        m1une::geometry::Point<long double>(point)
    );
    long double radius_squared = circle.radius * circle.radius;
    return squared <= radius_squared + 1e-9L * std::max(1.0L, radius_squared);
}

Circle diameter_circle(const Point& first, const Point& second) {
    m1une::geometry::Point<long double> a(first);
    m1une::geometry::Point<long double> b(second);
    auto center = (a + b) / 2.0L;
    return Circle{center, m1une::geometry::distance(a, b) / 2.0L};
}

std::optional<Circle> circumcircle(
    const Point& first,
    const Point& second,
    const Point& third
) {
    m1une::geometry::Point<long double> a(first);
    m1une::geometry::Point<long double> b(second);
    m1une::geometry::Point<long double> c(third);
    long double denominator = 2.0L * m1une::geometry::cross(a, b, c);
    if (denominator == 0.0L) return std::nullopt;
    long double a_norm = m1une::geometry::norm2(a);
    long double b_norm = m1une::geometry::norm2(b);
    long double c_norm = m1une::geometry::norm2(c);
    m1une::geometry::Point<long double> center(
        (
            a_norm * (b.y - c.y) +
            b_norm * (c.y - a.y) +
            c_norm * (a.y - b.y)
        ) / denominator,
        (
            a_norm * (c.x - b.x) +
            b_norm * (a.x - c.x) +
            c_norm * (b.x - a.x)
        ) / denominator
    );
    return Circle{center, m1une::geometry::distance(center, a)};
}

std::optional<Circle> brute_force(const std::vector<Point>& points) {
    if (points.empty()) return std::nullopt;
    std::optional<Circle> answer;
    auto consider = [&points, &answer](const Circle& candidate) {
        for (const Point& point : points) {
            if (!contains(candidate, point)) return;
        }
        if (!answer || candidate.radius < answer->radius) answer = candidate;
    };

    for (const Point& point : points) {
        consider(Circle{
            m1une::geometry::Point<long double>(point),
            0.0L
        });
    }
    for (int first = 0; first < int(points.size()); first++) {
        for (int second = first + 1; second < int(points.size()); second++) {
            consider(diameter_circle(points[first], points[second]));
        }
    }
    for (int first = 0; first < int(points.size()); first++) {
        for (int second = first + 1; second < int(points.size()); second++) {
            for (int third = second + 1; third < int(points.size()); third++) {
                auto candidate = circumcircle(
                    points[first],
                    points[second],
                    points[third]
                );
                if (candidate) consider(*candidate);
            }
        }
    }
    return answer;
}

void check(const std::vector<Point>& points) {
    auto expected = brute_force(points);
    auto actual = m1une::geometry::minimum_enclosing_circle(points);
    assert(expected.has_value() == actual.has_value());
    if (!actual) return;

    assert(1 <= int(actual->support.size()));
    assert(int(actual->support.size()) <= 3);
    assert(std::is_sorted(actual->support.begin(), actual->support.end()));
    for (int index : actual->support) {
        assert(0 <= index && index < int(points.size()));
        long double boundary_distance = m1une::geometry::distance(
            actual->circle.center,
            m1une::geometry::Point<long double>(points[index])
        );
        assert(
            std::fabs(boundary_distance - actual->circle.radius) <=
            1e-8L * std::max(1.0L, actual->circle.radius)
        );
    }
    for (const Point& point : points) assert(contains(actual->circle, point));
    assert(
        std::fabs(actual->circle.radius - expected->radius) <=
        1e-8L * std::max(1.0L, expected->radius)
    );
    assert(
        m1une::geometry::distance(
            actual->circle.center,
            expected->center
        ) <= 1e-8L * std::max(1.0L, expected->radius)
    );
}

void randomized_test() {
    check({});
    check({Point(2, 5)});
    check({Point(1, 1), Point(1, 1), Point(1, 1)});
    check({Point(0, 0), Point(4, 0), Point(2, 1)});
    check({Point(-3, 0), Point(0, 0), Point(8, 0)});

    std::uint64_t state = 277;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    for (int trial = 0; trial < 1000; trial++) {
        int size = int(random() % 10);
        std::vector<Point> points;
        points.reserve(size);
        for (int index = 0; index < size; index++) {
            points.emplace_back(
                static_cast<long long>(random() % 21) - 10,
                static_cast<long long>(random() % 21) - 10
            );
        }
        check(points);
    }

    using FloatingPoint = m1une::geometry::Point<long double>;
    std::vector<FloatingPoint> floating_points;
    floating_points.emplace_back(0.0L, 0.0L);
    floating_points.emplace_back(2.0L, 0.0L);
    floating_points.emplace_back(1.0L, 1.0L);
    auto floating_answer =
        m1une::geometry::minimum_enclosing_circle(floating_points);
    assert(floating_answer.has_value());
    assert(std::fabs(floating_answer->circle.center.x - 1.0L) <= 1e-12L);
    assert(std::fabs(floating_answer->circle.center.y) <= 1e-12L);
    assert(std::fabs(floating_answer->circle.radius - 1.0L) <= 1e-12L);
}

bool on_boundary(
    const std::vector<Point>& points,
    const std::vector<int>& support,
    int point_index
) {
    const Point& point = points[point_index];
    const Point& first = points[support[0]];
    if (support.size() == 1) return point == first;

    using W = __int128_t;
    const Point& second = points[support[1]];
    if (support.size() == 2) {
        W ux = W(2) * W(point.x) - W(first.x) - W(second.x);
        W uy = W(2) * W(point.y) - W(first.y) - W(second.y);
        W dx = W(first.x) - W(second.x);
        W dy = W(first.y) - W(second.y);
        return ux * ux + uy * uy == dx * dx + dy * dy;
    }

    const Point& third = points[support[2]];
    W ax = W(first.x) - W(point.x);
    W ay = W(first.y) - W(point.y);
    W bx = W(second.x) - W(point.x);
    W by = W(second.y) - W(point.y);
    W cx = W(third.x) - W(point.x);
    W cy = W(third.y) - W(point.y);
    W a_norm = ax * ax + ay * ay;
    W b_norm = bx * bx + by * by;
    W c_norm = cx * cx + cy * cy;
    W determinant =
        ax * (by * c_norm - cy * b_norm) -
        ay * (bx * c_norm - cx * b_norm) +
        a_norm * (bx * cy - by * cx);
    return determinant == 0;
}

}  // namespace

int main() {
    randomized_test();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<Point> points(n);
    for (Point& point : points) std::cin >> point.x >> point.y;

    auto answer = m1une::geometry::minimum_enclosing_circle(points);
    assert(answer.has_value());
    for (int index = 0; index < n; index++) {
        std::cout << (on_boundary(points, answer->support, index) ? '1' : '0');
    }
    std::cout << '\n';
}
