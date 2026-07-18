#ifndef M1UNE_DS_WAVELET_MATRIX_DYNAMIC_WAVELET_MATRIX_SUM_HPP
#define M1UNE_DS_WAVELET_MATRIX_DYNAMIC_WAVELET_MATRIX_SUM_HPP 1

#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <limits>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

#include "dynamic_wavelet_matrix.hpp"

namespace m1une {
namespace ds {

namespace dynamic_wavelet_matrix_sum_detail {

#ifdef M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_PROFILE
struct DynamicWaveletMatrixSumProfile {
    std::uint64_t bitvector_tree_traversals = 0;
    std::uint64_t weight_tree_traversals = 0;
    std::uint64_t chunk_splits = 0;
    std::uint64_t chunk_merges = 0;
    std::uint64_t local_element_moves = 0;
    std::uint64_t full_chunk_rebuilds = 0;
};

inline DynamicWaveletMatrixSumProfile profile;

inline void reset_profile() {
    profile = DynamicWaveletMatrixSumProfile();
}

inline DynamicWaveletMatrixSumProfile get_profile() {
    return profile;
}

#define M1UNE_DWM_SUM_PROFILE_ADD(field, amount) \
    (::m1une::ds::dynamic_wavelet_matrix_sum_detail::profile.field += \
     (amount))
#else
#define M1UNE_DWM_SUM_PROFILE_ADD(field, amount) ((void)0)
#endif

#ifdef M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_CHUNK_CAPACITY
inline constexpr int configured_chunk_capacity =
    M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_CHUNK_CAPACITY;
#else
inline constexpr int configured_chunk_capacity = 64;
#endif

#ifdef M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_GROUP_SIZE
inline constexpr int configured_group_size =
    M1UNE_DYNAMIC_WAVELET_MATRIX_SUM_GROUP_SIZE;
#else
inline constexpr int configured_group_size = 16;
#endif

// A chunked implicit treap storing routing bits and additive weights together.
template <
    typename Sum,
    int ChunkCapacity = configured_chunk_capacity,
    int GroupSize = configured_group_size
>
class DynamicWeightedRankSequence {
   public:
    struct AccessRankResult {
        bool bit;
        Sum weight;
        int ones_before;
    };

    struct EraseRankResult {
        bool bit;
        Sum weight;
        int ones_before;
    };

    struct PrefixStats {
        int ones = 0;
        Sum total_sum{};
        Sum zero_sum{};
    };

    struct PrefixStatsPair {
        PrefixStats left;
        PrefixStats right;
    };

   private:
    static_assert(2 <= ChunkCapacity);
    static_assert(
        ChunkCapacity <= std::numeric_limits<std::uint16_t>::max()
    );
    static_assert(0 < GroupSize && GroupSize <= ChunkCapacity);
    static_assert(ChunkCapacity % GroupSize == 0);
    static constexpr int word_bits = 64;
    static constexpr int word_count =
        (ChunkCapacity + word_bits - 1) / word_bits;
    static constexpr int group_count = ChunkCapacity / GroupSize;
    static constexpr int minimum_chunk_size = ChunkCapacity / 2;

    struct Node {
        std::array<Sum, ChunkCapacity> weights{};
        std::array<Sum, group_count> group_total_sums{};
        std::array<Sum, group_count> group_zero_sums{};
        std::array<std::uint64_t, word_count> bits{};
        Sum chunk_total_sum{};
        Sum chunk_zero_sum{};
        Sum subtree_total_sum{};
        Sum subtree_zero_sum{};
        std::uint32_t priority = 0;
        int left = 0;
        int right = 0;
        int subtree_size = 0;
        int subtree_ones = 0;
        std::uint16_t length = 0;
        std::uint16_t chunk_ones = 0;
    };

    std::vector<Node> _nodes;
    std::vector<int> _free_nodes;
    int _root = 0;
    std::uint32_t _random_state = 1;

    int size_of(int node) const {
        return _nodes[node].subtree_size;
    }

    int ones_of(int node) const {
        return _nodes[node].subtree_ones;
    }

    const Sum& total_sum_of(int node) const {
        return _nodes[node].subtree_total_sum;
    }

    const Sum& zero_sum_of(int node) const {
        return _nodes[node].subtree_zero_sum;
    }

    std::uint32_t next_priority() {
        _random_state ^= _random_state << 13;
        _random_state ^= _random_state >> 17;
        _random_state ^= _random_state << 5;
        if (_random_state == 0) _random_state = 1;
        return _random_state;
    }

    bool local_bit(int node, int position) const {
        return (_nodes[node].bits[position / word_bits] >>
                (position % word_bits)) &
               1U;
    }

    void local_set_bit(int node, int position, bool bit) {
        std::uint64_t mask =
            std::uint64_t(1) << (position % word_bits);
        std::uint64_t& word = _nodes[node].bits[position / word_bits];
        if (bit) {
            word |= mask;
        } else {
            word &= ~mask;
        }
    }

    int local_rank1(int node, int right) const {
        int full_words = right / word_bits;
        int result = 0;
        for (int word = 0; word < full_words; word++) {
            result += std::popcount(_nodes[node].bits[word]);
        }
        int remainder = right % word_bits;
        if (remainder != 0) {
            result += std::popcount(
                _nodes[node].bits[full_words] &
                ((std::uint64_t(1) << remainder) - 1)
            );
        }
        return result;
    }

    void update(int node) {
        if (node == 0) return;
        Node& current = _nodes[node];
        current.subtree_size =
            size_of(current.left) + int(current.length) +
            size_of(current.right);
        current.subtree_ones =
            ones_of(current.left) + int(current.chunk_ones) +
            ones_of(current.right);
        current.subtree_total_sum =
            total_sum_of(current.left) + current.chunk_total_sum +
            total_sum_of(current.right);
        current.subtree_zero_sum =
            zero_sum_of(current.left) + current.chunk_zero_sum +
            zero_sum_of(current.right);
    }

