#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C"

#include "../../string/map_trie.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace {

using Sequence = std::vector<int>;

void test_features() {
    using Trie = m1une::string::MapTrie<int>;
    Trie trie;
    assert(trie.empty());
    assert(trie.node_count() == 1);
    trie.reserve(128);

    Sequence empty;
    Sequence first;
    first.push_back(1000000000);
    first.push_back(-7);
    Sequence longer = first;
    longer.push_back(42);
    Sequence other;
    other.push_back(-1000000000);

    const auto empty_node = trie.insert(empty);
    const auto first_node = trie.insert(first, 2);
    trie.insert(longer);
    trie.insert(other);

    assert(empty_node == trie.root());
    assert(first_node == trie.find(first));
    Sequence absent;
    absent.push_back(5);
    assert(trie.find(absent) == Trie::null_node);
    assert(trie.node(trie.root()).subtree_count == 5);
    assert(trie.node(first_node).terminal_count == 2);
    assert(trie.node(first_node).subtree_count == 3);
    auto root_edge = trie.node(trie.root()).child.find(1000000000);
    assert(root_edge != trie.node(trie.root()).child.end());
    assert(trie.node(root_edge->second).subtree_count == 3);
    assert(trie.size() == 5);
    assert(trie.distinct_size() == 4);
    assert(trie.count(first) == 2);
    assert(trie.prefix_count(first) == 3);
    assert(trie.prefix_count(empty) == 5);
    assert(trie.starts_with(longer));
    assert(!trie.starts_with(absent));
    assert(trie.longest_prefix(longer) == 3);
    assert(trie.longest_prefix(absent) == 0);

    std::vector<std::pair<int, int>> prefixes;
    trie.for_each_prefix(longer, [&prefixes](int length, int count) {
        prefixes.emplace_back(length, count);
    });
    std::vector<std::pair<int, int>> expected;
    expected.emplace_back(0, 1);
    expected.emplace_back(2, 2);
    expected.emplace_back(3, 1);
    assert(prefixes == expected);

    assert(trie.erase_one(first));
    assert(trie.count(first) == 1);
    assert(trie.erase_all(first) == 1);
    assert(!trie.contains(first));
    assert(!trie.erase(first));
    assert(trie.distinct_size() == 3);

    m1une::string::MapTrie<std::string> token_trie;
    std::vector<std::string> tokens;
    tokens.push_back("large alphabet");
    tokens.push_back("token");
    token_trie.insert(tokens);
    assert(token_trie.contains(tokens));

    m1une::string::MapTrie<int, std::greater<int>> descending_trie;
    descending_trie.insert(longer);
    assert(descending_trie.contains(longer));

    Trie reusable_trie;
    reusable_trie.insert(longer);
    std::size_t allocated = reusable_trie.node_count();
    assert(reusable_trie.erase_all(longer) == 1);
    assert(reusable_trie.find(longer) == Trie::null_node);
    reusable_trie.insert(longer);
    assert(reusable_trie.contains(longer));
    assert(reusable_trie.node_count() == allocated);
}

void test_randomized() {
    std::uint64_t state = 73;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    m1une::string::MapTrie<int> trie;
    std::map<Sequence, int> expected;

    for (int step = 0; step < 10000; step++) {
        int length = int(random() % 9);
        Sequence sequence(length);
        for (int& symbol : sequence) {
            symbol = int(random() % 2000000001ULL) - 1000000000;
        }
        if (random() % 2 == 0 && !sequence.empty()) {
            sequence.back() = int(random() % 5) - 2;
        }
        int type = int(random() % 6);

        if (type == 0) {
            int multiplicity = int(random() % 3) + 1;
            trie.insert(sequence, multiplicity);
            expected[sequence] += multiplicity;
        } else if (type == 1) {
            [[maybe_unused]] bool erased = trie.erase_one(sequence);
            bool expected_erased = expected[sequence] != 0;
            assert(erased == expected_erased);
            if (expected_erased) expected[sequence]--;
        } else if (type == 2) {
            [[maybe_unused]] int erased = trie.erase_all(sequence);
            assert(erased == expected[sequence]);
            expected[sequence] = 0;
        } else {
            assert(trie.count(sequence) == expected[sequence]);
            [[maybe_unused]] int prefix_count = 0;
            for (const auto& entry : expected) {
                if (
                    entry.first.size() >= sequence.size() &&
                    std::equal(sequence.begin(), sequence.end(), entry.first.begin())
                ) {
                    prefix_count += entry.second;
                }
            }
            assert(trie.prefix_count(sequence) == prefix_count);

            int longest = -1;
            for (const auto& entry : expected) {
                if (
                    entry.second != 0 &&
                    entry.first.size() <= sequence.size() &&
                    std::equal(entry.first.begin(), entry.first.end(), sequence.begin())
                ) {
                    longest = std::max(longest, int(entry.first.size()));
                }
            }
            assert(trie.longest_prefix(sequence) == longest);
        }

        [[maybe_unused]] int size = 0;
        [[maybe_unused]] int distinct = 0;
        for (const auto& entry : expected) {
            size += entry.second;
            if (entry.second != 0) distinct++;
        }
        assert(trie.size() == size);
        assert(trie.distinct_size() == distinct);
    }

    trie.clear();
    assert(trie.empty());
    assert(trie.distinct_size() == 0);
    assert(trie.node_count() == 1);
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_features();
    test_randomized();

    int q;
    fast_input >> q;
    m1une::string::MapTrie<char> trie;
    while (q--) {
        std::string command;
        std::string word;
        fast_input >> command >> word;
        if (command == "insert") {
            trie.insert(word);
        } else {
            fast_output << (trie.contains(word) ? "yes" : "no") << '\n';
        }
    }
}
