#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include "../../../utilities/fast_io.hpp"
#include <random>
#include <utility>
#include <vector>

#include "../../../graph/flow/flow.hpp"

void test_max_flow() {
    m1une::flow::MaxFlow<long long> mf(4);
    int e0 = mf.add_edge(0, 1, 2);
    int e1 = mf.add_edge(0, 2, 1);
    int e2 = mf.add_edge(1, 2, 1);
    int e3 = mf.add_edge(1, 3, 1);
    int e4 = mf.add_edge(2, 3, 2);
    (void)e1;
    (void)e2;
    (void)e3;
    (void)e4;

    assert(mf.size() == 4);
    assert(mf.edge_count() == 5);
    assert(mf.max_flow(0, 3) == 3);
    auto edges = mf.edges();
    long long outgoing = 0;
    for (const auto& e : edges) {
        if (e.from == 0) outgoing += e.flow;
        assert(0 <= e.flow && e.flow <= e.cap);
    }
    assert(outgoing == 3);
    assert(mf.get_edge(e0).cap == 2);

    auto cut = mf.min_cut(0);
    assert(cut[0]);
    assert(!cut[3]);

    mf.change_edge(e0, 3, 1);
    auto changed = mf.get_edge(e0);
    assert(changed.cap == 3);
    assert(changed.flow == 1);
}

void test_gomory_hu() {
    m1une::flow::GomoryHu<long long> gh(4);
    gh.add_edge(0, 1, 3);
    gh.add_edge(1, 2, 2);
    gh.add_edge(0, 2, 1);
    gh.add_edge(2, 3, 4);
    gh.build();
    assert(gh.size() == 4);
    assert(gh.edge_count() == 4);
    assert(gh.tree_edges().size() == 3);
    assert(gh.min_cut(0, 1) == 4);
    assert(gh.min_cut(0, 2) == 3);
    assert(gh.min_cut(0, 3) == 3);
    assert(gh.min_cut(2, 3) == 4);

    m1une::flow::GomoryHu<long long> disconnected(3);
    disconnected.add_edge(0, 1, 5);
    disconnected.build();
    assert(disconnected.min_cut(0, 1) == 5);
    assert(disconnected.min_cut(0, 2) == 0);

    m1une::flow::GomoryHu<long long> rebuilt(2);
    rebuilt.build();
    assert(rebuilt.min_cut(0, 1) == 0);
    rebuilt.add_edge(0, 1, 7);
    rebuilt.add_edge(0, 0, 100);
    rebuilt.build();
    assert(rebuilt.min_cut(0, 1) == 7);

    m1une::flow::GomoryHu<long long> singleton(1);
    singleton.build();
    assert(singleton.tree_edges().empty());

    std::mt19937 random(123456789);
    for (int iteration = 0; iteration < 200; iteration++) {
        int n = 2 + int(random() % 8);
        struct InputEdge {
            int u;
            int v;
            long long cap;
        };
        std::vector<InputEdge> edges;
        m1une::flow::GomoryHu<long long> tree(n);
        int m = random() % (2 * n * n + 1);
        for (int i = 0; i < m; i++) {
            int u = random() % n;
            int v = random() % n;
            long long cap = random() % 1000001;
            edges.push_back(InputEdge{u, v, cap});
            tree.add_edge(u, v, cap);
        }
        tree.build();
        for (int s = 0; s < n; s++) {
            for (int t = s + 1; t < n; t++) {
                m1une::flow::MaxFlow<long long> mf(n);
                for (const auto& edge : edges) {
                    mf.add_edge(edge.u, edge.v, edge.cap);
                    mf.add_edge(edge.v, edge.u, edge.cap);
                }
                assert(tree.min_cut(s, t) == mf.max_flow(s, t));
            }
        }
    }
}