    void rebuild_chunk(int node) {
        M1UNE_DWM_SUM_PROFILE_ADD(full_chunk_rebuilds, 1);
        Node& current = _nodes[node];
        current.group_total_sums.fill(Sum{});
        current.group_zero_sums.fill(Sum{});
        current.chunk_total_sum = Sum{};
        current.chunk_zero_sum = Sum{};
        current.chunk_ones = 0;
        for (int position = 0; position < current.length; position++) {
            int group = position / GroupSize;
            const Sum& weight = current.weights[position];
            current.group_total_sums[group] =
                current.group_total_sums[group] + weight;
            current.chunk_total_sum = current.chunk_total_sum + weight;
            if (local_bit(node, position)) {
                current.chunk_ones++;
            } else {
                current.group_zero_sums[group] =
                    current.group_zero_sums[group] + weight;
                current.chunk_zero_sum = current.chunk_zero_sum + weight;
            }
        }
        update(node);
    }

    PrefixStats local_prefix_stats(int node, int right) const {
        PrefixStats result;
        result.ones = local_rank1(node, right);
        int full_groups = right / GroupSize;
        for (int group = 0; group < full_groups; group++) {
            result.total_sum =
                result.total_sum + _nodes[node].group_total_sums[group];
            result.zero_sum =
                result.zero_sum + _nodes[node].group_zero_sums[group];
        }
        for (int position = full_groups * GroupSize; position < right;
             position++) {
            const Sum& weight = _nodes[node].weights[position];
            result.total_sum = result.total_sum + weight;
            if (!local_bit(node, position)) {
                result.zero_sum = result.zero_sum + weight;
            }
        }
        return result;
    }

    static void add_stats(PrefixStats& destination, const PrefixStats& value) {
        destination.ones += value.ones;
        destination.total_sum = destination.total_sum + value.total_sum;
        destination.zero_sum = destination.zero_sum + value.zero_sum;
    }

    PrefixStats subtree_stats(int node) const {
        return PrefixStats{
            ones_of(node),
            total_sum_of(node),
            zero_sum_of(node)
        };
    }

    void local_insert(int node, int position, bool bit, const Sum& weight) {
        Node& current = _nodes[node];
        assert(0 <= position && position <= current.length);
        assert(current.length < ChunkCapacity);
        M1UNE_DWM_SUM_PROFILE_ADD(
            local_element_moves,
            int(current.length) - position
        );
        for (int i = current.length; position < i; i--) {
            current.weights[i] = current.weights[i - 1];
            local_set_bit(node, i, local_bit(node, i - 1));
        }
        current.weights[position] = weight;
        local_set_bit(node, position, bit);
        current.length++;
        rebuild_chunk(node);
    }

    EraseRankResult local_erase(int node, int position) {
        Node& current = _nodes[node];
        assert(0 <= position && position < current.length);
        M1UNE_DWM_SUM_PROFILE_ADD(
            local_element_moves,
            int(current.length) - position - 1
        );
        EraseRankResult result{
            local_bit(node, position),
            current.weights[position],
            0
        };
        for (int i = position; i + 1 < current.length; i++) {
            current.weights[i] = current.weights[i + 1];
            local_set_bit(node, i, local_bit(node, i + 1));
        }
        current.length--;
        current.weights[current.length] = Sum{};
        local_set_bit(node, current.length, false);
        rebuild_chunk(node);
        return result;
    }

    Sum local_set_weight(int node, int position, const Sum& weight) {
        Node& current = _nodes[node];
        Sum old_weight = current.weights[position];
        Sum delta = weight - old_weight;
        current.weights[position] = weight;
        int group = position / GroupSize;
        current.group_total_sums[group] =
            current.group_total_sums[group] + delta;
        current.chunk_total_sum = current.chunk_total_sum + delta;
        if (!local_bit(node, position)) {
            current.group_zero_sums[group] =
                current.group_zero_sums[group] + delta;
            current.chunk_zero_sum = current.chunk_zero_sum + delta;
        }
        update(node);
        return old_weight;
    }

    Sum local_add_weight(int node, int position, const Sum& delta) {
        return local_set_weight(
            node,
            position,
            _nodes[node].weights[position] + delta
        );
    }

    int new_node() {
        int node;
        if (_free_nodes.empty()) {
            node = int(_nodes.size());
            _nodes.emplace_back();
        } else {
            node = _free_nodes.back();
            _free_nodes.pop_back();
            _nodes[node] = Node();
        }
        _nodes[node].priority = next_priority();
        return node;
    }

    template <std::size_t Capacity>
    void assign_from_values(
        int node,
        const std::array<std::uint8_t, Capacity>& bits,
        const std::array<Sum, Capacity>& weights,
        int first,
        int last
    ) {
        Node& current = _nodes[node];
        current.bits.fill(0);
        current.weights.fill(Sum{});
        current.length = std::uint16_t(last - first);
        for (int position = first; position < last; position++) {
            int destination = position - first;
            current.weights[destination] = weights[position];
            if (bits[position]) local_set_bit(node, destination, true);
        }
        rebuild_chunk(node);
    }

    void assign_from_values(
        int node,
        const std::vector<std::uint8_t>& bits,
        const std::vector<Sum>& weights,
        int first,
        int last
    ) {
        Node& current = _nodes[node];
        current.bits.fill(0);
        current.weights.fill(Sum{});
        current.length = std::uint16_t(last - first);
        for (int position = first; position < last; position++) {
            int destination = position - first;
            current.weights[destination] = weights[position];
            if (bits[position]) local_set_bit(node, destination, true);
        }
        rebuild_chunk(node);
    }

    int new_node(
        const std::vector<std::uint8_t>& bits,
        const std::vector<Sum>& weights,
        int first,
        int last
    ) {
        int node = new_node();
        assign_from_values(node, bits, weights, first, last);
        return node;
    }

    void recycle_node(int node) {
        assert(node != 0);
        _nodes[node] = Node();
        _free_nodes.push_back(node);
    }

    int merge(int left, int right) {
        if (left == 0 || right == 0) return left != 0 ? left : right;
        if (_nodes[left].priority > _nodes[right].priority) {
            _nodes[left].right = merge(_nodes[left].right, right);
            update(left);
            return left;
        }
        _nodes[right].left = merge(left, _nodes[right].left);
        update(right);
        return right;
    }

    int rotate_right(int tree) {
        int result = _nodes[tree].left;
        _nodes[tree].left = _nodes[result].right;
        _nodes[result].right = tree;
        update(tree);
        update(result);
        return result;
    }

