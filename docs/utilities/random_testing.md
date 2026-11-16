---
title: Random Testing
documentation_of: ../../utilities/random_testing.hpp
---

## Contest Solution Files (Recommended for Fast I/O)

Use the repository's `stress.py` for an ordinary optimized solution, a separate
brute-force solution, and a generator. The runner uses real child processes and
stdin/stdout pipes, so it works with `FastInput`, `FastOutput`, `scan`, `print`,
`scanf`/`printf`, and iostreams. Global I/O objects and other global state are
fresh on every case. Your solution needs no testing macros or changes to `main`.

From your contest directory, name the files `main.cpp`, `brute.cpp`, and
`gen.cpp`, then run:

```sh
python3 /path/to/m1une_library/stress.py
```

The only generator convention is `gen <seed>`: read an unsigned 64-bit decimal
seed from `argv[1]`, use it to seed the existing `Random`, and print one complete
input to stdout. Write generator diagnostics to stderr. For example:

```cpp
#include "template.hpp"
#include "utilities/random.hpp"

int main(int argc, char** argv) {
    assert(argc == 2);
    m1une::utilities::Random random(std::stoull(argv[1]));
    int n = int(random.uniform(0, 30));
    print(n);
    print(random.sequence(n, -5, 5));
}
```

Small values, duplicates, empty inputs when valid, and boundary cases tend to
find bugs quickly. For a problem with multiple test cases, print `T` and all `T`
cases, just as the normal solution expects; the runner's `--cases` counts
complete program executions.

### Complete working example

