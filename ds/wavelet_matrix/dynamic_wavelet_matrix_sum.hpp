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

// An implicit treap of small chunks with additive range products.
template <typename Sum>
class DynamicSumSequence {
   private:
    static constexpr int chunk_capacity = 256;
    static constexpr int minimum_chunk_size = chunk_capacity / 2;
    static constexpr int group_size = 32;
    static constexpr int group_count = chunk_capacity / group_size;

    struct Node {
        std::array<Sum, chunk_capacity> values{};
        std::array<Sum, group_count> group_sums{};
        Sum chunk_sum{};
        Sum subtree_sum{};
        std::uint32_t priority = 0;
        int left = 0;
        int right = 0;
        int subtree_size = 0;
        std::uint16_t length = 0;
    };

    std::vector<Node> _nodes;
    std::vector<int> _free_nodes;
    int _root = 0;
    std::uint32_t _random_state = 1;

    int size_of(int node) const {
        return _nodes[node].subtree_size;
    }

    const Sum& sum_of(int node) const {
        return _nodes[node].subtree_sum;
    }

    std::uint32_t next_priority() {
        _random_state ^= _random_state << 13;
        _random_state ^= _random_state >> 17;
        _random_state ^= _random_state << 5;
        if (_random_state == 0) _random_state = 1;
        return _random_state;
    }

    void update(int node) {
        if (node == 0) return;
        _nodes[node].subtree_size =
            size_of(_nodes[node].left) + int(_nodes[node].length) +
            size_of(_nodes[node].right);
        _nodes[node].subtree_sum =
            sum_of(_nodes[node].left) + _nodes[node].chunk_sum +
            sum_of(_nodes[node].right);
    }

    void rebuild_chunk(int node) {
        Node& current = _nodes[node];
        current.group_sums.fill(Sum{});
        current.chunk_sum = Sum{};
        for (int position = 0; position < current.length; position++) {
            int group = position / group_size;
            current.group_sums[group] =
                current.group_sums[group] + current.values[position];
            current.chunk_sum = current.chunk_sum + current.values[position];
        }
        update(node);
    }

    Sum local_sum(int node, int right) const {
        Sum result{};
        int full_groups = right / group_size;
        for (int group = 0; group < full_groups; group++) {
            result = result + _nodes[node].group_sums[group];
        }
        for (int position = full_groups * group_size; position < right;
             position++) {
            result = result + _nodes[node].values[position];
        }
        return result;
    }

    void local_insert(int node, int position, const Sum& value) {
        Node& current = _nodes[node];
        assert(0 <= position && position <= current.length);
        assert(current.length < chunk_capacity);
        for (int i = current.length; i > position; i--) {
            current.values[i] = current.values[i - 1];
        }
        current.values[position] = value;
        current.length++;
        rebuild_chunk(node);
    }

    Sum local_erase(int node, int position) {
        Node& current = _nodes[node];
        assert(0 <= position && position < current.length);
        Sum result = current.values[position];
        for (int i = position; i + 1 < current.length; i++) {
            current.values[i] = current.values[i + 1];
        }
        current.length--;
        current.values[current.length] = Sum{};
        rebuild_chunk(node);
        return result;
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
        const std::array<Sum, Capacity>& values,
        int first,
        int last
    ) {
        Node& current = _nodes[node];
        current.values.fill(Sum{});
        current.length = std::uint16_t(last - first);
        for (int i = first; i < last; i++) {
            current.values[i - first] = values[i];
        }
        rebuild_chunk(node);
    }

    void assign_from_values(
        int node,
        const std::vector<Sum>& values,
        int first,
        int last
    ) {
        Node& current = _nodes[node];
        current.values.fill(Sum{});
        current.length = std::uint16_t(last - first);
        for (int i = first; i < last; i++) {
            current.values[i - first] = values[i];
        }
        rebuild_chunk(node);
    }