    int rotate_left(int tree) {
        int result = _nodes[tree].right;
        _nodes[tree].right = _nodes[result].left;
        _nodes[result].left = tree;
        update(tree);
        update(result);
        return result;
    }

    int extract_leftmost(int tree, int& extracted) {
        if (_nodes[tree].left == 0) {
            extracted = tree;
            int result = _nodes[tree].right;
            _nodes[tree].right = 0;
            update(tree);
            return result;
        }
        _nodes[tree].left = extract_leftmost(_nodes[tree].left, extracted);
        update(tree);
        return tree;
    }

    int extract_rightmost(int tree, int& extracted) {
        if (_nodes[tree].right == 0) {
            extracted = tree;
            int result = _nodes[tree].left;
            _nodes[tree].left = 0;
            update(tree);
            return result;
        }
        _nodes[tree].right = extract_rightmost(_nodes[tree].right, extracted);
        update(tree);
        return tree;
    }

    int rebalance(int node) {
        if (_nodes[node].length >= minimum_chunk_size) return node;

        if (_nodes[node].right != 0) {
            int neighbor = 0;
            _nodes[node].right =
                extract_leftmost(_nodes[node].right, neighbor);
            int node_length = _nodes[node].length;
            int neighbor_length = _nodes[neighbor].length;
            int total = node_length + neighbor_length;
            std::array<std::uint8_t, ChunkCapacity * 2> bits{};
            std::array<Sum, ChunkCapacity * 2> weights{};
            for (int i = 0; i < node_length; i++) {
                bits[i] = local_bit(node, i);
                weights[i] = _nodes[node].weights[i];
            }
            for (int i = 0; i < neighbor_length; i++) {
                bits[node_length + i] = local_bit(neighbor, i);
                weights[node_length + i] = _nodes[neighbor].weights[i];
            }
            if (total <= ChunkCapacity) {
                M1UNE_DWM_SUM_PROFILE_ADD(chunk_merges, 1);
                assign_from_values(node, bits, weights, 0, total);
                recycle_node(neighbor);
            } else {
                int left_length = total / 2;
                assign_from_values(node, bits, weights, 0, left_length);
                assign_from_values(
                    neighbor,
                    bits,
                    weights,
                    left_length,
                    total
                );
                _nodes[node].right = merge(neighbor, _nodes[node].right);
            }
            update(node);
            return node;
        }

        if (_nodes[node].left != 0) {
            int neighbor = 0;
            _nodes[node].left =
                extract_rightmost(_nodes[node].left, neighbor);
            int neighbor_length = _nodes[neighbor].length;
            int node_length = _nodes[node].length;
            int total = neighbor_length + node_length;
            std::array<std::uint8_t, ChunkCapacity * 2> bits{};
            std::array<Sum, ChunkCapacity * 2> weights{};
            for (int i = 0; i < neighbor_length; i++) {
                bits[i] = local_bit(neighbor, i);
                weights[i] = _nodes[neighbor].weights[i];
            }
            for (int i = 0; i < node_length; i++) {
                bits[neighbor_length + i] = local_bit(node, i);
                weights[neighbor_length + i] = _nodes[node].weights[i];
            }
            if (total <= ChunkCapacity) {
                M1UNE_DWM_SUM_PROFILE_ADD(chunk_merges, 1);
                assign_from_values(node, bits, weights, 0, total);
                recycle_node(neighbor);
            } else {
                int left_length = total / 2;
                assign_from_values(
                    neighbor,
                    bits,
                    weights,
                    0,
                    left_length
                );
                assign_from_values(
                    node,
                    bits,
                    weights,
                    left_length,
                    total
                );
                _nodes[node].left = merge(_nodes[node].left, neighbor);
            }
            update(node);
        }
        return node;
    }

    int insert_impl(
        int tree,
        int position,
        bool bit,
        const Sum& weight,
        int& ones_before
    ) {
        if (tree == 0) {
            int node = new_node();
            local_insert(node, 0, bit, weight);
            return node;
        }

        int left_size = size_of(_nodes[tree].left);
        int length = _nodes[tree].length;
        if (position < left_size) {
            _nodes[tree].left = insert_impl(
                _nodes[tree].left,
                position,
                bit,
                weight,
                ones_before
            );
            update(tree);
            if (_nodes[_nodes[tree].left].priority >
                _nodes[tree].priority) {
                tree = rotate_right(tree);
            }
            return tree;
        }
        if (position > left_size + length) {
            ones_before +=
                ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;
            _nodes[tree].right = insert_impl(
                _nodes[tree].right,
                position - left_size - length,
                bit,
                weight,
                ones_before
            );
            update(tree);
            if (_nodes[_nodes[tree].right].priority >
                _nodes[tree].priority) {
                tree = rotate_left(tree);
            }
            return tree;
        }

        int local_position = position - left_size;
        ones_before += ones_of(_nodes[tree].left) +
                       local_rank1(tree, local_position);
        if (length < ChunkCapacity) {
            local_insert(tree, local_position, bit, weight);
            return tree;
        }

        std::array<std::uint8_t, ChunkCapacity> bits{};
        std::array<Sum, ChunkCapacity> weights{};
        M1UNE_DWM_SUM_PROFILE_ADD(chunk_splits, 1);
        for (int i = 0; i < ChunkCapacity; i++) {
            bits[i] = local_bit(tree, i);
            weights[i] = _nodes[tree].weights[i];
        }
        int right_chunk = new_node();
        int middle = ChunkCapacity / 2;
        assign_from_values(tree, bits, weights, 0, middle);
        assign_from_values(
            right_chunk,
            bits,
            weights,
            middle,
            ChunkCapacity
        );
        if (local_position <= middle) {
            local_insert(tree, local_position, bit, weight);
        } else {
            local_insert(
                right_chunk,
                local_position - middle,
                bit,
                weight
            );
        }

        int old_right = _nodes[tree].right;
        _nodes[tree].right = 0;
        update(tree);
        return merge(merge(tree, right_chunk), old_right);
    }

