#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP2_1_C"

#include "../../../utilities/fast_io.hpp"

#include <bits/stdc++.h>
using namespace std;

#include "../../../ds/dynamic_array/dynamic_array.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    int cursor = 0;
    m1une::ds::DynamicArray<int> L;
    int q;
    fast_input >> q;
    while (q--) {
        int t;
        fast_input >> t;
        if (t == 0) {
            int x;
            fast_input >> x;
            L.insert(cursor, x);
        } else if (t == 1) {
            int d;
            fast_input >> d;
            cursor += d;
        } else {
            L.erase(cursor);
        }
    }
    vector<int> ans = L.to_vector();
    for (int x : ans) {
        fast_output << x << '\n';
    }
}
