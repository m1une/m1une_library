#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <numeric>
#include <random>
#include <vector>

#include "../../../algo/enumeration/permutation_lexicographical_order.hpp"
#include "../../../utilities/fast_io.hpp"

void test_exhaustively() {
    for (int size = 0; size <= 9; size++) {
        std::vector<int> permutation(size);
        std::iota(permutation.begin(), permutation.end(), 0);
        std::uint64_t expected_rank = 0;
        do {
            assert(
                m1une::algo::permutation_lexicographical_rank(permutation) ==
                expected_rank
            );
            assert(
                m1une::algo::kth_lexicographical_permutation(
                    size, expected_rank
                ) == permutation
            );
            expected_rank++;
        } while (
            std::next_permutation(permutation.begin(), permutation.end())
        );
    }
}

void test_checked_interfaces() {
    using m1une::algo::checked_kth_lexicographical_permutation;
    using m1une::algo::checked_permutation_lexicographical_rank;

    assert(!checked_permutation_lexicographical_rank(
        std::vector<int>{0, 0, 2}
    ));
    assert(!checked_permutation_lexicographical_rank(
        std::vector<int>{0, 1, 3}
    ));
    assert(!checked_permutation_lexicographical_rank(
        std::vector<int>{0, -1, 2}
    ));
    assert(!checked_kth_lexicographical_permutation(3, std::uint64_t(6)));
    assert(!checked_kth_lexicographical_permutation(
        -1, std::uint64_t(0)
    ));

    assert(
        checked_permutation_lexicographical_rank(std::vector<int>()) ==
        std::uint64_t(0)
    );
    assert(
        checked_kth_lexicographical_permutation(0, std::uint64_t(0)) ==
        std::vector<int>()
    );

    std::vector<int> descending_twenty(20);
    std::iota(descending_twenty.rbegin(), descending_twenty.rend(), 0);
    assert(
        checked_permutation_lexicographical_rank(descending_twenty) ==
        std::uint64_t(2432902008176640000ULL - 1)
    );

    std::vector<int> descending_twenty_one(21);
    std::iota(
        descending_twenty_one.rbegin(), descending_twenty_one.rend(), 0
    );
    assert(!checked_permutation_lexicographical_rank(
        descending_twenty_one
    ));

    const std::uint64_t largest =
        std::numeric_limits<std::uint64_t>::max();
    assert(!checked_kth_lexicographical_permutation(20, largest));
    const auto large = checked_kth_lexicographical_permutation(21, largest);
    assert(large);
    assert(checked_permutation_lexicographical_rank(*large) == largest);

    const auto narrow =
        checked_kth_lexicographical_permutation(300, std::uint8_t(255));
    assert(narrow);
    assert(
        checked_permutation_lexicographical_rank<std::uint8_t>(*narrow) ==
        std::uint8_t(255)
    );
}

void test_random_round_trips() {
    std::mt19937_64 random(123456789);
    for (int iteration = 0; iteration < 10000; iteration++) {
        const int size = int(random() % 80) + 21;
        const std::uint64_t rank = random();
        const std::vector<int> permutation =
            m1une::algo::kth_lexicographical_permutation(size, rank);
        assert(
            m1une::algo::permutation_lexicographical_rank(permutation) ==
            rank
        );
    }
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_exhaustively();
    test_checked_interfaces();
    test_random_round_trips();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