    int erase_impl(
        int tree,
        int position,
        EraseRankResult& result
    ) {
        int left_size = size_of(_nodes[tree].left);
        int length = _nodes[tree].length;
        if (position < left_size) {
            _nodes[tree].left = erase_impl(
                _nodes[tree].left,
                position,
                result
            );
            update(tree);
            return tree;
        }
        if (position >= left_size + length) {
            result.ones_before +=
                ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;
            _nodes[tree].right = erase_impl(
                _nodes[tree].right,
                position - left_size - length,
                result
            );
            update(tree);
            return tree;
        }

        int local_position = position - left_size;
        result.ones_before += ones_of(_nodes[tree].left) +
                              local_rank1(tree, local_position);
        EraseRankResult local = local_erase(tree, local_position);
        result.bit = local.bit;
        result.weight = local.weight;
        if (_nodes[tree].length == 0) {
            int merged = merge(_nodes[tree].left, _nodes[tree].right);
            recycle_node(tree);
            return merged;
        }
        return rebalance(tree);
    }

    template <bool Add>
    void change_weight_impl(
        int tree,
        int position,
        const Sum& value,
        AccessRankResult& result
    ) {
        int left_size = size_of(_nodes[tree].left);
        if (position < left_size) {
            change_weight_impl<Add>(
                _nodes[tree].left,
                position,
                value,
                result
            );
        } else if (position < left_size + _nodes[tree].length) {
            int local_position = position - left_size;
            result.ones_before += ones_of(_nodes[tree].left) +
                                  local_rank1(tree, local_position);
            result.bit = local_bit(tree, local_position);
            if constexpr (Add) {
                result.weight = local_add_weight(tree, local_position, value);
            } else {
                result.weight = local_set_weight(tree, local_position, value);
            }
            return;
        } else {
            result.ones_before +=
                ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;
            change_weight_impl<Add>(
                _nodes[tree].right,
                position - left_size - _nodes[tree].length,
                value,
                result
            );
        }
        update(tree);
    }

    PrefixStats prefix_stats_impl(int tree, int right) const {
        PrefixStats result;
        while (tree != 0 && right != 0) {
            int left_size = size_of(_nodes[tree].left);
            if (right <= left_size) {
                tree = _nodes[tree].left;
                continue;
            }
            add_stats(result, subtree_stats(_nodes[tree].left));
            right -= left_size;
            int take = std::min(right, int(_nodes[tree].length));
            add_stats(result, local_prefix_stats(tree, take));
            right -= take;
            if (right == 0) break;
            tree = _nodes[tree].right;
        }
        return result;
    }

    PrefixStatsPair prefix_stats_pair_impl(
        int tree,
        int left,
        int right
    ) const {
        if (left == right) {
            PrefixStats value = prefix_stats_impl(tree, left);
            return PrefixStatsPair{value, value};
        }
        if (tree == 0 || right == 0) return PrefixStatsPair{};

        int left_size = size_of(_nodes[tree].left);
        int chunk_end = left_size + _nodes[tree].length;
        if (right <= left_size) {
            return prefix_stats_pair_impl(
                _nodes[tree].left,
                left,
                right
            );
        }
        if (chunk_end <= left) {
            PrefixStats base = subtree_stats(_nodes[tree].left);
            add_stats(base, local_prefix_stats(tree, _nodes[tree].length));
            PrefixStatsPair result = prefix_stats_pair_impl(
                _nodes[tree].right,
                left - chunk_end,
                right - chunk_end
            );
            add_stats(result.left, base);
            add_stats(result.right, base);
            return result;
        }

        PrefixStats left_stats;
        if (left <= left_size) {
            left_stats = prefix_stats_impl(_nodes[tree].left, left);
        } else {
            left_stats = subtree_stats(_nodes[tree].left);
            add_stats(
                left_stats,
                local_prefix_stats(tree, left - left_size)
            );
        }

        PrefixStats right_stats = subtree_stats(_nodes[tree].left);
        if (right <= chunk_end) {
            add_stats(
                right_stats,
                local_prefix_stats(tree, right - left_size)
            );
        } else {
            add_stats(
                right_stats,
                local_prefix_stats(tree, _nodes[tree].length)
            );
            add_stats(
                right_stats,
                prefix_stats_impl(_nodes[tree].right, right - chunk_end)
            );
        }
        return PrefixStatsPair{left_stats, right_stats};
    }

    template <class Predicate>
    int consume_chunk_prefix(
        int node,
        int left,
        int right,
        Sum& sum,
        Predicate& predicate
    ) const {
        int position = left;
        while (position < right) {
            if (position % GroupSize == 0 &&
                position + GroupSize <= right) {
                int group = position / GroupSize;
                Sum candidate =
                    sum + _nodes[node].group_total_sums[group];
                if (predicate(candidate)) {
                    sum = candidate;
                    position += GroupSize;
                    continue;
                }
            }
            Sum candidate = sum + _nodes[node].weights[position];
            if (!predicate(candidate)) break;
            sum = candidate;
            position++;
        }
        return position - left;
    }

    template <class Predicate>
    int consume_chunk_suffix(
        int node,
        int left,
        int right,
        Sum& sum,
        Predicate& predicate
    ) const {
        int position = right;
        while (left < position) {
            if (position % GroupSize == 0 &&
                left <= position - GroupSize) {
                int group = position / GroupSize - 1;
                Sum candidate =
                    sum + _nodes[node].group_total_sums[group];
                if (predicate(candidate)) {
                    sum = candidate;
                    position -= GroupSize;
                    continue;
                }
            }
            Sum candidate = sum + _nodes[node].weights[position - 1];
            if (!predicate(candidate)) break;
            sum = candidate;
            position--;
        }
        return right - position;
    }

