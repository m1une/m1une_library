#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

#include "../../string/rolling_hash.hpp"
#include "../../utilities/fast_io.hpp"
#include <string>

using RH = m1une::string::RollingHash<10007, 2305843009213693951LL>;

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    std::string T, P;
    fast_input >> T >> P;

    if (T.size() < P.size()) return 0;

    RH rh(T);

    long long p_hash = RH::compute_hash(P);

    int n = T.size(), m = P.size();
    for (int i = 0; i <= n - m; ++i) {
        if (rh.get(i, i + m) == p_hash) {
            fast_output << i << "\n";
        }
    }

    return 0;
}
