#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include "../../ds/bst/persistent_ordered_multiset.hpp"
#include "../../ds/bst/persistent_ordered_set.hpp"
#include "../../ds/deque/persistent_deque.hpp"
#include "../../ds/dsu/partially_persistent_dsu.hpp"
#include "../../ds/dsu/persistent_dsu.hpp"
#include "../../ds/dsu/persistent_potentialized_dsu.hpp"
#include "../../ds/dynamic_array/persistent_dynamic_array.hpp"
#include "../../ds/dynamic_array/persistent_dynamic_lazy_monoid_array.hpp"
#include "../../ds/dynamic_array/persistent_dynamic_monoid_array.hpp"
#include "../../ds/queue/persistent_queue.hpp"
#include "../../ds/stack/persistent_stack.hpp"
#include "../../acted_monoid/range_add_range_sum.hpp"
#include "../../monoid/add.hpp"
#include "../../utilities/fast_io.hpp"

#include <cassert>
#include <memory>
#include <utility>
#include <vector>

void test_release() {
    {
        m1une::ds::PersistentDynamicArray<int> base = {1, 2, 3, 4};
        auto branch = base.insert(2, 9).reverse();
        std::size_t live = base.node_count();
        branch.release();
        assert(base.node_count() < live);
        std::vector<int> expected = {1, 2, 3, 4};
        assert(base.to_vector() == expected);
        base.release();
        assert(base.empty() && base.node_count() == 0);
    }
    {
        using Array = m1une::ds::PersistentDynamicMonoidArray<m1une::monoid::Add<long long>>;
        Array base(std::vector<long long>{1, 2, 3});
        auto branch = base.set(1, 7).reverse();
        std::size_t live = base.node_count();
        branch.release();
        assert(base.node_count() < live && base.all_prod() == 6);
        base.release();
        assert(base.empty() && base.node_count() == 0);
    }
    {
        using ActedMonoid = m1une::acted_monoid::RangeAddRangeSum<long long>;
        using Array = m1une::ds::PersistentDynamicLazyMonoidArray<ActedMonoid>;
        Array base(std::vector<long long>{1, 2, 3});
        auto branch = base.apply(0, 2, 5).reverse();
        std::size_t live = base.node_count();
        branch.release();
        assert(base.node_count() < live && base.all_prod().sum == 6);
        base.release();
        assert(base.empty() && base.node_count() == 0);
    }
    {
        m1une::ds::PersistentDsu base(5);
        auto branch = base.merge(0, 1).merge(1, 2);
        std::size_t live = base.node_count();
        branch.release();
        assert(base.node_count() < live && !base.same(0, 1));
        base.release();
        assert(base.empty() && base.node_count() == 0);
    }
    {
        using Dsu = m1une::ds::PersistentPotentializedDsu<m1une::monoid::Add<long long>>;
        Dsu base(4);
        auto branch = base.merge(0, 1, 3).first.merge(1, 2, 4).first;
        std::size_t live = base.node_count();
        branch.release();
        assert(base.node_count() < live && !base.same(0, 1));
        base.release();
        assert(base.empty() && base.node_count() == 0);
    }
    {
        m1une::ds::PersistentStack<int> base;
        base = base.push(1).push(2);
        auto branch = base.push(3);
        std::size_t live = base.node_count();
        branch.release();
        assert(base.node_count() < live && base.top() == 2);
        base.release();
        assert(base.empty() && base.node_count() == 0);
    }
    {
        m1une::ds::PersistentQueue<int> base;
        base = base.push(1).push(2).push(3);
        auto branch = base.push(4).pop();
        std::size_t live = base.node_count();
        branch.release();
        assert(base.node_count() < live);
        assert(base.front() == 1 && base.back() == 3);
        base.release();
        assert(base.empty() && base.node_count() == 0);
    }
    {
        m1une::ds::PersistentDeque<int> base;
        base = base.push_back(1).push_front(2).push_back(3);
        auto branch = base.push_front(4).pop_back();
        std::size_t live = base.node_count();
        branch.release();
        assert(base.node_count() < live);
        assert(base.front() == 2 && base.back() == 3);
        base.release();
        assert(base.empty() && base.node_count() == 0);
    }
    {
        m1une::ds::PersistentOrderedMultiset<int> base = {1, 2, 3};
        auto branch = base.insert(4).erase(2);
        std::size_t live = base.node_count();
        branch.release();
        assert(base.node_count() < live && base.contains(2));
        base.release();
        assert(base.empty() && base.node_count() == 0);
    }
    {
        m1une::ds::PersistentOrderedSet<int> base = {1, 2, 3};
        auto branch = base.insert(4).erase(2);
        std::size_t live = base.node_count();
        branch.release();
        assert(base.node_count() < live && base.contains(2));
        base.release();
        assert(base.empty() && base.node_count() == 0);
    }
    {
        m1une::ds::PartiallyPersistentDsu dsu(4);
        dsu.merge(0, 1);
        dsu.merge(2, 3);
        dsu.release();
        assert(dsu.empty() && dsu.time() == 0);
    }
    {
        auto value = std::make_shared<int>(1);
        std::weak_ptr<int> lifetime = value;
        m1une::ds::PersistentDynamicArray<std::shared_ptr<int>> empty;
        auto version = empty.push_back(value);
        value.reset();
        assert(!lifetime.expired());
        version.release();
        assert(lifetime.expired());
    }
    {
        auto value = std::make_shared<int>(1);
        std::weak_ptr<int> lifetime = value;
        m1une::ds::PersistentStack<std::shared_ptr<int>> empty;
        auto version = empty.push(value);
        value.reset();
        version.release();
        assert(lifetime.expired());
    }
    {
        auto value = std::make_shared<int>(1);
        std::weak_ptr<int> lifetime = value;
        m1une::ds::PersistentQueue<std::shared_ptr<int>> empty;
        auto version = empty.push(value);
        value.reset();
        version.release();
        assert(lifetime.expired());
    }
    {
        auto value = std::make_shared<int>(1);
        std::weak_ptr<int> lifetime = value;
        m1une::ds::PersistentDeque<std::shared_ptr<int>> empty;
        auto version = empty.push_back(value);
        value.reset();
        version.release();
        assert(lifetime.expired());
    }
}

int main() {
    test_release();

    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;
    int n, query_count;
    fast_input >> n >> query_count;
    using Dsu = m1une::ds::PersistentDsu;
    std::vector<Dsu> versions;
    versions.emplace_back(n);
    while (query_count--) {
        int type, version, u, v;
        fast_input >> type >> version >> u >> v;
        const Dsu& base = versions[version + 1];
        if (type == 0) {
            versions.push_back(base.merge(u, v));
        } else {
            fast_output << int(base.same(u, v)) << '\n';
            versions.emplace_back();
        }
    }
}