    template <class Predicate>
    int max_prefix_impl(
        int tree,
        int left,
        int right,
        Sum& sum,
        Predicate& predicate
    ) const {
        assert(tree != 0);
        assert(0 <= left && left < right && right <= size_of(tree));
        if (left == 0 && right == size_of(tree)) {
            Sum candidate = sum + total_sum_of(tree);
            if (predicate(candidate)) {
                sum = candidate;
                return size_of(tree);
            }
        }

        int left_size = size_of(_nodes[tree].left);
        int chunk_end = left_size + _nodes[tree].length;
        int count = 0;
        if (left < left_size) {
            int subtree_right = std::min(right, left_size);
            int consumed = max_prefix_impl(
                _nodes[tree].left,
                left,
                subtree_right,
                sum,
                predicate
            );
            count += consumed;
            if (consumed < subtree_right - left) return count;
        }

        int chunk_left = std::max(left, left_size);
        int chunk_right = std::min(right, chunk_end);
        if (chunk_left < chunk_right) {
            int consumed = consume_chunk_prefix(
                tree,
                chunk_left - left_size,
                chunk_right - left_size,
                sum,
                predicate
            );
            count += consumed;
            if (consumed < chunk_right - chunk_left) return count;
        }

        if (chunk_end < right) {
            int subtree_left = std::max(left, chunk_end) - chunk_end;
            int subtree_right = right - chunk_end;
            count += max_prefix_impl(
                _nodes[tree].right,
                subtree_left,
                subtree_right,
                sum,
                predicate
            );
        }
        return count;
    }

    template <class Predicate>
    int max_suffix_impl(
        int tree,
        int left,
        int right,
        Sum& sum,
        Predicate& predicate
    ) const {
        assert(tree != 0);
        assert(0 <= left && left < right && right <= size_of(tree));
        if (left == 0 && right == size_of(tree)) {
            Sum candidate = sum + total_sum_of(tree);
            if (predicate(candidate)) {
                sum = candidate;
                return size_of(tree);
            }
        }

        int left_size = size_of(_nodes[tree].left);
        int chunk_end = left_size + _nodes[tree].length;
        int count = 0;
        if (chunk_end < right) {
            int subtree_left = std::max(left, chunk_end) - chunk_end;
            int subtree_right = right - chunk_end;
            int consumed = max_suffix_impl(
                _nodes[tree].right,
                subtree_left,
                subtree_right,
                sum,
                predicate
            );
            count += consumed;
            if (consumed < subtree_right - subtree_left) return count;
        }

        int chunk_left = std::max(left, left_size);
        int chunk_right = std::min(right, chunk_end);
        if (chunk_left < chunk_right) {
            int consumed = consume_chunk_suffix(
                tree,
                chunk_left - left_size,
                chunk_right - left_size,
                sum,
                predicate
            );
            count += consumed;
            if (consumed < chunk_right - chunk_left) return count;
        }

        if (left < left_size) {
            int subtree_right = std::min(right, left_size);
            count += max_suffix_impl(
                _nodes[tree].left,
                left,
                subtree_right,
                sum,
                predicate
            );
        }
        return count;
    }

    void update_subtree(int tree) {
        if (tree == 0) return;
        update_subtree(_nodes[tree].left);
        update_subtree(_nodes[tree].right);
        update(tree);
    }

    void build(
        const std::vector<std::uint8_t>& bits,
        const std::vector<Sum>& weights
    ) {
        assert(bits.size() == weights.size());
        _nodes.clear();
        _nodes.emplace_back();
        _free_nodes.clear();
        _root = 0;
        _nodes.reserve(weights.size() / minimum_chunk_size + 2);

        std::vector<int> stack;
        for (int first = 0; first < int(weights.size());
             first += ChunkCapacity) {
            int last =
                std::min(first + ChunkCapacity, int(weights.size()));
            int node = new_node(bits, weights, first, last);
            int left = 0;
            while (!stack.empty() &&
                   _nodes[stack.back()].priority < _nodes[node].priority) {
                left = stack.back();
                stack.pop_back();
            }
            _nodes[node].left = left;
            if (!stack.empty()) _nodes[stack.back()].right = node;
            stack.push_back(node);
        }
        if (!stack.empty()) _root = stack.front();
        update_subtree(_root);
    }

   public:
    DynamicWeightedRankSequence() : _nodes(1) {}

    DynamicWeightedRankSequence(
        const std::vector<std::uint8_t>& bits,
        const std::vector<Sum>& weights,
        std::uint32_t seed = 1
    ) : _random_state(seed == 0 ? 1 : seed) {
        build(bits, weights);
    }

    explicit DynamicWeightedRankSequence(
        const std::vector<Sum>& weights,
        std::uint32_t seed = 1
    ) : _random_state(seed == 0 ? 1 : seed) {
        build(std::vector<std::uint8_t>(weights.size()), weights);
    }

    int size() const {
        return size_of(_root);
    }

    AccessRankResult access_with_rank(int position) const {
        assert(0 <= position && position < size());
        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals, 1);
        int tree = _root;
        int ones_before = 0;
        while (tree != 0) {
            int left_size = size_of(_nodes[tree].left);
            if (position < left_size) {
                tree = _nodes[tree].left;
            } else if (position < left_size + _nodes[tree].length) {
                int local_position = position - left_size;
                ones_before += ones_of(_nodes[tree].left) +
                               local_rank1(tree, local_position);
                return AccessRankResult{
                    local_bit(tree, local_position),
                    _nodes[tree].weights[local_position],
                    ones_before
                };
            } else {
                ones_before +=
                    ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;
                position -= left_size + _nodes[tree].length;
                tree = _nodes[tree].right;
            }
        }
        assert(false);
        return AccessRankResult{false, Sum{}, 0};
    }

    PrefixStats prefix_stats(int right) const {
        assert(0 <= right && right <= size());
        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals, 1);
        return prefix_stats_impl(_root, right);
    }

    PrefixStatsPair prefix_stats_pair(int left, int right) const {
        assert(0 <= left && left <= right && right <= size());
        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals, 1);
        return prefix_stats_pair_impl(_root, left, right);
    }

    Sum range_sum(int left, int right) const {
        PrefixStatsPair stats = prefix_stats_pair(left, right);
        return stats.right.total_sum - stats.left.total_sum;
    }

