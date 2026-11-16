#define PROBLEM "https://yukicoder.me/problems/no/1036"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <numeric>
#include <vector>

#include "../../acted_monoid/concept.hpp"
#include "../../acted_monoid/range_add_range_gcd.hpp"
#include "../../ds/segtree/lazy_segtree.hpp"
#include "../../utilities/fast_io.hpp"

namespace {

using AM = m1une::acted_monoid::RangeAddRangeGcd<long long>;

static_assert(m1une::acted_monoid::IsActedMonoid<AM>);
static_assert(AM::commutative && AM::operator_commutative);
static_assert(AM::gcd(AM::id()) == 0);
static_assert(AM::gcd(AM::make(-12)) == 12);
static_assert(AM::gcd(AM::mapping(2, AM::op(AM::make(6), AM::make(10)))) == 4);

template <typename Node>
bool same(const Node& a, const Node& b) {
    return a.min == b.min && a.diff_gcd == b.diff_gcd && a.empty == b.empty;
}

std::uint64_t state = 3141592653589793ULL;
std::uint64_t random_number() {
    state ^= state << 7;
    state ^= state >> 9;
    return state;
}

void test_laws() {
    auto random_node = []() {
        auto node = AM::id();
        int n = int(random_number() % 8);
        for (int i = 0; i < n; ++i) {
            node = AM::op(node, AM::make(static_cast<long long>(random_number() % 101) - 50));
        }
        return node;
    };
    for (int trial = 0; trial < 5000; ++trial) {
        auto a = random_node(), b = random_node(), c = random_node();
        long long f = static_cast<long long>(random_number() % 101) - 50;
        long long g = static_cast<long long>(random_number() % 101) - 50;
        long long h = static_cast<long long>(random_number() % 101) - 50;
        assert(same(AM::op(AM::id(), a), a));
        assert(same(AM::op(a, AM::id()), a));
        assert(same(AM::op(a, b), AM::op(b, a)));
        assert(same(AM::op(AM::op(a, b), c), AM::op(a, AM::op(b, c))));
        assert(same(AM::mapping(f, AM::id()), AM::id()));
        assert(same(AM::mapping(AM::op_id(), a), a));
        assert(AM::op_comp(f, AM::op_id()) == f);
        assert(AM::op_comp(AM::op_id(), f) == f);
        assert(AM::op_comp(f, g) == AM::op_comp(g, f));
        assert(AM::op_comp(AM::op_comp(f, g), h) == AM::op_comp(f, AM::op_comp(g, h)));
        assert(same(AM::mapping(AM::op_comp(f, g), a), AM::mapping(f, AM::mapping(g, a))));
        assert(same(AM::mapping(f, AM::op(a, b)),
                    AM::op(AM::mapping(f, a), AM::mapping(f, b))));
    }
}

template <typename T>
void check_range(m1une::ds::LazySegtree<m1une::acted_monoid::RangeAddRangeGcd<T>>& seg,
                 const std::vector<T>& values, int l, int r) {
    using M = m1une::acted_monoid::RangeAddRangeGcd<T>;
    T expected = 0;
    for (int i = l; i < r; ++i) expected = std::gcd(expected, values[i]);
    auto node = seg.prod(l, r);
    assert(M::gcd(node) == expected);
    assert(node.empty == (l == r));
    if (l < r) {
        T minimum = *std::min_element(values.begin() + l, values.begin() + r);
        T differences = 0;
        for (int i = l; i < r; ++i) differences = std::gcd(differences, T(values[i] - minimum));
        assert(node.min == minimum && node.diff_gcd == differences);
    } else {
        assert(same(node, M::id()));
    }
}

template <typename T>
void test_randomized() {
    using M = m1une::acted_monoid::RangeAddRangeGcd<T>;
    for (int n : {0, 1, 2, 3, 7, 16, 31, 32, 33, 73}) {
        std::vector<T> values(n, T(0));
        m1une::ds::LazySegtree<M> seg(values);
        for (int step = 0; step < 2000; ++step) {
            int l = int(random_number() % (n + 1));
            int r = int(random_number() % (n + 1));
            if (r < l) std::swap(l, r);
            T delta = T(static_cast<long long>(random_number() % 201) - 100);
            int type = int(random_number() % 5);
            if (type <= 1) {
                if (type == 0) l = 0, r = n;
                seg.apply(l, r, delta);
                for (int i = l; i < r; ++i) values[i] += delta;
            } else if (n > 0 && type <= 3) {
                int p = int(random_number() % n);
                if (type == 2) {
                    seg.set(p, M::make(delta));
                    values[p] = delta;
                } else {
                    seg.apply(p, delta);
                    values[p] += delta;
                }
                assert(same(seg.get(p), M::make(values[p])));
            }
            check_range(seg, values, l, r);
            check_range(seg, values, 0, n);
            assert(same(seg.prod(0, n), seg.all_prod()));
        }
        for (int l = 0; l <= n; ++l) {
            for (int r = l; r <= n; ++r) check_range(seg, values, l, r);
        }
    }
}

void test_boundaries() {
    assert(!AM::make(0).empty);
    assert(same(AM::mapping(17, AM::id()), AM::id()));
    assert(AM::gcd(AM::mapping(-12, AM::make(12))) == 0);
    for (long long value : {0LL, -12LL, 12LL,
                            std::numeric_limits<long long>::min() + 1,
                            std::numeric_limits<long long>::max()}) {
        std::vector<long long> values(5, value);
        m1une::ds::LazySegtree<AM> seg(values);
        check_range(seg, values, 0, 5);
        check_range(seg, values, 1, 4);
        // Shift to zero, then away from zero without overflowing composed tags.
        seg.apply(0, 5, -value);
        assert(AM::gcd(seg.all_prod()) == 0);
        seg.apply(0, 5, value > 0 ? 12 : -12);
        assert(AM::gcd(seg.all_prod()) == 12);
    }
    long long large = std::numeric_limits<long long>::max() / 3;
    auto mixed = AM::op(AM::make(-large), AM::make(large));
    assert(mixed.min == -large && mixed.diff_gcd == 2 * large);
    assert(AM::gcd(mixed) == large);
}

}  // namespace

int main() {
    test_laws();
    test_randomized<int>();
    test_randomized<long long>();
    test_boundaries();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    int n;
    input >> n;
    std::vector<long long> values(n);
    for (long long& value : values) input >> value;
    m1une::ds::LazySegtree<AM> seg(values);
    long long answer = 0;
    for (int l = 0; l < n; ++l) {
        int r = seg.max_right(l, [](const AM::value_type& x) { return AM::gcd(x) != 1; });
        answer += n - r;
    }
    output << answer << '\n';
}
