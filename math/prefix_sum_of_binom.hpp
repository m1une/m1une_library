#ifndef M1UNE_MATH_PREFIX_SUM_OF_BINOM_HPP
#define M1UNE_MATH_PREFIX_SUM_OF_BINOM_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <numeric>
#include <utility>
#include <vector>

#include "combinatorics.hpp"

namespace m1une {
namespace math {

// Answers sum_{k=0}^{m-1} binom(n, k) after square-root decomposition.
template <class Mint>
struct PrefixSumOfBinom {
   private:
    int _maximum;
    int _block_size;
    Combinatorics<Mint> _combinations;
    std::vector<Mint> _powers_of_two;
    std::vector<std::vector<Mint>> _data;

    Mint _block_prefix(int n, int block) const {
        const int endpoint = block * _block_size;
        if (n <= endpoint) return _powers_of_two[n];
        return _data[block][n - endpoint] * _combinations.inverse_factorial(endpoint);
    }

    Mint _binom_sum(int n, int left, int right) const {
        __uint128_t sum = 0;
        for (int k = left; k < right; k++) {
            sum += static_cast<__uint128_t>(_combinations.inverse_factorial(k).val()) *
                   _combinations.inverse_factorial(n - k).val();
        }
        const uint32_t reduced = static_cast<uint32_t>(sum % Mint::mod());
        return Mint::raw(reduced) * _combinations.factorial(n);
    }

   public:
    explicit PrefixSumOfBinom(int maximum)
        : _maximum(maximum),
          _block_size(std::max(1, int(std::sqrt(static_cast<double>(maximum) + 1)))),
          _combinations(maximum),
          _powers_of_two(maximum + 1, Mint(1)) {
        assert(maximum >= 0);

        for (int n = 0; n < maximum; n++) {
            _powers_of_two[n + 1] = _powers_of_two[n] + _powers_of_two[n];
        }

        const int block_count = maximum / (2 * _block_size) + 3;
        _data.resize(block_count);
        for (int block = 0; block < block_count; block++) {
            const int endpoint = block * _block_size;
            if (endpoint > maximum) continue;

            std::vector<Mint>& values = _data[block];
            values.resize(maximum - endpoint + 1);
            values[0] = _powers_of_two[endpoint] * _combinations.factorial(endpoint);
            for (int offset = 0; offset < maximum - endpoint; offset++) {
                values[offset + 1] =
                    values[offset] + values[offset] -
                    _combinations.factorial(offset + endpoint) *
                        _combinations.inverse_factorial(offset);
            }
        }
    }

    int maximum() const {
        return _maximum;
    }

    // Returns sum_{k=0}^{m-1} binom(n, k). Values m > n + 1 are clamped.
    Mint query(int n, int m) const {
        assert(0 <= n && n <= _maximum);
        assert(m >= 0);
        m = std::min(m, n + 1);
        if (m == 0) return Mint(0);
        if (2 * m > n + 1) {
            return _powers_of_two[n] - query(n, n + 1 - m);
        }

        const int endpoint = m - 1;
        const int block = endpoint / _block_size;
        const int lower = block * _block_size;
        const int upper = (block + 1) * _block_size;
        if (endpoint - lower <= upper - endpoint) {
            return _block_prefix(n, block) + _binom_sum(n, lower + 1, endpoint + 1);
        }
        return _block_prefix(n, block + 1) - _binom_sum(n, endpoint + 1, upper + 1);
    }
};

// Batches the same queries and evaluates them in Mo order with linear memory.
template <class Mint>
struct OfflinePrefixSumOfBinom {
   private:
    std::vector<std::pair<int, int>> _queries;

   public:
    int query_count() const {
        return int(_queries.size());
    }

    bool empty() const {
        return _queries.empty();
    }

    void reserve(int query_capacity) {
        assert(query_capacity >= 0);
        _queries.reserve(query_capacity);
    }

    void clear() {
        _queries.clear();
    }

    // Adds sum_{k=0}^{m-1} binom(n, k) and returns its insertion-order ID.
    int add_query(int n, int m) {
        assert(n >= 0);
        assert(m >= 0);
        m = std::min(m, n + 1);
        const int id = query_count();
        _queries.emplace_back(n, m);
        return id;
    }

    std::vector<Mint> calculate() const {
        const int count = query_count();
        std::vector<Mint> answers(count);
        if (count == 0) return answers;

        int maximum = 0;
        for (const auto& query : _queries) maximum = std::max(maximum, query.first);
        assert(static_cast<uint64_t>(maximum) < Mint::mod());
        assert(Mint::mod() % 2 == 1);
        Combinatorics<Mint> combinations(maximum);

        const int block_size =
            std::max(1, int(maximum / std::sqrt(static_cast<double>(count))));
        std::vector<int> order(count);
        std::iota(order.begin(), order.end(), 0);
        std::sort(order.begin(), order.end(), [&](int first, int second) {
            const int first_block = _queries[first].first / block_size;
            const int second_block = _queries[second].first / block_size;
            if (first_block != second_block) return first_block < second_block;
            if (first_block & 1) return _queries[first].second > _queries[second].second;
            return _queries[first].second < _queries[second].second;
        });

        int n = 0;
        int m = 0;
        Mint answer = 0;
        const Mint inverse_two = Mint(2).inv();
        for (int id : order) {
            const int next_n = _queries[id].first;
            const int next_m = _queries[id].second;
            while (n < next_n) {
                answer += answer;
                answer -= combinations.binom(n, m - 1);
                n++;
            }
            while (n > next_n) {
                answer += combinations.binom(n - 1, m - 1);
                answer *= inverse_two;
                n--;
            }
            while (m < next_m) answer += combinations.binom(n, m++);
            while (m > next_m) answer -= combinations.binom(n, --m);
            answers[id] = answer;
        }
        return answers;
    }
};

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_PREFIX_SUM_OF_BINOM_HPP
