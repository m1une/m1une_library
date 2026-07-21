#define PROBLEM "https://judge.yosupo.jp/problem/range_add_range_min"

#include "../../../acted_monoid/range_add_range_min.hpp"
#include "../../../ds/segtree/lazy_segtree.hpp"
#include "../../../utilities/fast_io.hpp"

#include <vector>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int size, query_count;
    fast_input >> size >> query_count;
    std::vector<long long> values(size);
    for (long long& value : values) fast_input >> value;

    using ActedMonoid = m1une::acted_monoid::RangeAddRangeMin<long long>;
    m1une::ds::LazySegtree<ActedMonoid> tree(values);
    while (query_count--) {
        int type, left, right;
        fast_input >> type >> left >> right;
        if (type == 0) {
            long long addition;
            fast_input >> addition;
            tree.apply(left, right, addition);
        } else {
            fast_output << tree.prod(left, right) << '\n';
        }
    }
}
