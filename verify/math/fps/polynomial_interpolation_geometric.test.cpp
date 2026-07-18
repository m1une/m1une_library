#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation_on_geometric_sequence"

#include <cassert>
#include <cstdint>
#include <vector>

#include "../../../math/fps/geometric_sequence_evaluation.hpp"
#include "../../../math/modint.hpp"
#include "../../../utilities/fast_io.hpp"

namespace {

using Mint = m1une::math::modint998244353;
using Fps = m1une::fps::FormalPowerSeries<Mint>;

uint64_t next_random(uint64_t& state) {
    state ^= state << 7;
    state ^= state >> 9;
    return state;
}

void check_interpolation(const Fps& polynomial, Mint initial, Mint ratio) {
    const std::vector<Mint> values = m1une::fps::multipoint_evaluate_geometric(
        polynomial, initial, ratio, polynomial.size());
    const Fps restored =
        m1une::fps::polynomial_interpolate_geometric(values, initial, ratio);
    assert(restored == polynomial);
}

void focused_tests() {
    assert(m1une::fps::polynomial_interpolate_geometric<Mint>({}, Mint(0), Mint(0)).empty());
    assert(m1une::fps::polynomial_interpolate_geometric(
               std::vector<Mint>(1, Mint(42)), Mint(0), Mint(0)) ==
           Fps(1, Mint(42)));

    uint64_t random = 0xac582f3d70619be4ULL;
    for (int size = 2; size <= 30; ++size) {
        Fps polynomial(size);
        for (Mint& coefficient : polynomial) {
            coefficient = Mint(next_random(random) % Mint::mod());
        }
        check_interpolation(polynomial, Mint(1 + next_random(random) % (Mint::mod() - 1)),
                            Mint(3));
    }

    const int order = 8;
    const Mint root = Mint(3).pow((Mint::mod() - 1) / order);
    Fps cyclic(order);
    for (Mint& coefficient : cyclic) coefficient = Mint(next_random(random) % Mint::mod());
    check_interpolation(cyclic, Mint(5), root);
}

}  // namespace

int main() {
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    focused_tests();

    int count;
    Mint initial, ratio;
    input >> count >> initial >> ratio;
    std::vector<Mint> values(count);
    for (Mint& value : values) input >> value;
    const Fps result =
        m1une::fps::polynomial_interpolate_geometric(values, initial, ratio);
    output << result << '\n';
}
