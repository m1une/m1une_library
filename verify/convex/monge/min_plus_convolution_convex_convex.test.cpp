#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex"

#include "../../../utilities/fast_io.hpp"
#include <vector>

#include "../../../convex/monge/min_plus_convolution.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int n, m;
    fast_input >> n >> m;
    std::vector<long long> first(n), second(m);
    for (long long& value : first) fast_input >> value;
    for (long long& value : second) fast_input >> value;

    constexpr long long infinity = 2'000'000'000'000'000'000LL;
    std::vector<long long> result =
        m1une::convex::min_plus_convolution_convex_convex(first, second, infinity);
    for (int i = 0; i < int(result.size()); i++) {
        if (i) fast_output << ' ';
        fast_output << result[i];
    }
    fast_output << '\n';
}
