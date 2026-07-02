#include "ds/segtree/segtree_beats.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <numeric>
#include <utility>
#include <vector>

#include "acted_monoid/beats_wrapper.hpp"

namespace {

struct SumNode {
    long long sum;
    int length;

    friend bool operator==(const SumNode&, const SumNode&) = default;
};

struct ConservativeRangeAdd {
    using value_type = SumNode;
    using operator_type = long long;

    static value_type id() {
        return SumNode{0, 0};
    }

    static value_type op(const value_type& lhs, const value_type& rhs) {
        return SumNode{lhs.sum + rhs.sum, lhs.length + rhs.length};
    }

    static operator_type op_id() {
        return 0;
    }

    static operator_type op_comp(operator_type f, operator_type g) {
        return f + g;
    }

    static value_type mapping(operator_type f, const value_type& x) {
        return SumNode{x.sum + f * x.length, x.length};
    }

    static bool can_apply(operator_type f, const value_type& x) {
        return f == 0 || x.length == 0 || x.length == 1 ||
            (4 <= x.length && -1 <= f && f <= 1);
    }

    static value_type make(long long value) {
        return SumNode{value, 1};
    }
};

struct IndexedRangeAdd {
    using value_type = SumNode;

    struct operator_type {
        long long slope;
        long long constant;
    };

    static value_type id() {
        return SumNode{0, 0};
    }

    static value_type op(const value_type& lhs, const value_type& rhs) {
        return SumNode{lhs.sum + rhs.sum, lhs.length + rhs.length};
    }

    static operator_type op_id() {
        return operator_type{0, 0};
    }

    static operator_type op_comp(
        const operator_type& f,
        const operator_type& g
    ) {
        return operator_type{f.slope + g.slope, f.constant + g.constant};
    }

    static value_type mapping(const operator_type&, const value_type& x) {
        return x;
    }

    static value_type mapping(
        const operator_type& f,
        const value_type& x,
        long long ordinal
    ) {
        long long local_sum = 1LL * x.length * (x.length - 1) / 2;
        return SumNode{
            x.sum + f.slope * (local_sum + ordinal * x.length) +
                f.constant * x.length,
            x.length
        };
    }

    static bool can_apply(const operator_type&, const value_type&) {
        return false;
    }

    static bool can_apply(
        const operator_type&,
        const value_type&,
        long long
    ) {
        return true;
    }

    static operator_type op_shift(
        const operator_type& f,
        long long ordinal
    ) {
        return operator_type{f.slope, f.constant + f.slope * ordinal};
    }

    static value_type make(long long value, int index) {
        return SumNode{value + index, 1};
    }
};

constexpr auto wrapper_op = [](const SumNode& lhs, const SumNode& rhs) {
    return SumNode{lhs.sum + rhs.sum, lhs.length + rhs.length};
};
constexpr auto wrapper_id = [] { return SumNode{0, 0}; };
constexpr auto wrapper_comp = [](long long f, long long g) { return f + g; };
constexpr auto wrapper_op_id = [] { return 0LL; };
constexpr auto wrapper_mapping = [](long long f, const SumNode& x) {
    return SumNode{x.sum + f * x.length, x.length};
};
constexpr auto wrapper_can_apply = [](long long, const SumNode&) {
    return true;
};
constexpr auto wrapper_make = [](long long value) {
    return SumNode{value, 1};
};

using WrappedRangeAdd = m1une::acted_monoid::BeatsWrapper<
    SumNode,
    long long,
    wrapper_op,
    wrapper_id,
    wrapper_comp,
    wrapper_op_id,
    wrapper_mapping,
    wrapper_can_apply,
    wrapper_make
>;

struct ReactorNode {
    long long min_remaining;
    long long vent_count;
    int terminal_count;
    int length;
    long long current_limit;
};

struct ReactorOperator {
    long long pressure_add;
    long long operation_count;
};

struct ReactorActedMonoid {
    using value_type = ReactorNode;
    using operator_type = ReactorOperator;

    static constexpr long long infinity =
        std::numeric_limits<long long>::max() / 4;

    static value_type id() {
        return value_type{infinity, 0, 0, 0, 0};
    }

