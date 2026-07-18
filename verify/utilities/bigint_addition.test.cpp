#define PROBLEM "https://judge.yosupo.jp/problem/addition_of_big_integers"

#pragma GCC optimize("O3")

#include "../../utilities/bigint.hpp"
using m1une::utilities::BigInt;

#include "../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    int test_count;
    input >> test_count;
    while (test_count--) {
        std::string lhs, rhs;
        input >> lhs >> rhs;
        output << (BigInt(lhs) + BigInt(rhs)).to_string() << '\n';
    }
}
