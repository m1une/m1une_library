#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_B"
#define ERROR 0.000001

#include "../../geometry/circle.hpp"

#include <cassert>
#include "../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;
    using namespace m1une::geometry;

    Point<long long> first;
    Point<long long> second;
    Point<long long> third;
    fast_input >> first.x >> first.y;
    fast_input >> second.x >> second.y;
    fast_input >> third.x >> third.y;
    auto result = incircle(first, second, third);
    assert(result.has_value());
    fast_output.set_fixed(15);
    fast_output << result->center.x << " " << result->center.y << " "
                << result->radius << '\n';
}
