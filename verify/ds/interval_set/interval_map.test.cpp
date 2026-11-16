#define PROBLEM "https://judge.yosupo.jp/problem/range_set_range_composite"

#include "../../../ds/interval_set/interval_map.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <limits>
#include <optional>
#include <utility>
#include <vector>

#include "../../../ds/segtree/segtree.hpp"
#include "../../../math/modint.hpp"
#include "../../../monoid/power.hpp"
#include "../../../utilities/fast_io.hpp"

namespace {

using Map = m1une::ds::IntervalMap<int, int>;
using Interval = Map::interval_type;

void assert_intervals(const std::vector<Interval>& actual, const std::vector<Interval>& expected) {
    assert(actual.size() == expected.size());
    for (int i = 0; i < int(actual.size()); ++i) {
        assert(actual[i].l == expected[i].l);
        assert(actual[i].r == expected[i].r);
        assert(actual[i].value == expected[i].value);
    }
}

std::vector<Interval> naive_intervals(const std::vector<std::optional<int>>& values) {
    std::vector<Interval> result;
    for (int l = 0; l < int(values.size());) {
        if (!values[l].has_value()) {
            ++l;
            continue;
        }
        int r = l + 1;
        while (r < int(values.size()) && values[l] == values[r]) ++r;
        result.push_back(Interval{l - 16, r - 16, *values[l]});
        l = r;
    }
    return result;
}

std::vector<Interval> clipped(const std::vector<Interval>& intervals, int l, int r) {
    std::vector<Interval> result;
    for (const auto& interval : intervals) {
        int a = std::max(l, interval.l);
        int b = std::min(r, interval.r);
        if (a < b) result.push_back(Interval{a, b, interval.value});
    }
    return result;
}

void check_map(const Map& map, const std::vector<std::optional<int>>& values) {
    auto expected = naive_intervals(values);
    assert_intervals(map.to_vector(), expected);
    assert(map.size() == int(expected.size()));
    assert(map.empty() == expected.empty());
    assert_intervals(std::vector<Interval>(map.begin(), map.end()), expected);
    for (int i = 0; i < int(values.size()); ++i) {
        int x = i - 16;
        assert(map.contains(x) == values[i].has_value());
        const int* value = map.get_if(x);
        auto it = map.find(x);
        assert((value != nullptr) == values[i].has_value());
        assert((it != map.end()) == values[i].has_value());
        if (value != nullptr) {
            assert(*value == *values[i]);
            assert(map.get(x) == *values[i]);
            assert(it->l <= x && x < it->r && it->value == *values[i]);
        }
    }
    assert(!map.contains(-17));
    assert(!map.contains(16));
    assert_intervals(map.to_vector(), expected);  // Const queries preserve the partition.
}

void test_boundaries() {
    Map map;
    int callbacks = 0;
    auto count = [&](int, int, const int&) { ++callbacks; };
    map.assign(3, 3, 7, count);
    map.erase(3, 3, count);
    map.for_each(3, 3, count);
    assert(map.empty() && callbacks == 0);

    map.assign(0, 2, 7);
    map.assign(4, 6, 7);
    assert(map.size() == 2 && map.get_if(2) == nullptr);
    map.assign(2, 4, 7, count);  // Filling a gap merges both neighbors without callbacks.
    assert(map.size() == 1 && map.begin()->l == 0 && map.begin()->r == 6);
    assert(callbacks == 0);
    map.assign(1, 5, map.get(2), count);  // Aliased input survives erasure.
    assert(callbacks == 1 && map.size() == 1);
    map.erase(2, 4);
    assert(map.size() == 2 && map.find(2) == map.end());
    map.assign(1, 5, 9);
    assert(map.size() == 3 && map.get(0) == 7 && map.get(5) == 7);

    std::vector<Interval> input;
    input.push_back(Interval{-10, -4, 3});
    input.push_back(Interval{-4, 0, 3});
    input.push_back(Interval{2, 5, 3});
    Map sorted(input);
    assert(sorted.size() == 2 && sorted.begin()->r == 0);
    Map copied = sorted;
    copied.assign(-10, 5, 1);
    assert(sorted.size() == 2 && copied.size() == 1);
    Map moved = std::move(copied);
    assert(moved.size() == 1 && moved.get(0) == 1);
    moved.clear();
    assert(moved.empty());
    Map no_runs(std::vector<Interval>{});
    Map no_values(std::vector<int>{});
    assert(no_runs.empty() && no_values.empty());
    Map empty_range(0, 0, 4);
    assert(empty_range.empty());

    using WideMap = m1une::ds::IntervalMap<long long, int>;
    const long long lo = std::numeric_limits<long long>::lowest();
    const long long hi = std::numeric_limits<long long>::max();
    WideMap wide(lo, hi, 1);
    wide.assign(lo, 0, 2);
    wide.assign(0, hi, 2);
    assert(wide.size() == 1 && wide.get(lo) == 2 && wide.get(hi - 1) == 2);
    assert(!wide.contains(hi));
    wide.erase(lo, hi);
    assert(wide.empty());
}

struct Coordinate {
    long long x;
    explicit Coordinate(long long value) : x(value) {}
    friend bool operator<(const Coordinate& a, const Coordinate& b) { return a.x < b.x; }
};

struct Label {
    int id;
    explicit Label(int value) : id(value) {}
    bool operator==(const Label&) const = default;
    const Label* operator&() const { return nullptr; }
};

void test_generic_types() {
    using GenericMap = m1une::ds::IntervalMap<Coordinate, Label>;
    GenericMap map(Coordinate(-10), Coordinate(10), Label(3));
    map.assign(Coordinate(-2), Coordinate(2), Label(8));
    assert(map.get(Coordinate(0)).id == 8);
    assert(map.get_if(Coordinate(0)) != nullptr);
    map.assign(Coordinate(-2), Coordinate(2), map.get(Coordinate(-5)));
    assert(map.size() == 1);
    map.erase(Coordinate(-1), Coordinate(1));
    assert(map.size() == 2 && !map.contains(Coordinate(0)));

    struct Counter {
        int calls = 0;
        Counter() = default;
        Counter(const Counter&) = delete;
        void operator()(Coordinate l, Coordinate r, const Label& value) {
            assert(l.x < r.x && value.id == 3);
            ++calls;
        }
    };
    Counter counter;
    map.for_each(Coordinate(-100), Coordinate(100), counter);
    assert(counter.calls == 2);
    map.erase(Coordinate(-100), Coordinate(100), counter);
    assert(counter.calls == 4 && map.empty());
}

void test_randomized() {
    std::uint64_t state = 20261117;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    for (int trial = 0; trial < 60; ++trial) {
        std::vector<std::optional<int>> values(32);
        Map map;
        for (int step = 0; step < 350; ++step) {
            int l = int(random() % 33);
            int r = int(random() % 33);
            if (r < l) std::swap(l, r);
            int value = int(random() % 5) - 2;
            int type = int(random() % 5);
            auto before = naive_intervals(values);
            std::vector<Interval> visited;
            auto callback = [&](int a, int b, const int& old_value) {
                visited.push_back(Interval{a, b, old_value});
            };
            if (type == 0) {
                map.assign(l - 16, r - 16, value, callback);
                for (int i = l; i < r; ++i) values[i] = value;
            } else if (type == 1) {
                map.erase(l - 16, r - 16, callback);
                for (int i = l; i < r; ++i) values[i].reset();
            } else if (type == 2) {
                const Map& view = map;
                view.for_each(l - 16, r - 16, callback);
            } else if (type == 3) {
                map.assign(l - 16, r - 16, value);
                for (int i = l; i < r; ++i) values[i] = value;
            } else {
                map.erase(l - 16, r - 16);
                for (int i = l; i < r; ++i) values[i].reset();
            }
            if (type <= 2) assert_intervals(visited, clipped(before, l - 16, r - 16));
            check_map(map, values);
        }

        std::vector<int> dense(32);
        for (int& value : dense) value = int(random() % 4);
        Map from_values(dense);
        for (int i = 0; i < 32; ++i) assert(from_values.get(i) == dense[i]);
        int runs = 0;
        for (int i = 0; i < 32; ++i) runs += i == 0 || dense[i] != dense[i - 1];
        assert(from_values.size() == runs);
    }
}

using Mint = m1une::math::modint998244353;
using Function = std::pair<Mint, Mint>;

struct Composition {
    using value_type = Function;
    static Function id() { return {Mint(1), Mint(0)}; }
    static Function op(const Function& a, const Function& b) {
        return {b.first * a.first, b.first * a.second + b.second};
    }
};

// One segment-tree marker per constant run. The interval map determines which
// markers to remove and which boundary fragments to rebuild after assignment.
class RunProducts {
    int _n;
    m1une::ds::IntervalMap<int, Function> _runs;
    m1une::ds::Segtree<Composition> _products;

