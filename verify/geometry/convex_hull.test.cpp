#define PROBLEM "https://judge.yosupo.jp/problem/static_convex_hull"

#include "../../geometry/convex_hull.hpp"

#include "../../utilities/fast_io.hpp"
#include <vector>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    using namespace m1une::geometry;
    int test_count;
    fast_input >> test_count;
    while (test_count--) {
        int size;
        fast_input >> size;
        std::vector<Point<long long>> points(size);
        for (auto& point : points) fast_input >> point.x >> point.y;

        std::vector<Point<long long>> hull = convex_hull(std::move(points));
        fast_output << hull.size() << '\n';
        for (const auto& point : hull) {
            fast_output << point.x << ' ' << point.y << '\n';
        }
    }
}
