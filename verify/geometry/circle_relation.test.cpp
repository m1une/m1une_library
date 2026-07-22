#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A"

#include "../../geometry/circle.hpp"

#include <cassert>
#include "../../utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput fast_input;
    m1une::utilities::FastOutput fast_output;
    using namespace m1une::geometry;

    Circle<long long> first;
    Circle<long long> second;
    fast_input >> first.center.x >> first.center.y >> first.radius;
    fast_input >> second.center.x >> second.center.y >> second.radius;

    int answer = -1;
    switch (circle_relation(first, second)) {
        case CircleRelation::Separate:
            answer = 4;
            break;
        case CircleRelation::ExternallyTangent:
            answer = 3;
            break;
        case CircleRelation::Intersecting:
            answer = 2;
            break;
        case CircleRelation::InternallyTangent:
            answer = 1;
            break;
        case CircleRelation::Contained:
            answer = 0;
            break;
        case CircleRelation::Coincident:
            assert(false);
    }
    fast_output << answer << '\n';
}
