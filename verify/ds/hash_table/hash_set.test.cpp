#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C"

#include "../../../ds/hash_table/hash_set.hpp"

#include <cassert>
#include "../../../utilities/fast_io.hpp"
#include <string>
#include <unordered_set>
#include <vector>

void self_test() {
    m1une::ds::HashSet<long long> st;
    assert(st.empty());
    assert(st.insert(5));
    assert(!st.insert(5));
    assert(st.insert(1));
    assert(st.contains(5));
    assert(st.count(1) == 1);
    assert(st.erase(5));
    assert(!st.contains(5));
    assert(!st.erase(5));

    std::vector<long long> xs;
    for (int i = 0; i < 1000; i++) xs.push_back(i * 1000000007LL);
    m1une::ds::HashSet<long long> large(xs.begin(), xs.end());
    for (long long x : xs) assert(large.contains(x));
    for (int i = 0; i < 500; i++) assert(large.erase(xs[i]));
    for (int i = 0; i < 500; i++) assert(!large.contains(xs[i]));
    for (int i = 500; i < 1000; i++) assert(large.contains(xs[i]));
    auto copied_large = large;
    auto moved_large = std::move(copied_large);
    for (int i = 500; i < 1000; i++) assert(moved_large.contains(xs[i]));

    m1une::ds::HashSet<int> tested;
    std::unordered_set<int> expected;
    unsigned long long seed = 123456789;
    for (int q = 0; q < 10000; q++) {
        seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;
        int x = static_cast<int>((seed >> 32) % 400) - 200;
        int type = static_cast<int>(seed % 4);
        if (type == 0) {
            assert(tested.insert(x) == (expected.insert(x).second));
        } else if (type == 1) {
            assert(tested.erase(x) == (expected.erase(x) == 1));
        } else {
            assert(tested.contains(x) == (expected.find(x) != expected.end()));
            assert(tested.count(x) == static_cast<int>(expected.count(x)));
        }
        assert(tested.size() == static_cast<int>(expected.size()));
    }
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    self_test();
    int n;
    fast_input >> n;
    m1une::ds::HashSet<std::string> dictionary;
    while (n--) {
        std::string command, word;
        fast_input >> command >> word;
        if (command == "insert") {
            dictionary.insert(word);
        } else {
            fast_output << (dictionary.contains(word) ? "yes" : "no") << '\n';
        }
    }
}
