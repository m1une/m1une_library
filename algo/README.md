# Algorithms

Use this directory for one-shot algorithms and optimization helpers that do not
maintain a long-lived query/update object.

| Category | Headers |
| --- | --- |
| [`sequence/`](sequence/) | `lis.hpp`, `inversion_count.hpp`, `subset_sum.hpp`, and `all.hpp` |
| [`dp_optimization/`](dp_optimization/) | `alien_trick.hpp`, Monge/SMAWK/Knuth/D&C helpers under `monge/`, and `all.hpp` |

Stateful query structures such as Li Chao tree, CHT, and slope trick live under
`ds/`.

Namespaces stay flat and short:

| Directory | Namespace |
| --- | --- |
| `algo/sequence/` | `m1une::sequence` |
| `algo/dp_optimization/alien_trick.hpp` | `m1une::dp` |
| `algo/dp_optimization/monge/` | `m1une::monge` |
