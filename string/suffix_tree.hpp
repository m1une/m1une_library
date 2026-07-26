#ifndef M1UNE_STRING_SUFFIX_TREE_HPP
#define M1UNE_STRING_SUFFIX_TREE_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <limits>
#include <utility>
#include <vector>

namespace m1une {
namespace string {

template <int AlphabetSize = 26, int FirstCharacter = 'a'>
struct SuffixTree {
    static_assert(0 < AlphabetSize);

    using node_id = int;
    static constexpr node_id root_node = 0;
    static constexpr node_id null_node = -1;
    static constexpr int terminal_symbol = AlphabetSize;

    struct Node {
        std::array<node_id, AlphabetSize + 1> next;
        node_id suffix_link;
        node_id parent;
        int left;
        int right;
        int suffix_start;
        int representative_suffix;
        int leaf_count;
        int incoming_symbol;
        node_id first_child;
        node_id next_sibling;
        int child_count;

        Node(int left_value = 0, int right_value = 0, node_id parent_value = null_node)
            : suffix_link(null_node),
              parent(parent_value),
              left(left_value),
              right(right_value),
              suffix_start(-1),
              representative_suffix(-1),
              leaf_count(0),
              incoming_symbol(-1),
              first_child(null_node),
              next_sibling(null_node),
              child_count(0) {
            next.fill(null_node);
        }
    };

    struct Locus {
        node_id node;
        int offset;

        explicit operator bool() const {
            return node != null_node;
        }

        friend bool operator==(const Locus&, const Locus&) = default;
    };

   private:
    struct ActivePoint {
        node_id node;
        int offset;
    };

    std::vector<Node> _nodes;
    std::vector<int> _text;
    ActivePoint _active;
    int _text_length;

    template <class Symbol>
    static int symbol_index(const Symbol& symbol) {
        int index = int(symbol) - FirstCharacter;
        assert(0 <= index && index < AlphabetSize);
        return index;
    }

    int edge_length_unchecked(node_id id) const {
        return _nodes[id].right - _nodes[id].left;
    }

    node_id new_node(int left, int right, node_id parent) {
        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));
        _nodes.emplace_back(left, right, parent);
        return int(_nodes.size()) - 1;
    }

    ActivePoint go(ActivePoint point, int left, int right) const {
        while (left < right) {
            if (point.offset == edge_length_unchecked(point.node)) {
                point = {_nodes[point.node].next[_text[left]], 0};
                if (point.node == null_node) return point;
            } else {
                if (_text[_nodes[point.node].left + point.offset] != _text[left]) {
                    return {null_node, 0};
                }
                int remaining = edge_length_unchecked(point.node) - point.offset;
                if (right - left < remaining) {
                    point.offset += right - left;
                    return point;
                }
                left += remaining;
                point.offset = edge_length_unchecked(point.node);
            }
        }
        return point;
    }

    node_id split(ActivePoint point) {
        if (point.offset == edge_length_unchecked(point.node)) return point.node;
        if (point.offset == 0) return _nodes[point.node].parent;

        node_id child = point.node;
        node_id parent = _nodes[child].parent;
        int left = _nodes[child].left;
        node_id middle = new_node(left, left + point.offset, parent);
        _nodes[parent].next[_text[left]] = middle;
        _nodes[middle].next[_text[left + point.offset]] = child;
        _nodes[child].parent = middle;
        _nodes[child].left += point.offset;
        return middle;
    }

    node_id get_suffix_link(node_id id) {
        if (_nodes[id].suffix_link != null_node) return _nodes[id].suffix_link;
        node_id parent = _nodes[id].parent;
        if (parent == null_node) return root_node;

        node_id parent_link = get_suffix_link(parent);
        ActivePoint point = {
            parent_link,
            edge_length_unchecked(parent_link)
        };
        int left = _nodes[id].left + (parent == root_node);
        point = go(point, left, _nodes[id].right);
        assert(point.node != null_node);
        return _nodes[id].suffix_link = split(point);
    }

    void extend(int position) {
        while (true) {
            ActivePoint next = go(_active, position, position + 1);
            if (next.node != null_node) {
                _active = next;
                return;
            }

            node_id middle = split(_active);
            node_id leaf = new_node(position, int(_text.size()), middle);
            _nodes[middle].next[_text[position]] = leaf;

            _active.node = get_suffix_link(middle);
            _active.offset = edge_length_unchecked(_active.node);
            if (middle == root_node) return;
        }
    }

