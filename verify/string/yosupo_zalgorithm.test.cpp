#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../string/z_algorithm.hpp"
#include "../../utilities/fast_io.hpp"
#include <string>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    std::string S;
    fast_input >> S;
    std::vector<int> z = m1une::string::z_algorithm(S);
    for (int i = 0; i < int(z.size()); ++i) {
        fast_output << z[i] << (i + 1 == int(z.size()) ? "" : " ");
    }
    fast_output << "\n";

    return 0;
}
