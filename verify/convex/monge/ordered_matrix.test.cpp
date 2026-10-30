// No direct judge target for explicit matrix-order lists or online LARSCH.
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <random>
#include <vector>
#include "../../../convex/all.hpp"
#include "../../../utilities/fast_io.hpp"

void test_orders() {
    std::mt19937 rng(712367);
    for (int h = 0; h <= 30; ++h) for (int w = 0; w <= 30; ++w) {
        // Sparse IDs in independently shuffled orders: answers must be compact
        // in row order, contain original IDs, and never query unlisted cells.
        std::vector<int> rows(h), cols(w), row_rank(3*h+1, -1), col_rank(4*w+1, -1);
        for (int r = 0; r < h; ++r) rows[r] = 3*r+1;
        for (int c = 0; c < w; ++c) cols[c] = 4*c+2;
        std::shuffle(rows.begin(), rows.end(), rng);
        std::shuffle(cols.begin(), cols.end(), rng);
        for (int r = 0; r < h; ++r) row_rank[rows[r]] = r;
        for (int c = 0; c < w; ++c) col_rank[cols[c]] = c;
        std::vector<std::vector<long long>> matrix(h, std::vector<long long>(w));
        if (h && w) {
            for (int r = 0; r < h; ++r) matrix[r][0] = int(rng()%31)-15;
            for (int c = 0; c < w; ++c) matrix[0][c] = int(rng()%31)-15;
            for (int r = 1; r < h; ++r) for (int c = 1; c < w; ++c)
                matrix[r][c] = matrix[r-1][c]+matrix[r][c-1]-matrix[r-1][c-1]-int(rng()%4);
        }
        auto value = [&](int r, int c) {
            assert(row_rank[r] >= 0 && col_rank[c] >= 0);
            return matrix[row_rank[r]][col_rank[c]];
        };
        std::vector<int> expected(h, -1);
        for (int r = 0; r < h; ++r) for (int c : cols) {
            if (expected[r] == -1 || value(rows[r], c) < value(rows[r], expected[r]))
                expected[r] = c;
        }
        assert(m1une::convex::is_monge(rows, cols, value));
        assert(m1une::convex::smawk_row_argmin(rows, cols, value) == expected);
        assert(m1une::convex::monotone_row_argmin(rows, cols, value) == expected);
        auto negative = [&](int r, int c) { return -value(r,c); };
        assert(m1une::convex::is_anti_monge(rows, cols, negative));
        assert(m1une::convex::smawk_row_argmax(rows, cols, negative) == expected);
        assert(m1une::convex::monotone_row_argmax(rows, cols, negative) == expected);
        auto oracle = [&](int r, int a, int b) { return value(r,b) < value(r,a); };
        assert(m1une::convex::smawk_row_select(rows, cols, oracle) == expected);

        std::vector<long long> previous(4*w+1);
        for (int c : cols) previous[c] = int(rng()%81) - 40;
        auto cost = [&](int source, int target) { return value(target, source); };
        auto result = m1une::convex::monge_transition(previous, rows, cols, cost);
        auto monotone = m1une::convex::monotone_transition(previous, rows, cols, cost);
        assert(result.value == monotone.value && result.argmin == monotone.argmin);
        for (int r = 0; r < h; ++r) {
            int best = -1;
            for (int c : cols) {
                if (best == -1 || previous[c]+cost(c,rows[r]) < previous[best]+cost(best,rows[r])) best = c;
            }
            assert(result.argmin[r] == best);
            if (best != -1) assert(result.value[r] == previous[best]+cost(best,rows[r]));
            else assert(result.value[r] == 0);
        }
        auto ties = [](int, int) { return 0; };
        assert(m1une::convex::smawk_row_argmin(rows, cols, ties) ==
               std::vector<int>(h, w ? cols[0] : -1));
        std::fill(previous.begin(), previous.end(), 0);
        auto tied = m1une::convex::monge_transition(previous, rows, cols, ties);
        assert(tied.argmin == std::vector<int>(h, w ? cols[0] : -1));
    }
}

void test_direct_anti_monge() {
    std::mt19937 rng(981234);
    for (int h = 0; h <= 40; ++h) for (int w = 0; w <= 40; ++w) {
        std::vector<long long> previous(w);
        for (auto& v : previous) v = int(rng()%51)-25;
        auto cost = [](int i, int j) { return -(i-j)*1LL*(i-j); };
        auto result = m1une::convex::anti_monge_transition(previous, h, cost);
        for (int j = 0; j < h; ++j) {
            int best = -1;
            for (int i = 0; i < w; ++i) {
                if (best == -1 || previous[i]+cost(i,j) <= previous[best]+cost(best,j)) best = i;
            }
            assert(result.argmin[j] == best);
            if (best != -1) assert(result.value[j] == previous[best]+cost(best,j));
        }
        auto ties = m1une::convex::anti_monge_transition(std::vector<int>(w), h,
            [](int, int) { return 0; });
        assert(ties.argmin == std::vector<int>(h, w-1));
    }
}

int main() {
    test_orders();
    test_direct_anti_monge();
    m1une::utilities::FastInput in;
    m1une::utilities::FastOutput out;
    long long a, b;
    in >> a >> b;
    out << a+b << '\n';
}
