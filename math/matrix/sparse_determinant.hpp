#ifndef M1UNE_MATRIX_SPARSE_DETERMINANT_HPP
#define M1UNE_MATRIX_SPARSE_DETERMINANT_HPP 1

#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

namespace m1une {
namespace matrix {

template <class T>
struct SparseMatrixEntry {
    int row;
    int col;
    T value;
};

namespace internal {

struct SparseDeterminantRandom {
    std::uint64_t state;

    explicit SparseDeterminantRandom(std::uint64_t seed) : state(seed) {}

    std::uint64_t operator()() {
        std::uint64_t value = (state += 0x9e3779b97f4a7c15ULL);
        value = (value ^ (value >> 30)) * 0xbf58476d1ce4e5b9ULL;
        value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;
        return value ^ (value >> 31);
    }
};

template <class T>
std::vector<T> berlekamp_massey(const std::vector<T>& sequence) {
    std::vector<T> recurrence(1, T(1));
    std::vector<T> previous(1, T(1));
    int degree = 0;
    int shift = 1;
    T previous_discrepancy = T(1);

    for (int index = 0; index < int(sequence.size()); index++) {
        T discrepancy = sequence[index];
        for (int i = 1; i <= degree; i++) {
            discrepancy += recurrence[i] * sequence[index - i];
        }
        if (discrepancy == T()) {
            shift++;
            continue;
        }

        const T factor = discrepancy / previous_discrepancy;
        std::vector<T> old_recurrence = recurrence;
        if (int(recurrence.size()) < int(previous.size()) + shift) {
            recurrence.resize(previous.size() + std::size_t(shift), T());
        }
        for (int i = 0; i < int(previous.size()); i++) {
            recurrence[i + shift] -= factor * previous[i];
        }

        if (2 * degree <= index) {
            degree = index + 1 - degree;
            previous = std::move(old_recurrence);
            previous_discrepancy = discrepancy;
            shift = 1;
        } else {
            shift++;
        }
    }
    recurrence.resize(std::size_t(degree + 1));
    return recurrence;
}

}  // namespace internal

// Randomized black-box determinant over a finite field. random_nonzero must
// return independent nonzero field elements.
template <class T, class RandomValue>
T sparse_determinant_with_randomizer(
    int size, const std::vector<SparseMatrixEntry<T>>& entries,
    RandomValue random_nonzero
) {
    assert(size >= 0);
    for (const SparseMatrixEntry<T>& entry : entries) {
        assert(0 <= entry.row && entry.row < size);
        assert(0 <= entry.col && entry.col < size);
    }
    if (size == 0) return T(1);

    auto random_vector = [&]() {
        std::vector<T> result(size);
        for (T& value : result) {
            value = random_nonzero();
            assert(value != T());
        }
        return result;
    };

    while (true) {
        std::vector<T> diagonal = random_vector();
        std::vector<T> left = random_vector();
        std::vector<T> state = random_vector();
        std::vector<T> sequence(std::size_t(2 * size));

        for (int step = 0; step < 2 * size; step++) {
            for (int i = 0; i < size; i++) sequence[step] += left[i] * state[i];
            for (int i = 0; i < size; i++) state[i] *= diagonal[i];

            std::vector<T> next(size);
            for (const SparseMatrixEntry<T>& entry : entries) {
                next[entry.row] += entry.value * state[entry.col];
            }
            state = std::move(next);
        }

        std::vector<T> recurrence = internal::berlekamp_massey(sequence);
        if (recurrence.back() == T()) return T();
        if (int(recurrence.size()) != size + 1) continue;

        T determinant = recurrence.back();
        if (size % 2 == 1) determinant = T() - determinant;
        for (const T& value : diagonal) determinant /= value;
        return determinant;
    }
}

template <class T>
T sparse_determinant(
    int size, const std::vector<SparseMatrixEntry<T>>& entries,
    std::uint64_t seed = 0x243f6a8885a308d3ULL
) {
    const std::uint64_t modulus = T::mod();
    assert(modulus > 1);
    internal::SparseDeterminantRandom random(seed);
    auto random_nonzero = [&]() {
        return T(1 + random() % (modulus - 1));
    };
    return sparse_determinant_with_randomizer<T>(size, entries, random_nonzero);
}

}  // namespace matrix
}  // namespace m1une

#endif  // M1UNE_MATRIX_SPARSE_DETERMINANT_HPP
