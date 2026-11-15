#include "pch.hpp"

auto& fastin = m1une::template_io::input();
auto& fastout = m1une::template_io::output();

void solve() {
    int n;
    scan(n);
    vi a(n);
    scan(a);
    ll answer = 0;
    FOR(i, n) FOR(j, i + 1, n) answer += a[i] > a[j];
    print(answer);
}

int main() {
    int T = 1;
    // scan(T);
    while (T--) solve();
    return 0;
}
