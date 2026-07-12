#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../string/minimum_rotation.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace {

template <class Sequence>
bool rotation_less(
    const Sequence& sequence,
    int first,
    int second
) {
    const int size = int(sequence.size());
    for (int offset = 0; offset < size; offset++) {
        const auto& left = sequence[(first + offset) % size];
        const auto& right = sequence[(second + offset) % size];
        if (left < right) return true;
        if (right < left) return false;
    }
    return false;
}

template <class Sequence>
int naive_minimum_cyclic_shift(const Sequence& sequence) {
    if (sequence.empty()) return 0;
    int answer = 0;
    for (int start = 1; start < int(sequence.size()); start++) {
        if (rotation_less(sequence, start, answer)) answer = start;
    }
    return answer;
}

void test_edge_cases() {
    assert(m1une::string::minimum_cyclic_shift(std::string()) == 0);
    assert(m1une::string::minimum_cyclic_shift(std::string("a")) == 0);
    assert(m1une::string::minimum_cyclic_shift(std::string("aaaa")) == 0);
    assert(m1une::string::minimum_cyclic_shift(std::string("abab")) == 0);
    assert(m1une::string::minimum_cyclic_shift(std::string("banana")) == 5);
    assert(m1une::string::minimum_cyclic_shift(std::string("baca")) == 3);

    std::vector<int> values{2, 1, 3, 1};
    assert(m1une::string::minimum_cyclic_shift(values) == 3);
}

void test_exhaustive() {
    for (int size = 0; size <= 9; size++) {
        std::uint64_t count = 1;
        for (int index = 0; index < size; index++) count *= 3;
        for (std::uint64_t code = 0; code < count; code++) {
            std::uint64_t value = code;
            std::string text(static_cast<std::size_t>(size), 'a');
            for (char& character : text) {
                character = char('a' + value % 3);
                value /= 3;
            }
            assert(
                m1une::string::minimum_cyclic_shift(text) ==
                naive_minimum_cyclic_shift(text)
            );
        }
    }
}

void test_randomized() {
    std::uint64_t state = 0x816f3ac924b75de0ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 5000; trial++) {
        const int size = int(random() % 50);
        std::vector<int> sequence(static_cast<std::size_t>(size));
        for (int& value : sequence) value = int(random() % 7);
        assert(
            m1une::string::minimum_cyclic_shift(sequence) ==
            naive_minimum_cyclic_shift(sequence)
        );
    }
}

}  // namespace

int main() {
    test_edge_cases();
    test_exhaustive();
    test_randomized();

    long long first, second;
    std::cin >> first >> second;
    std::cout << first + second << '\n';
}
