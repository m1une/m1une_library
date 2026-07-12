#ifndef M1UNE_MATH_MULTIPLICATIVE_FUNCTION_PREFIX_SUM_HPP
#define M1UNE_MATH_MULTIPLICATIVE_FUNCTION_PREFIX_SUM_HPP 1

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

namespace m1une {
namespace math {

// Computes summatory multiplicative functions with a Min_25 sieve.
// prime_power(p, e) must return f(p^e), and prime_prefix must contain
// sum_{p <= x} f(p) at every x represented by quotient_values().
template <class T, class PrimePower>
struct MultiplicativeFunctionPrefixSum {
   private:
    uint64_t _n;
    uint64_t _sqrt_n;
    uint64_t _large_size;
    std::vector<int> _primes;
    PrimePower _prime_power;

    static uint64_t integer_sqrt(uint64_t n) {
        uint64_t result = static_cast<uint64_t>(std::sqrt(static_cast<long double>(n)));
        while (result != 0 && result > n / result) result--;
        while (result + 1 <= n / (result + 1)) result++;
        return result;
    }

    static uint64_t validated_sqrt(uint64_t n) {
        const uint64_t result = integer_sqrt(n);
        assert(result <= static_cast<uint64_t>(std::numeric_limits<int>::max() / 2));
        return result;
    }

    static std::vector<int> enumerate_primes(uint64_t limit) {
        assert(limit <= static_cast<uint64_t>(std::numeric_limits<int>::max()));
        const int n = static_cast<int>(limit);
        std::vector<bool> is_composite(n + 1);
        std::vector<int> primes;
        for (int value = 2; value <= n; value++) {
            if (!is_composite[value]) primes.push_back(value);
            for (int prime : primes) {
                if (value > n / prime) break;
                is_composite[value * prime] = true;
                if (value % prime == 0) break;
            }
        }
        return primes;
    }

    T triangular(uint64_t n) const {
        if ((n & 1) == 0) return T(n / 2) * T(n + 1);
        return T(n) * T((n + 1) / 2);
    }

   public:
    explicit MultiplicativeFunctionPrefixSum(uint64_t n, PrimePower prime_power)
        : _n(n),
          _sqrt_n(validated_sqrt(n)),
          _large_size(n == 0 ? 0 : n / _sqrt_n),
          _primes(enumerate_primes(_sqrt_n)),
          _prime_power(std::move(prime_power)) {
        if (n == 0) return;
        while (_large_size > 1 && n / (_large_size - 1) == _sqrt_n) _large_size--;
    }

    uint64_t n() const {
        return _n;
    }

    uint64_t sqrt_n() const {
        return _sqrt_n;
    }

    const std::vector<int>& primes() const {
        return _primes;
    }

    int table_size() const {
        if (_n == 0) return 0;
        return static_cast<int>(_large_size + _sqrt_n);
    }

    // Returns the table index representing x. The argument must be one of the
    // values returned by quotient_values().
    int index(uint64_t x) const {
        assert(_n > 0 && 1 <= x && x <= _n);
        if (x <= _sqrt_n) return table_size() - static_cast<int>(x);
        const uint64_t result = _n / x;
        assert(result < _large_size);
        return static_cast<int>(result);
    }

    // table[i] represents the value at quotient_values()[i]. Index zero is a
    // dummy entry; the represented values occupy indices [1, table_size()).
    std::vector<uint64_t> quotient_values() const {
        if (_n == 0) return {};
        std::vector<uint64_t> result(table_size());
        for (uint64_t i = 1; i < _large_size; i++) result[i] = _n / i;
        for (uint64_t value = 1; value <= _sqrt_n; value++) {
            result[index(value)] = value;
        }
        return result;
    }

