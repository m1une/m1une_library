#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation_on_geometric_sequence"

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

void focused_tests() {
    uint64_t random = 0x194e762a80bf53d1ULL;
    for (int iteration = 0; iteration < 200; ++iteration) {
        const int coefficient_count = 1 + next_random(random) % 25;
        const int point_count = next_random(random) % 25;
        const Mint initial = Mint(next_random(random) % Mint::mod());
        const Mint ratio = Mint(next_random(random) % Mint::mod());
        Fps polynomial(coefficient_count);
        for (Mint& coefficient : polynomial) {
            coefficient = Mint(next_random(random) % Mint::mod());
        }

        const std::vector<Mint> actual = m1une::fps::multipoint_evaluate_geometric(
            polynomial, initial, ratio, point_count);
        assert(int(actual.size()) == point_count);
        Mint point = initial;
        for (int i = 0; i < point_count; ++i) {
            assert(actual[i] == polynomial.evaluate(point));
            point *= ratio;
        }
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    focused_tests();

    int coefficient_count, point_count;
    Mint initial, ratio;
    input >> coefficient_count >> point_count >> initial >> ratio;
    Fps polynomial(coefficient_count);
    for (Mint& coefficient : polynomial) input >> coefficient;
    const std::vector<Mint> result = m1une::fps::multipoint_evaluate_geometric(
        polynomial, initial, ratio, point_count);
    output << result << '\n';
}
