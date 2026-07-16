#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"

#include <vector>

#include "../../../math/fps/linear_recurrence.hpp"
#include "../../../math/modint.hpp"
#include "../../../utilities/fast_io.hpp"

using mint = m1une::math::modint998244353;

int main() {
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    int size = 0;
    input.read(size);
    std::vector<mint> sequence(size);
    input.read(sequence);

    std::vector<mint> recurrence = m1une::fps::berlekamp_massey(sequence);
    output.println(recurrence.size());
    output.println(recurrence);
}
