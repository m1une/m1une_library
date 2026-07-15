---
title: Fast IO
documentation_of: ../../utilities/fast_io.hpp
---

## Overview

`FastInput` and `FastOutput` are buffered replacements for `std::cin` and
`std::cout`. They provide familiar, chainable `operator>>` and `operator<<`
syntax while using `std::FILE*` internally. By default they read from `stdin`
and write to `stdout`. Terminal input is read one line at a time, so entered
values become available as soon as Enter is pressed; redirected input keeps the
larger high-throughput buffer.

```cpp
FastInput input;
FastOutput output;

int n;
input >> n;
output << n << '\n';
```

All names are in `m1une::utilities`.

## Supported types

Both operators support integral and floating-point types, including GCC/Clang
`__int128_t` and `__uint128_t`, as well as `bool`, `char`, `std::string`, and
`std::pair`. Pair members can be any recursively supported types. A ModInt-like
type must provide `value.val()` for output and be constructible from `long long`
for input. Output additionally accepts null-terminated C strings.

Ranges recognized by `std::begin` and `std::end` are also supported, including
ordinary arrays, `std::array`, and nested containers. Strings are treated as
single values rather than ranges of characters.

## Pairs

Pair members are read as two consecutive values and written with one space
between them:

```cpp
std::pair<int, std::string> item;
input >> item;             // Input: 3 apple
output << item << '\n';    // Output: 3 apple
```

## Vectors and other ranges

Input never changes a container's size. Allocate every dimension before using
`operator>>`:

```cpp
int n;
input >> n;
std::vector<int> a(n);
input >> a;

int h, w;
input >> h >> w;
std::vector<std::vector<int>> matrix(h, std::vector<int>(w));
input >> matrix;
```

Elements are processed in iteration order. Nested ranges are processed
recursively, so the matrix above is read in row-major order. Empty ranges read
nothing. `std::vector<bool>` is supported.

For output, elements of a one-dimensional range are separated by spaces by
default. Change that separator when a different layout is useful:

```cpp
output << a << '\n';                    // 1 2 3
output.set_range_separator('\n');
output << a << '\n';                    // One element per line
output.set_range_separator(' ');        // Restore the default
output << matrix << '\n';
```

When elements are themselves ranges, they are always separated by newlines.
The configured separator is used recursively between scalar elements. It also
separates pairs stored in a range, while the two members of each pair remain
space-separated; this makes newline mode convenient for edge lists.

For `a = {1, 2, 3}` and a two-row matrix, the result is:

```text
1 2 3
1 2 3
4 5 6
```

No trailing separator is written by the range itself. Add `<< '\n'` when a
final newline is wanted. Higher-dimensional ranges use a newline at every
nested-range boundary and the configured separator between scalar values.

## Interface

### `FastInput`

| Method | Description | Complexity |
| --- | --- | --- |
| `FastInput(std::FILE* stream = stdin)` | Creates an input buffer for `stream`. | $O(1)$ |
| `FastInput& operator>>(T& value)` | Reads one value or a pre-sized range and returns `*this`. | Linear in consumed input |
| `bool read(T& value)` | Reads one value and reports whether input was available. | Linear in consumed input |
| `bool read(a, b, ...)` | Reads several values and returns `false` if any read fails. | Linear in consumed input |
| `int read_char_raw()` | Reads the next byte without skipping whitespace, or returns `EOF`. | Amortized $O(1)$ |
| `bool skip_spaces()` | Skips whitespace and reports whether a token remains. | Linear in skipped input |

`operator>>` is intended for valid contest input and aborts if an expected token
is missing. Use `read(...)` when EOF or malformed/missing input must be
detected.

### `FastOutput`

| Method | Description | Complexity |
| --- | --- | --- |
| `FastOutput(std::FILE* stream = stdout)` | Creates an output buffer for `stream`. | $O(1)$ |
| `FastOutput& operator<<(const T& value)` | Writes a value or range and returns `*this`. | Linear in produced output |
| `void write(value)` | Writes one value or range without an added separator. | Linear in produced output |
| `void print(a, b, ...)` | Writes several values separated by spaces. | Linear in produced output |
| `void println(a, b, ...)` | Calls `print`, then writes a newline. | Linear in produced output |
| `void println()` | Writes a newline. | Amortized $O(1)$ |
| `void set_precision(int precision)` | Changes the number of significant or fractional digits used for floating-point output. | $O(1)$ |
| `void set_fixed(int precision = 6)` | Selects fixed-point output with `precision` fractional digits. | $O(1)$ |
| `void set_general(int precision = 6)` | Selects general floating-point output with `precision` significant digits. | $O(1)$ |
| `void set_range_separator(char separator)` | Changes the separator between non-range elements of ranges. | $O(1)$ |
| `void flush()` | Writes all buffered bytes to the underlying stream. | Linear in buffered output |

Pending output is flushed by the destructor. Standard iostream manipulators
such as `std::endl` are not supported; use `output << '\n'` and call `flush()`
explicitly only when the output must become visible immediately.

## Example

```cpp
#include "utilities/fast_io.hpp"

#include <vector>

using m1une::utilities::FastInput;
using m1une::utilities::FastOutput;

int main() {
    FastInput input;
    FastOutput output;

    int n;
    input >> n;

    std::vector<long long> a(n);
    input >> a;

    long long sum = 0;
    for (long long x : a) sum += x;

    output << sum << '\n';
    output << a << '\n';
}
```
