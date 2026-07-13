#define PROBLEM "https://judge.yosupo.jp/problem/longest_increasing_subsequence"

#include "../../../algo/sequence/lis.hpp"

#include <iostream>
#include <vector>

int main() {
    int size;
    std::cin >> size;
    std::vector<int> values(size);
    for (int& value : values) std::cin >> value;

    std::vector<int> indices = m1une::algo::lis(values);
    std::cout << indices.size() << '\n';
    for (int i = 0; i < int(indices.size()); i++) {
        if (i != 0) std::cout << ' ';
        std::cout << indices[i];
    }
    std::cout << '\n';
}
