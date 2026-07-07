#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <vector>

#include "../../../algo/offline/cdq_divide_and_conquer.hpp"

long long naive_inversion_count(const std::vector<int>& a) {
    long long result = 0;
    for (int i = 0; i < int(a.size()); ++i) {
        for (int j = i + 1; j < int(a.size()); ++j) {
            if (a[j] < a[i]) ++result;
        }
    }
    return result;
}

long long cdq_inversion_count(const std::vector<int>& a) {
    long long result = 0;
    m1une::algo::cdq_divide_and_conquer(int(a.size()), [&](int left, int middle, int right) {
        for (int i = left; i < middle; ++i) {
            for (int j = middle; j < right; ++j) {
                if (a[j] < a[i]) ++result;
            }
        }
    });
    return result;
}

void test_cdq_divide_and_conquer() {
    for (int n = 0; n <= 8; ++n) {
        std::vector<int> a(n);
        for (int seed = 0; seed < 100; ++seed) {
            for (int i = 0; i < n; ++i) {
                a[i] = (seed * 17 + i * i * 5 + i) % 7;
            }
            assert(cdq_inversion_count(a) == naive_inversion_count(a));
        }
    }
}

int main() {
    test_cdq_divide_and_conquer();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
