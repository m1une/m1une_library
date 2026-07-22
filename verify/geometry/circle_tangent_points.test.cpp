#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_F"
#define ERROR 0.00001

#include "../../geometry/circle.hpp"

#include <cassert>
#include "../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;
    using namespace m1une::geometry;

    Point<long long> point;
    Circle<long long> circle;
    fast_input >> point.x >> point.y;
    fast_input >> circle.center.x >> circle.center.y >> circle.radius;
    auto points = tangent_points(circle, point);
    assert(points.size() == 2);
    fast_output.set_fixed(15);
    for (const Point<long double>& tangent : points) {
        fast_output << tangent.x << " " << tangent.y << '\n';
    }
}
