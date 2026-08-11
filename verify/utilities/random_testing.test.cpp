#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../utilities/random_testing.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include "../../utilities/fast_io.hpp"
#include <numeric>
#include <string>
#include <vector>

#ifndef NDEBUG
void test_properties() {
    using namespace m1une::utilities;

    RandomTestConfig config;
    config.trials = 100;
    config.seed = 12345;
    RandomTestResult success = random_test(config, [](Random& random) {
        long long value = random.uniform(-1000, 1000);
        return value * value >= 0;
    });
    assert(success.passed());
    assert(bool(success));
    assert(success.completed_trials == 100);
    assert(success.failed_trial == -1);
    assert(success.seed == config.seed);

    RandomTestResult failure = random_test(
        config, [](Random&, int trial) { return trial != 17; });
    assert(!failure.passed());
    assert(!bool(failure));
    assert(failure.completed_trials == 17);
    assert(failure.failed_trial == 17);
    assert(failure.failure == RandomTestFailure::property);

    auto shorthand = random_test([](Random&, int trial) { return trial < 1000; });
    assert(shorthand.passed());
    auto required = stress_test(
        [](Random&, int trial) { return trial < 25; }, 25, 777);
    assert(required.passed());
    assert(required.seed == 777);
}

void test_comparison() {
    using namespace m1une::utilities;

    RandomTestConfig config;
    config.trials = 500;
    config.seed = 67890;
    auto success = compare_randomly(
        config,
        [](Random& random) {
            int size = int(random.uniform(0, 20));
            std::vector<int> values(size);
            for (int& value : values) value = int(random.uniform(-20, 20));
            return values;
        },
        [](std::vector<int>& values) {
            std::sort(values.begin(), values.end());
            return values;
        },
        [](std::vector<int>& values) {
            for (int i = 0; i < int(values.size()); i++) {
                for (int j = i + 1; j < int(values.size()); j++) {
                    if (values[j] < values[i]) std::swap(values[i], values[j]);
                }
            }
            return values;
        });
    assert(success.passed());

    auto mutation_isolated = compare_randomly(
        config,
        [](Random& random) {
            int size = int(random.uniform(0, 20));
            std::vector<int> values(size);
            for (int& value : values) value = int(random.uniform(-20, 20));
            return values;
        },
        [](std::vector<int>& values) {
            int sum = std::accumulate(values.begin(), values.end(), 0);
            values.clear();
            return sum;
        },
        [](std::vector<int>& values) {
            return std::accumulate(values.begin(), values.end(), 0);
        });
    assert(mutation_isolated.passed());

    auto quick = stress_test(
        [](Random& random) { return int(random.uniform(-10, 10)); },
        [](int& value) { return value * value; },
        [](int& value) {
            int magnitude = value < 0 ? -value : value;
            int result = 0;
            for (int i = 0; i < magnitude; i++) result += magnitude;
            return result;
        },
        50, 999);
    assert(quick.passed());

    int callback_count = 0;
    int callback_trial = -1;
    int callback_case = -1;
    int callback_expected = -1;
    int callback_actual = -1;
    std::uint64_t callback_seed = 0;
    auto failure = compare_randomly(
        config,
        [](Random&, int trial) { return trial; },
        [](int& value) { return value == 23 ? value + 1 : value; },
        [](int& value) { return value; },
        [&](int input, int expected, int actual, int trial,
            std::uint64_t seed) {
            callback_count++;
            callback_trial = trial;
            callback_case = input;
            callback_expected = expected;
            callback_actual = actual;
            callback_seed = seed;
        });
    assert(failure.failed_trial == 23);
    assert(failure.failure == RandomTestFailure::mismatch);
    assert(callback_count == 1);
    assert(callback_trial == 23);
    assert(callback_case == 23);
    assert(callback_expected == 23);
    assert(callback_actual == 24);
    assert(callback_seed == config.seed);

    RandomTestConfig empty_config;
    empty_config.trials = 0;
    auto empty = random_test(empty_config, [](Random&) { return false; });
    assert(empty.passed());
    assert(empty.completed_trials == 0);
}