    int insert_with_rank(
        int position,
        bool bit,
        const Sum& weight
    ) {
        assert(0 <= position && position <= size());
        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals, 1);
        int ones_before = 0;
        _root = insert_impl(
            _root,
            position,
            bit,
            weight,
            ones_before
        );
        return ones_before;
    }

    EraseRankResult erase_with_rank(int position) {
        assert(0 <= position && position < size());
        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals, 1);
        EraseRankResult result{false, Sum{}, 0};
        _root = erase_impl(_root, position, result);
        return result;
    }

    AccessRankResult set_weight_with_rank(
        int position,
        const Sum& weight
    ) {
        assert(0 <= position && position < size());
        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals, 1);
        AccessRankResult result{false, Sum{}, 0};
        change_weight_impl<false>(_root, position, weight, result);
        return result;
    }

    AccessRankResult add_weight_with_rank(
        int position,
        const Sum& delta
    ) {
        assert(0 <= position && position < size());
        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals, 1);
        AccessRankResult result{false, Sum{}, 0};
        change_weight_impl<true>(_root, position, delta, result);
        return result;
    }

    template <class Predicate>
    int max_prefix(
        int left,
        int right,
        Sum& sum,
        Predicate& predicate
    ) const {
        assert(0 <= left && left <= right && right <= size());
        if (left == right) return 0;
        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals, 1);
        return max_prefix_impl(_root, left, right, sum, predicate);
    }

    template <class Predicate>
    int max_suffix(
        int left,
        int right,
        Sum& sum,
        Predicate& predicate
    ) const {
        assert(0 <= left && left <= right && right <= size());
        if (left == right) return 0;
        M1UNE_DWM_SUM_PROFILE_ADD(weight_tree_traversals, 1);
        return max_suffix_impl(_root, left, right, sum, predicate);
    }
};

}  // namespace dynamic_wavelet_matrix_sum_detail

#undef M1UNE_DWM_SUM_PROFILE_ADD

// A dynamic wavelet matrix with additive weights.
// By default, each value is also used as its weight.
template <
    std::integral T,
    typename Sum = T,
    int BitWidth = std::numeric_limits<std::make_unsigned_t<T>>::digits
>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
class DynamicWaveletMatrixSum {
   public:
    using value_type = T;
    using sum_type = Sum;
    using unsigned_type = std::make_unsigned_t<T>;

   private:
    static constexpr int full_bit_width =
        std::numeric_limits<unsigned_type>::digits;
    static_assert(1 <= BitWidth && BitWidth <= full_bit_width);
    static_assert(
        BitWidth == full_bit_width || std::unsigned_integral<T>,
        "reduced-width keys must use an unsigned type"
    );

    static constexpr unsigned_type sign_mask = [] {
        if constexpr (std::signed_integral<T>) {
            return unsigned_type(1) << (BitWidth - 1);
        } else {
            return unsigned_type(0);
        }
    }();

    static constexpr unsigned_type reduced_limit = [] {
        if constexpr (BitWidth < full_bit_width) {
            return unsigned_type(1) << BitWidth;
        } else {
            return unsigned_type(0);
        }
    }();

    using Level = dynamic_wavelet_matrix_sum_detail::
        DynamicWeightedRankSequence<Sum>;

    struct ErasedElement {
        unsigned_type key;
        Sum weight;
    };

    int _size = 0;
    std::vector<Level> _levels;
    Level _final_weights;
    std::array<int, BitWidth> _zero_count{};

    static bool key_fits(T value) {
        if constexpr (BitWidth < full_bit_width) {
            return static_cast<unsigned_type>(value) < reduced_limit;
        } else {
            return true;
        }
    }

    static unsigned_type encode_unchecked(T value) {
        unsigned_type bits;
        if constexpr (std::signed_integral<T>) {
            bits = std::bit_cast<unsigned_type>(value);
        } else {
            bits = value;
        }
        return bits ^ sign_mask;
    }

    static unsigned_type encode_key(T value) {
        assert(key_fits(value));
        return encode_unchecked(value);
    }

    static T decode(unsigned_type key) {
        unsigned_type bits = key ^ sign_mask;
        if constexpr (std::signed_integral<T>) {
            return std::bit_cast<T>(bits);
        } else {
            return bits;
        }
    }

    static bool bit(unsigned_type key, int level) {
        return (key >> (BitWidth - 1 - level)) & unsigned_type(1);
    }

    static Sum range_total(const typename Level::PrefixStatsPair& stats) {
        return stats.right.total_sum - stats.left.total_sum;
    }

    static Sum range_zero(const typename Level::PrefixStatsPair& stats) {
        return stats.right.zero_sum - stats.left.zero_sum;
    }

    void build(const std::vector<T>& values, const std::vector<Sum>& weights) {
        assert(values.size() == weights.size());
        _size = int(values.size());

        std::vector<unsigned_type> current_keys(_size);
        std::vector<unsigned_type> next_keys(_size);
        std::vector<Sum> current_weights(weights);
        std::vector<Sum> next_weights(_size);
        for (int i = 0; i < _size; i++) {
            current_keys[i] = encode_key(values[i]);
        }

        _levels.clear();
        _levels.reserve(BitWidth);
        for (int level = 0; level < BitWidth; level++) {
            std::vector<std::uint8_t> bits(_size);
            int zeros = 0;
            for (int i = 0; i < _size; i++) {
                bits[i] = bit(current_keys[i], level);
                zeros += !bits[i];
            }
            _zero_count[level] = zeros;
            _levels.emplace_back(
                bits,
                current_weights,
                std::uint32_t(0x9e3779b9U + level * 0x85ebca6bU)
            );

            int zero_position = 0;
            int one_position = zeros;
            for (int i = 0; i < _size; i++) {
                int next_position = bits[i] ? one_position++ : zero_position++;
                next_keys[next_position] = current_keys[i];
                next_weights[next_position] = current_weights[i];
            }
            current_keys.swap(next_keys);
            current_weights.swap(next_weights);
        }
        _final_weights = Level(current_weights, 0xb7e15162U);
    }

    void insert_encoded(int position, unsigned_type key, const Sum& weight) {
        for (int level = 0; level < BitWidth; level++) {
            bool one = bit(key, level);
            int ones_before =
                _levels[level].insert_with_rank(position, one, weight);
            int next_position;
            if (one) {
                next_position = _zero_count[level] + ones_before;
            } else {
                next_position = position - ones_before;
                _zero_count[level]++;
            }
            position = next_position;
        }
        _final_weights.insert_with_rank(position, false, weight);
        _size++;
    }

