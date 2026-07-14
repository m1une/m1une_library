#define PROBLEM "https://judge.yosupo.jp/problem/stern_brocot_tree"

#include "../../utilities/fast_io.hpp"

#include <bits/stdc++.h>
using namespace std;

#include "math/stern_brocot_tree.hpp"
using ll = long long;

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    ll T;
    fast_input >> T;
    while (T--) {
        string s;
        fast_input >> s;
        if (s == "ENCODE_PATH") {
            ll a, b;
            fast_input >> a >> b;
            auto path = m1une::math::stern_brocot_path(a, b);
            auto& runs = path.runs;
            fast_output << runs.size();
            for (auto& dir : runs) {
                if (dir.direction == m1une::math::SternBrocotDirection::Left) {
                    fast_output << " L " << dir.count;
                } else {
                    fast_output << " R " << dir.count;
                }
            }
            fast_output << '\n';
        } else if (s == "DECODE_PATH") {
            m1une::math::SternBrocotPath path;
            ll k;
            fast_input >> k;
            while (k--) {
                char c;
                fast_input >> c;
                ll n;
                fast_input >> n;
                if (c == 'L') {
                    path.push(m1une::math::SternBrocotDirection::Left, n);
                } else if (c == 'R') {
                    path.push(m1une::math::SternBrocotDirection::Right, n);
                } else {
                    exit(1);
                }
            }
            auto r = m1une::math::stern_brocot_decode(path);
            fast_output << r.numerator() << ' ' << r.denominator() << '\n';
        } else if (s == "LCA") {
            ll a, b, c, d;
            fast_input >> a >> b >> c >> d;
            auto r = m1une::math::stern_brocot_lca(a, b, c, d);
            fast_output << r.numerator() << ' ' << r.denominator() << '\n';
        } else if (s == "ANCESTOR") {
            ll k, a, b;
            fast_input >> k >> a >> b;
            ll d = m1une::math::stern_brocot_depth(a, b);
            if (d < k) {
                fast_output << "-1\n";
            } else {
                auto r = m1une::math::stern_brocot_ancestor(a, b, d - k);
                fast_output << r.numerator() << ' ' << r.denominator() << '\n';
            }
        } else if (s == "RANGE") {
            ll a, b;
            fast_input >> a >> b;
            auto path = m1une::math::stern_brocot_path(a, b);
            auto bound = m1une::math::stern_brocot_bounds(path);
            fast_output << bound.left.first << ' ' << bound.left.second << ' ' << bound.right.first << ' ' << bound.right.second
                 << '\n';
        } else {
            exit(1);
        }
    }
}
