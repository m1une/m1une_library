#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

#include "../../acted_monoid/concept.hpp"
#include "../../acted_monoid/range_bitwise_and_or_xor_range_sum.hpp"
#include "../../ds/segtree/lazy_segtree.hpp"

namespace {

using AM = m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<long long, 10>;
using SignedFullWidth = m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<long long, 63>;
using UnsignedFullWidth =
    m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<unsigned long long, 64>;

long long apply_scalar(const AM::operator_type& f, long long x) {
    return (x & f.and_mask) ^ f.xor_mask;
}

void test_composition() {
    std::vector<AM::operator_type> operators;
    for (long long mask = 0; mask < 32; ++mask) {
        operators.push_back(AM::make_and(mask));
        operators.push_back(AM::make_or(mask));
        operators.push_back(AM::make_xor(mask));
    }

    for (const auto& f : operators) {
        for (const auto& g : operators) {
            auto composition = AM::op_comp(f, g);
            for (long long x = 0; x < 32; ++x) {
                assert(apply_scalar(composition, x) == apply_scalar(f, apply_scalar(g, x)));
            }
        }
    }
}

void test_randomized() {
    constexpr int n = 73;
    constexpr long long mask = (1LL << 10) - 1;
    std::uint64_t state = 123456789;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    std::vector<long long> values(n);
    for (long long& value : values) value = static_cast<long long>(random() & mask);
    m1une::ds::LazySegtree<AM> seg(values);

    for (int step = 0; step < 5000; ++step) {
        int l = static_cast<int>(random() % (n + 1));
        int r = static_cast<int>(random() % (n + 1));
        if (r < l) std::swap(l, r);

        if (random() % 4 != 0) {
            long long operand = static_cast<long long>(random() & mask);
            int type = static_cast<int>(random() % 3);
            AM::operator_type f = AM::op_id();
            if (type == 0) {
                f = AM::make_and(operand);
                for (int i = l; i < r; ++i) values[i] &= operand;
            } else if (type == 1) {
                f = AM::make_or(operand);
                for (int i = l; i < r; ++i) values[i] |= operand;
            } else {
                f = AM::make_xor(operand);
                for (int i = l; i < r; ++i) values[i] ^= operand;
            }
            seg.apply(l, r, f);
        } else {
            long long expected = 0;
            for (int i = l; i < r; ++i) expected += values[i];
            assert(seg.prod(l, r).sum == expected);
        }

        int index = static_cast<int>(random() % n);
        assert(seg.get(index).sum == values[index]);
    }
}

static_assert(m1une::acted_monoid::IsActedMonoid<AM>);
static_assert(AM::commutative);
static_assert(!AM::operator_commutative);
static_assert(SignedFullWidth::bit_mask() == std::numeric_limits<long long>::max());
static_assert(UnsignedFullWidth::bit_mask() == std::numeric_limits<unsigned long long>::max());

}  // namespace

int main() {
    test_composition();
    test_randomized();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
