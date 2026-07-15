#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A"

#include "../../../graph/flow/max_flow.hpp"
#include "../../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    int vertex_count, edge_count;
    input >> vertex_count >> edge_count;
    m1une::flow::MaxFlow<long long> flow(vertex_count);
    flow.reserve_edges(edge_count);
    for (int edge = 0; edge < edge_count; edge++) {
        int from, to;
        long long capacity;
        input >> from >> to >> capacity;
        flow.add_edge(from, to, capacity);
    }
    output << flow.max_flow_push_relabel(0, vertex_count - 1) << '\n';
}
