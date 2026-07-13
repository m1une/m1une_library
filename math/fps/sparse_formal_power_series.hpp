#ifndef M1UNE_FPS_SPARSE_FORMAL_POWER_SERIES_HPP
#define M1UNE_FPS_SPARSE_FORMAL_POWER_SERIES_HPP 1

#include <cassert>
#include <cstdint>
#include <optional>
#include <utility>
#include <vector>

#include "formal_power_series.hpp"

namespace m1une {
namespace fps {

template <class Mint>
using SparseFormalPowerSeries = std::vector<std::pair<int, Mint>>;

namespace internal {

template <class Mint>
void assert_valid_sparse_fps(const SparseFormalPowerSeries<Mint>& terms, int degree) {
    int previous_degree = -1;
    for (const auto& [term_degree, coefficient] : terms) {
        assert(0 <= term_degree && previous_degree < term_degree && term_degree < degree);
        assert(coefficient != Mint(0));
        previous_degree = term_degree;
    }
}

template <class Mint>
std::vector<Mint> sparse_integer_inverses(int degree) {
    assert(degree >= 0 && uint32_t(degree) < Mint::mod());
    std::vector<Mint> inverse(degree);
    if (degree <= 1) return inverse;
    inverse[1] = Mint(1);
    for (int i = 2; i < degree; i++) {
        const uint32_t quotient = Mint::mod() / uint32_t(i);
        const uint32_t remainder = Mint::mod() % uint32_t(i);
        inverse[i] = Mint(0) - Mint(quotient) * inverse[remainder];
    }
    return inverse;
}

template <class Mint>
FormalPowerSeries<Mint> sparse_unit_pow(const SparseFormalPowerSeries<Mint>& terms,
                                        Mint exponent, int degree) {
    assert(degree > 0 && !terms.empty());
    assert(terms[0].first == 0 && terms[0].second == Mint(1));
    std::vector<Mint> inverse = sparse_integer_inverses<Mint>(degree);
    FormalPowerSeries<Mint> result(degree);
    result[0] = Mint(1);
    for (int n = 1; n < degree; n++) {
        Mint coefficient = 0;
        for (int i = 1; i < int(terms.size()) && terms[i].first <= n; i++) {
            const auto& [d, value] = terms[i];
            coefficient += value * result[n - d] *
                           (exponent * Mint(d) - Mint(n - d));
        }
        result[n] = coefficient * inverse[n];
    }
    return result;
}

}  // namespace internal

template <class Mint>
FormalPowerSeries<Mint> sparse_fps_inv(const SparseFormalPowerSeries<Mint>& terms,
                                       int degree) {
    assert(degree >= 0);
    if (degree == 0) return {};
    internal::assert_valid_sparse_fps(terms, degree);
    assert(!terms.empty() && terms[0].first == 0);

    const Mint inverse_constant = terms[0].second.inv();
    FormalPowerSeries<Mint> result(degree);
    result[0] = inverse_constant;
    for (int n = 1; n < degree; n++) {
        Mint coefficient = 0;
        for (int i = 1; i < int(terms.size()) && terms[i].first <= n; i++) {
            coefficient -= terms[i].second * result[n - terms[i].first];
        }
        result[n] = coefficient * inverse_constant;
    }
    return result;
}

template <class Mint>
FormalPowerSeries<Mint> sparse_fps_log(const SparseFormalPowerSeries<Mint>& terms,
                                       int degree) {
    assert(degree >= 0);
    if (degree == 0) return {};
    assert(uint32_t(degree) < Mint::mod());
    internal::assert_valid_sparse_fps(terms, degree);
    assert(!terms.empty() && terms[0].first == 0 && terms[0].second == Mint(1));

    std::vector<Mint> inverse = internal::sparse_integer_inverses<Mint>(degree);
    FormalPowerSeries<Mint> result(degree);
    for (int n = 0; n + 1 < degree; n++) {
        Mint derivative_quotient = 0;
        for (int i = 1; i < int(terms.size()) && terms[i].first <= n + 1; i++) {
            const auto& [d, value] = terms[i];
            if (d == n + 1) derivative_quotient += Mint(d) * value;
            if (d <= n) {
                derivative_quotient -=
                    value * Mint(n - d + 1) * result[n - d + 1];
            }
        }
        result[n + 1] = derivative_quotient * inverse[n + 1];
    }
    return result;
}

template <class Mint>
FormalPowerSeries<Mint> sparse_fps_exp(const SparseFormalPowerSeries<Mint>& terms,
                                       int degree) {
    assert(degree >= 0);
    if (degree == 0) return {};
    assert(uint32_t(degree) < Mint::mod());
    internal::assert_valid_sparse_fps(terms, degree);
    assert(terms.empty() || terms[0].first > 0);

    std::vector<Mint> inverse = internal::sparse_integer_inverses<Mint>(degree);
    FormalPowerSeries<Mint> result(degree);
    result[0] = Mint(1);
    for (int n = 1; n < degree; n++) {
        Mint coefficient = 0;
        for (const auto& [d, value] : terms) {
            if (d > n) break;
            coefficient += Mint(d) * value * result[n - d];
        }
        result[n] = coefficient * inverse[n];
    }
    return result;
}

template <class Mint>
FormalPowerSeries<Mint> sparse_fps_pow(const SparseFormalPowerSeries<Mint>& terms,
                                       long long exponent, int degree) {
    assert(exponent >= 0 && degree >= 0);
    if (degree == 0) return {};
    assert(uint32_t(degree) < Mint::mod());
    internal::assert_valid_sparse_fps(terms, degree);
    if (exponent == 0) {
        FormalPowerSeries<Mint> result(degree);
        result[0] = Mint(1);
        return result;
    }
    if (terms.empty()) return FormalPowerSeries<Mint>(degree);

    const int leading_degree = terms[0].first;
    if (leading_degree > 0 && exponent > (degree - 1) / leading_degree) {
        return FormalPowerSeries<Mint>(degree);
    }
    const int offset = int(leading_degree * exponent);
    const int normalized_degree = degree - offset;
    const Mint leading = terms[0].second;
    const Mint inverse_leading = leading.inv();
    SparseFormalPowerSeries<Mint> normalized;
    normalized.reserve(terms.size());
    for (const auto& [d, value] : terms) {
        if (d - leading_degree >= normalized_degree) break;
        normalized.emplace_back(d - leading_degree, value * inverse_leading);
    }

    FormalPowerSeries<Mint> unit =
        internal::sparse_unit_pow(normalized, Mint(exponent), normalized_degree);
    const Mint scale = leading.pow(exponent);
    FormalPowerSeries<Mint> result(degree);
    for (int i = 0; i < normalized_degree; i++) result[offset + i] = unit[i] * scale;
    return result;
}

template <class Mint>
std::optional<FormalPowerSeries<Mint>> sparse_fps_sqrt(
    const SparseFormalPowerSeries<Mint>& terms, int degree) {
    assert(degree >= 0);
    if (degree == 0) return FormalPowerSeries<Mint>();
    assert(uint32_t(degree) < Mint::mod());
    internal::assert_valid_sparse_fps(terms, degree);
    assert(Mint(2) != Mint(0));
    if (terms.empty()) return FormalPowerSeries<Mint>(degree);

    const int leading_degree = terms[0].first;
    if (leading_degree & 1) return std::nullopt;
    auto leading_root = m1une::math::modular_square_root(terms[0].second);
    if (!leading_root.has_value()) return std::nullopt;

    const int normalized_degree = degree - leading_degree;
    const Mint inverse_leading = terms[0].second.inv();
    SparseFormalPowerSeries<Mint> normalized;
    normalized.reserve(terms.size());
    for (const auto& [d, value] : terms) {
        normalized.emplace_back(d - leading_degree, value * inverse_leading);
    }
    FormalPowerSeries<Mint> unit = internal::sparse_unit_pow(
        normalized, Mint(2).inv(), normalized_degree);

    FormalPowerSeries<Mint> result(degree);
    const int offset = leading_degree / 2;
    for (int i = 0; i < normalized_degree; i++) {
        result[offset + i] = unit[i] * *leading_root;
    }
    return result;
}

}  // namespace fps
}  // namespace m1une

#endif  // M1UNE_FPS_SPARSE_FORMAL_POWER_SERIES_HPP