void test_constructive() {
    using namespace m1une::utilities;

    RandomTestConfig config;
    config.trials = 200;
    config.seed = 13579;
    auto success = test_constructively(
        config,
        [](Random& random) {
            int size = int(random.uniform(0, 30));
            return random.sequence(size, -20, 20);
        },
        [](std::vector<int>& values) {
            std::vector<int> order(values.size());
            std::iota(order.begin(), order.end(), 0);
            std::sort(order.begin(), order.end(), [&](int first, int second) {
                return values[first] < values[second];
            });
            values.clear();
            return order;
        },
        [](const std::vector<int>& values, const std::vector<int>& order) {
            if (values.size() != order.size()) return false;
            std::vector<bool> used(values.size());
            for (int index = 0; index < int(order.size()); index++) {
                if (order[index] < 0 || int(values.size()) <= order[index]) {
                    return false;
                }
                if (used[order[index]]) return false;
                used[order[index]] = true;
                if (0 < index &&
                    values[order[index]] < values[order[index - 1]]) {
                    return false;
                }
            }
            return true;
        });
    assert(success.passed());

    int callback_count = 0;
    auto failure = test_constructively(
        config, [](Random&, int trial) { return trial + 1; },
        [](int& value) { return value == 8 ? 0 : value; },
        [](int input, int answer) { return input == answer; },
        [&](int input, int answer, int trial, std::uint64_t seed) {
            callback_count++;
            assert(input == 8);
            assert(answer == 0);
            assert(trial == 7);
            assert(seed == config.seed);
        });
    assert(failure.failed_trial == 7);
    assert(failure.failure == RandomTestFailure::rejected_output);
    assert(callback_count == 1);

    auto quick = constructive_stress_test(
        [](Random& random) { return int(random.uniform(0, 100)); },
        [](int& value) { return value; },
        [](const int& input, const int& answer) { return input == answer; },
        20, 97531);
    assert(quick.passed());
}

void test_interactive() {
    using namespace m1une::utilities;

    RandomTestConfig config;
    config.trials = 300;
    config.seed = 24680;
    auto success = test_interactively(
        config, 10,
        [](Random& random) {
            int upper = int(random.uniform(1, 1000));
            int secret = int(random.uniform(0, upper));
            return interactive_test_case(upper, secret);
        },
        [](const int& upper, auto& interaction) {
            int low = 0;
            int high = upper;
            while (low < high) {
                int middle = (low + high) / 2;
                int comparison = interaction.ask(middle);
                if (comparison <= 0) {
                    high = middle;
                } else {
                    low = middle + 1;
                }
            }
            return low;
        },
        [](int& secret, int guess) {
            if (guess < 0) reject_query("negative guess");
            if (secret < guess) return -1;
            if (guess < secret) return 1;
            return 0;
        },
        [](const int& upper, const int& secret, const int& answer) {
            return 0 <= answer && answer <= upper && answer == secret;
        });
    assert(success.passed());

    RandomTestConfig one_trial;
    one_trial.trials = 1;
    one_trial.seed = 112233;
    int callback_count = 0;
    auto invalid = test_interactively(
        one_trial, 5,
        [](Random&) { return interactive_test_case(10, 4); },
        [](const int&, auto& interaction) {
            interaction.ask(-1);
            return 0;
        },
        [](int&, int query) {
            if (query < 0) reject_query("query is outside [0, 10]");
            return 0;
        },
        [](const int&, const int&, const int&) { return true; },
        [&](const auto&, const InteractionTranscript& transcript, int trial,
            std::uint64_t seed, RandomTestFailure reason) {
            callback_count++;
            assert(trial == 0);
            assert(seed == one_trial.seed);
            assert(reason == RandomTestFailure::invalid_query);
            assert(transcript.exchanges.size() == 1);
            assert(transcript.exchanges[0].query == "-1");
            assert(!transcript.exchanges[0].responded);
            assert(transcript.failure_message ==
                   "query is outside [0, 10]");
        });
    assert(invalid.failure == RandomTestFailure::invalid_query);
    assert(invalid.query_count == 1);
    assert(callback_count == 1);

    auto too_many_queries = test_interactively(
        one_trial, 1,
        [](Random&) { return interactive_test_case(0, 0); },
        [](auto& interaction) {
            interaction.ask(1);
            interaction.ask(2);
            return 0;
        },
        [](int&, int query) { return query; },
        [](const int&, const int&, const int&) { return true; });
    assert(too_many_queries.failure == RandomTestFailure::query_limit);
    assert(too_many_queries.query_count == 2);

    auto wrong_answer = test_interactively(
        one_trial, 0,
        [](Random&) { return interactive_test_case(10, 7); },
        [](const int&, auto&) { return 6; },
        [](int&, int query) { return query; },
        [](const int&, const int& secret, const int& answer) {
            return secret == answer;
        });
    assert(wrong_answer.failure == RandomTestFailure::rejected_output);
    assert(wrong_answer.query_count == 0);

    auto quick = interactive_stress_test(
        0,
        [](Random& random) {
            int value = int(random.uniform(-100, 100));
            return interactive_test_case(value, value);
        },
        [](const int& input, auto&) { return input; },
        [](int&, int query) { return query; },
        [](const int&, const int& state, const int& answer) {
            return state == answer;
        },
        20, 86420);
    assert(quick.passed());
}

