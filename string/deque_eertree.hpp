#ifndef M1UNE_STRING_DEQUE_EERTREE_HPP
#define M1UNE_STRING_DEQUE_EERTREE_HPP 1

#include <array>
#include <cassert>
#include <cstddef>
#include <deque>
#include <limits>
#include <vector>

namespace m1une {
namespace string {

template <int AlphabetSize = 26, int FirstCharacter = 'a'>
struct DequeEertree {
    static_assert(0 < AlphabetSize);

    using node_id = int;
    static constexpr node_id odd_root = 0;
    static constexpr node_id even_root = 1;
    static constexpr node_id null_node = -1;

   private:
    struct Node {
        std::array<node_id, AlphabetSize> next;
        node_id parent;
        node_id suffix_link;
        node_id quick_link;
        int length;
        int surface_count;
        int suffix_link_children;
        bool active;

        Node(
            int length_value = 0,
            node_id parent_value = null_node,
            node_id suffix_link_value = null_node,
            node_id quick_link_value = null_node
        )
            : parent(parent_value),
              suffix_link(suffix_link_value),
              quick_link(quick_link_value),
              length(length_value),
              surface_count(0),
              suffix_link_children(0),
              active(true) {
            next.fill(null_node);
        }
    };

    struct Position {
        int symbol;
        node_id prefix_surface;
        node_id suffix_surface;
    };

    std::vector<Node> _nodes;
    std::deque<Position> _text;
    int _distinct_palindromes;

    template <class Symbol>
    static int symbol_index(const Symbol& value) {
        int symbol = int(value) - FirstCharacter;
        assert(0 <= symbol && symbol < AlphabetSize);
        return symbol;
    }

    node_id new_node(node_id parent, node_id suffix_link, int length, int symbol) {
        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));
        node_id id = int(_nodes.size());
        _nodes.emplace_back(length, parent, suffix_link, odd_root);
        _nodes[parent].next[symbol] = id;
        _nodes[suffix_link].suffix_link_children++;
        _distinct_palindromes++;
        return id;
    }

    void remove_node(node_id id, int symbol) {
        Node& removed = _nodes[id];
        assert(removed.active);
        assert(removed.surface_count == 0);
        assert(removed.suffix_link_children == 0);
        assert(_nodes[removed.parent].next[symbol] == id);
        _nodes[removed.parent].next[symbol] = null_node;
        _nodes[removed.suffix_link].suffix_link_children--;
        removed.active = false;
        _distinct_palindromes--;
    }

    node_id back_appendable(int symbol, node_id node) const {
        int n = int(_text.size());
        while (true) {
            int length = _nodes[node].length;
            if (length == -1 || (length < n && _text[n - length - 1].symbol == symbol)) {
                return node;
            }
            node_id suffix = _nodes[node].suffix_link;
            int suffix_length = _nodes[suffix].length;
            if (suffix_length == -1 || _text[n - suffix_length - 1].symbol == symbol) {
                return suffix;
            }
            node = _nodes[node].quick_link;
        }
    }

    node_id front_appendable(int symbol, node_id node) const {
        int n = int(_text.size());
        while (true) {
            int length = _nodes[node].length;
            if (length == -1 || (length < n && _text[length].symbol == symbol)) {
                return node;
            }
            node_id suffix = _nodes[node].suffix_link;
            int suffix_length = _nodes[suffix].length;
            if (suffix_length == -1 || _text[suffix_length].symbol == symbol) {
                return suffix;
            }
            node = _nodes[node].quick_link;
        }
    }

    node_id prefix_node() const {
        return _text.empty() ? even_root : _text.front().prefix_surface;
    }

    node_id suffix_node() const {
        return _text.empty() ? even_root : _text.back().suffix_surface;
    }

    void initialize_roots() {
        _nodes.clear();
        _nodes.emplace_back(-1, odd_root, odd_root, odd_root);
        _nodes.emplace_back(0, odd_root, odd_root, odd_root);
        _distinct_palindromes = 0;
    }

   public:
    DequeEertree() {
        initialize_roots();
    }

    template <class Sequence>
    explicit DequeEertree(const Sequence& sequence) {
        initialize_roots();
        build(sequence);
    }

    int size() const {
        return _distinct_palindromes;
    }

    int text_length() const {
        return int(_text.size());
    }

    bool empty() const {
        return _text.empty();
    }

    int distinct_palindrome_count() const {
        return _distinct_palindromes;
    }

    int longest_prefix_length() const {
        return _nodes[prefix_node()].length;
    }

    int longest_suffix_length() const {
        return _nodes[suffix_node()].length;
    }

    void reserve(std::size_t operation_capacity) {
        _nodes.reserve(operation_capacity + 2);
    }

    void clear() {
        _text.clear();
        initialize_roots();
    }

