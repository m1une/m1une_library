#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include <cassert>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "../../../ds/range_query/cumulative_sum.hpp"

void test_empty() {
    m1une::ds::CumulativeSum1D<long long> sum1;
    m1une::ds::CumulativeSum2D<long long> sum2;
    m1une::ds::CumulativeSum3D<long long> sum3;
    assert(sum1.empty());
    assert(sum2.empty());
    assert(sum3.empty());
    assert(sum1.sum(0) == 0);
    assert(sum2.sum(0, 0) == 0);
    assert(sum3.sum(0, 0, 0) == 0);
    assert(sum1.sum(0, 0) == 0);
    assert(sum2.sum(0, 0, 0, 0) == 0);
    assert(sum3.sum(0, 0, 0, 0, 0, 0) == 0);
}

void test_2d() {
    std::mt19937 rng(123456789);
    for (int iteration = 0; iteration < 100; ++iteration) {
        const int height = int(rng() % 7);
        const int width = int(rng() % 7);
        std::vector<std::vector<long long>> values(
            height, std::vector<long long>(width)
        );
        for (auto& row : values) {
            for (long long& value : row) value = int(rng() % 21) - 10;
        }

        m1une::ds::CumulativeSum2D<long long> sums(values);
        assert(sums.height() == height);
        assert(sums.width() == (height == 0 ? 0 : width));

        for (int y1 = 0; y1 <= height; ++y1) {
            for (int y2 = y1; y2 <= height; ++y2) {
                for (int x1 = 0; x1 <= sums.width(); ++x1) {
                    for (int x2 = x1; x2 <= sums.width(); ++x2) {
                        long long expected = 0;
                        for (int y = y1; y < y2; ++y) {
                            for (int x = x1; x < x2; ++x) {
                                expected += values[y][x];
                            }
                        }
                        assert(sums.sum(y1, y2, x1, x2) == expected);
                    }
                }
            }
        }
    }
}

void test_3d() {
    std::mt19937 rng(987654321);
    for (int iteration = 0; iteration < 100; ++iteration) {
        const int depth = int(rng() % 5);
        const int height = int(rng() % 5);
        const int width = int(rng() % 5);
        std::vector<std::vector<std::vector<long long>>> values(
            depth,
            std::vector<std::vector<long long>>(
                height, std::vector<long long>(width)
            )
        );
        for (auto& plane : values) {
            for (auto& row : plane) {
                for (long long& value : row) value = int(rng() % 21) - 10;
            }
        }

        m1une::ds::CumulativeSum3D<long long> sums(values);
        assert(sums.depth() == depth);
        assert(sums.height() == (depth == 0 ? 0 : height));
        assert(sums.width() == (depth == 0 || height == 0 ? 0 : width));

        for (int query = 0; query < 200; ++query) {
            int z1 = int(rng() % (sums.depth() + 1));
            int z2 = int(rng() % (sums.depth() + 1));
            int y1 = int(rng() % (sums.height() + 1));
            int y2 = int(rng() % (sums.height() + 1));
            int x1 = int(rng() % (sums.width() + 1));
            int x2 = int(rng() % (sums.width() + 1));
            if (z1 > z2) std::swap(z1, z2);
            if (y1 > y2) std::swap(y1, y2);
            if (x1 > x2) std::swap(x1, x2);

            long long expected = 0;
            for (int z = z1; z < z2; ++z) {
                for (int y = y1; y < y2; ++y) {
                    for (int x = x1; x < x2; ++x) {
                        expected += values[z][y][x];
                    }
                }
            }
            assert(sums.sum(z1, z2, y1, y2, x1, x2) == expected);
        }
    }
}

int main() {
    test_empty();
    test_2d();
    test_3d();

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    if (!(std::cin >> n >> q)) return 0;
    std::vector<long long> values(n);
    for (long long& value : values) std::cin >> value;

    m1une::ds::CumulativeSum<long long> sums(values);
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << sums.sum(l, r) << '\n';
    }
}
