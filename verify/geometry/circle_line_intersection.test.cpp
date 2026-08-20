#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D"
#define ERROR 0.000001

#include "../../geometry/circle.hpp"

#include <algorithm>
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
        const auto result = circle_boundary_intersection(circle, line);
        Point<long double> first = result.contacts[0].point;
        Point<long double> second = result.contact_count == 1
            ? first
            : result.contacts[1].point;
        if (second < first) std::swap(first, second);
        fast_output << first.x << " " << first.y << " "
                  << second.x << " " << second.y << '\n';
    }
}