    // Returns pi(x) at every represented x.
    std::vector<T> prime_count_table() const {
        if (_n == 0) return {};
        std::vector<uint64_t> large(_large_size);
        for (uint64_t i = 1; i < _large_size; i++) large[i] = _n / i - 1;

        std::vector<uint64_t> small(_sqrt_n + 1);
        for (uint64_t value = 1; value <= _sqrt_n; value++) small[value] = value - 1;

        uint64_t prime_count = 0;
        for (int prime_int : _primes) {
            const uint64_t prime = static_cast<uint64_t>(prime_int);
            const uint64_t square = prime * prime;
            const uint64_t end = std::min(_large_size, _n / square + 1);
            uint64_t product = prime;
            for (uint64_t i = 1; i < end; i++, product += prime) {
                const uint64_t previous = product < _large_size ? large[product] : small[_n / product];
                large[i] -= previous - prime_count;
            }
            for (uint64_t value = _sqrt_n; value >= square; value--) {
                small[value] -= small[value / prime] - prime_count;
            }
            prime_count++;
        }

        std::vector<T> result(table_size());
        for (uint64_t i = 0; i < _large_size; i++) result[i] = T(large[i]);
        for (uint64_t value = 1; value <= _sqrt_n; value++) result[index(value)] = T(small[value]);
        return result;
    }

    // Returns sum_{p <= x} p at every represented x.
    std::vector<T> prime_sum_table() const {
        if (_n == 0) return {};
        std::vector<T> result(table_size());
        for (uint64_t i = 1; i < _large_size; i++) result[i] = triangular(_n / i) - T(1);
        for (uint64_t value = 1; value <= _sqrt_n; value++) {
            result[index(value)] = triangular(value) - T(1);
        }

        for (int prime_int : _primes) {
            const uint64_t prime = static_cast<uint64_t>(prime_int);
            const uint64_t square = prime * prime;
            const T before = result[index(prime - 1)];
            const uint64_t end = std::min(_large_size, _n / square + 1);
            uint64_t product = prime;
            for (uint64_t i = 1; i < end; i++, product += prime) {
                result[i] -= (result[index(_n / product)] - before) * T(prime);
            }
            for (uint64_t value = _sqrt_n; value >= square; value--) {
                result[index(value)] -= (result[index(value / prime)] - before) * T(prime);
            }
        }
        return result;
    }

    // Returns sum_{k=1}^x f(k) at every represented x.
    std::vector<T> prefix_sum_table(const std::vector<T>& prime_prefix) const {
        if (_n == 0) {
            assert(prime_prefix.empty());
            return {};
        }
        assert(static_cast<int>(prime_prefix.size()) == table_size());

        const std::vector<uint64_t> values = quotient_values();
        std::vector<T> result = prime_prefix;
        std::vector<T> next = prime_prefix;
        for (int prime_index = static_cast<int>(_primes.size()) - 1; prime_index >= 0; prime_index--) {
            const uint64_t prime = static_cast<uint64_t>(_primes[prime_index]);
            uint64_t power = prime;
            int exponent = 1;
            while (power <= _n / prime) {
                const T current_value = _prime_power(prime, exponent);
                const T next_value = _prime_power(prime, exponent + 1);
                const T primes_before = prime_prefix[index(prime)];
                for (int i = 1; i < table_size(); i++) {
                    const uint64_t value = values[i];
                    if (value < power * prime) break;
                    next[i] += current_value * (result[index(value / power)] - primes_before) + next_value;
                }
                exponent++;
                power *= prime;
            }
            const uint64_t bound = prime * prime;
            const int copy_size = std::min(table_size(), index(bound) + 1);
            std::copy(next.begin(), next.begin() + copy_size, result.begin());
        }
        for (int i = 1; i < table_size(); i++) result[i] += T(1);
        return result;
    }

    T prefix_sum(const std::vector<T>& prime_prefix) const {
        if (_n == 0) {
            assert(prime_prefix.empty());
            return T{};
        }
        return prefix_sum_table(prime_prefix)[index(_n)];
    }
};

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_MULTIPLICATIVE_FUNCTION_PREFIX_SUM_HPP
