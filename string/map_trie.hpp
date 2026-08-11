#ifndef M1UNE_STRING_MAP_TRIE_HPP
#define M1UNE_STRING_MAP_TRIE_HPP 1

#include <cassert>
#include <cstddef>
#include <functional>
#include <limits>
#include <map>
#include <vector>

namespace m1une {
namespace string {

// A multiset trie whose outgoing edges are stored in ordered maps.
template <class Symbol, class Compare = std::less<Symbol>>
struct MapTrie {
    using node_id = int;
    static constexpr node_id null_node = -1;

    struct Node {
        std::map<Symbol, node_id, Compare> child;
        int subtree_count = 0;
        int terminal_count = 0;
    };

   private:
    std::vector<Node> _nodes;
    int _distinct_size;

    node_id new_node() {
        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));
        _nodes.emplace_back();
        return int(_nodes.size()) - 1;
    }

    template <class Sequence>
    node_id find_node(const Sequence& sequence) const {
        node_id node = 0;
        for (const auto& symbol : sequence) {
            auto iterator = _nodes[node].child.find(symbol);
            if (iterator == _nodes[node].child.end()) return null_node;
            node = iterator->second;
            if (_nodes[node].subtree_count == 0) return null_node;
        }
        return node;
    }

   public:
    MapTrie() : _nodes(1), _distinct_size(0) {}

    int size() const {
        return _nodes[0].subtree_count;
    }

    int distinct_size() const {
        return _distinct_size;
    }

    bool empty() const {
        return size() == 0;
    }

    node_id root() const {
        return 0;
    }

    const Node& node(node_id id) const {
        assert(0 <= id && std::size_t(id) < _nodes.size());
        return _nodes[id];
    }

    template <class Sequence>
    node_id find(const Sequence& sequence) const {
        return find_node(sequence);
    }

    std::size_t node_count() const {
        return _nodes.size();
    }

    void reserve(std::size_t node_capacity) {
        _nodes.reserve(node_capacity);
    }

    void clear() {
        _nodes.clear();
        _nodes.emplace_back();
        _distinct_size = 0;
    }

    template <class Sequence>
    node_id insert(const Sequence& sequence, int multiplicity = 1) {
        assert(0 < multiplicity);
        node_id node = 0;
        _nodes[node].subtree_count += multiplicity;
        for (const auto& symbol : sequence) {
            auto iterator = _nodes[node].child.find(symbol);
            node_id child;
            if (iterator == _nodes[node].child.end()) {
                child = new_node();
                _nodes[node].child.emplace(symbol, child);
            } else {
                child = iterator->second;
            }
            node = child;
            _nodes[node].subtree_count += multiplicity;
        }
        if (_nodes[node].terminal_count == 0) _distinct_size++;
        _nodes[node].terminal_count += multiplicity;
        return node;
    }

    template <class Sequence>
    int count(const Sequence& sequence) const {
        node_id node = find_node(sequence);
        return node == null_node ? 0 : _nodes[node].terminal_count;
    }

    template <class Sequence>
    bool contains(const Sequence& sequence) const {
        return count(sequence) != 0;
    }

    // Returns the number of stored sequences beginning with prefix.
    template <class Sequence>
    int prefix_count(const Sequence& prefix) const {
        node_id node = find_node(prefix);
        return node == null_node ? 0 : _nodes[node].subtree_count;
    }

    template <class Sequence>
    bool starts_with(const Sequence& prefix) const {
        return prefix_count(prefix) != 0;
    }

    template <class Sequence>
    bool erase_one(const Sequence& sequence) {
        node_id terminal = find_node(sequence);
        if (terminal == null_node || _nodes[terminal].terminal_count == 0) {
            return false;
        }

        node_id node = 0;
        _nodes[node].subtree_count--;
        for (const auto& symbol : sequence) {
            node = _nodes[node].child.find(symbol)->second;
            _nodes[node].subtree_count--;
        }
        _nodes[node].terminal_count--;
        if (_nodes[node].terminal_count == 0) _distinct_size--;
        return true;
    }

    template <class Sequence>
    bool erase(const Sequence& sequence) {
        return erase_one(sequence);
    }

    template <class Sequence>
    int erase_all(const Sequence& sequence) {
        int multiplicity = count(sequence);
        if (multiplicity == 0) return 0;

        node_id node = 0;
        _nodes[node].subtree_count -= multiplicity;
        for (const auto& symbol : sequence) {
            node = _nodes[node].child.find(symbol)->second;
            _nodes[node].subtree_count -= multiplicity;
        }
        _nodes[node].terminal_count = 0;
        _distinct_size--;
        return multiplicity;
    }

    // Calls callback(length, multiplicity) for every stored prefix.
    // The empty prefix is reported with length 0 when it is stored.
    template <class Sequence, class Callback>
    void for_each_prefix(const Sequence& sequence, Callback callback) const {
        node_id node = 0;
        if (_nodes[node].terminal_count != 0) {
            callback(0, _nodes[node].terminal_count);
        }

        int length = 0;
        for (const auto& symbol : sequence) {
            auto iterator = _nodes[node].child.find(symbol);
            if (iterator == _nodes[node].child.end()) return;
            node = iterator->second;
            if (_nodes[node].subtree_count == 0) return;
            length++;
            if (_nodes[node].terminal_count != 0) {
                callback(length, _nodes[node].terminal_count);
            }
        }
    }

    // Returns the length of the longest stored sequence that is a prefix.
    // Returns -1 when no stored prefix exists.
    template <class Sequence>
    int longest_prefix(const Sequence& sequence) const {
        int result = _nodes[0].terminal_count == 0 ? -1 : 0;
        for_each_prefix(sequence, [&result](int length, int) {
            result = length;
        });
        return result;
    }
};

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_MAP_TRIE_HPP
