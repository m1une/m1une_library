#define PROBLEM "https://judge.yosupo.jp/problem/counting_squarefrees"

#include "../../math/squarefree_count.hpp"

#include <cassert>
#include <cstdint>

#include "../../utilities/fast_io.hpp"

namespace {

bool is_squarefree(uint64_t value) {
    for (uint64_t prime = 2; prime <= value / prime; prime++) {
        if (value % (prime * prime) == 0) return false;
    }
    return true;
}

void test_small() {
    uint64_t expected = 0;
    for (uint64_t value = 1; value <= 5000; value++) {
        if (is_squarefree(value)) expected++;
        if (value % 97 == 0) {
            assert(m1une::math::count_squarefree(value) == expected);
        }
    }
    assert(m1une::math::count_squarefree(0) == 0);
    assert(m1une::math::count_squarefree(1) == 1);
    assert(m1une::math::count_squarefree(10) == 7);
    assert(m1une::math::count_squarefree(100) == 61);
    assert(m1une::math::count_squarefree(1000000) == 607926);
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_small();

    uint64_t n;
    fast_input >> n;
    fast_output << m1une::math::count_squarefree(n) << '\n';
}
