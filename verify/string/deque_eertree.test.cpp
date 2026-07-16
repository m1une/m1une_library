#define PROBLEM "https://judge.yosupo.jp/problem/palindromes_in_deque"

#include "../../string/deque_eertree.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <deque>
#include <set>
#include <string>
#include "../../utilities/fast_io.hpp"

namespace {

struct NaiveResult {
    int distinct;
    int longest_prefix;
    int longest_suffix;
};

bool is_palindrome(const std::string& text, int left, int right) {
    while (left < right) {
        right--;
        if (text[left] != text[right]) return false;
        left++;
    }
    return true;
}

NaiveResult solve_naively(const std::deque<char>& sequence) {
    std::string text(sequence.begin(), sequence.end());
    std::set<std::string> distinct;
    int longest_prefix = 0;
    int longest_suffix = 0;
    for (int left = 0; left < int(text.size()); left++) {
        for (int right = left + 1; right <= int(text.size()); right++) {
            if (!is_palindrome(text, left, right)) continue;
            distinct.insert(text.substr(left, right - left));
            if (left == 0) longest_prefix = std::max(longest_prefix, right);
            if (right == int(text.size())) longest_suffix = std::max(longest_suffix, right - left);
        }
    }
    return {int(distinct.size()), longest_prefix, longest_suffix};
}

void check(
    const m1une::string::DequeEertree<4, 'a'>& tree,
    const std::deque<char>& sequence
) {
    NaiveResult expected = solve_naively(sequence);
    assert(tree.size() == expected.distinct);
    assert(tree.text_length() == int(sequence.size()));
    assert(tree.empty() == sequence.empty());
    assert(tree.distinct_palindrome_count() == expected.distinct);
    assert(tree.longest_prefix_length() == expected.longest_prefix);
    assert(tree.longest_suffix_length() == expected.longest_suffix);
}

void test_features() {
    m1une::string::DequeEertree<4, 'a'> tree;
    tree.reserve(32);
    std::deque<char> sequence;
    check(tree, sequence);

    tree.push_back('a');
    sequence.push_back('a');
    tree.push_back('b');
    sequence.push_back('b');
    tree.push_front('b');
    sequence.push_front('b');
    check(tree, sequence);

    tree.pop_back();
    sequence.pop_back();
    check(tree, sequence);
    tree.clear();
    sequence.clear();
    check(tree, sequence);

    m1une::string::DoubleEndedEertree<4, 'a'> built(std::string("abacaba"));
    assert(built.text_length() == 7);
    assert(built.size() == 7);
    assert(built.distinct_palindrome_count() == 7);
    assert(built.longest_prefix_length() == 7);
    assert(built.longest_suffix_length() == 7);
}

void test_randomized() {
    std::uint64_t state = 817;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1500; trial++) {
        m1une::string::DequeEertree<4, 'a'> tree;
        tree.reserve(120);
        std::deque<char> sequence;
        for (int operation = 0; operation < 120; operation++) {
            int type = sequence.empty() ? int(random() % 2) : int(random() % 4);
            char symbol = char('a' + random() % 4);
            if (type == 0) {
                tree.push_front(symbol);
                sequence.push_front(symbol);
            } else if (type == 1) {
                tree.push_back(symbol);
                sequence.push_back(symbol);
            } else if (type == 2) {
                tree.pop_front();
                sequence.pop_front();
            } else {
                tree.pop_back();
                sequence.pop_back();
            }
            check(tree, sequence);
        }
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_features();
    test_randomized();

    int query_count;
    fast_input >> query_count;
    m1une::string::DequeEertree<> tree;
    tree.reserve(query_count);
    for (int query = 0; query < query_count; query++) {
        int type;
        fast_input >> type;
        if (type == 0) {
            char symbol;
            fast_input >> symbol;
            tree.push_front(symbol);
        } else if (type == 1) {
            char symbol;
            fast_input >> symbol;
            tree.push_back(symbol);
        } else if (type == 2) {
            tree.pop_front();
        } else {
            assert(type == 3);
            tree.pop_back();
        }
        fast_output << tree.distinct_palindrome_count() << ' '
                    << tree.longest_prefix_length() << ' '
                    << tree.longest_suffix_length() << '\n';
    }
}
