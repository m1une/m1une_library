#ifndef M1UNE_RANDOM_TESTING_HPP
#define M1UNE_RANDOM_TESTING_HPP 1

#include <cassert>
#include <concepts>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include "random.hpp"

namespace m1une {
namespace utilities {

inline constexpr std::uint64_t default_random_test_seed =
    0x243f6a8885a308d3ULL;

struct RandomTestConfig {
    int trials = 1000;
    std::uint64_t seed = default_random_test_seed;
};

enum class RandomTestFailure {
    none,
    property,
    mismatch,
    rejected_output,
    query_limit,
    invalid_query,
};

inline const char* random_test_failure_name(RandomTestFailure failure) {
    switch (failure) {
        case RandomTestFailure::none:
            return "none";
        case RandomTestFailure::property:
            return "property";
        case RandomTestFailure::mismatch:
            return "mismatch";
        case RandomTestFailure::rejected_output:
            return "rejected output";
        case RandomTestFailure::query_limit:
            return "query limit exceeded";
        case RandomTestFailure::invalid_query:
            return "invalid query";
    }
    return "unknown";
}

struct RandomTestResult {
    std::uint64_t seed = 0;
    int requested_trials = 0;
    int completed_trials = 0;
    int failed_trial = -1;
    RandomTestFailure failure = RandomTestFailure::none;
    int query_count = -1;

    bool passed() const {
        return failed_trial == -1;
    }

    explicit operator bool() const {
        return passed();
    }
};

struct IgnoreRandomTestFailure {
    template <class... Args>
    void operator()(Args&&...) const {}
};

struct InteractionExchange {
    std::string query;
    std::string response;
    bool responded = false;
};

struct InteractionTranscript {
    std::vector<InteractionExchange> exchanges;
    std::string answer;
    bool answered = false;
    std::string failure_message;
};

namespace random_testing_detail {

template <class T>
void print_value(std::ostream& output, const T& value) {
    if constexpr (requires { output << value; }) {
        output << value;
    } else if constexpr (requires {
                             typename std::tuple_size<
                                 std::remove_cvref_t<T>>::type;
                         }) {
        output << '(';
        int index = 0;
        std::apply(
            [&](const auto&... elements) {
                ((output << (index++ == 0 ? "" : ", "),
                  print_value(output, elements)),
                 ...);
            },
            value);
        output << ')';
    } else if constexpr (requires { std::begin(value); std::end(value); }) {
        output << '[';
        bool first = true;
        for (const auto& element : value) {
            if (!first) output << ", ";
            first = false;
            print_value(output, element);
        }
        output << ']';
    } else {
        output << "<unprintable>";
    }
}

template <class Function>
decltype(auto) invoke_with_trial(Function& function, Random& random, int trial) {
    if constexpr (std::invocable<Function&, Random&, int>) {
        return std::invoke(function, random, trial);
    } else {
        static_assert(std::invocable<Function&, Random&>);
        return std::invoke(function, random);
    }
}

inline RandomTestResult success_result(const RandomTestConfig& config) {
    RandomTestResult result;
    result.seed = config.seed;
    result.requested_trials = config.trials;
    result.completed_trials = config.trials;
    return result;
}

inline RandomTestResult failure_result(const RandomTestConfig& config,
                                       int failed_trial,
                                       RandomTestFailure failure,
                                       int query_count = -1) {
    RandomTestResult result;
    result.seed = config.seed;
    result.requested_trials = config.trials;
    result.completed_trials = failed_trial;
    result.failed_trial = failed_trial;
    result.failure = failure;
    result.query_count = query_count;
    return result;
}

template <class T>
std::string value_to_string(const T& value) {
    std::ostringstream output;
    print_value(output, value);
    return output.str();
}

struct InteractionAbort {
    RandomTestFailure failure;
    std::string message;
};

class StandardStreamRedirect {
   private:
    std::streambuf* _cin_buffer;
    std::streambuf* _cout_buffer;

