---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/matrix/hafnian.hpp
    title: Hafnian
  - icon: ':heavy_check_mark:'
    path: math/matrix/matrix.hpp
    title: Dense Matrix
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/hafnian_of_matrix
    links:
    - https://judge.yosupo.jp/problem/hafnian_of_matrix
  bundledCode: "#line 1 \"verify/math/matrix/hafnian.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/hafnian_of_matrix\"\n\n#line 1 \"math/matrix/hafnian.hpp\"\
    \n\n\n\n#include <cassert>\n#include <utility>\n#include <vector>\n\n#line 1 \"\
    math/matrix/matrix.hpp\"\n\n\n\n#line 5 \"math/matrix/matrix.hpp\"\n#include <cstddef>\n\
    #include <cstdint>\n#line 9 \"math/matrix/matrix.hpp\"\n\nnamespace m1une {\n\
    namespace matrix {\n\ntemplate <class T>\nclass Matrix {\n   private:\n    int\
    \ _rows;\n    int _cols;\n    std::vector<T> _data;\n\n    static std::size_t\
    \ storage_size(int rows, int cols) {\n        assert(rows >= 0);\n        assert(cols\
    \ >= 0);\n        return std::size_t(rows) * std::size_t(cols);\n    }\n\n   public:\n\
    \    using value_type = T;\n\n    Matrix() : _rows(0), _cols(0) {}\n\n    Matrix(int\
    \ rows, int cols, const T& value = T())\n        : _rows(rows), _cols(cols), _data(storage_size(rows,\
    \ cols), value) {}\n\n    Matrix(int rows, int cols, std::vector<T> values)\n\
    \        : _rows(rows), _cols(cols), _data(std::move(values)) {\n        assert(rows\
    \ >= 0);\n        assert(cols >= 0);\n        assert(_data.size() == std::size_t(rows)\
    \ * std::size_t(cols));\n    }\n\n    explicit Matrix(const std::vector<std::vector<T>>&\
    \ values)\n        : _rows(int(values.size())), _cols(values.empty() ? 0 : int(values[0].size())),\n\
    \          _data(storage_size(_rows, _cols)) {\n        for (int row = 0; row\
    \ < _rows; row++) {\n            assert(int(values[std::size_t(row)].size()) ==\
    \ _cols);\n            for (int col = 0; col < _cols; col++) {\n             \
    \   (*this)[row][col] = values[std::size_t(row)][std::size_t(col)];\n        \
    \    }\n        }\n    }\n\n    int rows() const {\n        return _rows;\n  \
    \  }\n\n    int cols() const {\n        return _cols;\n    }\n\n    bool empty()\
    \ const {\n        return _rows == 0 || _cols == 0;\n    }\n\n    std::vector<T>&\
    \ data() {\n        return _data;\n    }\n\n    const std::vector<T>& data() const\
    \ {\n        return _data;\n    }\n\n    T* operator[](int row) {\n        assert(0\
    \ <= row && row < _rows);\n        return _data.data() + std::size_t(row) * std::size_t(_cols);\n\
    \    }\n\n    const T* operator[](int row) const {\n        assert(0 <= row &&\
    \ row < _rows);\n        return _data.data() + std::size_t(row) * std::size_t(_cols);\n\
    \    }\n\n    T& operator()(int row, int col) {\n        assert(0 <= col && col\
    \ < _cols);\n        return (*this)[row][col];\n    }\n\n    const T& operator()(int\
    \ row, int col) const {\n        assert(0 <= col && col < _cols);\n        return\
    \ (*this)[row][col];\n    }\n\n    static Matrix identity(int size) {\n      \
    \  assert(size >= 0);\n        Matrix result(size, size);\n        for (int i\
    \ = 0; i < size; i++) result[i][i] = T(1);\n        return result;\n    }\n\n\
    \    Matrix transposed() const {\n        Matrix result(_cols, _rows);\n     \
    \   for (int row = 0; row < _rows; row++) {\n            for (int col = 0; col\
    \ < _cols; col++) {\n                result[col][row] = (*this)[row][col];\n \
    \           }\n        }\n        return result;\n    }\n\n    void swap_rows(int\
    \ first, int second) {\n        assert(0 <= first && first < _rows);\n       \
    \ assert(0 <= second && second < _rows);\n        if (first == second) return;\n\
    \        for (int col = 0; col < _cols; col++) {\n            std::swap((*this)[first][col],\
    \ (*this)[second][col]);\n        }\n    }\n\n    Matrix& operator+=(const Matrix&\
    \ rhs) {\n        assert(_rows == rhs._rows && _cols == rhs._cols);\n        for\
    \ (std::size_t i = 0; i < _data.size(); i++) _data[i] += rhs._data[i];\n     \
    \   return *this;\n    }\n\n    Matrix& operator-=(const Matrix& rhs) {\n    \
    \    assert(_rows == rhs._rows && _cols == rhs._cols);\n        for (std::size_t\
    \ i = 0; i < _data.size(); i++) _data[i] -= rhs._data[i];\n        return *this;\n\
    \    }\n\n    Matrix& operator*=(const T& scalar) {\n        for (T& value : _data)\
    \ value *= scalar;\n        return *this;\n    }\n\n    Matrix& operator/=(const\
    \ T& scalar) {\n        for (T& value : _data) value /= scalar;\n        return\
    \ *this;\n    }\n\n    Matrix& operator*=(const Matrix& rhs) {\n        return\
    \ *this = *this * rhs;\n    }\n\n    Matrix operator+() const {\n        return\
    \ *this;\n    }\n\n    Matrix operator-() const {\n        Matrix result = *this;\n\
    \        for (T& value : result._data) value = T() - value;\n        return result;\n\
    \    }\n\n    friend Matrix operator+(Matrix lhs, const Matrix& rhs) {\n     \
    \   return lhs += rhs;\n    }\n\n    friend Matrix operator-(Matrix lhs, const\
    \ Matrix& rhs) {\n        return lhs -= rhs;\n    }\n\n    friend Matrix operator*(Matrix\
    \ lhs, const T& rhs) {\n        return lhs *= rhs;\n    }\n\n    friend Matrix\
    \ operator*(const T& lhs, Matrix rhs) {\n        return rhs *= lhs;\n    }\n\n\
    \    friend Matrix operator/(Matrix lhs, const T& rhs) {\n        return lhs /=\
    \ rhs;\n    }\n\n    friend Matrix operator*(const Matrix& lhs, const Matrix&\
    \ rhs) {\n        assert(lhs._cols == rhs._rows);\n        Matrix result(lhs._rows,\
    \ rhs._cols);\n        for (int row = 0; row < lhs._rows; row++) {\n         \
    \   T* output = result[row];\n            for (int middle = 0; middle < lhs._cols;\
    \ middle++) {\n                const T coefficient = lhs[row][middle];\n     \
    \           if (coefficient == T()) continue;\n                const T* input\
    \ = rhs[middle];\n                for (int col = 0; col < rhs._cols; col++) {\n\
    \                    output[col] += coefficient * input[col];\n              \
    \  }\n            }\n        }\n        return result;\n    }\n\n    friend std::vector<T>\
    \ operator*(const Matrix& lhs, const std::vector<T>& rhs) {\n        assert(lhs._cols\
    \ == int(rhs.size()));\n        std::vector<T> result(std::size_t(lhs._rows));\n\
    \        for (int row = 0; row < lhs._rows; row++) {\n            T value = T();\n\
    \            for (int col = 0; col < lhs._cols; col++) {\n                value\
    \ += lhs[row][col] * rhs[std::size_t(col)];\n            }\n            result[std::size_t(row)]\
    \ = value;\n        }\n        return result;\n    }\n\n    friend std::vector<T>\
    \ operator*(const std::vector<T>& lhs, const Matrix& rhs) {\n        assert(int(lhs.size())\
    \ == rhs._rows);\n        std::vector<T> result(std::size_t(rhs._cols));\n   \
    \     for (int row = 0; row < rhs._rows; row++) {\n            if (lhs[std::size_t(row)]\
    \ == T()) continue;\n            for (int col = 0; col < rhs._cols; col++) {\n\
    \                result[std::size_t(col)] += lhs[std::size_t(row)] * rhs[row][col];\n\
    \            }\n        }\n        return result;\n    }\n\n    bool operator==(const\
    \ Matrix& rhs) const {\n        return _rows == rhs._rows && _cols == rhs._cols\
    \ && _data == rhs._data;\n    }\n\n    bool operator!=(const Matrix& rhs) const\
    \ {\n        return !(*this == rhs);\n    }\n\n    Matrix pow(std::uint64_t exponent)\
    \ const {\n        assert(_rows == _cols);\n        Matrix result = identity(_rows);\n\
    \        Matrix base = *this;\n        while (exponent > 0) {\n            if\
    \ (exponent & 1) result *= base;\n            exponent >>= 1;\n            if\
    \ (exponent > 0) base *= base;\n        }\n        return result;\n    }\n};\n\
    \n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 9 \"math/matrix/hafnian.hpp\"\
    \n\nnamespace m1une {\nnamespace matrix {\nnamespace internal {\n\ntemplate <class\
    \ T>\nclass HafnianSolver {\n    using Polynomial = std::vector<T>;\n    using\
    \ PolynomialMatrix = std::vector<std::vector<Polynomial>>;\n\n    int _degree;\n\
    \n    void add_shifted_product(Polynomial& result, const Polynomial& first,\n\
    \                             const Polynomial& second) const {\n        for (int\
    \ first_degree = 0; first_degree < _degree; first_degree++) {\n            for\
    \ (int second_degree = 0;\n                 first_degree + second_degree + 1 <\
    \ _degree;\n                 second_degree++) {\n                result[first_degree\
    \ + second_degree + 1] +=\n                    first[first_degree] * second[second_degree];\n\
    \            }\n        }\n    }\n\n    Polynomial solve(PolynomialMatrix matrix)\
    \ const {\n        if (matrix.empty()) {\n            Polynomial result(_degree);\n\
    \            result[0] = T(1);\n            return result;\n        }\n\n    \
    \    std::vector<Polynomial> first = std::move(matrix.back());\n        matrix.pop_back();\n\
    \        std::vector<Polynomial> second = std::move(matrix.back());\n        matrix.pop_back();\n\
    \        const int remaining = int(matrix.size());\n        Polynomial first_to_pair\
    \ = std::move(first[remaining]);\n\n        Polynomial result = solve(matrix);\n\
    \        for (T& coefficient : result) coefficient = T() - coefficient;\n\n  \
    \      for (int row = 0; row < remaining; row++) {\n            for (int col =\
    \ 0; col < row; col++) {\n                add_shifted_product(matrix[row][col],\
    \ first[row], second[col]);\n                add_shifted_product(matrix[row][col],\
    \ second[row], first[col]);\n            }\n        }\n\n        Polynomial with_connections\
    \ = solve(std::move(matrix));\n        add_shifted_product(result, first_to_pair,\
    \ with_connections);\n        for (int degree = 0; degree < _degree; degree++)\
    \ {\n            result[degree] += with_connections[degree];\n        }\n    \
    \    return result;\n    }\n\n   public:\n    explicit HafnianSolver(int size)\
    \ : _degree(size / 2 + 1) {}\n\n    T operator()(const Matrix<T>& matrix) const\
    \ {\n        const int size = matrix.rows();\n        PolynomialMatrix polynomial_matrix(size);\n\
    \        for (int row = 0; row < size; row++) {\n            polynomial_matrix[row].assign(row,\
    \ Polynomial(_degree));\n            for (int col = 0; col < row; col++) {\n \
    \               polynomial_matrix[row][col][0] = matrix[row][col];\n         \
    \   }\n        }\n        return solve(std::move(polynomial_matrix)).back();\n\
    \    }\n};\n\n}  // namespace internal\n\n// Returns the hafnian of an even-dimensional\
    \ symmetric zero-diagonal matrix.\ntemplate <class T>\nT hafnian(const Matrix<T>&\
    \ matrix) {\n    assert(matrix.rows() == matrix.cols());\n    const int size =\
    \ matrix.rows();\n    assert(size % 2 == 0);\n\n#ifndef NDEBUG\n    for (int row\
    \ = 0; row < size; row++) {\n        assert(matrix[row][row] == T());\n      \
    \  for (int col = row + 1; col < size; col++) {\n            assert(matrix[row][col]\
    \ == matrix[col][row]);\n        }\n    }\n#endif\n\n    return internal::HafnianSolver<T>(size)(matrix);\n\
    }\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 1 \"math/modint.hpp\"\
    \n\n\n\n#line 6 \"math/modint.hpp\"\n#include <iostream>\n#include <type_traits>\n\
    #line 9 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
    \ <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus, \"Modulus\
    \ must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n    static\
    \ constexpr uint32_t mod() {\n        return Modulus;\n    }\n\n    static constexpr\
    \ ModInt raw(uint32_t v) noexcept {\n        ModInt x;\n        x._v = v;\n  \
    \      return x;\n    }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    template\
    \ <class Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n  \
    \  constexpr ModInt(Integer v) noexcept {\n        if constexpr (std::is_signed_v<Integer>)\
    \ {\n            int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(Modulus);\n\
    \            if (x < 0) x += Modulus;\n            _v = static_cast<uint32_t>(x);\n\
    \        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1), x = *this;\n        while (n > 0) {\n            if (n & 1) res\
    \ *= x;\n            x *= x;\n            n >>= 1;\n        }\n        return\
    \ res;\n    }\n\n    constexpr ModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n            int64_t\
    \ t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n        \
    \    u -= t * v;\n            std::swap(u, v);\n        }\n        if (u < 0)\
    \ u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {\n        return\
    \ os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream& is,\
    \ ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\ntemplate <int Id = 0>\nstruct\
    \ DynamicModInt {\n   private:\n    uint32_t _v;\n    inline static uint32_t _mod\
    \ = 1;\n\n   public:\n    static uint32_t mod() noexcept {\n        return _mod;\n\
    \    }\n\n    static void set_mod(uint32_t modulus) noexcept {\n        assert(modulus\
    \ > 0);\n        assert(modulus <= uint32_t(1) << 31);\n        _mod = modulus;\n\
    \    }\n\n    static DynamicModInt raw(uint32_t v) noexcept {\n        assert(v\
    \ < _mod);\n        DynamicModInt x;\n        x._v = v;\n        return x;\n \
    \   }\n\n    DynamicModInt() noexcept : _v(0) {}\n\n    template <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    DynamicModInt(Integer\
    \ v) noexcept {\n        if constexpr (std::is_signed_v<Integer>) {\n        \
    \    int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(_mod);\n     \
    \       if (x < 0) x += _mod;\n            _v = static_cast<uint32_t>(x);\n  \
    \      } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % _mod);\n        }\n    }\n\n    uint32_t val() const noexcept {\n        return\
    \ _v;\n    }\n\n    DynamicModInt& operator++() noexcept {\n        _v++;\n  \
    \      if (_v == _mod) _v = 0;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator--() noexcept {\n        if (_v == 0) _v = _mod;\n        _v--;\n  \
    \      return *this;\n    }\n\n    DynamicModInt operator++(int) noexcept {\n\
    \        DynamicModInt result = *this;\n        ++*this;\n        return result;\n\
    \    }\n\n    DynamicModInt operator--(int) noexcept {\n        DynamicModInt\
    \ result = *this;\n        --*this;\n        return result;\n    }\n\n    DynamicModInt&\
    \ operator+=(const DynamicModInt& rhs) noexcept {\n        _v += rhs._v;\n   \
    \     if (_v >= _mod) _v -= _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator-=(const DynamicModInt& rhs) noexcept {\n        _v -= rhs._v;\n   \
    \     if (_v >= _mod) _v += _mod;\n        return *this;\n    }\n\n    DynamicModInt&\
    \ operator*=(const DynamicModInt& rhs) noexcept {\n        _v = static_cast<uint32_t>(uint64_t(_v)\
    \ * rhs._v % _mod);\n        return *this;\n    }\n\n    DynamicModInt& operator/=(const\
    \ DynamicModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n\
    \    DynamicModInt operator+(const DynamicModInt& rhs) const noexcept {\n    \
    \    return DynamicModInt(*this) += rhs;\n    }\n\n    DynamicModInt operator-(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) -=\
    \ rhs;\n    }\n\n    DynamicModInt operator*(const DynamicModInt& rhs) const noexcept\
    \ {\n        return DynamicModInt(*this) *= rhs;\n    }\n\n    DynamicModInt operator/(const\
    \ DynamicModInt& rhs) const noexcept {\n        return DynamicModInt(*this) /=\
    \ rhs;\n    }\n\n    bool operator==(const DynamicModInt& rhs) const noexcept\
    \ {\n        return _v == rhs._v;\n    }\n\n    bool operator!=(const DynamicModInt&\
    \ rhs) const noexcept {\n        return _v != rhs._v;\n    }\n\n    DynamicModInt\
    \ pow(long long exponent) const noexcept {\n        assert(exponent >= 0);\n \
    \       DynamicModInt result = raw(1 % _mod);\n        DynamicModInt base = *this;\n\
    \        while (exponent > 0) {\n            if (exponent & 1) result *= base;\n\
    \            base *= base;\n            exponent >>= 1;\n        }\n        return\
    \ result;\n    }\n\n    DynamicModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = _mod, u = 1, v = 0;\n        while (b) {\n            int64_t quotient\
    \ = a / b;\n            a -= quotient * b;\n            std::swap(a, b);\n   \
    \         u -= quotient * v;\n            std::swap(u, v);\n        }\n      \
    \  assert(a == 1);\n        u %= _mod;\n        if (u < 0) u += _mod;\n      \
    \  return raw(static_cast<uint32_t>(u));\n    }\n\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const DynamicModInt& rhs) {\n        return os << rhs._v;\n    }\n\n   \
    \ friend std::istream& operator>>(std::istream& is, DynamicModInt& rhs) {\n  \
    \      long long value;\n        is >> value;\n        rhs = DynamicModInt(value);\n\
    \        return is;\n    }\n};\n\n}  // namespace math\n}  // namespace m1une\n\
    \n\n#line 5 \"verify/math/matrix/hafnian.test.cpp\"\n\n#line 10 \"verify/math/matrix/hafnian.test.cpp\"\
    \n\nnamespace {\n\nusing mint = m1une::math::modint998244353;\nusing Matrix =\
    \ m1une::matrix::Matrix<mint>;\n\nmint naive_hafnian(const Matrix& matrix) {\n\
    \    const int size = matrix.rows();\n    std::vector<mint> memo(std::size_t(1\
    \ << size));\n    std::vector<char> calculated(std::size_t(1 << size), false);\n\
    \    auto solve = [&](auto&& self, int mask) -> mint {\n        if (mask == 0)\
    \ return mint(1);\n        if (calculated[mask]) return memo[mask];\n        calculated[mask]\
    \ = true;\n        const int first = __builtin_ctz(unsigned(mask));\n        mint\
    \ result = 0;\n        for (int second = first + 1; second < size; second++) {\n\
    \            if (mask >> second & 1) {\n                int next = mask ^ (1 <<\
    \ first) ^ (1 << second);\n                result += matrix[first][second] * self(self,\
    \ next);\n            }\n        }\n        return memo[mask] = result;\n    };\n\
    \    return solve(solve, (1 << size) - 1);\n}\n\nvoid test_edge_cases() {\n  \
    \  assert(m1une::matrix::hafnian(Matrix(0, 0)) == mint(1));\n\n    Matrix pair(2,\
    \ 2);\n    pair[0][1] = pair[1][0] = 9;\n    assert(m1une::matrix::hafnian(pair)\
    \ == mint(9));\n\n    Matrix zero(8, 8);\n    assert(m1une::matrix::hafnian(zero)\
    \ == mint(0));\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 0x4d595df4d0f33173ULL;\n\
    \    auto random = [&]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 300;\
    \ trial++) {\n        int size = 2 * int(random() % 6);\n        Matrix matrix(size,\
    \ size);\n        for (int row = 0; row < size; row++) {\n            for (int\
    \ col = row + 1; col < size; col++) {\n                matrix[row][col] = matrix[col][row]\
    \ = int(random() % 21) - 10;\n            }\n        }\n        assert(m1une::matrix::hafnian(matrix)\
    \ == naive_hafnian(matrix));\n    }\n}\n\n}  // namespace\n\nint main() {\n  \
    \  test_edge_cases();\n    test_randomized();\n\n    int size;\n    std::cin >>\
    \ size;\n    Matrix matrix(size, size);\n    for (int row = 0; row < size; row++)\
    \ {\n        for (int col = 0; col < size; col++) std::cin >> matrix[row][col];\n\
    \    }\n    std::cout << m1une::matrix::hafnian(matrix) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/hafnian_of_matrix\"\n\n\
    #include \"../../../math/matrix/hafnian.hpp\"\n#include \"../../../math/modint.hpp\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <vector>\n\
    \nnamespace {\n\nusing mint = m1une::math::modint998244353;\nusing Matrix = m1une::matrix::Matrix<mint>;\n\
    \nmint naive_hafnian(const Matrix& matrix) {\n    const int size = matrix.rows();\n\
    \    std::vector<mint> memo(std::size_t(1 << size));\n    std::vector<char> calculated(std::size_t(1\
    \ << size), false);\n    auto solve = [&](auto&& self, int mask) -> mint {\n \
    \       if (mask == 0) return mint(1);\n        if (calculated[mask]) return memo[mask];\n\
    \        calculated[mask] = true;\n        const int first = __builtin_ctz(unsigned(mask));\n\
    \        mint result = 0;\n        for (int second = first + 1; second < size;\
    \ second++) {\n            if (mask >> second & 1) {\n                int next\
    \ = mask ^ (1 << first) ^ (1 << second);\n                result += matrix[first][second]\
    \ * self(self, next);\n            }\n        }\n        return memo[mask] = result;\n\
    \    };\n    return solve(solve, (1 << size) - 1);\n}\n\nvoid test_edge_cases()\
    \ {\n    assert(m1une::matrix::hafnian(Matrix(0, 0)) == mint(1));\n\n    Matrix\
    \ pair(2, 2);\n    pair[0][1] = pair[1][0] = 9;\n    assert(m1une::matrix::hafnian(pair)\
    \ == mint(9));\n\n    Matrix zero(8, 8);\n    assert(m1une::matrix::hafnian(zero)\
    \ == mint(0));\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 0x4d595df4d0f33173ULL;\n\
    \    auto random = [&]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 300;\
    \ trial++) {\n        int size = 2 * int(random() % 6);\n        Matrix matrix(size,\
    \ size);\n        for (int row = 0; row < size; row++) {\n            for (int\
    \ col = row + 1; col < size; col++) {\n                matrix[row][col] = matrix[col][row]\
    \ = int(random() % 21) - 10;\n            }\n        }\n        assert(m1une::matrix::hafnian(matrix)\
    \ == naive_hafnian(matrix));\n    }\n}\n\n}  // namespace\n\nint main() {\n  \
    \  test_edge_cases();\n    test_randomized();\n\n    int size;\n    std::cin >>\
    \ size;\n    Matrix matrix(size, size);\n    for (int row = 0; row < size; row++)\
    \ {\n        for (int col = 0; col < size; col++) std::cin >> matrix[row][col];\n\
    \    }\n    std::cout << m1une::matrix::hafnian(matrix) << '\\n';\n}\n"
  dependsOn:
  - math/matrix/hafnian.hpp
  - math/matrix/matrix.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/math/matrix/hafnian.test.cpp
  requiredBy: []
  timestamp: '2026-07-14 02:42:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/matrix/hafnian.test.cpp
layout: document
redirect_from:
- /verify/verify/math/matrix/hafnian.test.cpp
- /verify/verify/math/matrix/hafnian.test.cpp.html
title: verify/math/matrix/hafnian.test.cpp
---
