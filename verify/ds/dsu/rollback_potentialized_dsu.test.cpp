#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B"

#include "../../../ds/dsu/rollback_potentialized_dsu.hpp"

#include <array>
#include <cassert>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>

#include "../../../monoid/add.hpp"

namespace {

using Add = m1une::monoid::Add<long long>;
using Dsu = m1une::ds::RollbackPotentializedDsu<Add>;

struct PermutationGroup {
    using value_type = std::array<int, 3>;

    static value_type id() { return {0, 1, 2}; }

    static value_type op(const value_type& first, const value_type& second) {
        value_type result;
        for (int index = 0; index < 3; ++index) {
            result[index] = second[first[index]];
        }
        return result;
    }

    static value_type inv(const value_type& value) {
        value_type result;
        for (int index = 0; index < 3; ++index) result[value[index]] = index;
        return result;
    }
};

void noncommutative_test() {
    using Permutation = PermutationGroup::value_type;
    m1une::ds::RollbackPotentializedDsu<PermutationGroup> dsu(4);
    Permutation rotate = {1, 2, 0};
    Permutation swap_last = {0, 2, 1};
    assert(dsu.merge(0, 1, rotate));
    int state = dsu.snapshot();
    assert(dsu.merge(1, 2, swap_last));
    Permutation composed = PermutationGroup::op(rotate, swap_last);
    assert(dsu.diff(0, 2) == composed);
    assert(!dsu.merge(0, 2, PermutationGroup::op(swap_last, rotate)));
    dsu.rollback(state);
    assert(!dsu.same(0, 2));
}

void randomized_test() {
    constexpr int size = 18;
    Dsu dsu(size);
    std::vector<std::vector<long long>> graph(size, std::vector<long long>(size));
    std::vector<std::vector<bool>> edge(size, std::vector<bool>(size));
    std::vector<std::tuple<int, int, long long>> history;
    std::mt19937 random(0);

    auto rebuild = [&] {
        graph.assign(size, std::vector<long long>(size));
        edge.assign(size, std::vector<bool>(size));
        for (const auto& [first, second, difference] : history) {
            edge[first][second] = edge[second][first] = true;
            graph[first][second] = difference;
            graph[second][first] = -difference;
        }
    };

    auto naive_potential = [&](int start) {
        std::vector<bool> seen(size);
        std::vector<long long> potential(size);
        std::vector<int> stack = {start};
        seen[start] = true;
        while (!stack.empty()) {
            int vertex = stack.back();
            stack.pop_back();
            for (int next = 0; next < size; ++next) {
                if (!edge[vertex][next] || seen[next]) continue;
                seen[next] = true;
                potential[next] = potential[vertex] + graph[vertex][next];
                stack.push_back(next);
            }
        }
        return std::pair(std::move(seen), std::move(potential));
    };

    auto validate = [&] {
        for (int first = 0; first < size; ++first) {
            auto [seen, potential] = naive_potential(first);
            for (int second = 0; second < size; ++second) {
                assert(dsu.same(first, second) == seen[second]);
                if (seen[second]) {
                    assert(dsu.diff(first, second) == potential[second]);
                }
            }
        }
    };

    for (int round = 0; round < 120; ++round) {
        int state = dsu.snapshot();
        std::size_t history_size = history.size();
        int update_count = 1 + int(random() % 8);
        for (int step = 0; step < update_count; ++step) {
            int first = int(random() % size);
            int second = int(random() % size);
            auto [seen, potential] = naive_potential(first);
            long long difference = seen[second]
                ? potential[second]
                : static_cast<long long>(int(random() % 41) - 20);
            bool consistent = dsu.merge(first, second, difference);
            assert(consistent);
            if (!seen[second]) history.emplace_back(first, second, difference);
            rebuild();
            validate();
        }

        dsu.rollback(state);
        history.resize(history_size);
        rebuild();
        validate();
    }
}

}  // namespace

int main() {
    noncommutative_test();
    randomized_test();

    int vertex_count, query_count;
    std::cin >> vertex_count >> query_count;
    Dsu dsu(vertex_count);
    for (int query = 0; query < query_count; ++query) {
        int type, first, second;
        std::cin >> type >> first >> second;
        if (type == 0) {
            long long difference;
            std::cin >> difference;
            dsu.merge(first, second, difference);
        } else if (dsu.same(first, second)) {
            std::cout << dsu.diff(first, second) << '\n';
        } else {
            std::cout << "?\n";
        }
    }
}
