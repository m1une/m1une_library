#ifndef M1UNE_DS_WAVELET_MATRIX_DYNAMIC_WAVELET_MATRIX_HPP
#define M1UNE_DS_WAVELET_MATRIX_DYNAMIC_WAVELET_MATRIX_HPP 1

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

namespace m1une {
namespace ds {

namespace dynamic_wavelet_matrix_detail {

// A dynamic bit vector stored as an implicit treap of small packed chunks.
class DynamicRankBitVector {
   public:
    struct AccessRankResult {
        bool value;
        int ones_before;
    };

    struct EraseRankResult {
        bool value;
        int ones_before;
    };

    struct RankPair {
        int left_ones;
        int right_ones;
    };

   private:
    static constexpr int word_bits = 64;
    static constexpr int chunk_words = 4;
    static constexpr int chunk_capacity = word_bits * chunk_words;
    static constexpr int minimum_chunk_size = chunk_capacity / 2;

    struct Node {
        std::array<std::uint64_t, chunk_words> bits{};
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
        _nodes[node].subtree_ones =
            ones_of(_nodes[node].left) + int(_nodes[node].chunk_ones) +
            ones_of(_nodes[node].right);
    }

    bool local_get(int node, int position) const {
        return (_nodes[node].bits[position / word_bits] >>
                (position % word_bits)) &
               1U;
    }

