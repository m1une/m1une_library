#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>

#include "../../heuristic/all.hpp"
#include "../../utilities/random.hpp"

using m1une::heuristic::AnnealingCooling;
using m1une::heuristic::AnnealingObjective;
using m1une::heuristic::SimulatedAnnealing;

bool close(double first, double second) {
    return std::abs(first - second) <=
           1e-12 * std::max(1.0, std::abs(second));
}

void test_temperature() {
    SimulatedAnnealing exponential(100.0, 1.0);
    assert(close(exponential.temperature(0.0), 100.0));
    assert(close(exponential.temperature(0.5), 10.0));
    assert(close(exponential.temperature(1.0), 1.0));

    SimulatedAnnealing linear(100.0, 0.0,
                              AnnealingObjective::maximize,
                              AnnealingCooling::linear);
    assert(close(linear.temperature(0.0), 100.0));
    assert(close(linear.temperature(0.25), 75.0));
    assert(close(linear.temperature(1.0), 0.0));
}

void test_maximization() {
    SimulatedAnnealing annealing(10.0, 10.0);
    assert(annealing.acceptance_probability(3, 4, 0.5) == 1.0);
    assert(annealing.acceptance_probability(3, 3, 0.5) == 1.0);
    assert(close(annealing.acceptance_probability(3, -7, 0.5),
                 std::exp(-1.0)));
    assert(annealing.accept(3, 4, 0.5, 0.999999));
    assert(annealing.accept(3, -7, 0.5, 0.3));
    assert(!annealing.accept(3, -7, 0.5, 0.4));
}

void test_minimization() {
    SimulatedAnnealing annealing(2.0, 2.0,
                                 AnnealingObjective::minimize);
    assert(annealing.acceptance_probability(5, 4, 0.0) == 1.0);
    assert(close(annealing.acceptance_probability(5, 7, 0.0),
                 std::exp(-1.0)));
    assert(annealing.accept_delta(-1.0, 0.0, 0.999999));
    assert(!annealing.accept_delta(2.0, 0.0, 0.4));
}

void test_zero_temperature_and_large_scores() {
    SimulatedAnnealing greedy(1.0, 0.0,
                              AnnealingObjective::maximize,
                              AnnealingCooling::linear);
    assert(greedy.acceptance_probability_delta(-1.0, 1.0) == 0.0);
    assert(!greedy.accept_delta(-1.0, 1.0, 0.0));
    assert(greedy.accept_delta(0.0, 1.0, 0.999999));

    long long low = std::numeric_limits<long long>::min();
    long long high = std::numeric_limits<long long>::max();
    assert(greedy.acceptance_probability(low, high, 1.0) == 1.0);
    assert(greedy.acceptance_probability(high, low, 1.0) == 0.0);
}

void test_randomized_against_formula() {
    m1une::utilities::Random random(0x51a7edULL);
    for (AnnealingObjective objective : {AnnealingObjective::minimize,
                                         AnnealingObjective::maximize}) {
        SimulatedAnnealing annealing(30.0, 0.03, objective);
        for (int trial = 0; trial < 10000; trial++) {
            long long current = random.uniform(-1000000000, 1000000000);
            long long candidate = random.uniform(-1000000000, 1000000000);
            double progress = random.real();
            double random01 = random.real();

            long double delta = static_cast<long double>(candidate) -
                                static_cast<long double>(current);
            long double improvement =
                objective == AnnealingObjective::maximize ? delta : -delta;
            double expected = 1.0;
            if (improvement < 0.0L) {
                expected = std::exp(static_cast<double>(
                    improvement / annealing.temperature(progress)));
            }
            assert(close(annealing.acceptance_probability(
                             current, candidate, progress),
                         expected));
            assert(annealing.accept(current, candidate, progress, random01) ==
                   (random01 < expected));
        }
    }
}

int main() {
    test_temperature();
    test_maximization();
    test_minimization();
    test_zero_temperature_and_large_scores();
    test_randomized_against_formula();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
