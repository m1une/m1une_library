#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B"

#include "../../geometry/convex_polygon.hpp"

#include "../../utilities/fast_io.hpp"
#include <vector>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int size;
    fast_input >> size;
    using Point = m1une::geometry::Point<long long>;
    std::vector<Point> polygon(size);
    for (Point& point : polygon) fast_input >> point.x >> point.y;
    fast_output << m1une::geometry::is_convex_polygon(polygon) << '\n';
}
