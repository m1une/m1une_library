#ifndef M1UNE_MATH_PARTITION_NUMBER_HRR_HPP
#define M1UNE_MATH_PARTITION_NUMBER_HRR_HPP 1

#include "../utilities/bigint.hpp"

#if !__has_include(<flint/partitions.h>)
#error "partition_number_hrr.hpp requires FLINT 3 (libflint-dev or brew install flint)"
#endif

#include <flint/flint.h>
#include <flint/fmpz.h>
#include <flint/partitions.h>

#include <stdexcept>
#include <string>

namespace m1une {
namespace math {

// Computes one exact partition number through FLINT's rigorous
// Hardy-Ramanujan-Rademacher implementation.
inline utilities::BigInt partition_number_hrr(unsigned long n) {
    fmpz_t value;
    fmpz_init(value);
    partitions_fmpz_ui(value, n);

    char* digits = fmpz_get_str(nullptr, 10, value);
    fmpz_clear(value);
    if (digits == nullptr) {
        throw std::runtime_error("FLINT failed to format the partition number");
    }

    std::string text(digits);
    flint_free(digits);
    return utilities::BigInt(text);
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_PARTITION_NUMBER_HRR_HPP
