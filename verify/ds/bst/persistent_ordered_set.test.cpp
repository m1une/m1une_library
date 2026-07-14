#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "../../../ds/bst/persistent_ordered_set.hpp"

#include <cassert>
#include "../../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    m1une::ds::PersistentOrderedSet<int> pointer_test = {1, 3, 5};
    const int* stable_pointer = pointer_test.lower_bound(3);
    auto pointer_test_next = pointer_test;
    for (int x = 10; x < 1000; x++) pointer_test_next = pointer_test_next.insert(x);
    assert(stable_pointer && *stable_pointer == 3);
    auto [small, large] = pointer_test_next.split(500);
    auto joined = small.merge(large);
    assert(pointer_test_next.size() == joined.size());
    assert(pointer_test_next.to_vector() == joined.to_vector());

    int N, Q;
    fast_input >> N >> Q;

    m1une::ds::PersistentOrderedSet<int> st;
    for (int i = 0; i < N; i++) {
        int a;
        fast_input >> a;
        st = st.insert(a);
    }

    while (Q--) {
        int type, x;
        fast_input >> type >> x;

        if (type == 0) {
            st = st.insert(x);
        } else if (type == 1) {
            st = st.erase(x);
        } else if (type == 2) {
            if (st.size() < x) {
                fast_output << -1 << '\n';
            } else {
                fast_output << st.kth(x - 1) << '\n';
            }
        } else if (type == 3) {
            fast_output << st.count_less_equal(x) << '\n';
        } else if (type == 4) {
            const int* ans = st.max_le(x);
            fast_output << (ans ? *ans : -1) << '\n';
        } else {
            const int* ans = st.min_ge(x);
            fast_output << (ans ? *ans : -1) << '\n';
        }
    }
}
