#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H"
#define ERROR 0.00001

#include "../../geometry/circle.hpp"

#include <vector>
#include "../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;
    using namespace m1une::geometry;

    int n;
    long long radius;
    fast_input >> n >> radius;
    std::vector<Point<long long>> polygon(n);
    for (Point<long long>& point : polygon) {
        fast_input >> point.x >> point.y;
    }
    Circle<long long> circle;
    circle.center = Point<long long>(0, 0);
    circle.radius = radius;
    fast_output.set_fixed(15);
    fast_output << circle_polygon_intersection_area(circle, polygon) << '\n';
}