    int new_node(const std::vector<Sum>& values, int first, int last) {
        int node = new_node();
        assign_from_values(node, values, first, last);
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
            std::array<Sum, chunk_capacity * 2> values{};
            for (int i = 0; i < node_length; i++) {
                values[i] = _nodes[node].values[i];
            }
            for (int i = 0; i < neighbor_length; i++) {
                values[node_length + i] = _nodes[neighbor].values[i];
            }
            if (total <= chunk_capacity) {
                assign_from_values(node, values, 0, total);
                recycle_node(neighbor);
            } else {
                int left_length = total / 2;
                assign_from_values(node, values, 0, left_length);
                assign_from_values(neighbor, values, left_length, total);
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
            std::array<Sum, chunk_capacity * 2> values{};
            for (int i = 0; i < neighbor_length; i++) {
                values[i] = _nodes[neighbor].values[i];
            }
            for (int i = 0; i < node_length; i++) {
                values[neighbor_length + i] = _nodes[node].values[i];
            }
            if (total <= chunk_capacity) {
                assign_from_values(node, values, 0, total);
                recycle_node(neighbor);
            } else {
                int left_length = total / 2;
                assign_from_values(neighbor, values, 0, left_length);
                assign_from_values(node, values, left_length, total);
                _nodes[node].left = merge(_nodes[node].left, neighbor);
            }
            update(node);
        }
        return node;
    }

    int insert_impl(int tree, int position, const Sum& value) {
        if (tree == 0) {
            int node = new_node();
            local_insert(node, 0, value);
            return node;
        }

        int left_size = size_of(_nodes[tree].left);
        int length = _nodes[tree].length;
        if (position < left_size) {
            _nodes[tree].left =
                insert_impl(_nodes[tree].left, position, value);
            update(tree);
            if (_nodes[_nodes[tree].left].priority >
                _nodes[tree].priority) {
                tree = rotate_right(tree);
            }
            return tree;
        }
        if (position > left_size + length) {
            _nodes[tree].right = insert_impl(
                _nodes[tree].right,
                position - left_size - length,
                value
            );
            update(tree);
            if (_nodes[_nodes[tree].right].priority >
                _nodes[tree].priority) {
                tree = rotate_left(tree);
            }
            return tree;
        }

        int local_position = position - left_size;
        if (length < chunk_capacity) {
            local_insert(tree, local_position, value);
            return tree;
        }

        std::array<Sum, chunk_capacity> values = _nodes[tree].values;
        int right_chunk = new_node();
        int middle = chunk_capacity / 2;
        assign_from_values(tree, values, 0, middle);
        assign_from_values(right_chunk, values, middle, chunk_capacity);
        if (local_position <= middle) {
            local_insert(tree, local_position, value);
        } else {
            local_insert(right_chunk, local_position - middle, value);
        }

        int old_right = _nodes[tree].right;
        _nodes[tree].right = 0;
        update(tree);
        return merge(merge(tree, right_chunk), old_right);
    }

    int erase_impl(int tree, int position) {
        int left_size = size_of(_nodes[tree].left);
        int length = _nodes[tree].length;
        if (position < left_size) {
            _nodes[tree].left = erase_impl(_nodes[tree].left, position);
            update(tree);
            return tree;
        }
        if (position >= left_size + length) {
            _nodes[tree].right = erase_impl(
                _nodes[tree].right,
                position - left_size - length
            );
            update(tree);
            return tree;
        }

        local_erase(tree, position - left_size);
        if (_nodes[tree].length == 0) {
            int result = merge(_nodes[tree].left, _nodes[tree].right);
            recycle_node(tree);
            return result;
        }
        return rebalance(tree);
    }

    void set_impl(int tree, int position, const Sum& value) {
        int left_size = size_of(_nodes[tree].left);
        if (position < left_size) {
            set_impl(_nodes[tree].left, position, value);
        } else if (position < left_size + _nodes[tree].length) {
            _nodes[tree].values[position - left_size] = value;
            rebuild_chunk(tree);
            return;
        } else {
            set_impl(
                _nodes[tree].right,
                position - left_size - _nodes[tree].length,
                value
            );
        }
        update(tree);
    }

    void update_subtree(int tree) {
        if (tree == 0) return;
        update_subtree(_nodes[tree].left);
        update_subtree(_nodes[tree].right);
        update(tree);
    }

