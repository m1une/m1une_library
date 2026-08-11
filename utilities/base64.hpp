#ifndef M1UNE_UTILITIES_BASE64_HPP
#define M1UNE_UTILITIES_BASE64_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <limits>
#include <optional>
#include <ranges>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

namespace m1une {
namespace utilities {

inline constexpr std::string_view base64_alphabet =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

namespace detail {

inline int base64_digit(char character) noexcept {
    if ('A' <= character && character <= 'Z') return character - 'A';
    if ('a' <= character && character <= 'z') return character - 'a' + 26;
    if ('0' <= character && character <= '9') return character - '0' + 52;
    if (character == '+') return 62;
    if (character == '/') return 63;
    return -1;
}

template <class Integer>
concept Base64Integer =
    std::integral<Integer> &&
    (!std::same_as<std::remove_cv_t<Integer>, bool>);

}  // namespace detail

// Packs fixed-width nonnegative integers, most-significant bit first. The last
// Base64 digit is zero-padded on the right; '=' padding is intentionally omitted.
template <class Sequence>
requires std::ranges::input_range<const Sequence&> &&
         detail::Base64Integer<std::ranges::range_value_t<Sequence>>
std::string to_base64(const Sequence& values, int bit_width) {
    using Integer = std::ranges::range_value_t<Sequence>;
    using Unsigned = std::make_unsigned_t<Integer>;
    constexpr int digits = std::numeric_limits<Integer>::digits;

    assert(1 <= bit_width && bit_width <= digits);
    if (bit_width < 1 || bit_width > digits) return {};

    std::string encoded;
    if constexpr (std::ranges::sized_range<const Sequence&>) {
        std::size_t count = static_cast<std::size_t>(std::ranges::size(values));
        constexpr std::size_t size_limit =
            std::numeric_limits<std::size_t>::max();
        if (count <= (size_limit - 5) / static_cast<unsigned>(bit_width)) {
            encoded.reserve((count * static_cast<unsigned>(bit_width) + 5) / 6);
        }
    }
    unsigned buffer = 0;
    int buffered_bits = 0;

    for (Integer value : values) {
        if constexpr (std::signed_integral<Integer>) {
            assert(value >= 0);
            if (value < 0) return {};
        }
        Unsigned unsigned_value = static_cast<Unsigned>(value);
        if (bit_width < digits) {
            assert((unsigned_value >> bit_width) == 0);
            if ((unsigned_value >> bit_width) != 0) return {};
        }

        int remaining_bits = bit_width;
        while (remaining_bits > 0) {
            int take = std::min(6 - buffered_bits, remaining_bits);
            int shift = remaining_bits - take;
            unsigned mask = (1U << take) - 1;
            unsigned part = static_cast<unsigned>((unsigned_value >> shift) & mask);
            buffer = (buffer << take) | part;
            buffered_bits += take;
            remaining_bits -= take;

            if (buffered_bits == 6) {
                encoded.push_back(base64_alphabet[buffer]);
                buffer = 0;
                buffered_bits = 0;
            }
        }
    }

    if (buffered_bits != 0) {
        encoded.push_back(base64_alphabet[buffer << (6 - buffered_bits)]);
    }
    return encoded;
}

// Returns nullopt unless encoded is the canonical encoding of exactly count
// values with the requested bit width.
template <detail::Base64Integer Integer>
std::optional<std::vector<Integer>> checked_from_base64(
    std::string_view encoded, std::size_t count, int bit_width) {
    constexpr int digits = std::numeric_limits<Integer>::digits;
    if (bit_width < 1 || bit_width > digits) return std::nullopt;

    constexpr std::size_t size_limit = std::numeric_limits<std::size_t>::max();
    if (count > (size_limit - 5) / static_cast<unsigned>(bit_width)) {
        return std::nullopt;
    }
    std::size_t total_bits = count * static_cast<unsigned>(bit_width);
    if (encoded.size() != (total_bits + 5) / 6) return std::nullopt;

    using Unsigned = std::make_unsigned_t<Integer>;
    std::vector<Integer> values;
    values.reserve(count);
    std::size_t position = 0;
    unsigned buffer = 0;
    int buffered_bits = 0;

    for (std::size_t index = 0; index < count; ++index) {
        Unsigned value = 0;
        int remaining_bits = bit_width;
        while (remaining_bits > 0) {
            if (buffered_bits == 0) {
                int digit = detail::base64_digit(encoded[position++]);
                if (digit < 0) return std::nullopt;
                buffer = static_cast<unsigned>(digit);
                buffered_bits = 6;
            }

            int take = std::min(buffered_bits, remaining_bits);
            int shift = buffered_bits - take;
            unsigned mask = (1U << take) - 1;
            unsigned part = (buffer >> shift) & mask;
            value = static_cast<Unsigned>((value << take) | part);
            buffered_bits -= take;
            remaining_bits -= take;
        }
        values.push_back(static_cast<Integer>(value));
    }

    if (buffered_bits != 0) {
        unsigned mask = (1U << buffered_bits) - 1;
        if ((buffer & mask) != 0) return std::nullopt;
    }
    return values;
}

template <detail::Base64Integer Integer>
std::vector<Integer> from_base64(std::string_view encoded, std::size_t count,
                                 int bit_width) {
    std::optional<std::vector<Integer>> result =
        checked_from_base64<Integer>(encoded, count, bit_width);
    assert(result.has_value());
    return result.value_or(std::vector<Integer>());
}

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_UTILITIES_BASE64_HPP
