#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"

#include <cstdint>
#include <iostream>
#include <optional>

#include "../../convex/li_chao_tree.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int segment_count, query_count;
    std::cin >> segment_count >> query_count;
    constexpr long long left_bound = -1'000'000'000LL;
    constexpr long long right_bound = 1'000'000'001LL;
    m1une::convex::MinLiChaoTree<long long> tree(left_bound, right_bound);

    for (int i = 0; i < segment_count; i++) {
        long long left, right, slope, intercept;
        std::cin >> left >> right >> slope >> intercept;
        tree.add_segment(left, right, slope, intercept);
    }

    while (query_count--) {
        int type;
        std::cin >> type;
        if (type == 0) {
            long long left, right, slope, intercept;
            std::cin >> left >> right >> slope >> intercept;
            tree.add_segment(left, right, slope, intercept);
        } else {
            long long point;
            std::cin >> point;
            std::optional<__int128_t> result = tree.query(point);
            if (result) {
                std::cout << static_cast<long long>(*result) << '\n';
            } else {
                std::cout << "INFINITY\n";
            }
        }
    }
}
