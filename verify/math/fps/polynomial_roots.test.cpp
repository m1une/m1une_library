#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_root_finding"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <vector>

#include "../../../math/fps/polynomial_roots.hpp"
#include "../../../math/modint.hpp"
#include "../../../utilities/fast_io.hpp"

namespace {

template <class Mint>
using Fps = m1une::fps::FormalPowerSeries<Mint>;

template <class Mint>
Fps<Mint> linear_factor(Mint root) {
    Fps<Mint> result(2);
    result[0] = Mint(0) - root;
    result[1] = Mint(1);
    return result;
}

uint64_t next_random(uint64_t& state) {
    state ^= state << 7;
    state ^= state >> 9;
    return state;
}

void focused_tests() {
    using Mint = m1une::math::modint998244353;
    Fps<Mint> polynomial(1, Mint(7));
    const std::vector<Mint> expected = {Mint(0), Mint(1), Mint(5), Mint(123456)};
    for (int copy = 0; copy < 3; ++copy) polynomial *= linear_factor(expected[0]);
    for (int copy = 0; copy < 2; ++copy) polynomial *= linear_factor(expected[1]);
    polynomial *= linear_factor(expected[2]);
    polynomial *= linear_factor(expected[3]);
    assert(m1une::fps::polynomial_roots(polynomial) == expected);

    Fps<Mint> no_roots(3);
    no_roots[0] = Mint(0) - Mint(3);
    no_roots[2] = Mint(1);
    assert(m1une::fps::polynomial_roots(no_roots).empty());
    assert(m1une::fps::polynomial_roots(Fps<Mint>(1, Mint(11))).empty());

    using BinaryMint = m1une::math::ModInt<2>;
    Fps<BinaryMint> binary(3);
    binary[1] = BinaryMint(1);
    binary[2] = BinaryMint(1);
    const std::vector<BinaryMint> binary_roots =
        m1une::fps::polynomial_roots(binary);
    assert(binary_roots.size() == 2);
    assert(binary_roots[0] == BinaryMint(0));
    assert(binary_roots[1] == BinaryMint(1));

    using SmallMint = m1une::math::ModInt<17>;
    uint64_t random = 0x73c0582af1d946beULL;
    for (int degree = 0; degree <= 10; ++degree) {
        for (int iteration = 0; iteration < 20; ++iteration) {
            Fps<SmallMint> small(degree + 1);
            for (SmallMint& coefficient : small) coefficient = SmallMint(next_random(random));
            if (small.back() == SmallMint(0)) small.back() = SmallMint(1);
            std::vector<SmallMint> brute;
            for (int value = 0; value < 17; ++value) {
                if (small.evaluate(SmallMint(value)) == SmallMint(0)) {
                    brute.push_back(SmallMint(value));
                }
            }
            assert(m1une::fps::polynomial_roots(small) == brute);
        }
    }
}

}  // namespace

int main() {
    using Mint = m1une::math::modint998244353;
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    focused_tests();

    int degree;
    input >> degree;
    Fps<Mint> polynomial(degree + 1);
    for (Mint& coefficient : polynomial) input >> coefficient;
    const std::vector<Mint> roots = m1une::fps::polynomial_roots(polynomial);
    output << roots.size() << '\n';
    output << roots << '\n';
}
