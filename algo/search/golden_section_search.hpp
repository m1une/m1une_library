#ifndef M1UNE_ALGO_SEARCH_GOLDEN_SECTION_SEARCH_HPP
#define M1UNE_ALGO_SEARCH_GOLDEN_SECTION_SEARCH_HPP 1

#include <cassert>
#include <concepts>
#include <numeric>
#include <type_traits>
#include <utility>
#include <vector>

namespace m1une {
namespace algo {

namespace detail {

template <std::integral Int, class F, class Compare>
Int integer_golden_section_search(Int left, Int right, F f, Compare comp) {
    assert(left < right);

    using UInt = std::make_unsigned_t<Int>;
    using Uint128 = unsigned __int128;
    const Uint128 n = static_cast<Uint128>(static_cast<UInt>(right) - static_cast<UInt>(left));

    auto add_offset = [left](Uint128 offset) -> Int {
        if constexpr (std::signed_integral<Int>) {
            if (left < 0) {
                const Uint128 negative_count = static_cast<Uint128>(-(left + 1)) + 1;
                if (offset < negative_count) {
                    return static_cast<Int>(left + static_cast<Int>(offset));
                }
                return static_cast<Int>(offset - negative_count);
            }
        }
        return static_cast<Int>(left + static_cast<Int>(offset));
    };

    using Value = std::decay_t<decltype(f(left))>;
    struct Evaluated {
        Uint128 pos;
        const Value* value;
    };

    Uint128 fib0 = 1;
    Uint128 fib1 = 1;
    Uint128 fib2 = 2;
    int k = 2;
    while (fib2 < n) {
        fib0 = fib1;
        fib1 = fib2;
        fib2 = fib0 + fib1;
        ++k;
    }

    std::vector<std::pair<Uint128, Value>> cache;
    cache.reserve(static_cast<unsigned>(k) + 4);

    auto find_cached = [&](Uint128 pos) -> const Value* {
        for (const auto& [cached_pos, value] : cache) {
            if (cached_pos == pos) return &value;
        }
        return nullptr;
    };

    auto advance_fibonacci = [&]() {
        const Uint128 old0 = fib0;
        const Uint128 old1 = fib1;
        fib0 = old1 - old0;
        fib1 = old0;
        fib2 = old1;
        --k;
    };

    auto eval = [&](Uint128 pos) -> Evaluated {
        if (pos >= n) return Evaluated{pos, nullptr};
        if (const Value* value = find_cached(pos)) return Evaluated{pos, value};
        cache.emplace_back(pos, f(add_offset(pos)));
        return Evaluated{pos, &cache.back().second};
    };

    auto get_value = [&](Uint128 pos) -> const Value& {
        if (const Value* value = find_cached(pos)) return *value;
        cache.emplace_back(pos, f(add_offset(pos)));
        return cache.back().second;
    };

    auto scan = [&](Uint128 scan_left, Uint128 scan_right) -> Int {
        Int best = add_offset(scan_left);
        const Value* best_value = &get_value(scan_left);
        for (Uint128 pos = scan_left + 1; pos <= scan_right; ++pos) {
            Int x = add_offset(pos);
            const Value& value = get_value(pos);
            if (comp(value, *best_value)) {
                best = x;
                best_value = &value;
            }
        }
        return best;
    };

    if (n <= 3) return scan(0, n - 1);

    auto better = [&](const Evaluated& a, const Evaluated& b) -> bool {
        if ((a.value != nullptr) != (b.value != nullptr)) return a.value != nullptr;
        if (a.value == nullptr) return false;
        return comp(*a.value, *b.value);
    };

    Uint128 left_pos = 0;
    Uint128 right_pos = fib2 - 1;
    Uint128 x1 = left_pos + fib0 - 1;
    Uint128 x2 = left_pos + fib1 - 1;
    Evaluated y1 = eval(x1);
    Evaluated y2 = eval(x2);

    while (k > 2) {
        if (better(y2, y1)) {
            left_pos = x1 + 1;
            x1 = x2;
            y1 = y2;
            advance_fibonacci();
            if (k == 2) break;
            x2 = left_pos + fib1 - 1;
            y2 = eval(x2);
        } else {
            right_pos = x2;
            x2 = x1;
            y2 = y1;
            advance_fibonacci();
            if (k == 2) break;
            x1 = left_pos + fib0 - 1;
            y1 = eval(x1);
        }
    }

    const Uint128 last_valid = n - 1;
    if (right_pos > last_valid) right_pos = last_valid;
    assert(left_pos <= right_pos);
    return scan(left_pos, right_pos);
}

}  // namespace detail

template <std::integral Int, class F>
Int golden_section_search_argmin(Int left, Int right, F f) {
    return detail::integer_golden_section_search(left, right, f, [](const auto& a, const auto& b) { return a < b; });
}

template <std::integral Int, class F>
Int golden_section_search_argmax(Int left, Int right, F f) {
    return detail::integer_golden_section_search(left, right, f, [](const auto& a, const auto& b) { return b < a; });
}

template <class F>
double golden_section_search_argmin(double left, double right, F f, int iterations = 100) {
    assert(left <= right);
    assert(0 <= iterations);
    if (left == right || iterations == 0) return std::midpoint(left, right);

    constexpr double inv_phi = 0.6180339887498948482045868343656381177203;
    double x1 = right - (right - left) * inv_phi;
    double x2 = left + (right - left) * inv_phi;
    auto y1 = f(x1);
    auto y2 = f(x2);

    for (int i = 1; i < iterations; ++i) {
        if (y2 < y1) {
            left = x1;
            x1 = x2;
            y1 = std::move(y2);
            x2 = left + (right - left) * inv_phi;
            y2 = f(x2);
        } else {
            right = x2;
            x2 = x1;
            y2 = std::move(y1);
            x1 = right - (right - left) * inv_phi;
            y1 = f(x1);
        }
    }

    if (y2 < y1) {
        left = x1;
    } else {
        right = x2;
    }
    return std::midpoint(left, right);
}

template <class F>
double golden_section_search_argmax(double left, double right, F f, int iterations = 100) {
    assert(left <= right);
    assert(0 <= iterations);
    if (left == right || iterations == 0) return std::midpoint(left, right);

    constexpr double inv_phi = 0.6180339887498948482045868343656381177203;
    double x1 = right - (right - left) * inv_phi;
    double x2 = left + (right - left) * inv_phi;
    auto y1 = f(x1);
    auto y2 = f(x2);

    for (int i = 1; i < iterations; ++i) {
        if (y1 < y2) {
            left = x1;
            x1 = x2;
            y1 = std::move(y2);
            x2 = left + (right - left) * inv_phi;
            y2 = f(x2);
        } else {
            right = x2;
            x2 = x1;
            y2 = std::move(y1);
            x1 = right - (right - left) * inv_phi;
            y1 = f(x1);
        }
    }

    if (y1 < y2) {
        left = x1;
    } else {
        right = x2;
    }
    return std::midpoint(left, right);
}

}  // namespace algo
}  // namespace m1une

#endif  // M1UNE_ALGO_SEARCH_GOLDEN_SECTION_SEARCH_HPP
