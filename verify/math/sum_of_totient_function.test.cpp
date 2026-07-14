#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_totient_function"

#include "../../math/totient_sum.hpp"

#include <cstdint>
#include "../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    std::uint64_t n;
    fast_input >> n;
    constexpr std::uint64_t modulus = 998244353;
    __uint128_t answer = m1une::math::totient_sum(n);
    fast_output << static_cast<std::uint64_t>(answer % modulus) << '\n';
}
