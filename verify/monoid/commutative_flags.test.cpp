#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <iostream>

#include "../../acted_monoid/beats_wrapper.hpp"
#include "../../acted_monoid/concept.hpp"
#include "../../acted_monoid/range_add_range_arg_max.hpp"
#include "../../acted_monoid/range_add_range_arg_min.hpp"
#include "../../acted_monoid/range_add_range_max.hpp"
#include "../../acted_monoid/range_add_range_min.hpp"
#include "../../acted_monoid/range_add_range_min_count.hpp"
#include "../../acted_monoid/range_add_range_sum.hpp"
#include "../../acted_monoid/range_affine_range_min_max.hpp"
#include "../../acted_monoid/range_affine_range_sum.hpp"
#include "../../acted_monoid/range_affine_range_sum_of_squares.hpp"
#include "../../acted_monoid/range_ap_add_range_sum.hpp"
#include "../../acted_monoid/range_ap_update_range_min_max.hpp"
#include "../../acted_monoid/range_ap_update_range_sum.hpp"
#include "../../acted_monoid/range_flip_range_binary_inversion.hpp"
#include "../../acted_monoid/range_flip_range_sum.hpp"
#include "../../acted_monoid/range_mul_range_sum.hpp"
#include "../../acted_monoid/range_or_range_sum.hpp"
#include "../../acted_monoid/range_update_range_longest_true.hpp"
#include "../../acted_monoid/range_update_range_max.hpp"
#include "../../acted_monoid/range_update_range_max_subarray.hpp"
#include "../../acted_monoid/range_update_range_min.hpp"
#include "../../acted_monoid/range_update_range_product.hpp"
#include "../../acted_monoid/range_update_range_sum.hpp"
#include "../../acted_monoid/range_xor_range_sum.hpp"
#include "../../acted_monoid/range_xor_range_xor.hpp"
#include "../../acted_monoid/wrapper.hpp"
#include "../../monoid/add.hpp"
#include "../../monoid/affine.hpp"
#include "../../monoid/and.hpp"
#include "../../monoid/arg_max.hpp"
#include "../../monoid/arg_min.hpp"
#include "../../monoid/binary_inversion.hpp"
#include "../../monoid/bottom_k.hpp"
#include "../../monoid/bracket.hpp"
#include "../../monoid/concept.hpp"
#include "../../monoid/gcd.hpp"
#include "../../monoid/longest_same.hpp"
#include "../../monoid/longest_true.hpp"
#include "../../monoid/matrix.hpp"
#include "../../monoid/max.hpp"
#include "../../monoid/max_count.hpp"
#include "../../monoid/max_plus_matrix.hpp"
#include "../../monoid/max_subarray.hpp"
#include "../../monoid/min.hpp"
#include "../../monoid/min_count.hpp"
#include "../../monoid/min_max.hpp"
#include "../../monoid/min_plus_matrix.hpp"
#include "../../monoid/min_subarray.hpp"
#include "../../monoid/mul.hpp"
#include "../../monoid/or.hpp"
#include "../../monoid/permutation.hpp"
#include "../../monoid/rolling_hash.hpp"
#include "../../monoid/strict_max2.hpp"
#include "../../monoid/strict_min2.hpp"
#include "../../monoid/top_k.hpp"
#include "../../monoid/top_k_count.hpp"
#include "../../monoid/update.hpp"
#include "../../monoid/wrapper.hpp"
#include "../../monoid/xor.hpp"

namespace {

struct ContestMonoid {
    using value_type = int;

    static constexpr int id() {
        return 0;
    }
    static constexpr int op(const int& a, const int& b) {
        return a + b;
    }
};

struct ContestActedMonoid {
    using value_type = int;
    using operator_type = int;

