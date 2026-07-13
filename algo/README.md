# Algorithms

Use this directory for one-shot algorithms that are not tied to another domain.
If a header builds an object and then answers repeated queries, it belongs in
`ds/` instead; for example, cumulative sums live in `ds/range_query/`.
Convex optimization helpers live under `convex/`, and mutable query/update
objects live under `ds/`.

| Category | Headers |
| --- | --- |
| [`sequence/`](sequence/) | `lis.hpp`, `inversion_count.hpp`, `number_of_subsequences.hpp`, `run_length_encoding.hpp`, `subset_sum.hpp`, and `all.hpp` |
| [`search/`](search/) | `bisect.hpp`, `golden_section_search.hpp`, `ternary_search.hpp`, and `all.hpp` |
| [`offline/`](offline/) | `mo.hpp`, `parallel_binary_search.hpp`, `cdq_divide_and_conquer.hpp`, and `all.hpp` |
| [`enumeration/`](enumeration/) | `gray_code.hpp`, `submask.hpp`, `combination.hpp`, `segtree_range.hpp`, and `all.hpp` |
| [`dp/`](dp/) | `knapsack.hpp` and `all.hpp` |

Convex tools such as Li Chao tree, CHT, slope trick, Alien Trick, and Monge
optimization live under `convex/`.

Namespaces stay flat and short:

| Directory | Namespace |
| --- | --- |
| `algo/` | `m1une::algo` |
