#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B"

#include "../../geometry/line.hpp"

#include "../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;

    using namespace m1une::geometry;
    int q;
    fast_input >> q;
    while (q--) {
        Segment<long long> first;
        Segment<long long> second;
        fast_input >> first.a.x >> first.a.y >> first.b.x >> first.b.y;
        fast_input >> second.a.x >> second.a.y >> second.b.x >> second.b.y;
        fast_output << intersects(first, second) << '\n';
    }
}
