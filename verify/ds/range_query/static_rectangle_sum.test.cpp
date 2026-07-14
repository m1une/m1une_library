#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include "../../../ds/range_query/static_rectangle_sum.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include "../../../utilities/fast_io.hpp"
#include <tuple>
#include <vector>

namespace {

using Query = m1une::ds::StaticRectangleSum<int, int, long long>;
using Point = Query::weighted_point_type;

void randomized_test() {
    Query empty;
    assert(empty.empty());
    assert(empty.size() == 0);
    assert(empty.sum(-10, 10, -10, 10) == 0);

    std::uint64_t state = 941;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 500; trial++) {
        int n = int(random() % 50);
        std::vector<Point> points;
        std::vector<int> xs;
        std::vector<int> ys;
        std::vector<long long> weights;
        points.reserve(n);
        xs.reserve(n);
        ys.reserve(n);
        weights.reserve(n);
        for (int index = 0; index < n; index++) {
            int x = int(random() % 31) - 15;
            int y = int(random() % 31) - 15;
            long long weight = static_cast<long long>(random() % 41) - 20;
            points.emplace_back(x, y, weight);
            xs.push_back(x);
            ys.push_back(y);
            weights.push_back(weight);
        }

        Query tuple_query(points);
        Query vector_query(xs, ys, weights);
        assert(tuple_query.size() == n);
        assert(vector_query.size() == n);

        for (int query_index = 0; query_index < 300; query_index++) {
            int left = int(random() % 41) - 20;
            int right = int(random() % 41) - 20;
            int lower = int(random() % 41) - 20;
            int upper = int(random() % 41) - 20;
            if (right < left) std::swap(left, right);
            if (upper < lower) std::swap(lower, upper);

            long long expected = 0;
            for (const auto& point : points) {
                auto [x, y, weight] = point;
                if (left <= x && x < right && lower <= y && y < upper) {
                    expected += weight;
                }
            }
            assert(tuple_query.sum(left, right, lower, upper) == expected);
            assert(vector_query.sum(left, right, lower, upper) == expected);
        }
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    randomized_test();
    int n, query_count;
    fast_input >> n >> query_count;
    std::vector<Point> points;
    points.reserve(n);
    for (int index = 0; index < n; index++) {
        int x, y;
        long long weight;
        fast_input >> x >> y >> weight;
        points.emplace_back(x, y, weight);
    }

    Query rectangle_sum(points);
    while (query_count--) {
        int left, lower, right, upper;
        fast_input >> left >> lower >> right >> upper;
        fast_output << rectangle_sum.sum(left, right, lower, upper) << '\n';
    }
}
