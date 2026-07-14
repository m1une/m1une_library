#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include "../../../utilities/fast_io.hpp"
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
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_parallel_binary_search();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