    static value_type op(const value_type& lhs, const value_type& rhs) {
        return value_type{
            std::min(lhs.min_remaining, rhs.min_remaining),
            lhs.vent_count + rhs.vent_count,
            lhs.terminal_count + rhs.terminal_count,
            lhs.length + rhs.length,
            0
        };
    }

    static operator_type op_id() {
        return operator_type{0, 0};
    }

    static operator_type op_comp(
        const operator_type& f,
        const operator_type& g
    ) {
        return operator_type{
            f.pressure_add + g.pressure_add,
            f.operation_count + g.operation_count
        };
    }

    static bool can_apply(const operator_type& f, const value_type& x) {
        return x.length == 0 || x.terminal_count == x.length ||
            f.pressure_add < x.min_remaining || x.length == 1;
    }

    static value_type mapping(const operator_type& f, value_type x) {
        assert(can_apply(f, x));
        assert(0 <= f.pressure_add);
        assert(0 <= f.operation_count);
        if (x.length == 0) return x;
        if (x.terminal_count == x.length) {
            x.vent_count += 1LL * x.terminal_count * f.operation_count;
            return x;
        }
        if (f.pressure_add < x.min_remaining) {
            x.min_remaining -= f.pressure_add;
            x.vent_count += 1LL * x.terminal_count * f.operation_count;
            return x;
        }

        assert(x.length == 1);
        assert(x.terminal_count == 0);
        assert(1 < x.current_limit);
        assert(0 < f.operation_count);
        ++x.vent_count;
        x.current_limit = std::max(x.current_limit / 2, 1LL);
        if (x.current_limit == 1) {
            x.terminal_count = 1;
            x.min_remaining = infinity;
        } else {
            x.min_remaining = x.current_limit;
        }
        return x;
    }

