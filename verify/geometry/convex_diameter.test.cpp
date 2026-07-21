#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B"

#include "../../geometry/convex_polygon.hpp"

#include <cmath>
#include "../../utilities/fast_io.hpp"
#include <vector>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int size;
    fast_input >> size;
    using Point = m1une::geometry::Point<long double>;
    std::vector<Point> polygon(size);
    for (Point& point : polygon) fast_input >> point.x >> point.y;

    const long double answer =
        std::sqrt(m1une::geometry::convex_diameter2(std::move(polygon)));
    fast_output.set_fixed(12);
    fast_output << answer << '\n';
}
