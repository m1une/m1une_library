#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D"
#define ERROR 0.000001

#include "../../geometry/circle.hpp"

#include "../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    using namespace m1une::geometry;
    Circle<long double> circle;
    fast_input >> circle.center.x >> circle.center.y >> circle.radius;

    int q;
    fast_input >> q;
    fast_output.set_fixed(15);
    while (q--) {
        Line<long double> line;
        fast_input >> line.a.x >> line.a.y >> line.b.x >> line.b.y;
        auto points = circle_line_intersections(circle, line);
        if (points.size() == 1) points.push_back(points[0]);
        fast_output << points[0].x << " " << points[0].y << " "
                  << points[1].x << " " << points[1].y << '\n';
    }
}