    void build(const std::vector<Sum>& values) {
        _nodes.clear();
        _nodes.emplace_back();
        _free_nodes.clear();
        _root = 0;
        _nodes.reserve(values.size() / chunk_capacity + 2);

        std::vector<int> stack;
        for (int first = 0; first < int(values.size());
             first += chunk_capacity) {
            int last = std::min(first + chunk_capacity, int(values.size()));
            int node = new_node(values, first, last);
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
    DynamicSumSequence() : _nodes(1) {}

    explicit DynamicSumSequence(
        const std::vector<Sum>& values,
        std::uint32_t seed = 1
    ) : _random_state(seed == 0 ? 1 : seed) {
        build(values);
    }

    int size() const {
        return size_of(_root);
    }

    Sum get(int position) const {
        assert(0 <= position && position < size());
        int tree = _root;
        while (tree != 0) {
            int left_size = size_of(_nodes[tree].left);
            if (position < left_size) {
                tree = _nodes[tree].left;
            } else if (position < left_size + _nodes[tree].length) {
                return _nodes[tree].values[position - left_size];
            } else {
                position -= left_size + _nodes[tree].length;
                tree = _nodes[tree].right;
            }
        }
        assert(false);
        return Sum{};
    }

    Sum prefix_sum(int right) const {
        assert(0 <= right && right <= size());
        Sum result{};
        int tree = _root;
        while (tree != 0 && right != 0) {
            int left_size = size_of(_nodes[tree].left);
            if (right <= left_size) {
                tree = _nodes[tree].left;
                continue;
            }
            result = result + sum_of(_nodes[tree].left);
            right -= left_size;
            int take = std::min(right, int(_nodes[tree].length));
            result = result + local_sum(tree, take);
            right -= take;
            if (right == 0) break;
            tree = _nodes[tree].right;
        }
        return result;
    }

    Sum range_sum(int left, int right) const {
        assert(0 <= left && left <= right && right <= size());
        return prefix_sum(right) - prefix_sum(left);
    }

    void insert(int position, const Sum& value) {
        assert(0 <= position && position <= size());
        _root = insert_impl(_root, position, value);
    }

    Sum erase(int position) {
        assert(0 <= position && position < size());
        Sum result = get(position);
        _root = erase_impl(_root, position);
        return result;
    }

    void set(int position, const Sum& value) {
        assert(0 <= position && position < size());
        set_impl(_root, position, value);
    }
};

}  // namespace dynamic_wavelet_matrix_sum_detail

// A dynamic wavelet matrix with additive weights.
// By default, each value is also used as its weight.
template <std::integral T, typename Sum = T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
class DynamicWaveletMatrixSum {
   public:
    using value_type = T;
    using sum_type = Sum;
    using unsigned_type = std::make_unsigned_t<T>;

   private:
    static constexpr int bit_width =
        std::numeric_limits<unsigned_type>::digits;
    static constexpr unsigned_type sign_mask = [] {
        if constexpr (std::signed_integral<T>) {
            return unsigned_type(1) << (bit_width - 1);
        } else {
            return unsigned_type(0);
        }
    }();

    using BitVector =
        dynamic_wavelet_matrix_detail::DynamicRankBitVector;
    using SumSequence =
        dynamic_wavelet_matrix_sum_detail::DynamicSumSequence<Sum>;

    int _size = 0;
    std::vector<BitVector> _matrix;
    std::vector<SumSequence> _zero_weights;
    SumSequence _original_weights;
    SumSequence _final_weights;
    std::array<int, bit_width> _zero_count{};

    static unsigned_type encode(T value) {
        unsigned_type bits;
        if constexpr (std::signed_integral<T>) {
            bits = std::bit_cast<unsigned_type>(value);
        } else {
            bits = value;
        }
        return bits ^ sign_mask;
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
        return (key >> (bit_width - 1 - level)) & unsigned_type(1);
    }

