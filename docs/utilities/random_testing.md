---
title: Random Testing
documentation_of: ../../utilities/random_testing.hpp
---

## The Quick Way

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

```cpp
#include "utilities/random_testing.hpp"

using namespace m1une::utilities;
```

## Non-Interactive and Constructive Recipe

Write these three pieces:

```cpp
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
