#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_set_power_series"

#include "../../math/modint.hpp"
#include "../../math/set_power_series.hpp"
#include "../../utilities/fast_io.hpp"

#include <bit>
#include <cassert>
#include <cstdint>
#include <vector>

namespace {

using Mint = m1une::math::modint998244353;

std::vector<Mint> naive_product(
    const std::vector<Mint>& first,
    const std::vector<Mint>& second
) {
    assert(first.size() == second.size());
    std::vector<Mint> result(first.size());
    for (int mask = 0; mask < int(first.size()); mask++) {
        int submask = mask;
        while (true) {
            result[mask] += first[submask] * second[mask ^ submask];
            if (submask == 0) break;
            submask = (submask - 1) & mask;
        }
    }
    return result;
}

std::vector<Mint> naive_exp(const std::vector<Mint>& series) {
    int bit_count = std::countr_zero(series.size());
    std::vector<Mint> result(series.size());
    std::vector<Mint> power(series.size());
    power[0] = 1;
    Mint factorial = 1;
    for (int exponent = 0; exponent <= bit_count; exponent++) {
        if (exponent > 0) factorial *= exponent;
        Mint inverse_factorial = Mint(1) / factorial;
        for (int mask = 0; mask < int(series.size()); mask++) {
            result[mask] += power[mask] * inverse_factorial;
        }
        power = naive_product(power, series);
    }
    return result;
}

void test_randomized() {
    std::uint64_t state = 0x9e3779b97f4a7c15ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 300; trial++) {
        int bit_count = int(random() % 6);
        int size = 1 << bit_count;
        std::vector<Mint> logarithm(size);
        logarithm[0] = 0;
        for (int mask = 1; mask < size; mask++) logarithm[mask] = random();

        std::vector<Mint> series =
            m1une::math::set_power_series_exp(logarithm);
        assert(series == naive_exp(logarithm));
        assert(m1une::math::set_power_series_log(series) == logarithm);

        std::vector<Mint> quotient(size), denominator(size);
        denominator[0] = Mint(random() % 998244352ULL + 1);
        for (int mask = 0; mask < size; mask++) quotient[mask] = random();
        for (int mask = 1; mask < size; mask++) denominator[mask] = random();
        std::vector<Mint> numerator = naive_product(quotient, denominator);
        assert(
            m1une::math::set_power_series_divide(numerator, denominator) ==
            quotient
        );
        std::vector<Mint> inverse =
            m1une::math::set_power_series_inverse(denominator);
        std::vector<Mint> identity(size);
        identity[0] = 1;
        assert(naive_product(denominator, inverse) == identity);

        std::vector<Mint> normalized = series;
        std::vector<Mint> cube = naive_product(
            naive_product(normalized, normalized),
            normalized
        );
        assert(m1une::math::set_power_series_pow(normalized, 3) == cube);
        assert(
            naive_product(
                normalized,
                m1une::math::set_power_series_pow(normalized, -1)
            ) == identity
        );
        assert(m1une::math::set_power_series_pow(normalized, 0) == identity);
        std::vector<Mint> square = naive_product(normalized, normalized);
        std::vector<Mint> root =
            m1une::math::set_power_series_sqrt(square);
        assert(naive_product(root, root) == square);
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_randomized();

    int bit_count = 0;
    fast_input >> bit_count;
    int size = 1 << bit_count;
    std::vector<Mint> series(size);
    for (Mint& value : series) fast_input >> value;
    std::vector<Mint> result = m1une::math::set_power_series_exp(series);
    for (int mask = 0; mask < size; mask++) {
        if (mask != 0) fast_output << ' ';
        fast_output << result[mask].val();
    }
    fast_output << '\n';
}
