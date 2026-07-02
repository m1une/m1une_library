---
title: Beats Acted Monoid Concept
documentation_of: ../../acted_monoid/beats_concept.hpp
---

## Overview

`m1une::acted_monoid::IsBeatsActedMonoid<AM>` extends
`IsActedMonoid<AM>` with:

```cpp
static bool can_apply(
    const operator_type& f,
    const value_type& x
);
```

It is used by `ds::SegtreeBeats`. A true result promises that `mapping(f, x)`
can update the whole represented segment. A false result requires descent and
forbids both calling `mapping` at that node and composing `f` into its lazy
tag. Every valid update must eventually be applicable at every real leaf. The
identity operator must always be applicable and leave values unchanged.

`op_comp(f, g)` means applying `g` first, then `f`.

Optional three-argument `can_apply` and `mapping` overloads and optional
`op_shift` are recognized by `SegtreeBeats`; they are not additional concept
requirements.
