#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include "../../graph/doubling.hpp"

#include <cassert>
#include <cstdint>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include "../../math/modint.hpp"
#include "../../monoid/add.hpp"
#include "../../monoid/affine.hpp"
#include "../../utilities/fast_io.hpp"

namespace {

template <class Monoid>
void check_walk(const m1une::graph::Doubling<Monoid>& doubling,
                const std::vector<int>& successor,
                const std::vector<typename Monoid::value_type>& values,
                int start, std::uint64_t steps) {
    int vertex = start;
    auto product = Monoid::id();
    for (std::uint64_t step = 0; step < steps && vertex != -1; ++step) {
        product = Monoid::op(product, values[vertex]);
        vertex = successor[vertex];
    }
    auto result = doubling.walk(start, steps);
    assert(result.vertex == vertex);
    assert(result.product == product);
    assert(doubling.jump(start, steps) == vertex);
    assert(doubling.prod(start, steps) == product);
}

struct Concat {
    using value_type = std::string;
    static value_type id() { return ""; }
    static value_type op(const value_type& a, const value_type& b) { return a + b; }
};

struct Box {
    int value;
    explicit Box(int x) : value(x) {}
};

struct BoxAdd {
    using value_type = Box;
    static Box id() { return Box(0); }
    static Box op(const Box& a, const Box& b) { return Box(a.value + b.value); }
};

void test_boundaries() {
    using Sum = m1une::monoid::Add<long long>;
    m1une::graph::Doubling<Sum> empty;
    assert(empty.empty() && empty.size() == 0);
    assert(empty.levels() == 0 && empty.max_steps() == 0);
    assert(empty.jump(-1, 0) == -1 && empty.prod(-1, 0) == 0);

    std::vector<int> successor = {1, 2, -1};
    std::vector<long long> values = {2, 5, 9};
    m1une::graph::Doubling<Sum> chain(successor, values, 100);
    auto zero = chain.walk(0, 0);
    assert(zero.vertex == 0 && zero.product == 0);
    auto before_exit = chain.walk(0, 2);
    assert(before_exit.vertex == 2 && before_exit.product == 7);
    auto exit = chain.walk(0, 3);
    assert(exit.vertex == -1 && exit.product == 16);
    assert(chain.jump(0, 100) == -1 && chain.prod(0, 100) == 16);
    assert(chain.walk(-1, 100).product == 0);
    assert(chain.size() == 3 && chain.levels() == 7 && chain.max_steps() == 100);

    chain.build(successor, values, 0);
    assert(chain.levels() == 0 && chain.jump(2, 0) == 2);
    assert(chain.prod(1, 0) == 0);
    chain.build(std::vector<int>{0}, std::vector<long long>{3}, 16);
    assert(chain.levels() == 5 && chain.prod(0, 16) == 48);
    auto copied = chain;
    chain.build(std::vector<int>{-1}, std::vector<long long>{8}, 1);
    assert(chain.prod(0, 1) == 8 && copied.prod(0, 16) == 48);
    const std::uint64_t maximum = std::numeric_limits<std::uint64_t>::max();
    chain.build(std::vector<int>{}, std::vector<long long>{}, maximum);
    assert(chain.empty() && chain.levels() == 64);
    assert(chain.walk(-1, maximum).vertex == -1 && chain.prod(-1, maximum) == 0);

    std::vector<Box> boxes;
    boxes.emplace_back(3);
    boxes.emplace_back(8);
    m1une::graph::Doubling<BoxAdd> boxed(std::vector<int>{1, -1}, boxes, 4);
    assert(boxed.prod(0, 4).value == 11);  // No default constructor or equality is needed.

    using Mint = m1une::math::modint998244353;
    using Affine = m1une::monoid::Affine<Mint>;
    std::vector<Affine::value_type> functions;
    functions.emplace_back(2, 3);
    functions.emplace_back(5, 7);
    m1une::graph::Doubling<Affine> composition(std::vector<int>{1, -1}, functions, 2);
    const auto result = composition.prod(0, 2);
    assert(result.first == Mint(10) && result.second == Mint(17));
}

void test_randomized() {
    using Sum = m1une::monoid::Add<long long>;
    using Mint = m1une::math::modint998244353;
    using Affine = m1une::monoid::Affine<Mint>;
    std::uint64_t state = 20261117;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 120; ++trial) {
        const int n = 1 + int(random() % 25);
        const std::uint64_t limit = random() % 257;
        std::vector<int> successor(n);
        std::vector<long long> values(n);
        std::vector<Affine::value_type> functions(n);
        for (int i = 0; i < n; ++i) {
            successor[i] = int(random() % (n + 1)) - 1;
            values[i] = int(random() % 41) - 20;
            functions[i] = Affine::value_type{Mint(random() % 10), Mint(random() % 10)};
        }
        m1une::graph::Doubling<Sum> sums(successor, values, limit);
        m1une::graph::Doubling<Affine> affine(successor, functions, limit);
        for (int query = 0; query < 160; ++query) {
            int start = int(random() % (n + 1)) - 1;
            std::uint64_t steps = random() % (limit + 1);
            check_walk<Sum>(sums, successor, values, start, steps);
            check_walk<Affine>(affine, successor, functions, start, steps);
        }

        std::vector<std::string> letters(n);
        for (int i = 0; i < n; ++i) letters[i] = char('a' + i);
        const m1une::graph::Doubling<Concat> words(successor, letters, 17);
        for (int start = -1; start < n; ++start) {
            for (int steps = 0; steps <= 17; ++steps) {
                check_walk<Concat>(words, successor, letters, start, steps);
            }
        }
    }
}

void test_full_width_steps() {
    using Sum = m1une::monoid::Add<std::uint64_t>;
    const std::uint64_t maximum = std::numeric_limits<std::uint64_t>::max();
    const std::vector<int> successor = {1, 2, 0};
    const std::vector<std::uint64_t> values = {1, 2, 4};
    const m1une::graph::Doubling<Sum> cycle(successor, values, maximum);
    assert(cycle.levels() == 64);
    std::vector<std::uint64_t> queries = {0, 1, 2, 3, 63, 64, 65};
    queries.push_back((std::uint64_t(1) << 63) - 1);
    queries.push_back(std::uint64_t(1) << 63);
    queries.push_back((std::uint64_t(1) << 63) + 1);
    queries.push_back(maximum);
    for (int start = 0; start < 3; ++start) {
        for (std::uint64_t steps : queries) {
            // Unsigned addition intentionally computes the aggregate modulo 2^64.
            std::uint64_t expected = (steps / 3) * 7;
            for (std::uint64_t i = 0; i < steps % 3; ++i) expected += values[(start + i) % 3];
            const int destination = (start + steps % 3) % 3;
            auto result = cycle.walk(start, steps);
            assert(result.vertex == destination && result.product == expected);
            assert(cycle.jump(start, steps) == destination);
            assert(cycle.prod(start, steps) == expected);
        }
    }
}

}  // namespace

int main() {
    test_boundaries();
    test_randomized();
    test_full_width_steps();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    int n, q;
    if (!input.read(n, q)) return 0;
    std::vector<int> successor(n + 1, -1);
    std::vector<long long> values(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        successor[i] = i + 1;
        input >> values[i];
    }
    using Sum = m1une::monoid::Add<long long>;
    const m1une::graph::Doubling<Sum> doubling(successor, values, n);
    while (q--) {
        int l, r;
        input >> l >> r;
        auto result = doubling.walk(l, r - l);
        assert(result.vertex == r);
        output << result.product << '\n';
    }
}
