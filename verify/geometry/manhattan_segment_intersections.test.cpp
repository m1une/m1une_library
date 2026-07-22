#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_6_A"

#include "../../geometry/manhattan_segment_intersections.hpp"
#include "../../utilities/fast_io.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <vector>

namespace {

using Point = m1une::geometry::Point<long long>;
using Segment = m1une::geometry::Segment<long long>;

bool perpendicular_intersection(const Segment& first, const Segment& second) {
    const Segment* vertical = &first;
    const Segment* horizontal = &second;
    if (vertical->a.y == vertical->b.y) std::swap(vertical, horizontal);
    if (
        vertical->a.x != vertical->b.x ||
        horizontal->a.y != horizontal->b.y
    ) {
        return false;
    }

    long long left = std::min(horizontal->a.x, horizontal->b.x);
    long long right = std::max(horizontal->a.x, horizontal->b.x);
    long long bottom = std::min(vertical->a.y, vertical->b.y);
    long long top = std::max(vertical->a.y, vertical->b.y);
    return left <= vertical->a.x && vertical->a.x <= right &&
           bottom <= horizontal->a.y && horizontal->a.y <= top;
}

std::vector<Point> brute(const std::vector<Segment>& segments) {
    std::vector<Point> result;
    for (int i = 0; i < int(segments.size()); i++) {
        for (int j = 0; j < i; j++) {
            if (!perpendicular_intersection(segments[i], segments[j])) {
                continue;
            }
            const Segment* vertical = &segments[i];
            const Segment* horizontal = &segments[j];
            if (vertical->a.y == vertical->b.y) {
                std::swap(vertical, horizontal);
            }
            result.emplace_back(vertical->a.x, horizontal->a.y);
        }
    }
    std::sort(result.begin(), result.end());
    return result;
}

void check(const std::vector<Segment>& segments) {
    std::vector<Point> expected = brute(segments);
    std::vector<Point> actual =
        m1une::geometry::manhattan_segment_intersection_points(segments);
    std::sort(actual.begin(), actual.end());
    assert(actual == expected);
    assert(
        m1une::geometry::manhattan_segment_intersections(segments) ==
        static_cast<long long>(expected.size())
    );
}

void test_fixed() {
    check({});
    check({Segment{Point(0, -1), Point(0, 1)}});

    std::vector<Segment> sample;
    sample.push_back(Segment{Point(2, 2), Point(2, 5)});
    sample.push_back(Segment{Point(1, 3), Point(5, 3)});
    sample.push_back(Segment{Point(4, 1), Point(4, 4)});
    sample.push_back(Segment{Point(5, 2), Point(7, 2)});
    sample.push_back(Segment{Point(6, 1), Point(6, 3)});
    sample.push_back(Segment{Point(6, 5), Point(6, 7)});
    check(sample);
    assert(m1une::geometry::manhattan_segment_intersections(sample) == 3);

    std::vector<Segment> endpoint_touches;
    endpoint_touches.push_back(Segment{Point(0, 0), Point(0, 2)});
    endpoint_touches.push_back(Segment{Point(-3, 0), Point(0, 0)});
    endpoint_touches.push_back(Segment{Point(0, 2), Point(4, 2)});
    check(endpoint_touches);
    assert(
        m1une::geometry::manhattan_segment_intersections(endpoint_touches) == 2
    );

    long long low = std::numeric_limits<long long>::min();
    long long high = std::numeric_limits<long long>::max();
    std::vector<Segment> limits;
    limits.push_back(Segment{Point(low, low), Point(low, high)});
    limits.push_back(Segment{Point(low, 0), Point(high, 0)});
    check(limits);
}

void test_randomized() {
    std::uint64_t state = 1732050807ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 5000; trial++) {
        int count = int(random() % 31);
        std::vector<Segment> segments;
        segments.reserve(count);
        for (int i = 0; i < count; i++) {
            long long first = static_cast<long long>(random() % 21) - 10;
            long long second = static_cast<long long>(random() % 21) - 10;
            if (first == second) second++;
            long long fixed = static_cast<long long>(random() % 21) - 10;
            if (random() & 1) {
                segments.push_back(
                    Segment{Point(fixed, first), Point(fixed, second)}
                );
            } else {
                segments.push_back(
                    Segment{Point(first, fixed), Point(second, fixed)}
                );
            }
        }
        check(segments);
    }
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    int n = 0;
    input.read(n);
    std::vector<Segment> segments;
    segments.reserve(n);
    for (int i = 0; i < n; i++) {
        long long x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        input.read(x1, y1, x2, y2);
        segments.push_back(Segment{Point(x1, y1), Point(x2, y2)});
    }
    output.println(
        m1une::geometry::manhattan_segment_intersections(segments)
    );
}
