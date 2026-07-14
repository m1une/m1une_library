#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

#include "../../string/kmp.hpp"

#include "../../utilities/fast_io.hpp"
#include <string>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    std::string text;
    std::string pattern;
    fast_input >> text >> pattern;

    for (int position : m1une::string::kmp_search(text, pattern)) {
        fast_output << position << '\n';
    }
}
