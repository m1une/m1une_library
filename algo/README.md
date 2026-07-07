# Algorithms

Use this directory for one-shot algorithms that are not tied to another domain.
Convex optimization helpers live under `convex/`, and mutable query/update
objects live under `ds/`.

| Category | Headers |
| --- | --- |
| [`sequence/`](sequence/) | `lis.hpp`, `inversion_count.hpp`, `run_length_encoding.hpp`, `subset_sum.hpp`, and `all.hpp` |
| [`search/`](search/) | `bisect.hpp` and `all.hpp` |
| [`offline/`](offline/) | `mo.hpp` and `all.hpp` |
| [`enumeration/`](enumeration/) | `gray_code.hpp` and `all.hpp` |

Convex tools such as Li Chao tree, CHT, slope trick, Alien Trick, and Monge
optimization live under `convex/`.

Ideas for future additions are tracked in [`TODO.md`](TODO.md).

Namespaces stay flat and short:

| Directory | Namespace |
| --- | --- |
| `algo/` | `m1une::algo` |