    template <class Symbol>
    void push_back(const Symbol& value) {
        int symbol = symbol_index(value);
        node_id parent = _text.empty() ? odd_root : back_appendable(symbol, suffix_node());
        node_id palindrome = _nodes[parent].next[symbol];
        node_id suffix = even_root;

        if (palindrome == null_node) {
            if (parent != odd_root) {
                node_id suffix_parent = back_appendable(symbol, _nodes[parent].suffix_link);
                suffix = _nodes[suffix_parent].next[symbol];
                assert(suffix != null_node);
            }
        } else {
            suffix = _nodes[palindrome].suffix_link;
        }

        _text.push_back(Position{symbol, even_root, even_root});
        int n = int(_text.size());
        if (palindrome == null_node) {
            palindrome = new_node(parent, suffix, _nodes[parent].length + 2, symbol);

            Node& created = _nodes[palindrome];
            if (
                _nodes[suffix].suffix_link != odd_root &&
                _text[n - _nodes[suffix].length - 1].symbol ==
                    _text[n - _nodes[_nodes[suffix].suffix_link].length - 1].symbol
            ) {
                created.quick_link = _nodes[suffix].quick_link;
            } else {
                created.quick_link = _nodes[suffix].suffix_link;
            }
        }

        int left = n - _nodes[palindrome].length;
        _text.back().suffix_surface = palindrome;
        _text[left].prefix_surface = palindrome;
        if (
            _nodes[suffix].length >= 1 &&
            _text[left + _nodes[suffix].length - 1].suffix_surface == suffix
        ) {
            _text[left + _nodes[suffix].length - 1].suffix_surface = even_root;
        }
        _nodes[palindrome].surface_count++;
    }

    template <class Symbol>
    void push_front(const Symbol& value) {
        int symbol = symbol_index(value);
        node_id parent = _text.empty() ? odd_root : front_appendable(symbol, prefix_node());
        node_id palindrome = _nodes[parent].next[symbol];
        node_id suffix = even_root;

        if (palindrome == null_node) {
            if (parent != odd_root) {
                node_id suffix_parent = front_appendable(symbol, _nodes[parent].suffix_link);
                suffix = _nodes[suffix_parent].next[symbol];
                assert(suffix != null_node);
            }
        } else {
            suffix = _nodes[palindrome].suffix_link;
        }

        _text.push_front(Position{symbol, even_root, even_root});
        if (palindrome == null_node) {
            palindrome = new_node(parent, suffix, _nodes[parent].length + 2, symbol);

            Node& created = _nodes[palindrome];
            if (
                _nodes[suffix].suffix_link != odd_root &&
                _text[_nodes[suffix].length].symbol ==
                    _text[_nodes[_nodes[suffix].suffix_link].length].symbol
            ) {
                created.quick_link = _nodes[suffix].quick_link;
            } else {
                created.quick_link = _nodes[suffix].suffix_link;
            }
        }

        _text.front().prefix_surface = palindrome;
        _text[_nodes[palindrome].length - 1].suffix_surface = palindrome;
        if (
            _nodes[suffix].length >= 1 &&
            _text[_nodes[palindrome].length - _nodes[suffix].length].prefix_surface == suffix
        ) {
            _text[_nodes[palindrome].length - _nodes[suffix].length].prefix_surface = even_root;
        }
        _nodes[palindrome].surface_count++;
    }

    void pop_back() {
        assert(!_text.empty());
        node_id palindrome = suffix_node();
        node_id suffix = _nodes[palindrome].suffix_link;
        int left = text_length() - _nodes[palindrome].length;
        int suffix_end = left + _nodes[suffix].length - 1;

        if (
            _nodes[palindrome].length >= 2 &&
            _nodes[_text[suffix_end].suffix_surface].length < _nodes[suffix].length
        ) {
            _text[suffix_end].suffix_surface = suffix;
            _text[left].prefix_surface = suffix;
        } else {
            _text[left].prefix_surface = even_root;
        }

        _nodes[palindrome].surface_count--;
        int symbol = _text.back().symbol;
        if (
            _nodes[palindrome].surface_count == 0 &&
            _nodes[palindrome].suffix_link_children == 0
        ) {
            remove_node(palindrome, symbol);
        }
        _text.pop_back();
    }

    void pop_front() {
        assert(!_text.empty());
        node_id palindrome = prefix_node();
        node_id suffix = _nodes[palindrome].suffix_link;
        int suffix_start = _nodes[palindrome].length - _nodes[suffix].length;

        if (
            _nodes[palindrome].length >= 2 &&
            _nodes[_text[suffix_start].prefix_surface].length < _nodes[suffix].length
        ) {
            _text[suffix_start].prefix_surface = suffix;
            _text[_nodes[palindrome].length - 1].suffix_surface = suffix;
        } else {
            _text[_nodes[palindrome].length - 1].suffix_surface = even_root;
        }

        _nodes[palindrome].surface_count--;
        int symbol = _text.front().symbol;
        if (
            _nodes[palindrome].surface_count == 0 &&
            _nodes[palindrome].suffix_link_children == 0
        ) {
            remove_node(palindrome, symbol);
        }
        _text.pop_front();
    }

    template <class Sequence>
    void build(const Sequence& sequence) {
        for (const auto& symbol : sequence) push_back(symbol);
    }
};

template <int AlphabetSize = 26, int FirstCharacter = 'a'>
using DoubleEndedEertree = DequeEertree<AlphabetSize, FirstCharacter>;

template <int AlphabetSize = 26, int FirstCharacter = 'a'>
using DequePalindromicTree = DequeEertree<AlphabetSize, FirstCharacter>;

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_DEQUE_EERTREE_HPP
