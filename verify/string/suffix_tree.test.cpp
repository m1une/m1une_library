#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include "../../string/suffix_tree.hpp"

#include "../../utilities/fast_io.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace {

void test_features() {
    using Tree = m1une::string::SuffixTree<>;
    Tree empty;
    assert(empty.empty());
    assert(empty.text_length() == 0);
    assert(empty.node_count() == 2);
    assert(empty.count_occurrences(std::string()) == 1);
    assert(empty.distinct_substring_count() == 0);

    std::string text = "ababa";
    Tree tree(text);
    assert(!tree.empty());
    assert(tree.text_length() == 5);
    assert(tree.root() == Tree::root_node);
    assert(tree.node_count() <= 2 * int(text.size()) + 1);
    assert(tree.contains(std::string("bab")));
    assert(!tree.contains(std::string("abb")));
    assert(tree.contains(std::string()));
    assert(tree.count_occurrences(std::string("a")) == 3);
    assert(tree.count_occurrences(std::string("aba")) == 2);
    assert(tree.count_occurrences(std::string("ababa")) == 1);
    assert(tree.count_occurrences(std::string()) == 6);
    assert(tree.distinct_substring_count() == 9);

    auto occurrence = tree.representative_occurrence(std::string("bab"));
    assert(text.substr(occurrence.first, occurrence.second - occurrence.first) == "bab");
    assert((tree.representative_occurrence(std::string("abb")) == std::pair<int, int>(-1, -1)));

    int root_children = 0;
    bool has_terminal_leaf = false;
    tree.for_each_child(tree.root(), [&](int symbol, int child) {
        root_children++;
        assert(tree.node(child).parent == tree.root());
        if (symbol == Tree::terminal_symbol) {
            has_terminal_leaf = true;
            assert(tree.is_leaf(child));
            assert(tree.node(child).suffix_start == int(text.size()));
        }
    });
    assert(root_children == 3);
    assert(has_terminal_leaf);
    assert(tree.child(tree.root(), 'a') != Tree::null_node);
    assert(tree.child_by_index(tree.root(), Tree::terminal_symbol) != Tree::null_node);

    m1une::string::SuffixTree<10, '0'> digits(std::string("012012"));
    assert(digits.contains(std::string("201")));

    tree.clear();
    assert(tree.empty());
    assert(tree.node_count() == 2);
}

void test_randomized() {
    std::uint64_t state = 918273645;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 3000; trial++) {
        int n = int(random() % 55);
        std::string text(n, 'a');
        for (char& character : text) character = char('a' + random() % 4);
        m1une::string::SuffixTree<4, 'a'> tree(text);

        assert(tree.node_count() <= std::max(2, 2 * n + 1));
        assert(tree.node(tree.root()).parent == tree.null_node);
        assert(tree.node(tree.root()).suffix_link == tree.root());

        std::map<std::string, int> expected;
        for (int left = 0; left < n; left++) {
            for (int right = left + 1; right <= n; right++) {
                expected[text.substr(left, right - left)]++;
            }
        }
        assert(tree.distinct_substring_count() == int(expected.size()));
        assert(tree.count_occurrences(std::string()) == n + 1);

        for (const auto& entry : expected) {
            const std::string& substring = entry.first;
            int count = entry.second;
            assert(tree.contains(substring));
            assert(tree.count_occurrences(substring) == count);
            auto [left, right] = tree.representative_occurrence(substring);
            assert(0 <= left && left < right && right <= n);
            assert(text.substr(left, right - left) == substring);
        }

        std::set<int> suffix_starts;
        int leaves = 0;
        for (int id = 0; id < tree.node_count(); id++) {
            const auto& node = tree.node(id);
            assert(0 <= node.left && node.left <= node.right && node.right <= n + 1);
            if (id != tree.root()) {
                assert(0 <= node.parent && node.parent < tree.node_count());
                assert(tree.edge_length(id) > 0);
            }
            if (tree.is_leaf(id)) {
                leaves++;
                assert(0 <= node.suffix_start && node.suffix_start <= n);
                suffix_starts.insert(node.suffix_start);
                assert(node.leaf_count == 1);
            } else {
                assert(node.suffix_start == -1);
                assert(node.leaf_count >= (id == tree.root() ? 1 : 2));
            }

            std::vector<std::pair<int, int>> children;
            tree.for_each_child(id, [&](int symbol, int child) {
                children.emplace_back(symbol, child);
            });
            assert(int(children.size()) == node.child_count);

            int position = 0;
            for (int child = node.first_child; child != tree.null_node; child = tree.node(child).next_sibling) {
                assert(position < int(children.size()));
                assert(tree.node(child).parent == id);
                assert(tree.node(child).incoming_symbol == children[position].first);
                assert(child == children[position].second);
                assert(tree.child_by_index(id, children[position].first) == child);
                position++;
            }
            assert(position == int(children.size()));
            for (int i = 1; i < int(children.size()); i++) {
                assert(children[i - 1].first < children[i].first);
            }
        }
        assert(leaves == n + 1);
        assert(int(suffix_starts.size()) == n + 1);
        for (int start = 0; start <= n; start++) assert(suffix_starts.count(start));

        for (int length = 0; length <= n; length++) {
            std::string suffix = text.substr(n - length);
            assert(tree.contains(suffix));
            assert(tree.count_occurrences(suffix) >= 1);
        }

        int query_length = int(random() % 25);
        std::string query(query_length, 'a');
        for (char& character : query) character = char('a' + random() % 4);
        int naive_count = 0;
        for (int position = 0; position + query_length <= n; position++) {
            if (text.compare(position, query_length, query) == 0) naive_count++;
        }
        if (query.empty()) naive_count = n + 1;
        assert(tree.count_occurrences(query) == naive_count);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_features();
    test_randomized();

    std::string text;
    fast_input >> text;
    m1une::string::SuffixTree<> tree(text);
    fast_output << tree.distinct_substring_count() << '\n';
}
