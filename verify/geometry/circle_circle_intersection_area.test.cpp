#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_I"
#define ERROR 0.000001

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
    fast_output.set_fixed(15);
    fast_output << circle_circle_intersection_area(first, second) << '\n';
}
