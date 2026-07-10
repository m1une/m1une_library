#define IGNORE

#if __has_include(<flint/partitions.h>)

#include "../../math/modint.hpp"
#include "../../math/partition_function.hpp"
#include "../../math/partition_number_hrr.hpp"

#include <cassert>
#include <string>
#include <vector>

int main() {
    using Mint = m1une::math::ModInt<1'000'000'007>;

    assert(m1une::math::partition_number_hrr(0).to_string() == "1");
    assert(m1une::math::partition_number_hrr(5).to_string() == "7");
    assert(
        m1une::math::partition_number_hrr(100).to_string()
        == "190569292"
    );
    assert(
        m1une::math::partition_number_hrr(1000).to_string()
        == "24061467864032622473692149727991"
    );

    std::vector<Mint> modulo = m1une::math::partition_function<Mint>(5000);
    for (int n = 0; n <= 5000; n++) {
        m1une::utilities::BigInt value =
            m1une::math::partition_number_hrr(n);
        m1une::utilities::BigInt remainder =
            value % m1une::utilities::BigInt(Mint::mod());
        assert(remainder.to_string() == std::to_string(modulo[n].val()));
    }

    m1une::utilities::BigInt large =
        m1une::math::partition_number_hrr(1'000'000);
    assert(large.to_string().size() == 1108);
}

#else

int main() {}

#endif
