#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"

#include "../../../ds/range_query/fenwick_tree_2d.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <map>
#include <tuple>
#include <utility>
#include <vector>

namespace {

using Point = std::pair<int, int>;

long long rectangle_sum(
    const std::map<Point, long long>& values,
    int x_lower,
    int x_upper,
    int y_lower,
    int y_upper
) {
    long long result = 0;
    for (const auto& [point, value] : values) {
        if (x_lower <= point.first && point.first < x_upper &&
            y_lower <= point.second && point.second < y_upper) {
            result += value;
        }
    }
    return result;
}

void test_edge_cases() {
    m1une::ds::FenwickTree2D<long long> empty;
    assert(empty.empty());
    assert(empty.size() == 0);
    assert(empty.sum(10, 20) == 0);
    assert(empty.sum(-10, 10, -20, 20) == 0);

    std::vector<std::tuple<int, int, long long>> weighted{
        {2, 3, 4},
        {2, 3, 5},
        {-1, 7, 6}
    };
    m1une::ds::FenwickTree2D<long long> fenwick(weighted);
    assert(fenwick.size() == 2);
    assert(fenwick.x_size() == 2);
    assert(fenwick.contains_point(2, 3));
    assert(!fenwick.contains_point(2, 4));
    assert(fenwick.sum(2, 3, 3, 4) == 9);
    assert(fenwick.sum(100, 100) == 15);
}

void test_randomized() {
    std::uint64_t state = 0xc75b921e4a630df8ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 200; trial++) {
        std::vector<Point> points;
        for (int index = 0; index < 50; index++) {
            points.emplace_back(int(random() % 21) - 10, int(random() % 21) - 10);
        }
        m1une::ds::FenwickTree2D<long long> fenwick(points);
        std::map<Point, long long> expected;
        for (const Point& point : points) expected[point] = 0;
        assert(fenwick.size() == int(expected.size()));

        std::vector<Point> distinct_points;
        for (const auto& [point, value] : expected) {
            (void)value;
            distinct_points.push_back(point);
        }

        for (int operation = 0; operation < 500; operation++) {
            if ((random() & 1) == 0) {
                const Point point =
                    distinct_points[std::size_t(random() % distinct_points.size())];
                const long long value = static_cast<long long>(random() % 101) - 50;
                fenwick.add(point.first, point.second, value);
                expected[point] += value;
            } else {
                int x_lower = int(random() % 25) - 12;
                int x_upper = int(random() % 25) - 12;
                int y_lower = int(random() % 25) - 12;
                int y_upper = int(random() % 25) - 12;
                if (x_upper < x_lower) std::swap(x_lower, x_upper);
                if (y_upper < y_lower) std::swap(y_lower, y_upper);
                assert(
                    fenwick.sum(x_lower, x_upper, y_lower, y_upper) ==
                    rectangle_sum(expected, x_lower, x_upper, y_lower, y_upper)
                );
                assert(
                    fenwick.sum(x_upper, y_upper) ==
                    rectangle_sum(expected, -100, x_upper, -100, y_upper)
                );
            }
        }
    }
}

struct Query {
    int type;
    int first;
    int second;
    int third;
    int fourth;
    long long value;
};

}  // namespace

int main() {
    test_edge_cases();
    test_randomized();

    int point_count, query_count;
    std::cin >> point_count >> query_count;
    std::vector<std::tuple<int, int, long long>> initial(
        static_cast<std::size_t>(point_count)
    );
    std::vector<Point> points;
    points.reserve(static_cast<std::size_t>(point_count + query_count));
    for (auto& [x, y, weight] : initial) {
        std::cin >> x >> y >> weight;
        points.emplace_back(x, y);
    }

    std::vector<Query> queries(static_cast<std::size_t>(query_count));
    for (Query& query : queries) {
        std::cin >> query.type;
        if (query.type == 0) {
            std::cin >> query.first >> query.second >> query.value;
            query.third = query.fourth = 0;
            points.emplace_back(query.first, query.second);
        } else {
            std::cin >> query.first >> query.second >> query.third >> query.fourth;
            query.value = 0;
        }
    }

    m1une::ds::FenwickTree2D<long long> fenwick(std::move(points));
    for (const auto& [x, y, weight] : initial) fenwick.add(x, y, weight);

    for (const Query& query : queries) {
        if (query.type == 0) {
            fenwick.add(query.first, query.second, query.value);
        } else {
            std::cout << fenwick.sum(
                query.first,
                query.third,
                query.second,
                query.fourth
            ) << '\n';
        }
    }
}