    void local_set(int node, int position, bool value) {
        std::uint64_t mask =
            std::uint64_t(1) << (position % word_bits);
        std::uint64_t& word = _nodes[node].bits[position / word_bits];
        if (value) {
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

    void clear_unused_bits(int node) {
        int length = _nodes[node].length;
        int word = length / word_bits;
        int remainder = length % word_bits;
        if (word < chunk_words) {
            if (remainder == 0) {
                _nodes[node].bits[word] = 0;
            } else {
                _nodes[node].bits[word] &=
                    (std::uint64_t(1) << remainder) - 1;
                word++;
            }
            for (; word < chunk_words; word++) {
                _nodes[node].bits[word] = 0;
            }
        }
    }

    void local_insert(int node, int position, bool value) {
        Node& current = _nodes[node];
        assert(0 <= position && position <= current.length);
        assert(current.length < chunk_capacity);

        int first_word = position / word_bits;
        int offset = position % word_bits;
        for (int word = chunk_words - 1; word > first_word; word--) {
            current.bits[word] =
                (current.bits[word] << 1) |
                (current.bits[word - 1] >> (word_bits - 1));
        }
        std::uint64_t lower_mask =
            offset == 0 ? 0 : (std::uint64_t(1) << offset) - 1;
        current.bits[first_word] =
            (current.bits[first_word] & lower_mask) |
            ((current.bits[first_word] & ~lower_mask) << 1);
        if (value) {
            current.bits[first_word] |= std::uint64_t(1) << offset;
        }
        current.length++;
        current.chunk_ones += value;
        clear_unused_bits(node);
        update(node);
    }

    bool local_erase(int node, int position) {
        Node& current = _nodes[node];
        assert(0 <= position && position < current.length);
        bool value = local_get(node, position);
        int first_word = position / word_bits;
        int offset = position % word_bits;
        std::uint64_t lower_mask =
            offset == 0 ? 0 : (std::uint64_t(1) << offset) - 1;
        std::uint64_t shifted =
            offset == word_bits - 1
                ? 0
                : (current.bits[first_word] >> (offset + 1)) << offset;
        std::uint64_t carry =
            first_word + 1 < chunk_words
                ? (current.bits[first_word + 1] & 1U) << (word_bits - 1)
                : 0;
        current.bits[first_word] =
            (current.bits[first_word] & lower_mask) | shifted | carry;
        for (int word = first_word + 1; word < chunk_words; word++) {
            std::uint64_t next_carry =
                word + 1 < chunk_words
                    ? (current.bits[word + 1] & 1U) << (word_bits - 1)
                    : 0;
            current.bits[word] = (current.bits[word] >> 1) | next_carry;
        }
        current.length--;
        current.chunk_ones -= value;
        clear_unused_bits(node);
        update(node);
        return value;
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

    int new_node(const std::vector<std::uint8_t>& bits, int first, int last) {
        int node = new_node();
        _nodes[node].length = std::uint16_t(last - first);
        for (int position = first; position < last; position++) {
            if (bits[position]) {
                local_set(node, position - first, true);
                _nodes[node].chunk_ones++;
            }
        }
        update(node);
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

    void assign_concatenation(
        int destination,
        int first,
        int second,
        int begin,
        int length
    ) {
        std::array<std::uint64_t, chunk_words> bits{};
        int ones = 0;
        int first_length = _nodes[first].length;
        for (int position = 0; position < length; position++) {
            int source_position = begin + position;
            bool value = source_position < first_length
                             ? local_get(first, source_position)
                             : local_get(
                                   second,
                                   source_position - first_length
                               );
            if (value) {
                bits[position / word_bits] |=
                    std::uint64_t(1) << (position % word_bits);
                ones++;
            }
        }
        _nodes[destination].bits = bits;
        _nodes[destination].length = std::uint16_t(length);
        _nodes[destination].chunk_ones = std::uint16_t(ones);
        update(destination);
    }

    int rebalance(int node) {
        if (_nodes[node].length >= minimum_chunk_size) return node;

        if (_nodes[node].right != 0) {
            int neighbor = 0;
            _nodes[node].right =
                extract_leftmost(_nodes[node].right, neighbor);
            int total = _nodes[node].length + _nodes[neighbor].length;
            if (total <= chunk_capacity) {
                assign_concatenation(node, node, neighbor, 0, total);
                recycle_node(neighbor);
            } else {
                int left_length = total / 2;
                std::array<std::uint8_t, chunk_capacity * 2> values{};
                for (int i = 0; i < _nodes[node].length; i++) {
                    values[i] = local_get(node, i);
                }
                int old_length = _nodes[node].length;
                for (int i = 0; i < _nodes[neighbor].length; i++) {
                    values[old_length + i] = local_get(neighbor, i);
                }
                std::vector<std::uint8_t> packed(values.begin(), values.begin() + total);
                assign_from_values(node, packed, 0, left_length);
                assign_from_values(neighbor, packed, left_length, total);
                _nodes[node].right = merge(neighbor, _nodes[node].right);
            }
            update(node);
            return node;
        }

        if (_nodes[node].left != 0) {
            int neighbor = 0;
            _nodes[node].left =
                extract_rightmost(_nodes[node].left, neighbor);
            int total = _nodes[neighbor].length + _nodes[node].length;
            std::array<std::uint8_t, chunk_capacity * 2> values{};
            for (int i = 0; i < _nodes[neighbor].length; i++) {
                values[i] = local_get(neighbor, i);
            }
            int neighbor_length = _nodes[neighbor].length;
            for (int i = 0; i < _nodes[node].length; i++) {
                values[neighbor_length + i] = local_get(node, i);
            }
            std::vector<std::uint8_t> packed(values.begin(), values.begin() + total);
            if (total <= chunk_capacity) {
                assign_from_values(node, packed, 0, total);
                recycle_node(neighbor);
            } else {
                int left_length = total / 2;
                assign_from_values(neighbor, packed, 0, left_length);
                assign_from_values(node, packed, left_length, total);
                _nodes[node].left = merge(_nodes[node].left, neighbor);
            }
            update(node);
        }
        return node;
    }

    void assign_from_values(
        int node,
        const std::vector<std::uint8_t>& values,
        int first,
        int last
    ) {
        _nodes[node].bits.fill(0);
        _nodes[node].length = std::uint16_t(last - first);
        _nodes[node].chunk_ones = 0;
        for (int i = first; i < last; i++) {
            if (values[i]) {
                local_set(node, i - first, true);
                _nodes[node].chunk_ones++;
            }
        }
        update(node);
    }

    int prefix_rank1_impl(int tree, int right) const {
        int result = 0;
        while (tree != 0 && right != 0) {
            int left_size = size_of(_nodes[tree].left);
            if (right <= left_size) {
                tree = _nodes[tree].left;
                continue;
            }
            result += ones_of(_nodes[tree].left);
            right -= left_size;
            int take = std::min(right, int(_nodes[tree].length));
            result += local_rank1(tree, take);
            right -= take;
            if (right == 0) break;
            tree = _nodes[tree].right;
        }
        return result;
    }

    RankPair rank1_pair_impl(int tree, int left, int right) const {
        if (left == right) {
            int ones = prefix_rank1_impl(tree, left);
            return RankPair{ones, ones};
        }
        if (tree == 0 || right == 0) return RankPair{0, 0};

        int left_size = size_of(_nodes[tree].left);
        int chunk_end = left_size + _nodes[tree].length;
        if (right <= left_size) {
            return rank1_pair_impl(_nodes[tree].left, left, right);
        }
        if (chunk_end <= left) {
            int base =
                ones_of(_nodes[tree].left) + _nodes[tree].chunk_ones;
            RankPair result = rank1_pair_impl(
                _nodes[tree].right,
                left - chunk_end,
                right - chunk_end
            );
            result.left_ones += base;
            result.right_ones += base;
            return result;
        }

        int left_ones;
        if (left <= left_size) {
            left_ones = prefix_rank1_impl(_nodes[tree].left, left);
        } else {
            left_ones = ones_of(_nodes[tree].left) +
                        local_rank1(tree, left - left_size);
        }

        int right_ones;
        if (right <= chunk_end) {
            right_ones = ones_of(_nodes[tree].left) +
                         local_rank1(tree, right - left_size);
        } else {
            right_ones = ones_of(_nodes[tree].left) +
                         _nodes[tree].chunk_ones +
                         prefix_rank1_impl(
                             _nodes[tree].right,
                             right - chunk_end
                         );
        }
        return RankPair{left_ones, right_ones};
    }

    int insert_impl(
        int tree,
        int position,
        bool value,
        int& ones_before
    ) {
        if (tree == 0) {
            int node = new_node();
            local_insert(node, 0, value);
            return node;
        }

        int left_size = size_of(_nodes[tree].left);
        int length = _nodes[tree].length;
        if (position < left_size) {
            _nodes[tree].left = insert_impl(
                _nodes[tree].left,
                position,
                value,
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
                value,
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
        if (length < chunk_capacity) {
            local_insert(tree, local_position, value);
            return tree;
        }

        std::vector<std::uint8_t> values(chunk_capacity);
        for (int i = 0; i < chunk_capacity; i++) {
            values[i] = local_get(tree, i);
        }
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
        result.value = local_erase(tree, local_position);
        if (_nodes[tree].length == 0) {
            int merged = merge(_nodes[tree].left, _nodes[tree].right);
            recycle_node(tree);
            return merged;
        }
        return rebalance(tree);
    }

    void update_subtree(int tree) {
        if (tree == 0) return;
        update_subtree(_nodes[tree].left);
        update_subtree(_nodes[tree].right);
        update(tree);
    }

    void build(const std::vector<std::uint8_t>& bits) {
        _nodes.clear();
        _nodes.emplace_back();
        _free_nodes.clear();
        _root = 0;
        _nodes.reserve(bits.size() / minimum_chunk_size + 2);

        std::vector<int> stack;
        for (int first = 0; first < int(bits.size()); first += chunk_capacity) {
            int last = std::min(first + chunk_capacity, int(bits.size()));
            int node = new_node(bits, first, last);
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
    DynamicRankBitVector() : _nodes(1) {}

    explicit DynamicRankBitVector(
        const std::vector<std::uint8_t>& bits,
        std::uint32_t seed = 1
    ) : _random_state(seed == 0 ? 1 : seed) {
        build(bits);
    }

    int size() const {
        return size_of(_root);
    }

    bool get(int position) const {
        return access_with_rank(position).value;
    }

    AccessRankResult access_with_rank(int position) const {
        assert(0 <= position && position < size());
        int ones_before = 0;
        int tree = _root;
        while (tree != 0) {
            int left_size = size_of(_nodes[tree].left);
            if (position < left_size) {
                tree = _nodes[tree].left;
            } else if (position < left_size + _nodes[tree].length) {
                int local_position = position - left_size;
                ones_before += ones_of(_nodes[tree].left) +
                               local_rank1(tree, local_position);
                return AccessRankResult{
                    local_get(tree, local_position),
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
        return AccessRankResult{false, 0};
    }

    int rank1(int right) const {
        assert(0 <= right && right <= size());
        return prefix_rank1_impl(_root, right);
    }

    RankPair rank1_pair(int left, int right) const {
        assert(0 <= left && left <= right && right <= size());
        return rank1_pair_impl(_root, left, right);
    }

    void insert(int position, bool value) {
        insert_with_rank(position, value);
    }

    int insert_with_rank(int position, bool value) {
        assert(0 <= position && position <= size());
        int ones_before = 0;
        _root = insert_impl(_root, position, value, ones_before);
        return ones_before;
    }

    bool erase(int position) {
        return erase_with_rank(position).value;
    }

    EraseRankResult erase_with_rank(int position) {
        assert(0 <= position && position < size());
        EraseRankResult result{false, 0};
        _root = erase_impl(_root, position, result);
        return result;
    }
};

}  // namespace dynamic_wavelet_matrix_detail

// A dynamic wavelet matrix for integral sequences.
template <std::integral T>
requires(!std::same_as<std::remove_cv_t<T>, bool>)
class DynamicWaveletMatrix {
   public:
    using value_type = T;
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

    int _size = 0;
    std::vector<dynamic_wavelet_matrix_detail::DynamicRankBitVector> _matrix;
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

    void insert_encoded(int position, unsigned_type key) {
        for (int level = 0; level < bit_width; level++) {
            if (bit(key, level)) {
                int ones_before =
                    _matrix[level].insert_with_rank(position, true);
                int next_position = _zero_count[level] + ones_before;
                position = next_position;
            } else {
                int ones_before =
                    _matrix[level].insert_with_rank(position, false);
                int next_position = position - ones_before;
                _zero_count[level]++;
                position = next_position;
            }
        }
        _size++;
    }

    void erase_encoded(int position) {
        for (int level = 0; level < bit_width; level++) {
            auto erased = _matrix[level].erase_with_rank(position);
            int next_position;
            if (erased.value) {
                next_position = _zero_count[level] + erased.ones_before;
            } else {
                next_position = position - erased.ones_before;
                _zero_count[level]--;
            }
            position = next_position;
        }
        _size--;
    }

    int count_less_encoded(int left, int right, unsigned_type upper) const {
        int result = 0;
        for (int level = 0; level < bit_width; level++) {
            auto ranks = _matrix[level].rank1_pair(left, right);
            int left_ones = ranks.left_ones;
            int right_ones = ranks.right_ones;
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

   public:
    DynamicWaveletMatrix() : _matrix(bit_width) {}

    explicit DynamicWaveletMatrix(const std::vector<T>& values)
        : _size(int(values.size())) {
        std::vector<unsigned_type> current(_size);
        std::vector<unsigned_type> next(_size);
        for (int i = 0; i < _size; i++) current[i] = encode(values[i]);

        _matrix.reserve(bit_width);
        for (int level = 0; level < bit_width; level++) {
            std::vector<std::uint8_t> bits(_size);
            int zeros = 0;
            for (int i = 0; i < _size; i++) {
                bits[i] = bit(current[i], level);
                zeros += !bits[i];
            }
            _zero_count[level] = zeros;
            int zero_position = 0;
            int one_position = zeros;
            for (int i = 0; i < _size; i++) {
                if (bits[i]) {
                    next[one_position++] = current[i];
                } else {
                    next[zero_position++] = current[i];
                }
            }
            _matrix.emplace_back(
                bits,
                std::uint32_t(0x9e3779b9U + level * 0x85ebca6bU)
            );
            current.swap(next);
        }
    }

    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    void clear() {
        *this = DynamicWaveletMatrix();
    }

    T access(int position) const {
        assert(0 <= position && position < _size);
        unsigned_type key = 0;
        for (int level = 0; level < bit_width; level++) {
            auto accessed = _matrix[level].access_with_rank(position);
            if (accessed.value) {
                key |= unsigned_type(1) << (bit_width - 1 - level);
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

    void insert(int position, T value) {
        assert(0 <= position && position <= _size);
        insert_encoded(position, encode(value));
    }

    void push_back(T value) {
        insert(_size, value);
    }

    T erase(int position) {
        assert(0 <= position && position < _size);
        T value = access(position);
        erase_encoded(position);
        return value;
    }

    void set(int position, T value) {
        assert(0 <= position && position < _size);
        if (access(position) == value) return;
        erase_encoded(position);
        insert_encoded(position, encode(value));
    }

    int rank(T value, int right) const {
        assert(0 <= right && right <= _size);
        return rank(value, 0, right);
    }

    int rank(T value, int left, int right) const {
        assert(0 <= left && left <= right && right <= _size);
        unsigned_type key = encode(value);
        for (int level = 0; level < bit_width; level++) {
            auto ranks = _matrix[level].rank1_pair(left, right);
            int left_ones = ranks.left_ones;
            int right_ones = ranks.right_ones;
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
            auto ranks = _matrix[level].rank1_pair(left, right);
            int left_ones = ranks.left_ones;
            int right_ones = ranks.right_ones;
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
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_WAVELET_MATRIX_DYNAMIC_WAVELET_MATRIX_HPP
