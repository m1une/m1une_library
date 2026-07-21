#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"

#include "../../math/bitwise_convolution.hpp"
#include "../../math/modint.hpp"
#include "../../utilities/fast_io.hpp"

#include <vector>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    using mint = m1une::math::modint998244353;
    int log_size;
    fast_input >> log_size;
    int size = 1 << log_size;
    std::vector<mint> first(size), second(size);
    for (mint& value : first) fast_input >> value;
    for (mint& value : second) fast_input >> value;

    const auto result = m1une::math::bitwise_and_convolution(
        std::move(first),
        std::move(second)
    );
    for (int index = 0; index < size; index++) {
        if (index != 0) fast_output << ' ';
        fast_output << result[index];
    }
    fast_output << '\n';
}
