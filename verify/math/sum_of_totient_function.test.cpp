#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_totient_function"

#include "../../math/totient_sum.hpp"

#include <cstdint>
#include <iostream>

int main() {
    std::uint64_t n;
    std::cin >> n;
    constexpr std::uint64_t modulus = 998244353;
    __uint128_t answer = m1une::math::totient_sum(n);
    std::cout << static_cast<std::uint64_t>(answer % modulus) << '\n';
}
