#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

#include "../../beats_acted_monoid/concept.hpp"
#include "../../beats_acted_monoid/range_bitwise_and_or_range_sum.hpp"
#include "../../ds/segtree/segtree_beats.hpp"

namespace {

using AM =
    m1une::beats_acted_monoid::RangeBitwiseAndOrRangeSum<long long, 10>;
using SignedFullWidth =
    m1une::beats_acted_monoid::RangeBitwiseAndOrRangeSum<long long, 63>;
using UnsignedFullWidth =
    m1une::beats_acted_monoid::RangeBitwiseAndOrRangeSum<
        unsigned long long,
        64
    >;

long long apply_scalar(const AM::operator_type& f, long long value) {
    return (value & f.and_mask) | f.or_mask;
}

void test_composition() {
    std::vector<AM::operator_type> operators;
    for (long long mask = 0; mask < 32; ++mask) {
        operators.emplace_back(AM::make_and(mask));
        operators.emplace_back(AM::make_or(mask));
    }

    for (const auto& f : operators) {
        for (const auto& g : operators) {
            auto composition = AM::op_comp(f, g);
            for (long long value = 0; value < 32; ++value) {
                assert(
                    apply_scalar(composition, value) ==
                    apply_scalar(f, apply_scalar(g, value))
                );
            }
        }
    }
}

void test_randomized() {
    constexpr int size = 73;
    constexpr long long mask = (1LL << 10) - 1;
    std::uint64_t state = 0x3141592653589793ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    std::vector<long long> values(size);
    for (long long& value : values) {
        value = static_cast<long long>(random() & mask);
    }
    m1une::ds::SegtreeBeats<AM> seg(values);

    for (int step = 0; step < 10000; ++step) {
        int left = int(random() % (size + 1));
        int right = int(random() % (size + 1));
        if (right < left) std::swap(left, right);

        if (random() % 3 != 0) {
            long long operand = static_cast<long long>(random() & mask);
            if (random() & 1) {
                seg.apply(left, right, AM::make_and(operand));
                for (int index = left; index < right; ++index) {
                    values[index] &= operand;
                }
            } else {
                seg.apply(left, right, AM::make_or(operand));
                for (int index = left; index < right; ++index) {
                    values[index] |= operand;
                }
            }
        } else {
            long long expected = 0;
            for (int index = left; index < right; ++index) {
                expected += values[index];
            }
            assert(seg.prod(left, right).sum == expected);
        }

        int index = int(random() % size);
        assert(seg.get(index).sum == values[index]);
    }
}

static_assert(m1une::beats_acted_monoid::IsBeatsActedMonoid<AM>);
static_assert(AM::commutative);
static_assert(!AM::operator_commutative);
static_assert(
    SignedFullWidth::bit_mask() ==
    std::numeric_limits<long long>::max()
);
static_assert(
    UnsignedFullWidth::bit_mask() ==
    std::numeric_limits<unsigned long long>::max()
);

}  // namespace

int main() {
    test_composition();
    test_randomized();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
