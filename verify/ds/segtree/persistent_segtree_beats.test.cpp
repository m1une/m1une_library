#define PROBLEM "https://judge.yosupo.jp/problem/persistent_range_affine_range_sum"

#include "../../../ds/segtree/persistent_segtree_beats.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <numeric>
#include <optional>
#include <utility>
#include <vector>

#include "../../../acted_monoid/range_affine_range_sum.hpp"
#include "../../../acted_monoid/range_ap_add_range_sum.hpp"
#include "../../../math/modint.hpp"
#include "../../../utilities/fast_io.hpp"

namespace {

struct ChminRangeSum {
    struct value_type {
        long long sum;
        long long maximum;
        long long second_maximum;
        int maximum_count;
        int length;
    };

    using operator_type = long long;

    static constexpr long long negative_infinity =
        std::numeric_limits<long long>::lowest();
    static constexpr long long positive_infinity =
        std::numeric_limits<long long>::max();

    static value_type id() {
        return {0, negative_infinity, negative_infinity, 0, 0};
    }

    static value_type op(const value_type& left, const value_type& right) {
        value_type result;
        result.sum = left.sum + right.sum;
        result.length = left.length + right.length;
        if (left.maximum == right.maximum) {
            result.maximum = left.maximum;
            result.second_maximum = std::max(
                left.second_maximum,
                right.second_maximum
            );
            result.maximum_count =
                left.maximum_count + right.maximum_count;
        } else if (left.maximum < right.maximum) {
            result.maximum = right.maximum;
            result.second_maximum = std::max(
                left.maximum,
                right.second_maximum
            );
            result.maximum_count = right.maximum_count;
        } else {
            result.maximum = left.maximum;
            result.second_maximum = std::max(
                left.second_maximum,
                right.maximum
            );
            result.maximum_count = left.maximum_count;
        }
        return result;
    }

    static operator_type op_id() {
        return positive_infinity;
    }

    static operator_type op_comp(operator_type f, operator_type g) {
        return std::min(f, g);
    }

    static bool can_apply(operator_type f, const value_type& value) {
        return value.maximum <= f || value.second_maximum < f;
    }

    static value_type mapping(operator_type f, value_type value) {
        if (value.maximum <= f) return value;
        assert(value.second_maximum < f);
        value.sum +=
            (f - value.maximum) * static_cast<long long>(
                value.maximum_count
            );
        value.maximum = f;
        return value;
    }

