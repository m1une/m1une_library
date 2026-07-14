#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include "../../string/manacher.hpp"

#include "../../utilities/fast_io.hpp"
#include <string>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    std::string text;
    fast_input >> text;
    m1une::string::ManacherResult result = m1une::string::manacher(text);

    for (int center = 0; center < 2 * int(text.size()) - 1; center++) {
        if (center != 0) fast_output << ' ';
        if (center & 1) {
            fast_output << 2 * result.even[(center + 1) / 2];
        } else {
            fast_output << 2 * result.odd[center / 2] - 1;
        }
    }
    fast_output << '\n';
}