    void build(const std::vector<T>& values, const std::vector<Sum>& weights) {
        assert(values.size() == weights.size());
        _size = int(values.size());

        std::vector<unsigned_type> current_keys(_size);
        std::vector<unsigned_type> next_keys(_size);
        std::vector<Sum> current_weights(weights);
        std::vector<Sum> next_weights(_size);
        for (int i = 0; i < _size; i++) {
            current_keys[i] = encode(values[i]);
        }

        _original_weights = SumSequence(weights, 0x243f6a88U);
        _matrix.clear();
        _matrix.reserve(bit_width);
        _zero_weights.clear();
        _zero_weights.reserve(bit_width);
        for (int level = 0; level < bit_width; level++) {
            std::vector<std::uint8_t> bits(_size);
            std::vector<Sum> zero_weights(_size, Sum{});
            int zeros = 0;
            for (int i = 0; i < _size; i++) {
                bits[i] = bit(current_keys[i], level);
                zeros += !bits[i];
                if (!bits[i]) zero_weights[i] = current_weights[i];
            }
            _zero_count[level] = zeros;
            _matrix.emplace_back(
                bits,
                std::uint32_t(0x9e3779b9U + level * 0x85ebca6bU)
            );
            _zero_weights.emplace_back(
                zero_weights,
                std::uint32_t(0xc2b2ae35U + level * 0x27d4eb2fU)
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
        _final_weights = SumSequence(current_weights, 0xb7e15162U);
    }

    void insert_encoded(int position, unsigned_type key, const Sum& weight) {
        _original_weights.insert(position, weight);
        for (int level = 0; level < bit_width; level++) {
            int ones_before = _matrix[level].rank1(position);
            bool one = bit(key, level);
            int next_position;
            if (one) {
                next_position = _zero_count[level] + ones_before;
            } else {
                next_position = position - ones_before;
                _zero_count[level]++;
            }
            _matrix[level].insert(position, one);
            _zero_weights[level].insert(
                position,
                one ? Sum{} : weight
            );
            position = next_position;
        }
        _final_weights.insert(position, weight);
        _size++;
    }

    void erase_encoded(int position) {
        _original_weights.erase(position);
        for (int level = 0; level < bit_width; level++) {
            int ones_before = _matrix[level].rank1(position);
            bool one = _matrix[level].get(position);
            int next_position;
            if (one) {
                next_position = _zero_count[level] + ones_before;
            } else {
                next_position = position - ones_before;
                _zero_count[level]--;
            }
            _matrix[level].erase(position);
            _zero_weights[level].erase(position);
            position = next_position;
        }
        _final_weights.erase(position);
        _size--;
    }

    int count_less_encoded(int left, int right, unsigned_type upper) const {
        int result = 0;
        for (int level = 0; level < bit_width; level++) {
            int left_ones = _matrix[level].rank1(left);
            int right_ones = _matrix[level].rank1(right);
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

    Sum sum_less_encoded(int left, int right, unsigned_type upper) const {
        Sum result{};
        for (int level = 0; level < bit_width; level++) {
            int left_ones = _matrix[level].rank1(left);
            int right_ones = _matrix[level].rank1(right);
            if (bit(upper, level)) {
                result = result +
                         _zero_weights[level].range_sum(left, right);
                left = _zero_count[level] + left_ones;
                right = _zero_count[level] + right_ones;
            } else {
                left -= left_ones;
                right -= right_ones;
            }
        }
        return result;
    }

   public:
    DynamicWaveletMatrixSum()
        : _matrix(bit_width), _zero_weights(bit_width) {}

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
        for (int level = 0; level < bit_width; level++) {
            int ones_before = _matrix[level].rank1(position);
            if (_matrix[level].get(position)) {
                key |= unsigned_type(1) << (bit_width - 1 - level);
                position = _zero_count[level] + ones_before;
            } else {
                position -= ones_before;
            }
        }
        return decode(key);
    }

    T operator[](int position) const {
        return access(position);
    }

    Sum weight(int position) const {
        assert(0 <= position && position < _size);
        return _original_weights.get(position);
    }

    std::pair<T, Sum> get(int position) const {
        return std::pair<T, Sum>(access(position), weight(position));
    }

    void insert(int position, T value)
        requires std::convertible_to<T, Sum>
    {
        insert(position, value, static_cast<Sum>(value));
    }

    void insert(int position, T value, const Sum& weight) {
        assert(0 <= position && position <= _size);
        insert_encoded(position, encode(value), weight);
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
        std::pair<T, Sum> result = get(position);
        erase_encoded(position);
        return result;
    }

    void set(int position, T value)
        requires std::convertible_to<T, Sum>
    {
        set(position, value, static_cast<Sum>(value));
    }

    void set(int position, T value, const Sum& weight) {
        assert(0 <= position && position < _size);
        if (access(position) == value) {
            set_weight(position, weight);
            return;
        }
        erase_encoded(position);
        insert_encoded(position, encode(value), weight);
    }

    void set_value(int position, T value) {
        assert(0 <= position && position < _size);
        if (access(position) == value) return;
        Sum current_weight = weight(position);
        erase_encoded(position);
        insert_encoded(position, encode(value), current_weight);
    }

    void set_weight(int position, const Sum& weight) {
        assert(0 <= position && position < _size);
        _original_weights.set(position, weight);
        for (int level = 0; level < bit_width; level++) {
            int ones_before = _matrix[level].rank1(position);
            bool one = _matrix[level].get(position);
            _zero_weights[level].set(position, one ? Sum{} : weight);
            if (one) {
                position = _zero_count[level] + ones_before;
            } else {
                position -= ones_before;
            }
        }
        _final_weights.set(position, weight);
    }

    void add_weight(int position, const Sum& delta) {
        assert(0 <= position && position < _size);
        set_weight(position, weight(position) + delta);
    }

    int rank(T value, int right) const {
        assert(0 <= right && right <= _size);
        return rank(value, 0, right);
    }

    int rank(T value, int left, int right) const {
        assert(0 <= left && left <= right && right <= _size);
        unsigned_type key = encode(value);
        for (int level = 0; level < bit_width; level++) {
            int left_ones = _matrix[level].rank1(left);
            int right_ones = _matrix[level].rank1(right);
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
        for (int level = 0; level < bit_width; level++) {
            int left_ones = _matrix[level].rank1(left);
            int right_ones = _matrix[level].rank1(right);
            int left_zeros = left - left_ones;
            int right_zeros = right - right_ones;
            int zeros = right_zeros - left_zeros;
            if (k < zeros) {
                left = left_zeros;
                right = right_zeros;
            } else {
                k -= zeros;
                key |= unsigned_type(1) << (bit_width - 1 - level);
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
        return count_less_encoded(left, right, encode(upper));
    }

    int range_freq(int left, int right, T lower, T upper) const {
        assert(0 <= left && left <= right && right <= _size);
        if (upper <= lower) return 0;
        return range_freq(left, right, upper) -
               range_freq(left, right, lower);
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
        return _original_weights.range_sum(left, right);
    }

    Sum range_sum(int left, int right, T upper) const {
        assert(0 <= left && left <= right && right <= _size);
        return sum_less_encoded(left, right, encode(upper));
    }

    Sum range_sum(int left, int right, T lower, T upper) const {
        assert(0 <= left && left <= right && right <= _size);
        if (upper <= lower) return Sum{};
        return range_sum(left, right, upper) -
               range_sum(left, right, lower);
    }

    Sum sum_k_smallest(int left, int right, int k) const {
        assert(0 <= left && left <= right && right <= _size);
        assert(0 <= k && k <= right - left);
        Sum result{};
        for (int level = 0; level < bit_width; level++) {
            int left_ones = _matrix[level].rank1(left);
            int right_ones = _matrix[level].rank1(right);
            int left_zeros = left - left_ones;
            int right_zeros = right - right_ones;
            int zeros = right_zeros - left_zeros;
            if (k < zeros) {
                left = left_zeros;
                right = right_zeros;
            } else {
                result = result +
                         _zero_weights[level].range_sum(left, right);
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
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_WAVELET_MATRIX_DYNAMIC_WAVELET_MATRIX_SUM_HPP
