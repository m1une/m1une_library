#ifndef M1UNE_GRAPH_BLOCK_CUT_TREE_HPP
#define M1UNE_GRAPH_BLOCK_CUT_TREE_HPP 1

#include <cassert>
#include <vector>

#include "biconnected_components.hpp"

namespace m1une {
namespace graph {

struct BlockCutTreeResult {
    std::vector<std::vector<int>> forest;
    std::vector<int> node_of_block;
    std::vector<int> node_of_articulation;
    std::vector<int> node_of_vertex;
    std::vector<int> block_of_node;
    std::vector<int> articulation_of_node;

    int node_count() const {
        return int(forest.size());
    }

    int block_count() const {
        return int(node_of_block.size());
    }

    bool is_block_node(int node) const {
        assert(0 <= node && node < node_count());
        return block_of_node[node] != -1;
    }

    bool is_articulation_node(int node) const {
        assert(0 <= node && node < node_count());
        return articulation_of_node[node] != -1;
    }
};

// Builds the block-cut forest of a biconnected-components decomposition.
// Block nodes have IDs [0, block_count); articulation nodes follow them.
inline BlockCutTreeResult block_cut_tree(
    const BiconnectedComponentsResult& biconnected
) {
    const int vertex_count = int(biconnected.vertex_components.size());
    const int block_count = biconnected.component_count();

    BlockCutTreeResult result;
    result.node_of_block.resize(block_count);
    result.node_of_articulation.assign(vertex_count, -1);
    result.node_of_vertex.assign(vertex_count, -1);
    result.forest.resize(block_count);
    result.block_of_node.resize(block_count);
    result.articulation_of_node.assign(block_count, -1);
    for (int block = 0; block < block_count; block++) {
        result.node_of_block[block] = block;
        result.block_of_node[block] = block;
    }

    for (int vertex = 0; vertex < vertex_count; vertex++) {
        const std::vector<int>& blocks = biconnected.vertex_components[vertex];
        assert(!blocks.empty());
        if (blocks.size() == 1) {
            assert(0 <= blocks[0] && blocks[0] < block_count);
            result.node_of_vertex[vertex] = result.node_of_block[blocks[0]];
            continue;
        }

        const int node = result.node_count();
        result.node_of_articulation[vertex] = node;
        result.node_of_vertex[vertex] = node;
        result.forest.emplace_back();
        result.block_of_node.push_back(-1);
        result.articulation_of_node.push_back(vertex);
        for (int block : blocks) {
            assert(0 <= block && block < block_count);
            const int block_node = result.node_of_block[block];
            result.forest[node].push_back(block_node);
            result.forest[block_node].push_back(node);
        }
    }
    return result;
}

template <class T>
BlockCutTreeResult block_cut_tree(const Graph<T>& graph) {
    return block_cut_tree(biconnected_components(graph));
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_BLOCK_CUT_TREE_HPP
