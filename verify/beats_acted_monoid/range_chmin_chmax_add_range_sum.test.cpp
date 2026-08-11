#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <numeric>
#include <vector>

#include "../../beats_acted_monoid/concept.hpp"
#include "../../beats_acted_monoid/range_chmin_chmax_add_range_sum.hpp"
#include "../../ds/segtree/segtree_beats.hpp"
#include "../../utilities/fast_io.hpp"

namespace {

using AM =
    m1une::beats_acted_monoid::RangeChminChmaxAddRangeSum<long long>;

long long apply_scalar(const AM::operator_type& f, long long value) {
    return std::clamp(value + f.add, f.lower, f.upper);
}

void test_composition() {
    std::vector<AM::operator_type> operators;
    for (long long value = -10; value <= 10; ++value) {
        operators.emplace_back(AM::make_chmin(value));
        operators.emplace_back(AM::make_chmax(value));
        operators.emplace_back(AM::make_add(value));
    }

    for (const auto& f : operators) {
        for (const auto& g : operators) {
            auto composition = AM::op_comp(f, g);
            for (long long value = -20; value <= 20; ++value) {
                assert(
                    apply_scalar(composition, value) ==
                    apply_scalar(f, apply_scalar(g, value))
                );
            }
        }
    }
}

void test_randomized() {
    std::uint64_t state = 0x123456789abcdef0ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 300; ++trial) {
        int size = int(random() % 80);
        std::vector<long long> values(size);
        for (long long& value : values) {
            value = static_cast<long long>(random() % 201) - 100;
        }
        m1une::ds::SegtreeBeats<AM> seg(values);

        for (int operation = 0; operation < 500; ++operation) {
            int left = int(random() % (size + 1));
            int right = int(random() % (size + 1));
            if (right < left) std::swap(left, right);
            int type = int(random() % 5);
            long long value =
                static_cast<long long>(random() % 101) - 50;

            if (type == 0) {
                seg.apply(left, right, AM::make_chmin(value));
                for (int index = left; index < right; ++index) {
                    values[index] = std::min(values[index], value);
                }
            } else if (type == 1) {
                seg.apply(left, right, AM::make_chmax(value));
                for (int index = left; index < right; ++index) {
                    values[index] = std::max(values[index], value);
                }
            } else if (type == 2) {
                seg.apply(left, right, AM::make_add(value));
                for (int index = left; index < right; ++index) {
                    values[index] += value;
                }
            } else {
                long long expected = std::accumulate(
                    values.begin() + left,
                    values.begin() + right,
                    0LL
                );
                assert(seg.prod(left, right).sum == expected);
            }

            if (operation % 31 == 0) {
                auto actual = seg.to_vector();
                for (int index = 0; index < size; ++index) {
                    assert(actual[index].sum == values[index]);
                }
            }
        }
    }
}

static_assert(m1une::beats_acted_monoid::IsBeatsActedMonoid<AM>);
static_assert(AM::commutative);
static_assert(!AM::operator_commutative);

}  // namespace

int main() {
    test_composition();
    test_randomized();

    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int n, q;
    fast_input >> n >> q;
    std::vector<long long> values(n);
    for (long long& value : values) fast_input >> value;
    m1une::ds::SegtreeBeats<AM> seg(values);

    while (q--) {
        int type, left, right;
        fast_input >> type >> left >> right;
        if (type == 0) {
            long long value;
            fast_input >> value;
            seg.apply(left, right, AM::make_chmin(value));
        } else if (type == 1) {
            long long value;
            fast_input >> value;
            seg.apply(left, right, AM::make_chmax(value));
        } else if (type == 2) {
            long long value;
            fast_input >> value;
            seg.apply(left, right, AM::make_add(value));
        } else {
            fast_output << seg.prod(left, right).sum << '\n';
        }
    }
}