    void rebuild(int position) {
        auto run = _runs.find(position);
        _products.set(run->l, m1une::monoid::power<Composition>(run->value, run->r - run->l));
    }

   public:
    explicit RunProducts(const std::vector<Function>& functions)
        : _n(int(functions.size())), _runs(functions), _products(_n) {
        for (const auto& run : _runs) rebuild(run.l);
    }

    void assign(int l, int r, Function value) {
        if (l == r) return;
        _products.set(_runs.find(l)->l, Composition::id());
        if (r < _n) _products.set(_runs.find(r)->l, Composition::id());
        _runs.assign(l, r, value, [&](int a, int, const Function&) {
            _products.set(a, Composition::id());
        });
        if (l > 0) rebuild(l - 1);
        rebuild(l);
        if (r < _n) rebuild(r);
    }

    Function prod(int l, int r) const {
        if (l == r) return Composition::id();
        auto first = _runs.find(l);
        auto last = _runs.find(r - 1);
        if (first == last) return m1une::monoid::power<Composition>(first->value, r - l);
        Function result = m1une::monoid::power<Composition>(first->value, first->r - l);
        result = Composition::op(result, _products.prod(first->r, last->l));
        return Composition::op(result, m1une::monoid::power<Composition>(last->value, r - last->l));
    }
};

void test_run_products() {
    std::uint64_t state = 123456789;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };
    for (int trial = 0; trial < 30; ++trial) {
        const int n = 1 + int(random() % 20);
        std::vector<Function> values(n);
        for (auto& value : values) value = Function{Mint(random() % 4), Mint(random() % 4)};
        RunProducts runs(values);
        for (int step = 0; step < 150; ++step) {
            int l = int(random() % (n + 1));
            int r = int(random() % (n + 1));
            if (r < l) std::swap(l, r);
            if (random() & 1) {
                Function value = {Mint(random() % 4), Mint(random() % 4)};
                runs.assign(l, r, value);
                std::fill(values.begin() + l, values.begin() + r, value);
            }
            Function expected = Composition::id();
            for (int i = l; i < r; ++i) expected = Composition::op(expected, values[i]);
            assert(runs.prod(l, r) == expected);
        }
    }
}

}  // namespace

int main() {
    test_boundaries();
    test_generic_types();
    test_randomized();
    test_run_products();

    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;
    int n, q;
    input >> n >> q;
    std::vector<Function> functions(n);
    for (auto& function : functions) {
        int a, b;
        input >> a >> b;
        function = Function{Mint(a), Mint(b)};
    }
    RunProducts runs(functions);
    while (q--) {
        int type, l, r, x;
        input >> type >> l >> r >> x;
        if (type == 0) {
            int b;
            input >> b;
            runs.assign(l, r, Function{Mint(x), Mint(b)});
        } else {
            Function result = runs.prod(l, r);
            output << (result.first * Mint(x) + result.second) << '\n';
        }
    }
}