   public:
    StandardStreamRedirect(std::streambuf* input, std::streambuf* output)
        : _cin_buffer(std::cin.rdbuf()), _cout_buffer(std::cout.rdbuf()) {
        std::cout.flush();
        std::cin.rdbuf(input);
        std::cout.rdbuf(output);
        std::cin.clear();
        std::cout.clear();
    }

    StandardStreamRedirect(const StandardStreamRedirect&) = delete;
    StandardStreamRedirect& operator=(const StandardStreamRedirect&) = delete;

    ~StandardStreamRedirect() {
        std::cout.flush();
        std::cin.rdbuf(_cin_buffer);
        std::cout.rdbuf(_cout_buffer);
        std::cin.clear();
        std::cout.clear();
    }
};

template <class Generator>
std::string generate_stream_input(Generator& generator, Random& random,
                                  int trial) {
    std::ostringstream output;
    if constexpr (std::invocable<Generator&, Random&, std::ostream&, int>) {
        std::invoke(generator, random, output, trial);
    } else {
        static_assert(std::invocable<Generator&, Random&, std::ostream&>);
        std::invoke(generator, random, output);
    }
    return output.str();
}

template <class Generator>
decltype(auto) generate_interactive_stream_input(Generator& generator,
                                                 Random& random,
                                                 std::ostream& output,
                                                 int trial) {
    if constexpr (std::invocable<Generator&, Random&, std::ostream&, int>) {
        return std::invoke(generator, random, output, trial);
    } else {
        static_assert(std::invocable<Generator&, Random&, std::ostream&>);
        return std::invoke(generator, random, output);
    }
}

template <class Solution>
std::string run_with_standard_streams(const std::string& input,
                                      Solution& solution) {
    std::istringstream input_stream(input);
    std::ostringstream output_stream;
    {
        StandardStreamRedirect redirect(input_stream.rdbuf(),
                                        output_stream.rdbuf());
        std::invoke(solution);
    }
    return output_stream.str();
}

inline std::string trim_line_breaks(std::string text) {
    while (!text.empty() &&
           (text.back() == '\n' || text.back() == '\r')) {
        text.pop_back();
    }
    return text;
}

template <class State, class QueryHandler>
class InteractiveStreamBuffer : public std::streambuf {
   private:
    State* _state;
    QueryHandler* _query_handler;
    std::stringbuf* _candidate_output;
    std::size_t _output_cursor = 0;
    int _query_limit;
    int _query_count = 0;
    std::string _input_chunk;
    InteractionTranscript _transcript;
    RandomTestFailure _failure = RandomTestFailure::none;
    std::exception_ptr _exception;

    void set_input_chunk(std::string text) {
        text.push_back('\n');
        _input_chunk = std::move(text);
        char* first = _input_chunk.data();
        setg(first, first, first + _input_chunk.size());
    }

    void fail(RandomTestFailure failure, std::string message) {
        _failure = failure;
        _transcript.failure_message = std::move(message);
        setg(nullptr, nullptr, nullptr);
    }

   protected:
    int_type underflow() override {
        if (gptr() != nullptr && gptr() < egptr()) {
            return traits_type::to_int_type(*gptr());
        }
        if (_failure != RandomTestFailure::none || _exception) {
            return traits_type::eof();
        }

        std::string all_output = _candidate_output->str();
        std::string query = all_output.substr(_output_cursor);
        _output_cursor = all_output.size();
        if (query.empty()) {
            fail(RandomTestFailure::invalid_query,
                 "solution requested input without writing a query");
            return traits_type::eof();
        }

        InteractionExchange exchange;
        exchange.query = trim_line_breaks(query);
        _transcript.exchanges.push_back(std::move(exchange));
        _query_count++;
        if (_query_limit < _query_count) {
            fail(RandomTestFailure::query_limit,
                 "attempted query " + std::to_string(_query_count) +
                     " with limit " + std::to_string(_query_limit));
            return traits_type::eof();
        }

        std::istringstream query_stream(query);
        std::ostringstream response_stream;
        try {
            std::invoke(*_query_handler, *_state, query_stream,
                        response_stream);
        } catch (const InteractionAbort& failure) {
            fail(failure.failure, failure.message);
            return traits_type::eof();
        } catch (...) {
            _exception = std::current_exception();
            return traits_type::eof();
        }

        std::string response = response_stream.str();
        InteractionExchange& recorded = _transcript.exchanges.back();
        recorded.response = trim_line_breaks(response);
        recorded.responded = true;
        set_input_chunk(std::move(response));
        return traits_type::to_int_type(*gptr());
    }

