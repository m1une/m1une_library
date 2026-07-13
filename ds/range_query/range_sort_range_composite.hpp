#ifndef M1UNE_DS_RANGE_QUERY_RANGE_SORT_RANGE_COMPOSITE_HPP
#define M1UNE_DS_RANGE_QUERY_RANGE_SORT_RANGE_COMPOSITE_HPP 1

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

#include "../../monoid/concept.hpp"
#include "../segtree/segtree.hpp"

namespace m1une {
namespace ds {

namespace detail {

class RangeSortBoundarySet {
   private:
    static constexpr int word_bits = 64;

    int _n;
    std::vector<std::vector<std::uint64_t>> _levels;

   public:
    explicit RangeSortBoundarySet(int n = 0) : _n(n) {
        assert(n >= 0);
        int size = std::max(n, 1);
        do {
            int words = (size + word_bits - 1) / word_bits;
            _levels.emplace_back(words, 0);
            size = words;
        } while (size > 1);
    }

    bool contains(int index) const {
        assert(0 <= index && index < _n);
        return ((_levels[0][index / word_bits] >> (index % word_bits)) & 1U) != 0;
    }

    void insert(int index) {
        assert(0 <= index && index < _n);
        for (auto& level : _levels) {
            level[index / word_bits] |= std::uint64_t(1) << (index % word_bits);
            index /= word_bits;
        }
    }

    void erase(int index) {
        assert(0 <= index && index < _n);
        for (auto& level : _levels) {
            level[index / word_bits] &= ~(std::uint64_t(1) << (index % word_bits));
            if (level[index / word_bits] != 0) break;
            index /= word_bits;
        }
    }

    int next(int index) const {
        if (index < 0) index = 0;
        for (int level = 0; level < int(_levels.size()); level++) {
            if (index / word_bits >= int(_levels[level].size())) break;
            std::uint64_t word = _levels[level][index / word_bits] >> (index % word_bits);
            if (word == 0) {
                index = index / word_bits + 1;
                continue;
            }
            index += int(std::countr_zero(word));
            for (int lower = level - 1; lower >= 0; lower--) {
                index *= word_bits;
                std::uint64_t lower_word = _levels[lower][index / word_bits];
                index += int(std::countr_zero(lower_word));
            }
            return std::min(index, _n);
        }
        return _n;
    }

    int previous(int index) const {
        if (_n == 0 || index < 0) return -1;
        if (index >= _n) index = _n - 1;
        for (int level = 0; level < int(_levels.size()); level++) {
            std::uint64_t word = _levels[level][index / word_bits]
                               << (word_bits - 1 - index % word_bits);
            if (word == 0) {
                index = index / word_bits - 1;
                if (index < 0) break;
                continue;
            }
            index += 63 - int(std::countl_zero(word)) - (word_bits - 1);
            for (int lower = level - 1; lower >= 0; lower--) {
                index *= word_bits;
                std::uint64_t lower_word = _levels[lower][index / word_bits];
                index += 63 - int(std::countl_zero(lower_word));
            }
            return index;
        }
        return -1;
    }
};

}  // namespace detail

// Maintains a sequence under point assignment, range product, and range sorting
// by distinct compressed integer keys.
template <m1une::monoid::IsMonoid Monoid>
class RangeSortRangeComposite {
   public:
    using T = typename Monoid::value_type;

   private:
    struct Node {
        T product;
        T reverse_product;
        int count;
        int left;
        int right;

        Node(T value, int node_count)
            : product(std::move(value)),
              reverse_product(product),
              count(node_count),
              left(0),
              right(0) {}
    };

    int _n;
    int _key_count;
    int _key_height;
    detail::RangeSortBoundarySet _boundaries;
    Segtree<Monoid> _segments;
    std::vector<bool> _reversed;
    std::vector<int> _roots;
    std::vector<int> _key_frequency;
    std::vector<Node> _nodes;
    int _node_count;
    std::size_t _node_limit;

    static int key_height(int key_count) {
        int result = 0;
        while (key_count > 1) {
            key_count = (key_count + 1) / 2;
            result++;
        }
        return result;
    }

    void reset_node_pool() {
        T identity = Monoid::id();
        if (_nodes.empty()) {
            _nodes.emplace_back(std::move(identity), 0);
        } else {
            _nodes[0] = Node(std::move(identity), 0);
        }
        _node_count = 1;
    }

    int new_node(T value = Monoid::id()) {
        int result = _node_count++;
        if (result == int(_nodes.size())) {
            _nodes.emplace_back(std::move(value), 1);
        } else {
            _nodes[result] = Node(std::move(value), 1);
        }
        return result;
    }

