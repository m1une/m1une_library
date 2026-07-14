#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include <algorithm>
#include <cassert>
#include "../../../utilities/fast_io.hpp"
#include <numeric>
#include <random>
#include <utility>
#include <vector>

#include "../../../ds/dsu/rollback_dsu.hpp"

namespace {

#ifndef NDEBUG
int naive_leader(std::vector<int>& parent, int vertex) {
    if (parent[vertex] == vertex) return vertex;
    return parent[vertex] = naive_leader(parent, parent[vertex]);
}

void validate(
    const m1une::ds::RollbackDsu& dsu,
    std::vector<int> parent
) {
    const int n = int(parent.size());
    int component_count = 0;
    std::vector<int> group_size(n, 0);
    for (int vertex = 0; vertex < n; vertex++) {
        int root = naive_leader(parent, vertex);
        group_size[root]++;
        if (root == vertex) component_count++;
    }
    assert(dsu.component_count() == component_count);
    assert(int(dsu.groups().size()) == component_count);
    for (int first = 0; first < n; first++) {
        assert(dsu.group_size(first) == group_size[naive_leader(parent, first)]);
        for (int second = 0; second < n; second++) {
            assert(dsu.same(first, second) ==
                   (naive_leader(parent, first) == naive_leader(parent, second)));
        }
    }
}

void randomized_test() {
    std::mt19937 random(712367);
    for (int test = 0; test < 80; test++) {
        const int n = 1 + int(random() % 18);
        m1une::ds::RollbackDsu dsu(n);
        dsu.reserve_history(600);
        std::vector<std::vector<int>> states(1, std::vector<int>(n));
        std::iota(states[0].begin(), states[0].end(), 0);

        for (int operation = 0; operation < 500; operation++) {
            int type = int(random() % 5);
            if (type <= 2 || states.size() == 1) {
                int first = int(random() % n);
                int second = int(random() % n);
                std::vector<int> next = states.back();
                int first_root = naive_leader(next, first);
                int second_root = naive_leader(next, second);
                bool changed = first_root != second_root;
                if (changed) next[second_root] = first_root;
                assert(dsu.merge(first, second) == changed);
                states.push_back(std::move(next));
            } else if (type == 3) {
                assert(dsu.undo());
                states.pop_back();
            } else {
                int state = int(random() % states.size());
                dsu.rollback(state);
                states.resize(state + 1);
            }
            assert(dsu.snapshot() == int(states.size()) - 1);
            validate(dsu, states.back());
        }
        dsu.rollback(0);
        assert(!dsu.undo());
        assert(dsu.component_count() == n);
    }
}
#endif

struct Operation {
    int first;
    int second;
};

struct Query {
    int first;
    int second;
    int answer_index;
};

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

#ifndef NDEBUG
    randomized_test();
#endif
    int vertex_count, query_count;
    fast_input >> vertex_count >> query_count;
    std::vector<std::vector<int>> children(query_count + 1);
    std::vector<Operation> operation(query_count + 1, Operation{-1, -1});
    std::vector<std::vector<Query>> queries(query_count + 1);
    int answer_count = 0;

    for (int query = 0; query < query_count; query++) {
        int type, parent, first, second;
        fast_input >> type >> parent >> first >> second;
        const int parent_node = parent + 1;
        if (type == 0) {
            const int node = query + 1;
            children[parent_node].push_back(node);
            operation[node] = Operation{first, second};
        } else {
            queries[parent_node].push_back(Query{first, second, answer_count++});
        }
    }

    std::vector<int> answer(answer_count);
    m1une::ds::RollbackDsu dsu(vertex_count);
    std::vector<std::pair<int, bool>> stack(1, std::make_pair(0, false));
    while (!stack.empty()) {
        auto [node, exiting] = stack.back();
        stack.pop_back();
        if (exiting) {
            if (node != 0) dsu.undo();
            continue;
        }

        if (node != 0) dsu.merge(operation[node].first, operation[node].second);
        for (const Query& query : queries[node]) {
            answer[query.answer_index] = dsu.same(query.first, query.second);
        }
        stack.emplace_back(node, true);
        for (auto it = children[node].rbegin(); it != children[node].rend(); ++it) {
            stack.emplace_back(*it, false);
        }
    }

    for (int value : answer) fast_output << value << '\n';
}
