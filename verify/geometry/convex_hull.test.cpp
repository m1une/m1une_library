#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A"

#include "../../geometry/convex_hull.hpp"

#include <algorithm>
#include "../../utilities/fast_io.hpp"
#include <vector>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    using namespace m1une::geometry;
    int n;
    fast_input >> n;
    std::vector<Point<long long>> points(n);
    for (auto& point : points) fast_input >> point.x >> point.y;

    std::vector<Point<long long>> hull = convex_hull(points, true);
    int start = int(std::min_element(
        hull.begin(),
        hull.end(),
        [](const auto& a, const auto& b) {
            if (a.y != b.y) return a.y < b.y;
            return a.x < b.x;
        }
    ) - hull.begin());

    fast_output << hull.size() << '\n';
    for (int offset = 0; offset < int(hull.size()); offset++) {
        const auto& point = hull[(start + offset) % hull.size()];
        fast_output << point.x << " " << point.y << '\n';
    }
}
