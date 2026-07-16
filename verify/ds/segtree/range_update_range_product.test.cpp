#define PROBLEM "https://judge.yosupo.jp/problem/range_set_range_composite"

#include "../../../acted_monoid/range_update_range_product.hpp"
#include "../../../ds/segtree/lazy_segtree.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

#include "../../../acted_monoid/concept.hpp"
#include "../../../math/modint.hpp"
#include "../../../utilities/fast_io.hpp"

namespace {

using Mint = m1une::math::modint998244353;
using Function = std::pair<Mint, Mint>;

struct AffineComposition {
    using value_type = Function;

    static value_type id() {
        return {Mint(1), Mint(0)};
    }

    static value_type op(const value_type& left, const value_type& right) {
        return {
            right.first * left.first,
            right.first * left.second + right.second
        };
    }
};

using AM = m1une::acted_monoid::RangeUpdateRangeProduct<AffineComposition>;
static_assert(m1une::acted_monoid::IsActedMonoid<AM>);

Function naive_product(const std::vector<Function>& values, int left, int right) {
    Function result = AffineComposition::id();
    for (int i = left; i < right; i++) {
        result = AffineComposition::op(result, values[i]);
    }
    return result;
}

void test_randomized() {
    std::vector<Function> no_values;
    m1une::ds::LazySegtree<AM> empty(no_values);
    assert(empty.empty());
    assert(empty.prod(0, 0).product == AffineComposition::id());
    assert(empty.prod(0, 0).size == 0);

    std::uint64_t state = 20260716;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 120; trial++) {
        int size = 1 + int(random() % 25);
        std::vector<Function> values(size);
        for (Function& value : values) {
            value = Function{Mint(random() % 20), Mint(random() % 20)};
        }
        m1une::ds::LazySegtree<AM> seg(values);

        for (int operation = 0; operation < 200; operation++) {
            int left = int(random() % (size + 1));
            int right = int(random() % (size + 1));
            if (left > right) std::swap(left, right);

            if ((random() & 1U) == 0) {
                Function value = {Mint(random() % 20), Mint(random() % 20)};
                seg.apply(left, right, value);
                for (int i = left; i < right; i++) values[i] = value;
            } else {
                auto actual = seg.prod(left, right);
                assert(actual.product == naive_product(values, left, right));
                assert(actual.size == right - left);
            }

            auto all = seg.all_prod();
            assert(all.product == naive_product(values, 0, size));
            assert(all.size == size);
        }
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_randomized();

    int n, q;
    fast_input >> n >> q;
    std::vector<Function> functions(n);
    for (Function& function : functions) {
        int a, b;
        fast_input >> a >> b;
        function = Function{Mint(a), Mint(b)};
    }

    m1une::ds::LazySegtree<AM> seg(functions);
    while (q--) {
        int type, left, right;
        fast_input >> type >> left >> right;
        if (type == 0) {
            int c, d;
            fast_input >> c >> d;
            seg.apply(left, right, Function{Mint(c), Mint(d)});
        } else {
            int x;
            fast_input >> x;
            Function function = seg.prod(left, right).product;
            fast_output << function.first * Mint(x) + function.second << '\n';
        }
    }
}