   public:
    InteractiveStreamBuffer(State& state, QueryHandler& query_handler,
                            std::stringbuf& candidate_output,
                            std::string initial_input, int query_limit)
        : _state(&state),
          _query_handler(&query_handler),
          _candidate_output(&candidate_output),
          _query_limit(query_limit) {
        set_input_chunk(std::move(initial_input));
    }

    void finish() {
        std::string all_output = _candidate_output->str();
        _transcript.answer = all_output.substr(_output_cursor);
        _transcript.answered = true;
    }

    RandomTestFailure failure() const {
        return _failure;
    }

    int query_count() const {
        return _query_count;
    }

    const InteractionTranscript& transcript() const {
        return _transcript;
    }

    const std::exception_ptr& exception() const {
        return _exception;
    }
};

template <class Solver, class Input, class Interaction>
decltype(auto) invoke_interactive_solver(Solver& solver, const Input& input,
                                         Interaction& interaction) {
    if constexpr (std::invocable<Solver&, const Input&, Interaction&>) {
        return std::invoke(solver, input, interaction);
    } else {
        static_assert(std::invocable<Solver&, Interaction&>);
        return std::invoke(solver, interaction);
    }
}

}  // namespace random_testing_detail

template <class Input, class State>
struct InteractiveTestCase {
    Input input;
    State state;
};

template <class Input, class State>
auto interactive_test_case(Input&& input, State&& state) {
    return InteractiveTestCase<std::remove_cvref_t<Input>,
                               std::remove_cvref_t<State>>{
        std::forward<Input>(input), std::forward<State>(state)};
}

// Call this from a query handler when the candidate violates the protocol.
[[noreturn]] inline void reject_query(std::string message = {}) {
    throw random_testing_detail::InteractionAbort{
        RandomTestFailure::invalid_query, std::move(message)};
}

template <class State, class QueryHandler>
class RandomInteraction {
   private:
    State* _state;
    QueryHandler* _query_handler;
    int _query_limit;
    int _query_count = 0;
    InteractionTranscript _transcript;

   public:
    RandomInteraction(State& state, QueryHandler& query_handler,
                      int query_limit)
        : _state(&state),
          _query_handler(&query_handler),
          _query_limit(query_limit) {}

    RandomInteraction(const RandomInteraction&) = delete;
    RandomInteraction& operator=(const RandomInteraction&) = delete;
    RandomInteraction(RandomInteraction&&) = delete;
    RandomInteraction& operator=(RandomInteraction&&) = delete;

    template <class Query>
    auto ask(Query&& query) {
        using Reply = std::remove_cvref_t<std::invoke_result_t<
            QueryHandler&, State&, Query>>;
        static_assert(!std::is_void_v<Reply>);

        InteractionExchange exchange;
        exchange.query = random_testing_detail::value_to_string(query);
        _transcript.exchanges.push_back(std::move(exchange));
        _query_count++;
        if (_query_limit < _query_count) {
            throw random_testing_detail::InteractionAbort{
                RandomTestFailure::query_limit,
                "attempted query " + std::to_string(_query_count) +
                    " with limit " + std::to_string(_query_limit)};
        }

        Reply reply = std::invoke(*_query_handler, *_state,
                                  std::forward<Query>(query));
        InteractionExchange& recorded = _transcript.exchanges.back();
        recorded.response = random_testing_detail::value_to_string(reply);
        recorded.responded = true;
        return reply;
    }

