#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <vector>

#include "../../../algo/offline/parallel_binary_search.hpp"

void test_parallel_binary_search() {
    std::vector<int> add = {3, 1, 4};
    std::vector<int> need = {0, 3, 4, 8, 9};
    int current = 0;

    std::vector<int> answer = m1une::algo::parallel_binary_search(
        int(need.size()),
        int(add.size()),
        [&](int event) {
            current += add[event];
        },
        [&](int query) {
            return need[query] <= current;
        },
        [&]() {
            current = 0;
        }
    );

    std::vector<int> expected = {0, 1, 2, 3, 4};
    assert(answer == expected);
}

int main() {
    test_parallel_binary_search();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
