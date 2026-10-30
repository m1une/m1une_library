// No matching forward anti-Monge shortest-path judge target was found.
// The aplusb fallback runs the focused checks below before handling input.
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <bit>
#include <cassert>
#include <climits>
#include <random>
#include <vector>

#include "../../../convex/monge_shortest_path.hpp"
#include "../../../utilities/fast_io.hpp"

constexpr long long infinity = 1LL << 60;

template <class Cost>
void check(int n, int step, Cost cost) {
    std::vector<long long> distance(n, infinity);
    std::vector<int> parent(n, -1);
    if (n > 0) distance[0] = 0;
    for (int to = 1; to < n; ++to) {
        for (int from = 0; from <= to - step; ++from) {
            if (distance[from] == infinity) continue;
            long long candidate = distance[from] + cost(from, to);
            if (candidate <= distance[to]) {
                distance[to] = candidate;
                parent[to] = from;
            }
        }
    }
    auto result = m1une::convex::anti_monge_shortest_path(
        n,
        [&](int from, int to) {
            assert(0 <= from && from < to && to < n);
            assert(to - from >= step);
            assert(distance[from] != infinity);
            return cost(from, to);
        },
        infinity, step);
    assert(result.distance == distance);
    assert(result.parent == parent);
    for (int j = 0; j < n; ++j) {
        if (distance[j] == infinity) continue;
        long long sum = 0;
        int v = j;
        while (v != 0) {
            int p = result.parent[v];
            assert(0 <= p && p < v && v-p >= step);
            sum += cost(p, v);
            v = p;
        }
        assert(sum == distance[j]);
    }
}

void test_random_anti_monge() {
    std::mt19937 random(0xC0FFEE);
    for (int n = 0; n <= 65; ++n) {
        for (int trial = 0; trial < 8; ++trial) {
            std::vector<std::vector<long long>> matrix(
                n, std::vector<long long>(n));
            for (int i = 0; i < n; ++i) {
                matrix[i][0] = int(random() % 101) - 50;
                matrix[0][i] = int(random() % 101) - 50;
            }
            // Nonnegative mixed second differences generate anti-Monge.
            for (int i = 1; i < n; ++i) {
                for (int j = 1; j < n; ++j) {
                    matrix[i][j] = matrix[i - 1][j] + matrix[i][j - 1] -
                                   matrix[i - 1][j - 1] + random() % 5;
                }
            }
            auto cost = [&](int from, int to) { return matrix[from][to]; };
            for (int step = 1; step <= n + 1; ++step) check(n, step, cost);
        }
    }
}

void test_concave_gap_costs() {
    std::mt19937 random(0x5EED);
    for (int n = 0; n <= 80; ++n) {
        for (int trial = 0; trial < 8; ++trial) {
            std::vector<long long> position(n), source_fee(n), target_fee(n);
            for (int i = 0; i < n; ++i) {
                if (i > 0) position[i] = position[i - 1] + random() % 4;
                source_fee[i] = int(random() % 101) - 50;
                target_fee[i] = int(random() % 101) - 50;
            }
            auto quadratic = [&](int from, int to) {
                long long gap = position[to] - position[from];
                return source_fee[from] + target_fee[to] - gap * gap;
            };
            auto piecewise_linear = [&](int from, int to) {
                long long gap = position[to] - position[from];
                return source_fee[from] + target_fee[to] +
                       std::min(2 * gap, gap + 5);
            };
            for (int step : std::vector<int>{1, 2, 3, n / 2 + 1, n + 1}) {
                check(n, step, quadratic);
                check(n, step, piecewise_linear);
            }
        }
    }
}

void test_exhaustive_concave_sequences() {
    // Enumerate concave gap costs by their nonincreasing first differences.
    // Arbitrary row/column fees retain anti-Monge and vary optimal parents.
    for (int n = 1, count = 1; n <= 8; ++n, count *= 3) {
        for (int mask = 0; mask < count; ++mask) {
            std::vector<long long> gap_cost(n);
            int code = mask;
            long long difference = 3;
            for (int gap = 1; gap < n; ++gap) {
                difference -= code % 3;
                code /= 3;
                gap_cost[gap] = gap_cost[gap - 1] + difference;
            }
            auto cost = [&](int from, int to) {
                return gap_cost[to - from] + (from * 7) % 5 - 2 +
                       (to * 11) % 7 - 3;
            };
            for (int step = 1; step <= n + 1; ++step) check(n, step, cost);
        }
    }
}

void test_large_and_boundaries() {
    auto zero = [](int, int) { return 0LL; };
    check(0, INT_MAX, zero);
    check(12, INT_MAX, zero);
    check(12, 1, zero);
    // Negative constant costs force many edges and exercise DP ordering.
    check(100, 1, [](int, int) { return -7LL; });
    check(100, 2, [](int, int) { return -1'000'000'000'000LL; });
    check(100, 5, [](int, int) { return 1'000'000'000'000LL; });
    auto integers = m1une::convex::anti_monge_shortest_path(
        12, [](int, int) { return -1; }, 1'000'000, 2);
    assert(integers.distance.back() == -5);
    auto defaults = m1une::convex::anti_monge_shortest_path(12, zero, infinity);
    assert(defaults.distance == std::vector<long long>(12, 0));
    for (int i = 1; i < 12; ++i) assert(defaults.parent[i] == i - 1);

    const int n = (1 << 17) + 3;
    for (int step : std::vector<int>{1, 2, 3, 17}) {
        long long evaluations = 0;
        auto result = m1une::convex::anti_monge_shortest_path(
            n,
            [&](int, int) {
                ++evaluations;
                return 0LL;
            },
            infinity, step);
        for (int j = 1; j < n; ++j) {
            if (j < step) {
                assert(result.distance[j] == infinity);
                assert(result.parent[j] == -1);
            } else {
                assert(result.distance[j] == 0);
                int expected = j >= 2 * step ? j - step : 0;
                assert(result.parent[j] == expected);
            }
        }
        // Reject quadratic rectangle scans for fixed small minimum steps.
        assert(evaluations < 24LL * n * std::bit_width(unsigned(n)));
    }
}

int main() {
    test_random_anti_monge();
    test_concave_gap_costs();
    test_exhaustive_concave_sequences();
    test_large_and_boundaries();
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    long long a, b;
    input >> a >> b;
    output << a + b << '\n';
}
