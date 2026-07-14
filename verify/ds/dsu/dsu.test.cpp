#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "../../../utilities/fast_io.hpp"

#include <bits/stdc++.h>
#include <cassert>
#include "../../../ds/dsu/dsu.hpp"
using namespace std;

namespace {

void test_callback() {
    m1une::ds::Dsu dsu(6);
    vector<long long> sum = {1, 2, 3, 4, 5, 6};
    int callback_count = 0;
    auto combine = [&](int new_leader, int absorbed_leader) {
        assert(dsu.leader(new_leader) == new_leader);
        assert(dsu.leader(absorbed_leader) == new_leader);
        sum[new_leader] += sum[absorbed_leader];
        callback_count++;
    };

    assert(dsu.merge(0, 1, combine) == 0);
    assert(dsu.merge(2, 3, combine) == 2);
    assert(dsu.merge(0, 2, combine) == 0);
    assert(sum[dsu.leader(3)] == 10);
    assert(callback_count == 3);

    assert(dsu.merge(1, 3, combine) == 0);
    assert(callback_count == 3);

    assert(dsu.merge(4, 0, combine) == 0);
    assert(sum[dsu.leader(4)] == 15);
    assert(callback_count == 4);
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_callback();

    int N, Q;
    fast_input >> N >> Q;
    m1une::ds::Dsu dsu(N);
    for (int q = 0; q < Q; ++q) {
        int t, u, v;
        fast_input >> t >> u >> v;
        if (t == 0) {
            dsu.merge(u, v);
        } else {
            fast_output << (int)dsu.same(u, v) << '\n';
        }
    }
}
