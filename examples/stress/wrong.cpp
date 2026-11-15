// Deliberately wrong: equal values are not inversions.
#include "template.hpp"

int main() {
    int n;
    scan(n);
    vi a(n);
    scan(a);
    ll answer = 0;
    FOR(i, n) FOR(j, i + 1, n) answer += a[i] >= a[j];
    print(answer);
}