    static value_type make(long long limit) {
        assert(1 <= limit);
        if (limit == 1) return value_type{infinity, 0, 1, 1, 1};
        return value_type{limit, 0, 0, 1, limit};
    }
};

void test_public_api_and_failure_paths() {
    m1une::ds::SegtreeBeats<ConservativeRangeAdd> empty;
    assert(empty.size() == 0);
    assert(empty.empty());
    assert(empty.prod(0, 0) == ConservativeRangeAdd::id());
    assert(empty.all_prod() == ConservativeRangeAdd::id());
    assert(empty.to_vector().empty());
    assert(empty.max_right(0, [](const SumNode&) { return true; }) == 0);
    assert(empty.min_left(0, [](const SumNode&) { return true; }) == 0);

    m1une::ds::SegtreeBeats<ConservativeRangeAdd> zero(0);
    assert(zero.empty());
    m1une::ds::SegtreeBeats<ConservativeRangeAdd> identities(5);
    assert(identities.size() == 5);

    std::vector<SumNode> nodes;
    for (long long value = 1; value <= 5; ++value) {
        nodes.push_back(SumNode{value, 1});
    }
    std::vector<SumNode> moved_nodes(nodes);
    m1une::ds::SegtreeBeats<ConservativeRangeAdd> moved(
        std::move(moved_nodes)
    );
    assert(moved.all_prod().sum == 15);

    std::vector<long long> four = {1, 2, 3, 4};
    m1une::ds::SegtreeBeats<ConservativeRangeAdd> root(four);
    root.apply(0, 4, 1);
    root.apply(0, 4, 2);
    assert(root.all_prod().sum == 22);
    assert(root.get(0).sum == 4);

    m1une::ds::SegtreeBeats<ConservativeRangeAdd> seg(nodes);
    seg.apply(0, 4, 1);
    seg.apply(0, 4, 2);
    seg.apply(1, 5, -3);
    seg.apply(2, 10);
    seg.set(4, SumNode{20, 1});

    std::vector<long long> expected = {4, 2, 13, 4, 20};
    auto materialized = seg.to_vector();
    for (int i = 0; i < 5; ++i) {
        assert(materialized[i].sum == expected[i]);
        assert(seg.get(i).sum == expected[i]);
        assert(seg[i].sum == expected[i]);
    }
    assert(seg.prod(1, 4).sum == 19);
    assert(seg.prod(2, 2) == ConservativeRangeAdd::id());
    assert(seg.all_prod().sum == 43);
    auto middle = seg.to_vector(1, 4);
    assert(middle.size() == 3);
    assert(middle[0].sum == 2 && middle[2].sum == 4);
    assert(seg.max_right(0, [](const SumNode& x) { return x.sum <= 19; }) == 3);
    assert(seg.min_left(5, [](const SumNode& x) { return x.sum <= 24; }) == 3);

    std::vector<long long> raw = {1, 2, 3};
    m1une::ds::SegtreeBeats<WrappedRangeAdd> wrapped(raw);
    wrapped.apply(0, 3, 4);
    assert(wrapped.all_prod().sum == 18);
}

void test_index_aware_operations() {
    std::vector<long long> raw = {10, 10, 10, 10, 10};
    m1une::ds::SegtreeBeats<IndexedRangeAdd> seg(raw);
    std::vector<long long> expected = {10, 11, 12, 13, 14};

    seg.apply(1, 5, IndexedRangeAdd::operator_type{2, 3});
    for (int i = 1; i < 5; ++i) expected[i] += 2 * (i - 1) + 3;
    seg.apply(2, IndexedRangeAdd::operator_type{5, -1});
    expected[2] += -1;

    auto values = seg.to_vector();
    for (int i = 0; i < 5; ++i) assert(values[i].sum == expected[i]);
    assert(
        seg.all_prod().sum ==
        std::accumulate(expected.begin(), expected.end(), 0LL)
    );
}

struct NaiveReactor {
    long long limit;
    long long pressure;
    long long vents;
};

void apply_naive(NaiveReactor& reactor, long long pressure_add) {
    if (reactor.limit == 1) {
        ++reactor.vents;
        return;
    }
    reactor.pressure += pressure_add;
    if (reactor.limit <= reactor.pressure) {
        ++reactor.vents;
        reactor.limit = std::max(reactor.limit / 2, 1LL);
        reactor.pressure = 0;
    }
}

void check_reactors(
    m1une::ds::SegtreeBeats<ReactorActedMonoid>& seg,
    const std::vector<NaiveReactor>& naive
) {
    auto values = seg.to_vector();
    long long total = 0;
    for (int i = 0; i < int(naive.size()); ++i) {
        total += naive[i].vents;
        assert(values[i].vent_count == naive[i].vents);
        assert(values[i].current_limit == naive[i].limit);
        assert(values[i].terminal_count == (naive[i].limit == 1));
        if (naive[i].limit == 1) {
            assert(values[i].min_remaining == ReactorActedMonoid::infinity);
        } else {
            assert(
                values[i].min_remaining ==
                naive[i].limit - naive[i].pressure
            );
        }
    }
    assert(seg.all_prod().vent_count == total);
}

void test_reactor_randomized() {
    std::uint64_t state = 0x106084123456789ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 300; ++trial) {
        int n = 1 + int(random() % 12);
        std::vector<long long> limits(n);
        std::vector<NaiveReactor> naive(n);
        for (int i = 0; i < n; ++i) {
            limits[i] = 1 + static_cast<long long>(random() % 24);
            naive[i] = NaiveReactor{limits[i], 0, 0};
        }
        m1une::ds::SegtreeBeats<ReactorActedMonoid> seg(limits);

        for (int operation = 0; operation < 500; ++operation) {
            int left = int(random() % (n + 1));
            int right = int(random() % (n + 1));
            if (right < left) std::swap(left, right);
            if (random() % 4 != 0) {
                long long pressure_add =
                    static_cast<long long>(random() % 20);
                seg.apply(
                    left,
                    right,
                    ReactorOperator{pressure_add, 1}
                );
                for (int i = left; i < right; ++i) {
                    apply_naive(naive[i], pressure_add);
                }
            } else {
                long long expected = 0;
                for (int i = left; i < right; ++i) {
                    expected += naive[i].vents;
                }
                assert(seg.prod(left, right).vent_count == expected);
            }
            if (operation % 17 == 0) check_reactors(seg, naive);
        }
        check_reactors(seg, naive);
    }
}

}  // namespace

int main() {
    test_public_api_and_failure_paths();
    test_index_aware_operations();
    test_reactor_randomized();
}
