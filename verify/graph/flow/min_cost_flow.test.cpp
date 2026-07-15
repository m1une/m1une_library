#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_B"

#include "../../../graph/flow/min_cost_flow.hpp"
#include "../../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    int vertex_count, edge_count;
    long long required_flow;
    input >> vertex_count >> edge_count >> required_flow;
    m1une::flow::MinCostFlow<long long, long long> flow(vertex_count);
    flow.reserve_edges(edge_count);
    for (int edge = 0; edge < edge_count; edge++) {
        int from, to;
        long long capacity, cost;
        input >> from >> to >> capacity >> cost;
        flow.add_edge(from, to, capacity, cost);
    }
    auto [sent, cost] = flow.flow(0, vertex_count - 1, required_flow);
    output << (sent == required_flow ? cost : -1) << '\n';
}
