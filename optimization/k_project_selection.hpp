#ifndef M1UNE_OPTIMIZATION_K_PROJECT_SELECTION_HPP
#define M1UNE_OPTIMIZATION_K_PROJECT_SELECTION_HPP 1

#include <cassert>
#include <cstddef>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>

#include "project_selection.hpp"

namespace m1une {
namespace opt {

template <class T>
struct KProjectSelectionResult {
    bool feasible;
    T max_gain;
    std::vector<int> values;

    bool is_feasible() const {
        return feasible;
    }
};

template <class T>
class KProjectSelection {
    static_assert(std::is_integral_v<T> && std::is_signed_v<T>);
    static_assert(sizeof(T) <= sizeof(long long));

    using Wide = __int128_t;

    std::vector<int> _value_counts;
    std::vector<int> _first_threshold;
    ProjectSelection<T> _binary;
    T _constant = T();

    static int threshold_count(const std::vector<int>& value_counts) {
        assert(value_counts.size() <=
               std::size_t(std::numeric_limits<int>::max()));
        long long count = 0;
        for (int value_count : value_counts) {
            assert(value_count >= 1);
            count += value_count - 1;
            assert(count <= std::numeric_limits<int>::max());
        }
        return int(count);
    }

    static std::vector<int> repeated_value_counts(
        int project_count,
        int value_count
    ) {
        assert(project_count >= 0);
        assert(value_count >= 1);
        return std::vector<int>(project_count, value_count);
    }

    void assert_project(int project) const {
        (void)project;
        assert(0 <= project && project < size());
    }

    int threshold(int project, int value) const {
        assert_project(project);
        (void)value;
        assert(1 <= value && value < _value_counts[project]);
        return _first_threshold[project] + value - 1;
    }

    static T narrow(Wide value) {
        assert(Wide(std::numeric_limits<T>::lowest()) <= value);
        assert(value <= Wide(std::numeric_limits<T>::max()));
        return T(value);
    }

    void add_constant(T gain) {
        _constant = narrow(Wide(_constant) + gain);
    }

    void add_threshold_gain(int project, int value, Wide gain) {
        if (gain == 0) return;
        _binary.add_gain(threshold(project, value), narrow(gain));
    }

   public:
    KProjectSelection() : KProjectSelection(std::vector<int>()) {}

    explicit KProjectSelection(std::vector<int> value_counts)
        : _value_counts(std::move(value_counts)),
          _first_threshold(_value_counts.size()),
          _binary(threshold_count(_value_counts)) {
        int first = 0;
        for (int project = 0; project < size(); project++) {
            _first_threshold[project] = first;
            first += _value_counts[project] - 1;
        }

        for (int project = 0; project < size(); project++) {
            for (int value = 2; value < _value_counts[project]; value++) {
                _binary.add_hard_implication(
                    threshold(project, value),
                    threshold(project, value - 1)
                );
            }
        }
    }

    KProjectSelection(int project_count, int value_count)
        : KProjectSelection(repeated_value_counts(project_count, value_count)) {}

    int size() const {
        return int(_value_counts.size());
    }

    int value_count(int project) const {
        assert_project(project);
        return _value_counts[project];
    }

    void add_gain(int project, const std::vector<T>& gains) {
        assert_project(project);
        assert(int(gains.size()) == _value_counts[project]);
        add_constant(gains[0]);
        for (int value = 1; value < _value_counts[project]; value++) {
            add_threshold_gain(
                project,
                value,
                Wide(gains[value]) - gains[value - 1]
            );
        }
    }

    void add_gain(
        int project_a,
        int project_b,
        const std::vector<std::vector<T>>& gains
    ) {
        assert_project(project_a);
        assert_project(project_b);
        assert(project_a != project_b);
        const int count_a = _value_counts[project_a];
        const int count_b = _value_counts[project_b];
        assert(int(gains.size()) == count_a);
        for (const auto& row : gains) assert(int(row.size()) == count_b);

        add_constant(gains[0][0]);
        for (int value_a = 1; value_a < count_a; value_a++) {
            add_threshold_gain(
                project_a,
                value_a,
                Wide(gains[value_a][0]) - gains[value_a - 1][0]
            );
        }
        for (int value_b = 1; value_b < count_b; value_b++) {
            add_threshold_gain(
                project_b,
                value_b,
                Wide(gains[0][value_b]) - gains[0][value_b - 1]
            );
        }

        for (int value_a = 1; value_a < count_a; value_a++) {
            for (int value_b = 1; value_b < count_b; value_b++) {
                Wide mixed =
                    Wide(gains[value_a][value_b])
                    - gains[value_a - 1][value_b]
                    - gains[value_a][value_b - 1]
                    + gains[value_a - 1][value_b - 1];
                assert(mixed >= 0);
                T gain = narrow(mixed);
                if (gain == T()) continue;
                int threshold_a = threshold(project_a, value_a);
                int threshold_b = threshold(project_b, value_b);
                _binary.add_gain(threshold_a, gain);
                _binary.add_penalty(threshold_a, threshold_b, gain);
            }
        }
    }

    void force_value(int project, int value) {
        assert_project(project);
        assert(0 <= value && value < _value_counts[project]);
        force_value_at_least(project, value);
        force_value_at_most(project, value);
    }

    void force_value_at_least(int project, int lower_bound) {
        assert_project(project);
        assert(0 <= lower_bound && lower_bound < _value_counts[project]);
        if (lower_bound > 0) {
            _binary.force_selected(threshold(project, lower_bound));
        }
    }

    void force_value_at_most(int project, int upper_bound) {
        assert_project(project);
        assert(0 <= upper_bound && upper_bound < _value_counts[project]);
        if (upper_bound + 1 < _value_counts[project]) {
            _binary.force_unselected(threshold(project, upper_bound + 1));
        }
    }

    KProjectSelectionResult<T> solve() const {
        auto binary_result = _binary.solve();
        KProjectSelectionResult<T> result;
        result.feasible = binary_result.feasible;
        result.max_gain = T();
        result.values.assign(size(), 0);
        if (!result.feasible) return result;

        result.max_gain = narrow(Wide(_constant) + binary_result.max_gain);
        for (int project = 0; project < size(); project++) {
            for (int value = 1; value < _value_counts[project]; value++) {
                if (!binary_result.selected[threshold(project, value)]) break;
                result.values[project] = value;
            }
        }
        return result;
    }
};

}  // namespace opt
}  // namespace m1une

#endif  // M1UNE_OPTIMIZATION_K_PROJECT_SELECTION_HPP
