#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary"

#include "../../../utilities/fast_io.hpp"
#include <vector>

#include "../../../convex/monge/min_plus_convolution.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int n, m;
    fast_input >> n >> m;
    std::vector<long long> concave(n), arbitrary(m);
    for (long long& value : concave) {
        fast_input >> value;
        value = -value;
    }
    for (long long& value : arbitrary) {
        fast_input >> value;
        value = -value;
    }

    constexpr long long negative_infinity = -2'000'000'000'000'000'000LL;
    std::vector<long long> result = m1une::convex::max_plus_convolution_concave(
        arbitrary, concave, negative_infinity);
    for (int i = 0; i < int(result.size()); i++) {
        if (i) fast_output << ' ';
        fast_output << -result[i];
    }
    fast_output << '\n';
}
