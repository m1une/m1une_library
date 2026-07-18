#ifndef M1UNE_MATRIX_DETERMINANT_MOD_HPP
#define M1UNE_MATRIX_DETERMINANT_MOD_HPP 1

#include <cassert>
#include <cstdint>
#include <type_traits>

#include "matrix.hpp"

namespace m1une {
namespace matrix {

namespace detail {

inline std::uint64_t determinant_multiply_mod(std::uint64_t lhs,
                                              std::uint64_t rhs,
                                              std::uint64_t modulus) {
    return std::uint64_t(static_cast<unsigned __int128>(lhs) * rhs % modulus);
}

inline std::uint64_t determinant_subtract_product_mod(
    std::uint64_t value, std::uint64_t lhs, std::uint64_t rhs,
    std::uint64_t modulus) {
    const std::uint64_t product = determinant_multiply_mod(lhs, rhs, modulus);
    return std::uint64_t((static_cast<unsigned __int128>(value) + modulus - product) %
                         modulus);
}

inline std::uint64_t determinant_add_products_mod(
    std::uint64_t first_lhs, std::uint64_t first_rhs,
    std::uint64_t second_lhs, std::uint64_t second_rhs,
    std::uint64_t modulus) {
    const std::uint64_t first =
        determinant_multiply_mod(first_lhs, first_rhs, modulus);
    const std::uint64_t second =
        determinant_multiply_mod(second_lhs, second_rhs, modulus);
    return std::uint64_t((static_cast<unsigned __int128>(first) + second) % modulus);
}

template <class Integer>
std::uint64_t determinant_normalize(Integer value, std::uint64_t modulus) {
    static_assert(std::is_integral_v<Integer>);
    static_assert(sizeof(Integer) <= sizeof(std::uint64_t));
    if constexpr (std::is_signed_v<Integer>) {
        __int128 residue = static_cast<__int128>(value) % static_cast<__int128>(modulus);
        if (residue < 0) residue += modulus;
        return std::uint64_t(residue);
    } else {
        return std::uint64_t(static_cast<unsigned __int128>(value) % modulus);
    }
}

}  // namespace detail

template <class Integer>
std::uint64_t determinant_mod(const Matrix<Integer>& matrix,
                              std::uint64_t modulus) {
    static_assert(std::is_integral_v<Integer>);
    assert(matrix.rows() == matrix.cols());
    assert(modulus > 0);
    const int size = matrix.rows();
    if (size == 0) return std::uint64_t(1) % modulus;

    Matrix<std::uint64_t> reduced(size, size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            reduced[row][col] =
                detail::determinant_normalize(matrix[row][col], modulus);
        }
    }

    std::uint64_t result = std::uint64_t(1) % modulus;
    bool negate = false;
    for (int col = 0; col < size; col++) {
        int pivot = col;
        while (pivot < size && reduced[pivot][col] == 0) pivot++;
        if (pivot == size) return 0;
        if (pivot != col) {
            reduced.swap_rows(pivot, col);
            negate = !negate;
        }

        for (int row = col + 1; row < size; row++) {
            std::uint64_t upper = reduced[col][col];
            std::uint64_t lower = reduced[row][col];
            if (lower == 0) continue;

            std::uint64_t upper_upper = 1 % modulus;
            std::uint64_t upper_lower = 0;
            std::uint64_t lower_upper = 0;
            std::uint64_t lower_lower = 1 % modulus;
            while (upper != 0 && lower != 0) {
                if (upper < lower) {
                    const std::uint64_t quotient = lower / upper;
                    lower -= quotient * upper;
                    lower_upper = detail::determinant_subtract_product_mod(
                        lower_upper, quotient, upper_upper, modulus);
                    lower_lower = detail::determinant_subtract_product_mod(
                        lower_lower, quotient, upper_lower, modulus);
                } else {
                    const std::uint64_t quotient = upper / lower;
                    upper -= quotient * lower;
                    upper_upper = detail::determinant_subtract_product_mod(
                        upper_upper, quotient, lower_upper, modulus);
                    upper_lower = detail::determinant_subtract_product_mod(
                        upper_lower, quotient, lower_lower, modulus);
                }
            }

            for (int index = col; index < size; index++) {
                const std::uint64_t old_upper = reduced[col][index];
                const std::uint64_t old_lower = reduced[row][index];
                reduced[col][index] = detail::determinant_add_products_mod(
                    upper_upper, old_upper, upper_lower, old_lower, modulus);
                reduced[row][index] = detail::determinant_add_products_mod(
                    lower_upper, old_upper, lower_lower, old_lower, modulus);
            }
            if (upper == 0) {
                reduced.swap_rows(col, row);
                negate = !negate;
            }
        }

        result = detail::determinant_multiply_mod(
            result, reduced[col][col], modulus);
        if (result == 0) return 0;
    }
    return negate ? modulus - result : result;
}

}  // namespace matrix
}  // namespace m1une

#endif  // M1UNE_MATRIX_DETERMINANT_MOD_HPP
