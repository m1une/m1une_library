#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "../../string/suffix_array.hpp"

#include "../../utilities/fast_io.hpp"
#include <string>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    std::string text;
    fast_input >> text;
    std::vector<int> suffixes = m1une::string::suffix_array(text);
    for (int i = 0; i < int(suffixes.size()); i++) {
        if (i != 0) fast_output << ' ';
        fast_output << suffixes[i];
    }
    fast_output << '\n';
}
