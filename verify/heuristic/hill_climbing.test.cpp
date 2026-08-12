#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <limits>

#include "../../heuristic/hill_climbing.hpp"
#include "../../utilities/random.hpp"

using m1une::heuristic::HillClimbing;
using m1une::heuristic::Objective;

void test_basic() {
    HillClimbing maximize;
    assert(maximize.accept(10, 11));
    assert(!maximize.accept(10, 10));
    assert(!maximize.accept(10, 9));

    HillClimbing maximize_equal(Objective::maximize, true);
    assert(maximize_equal.accept_delta(1.0));
    assert(maximize_equal.accept_delta(0.0));
    assert(!maximize_equal.accept_delta(-1.0));

    HillClimbing minimize(Objective::minimize);
    assert(minimize.accept(10, 9));
    assert(!minimize.accept(10, 10));
    assert(!minimize.accept(10, 11));

    HillClimbing minimize_equal(Objective::minimize, true);
    assert(minimize_equal.accept_delta(-1.0));
    assert(minimize_equal.accept_delta(0.0));
    assert(!minimize_equal.accept_delta(1.0));
}

void test_extreme_scores() {
    long long low = std::numeric_limits<long long>::min();
    long long high = std::numeric_limits<long long>::max();
    assert(HillClimbing(Objective::maximize).accept(low, high));
    assert(HillClimbing(Objective::minimize).accept(high, low));
}

void test_randomized() {
    m1une::utilities::Random random(0xc11ab1eULL);
    for (bool accept_equal : {false, true}) {
        for (int trial = 0; trial < 20000; trial++) {
            long long current = random.uniform(-1000, 1000);
            long long candidate = random.uniform(-1000, 1000);
            HillClimbing maximize(Objective::maximize, accept_equal);
            HillClimbing minimize(Objective::minimize, accept_equal);
            assert(maximize.accept(current, candidate) ==
                   (accept_equal ? current <= candidate : current < candidate));
            assert(minimize.accept(current, candidate) ==
                   (accept_equal ? candidate <= current : candidate < current));
        }
    }
}

int main() {
    test_basic();
    test_extreme_scores();
    test_randomized();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
