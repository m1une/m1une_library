---
title: Game Library
documentation_of: ../../game/all.hpp
---

## Overview

`game/all.hpp` includes the game-theory library. Public APIs use the
`m1une::game` namespace.

## Included Headers

| Header | Contents |
| --- | --- |
| `game/nim.hpp` | Ordinary and misere Nim outcomes and winning moves. |
| `game/nim_product.hpp` | 64-bit nimber multiplication, powers, inverses, and quotients. |
| `game/grundy.hpp` | Linear-time Sprague-Grundy numbers for finite DAG games. |
| `game/retrograde_analysis.hpp` | Win/lose/draw classification and strategy recovery for finite directed games, including cycles. |
| `game/partisan_game.hpp` | Four outcome classes for finite short partisan games. |
| `game/minimax.hpp` | Backward-induction values and optimal moves for scoring games on DAGs. |
| `game/subtraction_game.hpp` | Grundy tables and multi-heap outcomes for subtraction games. |
| `game/green_hackenbush.hpp` | Linear-time Grundy numbers for Green Hackenbush forests. |
| `game/silver_dollar_game.hpp` | Linear-time Grundy numbers for coin-sliding positions. |
