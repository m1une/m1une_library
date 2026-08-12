#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../heuristic/beam_search.hpp"
#include "../../utilities/random.hpp"

using m1une::heuristic::Objective;
using m1une::heuristic::beam_search;

auto digit_expander(int radix) {
    return [radix](const std::string& state, int, auto emit) {
        for (int digit = 0; digit < radix; digit++) {
            std::string candidate = state;
            candidate.push_back(static_cast<char>('0' + digit));
            emit(std::move(candidate));
        }
    };
}

auto digit_range_expander(int radix) {
    return [radix](const std::string& state, int) {
        std::vector<std::string> result;
        result.reserve(radix);
        for (int digit = 0; digit < radix; digit++) {
            result.push_back(state + static_cast<char>('0' + digit));
        }
        return result;
    };
}

int digit_value(const std::string& state) {
    int result = 0;
    for (char digit : state) result = result * 10 + digit - '0';
    return result;
}

void test_objectives_and_statistics() {
    auto maximize = beam_search(std::string(), 3, 2, digit_range_expander(3),
                                digit_value, Objective::maximize);
    assert(maximize.state == "222");
    assert(maximize.score == 222);
    assert(maximize.depth == 3);
    assert(maximize.expanded_states == 5);
    assert(maximize.generated_states == 15);

    auto minimize = beam_search(std::string(), 3, 2, digit_range_expander(3),
                                digit_value, Objective::minimize);
    assert(minimize.state == "000");
    assert(minimize.score == 0);
}

void test_early_stop_and_zero_depth() {
    auto expand_once = [](const int& state, int depth, auto emit) {
        if (depth == 1) {
            emit(state + 3);
            emit(state + 5);
        }
    };
    auto identity = [](const int& state) { return state; };

    auto stopped = beam_search(0, 10, 4, expand_once, identity);
    assert(stopped.state == 5);
    assert(stopped.depth == 1);
    assert(stopped.expanded_states == 3);
    assert(stopped.generated_states == 2);

    auto zero = beam_search(7, 0, 1, expand_once, identity);
    assert(zero.state == 7);
    assert(zero.score == 7);
    assert(zero.depth == 0);
    assert(zero.expanded_states == 0);

    auto expand_without_depth = [](const int& state) {
        return std::vector<int>{state + 1, state + 2};
    };
    auto no_depth = beam_search(0, 3, 1, expand_without_depth, identity);
    assert(no_depth.state == 6);
    assert(no_depth.depth == 3);
}

struct MoveOnlyState {
    std::unique_ptr<int> value;

    explicit MoveOnlyState(int value_) : value(std::make_unique<int>(value_)) {}
    MoveOnlyState(MoveOnlyState&&) = default;
    MoveOnlyState& operator=(MoveOnlyState&&) = default;
    MoveOnlyState(const MoveOnlyState&) = delete;
    MoveOnlyState& operator=(const MoveOnlyState&) = delete;
};

void test_move_only_state() {
    auto expand = [](const MoveOnlyState& state, int, auto emit) {
        emit(MoveOnlyState(*state.value + 1));
        emit(MoveOnlyState(*state.value + 2));
    };
    auto evaluate = [](const MoveOnlyState& state) { return *state.value; };
    auto result = beam_search(MoveOnlyState(0), 4, 2, expand, evaluate);
    assert(*result.state.value == 8);
    assert(result.score == 8);
}

void test_randomized_against_exhaustive_search() {
    m1une::utilities::Random random(0xbea45eaULL);
    for (int trial = 0; trial < 200; trial++) {
        int depth_limit = int(random.uniform(1, 5));
        int radix = int(random.uniform(2, 4));
        bool maximize = random.uniform(0, 1) != 0;
        Objective objective = maximize ? Objective::maximize
                                       : Objective::minimize;
        int state_count = 1;
        for (int depth = 0; depth < depth_limit; depth++) {
            state_count *= radix;
        }

        auto result = beam_search(std::string(), depth_limit, state_count,
                                  digit_expander(radix), digit_value, objective);
        int expected = 0;
        if (maximize) {
            for (int depth = 0; depth < depth_limit; depth++) {
                expected = expected * 10 + radix - 1;
            }
        }
        assert(result.score == expected);
    }
}

int main() {
    test_objectives_and_statistics();
    test_early_stop_and_zero_depth();
    test_move_only_state();
    test_randomized_against_exhaustive_search();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
