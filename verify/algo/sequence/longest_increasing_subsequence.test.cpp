#define PROBLEM "https://judge.yosupo.jp/problem/longest_increasing_subsequence"

#include "../../../algo/sequence/lis.hpp"

#include "../../../utilities/fast_io.hpp"
#include <vector>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int size;
    fast_input >> size;
    std::vector<int> values(size);
    for (int& value : values) fast_input >> value;

    std::vector<int> indices = m1une::algo::lis(values);
    fast_output << indices.size() << '\n';
    for (int i = 0; i < int(indices.size()); i++) {
        if (i != 0) fast_output << ' ';
        fast_output << indices[i];
    }
    fast_output << '\n';
}
