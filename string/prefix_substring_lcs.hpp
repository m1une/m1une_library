#ifndef M1UNE_STRING_PREFIX_SUBSTRING_LCS_HPP
#define M1UNE_STRING_PREFIX_SUBSTRING_LCS_HPP 1

#include <algorithm>
#include <cassert>
#include <type_traits>
#include <utility>
#include <vector>

namespace m1une {
namespace string {

// Answers LCS-length queries between a prefix of the first sequence and a
// substring of the second sequence. Queries are evaluated as one offline batch.
template <class FirstSequence, class SecondSequence>
class PrefixSubstringLcs {
   private:
    struct Query {
        int first_prefix;
        int second_left;
        int second_right;
    };

    FirstSequence _first;
    SecondSequence _second;
    std::vector<Query> _queries;

   public:
    PrefixSubstringLcs(FirstSequence first, SecondSequence second)
        : _first(std::move(first)), _second(std::move(second)) {}

    int first_size() const {
        return int(_first.size());
    }

    int second_size() const {
        return int(_second.size());
    }

    int query_count() const {
        return int(_queries.size());
    }

    bool empty() const {
        return _queries.empty();
    }

    void reserve(int query_capacity) {
        assert(0 <= query_capacity);
        _queries.reserve(query_capacity);
    }

    void clear() {
        _queries.clear();
    }

    // Adds LCS(first[0..first_prefix), second[second_left..second_right)) and
    // returns its insertion-order ID.
    int add_query(int first_prefix, int second_left, int second_right) {
        assert(0 <= first_prefix && first_prefix <= first_size());
        assert(0 <= second_left && second_left <= second_right);
        assert(second_right <= second_size());
        const int id = query_count();
        _queries.push_back(Query{first_prefix, second_left, second_right});
        return id;
    }

    std::vector<int> calculate() const {
        const int first_length = first_size();
        const int second_length = second_size();
        const int count = query_count();
        std::vector<int> answers(count, 0);
        if (count == 0 || first_length == 0 || second_length == 0) {
            return answers;
        }

        std::vector<std::vector<int>> queries_by_prefix(first_length + 1);
        for (int id = 0; id < count; id++) {
            const Query& query = _queries[id];
            if (query.first_prefix > 0 &&
                query.second_left < query.second_right) {
                queries_by_prefix[query.first_prefix].push_back(id);
            }
        }

        // seaweed[j] is the bottom endpoint of the seaweed entering at j for
        // the current prefix of the first sequence. -1 denotes the left edge.
        std::vector<int> seaweed(second_length);
        for (int j = 0; j < second_length; j++) seaweed[j] = j;

        std::vector<int> heads(second_length + 1, -1);
        std::vector<int> next(count, -1);
        std::vector<int> fenwick(second_length + 1, 0);

        for (int i = 0; i < first_length; i++) {
            int displaced = -1;
            for (int j = 0; j < second_length; j++) {
                if (_first[i] == _second[j] || seaweed[j] < displaced) {
                    std::swap(seaweed[j], displaced);
                }
            }

            const std::vector<int>& prefix_queries = queries_by_prefix[i + 1];
            if (prefix_queries.empty()) continue;

            std::fill(heads.begin(), heads.end(), -1);
            for (int id : prefix_queries) {
                const int right = _queries[id].second_right;
                next[id] = heads[right];
                heads[right] = id;
            }
            std::fill(fenwick.begin(), fenwick.end(), 0);

            int inserted = 0;
            for (int right = 1; right <= second_length; right++) {
                const int endpoint = seaweed[right - 1];
                if (endpoint >= 0) {
                    inserted++;
                    for (int position = endpoint + 1;
                         position <= second_length;
                         position += position & -position) {
                        fenwick[position]++;
                    }
                }

                for (int id = heads[right]; id != -1; id = next[id]) {
                    const int left = _queries[id].second_left;
                    int below_left = 0;
                    for (int position = left; position > 0;
                         position -= position & -position) {
                        below_left += fenwick[position];
                    }
                    const int crossing = inserted - below_left;
                    answers[id] = (right - left) - crossing;
                }
            }
        }
        return answers;
    }
};

template <class FirstSequence, class SecondSequence>
PrefixSubstringLcs(FirstSequence&&, SecondSequence&&)
    -> PrefixSubstringLcs<
        std::decay_t<FirstSequence>,
        std::decay_t<SecondSequence>
    >;

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_PREFIX_SUBSTRING_LCS_HPP
