#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../../../algo/enumeration/submask.hpp"

void test_submasks() {
    std::vector<std::uint32_t> submasks;
    m1une::algo::for_each_submask(std::uint32_t(0b1011), [&](std::uint32_t mask) {
        submasks.push_back(mask);
    });
    std::vector<std::uint32_t> expected = {
        0b1011, 0b1010, 0b1001, 0b1000, 0b0011, 0b0010, 0b0001, 0b0000
    };
    assert(submasks == expected);

    int nonzero_count = 0;
    m1une::algo::for_each_nonzero_submask(std::uint32_t(0b1011), [&](std::uint32_t) {
        ++nonzero_count;
    });
    assert(nonzero_count == 7);
}

void test_supermasks() {
    std::vector<std::uint32_t> supermasks;
    m1une::algo::for_each_supermask(std::uint32_t(0b001), 3, [&](std::uint32_t mask) {
        supermasks.push_back(mask);
    });
    std::sort(supermasks.begin(), supermasks.end());
    std::vector<std::uint32_t> expected = {0b001, 0b011, 0b101, 0b111};
    assert(supermasks == expected);
}

int main() {
    test_submasks();
    test_supermasks();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
