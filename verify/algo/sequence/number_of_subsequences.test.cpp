#define PROBLEM "https://judge.yosupo.jp/problem/number_of_subsequences"

#include "../../../algo/sequence/number_of_subsequences.hpp"
#include "../../../math/modint.hpp"
#include "../../../utilities/fast_io.hpp"

#include <cassert>
#include <cstdint>
#include <set>
#include <utility>
#include <vector>

namespace {

using Mint = m1une::math::ModInt<998244353>;

long long brute(const std::vector<int>& values) {
    std::set<std::vector<int>> subsequences;
    int n = int(values.size());
    for (int mask = 1; mask < (1 << n); mask++) {
        std::vector<int> subsequence;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) subsequence.push_back(values[i]);
        }
        subsequences.insert(std::move(subsequence));
    }
    return static_cast<long long>(subsequences.size());
}

void test_randomized() {
    std::vector<int> empty;
    assert(m1une::algo::number_of_subsequences<Mint>(empty) == Mint(0));

    std::uint64_t state = 1732050807ULL;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 3000; trial++) {
        int n = int(random() % 13);
        std::vector<int> values(n);
        for (int& value : values) value = int(random() % 7) - 3;
        Mint expected = brute(values);
        assert(
            m1une::algo::number_of_distinct_subsequences<Mint>(values)
            == expected
        );
        assert(
            m1une::algo::number_of_subsequences<Mint>(values) == expected
        );
    }
}

}  // namespace

int main() {
    test_randomized();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    int n = 0;
    input.read(n);
    std::vector<int> values(n);
    for (int& value : values) input.read(value);
    output.println(
        m1une::algo::number_of_subsequences<Mint>(values).val()
    );
}
