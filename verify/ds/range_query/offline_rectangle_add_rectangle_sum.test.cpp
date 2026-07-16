#define PROBLEM "https://judge.yosupo.jp/problem/static_rectangle_add_rectangle_sum"

#include "../../../ds/range_query/offline_rectangle_add_rectangle_sum.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>

#include "../../../math/modint.hpp"
#include "../../../utilities/fast_io.hpp"

namespace {

struct Rectangle {
    int x_lower;
    int x_upper;
    int y_lower;
    int y_upper;
    long long value;
};

long long overlap_length(int first_lower, int first_upper, int second_lower, int second_upper) {
    return std::max(0, std::min(first_upper, second_upper) -
                           std::max(first_lower, second_lower));
}

long long naive_sum(
    const std::vector<Rectangle>& updates,
    int x_lower,
    int x_upper,
    int y_lower,
    int y_upper
) {
    long long result = 0;
    for (const Rectangle& update : updates) {
        const long long width = overlap_length(
            update.x_lower, update.x_upper, x_lower, x_upper
        );
        const long long height = overlap_length(
            update.y_lower, update.y_upper, y_lower, y_upper
        );
        result += width * height * update.value;
    }
    return result;
}

void test_randomized() {
    using Solver = m1une::ds::OfflineRectangleAddRectangleSum<long long, int>;

    Solver empty;
    assert(empty.empty());
    assert(empty.update_count() == 0);
    assert(empty.query_count() == 0);
    assert(empty.calculate().empty());

    int empty_query = empty.add_query(-5, 5, -5, 5);
    assert(empty_query == 0);
    assert(empty.calculate() == std::vector<long long>(1, 0));
    empty.clear();
    assert(empty.empty());

    Solver unordered_batch;
    int first_query = unordered_batch.add_query(1, 4, 1, 3);
    unordered_batch.add_rectangle(0, 3, 0, 2, 5);
    assert(unordered_batch.calculate()[first_query] == 10);

    std::uint64_t state = 987654321;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 400; trial++) {
        const int update_count = int(random() % 26);
        const int query_count = int(random() % 31);
        Solver solver;
        solver.reserve_updates(update_count);
        solver.reserve_queries(query_count);
        std::vector<Rectangle> updates;
        std::vector<long long> expected;

        for (int update_id = 0; update_id < update_count; update_id++) {
            int x_lower = int(random() % 21) - 10;
            int x_upper = int(random() % 21) - 10;
            int y_lower = int(random() % 21) - 10;
            int y_upper = int(random() % 21) - 10;
            if (x_upper < x_lower) std::swap(x_lower, x_upper);
            if (y_upper < y_lower) std::swap(y_lower, y_upper);
            long long value = static_cast<long long>(random() % 21) - 10;
            assert(
                solver.add_rectangle(x_lower, x_upper, y_lower, y_upper, value) ==
                update_id
            );
            updates.push_back(Rectangle{x_lower, x_upper, y_lower, y_upper, value});
        }

        for (int query_id = 0; query_id < query_count; query_id++) {
            int x_lower = int(random() % 25) - 12;
            int x_upper = int(random() % 25) - 12;
            int y_lower = int(random() % 25) - 12;
            int y_upper = int(random() % 25) - 12;
            if (x_upper < x_lower) std::swap(x_lower, x_upper);
            if (y_upper < y_lower) std::swap(y_lower, y_upper);
            assert(solver.add_query(x_lower, x_upper, y_lower, y_upper) == query_id);
            expected.push_back(
                naive_sum(updates, x_lower, x_upper, y_lower, y_upper)
            );
        }

        assert(solver.update_count() == update_count);
        assert(solver.query_count() == query_count);
        assert(solver.empty() == (update_count == 0 && query_count == 0));
        assert(solver.calculate() == expected);
        assert(solver.calculate() == expected);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_randomized();

    using Mint = m1une::math::modint998244353;
    using Solver = m1une::ds::OfflineRectangleAddRectangleSum<Mint>;

    int n, q;
    fast_input >> n >> q;
    Solver solver;
    solver.reserve_updates(n);
    solver.reserve_queries(q);
    for (int update = 0; update < n; update++) {
        long long left, lower, right, upper, value;
        fast_input >> left >> lower >> right >> upper >> value;
        solver.add_rectangle(left, right, lower, upper, Mint(value));
    }
    for (int query = 0; query < q; query++) {
        long long left, lower, right, upper;
        fast_input >> left >> lower >> right >> upper;
        solver.add_query(left, right, lower, upper);
    }

    for (const Mint& answer : solver.calculate()) {
        fast_output << answer << '\n';
    }
}