    int query_count() const {
        return _query_count;
    }

    const InteractionTranscript& transcript() const {
        return _transcript;
    }

    template <class Answer>
    void record_answer(const Answer& answer) {
        _transcript.answer =
            random_testing_detail::value_to_string(answer);
        _transcript.answered = true;
    }

    void record_failure(std::string message) {
        _transcript.failure_message = std::move(message);
    }
};

struct PrintRandomTestFailure {
    template <class Case, class Expected, class Actual>
    void operator()(const Case& test_case, const Expected& expected,
                    const Actual& actual, int trial,
                    std::uint64_t seed) const {
        std::cerr << "random test failed: seed=" << seed
                  << " trial=" << trial << '\n';
        std::cerr << "input: ";
        random_testing_detail::print_value(std::cerr, test_case);
        std::cerr << "\nexpected: ";
        random_testing_detail::print_value(std::cerr, expected);
        std::cerr << "\nactual: ";
        random_testing_detail::print_value(std::cerr, actual);
        std::cerr << '\n';
    }
};

struct PrintConstructiveTestFailure {
    template <class Case, class Answer>
    void operator()(const Case& test_case, const Answer& answer, int trial,
                    std::uint64_t seed) const {
        std::cerr << "constructive random test failed: seed=" << seed
                  << " trial=" << trial << '\n';
        std::cerr << "input: ";
        random_testing_detail::print_value(std::cerr, test_case);
        std::cerr << "\noutput: ";
        random_testing_detail::print_value(std::cerr, answer);
        std::cerr << '\n';
    }
};

struct PrintStreamTestFailure {
    void operator()(const std::string& input, const std::string& output,
                    int trial, std::uint64_t seed) const {
        std::cerr << "stream random test failed: seed=" << seed
                  << " trial=" << trial << "\ninput:\n"
                  << input;
        if (input.empty() || input.back() != '\n') std::cerr << '\n';
        std::cerr << "output:\n" << output;
        if (output.empty() || output.back() != '\n') std::cerr << '\n';
    }
};

struct PrintInteractiveTestFailure {
    template <class Input, class State>
    void operator()(const InteractiveTestCase<Input, State>& test_case,
                    const InteractionTranscript& transcript, int trial,
                    std::uint64_t seed,
                    RandomTestFailure failure) const {
        std::cerr << "interactive random test failed: seed=" << seed
                  << " trial=" << trial
                  << " reason=" << random_test_failure_name(failure) << '\n';
        std::cerr << "input: ";
        random_testing_detail::print_value(std::cerr, test_case.input);
        std::cerr << "\njudge state: ";
        random_testing_detail::print_value(std::cerr, test_case.state);
        std::cerr << '\n';
        for (int index = 0; index < int(transcript.exchanges.size()); index++) {
            const InteractionExchange& exchange = transcript.exchanges[index];
            std::cerr << "query " << index + 1 << ": " << exchange.query;
            if (exchange.responded) {
                std::cerr << " -> " << exchange.response;
            } else {
                std::cerr << " -> <no response>";
            }
            std::cerr << '\n';
        }
        if (transcript.answered) {
            std::cerr << "answer: " << transcript.answer << '\n';
        }
        if (!transcript.failure_message.empty()) {
            std::cerr << "message: " << transcript.failure_message << '\n';
        }
    }
};

struct PrintInteractiveStreamTestFailure {
    template <class State>
    void operator()(const std::string& input, const State& state,
                    const InteractionTranscript& transcript, int trial,
                    std::uint64_t seed,
                    RandomTestFailure failure) const {
        std::cerr << "interactive stream random test failed: seed=" << seed
                  << " trial=" << trial
                  << " reason=" << random_test_failure_name(failure)
                  << "\ninput:\n"
                  << input;
        if (input.empty() || input.back() != '\n') std::cerr << '\n';
        std::cerr << "judge state: ";
        random_testing_detail::print_value(std::cerr, state);
        std::cerr << '\n';
        for (int index = 0; index < int(transcript.exchanges.size()); index++) {
            const InteractionExchange& exchange = transcript.exchanges[index];
            std::cerr << "query " << index + 1 << ": " << exchange.query;
            if (exchange.responded) {
                std::cerr << " -> " << exchange.response;
            } else {
                std::cerr << " -> <no response>";
            }
            std::cerr << '\n';
        }
        if (transcript.answered) {
            std::cerr << "answer: " << transcript.answer;
            if (transcript.answer.empty() || transcript.answer.back() != '\n') {
                std::cerr << '\n';
            }
        }
        if (!transcript.failure_message.empty()) {
            std::cerr << "message: " << transcript.failure_message << '\n';
        }
    }
};

// Runs a property returning bool for every generated trial.
// The property may accept (Random&) or (Random&, int trial).
template <class Property>
RandomTestResult random_test(RandomTestConfig config, Property property) {
    assert(0 <= config.trials);
    if (config.trials < 0) config.trials = 0;
    Random random(config.seed);
    for (int trial = 0; trial < config.trials; trial++) {
        static_assert(std::convertible_to<
                      decltype(random_testing_detail::invoke_with_trial(
                          property, random, trial)),
                      bool>);
        bool passed = bool(
            random_testing_detail::invoke_with_trial(property, random, trial));
        if (!passed) {
            return random_testing_detail::failure_result(
                config, trial, RandomTestFailure::property);
        }
    }
    return random_testing_detail::success_result(config);
}

template <class Property>
RandomTestResult random_test(Property property) {
    return random_test(RandomTestConfig(), std::move(property));
}

// Generates a case, runs an optimized solver and an oracle on separate copies,
// and compares their results. Stops at the first mismatch.
//
// generator: (Random&) or (Random&, int trial) -> Case
// solver/oracle: (Case&) -> result
// on_failure: (case, expected, actual, trial, seed) -> void
template <class Generator, class Solver, class Oracle,
          class OnFailure = IgnoreRandomTestFailure,
          class Equal = std::equal_to<>>
RandomTestResult compare_randomly(RandomTestConfig config, Generator generator,
                                  Solver solver, Oracle oracle,
                                  OnFailure on_failure = {}, Equal equal = {}) {
    assert(0 <= config.trials);
    if (config.trials < 0) config.trials = 0;
    Random random(config.seed);

    for (int trial = 0; trial < config.trials; trial++) {
        auto test_case =
            random_testing_detail::invoke_with_trial(generator, random, trial);
        using Case = std::remove_cvref_t<decltype(test_case)>;
        static_assert(std::copy_constructible<Case>);

        Case actual_input = test_case;
        Case expected_input = test_case;
        decltype(auto) actual = std::invoke(solver, actual_input);
        decltype(auto) expected = std::invoke(oracle, expected_input);
        if (!bool(std::invoke(equal, actual, expected))) {
            std::invoke(on_failure, test_case, expected, actual, trial,
                        config.seed);
            return random_testing_detail::failure_result(
                config, trial, RandomTestFailure::mismatch);
        }
    }
    return random_testing_detail::success_result(config);
}

template <class Generator, class Solver, class Oracle>
RandomTestResult compare_randomly(Generator generator, Solver solver,
                                  Oracle oracle) {
    return compare_randomly(RandomTestConfig(), std::move(generator),
                            std::move(solver), std::move(oracle));
}

// Generates an input, runs a constructive solver, and validates its output.
// validator: (const Case&, const Answer&) -> bool
template <class Generator, class Solver, class Validator,
          class OnFailure = IgnoreRandomTestFailure>
RandomTestResult test_constructively(RandomTestConfig config,
                                     Generator generator, Solver solver,
                                     Validator validator,
                                     OnFailure on_failure = {}) {
    assert(0 <= config.trials);
    if (config.trials < 0) config.trials = 0;
    Random random(config.seed);

    for (int trial = 0; trial < config.trials; trial++) {
        auto test_case =
            random_testing_detail::invoke_with_trial(generator, random, trial);
        using Case = std::remove_cvref_t<decltype(test_case)>;
        static_assert(std::copy_constructible<Case>);
        Case solver_input = test_case;
        auto answer = std::invoke(solver, solver_input);
        if (!bool(std::invoke(validator, std::as_const(test_case),
                              std::as_const(answer)))) {
            std::invoke(on_failure, std::as_const(test_case),
                        std::as_const(answer), trial, config.seed);
            return random_testing_detail::failure_result(
                config, trial, RandomTestFailure::rejected_output);
        }
    }
    return random_testing_detail::success_result(config);
}

template <class Generator, class Solver, class Validator>
RandomTestResult test_constructively(Generator generator, Solver solver,
                                     Validator validator) {
    return test_constructively(RandomTestConfig(), std::move(generator),
                               std::move(solver), std::move(validator));
}

// Runs an ordinary solution that reads std::cin and writes std::cout.
// generator: (Random&, ostream&) or (Random&, ostream&, trial) -> void
// checker: (istream& generated_input, istream& candidate_output) -> bool
template <class Generator, class Solution, class Checker,
          class OnFailure = IgnoreRandomTestFailure>
RandomTestResult test_streams(RandomTestConfig config, Generator generator,
                              Solution solution, Checker checker,
                              OnFailure on_failure = {}) {
    assert(0 <= config.trials);
    if (config.trials < 0) config.trials = 0;
    Random random(config.seed);

    for (int trial = 0; trial < config.trials; trial++) {
        std::string input = random_testing_detail::generate_stream_input(
            generator, random, trial);
        std::string output =
            random_testing_detail::run_with_standard_streams(input, solution);
        std::istringstream input_stream(input);
        std::istringstream output_stream(output);
        if (!bool(std::invoke(checker, input_stream, output_stream))) {
            std::invoke(on_failure, std::as_const(input),
                        std::as_const(output), trial, config.seed);
            return random_testing_detail::failure_result(
                config, trial, RandomTestFailure::rejected_output);
        }
    }
    return random_testing_detail::success_result(config);
}

template <class Generator, class Solution, class Checker>
RandomTestResult test_streams(Generator generator, Solution solution,
                              Checker checker) {
    return test_streams(RandomTestConfig(), std::move(generator),
                        std::move(solution), std::move(checker));
}

// generator: (Random&) or (Random&, trial) -> InteractiveTestCase<Input, State>
// solver: (const Input&, interaction) or (interaction) -> Answer
// query_handler: (State&, Query) -> Reply
// validator: (const Input&, const State&, const Answer&) -> bool
template <class Generator, class Solver, class QueryHandler, class Validator,
          class OnFailure = IgnoreRandomTestFailure>
RandomTestResult test_interactively(RandomTestConfig config, int query_limit,
                                    Generator generator, Solver solver,
                                    QueryHandler query_handler,
                                    Validator validator,
                                    OnFailure on_failure = {}) {
    assert(0 <= config.trials);
    assert(0 <= query_limit);
    if (config.trials < 0) config.trials = 0;
    if (query_limit < 0) query_limit = 0;
    Random random(config.seed);

    for (int trial = 0; trial < config.trials; trial++) {
        auto test_case =
            random_testing_detail::invoke_with_trial(generator, random, trial);
        using State = std::remove_cvref_t<decltype(test_case.state)>;
        RandomInteraction<State, QueryHandler> interaction(
            test_case.state, query_handler, query_limit);

        try {
            auto answer = random_testing_detail::invoke_interactive_solver(
                solver, std::as_const(test_case.input), interaction);
            interaction.record_answer(answer);
            if (!bool(std::invoke(validator, std::as_const(test_case.input),
                                  std::as_const(test_case.state),
                                  std::as_const(answer)))) {
                RandomTestResult result =
                    random_testing_detail::failure_result(
                        config, trial, RandomTestFailure::rejected_output,
                        interaction.query_count());
                std::invoke(on_failure, std::as_const(test_case),
                            interaction.transcript(), trial, config.seed,
                            result.failure);
                return result;
            }
        } catch (const random_testing_detail::InteractionAbort& failure) {
            interaction.record_failure(failure.message);
            RandomTestResult result = random_testing_detail::failure_result(
                config, trial, failure.failure, interaction.query_count());
            std::invoke(on_failure, std::as_const(test_case),
                        interaction.transcript(), trial, config.seed,
                        result.failure);
            return result;
        }
    }
    return random_testing_detail::success_result(config);
}

template <class Generator, class Solver, class QueryHandler, class Validator>
RandomTestResult test_interactively(int query_limit, Generator generator,
                                    Solver solver, QueryHandler query_handler,
                                    Validator validator) {
    return test_interactively(RandomTestConfig(), query_limit,
                              std::move(generator), std::move(solver),
                              std::move(query_handler), std::move(validator));
}

// Runs an ordinary interactive solution using std::cin and std::cout.
// generator: (Random&, ostream&) or (Random&, ostream&, trial) -> JudgeState
// query_handler: (JudgeState&, istream& query, ostream& response) -> void
// checker: (istream& public_input, const JudgeState&,
//           istream& final_output) -> bool
template <class Generator, class Solution, class QueryHandler, class Checker,
          class OnFailure = IgnoreRandomTestFailure>
RandomTestResult test_interactive_streams(
    RandomTestConfig config, int query_limit, Generator generator,
    Solution solution, QueryHandler query_handler, Checker checker,
    OnFailure on_failure = {}) {
    assert(0 <= config.trials);
    assert(0 <= query_limit);
    if (config.trials < 0) config.trials = 0;
    if (query_limit < 0) query_limit = 0;
    Random random(config.seed);

    for (int trial = 0; trial < config.trials; trial++) {
        std::ostringstream generated_input;
        auto state =
            random_testing_detail::generate_interactive_stream_input(
                generator, random, generated_input, trial);
        std::string input = generated_input.str();
        std::stringbuf candidate_output(std::ios::out);
        using State = std::remove_cvref_t<decltype(state)>;
        random_testing_detail::InteractiveStreamBuffer<State, QueryHandler>
            input_buffer(state, query_handler, candidate_output, input,
                         query_limit);
        {
            random_testing_detail::StandardStreamRedirect redirect(
                &input_buffer, &candidate_output);
            std::invoke(solution);
        }
        input_buffer.finish();
        if (input_buffer.exception()) {
            std::rethrow_exception(input_buffer.exception());
        }

        RandomTestFailure failure = input_buffer.failure();
        if (failure != RandomTestFailure::none) {
            RandomTestResult result = random_testing_detail::failure_result(
                config, trial, failure, input_buffer.query_count());
            std::invoke(on_failure, std::as_const(input),
                        std::as_const(state), input_buffer.transcript(), trial,
                        config.seed, failure);
            return result;
        }

        std::istringstream input_stream(input);
        std::istringstream output_stream(input_buffer.transcript().answer);
        if (!bool(std::invoke(checker, input_stream, std::as_const(state),
                              output_stream))) {
            RandomTestResult result = random_testing_detail::failure_result(
                config, trial, RandomTestFailure::rejected_output,
                input_buffer.query_count());
            std::invoke(on_failure, std::as_const(input),
                        std::as_const(state), input_buffer.transcript(), trial,
                        config.seed, result.failure);
            return result;
        }
    }
    return random_testing_detail::success_result(config);
}

template <class Generator, class Solution, class QueryHandler, class Checker>
RandomTestResult test_interactive_streams(
    int query_limit, Generator generator, Solution solution,
    QueryHandler query_handler, Checker checker) {
    return test_interactive_streams(
        RandomTestConfig(), query_limit, std::move(generator),
        std::move(solution), std::move(query_handler), std::move(checker));
}

// Short contest interface. Prints failure metadata and terminates on failure.
template <class Property>
RandomTestResult stress_test(Property property, int trials = 1000,
                             std::uint64_t seed = default_random_test_seed) {
    RandomTestConfig config;
    config.trials = trials;
    config.seed = seed;
    RandomTestResult result = random_test(config, std::move(property));
    if (!result) {
        std::cerr << "random test failed: seed=" << result.seed
                  << " trial=" << result.failed_trial << '\n';
        std::abort();
    }
    return result;
}

// Short optimized-versus-brute-force interface.
template <class Generator, class Solver, class Oracle>
requires(!std::integral<std::remove_cvref_t<Solver>> &&
         !std::integral<std::remove_cvref_t<Oracle>>)
RandomTestResult stress_test(Generator generator, Solver solver, Oracle oracle,
                             int trials = 1000,
                             std::uint64_t seed = default_random_test_seed) {
    RandomTestConfig config;
    config.trials = trials;
    config.seed = seed;
    RandomTestResult result = compare_randomly(
        config, std::move(generator), std::move(solver), std::move(oracle),
        PrintRandomTestFailure());
    if (!result) std::abort();
    return result;
}

template <class Generator, class Solver, class Validator>
RandomTestResult constructive_stress_test(
    Generator generator, Solver solver, Validator validator,
    int trials = 1000, std::uint64_t seed = default_random_test_seed) {
    RandomTestConfig config;
    config.trials = trials;
    config.seed = seed;
    RandomTestResult result = test_constructively(
        config, std::move(generator), std::move(solver),
        std::move(validator), PrintConstructiveTestFailure());
    if (!result) std::abort();
    return result;
}

template <class Generator, class Solution, class Checker>
RandomTestResult stream_stress_test(
    Generator generator, Solution solution, Checker checker,
    int trials = 1000, std::uint64_t seed = default_random_test_seed) {
    RandomTestConfig config;
    config.trials = trials;
    config.seed = seed;
    RandomTestResult result = test_streams(
        config, std::move(generator), std::move(solution),
        std::move(checker), PrintStreamTestFailure());
    if (!result) std::abort();
    return result;
}

template <class Generator, class Solver, class QueryHandler, class Validator>
RandomTestResult interactive_stress_test(
    int query_limit, Generator generator, Solver solver,
    QueryHandler query_handler, Validator validator, int trials = 1000,
    std::uint64_t seed = default_random_test_seed) {
    RandomTestConfig config;
    config.trials = trials;
    config.seed = seed;
    RandomTestResult result = test_interactively(
        config, query_limit, std::move(generator), std::move(solver),
        std::move(query_handler), std::move(validator),
        PrintInteractiveTestFailure());
    if (!result) std::abort();
    return result;
}

template <class Generator, class Solution, class QueryHandler, class Checker>
RandomTestResult interactive_stream_stress_test(
    int query_limit, Generator generator, Solution solution,
    QueryHandler query_handler, Checker checker, int trials = 1000,
    std::uint64_t seed = default_random_test_seed) {
    RandomTestConfig config;
    config.trials = trials;
    config.seed = seed;
    RandomTestResult result = test_interactive_streams(
        config, query_limit, std::move(generator), std::move(solution),
        std::move(query_handler), std::move(checker),
        PrintInteractiveStreamTestFailure());
    if (!result) std::abort();
    return result;
}

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_RANDOM_TESTING_HPP