    void update(int node) {
        int left = _nodes[node].left;
        int right = _nodes[node].right;
        if (left == 0 && right == 0) return;
        if (left == 0) {
            _nodes[node].product = _nodes[right].product;
            _nodes[node].reverse_product = _nodes[right].reverse_product;
            _nodes[node].count = _nodes[right].count;
            return;
        }
        if (right == 0) {
            _nodes[node].product = _nodes[left].product;
            _nodes[node].reverse_product = _nodes[left].reverse_product;
            _nodes[node].count = _nodes[left].count;
            return;
        }
        _nodes[node].product = Monoid::op(_nodes[left].product, _nodes[right].product);
        _nodes[node].reverse_product = Monoid::op(
            _nodes[right].reverse_product,
            _nodes[left].reverse_product
        );
        _nodes[node].count = _nodes[left].count + _nodes[right].count;
    }

    void set_key(int node, int left, int right, int key, const T& value) {
        if (right - left == 1) {
            _nodes[node].product = value;
            _nodes[node].reverse_product = value;
            return;
        }
        int middle = (left + right) / 2;
        if (key < middle) {
            if (_nodes[node].left == 0) _nodes[node].left = new_node();
            int child = _nodes[node].left;
            set_key(child, left, middle, key, value);
        } else {
            if (_nodes[node].right == 0) _nodes[node].right = new_node();
            int child = _nodes[node].right;
            set_key(child, middle, right, key, value);
        }
        update(node);
    }

    std::pair<int, int> split_tree(int node, int count) {
        if (count == 0) return {0, node};
        if (count == _nodes[node].count) return {node, 0};

        int second = new_node();
        int left_count = _nodes[_nodes[node].left].count;
        if (count <= left_count) {
            auto [first_left, second_left] = split_tree(_nodes[node].left, count);
            int old_right = _nodes[node].right;
            _nodes[node].left = first_left;
            _nodes[node].right = 0;
            _nodes[second].left = second_left;
            _nodes[second].right = old_right;
        } else {
            auto [first_right, second_right]
                = split_tree(_nodes[node].right, count - left_count);
            _nodes[node].right = first_right;
            _nodes[second].left = 0;
            _nodes[second].right = second_right;
        }
        update(node);
        update(second);
        return {node, second};
    }

    int merge_trees(int first, int second) {
        if (first == 0 || second == 0) return first != 0 ? first : second;
        int first_left = _nodes[first].left;
        int first_right = _nodes[first].right;
        _nodes[first].left = merge_trees(first_left, _nodes[second].left);
        _nodes[first].right = merge_trees(first_right, _nodes[second].right);
        update(first);
        return first;
    }

    int only_key(int node, int left, int right) const {
        assert(node != 0 && _nodes[node].count == 1);
        while (right - left > 1) {
            int middle = (left + right) / 2;
            if (_nodes[node].left != 0) {
                node = _nodes[node].left;
                right = middle;
            } else {
                node = _nodes[node].right;
                left = middle;
            }
        }
        return left;
    }

    void split_at(int position) {
        if (position == _n || _boundaries.contains(position)) return;
        int first = _boundaries.previous(position);
        int next = _boundaries.next(first + 1);
        assert(first >= 0 && next > position);
        _boundaries.insert(position);

        if (!_reversed[first]) {
            auto [left, right] = split_tree(_roots[first], position - first);
            _roots[first] = left;
            _roots[position] = right;
            _reversed[first] = false;
            _reversed[position] = false;
            _segments.set(first, _nodes[left].product);
            _segments.set(position, _nodes[right].product);
        } else {
            auto [left, right] = split_tree(_roots[first], next - position);
            _roots[first] = right;
            _roots[position] = left;
            _reversed[first] = true;
            _reversed[position] = true;
            _segments.set(first, _nodes[right].reverse_product);
            _segments.set(position, _nodes[left].reverse_product);
        }
    }

    void dump_tree(
        int node,
        int left,
        int right,
        bool reversed,
        std::vector<int>& keys,
        std::vector<T>& values
    ) const {
        if (node == 0) return;
        if (right - left == 1) {
            assert(_nodes[node].count == 1);
            keys.push_back(left);
            values.push_back(_nodes[node].product);
            return;
        }
        int middle = (left + right) / 2;
        if (!reversed) {
            dump_tree(_nodes[node].left, left, middle, false, keys, values);
            dump_tree(_nodes[node].right, middle, right, false, keys, values);
        } else {
            dump_tree(_nodes[node].right, middle, right, true, keys, values);
            dump_tree(_nodes[node].left, left, middle, true, keys, values);
        }
    }

