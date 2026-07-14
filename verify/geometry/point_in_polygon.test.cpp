#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C"

#include "../../geometry/polygon.hpp"

#include "../../utilities/fast_io.hpp"
#include <vector>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    using namespace m1une::geometry;
    int n;
    fast_input >> n;
    std::vector<Point<long long>> polygon(n);
    for (auto& point : polygon) fast_input >> point.x >> point.y;

    int q;
    fast_input >> q;
    while (q--) {
        Point<long long> point;
        fast_input >> point.x >> point.y;
        fast_output << int(point_in_polygon(polygon, point)) << '\n';
    }
}
