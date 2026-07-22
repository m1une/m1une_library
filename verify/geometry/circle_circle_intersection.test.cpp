#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E"
#define ERROR 0.000001

#include "../../geometry/circle.hpp"

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
    auto points = circle_intersections(first, second);
    assert(!points.empty());
    if (points.size() == 1) points.push_back(points.front());
    fast_output.set_fixed(15);
    fast_output << points[0].x << " " << points[0].y << " "
                << points[1].x << " " << points[1].y << '\n';
}
