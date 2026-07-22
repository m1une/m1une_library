#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_G"
#define ERROR 0.00001

#include "../../geometry/circle.hpp"

#include "../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;
    using namespace m1une::geometry;

    Circle<long long> first;
    Circle<long long> second;
    fast_input >> first.center.x >> first.center.y >> first.radius;
    fast_input >> second.center.x >> second.center.y >> second.radius;
    auto points = common_tangent_points(first, second);
    fast_output.set_fixed(15);
    for (const Point<long double>& point : points) {
        fast_output << point.x << " " << point.y << '\n';
    }
}
