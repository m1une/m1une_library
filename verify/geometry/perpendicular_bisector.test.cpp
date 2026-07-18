#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A"

#include "../../geometry/perpendicular_bisector.hpp"

#include <cassert>
#include <cmath>
#include <concepts>
#include <cstdint>
#include <limits>
#include <numeric>
#include "../../utilities/fast_io.hpp"

namespace {

using namespace m1une::geometry;
using IntegerPoint = Point<long long>;

using IntegerBisectorResult = decltype(
    perpendicular_bisector(IntegerPoint(0, 0), IntegerPoint(1, 1))
);
static_assert(std::same_as<IntegerBisectorResult, Line<long long>>);
constexpr Line<int> constexpr_bisector =
    perpendicular_bisector(Point<int>(0, 0), Point<int>(2, 0));
static_assert(constexpr_bisector.a == Point<int>(1, 0));
static_assert(constexpr_bisector.b == Point<int>(1, 1));

bool close(long double first, long double second) {
    return std::fabs(first - second) <= 1e-12L;
}

void check_floating_bisector(
    const IntegerPoint& integer_first,
    const IntegerPoint& integer_second
) {
    Point<long double> first(integer_first);
    Point<long double> second(integer_second);
    Line<long double> bisector = perpendicular_bisector(first, second);
    Point<long double> expected_midpoint(
        std::midpoint(first.x, second.x),
        std::midpoint(first.y, second.y)
    );

    assert(close(bisector.a.x, expected_midpoint.x));
    assert(close(bisector.a.y, expected_midpoint.y));
    assert(close(dot(second - first, bisector.b - bisector.a), 0));
    assert(close(
        distance2(bisector.a, first),
        distance2(bisector.a, second)
    ));
    assert(close(
        distance2(bisector.b, first),
        distance2(bisector.b, second)
    ));
}

void check_integral_bisector(
    const IntegerPoint& first,
    const IntegerPoint& second
) {
    Line<long long> bisector = perpendicular_bisector(first, second);
    assert(bisector.a != bisector.b);
    assert(distance2(bisector.a, first) == distance2(bisector.a, second));
    assert(distance2(bisector.b, first) == distance2(bisector.b, second));

    Line<long long> original;
    original.a = first;
    original.b = second;
    assert(orthogonal(original, bisector));
}

bool has_lattice_point(
    const IntegerPoint& first,
    const IntegerPoint& second
) {
    long long difference_x = second.x - first.x;
    long long difference_y = second.y - first.y;
    long long divisor = 2 * std::gcd(
        std::abs(difference_x),
        std::abs(difference_y)
    );
    long long right_side =
        second.x * second.x + second.y * second.y -
        first.x * first.x - first.y * first.y;
    return right_side % divisor == 0;
}

void test_fixed() {
    check_floating_bisector(IntegerPoint(0, 0), IntegerPoint(4, 0));
    check_floating_bisector(IntegerPoint(1, 1), IntegerPoint(4, 5));
    check_floating_bisector(IntegerPoint(-7, 3), IntegerPoint(2, -8));

    check_integral_bisector(IntegerPoint(0, 0), IntegerPoint(4, 0));
    check_integral_bisector(IntegerPoint(0, 0), IntegerPoint(1, 1));
    check_integral_bisector(IntegerPoint(-7, 3), IntegerPoint(2, -8));

    Line<long long> diagonal =
        perpendicular_bisector(IntegerPoint(0, 0), IntegerPoint(1, 1));
    assert(diagonal.a == IntegerPoint(1, 0));
    assert(diagonal.b == IntegerPoint(0, 1));

    Line<long long> horizontal =
        perpendicular_bisector(IntegerPoint(0, -3), IntegerPoint(0, 5));
    assert(horizontal.a == IntegerPoint(0, 1));
    assert(horizontal.b.y == 1);

    int int_minimum = std::numeric_limits<int>::lowest();
    int int_maximum = std::numeric_limits<int>::max();
    Line<int> near_upper = perpendicular_bisector(
        Point<int>(0, int_maximum),
        Point<int>(2, int_maximum)
    );
    assert(near_upper.a == Point<int>(1, int_maximum - 1));
    assert(near_upper.b == Point<int>(1, int_maximum));

    Line<int> near_left = perpendicular_bisector(
        Point<int>(int_minimum, 0),
        Point<int>(int_minimum, 2)
    );
    assert(near_left.a == Point<int>(int_minimum + 1, 1));
    assert(near_left.b == Point<int>(int_minimum, 1));

    unsigned unsigned_maximum = std::numeric_limits<unsigned>::max();
    Line<unsigned> unsigned_upper = perpendicular_bisector(
        Point<unsigned>(0, unsigned_maximum),
        Point<unsigned>(2, unsigned_maximum)
    );
    assert(unsigned_upper.a == Point<unsigned>(1, unsigned_maximum - 1));
    assert(unsigned_upper.b == Point<unsigned>(1, unsigned_maximum));
}

void test_randomized() {
    std::uint64_t state = 0x5b8d9f1be2220cbaULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    int integral_cases = 0;
    for (int trial = 0; trial < 10000; ++trial) {
        IntegerPoint first(
            static_cast<long long>(random() % 2001) - 1000,
            static_cast<long long>(random() % 2001) - 1000
        );
        IntegerPoint second;
        do {
            second = IntegerPoint(
                static_cast<long long>(random() % 2001) - 1000,
                static_cast<long long>(random() % 2001) - 1000
            );
        } while (first == second);

        check_floating_bisector(first, second);
        if (has_lattice_point(first, second)) {
            check_integral_bisector(first, second);
            ++integral_cases;
        }
    }
    assert(integral_cases > 1000);
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_fixed();
    test_randomized();

    using namespace m1une::geometry;
    int q;
    fast_input >> q;
    while (q--) {
        Line<long double> first;
        Line<long double> second;
        fast_input >> first.a.x >> first.a.y >> first.b.x >> first.b.y;
        fast_input >> second.a.x >> second.a.y >> second.b.x >> second.b.y;

        Line<long double> bisector =
            perpendicular_bisector(first.a, first.b);
        if (orthogonal(bisector, second)) {
            fast_output << 2 << '\n';
        } else if (parallel(bisector, second)) {
            fast_output << 1 << '\n';
        } else {
            fast_output << 0 << '\n';
        }
    }
}
