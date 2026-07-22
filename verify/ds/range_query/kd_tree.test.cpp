#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_C"

#include "../../../ds/range_query/kd_tree.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <vector>

#include "../../../utilities/fast_io.hpp"

namespace {

using RandomTree = m1une::ds::KdTree<long long, 3>;
using RandomPoint = RandomTree::point_type;

long long distance_squared(
    const RandomPoint& first,
    const RandomPoint& second
) {
    long long result = 0;
    for (int axis = 0; axis < 3; axis++) {
        long long difference = first[axis] - second[axis];
        result += difference * difference;
    }
    return result;
}

void fixed_test() {
    using Tree = m1une::ds::KdTree<int, 2>;
    using Point = Tree::point_type;

    Tree empty;
    Point origin = {0, 0};
    assert(empty.empty());
    assert(empty.size() == 0);
    assert(empty.range_search(origin, origin).empty());
    assert(empty.count(origin, origin) == 0);
    assert(!empty.nearest(origin));
    assert(empty.k_nearest(origin, 0).empty());

    std::vector<Point> points = {
        Point{0, 0},
        Point{2, 0},
        Point{0, 2},
        Point{0, 0},
        Point{-2, 0}
    };
    Tree tree(points);
    assert(tree.size() == 5);
    assert(tree[3] == points[3]);

    Point lower = {-1, -1};
    Point upper = {1, 1};
    std::vector<int> indices = tree.range_search(lower, upper);
    std::sort(indices.begin(), indices.end());
    assert(indices == std::vector<int>({0, 3}));
    assert(tree.count(lower, upper) == 2);

    Point query = {1, 0};
    auto nearest = tree.nearest(query);
    assert(nearest.has_value());
    assert(nearest->index == 0);
    assert(nearest->distance_squared == 1);

    std::vector<Tree::Neighbor> neighbors = tree.k_nearest(query, 3);
    assert(neighbors.size() == 3);
    Tree::Neighbor first_expected{0, 1};
    Tree::Neighbor second_expected{1, 1};
    Tree::Neighbor third_expected{3, 1};
    assert(neighbors[0] == first_expected);
    assert(neighbors[1] == second_expected);
    assert(neighbors[2] == third_expected);

    tree.build({Point{10, 20}});
    assert(tree.size() == 1);
    assert(tree.nearest(origin)->index == 0);
    assert(tree.nearest(origin)->distance_squared == 500);

    using FloatTree = m1une::ds::KdTree<double, 2>;
    using FloatPoint = FloatTree::point_type;
    FloatPoint floating_first = {-0.5, 1.25};
    FloatPoint floating_second = {2.0, 3.0};
    std::vector<FloatPoint> floating_points = {
        floating_first,
        floating_second
    };
    FloatTree floating_tree(floating_points);
    FloatPoint floating_query = {0.0, 1.0};
    auto floating_nearest = floating_tree.nearest(floating_query);
    assert(floating_nearest->index == 0);
    assert(floating_nearest->distance_squared == 0.3125L);
}

void randomized_test() {
    std::uint64_t state = 123456789123456789ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 300; trial++) {
        int n = int(random() % 50);
        std::vector<RandomPoint> points(n);
        for (RandomPoint& point : points) {
            for (long long& coordinate : point) {
                coordinate = static_cast<long long>(random() % 31) - 15;
            }
        }

        RandomTree tree(points);
        assert(tree.size() == n);
        assert(tree.empty() == points.empty());
        for (int index = 0; index < n; index++) {
            assert(tree[index] == points[index]);
        }

        for (int query_index = 0; query_index < 100; query_index++) {
            RandomPoint lower;
            RandomPoint upper;
            RandomPoint query;
            for (int axis = 0; axis < 3; axis++) {
                lower[axis] = static_cast<long long>(random() % 41) - 20;
                upper[axis] = static_cast<long long>(random() % 41) - 20;
                if (upper[axis] < lower[axis]) {
                    std::swap(lower[axis], upper[axis]);
                }
                query[axis] = static_cast<long long>(random() % 41) - 20;
            }

            std::vector<int> expected_range;
            std::vector<RandomTree::Neighbor> expected_neighbors;
            for (int index = 0; index < n; index++) {
                bool inside = true;
                for (int axis = 0; axis < 3; axis++) {
                    inside &= lower[axis] <= points[index][axis]
                        && points[index][axis] < upper[axis];
                }
                if (inside) expected_range.push_back(index);
                expected_neighbors.push_back(RandomTree::Neighbor{
                    index,
                    distance_squared(points[index], query)
                });
            }

            std::vector<int> actual_range = tree.range_search(lower, upper);
            std::sort(actual_range.begin(), actual_range.end());
            assert(actual_range == expected_range);
            assert(tree.count(lower, upper) == int(expected_range.size()));

            std::sort(
                expected_neighbors.begin(),
                expected_neighbors.end(),
                [](const auto& first, const auto& second) {
                    if (first.distance_squared != second.distance_squared) {
                        return first.distance_squared < second.distance_squared;
                    }
                    return first.index < second.index;
                }
            );
            auto nearest = tree.nearest(query);
            if (n == 0) {
                assert(!nearest);
            } else {
                assert(nearest.has_value());
                assert(*nearest == expected_neighbors[0]);
            }

            int k = int(random() % (n + 1));
            std::vector<RandomTree::Neighbor> actual_neighbors =
                tree.k_nearest(query, k);
            expected_neighbors.resize(k);
            assert(actual_neighbors == expected_neighbors);
        }
    }
}

}  // namespace

int main() {
    fixed_test();
    randomized_test();

    using Tree = m1une::ds::KdTree<long long, 2>;
    using Point = Tree::point_type;
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int n;
    fast_input >> n;
    std::vector<Point> points(n);
    for (Point& point : points) fast_input >> point[0] >> point[1];
    Tree tree(points);

    int query_count;
    fast_input >> query_count;
    while (query_count--) {
        long long left, right, lower, upper;
        fast_input >> left >> right >> lower >> upper;
        Point box_lower = {left, lower};
        Point box_upper = {right + 1, upper + 1};
        std::vector<int> result = tree.range_search(box_lower, box_upper);
        std::sort(result.begin(), result.end());
        for (int index : result) fast_output << index << '\n';
        fast_output << '\n';
    }
}
