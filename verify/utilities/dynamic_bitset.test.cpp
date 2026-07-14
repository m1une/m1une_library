#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include "../../utilities/fast_io.hpp"
#include <random>
#include <vector>

#include "../../utilities/dynamic_bitset.hpp"

using m1une::utilities::DynamicBitset;

void verify_state(const DynamicBitset& bits, const std::vector<int>& model) {
    const int n = static_cast<int>(model.size());
    assert(bits.size() == n);

    int count = 0;
    int low = -1;
    int top = -1;
    for (int i = 0; i < n; ++i) {
        assert(bits.test(i) == static_cast<bool>(model[i]));
        if (model[i]) {
            ++count;
            if (low == -1) low = i;
            top = i;
        }
    }

    assert(bits.popcount() == count);
    assert(bits.lowbit() == low);
    assert(bits.topbit() == top);
    assert(bits.any() == (count > 0));
    assert(bits.none() == (count == 0));
    assert(bits.all() == (count == n));
}

DynamicBitset make_bitset(const std::vector<int>& model) {
    DynamicBitset bits(static_cast<int>(model.size()));
    for (int i = 0; i < static_cast<int>(model.size()); ++i) {
        if (model[i]) bits.set(i);
    }
    return bits;
}

std::vector<int> bitwise_and_model(const std::vector<int>& lhs, const std::vector<int>& rhs) {
    std::vector<int> res(lhs.size());
    for (int i = 0; i < static_cast<int>(lhs.size()); ++i) res[i] = lhs[i] & rhs[i];
    return res;
}

std::vector<int> bitwise_or_model(const std::vector<int>& lhs, const std::vector<int>& rhs) {
    std::vector<int> res(lhs.size());
    for (int i = 0; i < static_cast<int>(lhs.size()); ++i) res[i] = lhs[i] | rhs[i];
    return res;
}

std::vector<int> bitwise_xor_model(const std::vector<int>& lhs, const std::vector<int>& rhs) {
    std::vector<int> res(lhs.size());
    for (int i = 0; i < static_cast<int>(lhs.size()); ++i) res[i] = lhs[i] ^ rhs[i];
    return res;
}

std::vector<int> bitwise_not_model(const std::vector<int>& model) {
    std::vector<int> res(model.size());
    for (int i = 0; i < static_cast<int>(model.size()); ++i) res[i] = model[i] ^ 1;
    return res;
}

void test_constructors() {
    const std::vector<int> sizes = {0, 1, 2, 3, 31, 32, 33, 63, 64, 65, 66,
                                    127, 128, 129, 130, 191, 192, 193, 257};

    DynamicBitset empty;
    verify_state(empty, std::vector<int>());

    for (int n : sizes) {
        DynamicBitset zero(n);
        verify_state(zero, std::vector<int>(n, 0));

        DynamicBitset one(n, true);
        verify_state(one, std::vector<int>(n, 1));
    }
}

void test_point_and_global_operations() {
    const std::vector<int> sizes = {0, 1, 5, 63, 64, 65, 129, 257};

    for (int n : sizes) {
        DynamicBitset bits(n);
        std::vector<int> model(n, 0);
        verify_state(bits, model);

        bits.set();
        std::fill(model.begin(), model.end(), 1);
        verify_state(bits, model);

        bits.reset();
        std::fill(model.begin(), model.end(), 0);
        verify_state(bits, model);

        bits.flip();
        for (int& x : model) x ^= 1;
        verify_state(bits, model);

        bits.flip();
        for (int& x : model) x ^= 1;
        verify_state(bits, model);

        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                bits.set(i);
                model[i] = 1;
            }
        }
        verify_state(bits, model);

        for (int i = 0; i < n; ++i) {
            if (i % 5 == 0) {
                bits.reset(i);
                model[i] = 0;
            }
        }
        verify_state(bits, model);

        for (int i = 0; i < n; ++i) {
            if (i % 7 == 0) {
                bits.flip(i);
                model[i] ^= 1;
            }
        }
        verify_state(bits, model);
    }
}

void test_bitwise_operations() {
    const std::vector<int> sizes = {0, 1, 2, 63, 64, 65, 100, 127, 128, 129, 255};

    for (int n : sizes) {
        std::vector<int> lhs(n), rhs(n);
        for (int i = 0; i < n; ++i) {
            lhs[i] = ((i * 37 + n) % 5) < 2;
            rhs[i] = ((i * 19 + n * 3) % 7) < 3;
        }

        const DynamicBitset a = make_bitset(lhs);
        const DynamicBitset b = make_bitset(rhs);

        verify_state(a & b, bitwise_and_model(lhs, rhs));
        verify_state(a | b, bitwise_or_model(lhs, rhs));
        verify_state(a ^ b, bitwise_xor_model(lhs, rhs));
        verify_state(~a, bitwise_not_model(lhs));

        DynamicBitset c = a;
        c &= b;
        verify_state(c, bitwise_and_model(lhs, rhs));

        c = a;
        c |= b;
        verify_state(c, bitwise_or_model(lhs, rhs));

        c = a;
        c ^= b;
        verify_state(c, bitwise_xor_model(lhs, rhs));
    }
}

void test_randomized() {
    std::mt19937_64 rng(123456789);

    for (int trial = 0; trial < 200; ++trial) {
        int n;
        if (trial < 130) {
            n = trial;
        } else {
            n = static_cast<int>(rng() % 600);
        }

        DynamicBitset bits(n, (rng() & 1) != 0);
        std::vector<int> model(n, bits.all() ? 1 : 0);
        verify_state(bits, model);

        for (int step = 0; step < 400; ++step) {
            const int op = static_cast<int>(rng() % 10);
            if (op == 0) {
                bits.set();
                std::fill(model.begin(), model.end(), 1);
            } else if (op == 1) {
                bits.reset();
                std::fill(model.begin(), model.end(), 0);
            } else if (op == 2) {
                bits.flip();
                for (int& x : model) x ^= 1;
            } else if (op <= 5) {
                if (n == 0) continue;
                const int i = static_cast<int>(rng() % n);
                if (op == 3) {
                    bits.set(i);
                    model[i] = 1;
                } else if (op == 4) {
                    bits.reset(i);
                    model[i] = 0;
                } else {
                    bits.flip(i);
                    model[i] ^= 1;
                }
            } else {
                std::vector<int> other_model(n);
                for (int i = 0; i < n; ++i) other_model[i] = (rng() % 3) == 0;
                DynamicBitset other = make_bitset(other_model);

                if (op == 6) {
                    bits &= other;
                    model = bitwise_and_model(model, other_model);
                } else if (op == 7) {
                    bits |= other;
                    model = bitwise_or_model(model, other_model);
                } else if (op == 8) {
                    bits ^= other;
                    model = bitwise_xor_model(model, other_model);
                } else {
                    verify_state(bits & other, bitwise_and_model(model, other_model));
                    verify_state(bits | other, bitwise_or_model(model, other_model));
                    verify_state(bits ^ other, bitwise_xor_model(model, other_model));
                    verify_state(~bits, bitwise_not_model(model));
                }
            }
            verify_state(bits, model);
        }
    }
}

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_constructors();
    test_point_and_global_operations();
    test_bitwise_operations();
    test_randomized();

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
