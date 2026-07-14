#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/1283"

#include "../../geometry/half_plane_intersection.hpp"

#include <cmath>
#include "../../utilities/fast_io.hpp"
#include <vector>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    using namespace m1une::geometry;
    using PointType = Point<long double>;

    fast_output.set_fixed(6);
    while (true) {
        int n;
        fast_input >> n;
        if (n == 0) break;

        std::vector<PointType> polygon(n);
        for (PointType& point : polygon) {
            fast_input >> point.x >> point.y;
        }

        long double lower = 0;
        long double upper = 1e9L;
        for (int iteration = 0; iteration < 100; ++iteration) {
            long double middle = (lower + upper) / 2;
            std::vector<Line<long double>> half_planes;
            half_planes.reserve(n);
            for (int index = 0; index < n; ++index) {
                PointType first = polygon[index];
                PointType second = polygon[(index + 1) % n];
                PointType direction = second - first;
                PointType left_normal(-direction.y, direction.x);
                PointType shift = left_normal * (middle / norm(left_normal));
                half_planes.push_back(Line<long double>{
                    first + shift,
                    second + shift,
                });
            }
            auto result = half_plane_intersection(half_planes, 1e-18L);
            if (result.status != HalfPlaneIntersectionStatus::Bounded) {
                upper = middle;
            } else {
                lower = middle;
            }
        }
        fast_output << lower << '\n';
    }
}