    void finish_metadata() {
        std::vector<node_id> order;
        order.reserve(_nodes.size());
        order.push_back(root_node);
        std::vector<int> depth(_nodes.size(), 0);

        for (std::size_t i = 0; i < order.size(); i++) {
            node_id id = order[i];
            node_id previous_child = null_node;
            for (int symbol = 0; symbol <= terminal_symbol; symbol++) {
                node_id child = _nodes[id].next[symbol];
                if (child == null_node) continue;
                _nodes[child].incoming_symbol = symbol;
                if (previous_child == null_node) {
                    _nodes[id].first_child = child;
                } else {
                    _nodes[previous_child].next_sibling = child;
                }
                previous_child = child;
                _nodes[id].child_count++;
                depth[child] = depth[id] + edge_length_unchecked(child);
                order.push_back(child);
            }
        }

        for (int i = int(order.size()) - 1; i >= 0; i--) {
            node_id id = order[i];
            bool leaf = true;
            for (node_id child : _nodes[id].next) {
                if (child == null_node) continue;
                leaf = false;
                _nodes[id].leaf_count += _nodes[child].leaf_count;
                if (_nodes[id].representative_suffix == -1) {
                    _nodes[id].representative_suffix = _nodes[child].representative_suffix;
                }
            }
            if (leaf) {
                _nodes[id].suffix_start = int(_text.size()) - depth[id];
                _nodes[id].representative_suffix = _nodes[id].suffix_start;
                _nodes[id].leaf_count = 1;
            }
        }
    }

    void initialize() {
        _nodes.clear();
        _nodes.reserve(2 * _text.size() + 1);
        _nodes.emplace_back();
        _nodes[root_node].suffix_link = root_node;
        _active = {root_node, 0};
        for (int position = 0; position < int(_text.size()); position++) extend(position);
        finish_metadata();
    }

   public:
    SuffixTree() {
        clear();
    }

    template <class Sequence>
    explicit SuffixTree(const Sequence& sequence) {
        build(sequence);
    }

    int size() const {
        return node_count();
    }

    bool empty() const {
        return _text_length == 0;
    }

    int node_count() const {
        return int(_nodes.size());
    }

    int text_length() const {
        return _text_length;
    }

    node_id root() const {
        return root_node;
    }

    const Node& node(node_id id) const {
        assert(0 <= id && id < node_count());
        return _nodes[id];
    }

    const std::vector<Node>& nodes() const {
        return _nodes;
    }

    int edge_length(node_id id) const {
        assert(0 <= id && id < node_count());
        return edge_length_unchecked(id);
    }

    bool is_leaf(node_id id) const {
        assert(0 <= id && id < node_count());
        return _nodes[id].suffix_start != -1;
    }

    template <class Symbol>
    node_id child(node_id id, const Symbol& symbol) const {
        assert(0 <= id && id < node_count());
        return _nodes[id].next[symbol_index(symbol)];
    }

    node_id child_by_index(node_id id, int symbol) const {
        assert(0 <= id && id < node_count());
        assert(0 <= symbol && symbol <= terminal_symbol);
        return _nodes[id].next[symbol];
    }

    template <class Callback>
    void for_each_child(node_id id, Callback callback) const {
        assert(0 <= id && id < node_count());
        for (
            node_id child_id = _nodes[id].first_child;
            child_id != null_node;
            child_id = _nodes[child_id].next_sibling
        ) {
            callback(_nodes[child_id].incoming_symbol, child_id);
        }
    }

    void clear() {
        _text.clear();
        _text.push_back(terminal_symbol);
        _text_length = 0;
        initialize();
    }

    template <class Sequence>
    void build(const Sequence& sequence) {
        _text.clear();
        for (const auto& symbol : sequence) _text.push_back(symbol_index(symbol));
        assert(_text.size() < std::size_t(std::numeric_limits<int>::max()));
        _text_length = int(_text.size());
        _text.push_back(terminal_symbol);
        initialize();
    }

    template <class Sequence>
    Locus find(const Sequence& sequence) const {
        ActivePoint point = {root_node, 0};
        for (const auto& value : sequence) {
            int symbol = symbol_index(value);
            if (point.offset == edge_length_unchecked(point.node)) {
                point = {_nodes[point.node].next[symbol], 0};
                if (point.node == null_node) return {null_node, 0};
            }
            if (_text[_nodes[point.node].left + point.offset] != symbol) {
                return {null_node, 0};
            }
            point.offset++;
        }
        return {point.node, point.offset};
    }

    template <class Sequence>
    bool contains(const Sequence& sequence) const {
        return bool(find(sequence));
    }

    template <class Sequence>
    int count_occurrences(const Sequence& sequence) const {
        Locus locus = find(sequence);
        return locus ? _nodes[locus.node].leaf_count : 0;
    }

    template <class Sequence>
    std::pair<int, int> representative_occurrence(const Sequence& sequence) const {
        Locus locus = {root_node, 0};
        int length = 0;
        for (const auto& value : sequence) {
            int symbol = symbol_index(value);
            if (locus.offset == edge_length_unchecked(locus.node)) {
                locus = {_nodes[locus.node].next[symbol], 0};
                if (locus.node == null_node) return {-1, -1};
            }
            if (_text[_nodes[locus.node].left + locus.offset] != symbol) return {-1, -1};
            locus.offset++;
            length++;
        }
        int left = _nodes[locus.node].representative_suffix;
        return {left, left + length};
    }

    long long distinct_substring_count() const {
        long long result = 0;
        for (node_id id = 1; id < node_count(); id++) {
            result += std::max(0, std::min(_nodes[id].right, _text_length) - _nodes[id].left);
        }
        return result;
    }
};

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_SUFFIX_TREE_HPP