    void initialize_runs(const std::vector<int>& keys, const std::vector<T>& values) {
        reset_node_pool();
        _boundaries = detail::RangeSortBoundarySet(_n);
        _segments = Segtree<Monoid>(values);
        _reversed.assign(_n, false);
        _roots.assign(_n, 0);
        for (int index = 0; index < _n; index++) {
            _boundaries.insert(index);
            _roots[index] = new_node();
            set_key(_roots[index], 0, _key_count, keys[index], values[index]);
        }
    }

    void rebuild() {
        std::vector<int> keys;
        std::vector<T> values;
        keys.reserve(_n);
        values.reserve(_n);
        for (int position = _boundaries.next(0); position < _n;
             position = _boundaries.next(position + 1)) {
            dump_tree(
                _roots[position],
                0,
                _key_count,
                _reversed[position],
                keys,
                values
            );
        }
        assert(int(keys.size()) == _n);
        initialize_runs(keys, values);
    }

    void ensure_node_space() {
        std::size_t margin = std::size_t(4) * std::size_t(_key_height + 2);
        if (std::size_t(_node_count) + margin > _node_limit) rebuild();
    }

   public:
    RangeSortRangeComposite()
        : _n(0),
          _key_count(0),
          _key_height(0),
          _boundaries(0),
          _segments(),
          _node_count(0),
          _node_limit(1) {
        reset_node_pool();
    }

    RangeSortRangeComposite(
        int key_count,
        const std::vector<int>& keys,
        const std::vector<T>& values
    )
        : _n(0),
          _key_count(key_count),
          _key_height(0),
          _boundaries(0),
          _segments(),
          _node_count(0),
          _node_limit(1) {
        assert(key_count >= 0);
        assert(keys.size() == values.size());
        assert(keys.size() <= std::size_t(std::numeric_limits<int>::max()));
        _n = int(keys.size());
        assert(_n == 0 || key_count > 0);
        _key_height = key_height(key_count);
        _key_frequency.assign(key_count, 0);
        for (int key : keys) {
            assert(0 <= key && key < key_count);
            assert(_key_frequency[key] == 0);
            _key_frequency[key] = 1;
        }

        std::size_t height = std::size_t(_key_height + 1);
        std::size_t initial_nodes = std::size_t(_n) * height + 1;
        std::size_t slack = std::max<std::size_t>(1024, std::size_t(8) * std::size_t(_n) + 64);
        _node_limit = initial_nodes + slack;
        _nodes.reserve(_node_limit);
        initialize_runs(keys, values);
        assert(std::size_t(_node_count) <= initial_nodes);
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    int key_count() const {
        return _key_count;
    }

    std::pair<int, T> get(int position) {
        assert(0 <= position && position < _n);
        ensure_node_space();
        split_at(position);
        split_at(position + 1);
        int key = only_key(_roots[position], 0, _key_count);
        return {key, _nodes[_roots[position]].product};
    }

    void set(int position, int key, T value) {
        assert(0 <= position && position < _n);
        assert(0 <= key && key < _key_count);
        ensure_node_space();
        split_at(position);
        split_at(position + 1);
        int old_key = only_key(_roots[position], 0, _key_count);
        assert(key == old_key || _key_frequency[key] == 0);
        _key_frequency[old_key]--;
        _key_frequency[key]++;

        _reversed[position] = false;
        _roots[position] = new_node();
        set_key(_roots[position], 0, _key_count, key, value);
        _segments.set(position, value);
    }

    T prod(int left, int right) {
        assert(0 <= left && left <= right && right <= _n);
        if (left == right) return Monoid::id();
        ensure_node_space();
        split_at(left);
        split_at(right);
        return _segments.prod(left, right);
    }

    T all_prod() const {
        return _segments.all_prod();
    }

    void sort_ascending(int left, int right) {
        assert(0 <= left && left <= right && right <= _n);
        if (left == right) return;
        ensure_node_space();
        split_at(left);
        split_at(right);
        while (true) {
            int next = _boundaries.next(left + 1);
            if (next == right) break;
            _roots[left] = merge_trees(_roots[left], _roots[next]);
            _roots[next] = 0;
            _reversed[next] = false;
            _boundaries.erase(next);
            _segments.set(next, Monoid::id());
        }
        _reversed[left] = false;
        _segments.set(left, _nodes[_roots[left]].product);
    }

    void sort_descending(int left, int right) {
        assert(0 <= left && left <= right && right <= _n);
        if (left == right) return;
        sort_ascending(left, right);
        _reversed[left] = true;
        _segments.set(left, _nodes[_roots[left]].reverse_product);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_RANGE_QUERY_RANGE_SORT_RANGE_COMPOSITE_HPP
