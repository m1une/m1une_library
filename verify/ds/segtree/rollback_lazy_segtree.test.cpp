#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <random>
#include <vector>

#include "../../../acted_monoid/range_affine_range_sum.hpp"
#include "../../../acted_monoid/range_ap_add_range_sum.hpp"
#include "../../../acted_monoid/range_bitwise_and_or_xor_range_sum.hpp"
#include "../../../ds/segtree/rollback_lazy_segtree.hpp"
#include "../../../math/modint.hpp"
#include "../../../utilities/fast_io.hpp"

namespace {

using mint = m1une::math::modint998244353;
using Affine = m1une::acted_monoid::RangeAffineRangeSum<mint>;

template <class AM, class Scalar, class MakeAction, class ApplyScalar>
void randomized_test(MakeAction make_action, ApplyScalar apply_scalar) {
    std::mt19937 random(173);
    for (int n : {0, 1, 2, 7, 32, 73}) {
        std::vector<Scalar> expected(n);
        for (auto& value : expected) value = Scalar(random() % 1024);
        m1une::ds::RollbackLazySegtree<AM> seg(expected);
        std::vector<std::vector<Scalar>> states;
        for (int step = 0; step < 2500; ++step) {
            int type = int(random() % 9);
            int left = int(random() % (n + 1));
            int right = int(random() % (n + 1));
            if (right < left) std::swap(left, right);
            if (type == 0) {
                int token = seg.snapshot();
                states.push_back(expected);
                assert(token == int(states.size()));
            } else if (type == 1 && !states.empty()) {
                int index = int(random() % states.size());
                seg.rollback(index + 1);
                expected = states[index];
                states.resize(index + 1);
            } else if (type == 2) {
                seg.clear_history();
                states.clear();
            } else if (type == 3 && n > 0) {
                int pos = int(random() % n);
                expected[pos] = Scalar(random() % 1024);
                seg.set(pos, AM::make(expected[pos]));
            } else if (type == 4 && n > 0) {
                int pos = int(random() % n);
                auto action = make_action(random);
                seg.apply(pos, action);
                expected[pos] = apply_scalar(action, expected[pos], 0);
            } else if (type >= 5) {
                auto action = make_action(random);
                seg.apply(left, right, action);
                for (int i = left; i < right; ++i) {
                    expected[i] = apply_scalar(action, expected[i], i - left);
                }
            }

            // Read through a const reference, including under unpushed tags and
            // nested snapshots. Queries must not mutate the tree or its history.
            const auto& query = seg;
            Scalar sum = 0;
            for (int i = left; i < right; ++i) sum += expected[i];
            assert(query.prod(left, right).sum == sum);
            assert(seg.snapshot_count() == int(states.size()));
            if (n > 0) {
                int pos = int(random() % n);
                assert(query.get(pos).sum == expected[pos]);
                assert(query[pos].sum == expected[pos]);
            }
            if (step % 97 == 0) {
                auto values = seg.to_vector();
                for (int i = 0; i < n; ++i) assert(values[i].sum == expected[i]);
            }
        }
    }
}

void test_queries() {
    randomized_test<Affine, mint>(
        [](auto& random) {
            return Affine::operator_type{mint(random() % 5), mint(random() % 1024)};
        },
        [](const auto& f, mint x, int) { return f.first * x + f.second; }
    );
    using AP = m1une::acted_monoid::RangeApAddRangeSum<long long>;
    randomized_test<AP, long long>(
        [](auto& random) {
            return AP::operator_type{int(random() % 11) - 5, int(random() % 21) - 10};
        },
        [](const auto& f, long long x, int ordinal) {
            return x + f.first * ordinal + f.second;
        }
    );
    using Bits = m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<std::uint32_t>;
    randomized_test<Bits, std::uint32_t>(
        [](auto& random) {
            int type = int(random() % 3);
            std::uint32_t mask = random() & Bits::bit_mask();
            if (type == 0) return Bits::make_and(mask);
            if (type == 1) return Bits::make_or(mask);
            return Bits::make_xor(mask);
        },
        [](const auto& f, std::uint32_t x, int) { return (x & f.and_mask) ^ f.xor_mask; }
    );
    using CompactBits =
        m1une::acted_monoid::RangeBitwiseAndOrXorRangeSum<std::uint32_t, 30, int>;
    randomized_test<CompactBits, std::uint32_t>(
        [](auto& random) {
            return CompactBits::operator_type{
                static_cast<std::uint32_t>(random()) & CompactBits::bit_mask(),
                static_cast<std::uint32_t>(random()) & CompactBits::bit_mask()
            };
        },
        [](const auto& f, std::uint32_t x, int) { return (x & f.and_mask) ^ f.xor_mask; }
    );
}

}  // namespace

int main() {
    test_queries();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    int n, q;
    input >> n >> q;
    std::vector<mint> values(n);
    for (mint& value : values) input >> value;
    m1une::ds::RollbackLazySegtree<Affine> seg(values);
    int state = seg.snapshot();
    while (q--) {
        int type, left, right;
        input >> type >> left >> right;
        if (type == 0) {
            mint a, b;
            input >> a >> b;
            seg.apply(left, right, {a, b});
        } else {
            output << seg.prod(left, right).sum << '\n';
        }
    }
    seg.rollback(state);
    for (int i = 0; i < n; ++i) assert(seg.get(i).sum == values[i]);
}
