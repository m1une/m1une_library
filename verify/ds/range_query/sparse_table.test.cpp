#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../../../ds/range_query/sparse_table.hpp"
#include "../../../monoid/min.hpp"

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

    m1une::ds::SparseTable<m1une::monoid::Min<long long>> st(A);

    for (int q = 0; q < Q; ++q) {
        int l, r;
        fast_input >> l >> r;

        fast_output << st.prod(l, r) << "\n";
    }

    return 0;
}