The files under
[examples/stress](https://github.com/m1une/m1une_library/tree/main/examples/stress)
count inversions: `main.cpp` uses the library's O(n log n) algorithm,
`brute.cpp` uses O(n²) pair enumeration, and `gen.cpp` uses `Random`. Both
solutions use the usual `pch.hpp`, `solve()`, `scan`, and `print` workflow.
`wrong.cpp` deliberately counts equal values as inversions.

Run these exact commands from the repository root:

```sh
# Correct solution: compiles all three once, then runs 1000 inputs.
python3 stress.py examples/stress/main.cpp examples/stress/brute.cpp examples/stress/gen.cpp --seed 42 --cases 1000

# Deliberately wrong: exits with a failure report on the first mismatch.
python3 stress.py examples/stress/wrong.cpp examples/stress/brute.cpp examples/stress/gen.cpp --seed 42 --cases 1000
```

The failure report prints the complete input, both outputs, exit status or
signal, stderr, initial seed, case number, and case seed. It also saves exact
bytes to a fresh `stress-failure-.../` directory in the current directory:

* `input.txt`, `optimized.out`, `brute.out`
* `generator.out` (the input), `generator.err`, `optimized.err`, `brute.err`
* `report.json` with seeds, statuses, and invocation

Copy the printed `Replay:` command to rerun just the failing input. On
one-based case `k`, the generator seed is `(initial_seed + k - 1) mod 2^64`,
so replay is simply the same command with `--seed CASE_SEED --cases 1`.
The runner stops after this input; it still runs the brute on the failing
input if the optimized solution crashes, so both results are available.
A generator failure skips both solutions and preserves its partial output.

Seed replay assumes the generator uses only the supplied seed for randomness
and the generator/compiler/standard library remain the same. The saved input
is the authoritative reproducer even after code or toolchain changes.

### Typical Codeforces or AtCoder workflow

1. Write `C.cpp` normally with your solution template.
2. Write `brute.cpp` using the same input format and a simple slow algorithm.
3. Write `gen.cpp` to print small valid inputs from `Random(std::stoull(argv[1]))`.
4. Run the tester, fix the first failure, and replay it before trying more seeds.
5. Compile and expand `C.cpp` as usual for submission. Testing stays external.

```sh
# Run from your contest directory; the library include path is added for you.
python3 /path/to/m1une_library/stress.py C.cpp brute.cpp gen.cpp --seed 123 --cases 10000

# With main.cpp/brute.cpp/gen.cpp, positional arguments can be omitted.
python3 /path/to/m1une_library/stress.py --cases 10000
```

An optional shell alias makes the usual invocation `stress --cases 10000`:

```sh
alias stress='python3 /path/to/m1une_library/stress.py'
```

### Options and build behavior

| Argument | Default | Behavior |
| --- | --- | --- |
| `solution brute generator` | `main.cpp brute.cpp gen.cpp` | Paths relative to the current directory; `.cpp`, `.cc`, `.cxx` files are compiled, other paths must be executable files. |
| `--seed N` | Random unsigned 64-bit seed, printed at startup | First case seed; accepts `0` through `18446744073709551615`. |
| `--cases N` | `1000` | Positive number of generated inputs. |
| `--timeout S` | `2` | Positive finite wall-clock seconds for each generator/solution/brute execution; kills the process group on timeout. |
| `--exact` | Off | Compare exact bytes instead of whitespace-separated byte tokens. |
| `--cxx COMMAND` | `CXX`, then `/opt/homebrew/bin/g++-16`, then `g++-16`, then `g++` | Compiler command; quoted wrappers such as `--cxx 'ccache g++-16'` work. |
| `--cxxflags FLAGS` | `CXXFLAGS`, or the flags below | Replaces compiler flags; quote the entire value. |

Default flags are `-std=c++23 -O2 -gdwarf-3 -g -Wall -Wextra -ftrapv`, based
on the VS Code build task, with optimization for stress testing. Assertions
remain enabled. The library root is always added with `-I`; no `LOCAL` or
testing macro is defined. `pch.hpp` keeps its existing optimization pragmas.
The verification-helper configuration still targets GNU C++20; it and the
normal VS Code build are unchanged.

```sh
# Override flags if needed; include the standard and optimization explicitly.
python3 stress.py --cxx /opt/homebrew/bin/g++-16 --cxxflags='-std=c++23 -O2 -g -Wall -Wextra'

# Skip compilation when using binaries you have already built.
python3 stress.py ./solution.out ./brute.out ./gen.out --seed 42
```

Compilation happens once per invocation in an automatically removed temporary
directory. It does not overwrite `a.out` or your other binaries. A compile
failure prevents testing. Exit codes are `0` for all cases passing, `1` for a
mismatch/crash/timeout, `2` for configuration or compilation errors, and `130`
for Ctrl-C. Progress is printed every 100 passing cases.

This compares tokens exactly: extra whitespace is ignored, but `1` and `1.0`
differ. Use `--exact` for whitespace-sensitive output. Floating-point tolerance,
multiple valid answers, and interactive protocols need a problem-specific
checker; use the existing C++ helpers below for those. Keep generated cases
small: input and captured output are held in memory. Starting three processes
per case costs more than function-level testing, but isolates crashes and
tests the complete normal program, including its I/O and initialization.

The runner requires only Python 3.9+ and a C++ compiler on macOS or Linux.
Its focused regression suite compiles the examples and checks mismatches,
seed replay, immediate stopping, signals, nonzero exits, and timeouts:

```sh
python3 verify/utilities/stress_test.py
```

## In-Process Testing

For pure functions, `stress_test(generate, solve, brute, trials, seed)` remains
the fastest option. It reuses `Random` and runs without process startup.
It cannot isolate crashes, `exit()`, or hangs. All existing APIs remain available.

### The Quick Way for Iostream Solutions

You do not need to rewrite a solution to return custom input and answer types.
Keep ordinary contest code that reads `std::cin` and writes `std::cout`:

```cpp
void solve() {
    // The same code used in the submission.
}
```

Then choose one helper:

| Problem | Helper |
| --- | --- |
| Non-interactive or constructive | `stream_stress_test(generate, solve, check)` |
| Interactive | `interactive_stream_stress_test(limit, generate, solve, reply, check)` |

The helper redirects `std::cin` and `std::cout` for every random case. You only
write the random input generator and checker. On failure it prints the input,
output or interaction transcript, seed, and zero-based trial.
These stream helpers do not redirect `FastInput`/`FastOutput` or C stdio;
use `stress.py` above for the normal custom-I/O solution template.

```cpp
#include "utilities/random_testing.hpp"

using namespace m1une::utilities;
```

## Non-Interactive and Constructive Recipe

Replace the generator, solution, and checker bodies below with your problem logic.
The complete sorting example follows this skeleton.

```cpp
#include "utilities/random_testing.hpp"
#include <iostream>

using namespace m1une::utilities;

auto generate = [](Random& random, std::ostream& input) {
    // Write one small random case to input.
};

void solve() {
    // Read std::cin and write std::cout as usual.
}

auto check = [](std::istream& input, std::istream& output) {
    // Read the original input and candidate output.
    return true;  // Return whether the output is valid.
};

int main() {
    stream_stress_test(generate, solve, check);
}
```

This works for constructive problems because `check` validates the output; it
does not compare against one fixed answer.

### Complete example

The following tester checks ordinary code that prints the values in sorted
order:

```cpp
#include "utilities/random_testing.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace m1une::utilities;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> values(n);
    for (int& value : values) std::cin >> value;

    std::sort(values.begin(), values.end());
    for (int value : values) std::cout << value << ' ';
    std::cout << '\n';
}

int main() {
    auto generate = [](Random& random, std::ostream& input) {
        int n = int(random.uniform(0, 20));
        input << n << '\n';
        for (int value : random.sequence(n, -10, 10)) {
            input << value << ' ';
        }
        input << '\n';
    };

    auto check = [](std::istream& input, std::istream& output) {
        int n;
        input >> n;
        std::vector<int> expected(n);
        for (int& value : expected) input >> value;
        std::sort(expected.begin(), expected.end());

        std::vector<int> actual(n);
        for (int& value : actual) {
            if (!(output >> value)) return false;
        }
        std::string extra;
        return actual == expected && !(output >> extra);
    };

    stream_stress_test(generate, solve, check);
}
```

Usually the generator is just a few `random.uniform(...)` calls and `<<`
operations. The checker can reuse input constraints and validation logic from
the problem statement.

The default is 1000 cases with a fixed seed. Add a trial count and seed at the
end when needed:

```cpp
stream_stress_test(generate, solve, check, 10000, 123456789);
```

## Interactive Recipe

The submitted solution can keep the ordinary protocol:

```cpp
std::cout << "? " << query << std::endl;
std::cin >> reply;
// ...
std::cout << "! " << answer << std::endl;
```

The tester needs four pieces:

1. `generate` writes the public input and returns hidden judge state;
2. `solve` is the ordinary interactive solution;
3. `reply` reads one query and writes the mock judge's response;
4. `check` validates the final output.

### Complete example

```cpp
#include "utilities/random_testing.hpp"

#include <iostream>
#include <string>

using namespace m1une::utilities;

void solve() {
    int upper;
    std::cin >> upper;

    int low = 0;
    int high = upper;
    while (low < high) {
        int middle = (low + high) / 2;
        std::cout << "? " << middle << std::endl;

        int comparison;
        std::cin >> comparison;
        if (comparison <= 0) high = middle;
        else low = middle + 1;
    }
    std::cout << "! " << low << std::endl;
}

int main() {
    auto generate = [](Random& random, std::ostream& input) {
        int upper = 1000;
        input << upper << '\n';
        return int(random.uniform(0, upper));  // Hidden number.
    };

    auto reply = [](int& secret, std::istream& query,
                    std::ostream& response) {
        char type;
        int guess;
        std::string extra;
        if (!(query >> type >> guess) || type != '?' || query >> extra) {
            reject_query("expected: ? x");
        }

        if (secret < guess) response << -1;
        else if (guess < secret) response << 1;
        else response << 0;
    };

    auto check = [](std::istream& input, const int& secret,
                    std::istream& output) {
        int upper;
        char type;
        int answer;
        std::string extra;
        input >> upper;
        return bool(output >> type >> answer) && type == '!' &&
               0 <= answer && answer <= upper && answer == secret &&
               !(output >> extra);
    };

    interactive_stream_stress_test(10, generate, solve, reply, check);
}
```

When `solve` tries to read after printing, the helper sends that pending output
to `reply` and feeds the generated response back through `std::cin`. Output
remaining when `solve` returns is passed to `check` as the final answer.

Call `reject_query("reason")` for malformed or forbidden queries. The first
query beyond the limit also fails. Both failures include the full query/reply
transcript.

Select trials and a seed with trailing arguments:

```cpp
interactive_stream_stress_test(
    query_limit, generate, solve, reply, check, 10000, 123456789);
```

## Practical Limitations

The stream helpers redirect C++ `std::cin` and `std::cout`. They cannot capture
`scanf`, `printf`, `fread`, `FastInput`, or other code that accesses the C file
handles directly. Keep a `std::cin`/`std::cout` version while stress testing, or
move only the algorithm into a shared function used by both I/O frontends.

Call `std::ios::sync_with_stdio(false)` before starting the tester, not inside
`solve`, because changing synchronization can replace standard stream buffers.

The interactive helper runs in one process without real pipes. It checks the
algorithm and protocol, but it does not detect missing flushes, deadlocks, or
timing problems.

## Typed Helpers (Optional)

Use the typed interface only when the solution already accepts values and
returns an answer.

For ordinary optimized-vs-brute testing:

```cpp
stress_test(generate, solve, brute);
```

For constructive testing:

```cpp
constructive_stress_test(
    generate,
    solve,
    [](const Input& input, const Answer& answer) {
        return is_valid(input, answer);
    });
```

For a typed interactive solution, generate public input and hidden state with
`interactive_test_case(input, state)`. The solution receives the public input
and an object providing `interaction.ask(query)`:

```cpp
interactive_stress_test(
    query_limit, generate, solve, reply, check);
```

The stream and typed interfaces use the same deterministic seeds, failure
categories, query limits, and transcript reporting.

## Handle Failure Without Aborting

The `*_stress_test` helpers print a failure and call `std::abort`. Use the
lower-level version to inspect a result instead:

```cpp
RandomTestConfig config;
config.trials = 10000;
config.seed = 123456789;

auto result = test_streams(config, generate, solve, check);
if (!result) {
    // result.seed
    // result.failed_trial
    // result.failure
}
```

The interactive equivalent is:

```cpp
auto result = test_interactive_streams(
    config, query_limit, generate, solve, reply, check);
```

| Result field | Meaning |
| --- | --- |
| `seed` | Seed used by the generator. |
| `requested_trials` | Number of requested cases. |
| `completed_trials` | Cases that passed before the failure. |
| `failed_trial` | Zero-based failed case, or `-1` on success. |
| `failure` | `property`, `mismatch`, `rejected_output`, `query_limit`, or `invalid_query`. |
| `query_count` | Attempted queries on an interactive failure, otherwise `-1`. |

`result.passed()` and `bool(result)` report success.

## Interface Reference

```cpp
template <class Generator, class Solution, class Checker>
RandomTestResult stream_stress_test(
    Generator generator,
    Solution solution,
    Checker checker,
    int trials = 1000,
    std::uint64_t seed = default_random_test_seed);

template <class Generator, class Solution, class QueryHandler, class Checker>
RandomTestResult interactive_stream_stress_test(
    int query_limit,
    Generator generator,
    Solution solution,
    QueryHandler query_handler,
    Checker checker,
    int trials = 1000,
    std::uint64_t seed = default_random_test_seed);
```

The lower-level forms add a configuration and optional failure callback:

```cpp
template <class Generator, class Solution, class Checker,
          class OnFailure = IgnoreRandomTestFailure>
RandomTestResult test_streams(
    RandomTestConfig config,
    Generator generator,
    Solution solution,
    Checker checker,
    OnFailure on_failure = {});

template <class Generator, class Solution, class QueryHandler, class Checker,
          class OnFailure = IgnoreRandomTestFailure>
RandomTestResult test_interactive_streams(
    RandomTestConfig config,
    int query_limit,
    Generator generator,
    Solution solution,
    QueryHandler query_handler,
    Checker checker,
    OnFailure on_failure = {});
```

The non-interactive callback is called as
`on_failure(input_text, output_text, trial, seed)`. The interactive callback is
called as `on_failure(input_text, state, transcript, trial, seed, failure)`.

Generators may also accept a final `int trial`. The non-interactive generator
returns `void`; the interactive generator returns the hidden state. Query
handlers return `void` and write their response to the supplied output stream.

The harness adds $O(1)$ work per trial apart from the supplied functions and
the size of generated/captured text. Interactive transcript time and memory are
linear in the total query and response text.
