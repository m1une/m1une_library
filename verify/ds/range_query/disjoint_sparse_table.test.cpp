#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include "../../../ds/range_query/disjoint_sparse_table.hpp"
#include "../../../monoid/add.hpp"

#include "../../../utilities/fast_io.hpp"
#include <vector>

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int N, Q;
    fast_input >> N >> Q;

    std::vector<long long> A(N);
    for (int i = 0; i < N; ++i) {
        fast_input >> A[i];
    }

    m1une::ds::DisjointSparseTable<m1une::monoid::Add<long long>> dst(A);

    for (int q = 0; q < Q; ++q) {
        int l, r;
        fast_input >> l >> r;

        fast_output << dst.prod(l, r) << "\n";
    }

    return 0;
}
