#include "template.hpp"
#include "utilities/random.hpp"

int main(int argc, char** argv) {
    assert(argc == 2);
    m1une::utilities::Random random(std::stoull(argv[1]));
    int n = int(random.uniform(0, 30));
    print(n);
    print(random.sequence(n, -5, 5));
}
