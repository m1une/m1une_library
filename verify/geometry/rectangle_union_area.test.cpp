#define PROBLEM "https://judge.yosupo.jp/problem/area_of_union_of_rectangles"

#include "../../geometry/rectangle_union_area.hpp"
#include "../../utilities/fast_io.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>

namespace {

using Rectangle = m1une::geometry::AxisAlignedRectangle<long long>;

long long brute(const std::vector<Rectangle>& rectangles) {
    long long result = 0;
    for (int x = -8; x < 8; x++) {
        for (int y = -8; y < 8; y++) {
            bool covered = false;
            for (const Rectangle& rectangle : rectangles) {
                if (
                    rectangle.left <= x && x < rectangle.right &&
                    rectangle.bottom <= y && y < rectangle.top
                ) {
                    covered = true;
                }
            }
            result += covered;
        }
    }
    return result;
}

void test_edge_cases() {
    std::vector<Rectangle> rectangles;
    assert(m1une::geometry::rectangle_union_area(rectangles) == 0);

    rectangles.emplace_back(0, 0, 4, 3);
    rectangles.emplace_back(2, 1, 6, 5);
    assert(m1une::geometry::rectangle_union_area(rectangles) == 24);

    rectangles.emplace_back(1, 1, 1, 10);
    rectangles.emplace_back(-5, 2, 8, 2);
    assert(m1une::geometry::rectangle_union_area(rectangles) == 24);

    std::vector<Rectangle> large;
    large.emplace_back(
        -4'000'000'000LL,
        -3'000'000'000LL,
        4'000'000'000LL,
        3'000'000'000LL
    );
    __int128 expected = __int128(8'000'000'000LL) * 6'000'000'000LL;
    assert(m1une::geometry::rectangle_union_area(large) == expected);
}

void test_randomized() {
    std::uint64_t state = 1414213562ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 5000; trial++) {
        int count = int(random() % 15);
        std::vector<Rectangle> rectangles;
        for (int i = 0; i < count; i++) {
            long long left = static_cast<long long>(random() % 16) - 8;
            long long right = static_cast<long long>(random() % 16) - 8;
            long long bottom = static_cast<long long>(random() % 16) - 8;
            long long top = static_cast<long long>(random() % 16) - 8;
            if (right < left) std::swap(left, right);
            if (top < bottom) std::swap(bottom, top);
            rectangles.emplace_back(left, bottom, right, top);
        }
        assert(
            m1une::geometry::rectangle_union_area(rectangles)
            == brute(rectangles)
        );
    }
}

}  // namespace

int main() {
    test_edge_cases();
    test_randomized();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    int n = 0;
    input.read(n);
    std::vector<Rectangle> rectangles;
    rectangles.reserve(n);
    for (int i = 0; i < n; i++) {
        long long left = 0, bottom = 0, right = 0, top = 0;
        input.read(left, bottom, right, top);
        rectangles.emplace_back(left, bottom, right, top);
    }
    long long answer = static_cast<long long>(
        m1une::geometry::rectangle_union_area(rectangles)
    );
    output.println(answer);
}
