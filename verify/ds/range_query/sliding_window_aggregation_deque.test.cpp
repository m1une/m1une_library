#define PROBLEM "https://judge.yosupo.jp/problem/deque_operate_all_composite"

#include "../../../ds/range_query/sliding_window_aggregation_deque.hpp"

#include <cassert>
#include <cstdint>
#include <deque>
#include "../../../utilities/fast_io.hpp"
#include <string>
#include <vector>

namespace {

struct Concat {
    using value_type = std::string;

    static value_type id() {
        return "";
    }

    static value_type op(const value_type& left, const value_type& right) {
        return left + right;
    }
};

constexpr long long mod = 998244353;

struct Affine {
    struct value_type {
        long long a;
        long long b;
    };

    static value_type id() {
        return value_type{1, 0};
    }

    static value_type op(const value_type& first, const value_type& second) {
        return value_type{
            second.a * first.a % mod,
            (second.a * first.b + second.b) % mod,
        };
    }
};

void test_fixed() {
    m1une::ds::SwagDeque<Concat> deque;
    assert(deque.empty());
    assert(deque.prod().empty());

    deque.reserve(10);
    deque.push_back("b");
    deque.push_front("a");
    deque.push_back("c");
    deque.push_front("z");
    assert(deque.size() == 4);
    assert(deque.front() == "z");
    assert(deque.back() == "c");
    assert(deque.prod() == "zabc");

    deque.pop_front();
    deque.pop_back();
    assert(deque.front() == "a");
    assert(deque.back() == "b");
    assert(deque.all_prod() == "ab");

    deque.clear();
    assert(deque.empty());

    std::vector<std::string> values = {"x", "y", "z"};
    m1une::ds::SlidingWindowAggregationDeque<Concat> built(values);
    assert(built.prod() == "xyz");
    built.pop_back();
    built.pop_back();
    assert(built.front() == "x");
    assert(built.back() == "x");
}

void test_randomized() {
    std::uint64_t state = 904;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    m1une::ds::SwagDeque<Concat> deque;
    std::deque<std::string> expected;
    for (int operation = 0; operation < 50000; ++operation) {
        int type = expected.empty() ? int(random() % 2) : int(random() % 4);
        if (type == 0) {
            std::string value(1, char('a' + random() % 5));
            deque.push_front(value);
            expected.push_front(value);
        } else if (type == 1) {
            std::string value(1, char('a' + random() % 5));
            deque.push_back(value);
            expected.push_back(value);
        } else if (type == 2) {
            deque.pop_front();
            expected.pop_front();
        } else {
            deque.pop_back();
            expected.pop_back();
        }

        assert(deque.size() == expected.size());
        assert(deque.empty() == expected.empty());
        std::string product;
        for (const std::string& value : expected) product += value;
        assert(deque.prod() == product);
        if (!expected.empty()) {
            assert(deque.front() == expected.front());
            assert(deque.back() == expected.back());
        }
    }
}

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_fixed();
    test_randomized();

    int query_count;
    fast_input >> query_count;
    m1une::ds::SwagDeque<Affine> deque;
    while (query_count--) {
        int type;
        fast_input >> type;
        if (type == 0 || type == 1) {
            Affine::value_type function;
            fast_input >> function.a >> function.b;
            if (type == 0) {
                deque.push_front(function);
            } else {
                deque.push_back(function);
            }
        } else if (type == 2) {
            deque.pop_front();
        } else if (type == 3) {
            deque.pop_back();
        } else {
            long long x;
            fast_input >> x;
            auto function = deque.prod();
            fast_output << (function.a * x + function.b) % mod << '\n';
        }
    }
}
