#define PROBLEM "https://judge.yosupo.jp/problem/persistent_range_affine_range_sum"

#include "../../../ds/segtree/persistent_lazy_segtree.hpp"

#include <cassert>
#include <iostream>
#include <optional>
#include <utility>
#include <vector>

#include "../../../acted_monoid/range_add_range_sum.hpp"
#include "../../../acted_monoid/range_affine_range_sum.hpp"
#include "../../../math/modint.hpp"

namespace {

void test_range_add() {
    using AM = m1une::acted_monoid::RangeAddRangeSum<long long>;
    using Seg = m1une::ds::PersistentLazySegtree<AM>;

    Seg seg(std::vector<long long>{1, 2, 3, 4, 5});
    Seg seg1 = seg.apply(1, 4, 10);
    Seg seg2 = seg1.set(2, AM::make(100));
    Seg seg3 = seg2.apply(0, 5, -1);

    auto check = [](const Seg& tree, const std::vector<long long>& a) {
        assert(tree.size() == int(a.size()));
        assert(tree.empty() == a.empty());
        auto values = tree.to_vector();
        assert(int(values.size()) == int(a.size()));
        auto middle = tree.to_vector(1, 4);
        assert(int(middle.size()) == 3);
        long long total = 0;
        for (long long x : a) total += x;
        assert(tree.all_prod().sum == total);
        for (int l = 0; l <= int(a.size()); l++) {
            long long sum = 0;
            for (int r = l; r <= int(a.size()); r++) {
                assert(tree.prod(l, r).sum == sum);
                if (r < int(a.size())) sum += a[r];
            }
        }
        for (int i = 0; i < int(a.size()); i++) {
            assert(tree.get(i).sum == a[i]);
            assert(tree[i].sum == a[i]);
            assert(values[i].sum == a[i]);
            if (1 <= i && i < 4) assert(middle[i - 1].sum == a[i]);
        }
    };

    check(seg, {1, 2, 3, 4, 5});
    check(seg1, {1, 12, 13, 14, 5});
    check(seg2, {1, 12, 100, 14, 5});
    check(seg3, {0, 11, 99, 13, 4});

    assert(seg.prod(0, 5).sum == 15);
    assert(seg1.prod(0, 5).sum == 45);
    assert(seg2.prod(0, 5).sum == 132);
    assert(seg3.prod(0, 5).sum == 127);
    assert(seg.get(2).sum == 3);
    assert(seg1.get(2).sum == 13);
    assert(seg2.get(2).sum == 100);
    assert(seg3.get(2).sum == 99);
    assert(seg1.max_right(0, [](const AM::value_type& x) { return x.sum <= 26; }) == 3);
    assert(seg1.min_left(5, [](const AM::value_type& x) { return x.sum <= 19; }) == 3);

    Seg mixed = seg.copy_range_from(seg2, 1, 4);
    check(mixed, {1, 12, 100, 14, 5});
    assert(seg.prod(0, 5).sum == 15);
    assert(seg2.prod(0, 5).sum == 132);
}

}  // namespace

int main() {
    test_range_add();

    using mint = m1une::math::modint998244353;
    using AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;
    using Seg = m1une::ds::PersistentLazySegtree<AM>;

    int size, query_count;
    std::cin >> size >> query_count;
    std::vector<mint> initial(size);
    for (mint& value : initial) std::cin >> value;

    std::vector<std::optional<Seg>> versions(query_count + 1);
    versions[0].emplace(initial);
    for (int query = 0; query < query_count; query++) {
        int type, version, left, right;
        std::cin >> type >> version;
        version++;
        if (type == 0) {
            mint multiplier, addition;
            std::cin >> left >> right >> multiplier >> addition;
            versions[query + 1] = versions[version]->apply(
                left,
                right,
                std::pair<mint, mint>(multiplier, addition)
            );
        } else if (type == 1) {
            int source;
            std::cin >> source >> left >> right;
            source++;
            versions[query + 1] = versions[version]->copy_range_from(
                *versions[source],
                left,
                right
            );
        } else {
            std::cin >> left >> right;
            std::cout << versions[version]->prod(left, right).sum << '\n';
        }
    }
}