void test_stream_interface() {
    using namespace m1une::utilities;

    RandomTestConfig config;
    config.trials = 200;
    config.seed = 424242;
    auto generate = [](Random& random, std::ostream& input) {
        int size = int(random.uniform(0, 30));
        input << size << '\n';
        for (int value : random.sequence(size, -20, 20)) {
            input << value << ' ';
        }
        input << '\n';
    };
    auto solve = [] {
        int size;
        std::cin >> size;
        std::vector<int> values(size);
        for (int& value : values) std::cin >> value;
        std::sort(values.begin(), values.end());
        for (int value : values) std::cout << value << ' ';
        std::cout << '\n';
    };
    auto check = [](std::istream& input, std::istream& output) {
        int size;
        input >> size;
        std::vector<int> expected(size);
        for (int& value : expected) input >> value;
        std::sort(expected.begin(), expected.end());
        std::vector<int> actual(size);
        for (int& value : actual) {
            if (!(output >> value)) return false;
        }
        std::string extra;
        return expected == actual && !(output >> extra);
    };
    auto success = test_streams(config, generate, solve, check);
    assert(success.passed());

    int callback_count = 0;
    RandomTestConfig one_trial;
    one_trial.trials = 1;
    one_trial.seed = 515151;
    auto failure = test_streams(
        one_trial,
        [](Random&, std::ostream& input) { input << "3\n1 2 3\n"; },
        [] {
            int size;
            std::cin >> size;
            std::cout << size - 1 << '\n';
        },
        [](std::istream&, std::istream& output) {
            int answer;
            return bool(output >> answer) && answer == 3;
        },
        [&](const std::string& input, const std::string& output, int trial,
            std::uint64_t seed) {
            callback_count++;
            assert(input == "3\n1 2 3\n");
            assert(output == "2\n");
            assert(trial == 0);
            assert(seed == one_trial.seed);
        });
    assert(failure.failure == RandomTestFailure::rejected_output);
    assert(callback_count == 1);

    auto quick = stream_stress_test(generate, solve, check, 20, 616161);
    assert(quick.passed());
}

void test_interactive_stream_interface() {
    using namespace m1une::utilities;

    auto generate = [](Random& random, std::ostream& input) {
        int upper = int(random.uniform(1, 1000));
        input << upper << '\n';
        return int(random.uniform(0, upper));
    };
    auto solve = [] {
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

    auto success = interactive_stream_stress_test(
        10, generate, solve, reply, check, 200, 717171);
    assert(success.passed());

    RandomTestConfig one_trial;
    one_trial.trials = 1;
    one_trial.seed = 818181;
    int callback_count = 0;
    auto invalid = test_interactive_streams(
        one_trial, 1,
        [](Random&, std::ostream& input) {
            input << "10\n";
            return 5;
        },
        [] {
            int upper;
            std::cin >> upper;
            std::cout << "invalid query" << std::endl;
            int response;
            std::cin >> response;
        },
        reply, check,
        [&](const std::string& input, const int& state,
            const InteractionTranscript& transcript, int trial,
            std::uint64_t seed, RandomTestFailure reason) {
            callback_count++;
            assert(input == "10\n");
            assert(state == 5);
            assert(transcript.exchanges.size() == 1);
            assert(transcript.exchanges[0].query == "invalid query");
            assert(!transcript.exchanges[0].responded);
            assert(transcript.failure_message == "expected: ? x");
            assert(trial == 0);
            assert(seed == one_trial.seed);
            assert(reason == RandomTestFailure::invalid_query);
        });
    assert(invalid.failure == RandomTestFailure::invalid_query);
    assert(invalid.query_count == 1);
    assert(callback_count == 1);

    auto query_limit = test_interactive_streams(
        one_trial, 0,
        [](Random&, std::ostream& input) {
            input << "10\n";
            return 5;
        },
        [] {
            int upper;
            std::cin >> upper;
            std::cout << "? 5" << std::endl;
            int response;
            std::cin >> response;
        },
        reply, check);
    assert(query_limit.failure == RandomTestFailure::query_limit);
    assert(query_limit.query_count == 1);
}
#endif

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

#ifndef NDEBUG
    test_properties();
    test_comparison();
    test_constructive();
    test_interactive();
    test_stream_interface();
    test_interactive_stream_interface();
#endif

    long long a, b;
    fast_input >> a >> b;
    fast_output << a + b << '\n';
}