    ErasedElement erase_encoded(int position) {
        unsigned_type key = 0;
        Sum weight{};
        for (int level = 0; level < BitWidth; level++) {
            auto erased = _levels[level].erase_with_rank(position);
            if (level == 0) weight = erased.weight;
            int next_position;
            if (erased.bit) {
                key |= unsigned_type(1) << (BitWidth - 1 - level);
                next_position = _zero_count[level] + erased.ones_before;
            } else {
                next_position = position - erased.ones_before;
                _zero_count[level]--;
            }
            position = next_position;
        }
        _final_weights.erase_with_rank(position);
        _size--;
        return ErasedElement{key, weight};
    }

    int count_less_encoded(int left, int right, unsigned_type upper) const {
        int result = 0;
        for (int level = 0; level < BitWidth; level++) {
            auto stats = _levels[level].prefix_stats_pair(left, right);
            int left_ones = stats.left.ones;
            int right_ones = stats.right.ones;
            if (bit(upper, level)) {
                result += (right - left) - (right_ones - left_ones);
                left = _zero_count[level] + left_ones;
                right = _zero_count[level] + right_ones;
            } else {
                left -= left_ones;
                right -= right_ones;
            }
        }
        return result;
    }

    int count_less(int left, int right, T upper) const {
        if constexpr (BitWidth < full_bit_width) {
            if (!key_fits(upper)) return right - left;
        }
        return count_less_encoded(left, right, encode_unchecked(upper));
    }

    Sum sum_less_encoded(int left, int right, unsigned_type upper) const {
        Sum result{};
        for (int level = 0; level < BitWidth; level++) {
            auto stats = _levels[level].prefix_stats_pair(left, right);
            int left_ones = stats.left.ones;
            int right_ones = stats.right.ones;
            if (bit(upper, level)) {
                result = result + range_zero(stats);
                left = _zero_count[level] + left_ones;
                right = _zero_count[level] + right_ones;
            } else {
                left -= left_ones;
                right -= right_ones;
            }
        }
        return result;
    }

    Sum sum_less(int left, int right, T upper) const {
        if constexpr (BitWidth < full_bit_width) {
            if (!key_fits(upper)) return range_sum(left, right);
        }
        return sum_less_encoded(left, right, encode_unchecked(upper));
    }

   public:
    DynamicWaveletMatrixSum() : _levels(BitWidth) {}

    explicit DynamicWaveletMatrixSum(const std::vector<T>& values)
        requires std::convertible_to<T, Sum>
    {
        std::vector<Sum> weights;
        weights.reserve(values.size());
        for (T value : values) weights.push_back(static_cast<Sum>(value));
        build(values, weights);
    }

    DynamicWaveletMatrixSum(
        const std::vector<T>& values,
        const std::vector<Sum>& weights
    ) {
        build(values, weights);
    }

    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    void clear() {
        *this = DynamicWaveletMatrixSum();
    }

    T access(int position) const {
        assert(0 <= position && position < _size);
        unsigned_type key = 0;
        for (int level = 0; level < BitWidth; level++) {
            auto accessed = _levels[level].access_with_rank(position);
            if (accessed.bit) {
                key |= unsigned_type(1) << (BitWidth - 1 - level);
                position = _zero_count[level] + accessed.ones_before;
            } else {
                position -= accessed.ones_before;
            }
        }
        return decode(key);
    }

    T operator[](int position) const {
        return access(position);
    }

    Sum weight(int position) const {
        assert(0 <= position && position < _size);
        return _levels[0].access_with_rank(position).weight;
    }

    std::pair<T, Sum> get(int position) const {
        assert(0 <= position && position < _size);
        unsigned_type key = 0;
        Sum result_weight{};
        for (int level = 0; level < BitWidth; level++) {
            auto accessed = _levels[level].access_with_rank(position);
            if (level == 0) result_weight = accessed.weight;
            if (accessed.bit) {
                key |= unsigned_type(1) << (BitWidth - 1 - level);
                position = _zero_count[level] + accessed.ones_before;
            } else {
                position -= accessed.ones_before;
            }
        }
        return std::pair<T, Sum>(decode(key), result_weight);
    }

    void insert(int position, T value)
        requires std::convertible_to<T, Sum>
    {
        insert(position, value, static_cast<Sum>(value));
    }

    void insert(int position, T value, const Sum& weight) {
        assert(0 <= position && position <= _size);
        insert_encoded(position, encode_key(value), weight);
    }

    void push_back(T value)
        requires std::convertible_to<T, Sum>
    {
        insert(_size, value);
    }

    void push_back(T value, const Sum& weight) {
        insert(_size, value, weight);
    }

    std::pair<T, Sum> erase(int position) {
        assert(0 <= position && position < _size);
        ErasedElement erased = erase_encoded(position);
        return std::pair<T, Sum>(decode(erased.key), erased.weight);
    }

    void set(int position, T value)
        requires std::convertible_to<T, Sum>
    {
        set(position, value, static_cast<Sum>(value));
    }

    void set(int position, T value, const Sum& weight) {
        assert(0 <= position && position < _size);
        unsigned_type key = encode_key(value);
        erase_encoded(position);
        insert_encoded(position, key, weight);
    }

    void set_value(int position, T value) {
        assert(0 <= position && position < _size);
        unsigned_type key = encode_key(value);
        ErasedElement erased = erase_encoded(position);
        insert_encoded(position, key, erased.weight);
    }

    void set_weight(int position, const Sum& new_weight) {
        assert(0 <= position && position < _size);
        for (int level = 0; level < BitWidth; level++) {
            auto accessed =
                _levels[level].set_weight_with_rank(position, new_weight);
            if (accessed.bit) {
                position = _zero_count[level] + accessed.ones_before;
            } else {
                position -= accessed.ones_before;
            }
        }
        _final_weights.set_weight_with_rank(position, new_weight);
    }

    void add_weight(int position, const Sum& delta) {
        assert(0 <= position && position < _size);
        for (int level = 0; level < BitWidth; level++) {
            auto accessed =
                _levels[level].add_weight_with_rank(position, delta);
            if (accessed.bit) {
                position = _zero_count[level] + accessed.ones_before;
            } else {
                position -= accessed.ones_before;
            }
        }
        _final_weights.add_weight_with_rank(position, delta);
    }

    int rank(T value, int right) const {
        assert(0 <= right && right <= _size);
        return rank(value, 0, right);
    }

