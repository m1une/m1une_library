#define PROBLEM "https://judge.yosupo.jp/problem/unionfind_with_potential_non_commutative_group"

#include <array>

#include "../../../ds/dsu/potentialized_dsu.hpp"
#include "../../../math/modint.hpp"
#include "../../../utilities/fast_io.hpp"

using mint = m1une::math::modint998244353;

struct Matrix2Group {
    using value_type = std::array<std::array<mint, 2>, 2>;

    static value_type id() {
        value_type result;
        result[0][0] = 1;
        result[1][1] = 1;
        return result;
    }

    static value_type op(const value_type& first, const value_type& second) {
        value_type result;
        for (int i = 0; i < 2; i++) {
            for (int k = 0; k < 2; k++) {
                for (int j = 0; j < 2; j++) {
                    result[i][j] += first[i][k] * second[k][j];
                }
            }
        }
        return result;
    }

    static value_type inv(const value_type& value) {
        value_type result;
        result[0][0] = value[1][1];
        result[0][1] = mint(0) - value[0][1];
        result[1][0] = mint(0) - value[1][0];
        result[1][1] = value[0][0];
        return result;
    }
};

static_assert(m1une::monoid::IsGroup<Matrix2Group>);

int main() {
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    int size = 0;
    int query_count = 0;
    input.read(size, query_count);
    m1une::ds::PotentializedDsu<Matrix2Group> dsu(size);

    while (query_count--) {
        int type = 0;
        int u = 0;
        int v = 0;
        input.read(type, u, v);
        if (type == 0) {
            Matrix2Group::value_type value;
            for (auto& row : value) input.read(row);
            output.println(dsu.merge(v, u, value));
        } else if (!dsu.same(u, v)) {
            output.println(-1);
        } else {
            Matrix2Group::value_type value = dsu.diff(v, u);
            output.println(value[0][0], value[0][1], value[1][0], value[1][1]);
        }
    }
}
