#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"

#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <optional>

#include "../../convex/li_chao_tree.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int segment_count, query_count;
    fast_input >> segment_count >> query_count;
    constexpr long long left_bound = -1'000'000'000LL;
    constexpr long long right_bound = 1'000'000'001LL;
    m1une::convex::MinLiChaoTree<long long> tree(left_bound, right_bound);

    for (int i = 0; i < segment_count; i++) {
        long long left, right, slope, intercept;
        fast_input >> left >> right >> slope >> intercept;
        tree.add_segment(left, right, slope, intercept);
    }

    while (query_count--) {
        int type;
        fast_input >> type;
        if (type == 0) {
            long long left, right, slope, intercept;
            fast_input >> left >> right >> slope >> intercept;
            tree.add_segment(left, right, slope, intercept);
        } else {
            long long point;
            fast_input >> point;
            std::optional<__int128_t> result = tree.query(point);
            if (result) {
                fast_output << static_cast<long long>(*result) << '\n';
            } else {
                fast_output << "INFINITY\n";
            }
        }
    }
}