    int rank(T value, int left, int right) const {
        assert(0 <= left && left <= right && right <= _size);
        if constexpr (BitWidth < full_bit_width) {
            if (!key_fits(value)) return 0;
        }
        unsigned_type key = encode_unchecked(value);
        for (int level = 0; level < BitWidth; level++) {
            auto stats = _levels[level].prefix_stats_pair(left, right);
            int left_ones = stats.left.ones;
            int right_ones = stats.right.ones;
            if (bit(key, level)) {
                left = _zero_count[level] + left_ones;
                right = _zero_count[level] + right_ones;
            } else {
                left -= left_ones;
                right -= right_ones;
            }
        }
        return right - left;
    }

    T kth_smallest(int left, int right, int k) const {
        assert(0 <= left && left <= right && right <= _size);
        assert(0 <= k && k < right - left);
        unsigned_type key = 0;
        for (int level = 0; level < BitWidth; level++) {
            auto stats = _levels[level].prefix_stats_pair(left, right);
            int left_ones = stats.left.ones;
            int right_ones = stats.right.ones;
            int left_zeros = left - left_ones;
            int right_zeros = right - right_ones;
            int zeros = right_zeros - left_zeros;
            if (k < zeros) {
                left = left_zeros;
                right = right_zeros;
            } else {
                k -= zeros;
                key |= unsigned_type(1) << (BitWidth - 1 - level);
                left = _zero_count[level] + left_ones;
                right = _zero_count[level] + right_ones;
            }
        }
        return decode(key);
    }

    T kth_largest(int left, int right, int k) const {
        assert(0 <= left && left <= right && right <= _size);
        assert(0 <= k && k < right - left);
        return kth_smallest(left, right, right - left - 1 - k);
    }

    int range_freq(int left, int right, T upper) const {
        assert(0 <= left && left <= right && right <= _size);
        return count_less(left, right, upper);
    }

    int range_freq(int left, int right, T lower, T upper) const {
        assert(0 <= left && left <= right && right <= _size);
        if (upper <= lower) return 0;
        return count_less(left, right, upper) -
               count_less(left, right, lower);
    }

    std::optional<T> prev_value(int left, int right, T upper) const {
        assert(0 <= left && left <= right && right <= _size);
        int count = range_freq(left, right, upper);
        if (count == 0) return std::nullopt;
        return kth_smallest(left, right, count - 1);
    }

    std::optional<T> next_value(int left, int right, T lower) const {
        assert(0 <= left && left <= right && right <= _size);
        int count = range_freq(left, right, lower);
        if (count == right - left) return std::nullopt;
        return kth_smallest(left, right, count);
    }

    Sum range_sum(int left, int right) const {
        assert(0 <= left && left <= right && right <= _size);
        return _levels[0].range_sum(left, right);
    }

    Sum range_sum(int left, int right, T upper) const {
        assert(0 <= left && left <= right && right <= _size);
        return sum_less(left, right, upper);
    }

    Sum range_sum(int left, int right, T lower, T upper) const {
        assert(0 <= left && left <= right && right <= _size);
        if (upper <= lower) return Sum{};
        return sum_less(left, right, upper) -
               sum_less(left, right, lower);
    }

    Sum sum_k_smallest(int left, int right, int k) const {
        assert(0 <= left && left <= right && right <= _size);
        assert(0 <= k && k <= right - left);
        Sum result{};
        for (int level = 0; level < BitWidth; level++) {
            auto stats = _levels[level].prefix_stats_pair(left, right);
            int left_ones = stats.left.ones;
            int right_ones = stats.right.ones;
            int left_zeros = left - left_ones;
            int right_zeros = right - right_ones;
            int zeros = right_zeros - left_zeros;
            if (k < zeros) {
                left = left_zeros;
                right = right_zeros;
            } else {
                result = result + range_zero(stats);
                k -= zeros;
                left = _zero_count[level] + left_ones;
                right = _zero_count[level] + right_ones;
            }
        }
        return result + _final_weights.range_sum(left, left + k);
    }

    Sum sum_k_largest(int left, int right, int k) const {
        assert(0 <= left && left <= right && right <= _size);
        assert(0 <= k && k <= right - left);
        return range_sum(left, right) -
               sum_k_smallest(left, right, right - left - k);
    }

    template <class Predicate>
    int max_count_smallest(
        int left,
        int right,
        Predicate predicate
    ) const {
        assert(0 <= left && left <= right && right <= _size);
        assert(predicate(Sum{}));
        Sum result{};
        int count = 0;
        for (int level = 0; level < BitWidth; level++) {
            auto stats = _levels[level].prefix_stats_pair(left, right);
            int left_ones = stats.left.ones;
            int right_ones = stats.right.ones;
            int left_zeros = left - left_ones;
            int right_zeros = right - right_ones;
            int zeros = right_zeros - left_zeros;
            Sum candidate = result + range_zero(stats);
            if (predicate(candidate)) {
                result = candidate;
                count += zeros;
                left = _zero_count[level] + left_ones;
                right = _zero_count[level] + right_ones;
            } else {
                left = left_zeros;
                right = right_zeros;
            }
        }
        return count +
               _final_weights.max_prefix(
                   left,
                   right,
                   result,
                   predicate
               );
    }

    template <class Predicate>
    int max_count_largest(
        int left,
        int right,
        Predicate predicate
    ) const {
        assert(0 <= left && left <= right && right <= _size);
        assert(predicate(Sum{}));
        Sum result{};
        int count = 0;
        for (int level = 0; level < BitWidth; level++) {
            auto stats = _levels[level].prefix_stats_pair(left, right);
            int left_ones = stats.left.ones;
            int right_ones = stats.right.ones;
            int left_zeros = left - left_ones;
            int right_zeros = right - right_ones;
            int ones = right_ones - left_ones;
            Sum zero_result = range_zero(stats);
            Sum one_result = range_total(stats) - zero_result;
            Sum candidate = result + one_result;
            if (predicate(candidate)) {
                result = candidate;
                count += ones;
                left = left_zeros;
                right = right_zeros;
            } else {
                left = _zero_count[level] + left_ones;
                right = _zero_count[level] + right_ones;
            }
        }
        return count +
               _final_weights.max_suffix(
                   left,
                   right,
                   result,
                   predicate
               );
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_WAVELET_MATRIX_DYNAMIC_WAVELET_MATRIX_SUM_HPP
