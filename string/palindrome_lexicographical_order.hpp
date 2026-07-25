#ifndef M1UNE_STRING_PALINDROME_LEXICOGRAPHICAL_ORDER_HPP
#define M1UNE_STRING_PALINDROME_LEXICOGRAPHICAL_ORDER_HPP 1

#include <algorithm>
#include <cassert>
#include <string>
#include <utility>
#include <vector>

#include "eertree.hpp"
#include "suffix_array.hpp"

namespace m1une {
namespace string {

// Indexes the distinct nonempty palindromic substrings of one sequence.
template <
    class Sequence = std::string,
    int AlphabetSize = 26,
    int FirstCharacter = 'a'
>
struct PalindromeLexicographicalOrder {
    static_assert(0 < AlphabetSize);

    using eertree_type = Eertree<AlphabetSize, FirstCharacter>;
    using node_id = typename eertree_type::node_id;

   private:
    Sequence _sequence;
    eertree_type _eertree;
    std::vector<node_id> _nodes_in_order;
    std::vector<int> _order_of_node;

    template <class Symbol>
    static int symbol_index(const Symbol& symbol) {
        int index = int(symbol) - FirstCharacter;
        assert(0 <= index && index < AlphabetSize);
        return index;
    }

    void build_order() {
        const int node_count = _eertree.node_count();
        std::vector<std::vector<node_id>> suffix_children(node_count);
        for (node_id id = 0; id < node_count; id++) {
            if (id == eertree_type::odd_root) continue;
            suffix_children[_eertree.node(id).suffix_link].push_back(id);
        }

        std::vector<int> enter(node_count);
        std::vector<int> leave(node_count);
        std::vector<std::pair<node_id, bool>> stack;
        stack.reserve(2 * node_count);
        stack.emplace_back(eertree_type::odd_root, false);
        int timer = 0;
        while (!stack.empty()) {
            auto [id, exiting] = stack.back();
            stack.pop_back();
            if (exiting) {
                leave[id] = timer;
                continue;
            }

            enter[id] = timer++;
            stack.emplace_back(id, true);
            const auto& children = suffix_children[id];
            for (int i = int(children.size()) - 1; i >= 0; i--) {
                stack.emplace_back(children[i], false);
            }
        }

        std::vector<int> suffixes = suffix_array(_sequence);
        std::vector<int> suffix_rank(_sequence.size());
        for (int rank = 0; rank < int(suffixes.size()); rank++) {
            suffix_rank[suffixes[rank]] = rank;
        }

        _nodes_in_order.resize(_eertree.size());
        for (int i = 0; i < _eertree.size(); i++) {
            _nodes_in_order[i] = i + 2;
        }

        auto is_ancestor = [&](node_id ancestor, node_id descendant) {
            return
                enter[ancestor] <= enter[descendant] &&
                leave[descendant] <= leave[ancestor];
        };
        std::sort(
            _nodes_in_order.begin(),
            _nodes_in_order.end(),
            [&](node_id first, node_id second) {
                if (first == second) return false;

                // A palindromic prefix is also a palindromic suffix, so prefix
                // cases are exactly the ancestor cases in the suffix-link tree.
                if (is_ancestor(first, second)) return true;
                if (is_ancestor(second, first)) return false;

                // Otherwise the first mismatch occurs inside both substrings,
                // and the ranks of representative suffixes give their order.
                int first_start = _eertree.first_occurrence(first).first;
                int second_start = _eertree.first_occurrence(second).first;
                return suffix_rank[first_start] < suffix_rank[second_start];
            }
        );

        _order_of_node.assign(node_count, -1);
        for (int order = 0; order < size(); order++) {
            _order_of_node[_nodes_in_order[order]] = order;
        }
    }

   public:
    PalindromeLexicographicalOrder() : _order_of_node(2, -1) {}

    explicit PalindromeLexicographicalOrder(const Sequence& sequence)
        : _sequence(sequence), _eertree(_sequence) {
        build_order();
    }

    explicit PalindromeLexicographicalOrder(Sequence&& sequence)
        : _sequence(std::move(sequence)), _eertree(_sequence) {
        build_order();
    }

    int size() const {
        return int(_nodes_in_order.size());
    }

    bool empty() const {
        return _nodes_in_order.empty();
    }

    int text_length() const {
        return int(_sequence.size());
    }

    const Sequence& sequence() const {
        return _sequence;
    }

    const eertree_type& eertree() const {
        return _eertree;
    }

    const std::vector<node_id>& nodes_in_order() const {
        return _nodes_in_order;
    }

    int order_of_node(node_id id) const {
        assert(2 <= id && id < _eertree.node_count());
        return _order_of_node[id];
    }

    node_id node_by_order(int order) const {
        assert(0 <= order && order < size());
        return _nodes_in_order[order];
    }

    template <class Palindrome>
    node_id find(const Palindrome& palindrome) const {
        const int length = int(palindrome.size());
        if (length == 0) return eertree_type::null_node;
        for (int i = 0; i < length / 2; i++) {
            if (palindrome[i] != palindrome[length - 1 - i]) {
                return eertree_type::null_node;
            }
        }

        node_id id =
            length & 1 ? eertree_type::odd_root : eertree_type::even_root;
        for (int i = (length - 1) / 2; i >= 0; i--) {
            int symbol = symbol_index(palindrome[i]);
            id = _eertree.node(id).next[symbol];
            if (id == eertree_type::null_node) return id;
        }
        return id;
    }

    template <class Palindrome>
    bool contains(const Palindrome& palindrome) const {
        return find(palindrome) != eertree_type::null_node;
    }

    template <class Palindrome>
    int order_of_palindrome(const Palindrome& palindrome) const {
        node_id id = find(palindrome);
        return id == eertree_type::null_node ? -1 : order_of_node(id);
    }

    std::pair<int, int> representative_occurrence(int order) const {
        return _eertree.first_occurrence(node_by_order(order));
    }

    Sequence palindrome(int order) const {
        auto [left, right] = representative_occurrence(order);
        return Sequence(_sequence.begin() + left, _sequence.begin() + right);
    }

    Sequence kth(int order) const {
        return palindrome(order);
    }
};

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_PALINDROME_LEXICOGRAPHICAL_ORDER_HPP
