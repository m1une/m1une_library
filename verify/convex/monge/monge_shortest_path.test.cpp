// No matching Monge forward-DAG judge target; check against quadratic DP.
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <climits>
#include <memory>
#include <random>
#include <vector>
#include "../../../convex/monge_shortest_path.hpp"
#include "../../../utilities/fast_io.hpp"

constexpr long long infinity = 1LL << 60;

template <class Cost>
void check(int n, int step, Cost raw_cost) {
    std::vector<long long> distance(n, infinity);
    std::vector<int> parent(n, -1);
    if (n) distance[0] = 0;
    for (int j = 1; j < n; ++j) for (int i = 0; i <= j-step; ++i) {
        if (distance[i] == infinity) continue;
        long long candidate = distance[i] + raw_cost(i,j);
        if (candidate < distance[j]) { distance[j] = candidate; parent[j] = i; }
    }
    auto result = m1une::convex::monge_shortest_path(n, [&](int i, int j) {
        assert(0 <= i && i < j && j < n && j-i >= step);
        assert(distance[i] != infinity);
        return raw_cost(i,j);
    }, infinity, step);
    assert(result.distance == distance && result.parent == parent);
    for (int j = 0; j < n; ++j) {
        if (distance[j] == infinity) { assert(parent[j] == -1); continue; }
        long long sum = 0;
        int v = j;
        while (v != 0) {
            int p = result.parent[v];
            assert(0 <= p && p < v && v-p >= step);
            sum += raw_cost(p,v);
            v = p;
        }
        assert(sum == distance[j]);
    }
}

void test_random() {
    std::mt19937 rng(0xA1739);
    for (int n = 0; n <= 70; ++n) for (int trial = 0; trial < 10; ++trial) {
        std::vector<std::vector<long long>> matrix(n, std::vector<long long>(n));
        for (int i = 0; i < n; ++i) {
            matrix[0][i] = int(rng()%101)-50;
            matrix[i][0] = int(rng()%101)-50;
        }
        for (int i = 1; i < n; ++i) for (int j = 1; j < n; ++j) {
            matrix[i][j] = matrix[i-1][j]+matrix[i][j-1]-matrix[i-1][j-1]-int(rng()%5);
        }
        for (int step = 1; step <= n+1; ++step)
            check(n, step, [&](int i, int j) { return matrix[i][j]; });
    }
}

void test_boundaries_and_complexity() {
    auto zero = [](int, int) { return 0LL; };
    for (int n = 0; n <= 100; ++n) {
        for (int d : std::vector<int>{1, 2, 3, 17, n/2+1, n+1, INT_MAX}) {
            check(n, d, zero);
            check(n, d, [](int, int) { return -7LL; });
            check(n, d, [](int, int) { return 1'000'000'000'000LL; });
        }
    }
    const int n = (1 << 17) + 3;
    for (int d : std::vector<int>{1, 2, 17, n/2, n-1, INT_MAX}) {
        long long calls = 0;
        auto result = m1une::convex::monge_shortest_path(n,
            [&](int i, int j) { assert(j-i >= d); ++calls; return 0LL; }, infinity, d);
        assert(calls < 80LL*n);
        for (int j = 1; j < n; ++j) {
            assert(result.parent[j] == (j < d ? -1 : 0));
            assert(result.distance[j] == (j < d ? infinity : 0));
        }
    }
    auto integers = m1une::convex::monge_shortest_path(12,
        [](int, int) { return -1; }, 1'000'000, 2);
    assert(integers.distance.back() == -5);
}

void test_larsch_online() {
    for (int n = 0; n < 200; ++n) {
        int finalized = -1;
        m1une::convex::Larsch optimizer(n, [&, token=std::make_unique<int>(7)](int r, int c) {
            assert(*token == 7 && 0 <= c && c <= r && r < n);
            assert(c <= finalized+1);  // future rows may only use ready columns
            return (r-c)*1LL*(r-c);
        });
        // Moving the primitive must not invalidate stored evaluator references.
        auto moved = std::move(optimizer);
        for (int row = 0; row < n; ++row) {
            assert(moved.next_argmin() == row);
            finalized = row;
        }
        assert(moved.finished());
    }
}

int main() {
    test_random();
    test_boundaries_and_complexity();
    test_larsch_online();
    m1une::utilities::FastInput in;
    m1une::utilities::FastOutput out;
    long long a, b;
    in >> a >> b;
    out << a+b << '\n';
}
