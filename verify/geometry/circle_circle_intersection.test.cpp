#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E"
#define ERROR 0.000001

#include "../../geometry/circle.hpp"

#include <algorithm>
#include <cassert>
#include "../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;
    using namespace m1une::geometry;

    Circle<long long> first;
    Circle<long long> second;
    fast_input >> first.center.x >> first.center.y >> first.radius;
    fast_input >> second.center.x >> second.center.y >> second.radius;
    const auto result = circle_boundary_intersection(first, second);
    assert(result.contact_count() >= 1);
    Point<long double> first_point = result.contacts[0].point;
    Point<long double> second_point = result.contact_count() == 1
        ? first_point
        : result.contacts[1].point;
    if (second_point < first_point) std::swap(first_point, second_point);
    fast_output.set_fixed(15);
    fast_output << first_point.x << " " << first_point.y << " "
                << second_point.x << " " << second_point.y << '\n';
}
