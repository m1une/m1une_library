#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

#include "../../utilities/chmin_chmax.hpp"
#include "../../utilities/compressor.hpp"
#include "../../utilities/y_combinator.hpp"

void test_chmin_chmax() {
    int x = 10;
    assert(m1une::utilities::chmin(x, 3));
    assert(x == 3);
    assert(!m1une::utilities::chmin(x, 7));
    assert(m1une::utilities::chmax(x, 7));
    assert(x == 7);
    assert(!m1une::utilities::chmax(x, 4));
}

void test_compressor() {
    vector<long long> xs = {100, -5, 100, 7};
    m1une::utilities::Compressor<long long> comp(xs);

    assert(comp.size() == 3);
    assert(comp[0] == -5);
    assert(comp[1] == 7);
    assert(comp[2] == 100);
    assert(comp.get(100) == 2);
    assert(comp.lower_bound(8) == 2);
    assert(comp.upper_bound(7) == 2);
    assert(comp.contains(-5));
    assert(!comp.contains(6));

    m1une::utilities::Compressor<int> incremental;
    incremental.add(4);
    incremental.add(1);
    incremental.add(4);
    incremental.build();
    assert(incremental.size() == 2);
    assert(incremental.get(1) == 0);
    assert(incremental.get(4) == 1);

    bool rejected = false;
    try {
        (void)comp.get(6);
    } catch (const out_of_range&) {
        rejected = true;
    }
    assert(rejected);
}

void test_y_combinator() {
    auto fact = m1une::utilities::y_combinator([](auto self, int n) -> long long {
        if (n == 0) return 1;
        return n * self(n - 1);
    });
    assert(fact(10) == 3628800);
}

int main() {
    test_chmin_chmax();
    test_compressor();
    test_y_combinator();

    long long a, b;
    cin >> a >> b;
    cout << a + b << '\n';
}
