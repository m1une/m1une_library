#define PROBLEM "https://judge.yosupo.jp/problem/sparse_matrix_det"

#include "../../../math/matrix/linear_algebra.hpp"
#include "../../../math/matrix/sparse_determinant.hpp"
#include "../../../math/modint.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {

using mint = m1une::math::modint998244353;
using Entry = m1une::matrix::SparseMatrixEntry<mint>;
using Matrix = m1une::matrix::Matrix<mint>;

mint dense_determinant(int size, const std::vector<Entry>& entries) {
    Matrix matrix(size, size);
    for (const Entry& entry : entries) matrix[entry.row][entry.col] += entry.value;
    return m1une::matrix::determinant(std::move(matrix));
}

void validate(int size, const std::vector<Entry>& entries, std::uint64_t seed) {
    mint expected = dense_determinant(size, entries);
    mint actual = m1une::matrix::sparse_determinant(size, entries, seed);
    assert(actual == expected);
}

void test_edge_cases() {
    validate(0, {}, 1);
    validate(4, {}, 2);

    std::vector<Entry> identity;
    for (int i = 0; i < 7; i++) identity.push_back(Entry{i, i, mint(1)});
    validate(7, identity, 3);

    std::vector<Entry> singular;
    singular.push_back(Entry{0, 0, mint(2)});
    singular.push_back(Entry{0, 1, mint(3)});
    singular.push_back(Entry{1, 0, mint(2)});
    singular.push_back(Entry{1, 1, mint(3)});
    validate(2, singular, 4);

    std::vector<Entry> permutation;
    permutation.push_back(Entry{0, 1, mint(1)});
    permutation.push_back(Entry{1, 2, mint(1)});
    permutation.push_back(Entry{2, 0, mint(1)});
    validate(3, permutation, 5);
}

void test_randomized() {
    std::uint64_t state = 0x94d049bb133111ebULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 500; trial++) {
        int size = int(random() % 9);
        std::vector<Entry> entries;
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                if (random() % 3 == 0) continue;
                entries.push_back(Entry{row, col, mint(int(random() % 17) - 8)});
                if (random() % 7 == 0) {
                    entries.push_back(Entry{row, col, mint(int(random() % 11) - 5)});
                }
            }
        }
        validate(size, entries, random());
    }
}

}  // namespace

int main() {
    test_edge_cases();
    test_randomized();

    int size, entry_count;
    std::cin >> size >> entry_count;
    std::vector<Entry> entries;
    entries.reserve(entry_count);
    while (entry_count--) {
        int row, col;
        mint value;
        std::cin >> row >> col >> value;
        entries.push_back(Entry{row, col, value});
    }
    std::cout << m1une::matrix::sparse_determinant(size, entries) << '\n';
}
