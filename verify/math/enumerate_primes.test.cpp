#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include "../../utilities/fast_io.hpp"
#include <vector>

#include "../../math/prime_sieve.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int n, step, offset;
    fast_input >> n >> step >> offset;
    m1une::math::PrimeSieve sieve(n);
    const std::vector<int>& primes = sieve.primes();

    int selected_count = 0;
    if (offset < int(primes.size())) {
        selected_count = (int(primes.size()) - 1 - offset) / step + 1;
    }
    fast_output << primes.size() << ' ' << selected_count << '\n';
    for (int i = offset; i < int(primes.size()); i += step) {
        if (i != offset) fast_output << ' ';
        fast_output << primes[i];
    }
    fast_output << '\n';
}
