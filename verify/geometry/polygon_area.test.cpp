#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A"

#include "../../geometry/polygon.hpp"

#include "../../utilities/fast_io.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <type_traits>
#include <vector>

namespace {

using namespace m1une::geometry;
using P = Point<long long>;

void test_scaling() {
    Polygon<long long> polygon;
    polygon.vertices.emplace_back(0, 0);
    polygon.vertices.emplace_back(4, 0);
    polygon.vertices.emplace_back(4, 4);
    polygon.vertices.emplace_back(2, 4);
    polygon.vertices.emplace_back(2, 2);
    polygon.vertices.emplace_back(0, 2);
    polygon.filled = false;
    const auto saved = polygon;
    const auto half = polygon * 0.5L;
    static_assert(std::is_same_v<
        decltype(polygon * 0.5L), Polygon<long double>
    >);
    static_assert(std::is_same_v<decltype(2 * polygon), Polygon<long long>>);
    std::vector<Point<long double>> expected;
    expected.emplace_back(0, 0);
    expected.emplace_back(2, 0);
    expected.emplace_back(2, 2);
    expected.emplace_back(1, 2);
    expected.emplace_back(1, 1);
    expected.emplace_back(0, 1);
    assert(half.vertices == expected);
    assert((0.5L * polygon).vertices == expected);
    assert(!half.filled);
    assert(contains(half, Point<long double>(1, 1)));
    assert(!contains(half, Point<long double>(1.5L, 0.5L)));
    assert((half * 2).vertices == (polygon * 1.0L).vertices);

    const auto zero = polygon * 0;
    assert(zero.vertices.size() == polygon.vertices.size());
    assert(!zero.filled);
    for (const auto& vertex : zero.vertices) assert(vertex == P(0, 0));
    const Polygon<long long> empty;
    assert((empty * -2).vertices.empty());
    assert((0.5L * empty).filled);
    assert(polygon.vertices == saved.vertices && polygon.filled == saved.filled);

    std::uint64_t state = 0x6a09e667f3bcc909ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    for (int trial = 0; trial < 1000; ++trial) {
        // Concave L-shaped polygons with an analytically known area.
        const long long width = 2 + random() % 19;
        const long long height = 2 + random() % 19;
        const long long cut_x = 1 + random() % (width - 1);
        const long long cut_y = 1 + random() % (height - 1);
        polygon.vertices = std::vector<P>{
            P(0, 0), P(width, 0), P(width, height),
            P(cut_x, height), P(cut_x, cut_y), P(0, cut_y)
        };
        const P offset(
            static_cast<long long>(random() % 41) - 20,
            static_cast<long long>(random() % 41) - 20
        );
        for (auto& vertex : polygon.vertices) vertex += offset;
        const bool clockwise = random() & 1;
        if (clockwise) std::reverse(polygon.vertices.begin(), polygon.vertices.end());
        polygon.filled = random() & 1;
        const auto original = polygon;
        const long long area2 =
            2 * (width * height - cut_x * (height - cut_y));
        for (long double scalar : {-3.0L, -0.5L, 0.5L, 1.0L, 2.0L}) {
            const auto scaled = scalar * polygon;
            assert(scaled.filled == polygon.filled);
            assert(scaled.vertices.size() == polygon.vertices.size());
            assert(polygon_area2(scaled) ==
                (clockwise ? -area2 : area2) * scalar * scalar);
            assert((polygon * scalar).vertices == scaled.vertices);
            for (int query = 0; query < 10; ++query) {
                const P point(
                    static_cast<long long>(random() % 61) - 30,
                    static_cast<long long>(random() % 61) - 30
                );
                assert(contains(scaled, point * scalar) == contains(polygon, point));
            }
        }
        assert(polygon.vertices == original.vertices);
        assert(polygon.filled == original.filled);
    }
}

}  // namespace

int main() {
    test_scaling();
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    using namespace m1une::geometry;
    int n;
    fast_input >> n;
    Polygon<long long> polygon;
    polygon.vertices.resize(n);
    for (auto& point : polygon.vertices) fast_input >> point.x >> point.y;
    fast_output.set_fixed(1);
    // Judge inputs exercise negative scaling and coordinate-type promotion.
    fast_output << polygon_area((polygon * -2) * 0.5L) << '\n';
}
