#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "../../../ds/bst/persistent_ordered_multiset.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include "../../../utilities/fast_io.hpp"
#include <set>
#include <vector>

void randomized_test() {
    m1une::ds::PersistentOrderedMultiset<int> tree;
    std::multiset<int> expected;
    std::vector<m1une::ds::PersistentOrderedMultiset<int>> old_versions;
    std::uint64_t state = 123456789;

    for (int query = 0; query < 5000; ++query) {
        state = state * 6364136223846793005ULL + 1442695040888963407ULL;
        const int key = int(state >> 32) % 100;
        const int type = int(state % 5);
        if (type <= 1) {
            tree = tree.insert(key);
            expected.insert(key);
        } else if (type == 2) {
            tree = tree.erase_one(key);
            auto it = expected.find(key);
            if (it != expected.end()) expected.erase(it);
        } else if (type == 3) {
            tree = tree.erase_all(key);
            expected.erase(key);
        } else {
            auto before = tree;
            auto [left, right] = tree.split(key);
            tree = left.merge(right);
            assert(before.to_vector() == tree.to_vector());
        }
        if (query % 100 == 0) old_versions.push_back(tree);
        std::vector<int> values(expected.begin(), expected.end());
        assert(tree.to_vector() == values);
    }

    for (const auto& version : old_versions) {
        const auto values = version.to_vector();
        assert(int(values.size()) == version.size());
        assert(std::is_sorted(values.begin(), values.end()));
    }
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    randomized_test();

    int N, Q;
    fast_input >> N >> Q;

    std::vector<int> a(N);
    std::vector<int> xs;
    xs.reserve(N);
    for (int i = 0; i < N; i++) {
        fast_input >> a[i];
        xs.push_back(a[i]);
    }

    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());

    auto rank = [&](int value) { return int(std::lower_bound(xs.begin(), xs.end(), value) - xs.begin()); };

    std::vector<m1une::ds::PersistentOrderedMultiset<int>> versions(N + 1);
    for (int i = 0; i < N; i++) {
        versions[i + 1] = versions[i].insert(rank(a[i]));
    }

    while (Q--) {
        int l, r, k;
        fast_input >> l >> r >> k;

        int ok = int(xs.size()) - 1;
        int ng = -1;
        while (ok - ng > 1) {
            int mid = (ok + ng) / 2;
            int count_le = versions[r].count_less_equal(mid) - versions[l].count_less_equal(mid);
            if (count_le > k) {
                ok = mid;
            } else {
                ng = mid;
            }
        }

        fast_output << xs[ok] << '\n';
    }
}
