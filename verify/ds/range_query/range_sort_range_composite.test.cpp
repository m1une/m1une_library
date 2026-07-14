#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_sort_range_composite"

#include "../../../ds/range_query/range_sort_range_composite.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include "../../../utilities/fast_io.hpp"
#include <tuple>
#include <utility>
#include <vector>

#include "../../../math/modint.hpp"

namespace {

using Mint = m1une::math::modint998244353;
using Function = std::pair<Mint, Mint>;

struct AffineComposition {
    using value_type = Function;

    static value_type id() {
        return {Mint(1), Mint(0)};
    }

    static value_type op(const value_type& left, const value_type& right) {
        return {
            right.first * left.first,
            right.first * left.second + right.second
        };
    }
};

struct Item {
    int key;
    Function function;
};

Function naive_product(const std::vector<Item>& items, int left, int right) {
    Function result = AffineComposition::id();
    for (int i = left; i < right; i++) {
        result = AffineComposition::op(result, items[i].function);
    }
    return result;
}

void test_randomized() {
    using Data = m1une::ds::RangeSortRangeComposite<AffineComposition>;
    Data empty;
    assert(empty.empty());
    assert(empty.size() == 0);
    assert(empty.key_count() == 0);
    assert(empty.all_prod() == AffineComposition::id());

    std::uint64_t state = 818181;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 600; trial++) {
        int size = 1 + int(random() % 18);
        int key_count = 32;
        std::vector<int> available(key_count);
        for (int i = 0; i < key_count; i++) available[i] = i;
        for (int i = key_count - 1; i > 0; i--) {
            std::swap(available[i], available[random() % (i + 1)]);
        }

        std::vector<int> keys;
        std::vector<Function> functions;
        std::vector<Item> items;
        for (int i = 0; i < size; i++) {
            Function function = {
                Mint(1 + random() % 20),
                Mint(random() % 20)
            };
            keys.push_back(available[i]);
            functions.push_back(function);
            items.push_back(Item{available[i], function});
        }

        Data data(key_count, keys, functions);
        assert(data.size() == size);
        assert(!data.empty());
        assert(data.key_count() == key_count);

        for (int operation = 0; operation < 300; operation++) {
            int type = int(random() % 6);
            int left = int(random() % (size + 1));
            int right = int(random() % (size + 1));
            if (left > right) std::swap(left, right);
            if (type == 0) {
                int position = int(random() % size);
                std::vector<bool> used(key_count, false);
                for (const auto& item : items) used[item.key] = true;
                int key = items[position].key;
                if ((random() & 1U) != 0) {
                    do {
                        key = int(random() % key_count);
                    } while (used[key]);
                }
                Function function = {
                    Mint(1 + random() % 20),
                    Mint(random() % 20)
                };
                data.set(position, key, function);
                items[position] = Item{key, function};
            } else if (type == 1) {
                assert(data.prod(left, right) == naive_product(items, left, right));
            } else if (type == 2) {
                data.sort_ascending(left, right);
                std::sort(items.begin() + left, items.begin() + right, [](const Item& a, const Item& b) {
                    return a.key < b.key;
                });
            } else if (type == 3) {
                data.sort_descending(left, right);
                std::sort(items.begin() + left, items.begin() + right, [](const Item& a, const Item& b) {
                    return a.key > b.key;
                });
            } else if (type == 4) {
                int position = int(random() % size);
                auto [key, function] = data.get(position);
                assert(key == items[position].key);
                assert(function == items[position].function);
            } else {
                assert(data.all_prod() == naive_product(items, 0, size));
            }
        }
    }
}

struct Query {
    int type;
    int first;
    int second;
    int third;
    int fourth;
};

}  // namespace

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    test_randomized();
    int n, q;
    fast_input >> n >> q;
    std::vector<int> keys(n);
    std::vector<Function> functions(n);
    std::vector<int> all_keys;
    all_keys.reserve(n + q);
    for (int i = 0; i < n; i++) {
        int a, b;
        fast_input >> keys[i] >> a >> b;
        functions[i] = {Mint(a), Mint(b)};
        all_keys.push_back(keys[i]);
    }

    std::vector<Query> queries(q);
    for (auto& query : queries) {
        fast_input >> query.type;
        if (query.type == 0) {
            fast_input >> query.first >> query.second >> query.third >> query.fourth;
            all_keys.push_back(query.second);
        } else if (query.type == 1) {
            fast_input >> query.first >> query.second >> query.third;
            query.fourth = 0;
        } else {
            fast_input >> query.first >> query.second;
            query.third = query.fourth = 0;
        }
    }

    std::sort(all_keys.begin(), all_keys.end());
    all_keys.erase(std::unique(all_keys.begin(), all_keys.end()), all_keys.end());
    for (int& key : keys) {
        key = int(std::lower_bound(all_keys.begin(), all_keys.end(), key) - all_keys.begin());
    }

    using Data = m1une::ds::RangeSortRangeComposite<AffineComposition>;
    Data data(int(all_keys.size()), keys, functions);
    for (const auto& query : queries) {
        if (query.type == 0) {
            int key = int(
                std::lower_bound(all_keys.begin(), all_keys.end(), query.second) - all_keys.begin()
            );
            data.set(query.first, key, Function{Mint(query.third), Mint(query.fourth)});
        } else if (query.type == 1) {
            Function function = data.prod(query.first, query.second);
            Mint answer = function.first * Mint(query.third) + function.second;
            fast_output << answer << '\n';
        } else if (query.type == 2) {
            data.sort_ascending(query.first, query.second);
        } else {
            data.sort_descending(query.first, query.second);
        }
    }
}