void test_bounded_flow() {
    m1une::flow::BoundedFlow<long long> st(4);
    int a = st.add_edge(0, 1, 1, 3);
    int b = st.add_edge(0, 2, 0, 2);
    int c = st.add_edge(1, 3, 1, 2);
    int d = st.add_edge(2, 3, 0, 2);
    int e = st.add_edge(1, 2, 0, 1);
    (void)a;
    (void)b;
    (void)c;
    (void)d;
    (void)e;

    auto exact = st.feasible_st_flow(0, 3, 3);
    assert(exact.has_value());
    std::vector<long long> balance(4, 0);
    for (const auto& edge : exact->edges) {
        assert(edge.lower <= edge.flow && edge.flow <= edge.upper);
        balance[edge.from] += edge.flow;
        balance[edge.to] -= edge.flow;
    }
    assert((balance == std::vector<long long>{3, 0, 0, -3}));

    auto too_much = st.feasible_st_flow(0, 3, 6);
    assert(!too_much.has_value());

    m1une::flow::BoundedFlow<long long> bf(3);
    int f01 = bf.add_edge(0, 1, 1, 3);
    int f02 = bf.add_edge(0, 2, 0, 4);
    bf.add_edge(1, 2, 0, 2);
    bf.add_supply(0, 4);
    bf.add_demand(1, 1);
    bf.add_demand(2, 3);
    assert(bf.balance(0) == 4);
    auto bflow = bf.feasible_flow();
    assert(bflow.has_value());
    assert(bflow->get_edge(f01).flow >= 1);
    assert(bflow->get_edge(f02).flow >= 0);
    std::vector<long long> b_balance(3, 0);
    for (const auto& edge : bflow->edges) {
        assert(edge.lower <= edge.flow && edge.flow <= edge.upper);
        b_balance[edge.from] += edge.flow;
        b_balance[edge.to] -= edge.flow;
    }
    assert((b_balance == std::vector<long long>{4, -1, -3}));

    m1une::flow::BoundedFlow<long long> negative(2);
    int neg = negative.add_edge(0, 1, -5, 5);
    negative.add_demand(0, 3);
    negative.add_supply(1, 3);
    auto negative_flow = negative.feasible_flow();
    assert(negative_flow.has_value());
    assert(negative_flow->flow(neg) == -3);

    m1une::flow::BoundedFlow<long long> impossible(2);
    impossible.add_edge(0, 1, 0, 1);
    impossible.add_supply(0, 2);
    impossible.add_demand(1, 2);
    assert(!impossible.feasible_flow().has_value());

    m1une::flow::BFlow<long long> alias(1);
    assert(alias.size() == 1);
}