    static constexpr int id() {
        return 0;
    }
    static constexpr int op(const int& a, const int& b) {
        return a + b;
    }
    static constexpr int op_id() {
        return 0;
    }
    static constexpr int op_comp(const int& f, const int& g) {
        return f + g;
    }
    static constexpr int mapping(const int& f, const int& x) {
        return f + x;
    }
};

constexpr auto int_add = [](const int& a, const int& b) { return a + b; };
constexpr auto int_zero = [] { return 0; };
constexpr auto int_mapping = [](const int& f, const int& x) { return f + x; };
constexpr auto always_applicable = [](const int&, const int&) { return true; };

using DefaultMonoidWrapper = m1une::monoid::Wrapper<int, int_add, int_zero>;
using CommutativeMonoidWrapper = m1une::monoid::Wrapper<int, int_add, int_zero, true>;
using DefaultActedWrapper =
    m1une::acted_monoid::Wrapper<int, int, int_add, int_zero, int_add, int_zero, int_mapping>;
using CommutativeActedWrapper =
    m1une::acted_monoid::Wrapper<int, int, int_add, int_zero, int_add, int_zero, int_mapping, true>;
using CommutativeOperatorActedWrapper =
    m1une::acted_monoid::Wrapper<int, int, int_add, int_zero, int_add, int_zero, int_mapping, false, true>;
using DefaultBeatsWrapper = m1une::acted_monoid::BeatsWrapper<
    int, int, int_add, int_zero, int_add, int_zero, int_mapping, always_applicable>;
using CommutativeBeatsWrapper = m1une::acted_monoid::BeatsWrapper<
    int, int, int_add, int_zero, int_add, int_zero, int_mapping, always_applicable,
    nullptr, nullptr, nullptr, nullptr, nullptr, true>;
using CommutativeOperatorBeatsWrapper = m1une::acted_monoid::BeatsWrapper<
    int, int, int_add, int_zero, int_add, int_zero, int_mapping, always_applicable,
    nullptr, nullptr, nullptr, nullptr, nullptr, false, true>;

static_assert(m1une::monoid::IsMonoid<ContestMonoid>);
static_assert(m1une::acted_monoid::IsActedMonoid<ContestActedMonoid>);

static_assert(m1une::monoid::Add<int>::commutative);
static_assert(m1une::monoid::And<int>::commutative);
static_assert(m1une::monoid::BottomK<int, 2>::commutative);
static_assert(m1une::monoid::Gcd<int>::commutative);
static_assert(m1une::monoid::Max<int>::commutative);
static_assert(m1une::monoid::MaxCount<int>::commutative);
static_assert(m1une::monoid::Min<int>::commutative);
static_assert(m1une::monoid::MinCount<int>::commutative);
static_assert(m1une::monoid::MinMax<int>::commutative);
static_assert(m1une::monoid::Mul<int>::commutative);
static_assert(m1une::monoid::Or<int>::commutative);
static_assert(m1une::monoid::StrictMax2<int>::commutative);
static_assert(m1une::monoid::StrictMin2<int>::commutative);
static_assert(m1une::monoid::TopK<int, 2>::commutative);
static_assert(m1une::monoid::TopKCount<int, 2>::commutative);
static_assert(m1une::monoid::Xor<int>::commutative);
static_assert(CommutativeMonoidWrapper::commutative);

static_assert(!m1une::monoid::Affine<int>::commutative);
static_assert(!m1une::monoid::ArgMax<int>::commutative);
static_assert(!m1une::monoid::ArgMin<int>::commutative);
static_assert(!m1une::monoid::BinaryInversion<int>::commutative);
static_assert(!m1une::monoid::Bracket::commutative);
static_assert(!m1une::monoid::LongestSame<int>::commutative);
static_assert(!m1une::monoid::LongestTrue::commutative);
static_assert(!m1une::monoid::Matrix<int, 2>::commutative);
static_assert(!m1une::monoid::MaxPlusMatrix<int, 2>::commutative);
static_assert(!m1une::monoid::MaxSubarray<int>::commutative);
static_assert(!m1une::monoid::MinPlusMatrix<int, 2>::commutative);
static_assert(!m1une::monoid::MinSubarray<int>::commutative);
static_assert(!m1une::monoid::Permutation<3>::commutative);
static_assert(!m1une::monoid::RollingHash<>::commutative);
static_assert(!m1une::monoid::Update<int>::commutative);
static_assert(!DefaultMonoidWrapper::commutative);

static_assert(m1une::acted_monoid::RangeAddRangeMax<int>::commutative);
static_assert(m1une::acted_monoid::RangeAddRangeMin<int>::commutative);
static_assert(m1une::acted_monoid::RangeAddRangeMinCount<int>::commutative);
static_assert(m1une::acted_monoid::RangeAddRangeSum<int>::commutative);
static_assert(m1une::acted_monoid::RangeAffineRangeMinMax<int>::commutative);
static_assert(m1une::acted_monoid::RangeAffineRangeSum<int>::commutative);
static_assert(m1une::acted_monoid::RangeAffineRangeSumOfSquares<int>::commutative);
static_assert(m1une::acted_monoid::RangeApUpdateRangeMinMax<int>::commutative);
static_assert(m1une::acted_monoid::RangeFlipRangeSum<int>::commutative);
static_assert(m1une::acted_monoid::RangeMulRangeSum<int>::commutative);
static_assert(m1une::acted_monoid::RangeOrRangeSum<int>::commutative);
static_assert(m1une::acted_monoid::RangeUpdateRangeMax<int>::commutative);
static_assert(m1une::acted_monoid::RangeUpdateRangeMin<int>::commutative);
static_assert(m1une::acted_monoid::RangeUpdateRangeProduct<m1une::monoid::Add<int>>::commutative);
static_assert(m1une::acted_monoid::RangeUpdateRangeSum<int>::commutative);
static_assert(m1une::acted_monoid::RangeXorRangeSum<int>::commutative);
static_assert(m1une::acted_monoid::RangeXorRangeXor<int>::commutative);
static_assert(CommutativeActedWrapper::commutative);
static_assert(CommutativeBeatsWrapper::commutative);

static_assert(!m1une::acted_monoid::RangeAddRangeArgMax<int>::commutative);
static_assert(!m1une::acted_monoid::RangeAddRangeArgMin<int>::commutative);
static_assert(!m1une::acted_monoid::RangeApAddRangeSum<int>::commutative);
static_assert(!m1une::acted_monoid::RangeApUpdateRangeSum<int>::commutative);
static_assert(!m1une::acted_monoid::RangeFlipRangeBinaryInversion<int>::commutative);
static_assert(!m1une::acted_monoid::RangeUpdateRangeLongestTrue::commutative);
static_assert(!m1une::acted_monoid::RangeUpdateRangeMaxSubarray<int>::commutative);
static_assert(!m1une::acted_monoid::RangeUpdateRangeProduct<m1une::monoid::Affine<int>>::commutative);
static_assert(!m1une::acted_monoid::RangeUpdateRangeProduct<ContestMonoid>::commutative);
static_assert(!DefaultActedWrapper::commutative);
static_assert(!DefaultBeatsWrapper::commutative);

static_assert(m1une::acted_monoid::RangeAddRangeArgMax<int>::operator_commutative);
static_assert(m1une::acted_monoid::RangeAddRangeArgMin<int>::operator_commutative);
static_assert(m1une::acted_monoid::RangeAddRangeMax<int>::operator_commutative);
static_assert(m1une::acted_monoid::RangeAddRangeMin<int>::operator_commutative);
static_assert(m1une::acted_monoid::RangeAddRangeMinCount<int>::operator_commutative);
static_assert(m1une::acted_monoid::RangeAddRangeSum<int>::operator_commutative);
static_assert(m1une::acted_monoid::RangeApAddRangeSum<int>::operator_commutative);
static_assert(m1une::acted_monoid::RangeFlipRangeBinaryInversion<int>::operator_commutative);
static_assert(m1une::acted_monoid::RangeFlipRangeSum<int>::operator_commutative);
static_assert(m1une::acted_monoid::RangeMulRangeSum<int>::operator_commutative);
static_assert(m1une::acted_monoid::RangeOrRangeSum<int>::operator_commutative);
static_assert(m1une::acted_monoid::RangeXorRangeSum<int>::operator_commutative);
static_assert(m1une::acted_monoid::RangeXorRangeXor<int>::operator_commutative);
static_assert(CommutativeOperatorActedWrapper::operator_commutative);
static_assert(CommutativeOperatorBeatsWrapper::operator_commutative);

static_assert(!m1une::acted_monoid::RangeAffineRangeMinMax<int>::operator_commutative);
static_assert(!m1une::acted_monoid::RangeAffineRangeSum<int>::operator_commutative);
static_assert(!m1une::acted_monoid::RangeAffineRangeSumOfSquares<int>::operator_commutative);
static_assert(!m1une::acted_monoid::RangeApUpdateRangeMinMax<int>::operator_commutative);
static_assert(!m1une::acted_monoid::RangeApUpdateRangeSum<int>::operator_commutative);
static_assert(!m1une::acted_monoid::RangeUpdateRangeLongestTrue::operator_commutative);
static_assert(!m1une::acted_monoid::RangeUpdateRangeMax<int>::operator_commutative);
static_assert(!m1une::acted_monoid::RangeUpdateRangeMaxSubarray<int>::operator_commutative);
static_assert(!m1une::acted_monoid::RangeUpdateRangeMin<int>::operator_commutative);
static_assert(
    !m1une::acted_monoid::RangeUpdateRangeProduct<m1une::monoid::Add<int>>::operator_commutative);
static_assert(!m1une::acted_monoid::RangeUpdateRangeSum<int>::operator_commutative);
static_assert(!DefaultActedWrapper::operator_commutative);
static_assert(!DefaultBeatsWrapper::operator_commutative);
static_assert(!CommutativeActedWrapper::operator_commutative);
static_assert(!CommutativeBeatsWrapper::operator_commutative);
static_assert(!CommutativeOperatorActedWrapper::commutative);
static_assert(!CommutativeOperatorBeatsWrapper::commutative);

}  // namespace

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
