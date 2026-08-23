#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>
#include <random>
#include <utility>
#include <vector>

#include "../../optimization/k_project_selection.hpp"
#include "../../utilities/fast_io.hpp"

using Solver = m1une::opt::KProjectSelection<long long>;

struct PairGain {
    int a;
    int b;
    std::vector<std::vector<long long>> gain;
};

void test_basic() {
    Solver solver(std::vector<int>{3, 2});
    solver.add_gain(0, std::vector<long long>{1, 4, 2});
    solver.add_gain(1, std::vector<long long>{-2, 3});

    std::vector<std::vector<long long>> pair_gain(3, std::vector<long long>(2));
    pair_gain[0] = std::vector<long long>{0, 1};
    pair_gain[1] = std::vector<long long>{-1, 3};
    pair_gain[2] = std::vector<long long>{1, 7};
    solver.add_gain(0, 1, pair_gain);

    auto result = solver.solve();
    assert(result.is_feasible());
    assert(result.max_gain == 12);
    assert(result.values == std::vector<int>({2, 1}));

    auto repeated = solver.solve();
    assert(repeated.max_gain == result.max_gain);
    assert(repeated.values == result.values);
}

void test_bounds_and_infeasibility() {
    Solver solver(std::vector<int>{4, 1});
    solver.add_gain(0, std::vector<long long>{0, 5, 9, 20});
    solver.add_gain(1, std::vector<long long>{7});
    solver.force_value_at_least(0, 1);
    solver.force_value_at_most(0, 2);
    auto result = solver.solve();
    assert(result.is_feasible());
    assert(result.max_gain == 16);
    assert(result.values == std::vector<int>({2, 0}));

    Solver impossible(1, 3);
    impossible.force_value(0, 0);
    impossible.force_value(0, 2);
    assert(!impossible.solve().is_feasible());

    Solver empty;
    auto empty_result = empty.solve();
    assert(empty_result.is_feasible());
    assert(empty_result.max_gain == 0);
    assert(empty_result.values.empty());
}

std::vector<std::vector<long long>> make_supermodular_gain(
    int rows,
    int columns,
    std::mt19937& rng
) {
    auto random_value = [&](int low, int high) {
        return static_cast<long long>(
            low + int(rng() % unsigned(high - low + 1))
        );
    };

    std::vector<std::vector<long long>> gain(
        rows,
        std::vector<long long>(columns)
    );
    gain[0][0] = random_value(-5, 5);
    for (int row = 1; row < rows; row++) {
        gain[row][0] = gain[row - 1][0] + random_value(-4, 4);
    }
    for (int column = 1; column < columns; column++) {
        gain[0][column] = gain[0][column - 1] + random_value(-4, 4);
    }
    for (int row = 1; row < rows; row++) {
        for (int column = 1; column < columns; column++) {
            long long mixed = random_value(0, 5);
            gain[row][column] =
                gain[row - 1][column]
                + gain[row][column - 1]
                - gain[row - 1][column - 1]
                + mixed;
        }
    }
    return gain;
}

void test_random_against_bruteforce() {
    std::mt19937 rng(712367821);
    for (int test = 0; test < 240; test++) {
        int n = 1 + int(rng() % 4);
        std::vector<int> counts(n);
        for (int& count : counts) count = 1 + int(rng() % 4);
        Solver solver(counts);

        std::vector<std::vector<long long>> unary(n);
        for (int project = 0; project < n; project++) {
            unary[project].resize(counts[project]);
            for (long long& gain : unary[project]) {
                gain = int(rng() % 17) - 8;
            }
            solver.add_gain(project, unary[project]);
        }

        std::vector<PairGain> pairs;
        for (int a = 0; a < n; a++) {
            for (int b = a + 1; b < n; b++) {
                if (rng() % 3 == 0) continue;
                PairGain term;
                term.a = a;
                term.b = b;
                term.gain = make_supermodular_gain(counts[a], counts[b], rng);
                solver.add_gain(a, b, term.gain);
                pairs.push_back(std::move(term));
            }
        }

        std::vector<int> lower(n, 0);
        std::vector<int> upper = counts;
        for (int& value : upper) value--;
        for (int project = 0; project < n; project++) {
            if (rng() % 5 == 0) {
                lower[project] = int(rng() % unsigned(counts[project]));
                solver.force_value_at_least(project, lower[project]);
            }
            if (rng() % 5 == 0) {
                upper[project] = int(rng() % unsigned(counts[project]));
                solver.force_value_at_most(project, upper[project]);
            }
        }

        bool found = false;
        long long expected = std::numeric_limits<long long>::lowest();
        std::vector<int> values(n);
        std::function<void(int)> enumerate = [&](int project) {
            if (project != n) {
                for (values[project] = 0;
                     values[project] < counts[project];
                     values[project]++) {
                    enumerate(project + 1);
                }
                return;
            }

            for (int i = 0; i < n; i++) {
                if (values[i] < lower[i] || upper[i] < values[i]) return;
            }
            long long total = 0;
            for (int i = 0; i < n; i++) total += unary[i][values[i]];
            for (const auto& term : pairs) {
                total += term.gain[values[term.a]][values[term.b]];
            }
            found = true;
            expected = std::max(expected, total);
        };
        enumerate(0);

        auto result = solver.solve();
        assert(result.is_feasible() == found);
        if (!found) continue;
        assert(result.max_gain == expected);

        long long returned_gain = 0;
        for (int project = 0; project < n; project++) {
            assert(lower[project] <= result.values[project]);
            assert(result.values[project] <= upper[project]);
            returned_gain += unary[project][result.values[project]];
        }
        for (const auto& term : pairs) {
            returned_gain +=
                term.gain[result.values[term.a]][result.values[term.b]];
        }
        assert(returned_gain == expected);
    }
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_basic();
    test_bounds_and_infeasibility();
    test_random_against_bruteforce();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
