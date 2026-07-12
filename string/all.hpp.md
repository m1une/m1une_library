---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fps/convolution.hpp
    title: Convolution
  - icon: ':heavy_check_mark:'
    path: math/fps/internal/ntt998_faster.hpp
    title: math/fps/internal/ntt998_faster.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: string/aho_corasick.hpp
    title: Aho-Corasick
  - icon: ':heavy_check_mark:'
    path: string/eertree.hpp
    title: Eertree
  - icon: ':heavy_check_mark:'
    path: string/kmp.hpp
    title: Knuth-Morris-Pratt
  - icon: ':heavy_check_mark:'
    path: string/levenshtein_distance.hpp
    title: Levenshtein Distance
  - icon: ':heavy_check_mark:'
    path: string/longest_common_extension.hpp
    title: Longest Common Extension
  - icon: ':heavy_check_mark:'
    path: string/longest_common_subsequence.hpp
    title: Longest Common Subsequence
  - icon: ':heavy_check_mark:'
    path: string/longest_common_substring.hpp
    title: Longest Common Substring
  - icon: ':heavy_check_mark:'
    path: string/lyndon_factorization.hpp
    title: Lyndon Factorization
  - icon: ':heavy_check_mark:'
    path: string/manacher.hpp
    title: Manacher Algorithm
  - icon: ':heavy_check_mark:'
    path: string/minimum_rotation.hpp
    title: Minimum Rotation
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash.hpp
    title: Static Rolling Hash
  - icon: ':heavy_check_mark:'
    path: string/runs.hpp
    title: Runs
  - icon: ':heavy_check_mark:'
    path: string/string_hash.hpp
    title: String Hash
  - icon: ':heavy_check_mark:'
    path: string/suffix_array.hpp
    title: Suffix Array and LCP Array
  - icon: ':heavy_check_mark:'
    path: string/suffix_automaton.hpp
    title: Suffix Automaton
  - icon: ':heavy_check_mark:'
    path: string/trie.hpp
    title: Trie
  - icon: ':heavy_check_mark:'
    path: string/wildcard_pattern_matching.hpp
    title: Wildcard Pattern Matching
  - icon: ':heavy_check_mark:'
    path: string/z_algorithm.hpp
    title: Z Algorithm
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/fps/convolution.hpp: line 19: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: '#ifndef M1UNE_STRING_ALL_HPP

    #define M1UNE_STRING_ALL_HPP 1


    #include "aho_corasick.hpp"

    #include "eertree.hpp"

    #include "kmp.hpp"

    #include "levenshtein_distance.hpp"

    #include "longest_common_extension.hpp"

    #include "longest_common_subsequence.hpp"

    #include "longest_common_substring.hpp"

    #include "lyndon_factorization.hpp"

    #include "manacher.hpp"

    #include "minimum_rotation.hpp"

    #include "rolling_hash.hpp"

    #include "runs.hpp"

    #include "string_hash.hpp"

    #include "suffix_automaton.hpp"

    #include "suffix_array.hpp"

    #include "trie.hpp"

    #include "wildcard_pattern_matching.hpp"

    #include "z_algorithm.hpp"


    #endif  // M1UNE_STRING_ALL_HPP

    '
  dependsOn:
  - string/aho_corasick.hpp
  - string/eertree.hpp
  - string/kmp.hpp
  - string/levenshtein_distance.hpp
  - string/longest_common_extension.hpp
  - string/suffix_array.hpp
  - string/longest_common_subsequence.hpp
  - string/longest_common_substring.hpp
  - string/lyndon_factorization.hpp
  - string/minimum_rotation.hpp
  - string/manacher.hpp
  - string/rolling_hash.hpp
  - string/runs.hpp
  - string/string_hash.hpp
  - string/suffix_automaton.hpp
  - string/trie.hpp
  - string/wildcard_pattern_matching.hpp
  - math/fps/convolution.hpp
  - math/fps/internal/ntt998_faster.hpp
  - math/modint.hpp
  - string/z_algorithm.hpp
  isVerificationFile: false
  path: string/all.hpp
  requiredBy: []
  timestamp: '2026-07-13 05:39:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/string_algorithms.test.cpp
documentation_of: string/all.hpp
layout: document
title: String Algorithms Bundle
---

## Overview

`string/all.hpp` includes the reusable string algorithms in this repository.
Use individual headers when compile time matters, or this bundle during a
contest when convenience matters more.

## Included Headers

| Header | Contents |
| --- | --- |
| `string/aho_corasick.hpp` | Multi-pattern matching with failure links and occurrence counting. |
| `string/eertree.hpp` | Online palindromic tree with suffix and series links. |
| `string/levenshtein_distance.hpp` | Unit-cost edit distance in linear auxiliary memory. |
| `string/kmp.hpp` | Prefix function and linear-time KMP occurrence search. |
| `string/longest_common_extension.hpp` | Static longest-common-extension queries and substring comparisons. |
| `string/longest_common_subsequence.hpp` | Finds one longest subsequence common to two sequences. |
| `string/longest_common_substring.hpp` | Finds one longest substring common to two sequences. |
| `string/lyndon_factorization.hpp` | Duval's linear-time Lyndon factorization. |
| `string/z_algorithm.hpp` | Linear-time Z array. |
| `string/manacher.hpp` | Odd/even palindrome radii and substring checks. |
| `string/minimum_rotation.hpp` | Earliest lexicographically minimum cyclic shift in linear time. |
| `string/suffix_automaton.hpp` | Online suffix automaton for substring queries and occurrence classes. |
| `string/suffix_array.hpp` | Suffix array and LCP array. |
| `string/trie.hpp` | Contiguous-alphabet multiset trie with prefix queries. |
| `string/wildcard_pattern_matching.hpp` | Exact wildcard matching at every text alignment. |
| `string/rolling_hash.hpp` | Static substring hashing, LCP, and comparison. |
| `string/runs.hpp` | Enumerates maximal periodic substrings and their minimum periods. |
| `string/string_hash.hpp` | Double whole-string hashing and constant-time hash concatenation. |
