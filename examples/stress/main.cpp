#include "pch.hpp"
#include "algo/sequence/inversion_count.hpp"

auto& fastin = m1une::template_io::input();
auto& fastout = m1une::template_io::output();

void solve() {
    int n;
    scan(n);
    vi a(n);
    scan(a);
    print(m1une::algo::inversion_count(a));
}

int main() {
    int T = 1;
    // scan(T);
    while (T--) solve();
    return 0;
}