    static value_type make(long long value) {
        return {value, value, negative_infinity, 1, 1};
    }
};

struct RangeApAddRangeSumBeats
    : m1une::acted_monoid::RangeApAddRangeSum<long long> {
    static bool can_apply(
        const operator_type&,
        const value_type&
    ) {
        return true;
    }
};

void check_version(
    const m1une::ds::PersistentSegtreeBeats<ChminRangeSum>& seg,
    const std::vector<long long>& expected
) {
    assert(seg.size() == int(expected.size()));
    assert(seg.empty() == expected.empty());
    assert(
        seg.all_prod().sum
        == std::accumulate(expected.begin(), expected.end(), 0LL)
    );

    std::vector<ChminRangeSum::value_type> materialized =
        seg.to_vector();
    assert(materialized.size() == expected.size());
    for (int index = 0; index < int(expected.size()); ++index) {
        assert(materialized[index].sum == expected[index]);
        assert(seg.get(index).sum == expected[index]);
        assert(seg[index].sum == expected[index]);
    }

    int slice_left = int(expected.size()) / 4;
    int slice_right = int(expected.size()) * 3 / 4;
    std::vector<ChminRangeSum::value_type> slice =
        seg.to_vector(slice_left, slice_right);
    assert(int(slice.size()) == slice_right - slice_left);
    for (int index = slice_left; index < slice_right; ++index) {
        assert(slice[index - slice_left].sum == expected[index]);
    }

    for (int left = 0; left <= int(expected.size()); ++left) {
        long long sum = 0;
        for (int right = left; right <= int(expected.size()); ++right) {
            assert(seg.prod(left, right).sum == sum);
            if (right < int(expected.size())) sum += expected[right];
        }
    }

    if (!expected.empty()) {
        int left = int(expected.size()) / 3;
        long long limit = 0;
        int expected_right = left;
        while (
            expected_right < int(expected.size()) &&
            limit + expected[expected_right] <= 60
        ) {
            limit += expected[expected_right++];
        }
        assert(seg.max_right(
            left,
            [](const ChminRangeSum::value_type& value) {
                return value.sum <= 60;
            }
        ) == expected_right);

        int right = int(expected.size()) * 2 / 3 + 1;
        right = std::min(right, int(expected.size()));
        limit = 0;
        int expected_left = right;
        while (
            expected_left > 0 &&
            limit + expected[expected_left - 1] <= 60
        ) {
            limit += expected[--expected_left];
        }
        assert(seg.min_left(
            right,
            [](const ChminRangeSum::value_type& value) {
                return value.sum <= 60;
            }
        ) == expected_left);
    }
}

void test_randomized_persistence() {
    using Seg = m1une::ds::PersistentSegtreeBeats<ChminRangeSum>;

    Seg empty;
    assert(empty.empty());
    assert(empty.size() == 0);
    assert(empty.all_prod().sum == 0);
    assert(empty.prod(0, 0).sum == 0);
    assert(empty.to_vector().empty());
    assert(empty.max_right(0, [](const ChminRangeSum::value_type&) {
        return true;
    }) == 0);
    assert(empty.min_left(0, [](const ChminRangeSum::value_type&) {
        return true;
    }) == 0);

    std::uint64_t state = 0x6a09e667f3bcc909ULL;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 80; ++trial) {
        int size = int(random() % 20) + 1;
        std::vector<long long> initial(size);
        for (long long& value : initial) {
            value = static_cast<long long>(random() % 51);
        }

        std::vector<std::optional<Seg>> versions;
        std::vector<std::vector<long long>> naive_versions;
        versions.emplace_back(std::in_place, initial);
        naive_versions.push_back(initial);

        for (int operation = 0; operation < 240; ++operation) {
            int base = int(random() % versions.size());
            int left = int(random() % (size + 1));
            int right = int(random() % (size + 1));
            if (right < left) std::swap(left, right);
            int type = int(random() % 5);

            std::vector<long long> next = naive_versions[base];
            if (type <= 1) {
                long long upper = static_cast<long long>(random() % 51);
                versions.push_back(
                    versions[base]->apply(left, right, upper)
                );
                for (int index = left; index < right; ++index) {
                    next[index] = std::min(next[index], upper);
                }
                naive_versions.push_back(std::move(next));
            } else if (type == 2) {
                int index = int(random() % size);
                long long value = static_cast<long long>(random() % 51);
                versions.push_back(versions[base]->set(
                    index,
                    ChminRangeSum::make(value)
                ));
                next[index] = value;
                naive_versions.push_back(std::move(next));
            } else if (type == 3) {
                int source = int(random() % versions.size());
                versions.push_back(versions[base]->copy_range_from(
                    *versions[source],
                    left,
                    right
                ));
                std::copy(
                    naive_versions[source].begin() + left,
                    naive_versions[source].begin() + right,
                    next.begin() + left
                );
                naive_versions.push_back(std::move(next));
            } else {
                long long expected = std::accumulate(
                    next.begin() + left,
                    next.begin() + right,
                    0LL
                );
                assert(versions[base]->prod(left, right).sum == expected);
            }

            int checked = int(random() % versions.size());
            check_version(*versions[checked], naive_versions[checked]);
        }
        check_version(*versions[0], initial);

        Seg base(initial);
        std::size_t before = base.node_count();
        {
            Seg disposable = base.apply(0, size, 17);
            assert(base.node_count() >= before);
            check_version(base, initial);
        }
        assert(base.node_count() == before);

        Seg released = base;
        released.release();
        assert(released.empty());
        assert(base.node_count() == before);
        check_version(base, initial);
    }
}

void test_index_aware_action() {
    using Seg =
        m1une::ds::PersistentSegtreeBeats<RangeApAddRangeSumBeats>;
    Seg original(std::vector<long long>{1, 2, 3, 4, 5});
    Seg updated = original.apply(1, 5, std::pair<long long, long long>(2, 3));
    std::vector<long long> expected{1, 5, 8, 11, 14};
    assert(original.all_prod().sum == 15);
    assert(updated.all_prod().sum == 39);
    for (int index = 0; index < 5; ++index) {
        assert(updated[index].sum == expected[index]);
    }
}

}  // namespace

using mint = m1une::math::modint998244353;

struct RangeAffineRangeSumBeats
    : m1une::acted_monoid::RangeAffineRangeSum<mint> {
    static bool can_apply(
        const operator_type&,
        const value_type&
    ) {
        return true;
    }
};

int main() {
    test_randomized_persistence();
    test_index_aware_action();

    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int size, query_count;
    fast_input >> size >> query_count;
    std::vector<mint> initial(size);
    for (mint& value : initial) fast_input >> value;

    using Seg =
        m1une::ds::PersistentSegtreeBeats<RangeAffineRangeSumBeats>;
    std::vector<std::optional<Seg>> versions(query_count + 1);
    versions[0].emplace(initial);
    for (int query = 0; query < query_count; ++query) {
        int type, version, left, right;
        fast_input >> type >> version;
        ++version;
        if (type == 0) {
            mint multiplier, addition;
            fast_input >> left >> right >> multiplier >> addition;
            versions[query + 1] = versions[version]->apply(
                left,
                right,
                std::pair<mint, mint>(multiplier, addition)
            );
        } else if (type == 1) {
            int source;
            fast_input >> source >> left >> right;
            ++source;
            versions[query + 1] = versions[version]->copy_range_from(
                *versions[source],
                left,
                right
            );
        } else {
            fast_input >> left >> right;
            fast_output << versions[version]->prod(left, right).sum << '\n';
        }
    }
}
