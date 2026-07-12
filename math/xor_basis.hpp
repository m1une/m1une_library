#ifndef M1UNE_MATH_XOR_BASIS_HPP
#define M1UNE_MATH_XOR_BASIS_HPP 1

#include <array>
#include <cassert>
#include <concepts>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <vector>

namespace m1une {
namespace math {

template <std::unsigned_integral UInt = unsigned long long>
class XorBasis {
    static_assert(!std::same_as<UInt, bool>);

public:
    static constexpr int bit_width = std::numeric_limits<UInt>::digits;

    XorBasis() = default;

    template <std::input_iterator Iterator, std::sentinel_for<Iterator> Sentinel>
        requires std::convertible_to<std::iter_reference_t<Iterator>, UInt>
    XorBasis(Iterator first, Sentinel last) {
        for (; first != last; ++first) insert(UInt(*first));
    }

    XorBasis(std::initializer_list<UInt> values)
        : XorBasis(values.begin(), values.end()) {}

    bool insert(UInt value) {
        for (int bit = bit_width - 1; bit >= 0; bit--) {
            if (((value >> bit) & UInt(1)) == 0) continue;
            if (basis_[bit] != 0) {
                value ^= basis_[bit];
                continue;
            }

            for (int lower = bit - 1; lower >= 0; lower--) {
                if (((value >> lower) & UInt(1)) != 0) value ^= basis_[lower];
            }
            basis_[bit] = value;
            rank_++;
            for (int higher = bit + 1; higher < bit_width; higher++) {
                if (((basis_[higher] >> bit) & UInt(1)) != 0) {
                    basis_[higher] ^= value;
                }
            }
            return true;
        }
        return false;
    }

    bool contains(UInt value) const {
        for (int bit = bit_width - 1; bit >= 0; bit--) {
            if (((value >> bit) & UInt(1)) != 0) value ^= basis_[bit];
        }
        return value == 0;
    }

    int rank() const {
        return rank_;
    }

    bool empty() const {
        return rank_ == 0;
    }

    void clear() {
        basis_.fill(UInt(0));
        rank_ = 0;
    }

    int merge(const XorBasis& other) {
        const int old_rank = rank_;
        for (UInt value : other.basis_) {
            if (value != 0) insert(value);
        }
        return rank_ - old_rank;
    }

    UInt min_xor(UInt value = 0) const {
        for (int bit = bit_width - 1; bit >= 0; bit--) {
            if ((value ^ basis_[bit]) < value) value ^= basis_[bit];
        }
        return value;
    }

    UInt max_xor(UInt value = 0) const {
        for (int bit = bit_width - 1; bit >= 0; bit--) {
            if (value < (value ^ basis_[bit])) value ^= basis_[bit];
        }
        return value;
    }

    UInt kth_smallest(UInt index) const {
        if (rank_ < bit_width) assert(index < (UInt(1) << rank_));
        UInt result = 0;
        int coefficient = 0;
        for (int bit = 0; bit < bit_width; bit++) {
            if (basis_[bit] == 0) continue;
            if (((index >> coefficient) & UInt(1)) != 0) result ^= basis_[bit];
            coefficient++;
        }
        return result;
    }

    std::vector<UInt> vectors() const {
        std::vector<UInt> result;
        result.reserve(rank_);
        for (UInt value : basis_) {
            if (value != 0) result.push_back(value);
        }
        return result;
    }

private:
    std::array<UInt, bit_width> basis_{};
    int rank_ = 0;
};

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_XOR_BASIS_HPP
