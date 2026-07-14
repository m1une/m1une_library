#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A"
#define ERROR "1e-8"

#include "../../geometry/line.hpp"

#include "../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    using namespace m1une::geometry;
    Line<long double> line;
    fast_input >> line.a.x >> line.a.y >> line.b.x >> line.b.y;

    int q;
    fast_input >> q;
    fast_output.set_fixed(15);
    while (q--) {
        Point<long double> point;
        fast_input >> point.x >> point.y;
        Point<long double> result = projection(line, point);
        fast_output << result.x << " " << result.y << '\n';
    }
}
