#define PROBLEM "https://judge.yosupo.jp/problem/range_parallel_unionfind"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../../../ds/dsu/dsu.hpp"
#include "../../../ds/dsu/range_parallel_dsu.hpp"
#include "../../../math/modint.hpp"

namespace {

void test_randomized() {
    uint64_t state = 0xa0761d6478bd642fULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 200; trial++) {
        const int size = int(random() % 60) + 1;
        m1une::ds::RangeParallelDsu range_dsu(size);
        m1une::ds::Dsu naive(size);
        assert(range_dsu.size() == size);
        assert(!range_dsu.empty());

        for (int query = 0; query < 500; query++) {
            const int length = int(random() % (size + 1));
            const int first = int(random() % (size - length + 1));
            const int second = int(random() % (size - length + 1));

            int expected_merges = 0;
            for (int offset = 0; offset < length; offset++) {
                if (!naive.same(first + offset, second + offset)) {
                    naive.merge(first + offset, second + offset);
                    expected_merges++;
                }
            }

            int callback_count = 0;
            const int merges = range_dsu.merge(
                first, second, length,
                [&](int leader, int absorbed) {
                    assert(range_dsu.leader(leader) == leader);
                    assert(range_dsu.leader(absorbed) == leader);
                    callback_count++;
                });
            assert(merges == expected_merges);
            assert(callback_count == expected_merges);

            for (int first_vertex = 0; first_vertex < size; first_vertex++) {
                assert(range_dsu.group_size(first_vertex) ==
                       naive.size(first_vertex));
                for (int second_vertex = 0; second_vertex < size;
                     second_vertex++) {
                    assert(range_dsu.same(first_vertex, second_vertex) ==
                           naive.same(first_vertex, second_vertex));
                }
            }
        }
        assert(range_dsu.component_count() == int(naive.groups().size()));
    }
}

void test_overloads() {
    m1une::ds::RangeParallelUnionFind dsu(8);
    assert(dsu.merge_ranges(0, 4, 4, 8) == 4);
    assert(dsu.same(0, 4));
    assert(dsu.same(3, 7));
    assert(dsu.merge(0, 1) == 1);
    assert(dsu.group_size(0) == 4);
    assert(dsu.merge(0, 4, 4) == 0);

    m1une::ds::RangeParallelDsu empty;
    assert(empty.empty());
    assert(empty.component_count() == 0);
    assert(empty.merge(0, 0, 0) == 0);
}

}  // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    test_randomized();
    test_overloads();

    using Mint = m1une::math::modint998244353;
    int size, query_count;
    std::cin >> size >> query_count;
    std::vector<Mint> component_sum(size);
    for (Mint& value : component_sum) std::cin >> value;

    m1une::ds::RangeParallelDsu dsu(size);
    Mint answer = 0;
    auto on_merge = [&](int leader, int absorbed) {
        answer += component_sum[leader] * component_sum[absorbed];
        component_sum[leader] += component_sum[absorbed];
    };

    while (query_count--) {
        int length, first, second;
        std::cin >> length >> first >> second;
        dsu.merge(first, second, length, on_merge);
        std::cout << answer << '\n';
    }
}
