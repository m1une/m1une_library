#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../../../ds/segtree/persistent_segtree.hpp"

#include "../../../utilities/fast_io.hpp"
#include <cassert>
#include <vector>

#include "../../../monoid/add.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    using Seg = m1une::ds::PersistentSegtree<m1une::monoid::Add<long long>>;

    Seg seg(std::vector<long long>{1, 2, 3, 4, 5});
    Seg seg1 = seg.set(2, 10);
    Seg seg2 = seg1.set(0, -1);

    auto check = [](const Seg& tree, const std::vector<long long>& a) {
        assert(tree.size() == int(a.size()));
        assert(tree.empty() == a.empty());
        assert(tree.to_vector() == a);
        assert(tree.to_vector(1, 4) == std::vector<long long>(a.begin() + 1, a.begin() + 4));
        long long total = 0;
        for (long long x : a) total += x;
        assert(tree.all_prod() == total);
        for (int l = 0; l <= int(a.size()); l++) {
            long long sum = 0;
            for (int r = l; r <= int(a.size()); r++) {
                assert(tree.prod(l, r) == sum);
                if (r < int(a.size())) sum += a[r];
            }
        }
        for (int i = 0; i < int(a.size()); i++) {
            assert(tree.get(i) == a[i]);
            assert(tree[i] == a[i]);
        }
    };

    check(seg, {1, 2, 3, 4, 5});
    check(seg1, {1, 2, 10, 4, 5});
    check(seg2, {-1, 2, 10, 4, 5});

    assert(seg.prod(0, 5) == 15);
    assert(seg1.prod(0, 5) == 22);
    assert(seg2.prod(0, 5) == 20);
    assert(seg.get(2) == 3);
    assert(seg1.get(2) == 10);
    assert(seg2.get(0) == -1);
    assert(seg1.max_right(0, [](long long x) { return x <= 13; }) == 3);
    assert(seg1.min_left(5, [](long long x) { return x <= 9; }) == 3);

    {
        Seg base(std::vector<long long>{1, 2, 3, 4});
        std::size_t base_nodes = base.node_count();
        Seg branch = base.set(1, 20);
        std::size_t branch_nodes = base.node_count();
        assert(branch_nodes > base_nodes);
        Seg copy = branch;
        branch.release();
        assert(branch.empty());
        assert(base.node_count() == branch_nodes);
        copy.release();
        assert(base.node_count() == base_nodes);
        Seg reused = base.set(2, 30);
        assert(base.node_count() == branch_nodes);
        reused.release();
        base.release();
        assert(base.node_count() == 0);
    }

    int size, query_count;
    fast_input >> size >> query_count;
    std::vector<long long> values(size);
    for (long long& value : values) fast_input >> value;
    Seg current(values);
    while (query_count--) {
        int type, first, second;
        fast_input >> type >> first >> second;
        if (type == 0) {
            current = current.set(first, current.get(first) + second);
        } else {
            fast_output << current.prod(first, second) << '\n';
        }
    }
}
