#define PROBLEM "https://judge.yosupo.jp/problem/eertree"

#include "../../string/palindrome_lexicographical_order.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <set>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace {

template <class Sequence>
bool is_palindrome(const Sequence& sequence, int left, int right) {
    while (left < right) {
        right--;
        if (sequence[left] != sequence[right]) return false;
        left++;
    }
    return true;
}

template <class Sequence>
std::vector<Sequence> naive_palindromes(const Sequence& sequence) {
    std::set<Sequence> distinct;
    int n = int(sequence.size());
    for (int left = 0; left < n; left++) {
        for (int right = left + 1; right <= n; right++) {
            if (!is_palindrome(sequence, left, right)) continue;
            distinct.emplace(sequence.begin() + left, sequence.begin() + right);
        }
    }
    return std::vector<Sequence>(distinct.begin(), distinct.end());
}

template <class Index>
void check_index(const Index& index) {
    using Tree = typename Index::eertree_type;
    using Sequence = std::remove_cvref_t<decltype(index.sequence())>;

    std::vector<Sequence> expected = naive_palindromes(index.sequence());
    assert(index.size() == int(expected.size()));
    assert(index.empty() == expected.empty());
    assert(index.text_length() == int(index.sequence().size()));
    assert(index.eertree().size() == index.size());
    assert(int(index.nodes_in_order().size()) == index.size());

    for (int order = 0; order < index.size(); order++) {
        const Sequence& palindrome = expected[order];
        int id = index.node_by_order(order);
        assert(index.nodes_in_order()[order] == id);
        assert(index.order_of_node(id) == order);
        assert(index.find(palindrome) == id);
        assert(index.contains(palindrome));
        assert(index.order_of_palindrome(palindrome) == order);
        assert(index.palindrome(order) == palindrome);
        assert(index.kth(order) == palindrome);

        auto [left, right] = index.representative_occurrence(order);
        assert(0 <= left && left < right);
        assert(right <= index.text_length());
        assert(
            Sequence(
                index.sequence().begin() + left,
                index.sequence().begin() + right
            ) == palindrome
        );
    }

    Sequence empty;
    assert(index.find(empty) == Tree::null_node);
    assert(!index.contains(empty));
    assert(index.order_of_palindrome(empty) == -1);
}

void fixed_tests() {
    using Index = m1une::string::PalindromeLexicographicalOrder<>;
    Index empty;
    check_index(empty);

    Index index(std::string("abacaba"));
    check_index(index);
    std::vector<std::string> expected = {
        "a", "aba", "abacaba", "aca", "b", "bacab", "c"
    };
    assert(naive_palindromes(index.sequence()) == expected);
    assert(index.order_of_palindrome(std::string("aca")) == 3);
    assert(index.order_of_palindrome(std::string("aa")) == -1);
    assert(index.order_of_palindrome(std::string("abc")) == -1);
    assert(!index.contains(std::string("aa")));
    assert(!index.contains(std::string("abc")));

    Index moved(std::string("aaaaa"));
    check_index(moved);
    for (int length = 1; length <= 5; length++) {
        assert(moved.palindrome(length - 1) == std::string(length, 'a'));
    }

    using IntegerIndex =
        m1une::string::PalindromeLexicographicalOrder<std::vector<int>, 4, 0>;
    std::vector<int> values;
    values.push_back(2);
    values.push_back(1);
    values.push_back(2);
    values.push_back(0);
    values.push_back(2);
    values.push_back(1);
    values.push_back(2);
    IntegerIndex integer_index(values);
    check_index(integer_index);
}

void exhaustive_tests() {
    for (int length = 0; length <= 8; length++) {
        std::uint64_t count = 1;
        for (int i = 0; i < length; i++) count *= 3;
        for (std::uint64_t code = 0; code < count; code++) {
            std::uint64_t value = code;
            std::string text(length, 'a');
            for (char& character : text) {
                character = char('a' + value % 3);
                value /= 3;
            }
            check_index(
                m1une::string::PalindromeLexicographicalOrder<
                    std::string, 3, 'a'
                >(std::move(text))
            );
        }
    }
}

void randomized_tests() {
    std::uint64_t state = 0xf4c3182d9ab760e5ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1000; trial++) {
        int length = int(random() % 45);
        std::string text(length, 'a');
        for (char& character : text) {
            character = char('a' + random() % 4);
        }
        check_index(
            m1une::string::PalindromeLexicographicalOrder<
                std::string, 4, 'a'
            >(std::move(text))
        );
    }
}

int library_checker_id(int id) {
    using Tree = m1une::string::Eertree<>;
    if (id == Tree::odd_root) return 0;
    if (id == Tree::even_root) return 1;
    return id;
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    fixed_tests();
    exhaustive_tests();
    randomized_tests();

    std::string text;
    fast_input >> text;
    m1une::string::PalindromeLexicographicalOrder<> index(std::move(text));
    const auto& tree = index.eertree();

    std::vector<int> parent(tree.node_count(), -1);
    for (int id = 0; id < tree.node_count(); id++) {
        const auto& node = tree.node(id);
        for (int symbol = 0; symbol < 26; symbol++) {
            int to = node.next[symbol];
            if (to != m1une::string::Eertree<>::null_node) parent[to] = id;
        }
    }

    fast_output << tree.size() << '\n';
    for (int id = 2; id < tree.node_count(); id++) {
        fast_output << library_checker_id(parent[id]) - 1 << ' '
                    << library_checker_id(tree.node(id).suffix_link) - 1
                    << '\n';
    }
    const auto& longest_suffix = tree.longest_suffix_nodes();
    for (int i = 0; i < int(longest_suffix.size()); i++) {
        if (i) fast_output << ' ';
        fast_output << longest_suffix[i] - 1;
    }
    fast_output << '\n';
}