void test_bounded_min_cost_flow() {
    m1une::flow::BoundedMinCostFlow<long long, long long> st(3);
    st.reserve_edges(3);
    int e01 = st.add_edge(0, 1, 1, 3, 2);
    int e12 = st.add_edge(1, 2, 1, 3, 1);
    int e02 = st.add_edge(0, 2, 0, 3, 10);

    auto exact = st.min_cost_st_flow(0, 2, 3);
    assert(exact.has_value());
    assert(exact->cost == 9);
    assert(exact->flow(e01) == 3);
    assert(exact->flow(e12) == 3);
    assert(exact->flow(e02) == 0);
    std::vector<long long> balance(3, 0);
    for (const auto& edge : exact->edges) {
        assert(edge.lower <= edge.flow && edge.flow <= edge.upper);
        balance[edge.from] += edge.flow;
        balance[edge.to] -= edge.flow;
    }
    assert((balance == std::vector<long long>{3, 0, -3}));

    m1une::flow::BoundedMinCostFlow<long long, long long> bf(3);
    int p01 = bf.add_edge(0, 1, 0, 2, 1);
    int p12 = bf.add_edge(1, 2, 0, 2, 1);
    int p02 = bf.add_edge(0, 2, 0, 2, 5);
    bf.add_supply(0, 2);
    bf.add_demand(2, 2);
    auto bflow = bf.min_cost_flow();
    assert(bflow.has_value());
    assert(bflow->cost == 4);
    assert(bflow->flow(p01) == 2);
    assert(bflow->flow(p12) == 2);
    assert(bflow->flow(p02) == 0);

    m1une::flow::BoundedMinCostFlow<long long, long long> negative(2);
    int neg = negative.add_edge(0, 1, -5, 5, 2);
    negative.add_demand(0, 3);
    negative.add_supply(1, 3);
    auto negative_flow = negative.min_cost_flow();
    assert(negative_flow.has_value());
    assert(negative_flow->flow(neg) == -3);
    assert(negative_flow->cost == -6);

    m1une::flow::BoundedMinCostFlow<long long, long long> cycle(2);
    int c01 = cycle.add_edge(0, 1, 0, 1, -5);
    int c10 = cycle.add_edge(1, 0, 0, 1, 3);
    auto circulation = cycle.min_cost_flow();
    assert(circulation.has_value());
    assert(circulation->flow(c01) == 1);
    assert(circulation->flow(c10) == 1);
    assert(circulation->cost == -2);

    m1une::flow::BoundedMinCostFlow<long long, long long> impossible(2);
    impossible.add_edge(0, 1, 0, 1, 0);
    impossible.add_supply(0, 2);
    impossible.add_demand(1, 2);
    assert(!impossible.min_cost_flow().has_value());

    using WideCostFlow = m1une::flow::BoundedMinCostFlow<
        long long, long long, __int128_t
    >;
    WideCostFlow wide_cost(1);
    wide_cost.reserve_edges(1);
    constexpr long long trillion = 1000000000000LL;
    wide_cost.add_edge(0, 0, trillion, trillion, trillion);
    auto wide_result = wide_cost.min_cost_flow();
    assert(wide_result.has_value());
    assert(wide_result->cost == __int128_t(trillion) * trillion);

    std::mt19937 random(987654321);
    for (int iteration = 0; iteration < 500; iteration++) {
        int n = 1 + int(random() % 4);
        int m = int(random() % 7);
        struct SmallEdge {
            int from;
            int to;
            long long lower;
            long long upper;
            long long cost;
        };
        std::vector<SmallEdge> edges;
        m1une::flow::BoundedMinCostFlow<long long, long long> solver(n);
        for (int i = 0; i < m; i++) {
            int from = int(random() % n);
            int to = int(random() % n);
            long long lower = static_cast<long long>(random() % 5) - 2;
            long long upper = lower + static_cast<long long>(random() % 4);
            long long cost = static_cast<long long>(random() % 9) - 4;
            edges.push_back(SmallEdge{from, to, lower, upper, cost});
            solver.add_edge(from, to, lower, upper, cost);
        }

        std::vector<long long> required_balance(n, 0);
        long long balance_sum = 0;
        for (int vertex = 0; vertex + 1 < n; vertex++) {
            required_balance[vertex] =
                static_cast<long long>(random() % 7) - 3;
            balance_sum += required_balance[vertex];
        }
        required_balance.back() = -balance_sum;

        bool feasible = false;
        long long best_cost = 0;
        std::vector<long long> flow(m);
        auto enumerate = [&](auto&& self, int edge_id) -> void {
            if (edge_id != m) {
                for (
                    flow[edge_id] = edges[edge_id].lower;
                    flow[edge_id] <= edges[edge_id].upper;
                    flow[edge_id]++
                ) {
                    self(self, edge_id + 1);
                }
                return;
            }

            std::vector<long long> actual_balance(n, 0);
            long long cost = 0;
            for (int i = 0; i < m; i++) {
                actual_balance[edges[i].from] += flow[i];
                actual_balance[edges[i].to] -= flow[i];
                cost += flow[i] * edges[i].cost;
            }
            if (actual_balance != required_balance) return;
            if (!feasible || cost < best_cost) best_cost = cost;
            feasible = true;
        };
        enumerate(enumerate, 0);

        auto result = solver.min_cost_flow(required_balance);
        assert(result.has_value() == feasible);
        if (!result.has_value()) continue;
        assert(result->cost == best_cost);

        std::vector<long long> actual_balance(n, 0);
        for (const auto& edge : result->edges) {
            assert(edge.lower <= edge.flow && edge.flow <= edge.upper);
            actual_balance[edge.from] += edge.flow;
            actual_balance[edge.to] -= edge.flow;
            long long reduced_cost =
                edge.cost
                + result->potential[edge.from] - result->potential[edge.to];
            if (edge.flow < edge.upper) assert(0 <= reduced_cost);
            if (edge.lower < edge.flow) assert(reduced_cost <= 0);
        }
        assert(actual_balance == required_balance);
    }

    m1une::flow::BMinCostFlow<long long, long long> alias(1);
    assert(alias.size() == 1);
    m1une::flow::BMinCostFlow<long long, long long, __int128_t> wide_alias(1);
    assert(wide_alias.size() == 1);
}

void test_min_cost_flow() {
    m1une::flow::MinCostFlow<long long, long long> mcf(4);
    mcf.add_edge(0, 1, 2, 1);
    mcf.add_edge(0, 2, 1, 2);
    mcf.add_edge(1, 2, 1, 0);
    mcf.add_edge(1, 3, 1, 3);
    mcf.add_edge(2, 3, 2, 1);

    auto result = mcf.flow(0, 3, 2);
    assert(result.first == 2);
    assert(result.second == 5);
    auto edges = mcf.edges();
    long long total_source_flow = 0;
    for (const auto& e : edges) {
        if (e.from == 0) total_source_flow += e.flow;
        assert(0 <= e.flow && e.flow <= e.cap);
    }
    assert(total_source_flow == 2);

    m1une::flow::MinCostFlow<long long, long long> negative(3);
    negative.add_edge(0, 1, 1, -5);
    negative.add_edge(1, 2, 1, 2);
    negative.add_edge(0, 2, 1, 10);
    auto slope = negative.slope(0, 2, 2);
    std::vector<std::pair<long long, long long>> expected_slope = {
        std::pair<long long, long long>{0, 0},
        std::pair<long long, long long>{1, -3},
        std::pair<long long, long long>{2, 7},
    };
    assert(slope == expected_slope);
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_max_flow();
    test_gomory_hu();
    test_bounded_flow();
    test_bounded_min_cost_flow();
    test_min_cost_flow();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
