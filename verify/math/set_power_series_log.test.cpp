#define PROBLEM "https://judge.yosupo.jp/problem/log_of_set_power_series"

#include "../../math/modint.hpp"
#include "../../math/set_power_series.hpp"
#include "../../utilities/fast_io.hpp"

#include <vector>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int bit_count = 0;
    fast_input >> bit_count;
    int size = 1 << bit_count;
    using Mint = m1une::math::modint998244353;
    std::vector<Mint> series(size);
    for (Mint& value : series) fast_input >> value;
    std::vector<Mint> result = m1une::math::set_power_series_log(series);
    for (int mask = 0; mask < size; mask++) {
        if (mask != 0) fast_output << ' ';
        fast_output << result[mask].val();
    }
    fast_output << '\n';
}
