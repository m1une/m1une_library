---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/matrix/adjugate.hpp
    title: Adjugate Matrix
  - icon: ':heavy_check_mark:'
    path: math/matrix/all.hpp
    title: Matrix Bundle
  - icon: ':heavy_check_mark:'
    path: math/matrix/bit_matrix.hpp
    title: Bit Matrix
  - icon: ':heavy_check_mark:'
    path: math/matrix/characteristic_polynomial.hpp
    title: Characteristic Polynomial
  - icon: ':heavy_check_mark:'
    path: math/matrix/determinant_mod.hpp
    title: Determinant Modulo a Composite Modulus
  - icon: ':heavy_check_mark:'
    path: math/matrix/hafnian.hpp
    title: Hafnian
  - icon: ':heavy_check_mark:'
    path: math/matrix/linear_algebra.hpp
    title: Matrix Linear Algebra
  - icon: ':heavy_check_mark:'
    path: math/matrix/matrix.hpp
    title: Dense Matrix
  - icon: ':heavy_check_mark:'
    path: math/matrix/pfaffian.hpp
    title: Pfaffian
  - icon: ':heavy_check_mark:'
    path: math/matrix/sparse_determinant.hpp
    title: Sparse Determinant
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/pow_of_matrix
    links:
    - https://judge.yosupo.jp/problem/pow_of_matrix
  bundledCode: "#line 1 \"verify/math/matrix/matrix.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/pow_of_matrix\"\n\n#line 1 \"math/modint.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n#include\
    \ <type_traits>\n#include <utility>\n\nnamespace m1une {\nnamespace math {\n\n\
    template <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus, \"\
    Modulus must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n\
    \    static constexpr uint32_t mod() {\n        return Modulus;\n    }\n\n   \
    \ static constexpr ModInt raw(uint32_t v) noexcept {\n        ModInt x;\n    \
    \    x._v = v;\n        return x;\n    }\n\n    constexpr ModInt() noexcept :\
    \ _v(0) {}\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
    \ int> = 0>\n    constexpr ModInt(Integer v) noexcept {\n        if constexpr\
    \ (std::is_signed_v<Integer>) {\n            int64_t x = static_cast<int64_t>(v)\
    \ % static_cast<int64_t>(Modulus);\n            if (x < 0) x += Modulus;\n   \
    \         _v = static_cast<uint32_t>(x);\n        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
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
    \ res = raw(1 % Modulus);\n        ModInt x = n < 0 ? inv() : *this;\n       \
    \ uint64_t exponent = n < 0 ? uint64_t(-(n + 1)) + 1 : uint64_t(n);\n        while\
    \ (exponent > 0) {\n            if (exponent & 1) res *= x;\n            x *=\
    \ x;\n            exponent >>= 1;\n        }\n        return res;\n    }\n\n \
    \   constexpr ModInt inv() const noexcept {\n        int64_t a = _v, b = Modulus,\
    \ u = 1, v = 0;\n        while (b) {\n            int64_t t = a / b;\n       \
    \     a -= t * b;\n            std::swap(a, b);\n            u -= t * v;\n   \
    \         std::swap(u, v);\n        }\n        assert(a == 1);\n        u %= Modulus;\n\
    \        if (u < 0) u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n\
    \    }\n\n    friend std::ostream& operator<<(std::ostream& os, const ModInt&\
    \ rhs) {\n        return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
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
    \ pow(long long exponent) const noexcept {\n        DynamicModInt result = raw(1\
    \ % _mod);\n        DynamicModInt base = exponent < 0 ? inv() : *this;\n     \
    \   uint64_t magnitude =\n            exponent < 0 ? uint64_t(-(exponent + 1))\
    \ + 1 : uint64_t(exponent);\n        while (magnitude > 0) {\n            if (magnitude\
    \ & 1) result *= base;\n            base *= base;\n            magnitude >>= 1;\n\
    \        }\n        return result;\n    }\n\n    DynamicModInt inv() const noexcept\
    \ {\n        int64_t a = _v, b = _mod, u = 1, v = 0;\n        while (b) {\n  \
    \          int64_t quotient = a / b;\n            a -= quotient * b;\n       \
    \     std::swap(a, b);\n            u -= quotient * v;\n            std::swap(u,\
    \ v);\n        }\n        assert(a == 1);\n        u %= _mod;\n        if (u <\
    \ 0) u += _mod;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const DynamicModInt& rhs) {\n   \
    \     return os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream&\
    \ is, DynamicModInt& rhs) {\n        long long value;\n        is >> value;\n\
    \        rhs = DynamicModInt(value);\n        return is;\n    }\n};\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 1 \"math/matrix/all.hpp\"\n\n\n\n#line\
    \ 1 \"math/matrix/adjugate.hpp\"\n\n\n\n#line 5 \"math/matrix/adjugate.hpp\"\n\
    #include <vector>\n\n#line 1 \"math/matrix/matrix.hpp\"\n\n\n\n#line 5 \"math/matrix/matrix.hpp\"\
    \n#include <cstddef>\n#line 9 \"math/matrix/matrix.hpp\"\n\nnamespace m1une {\n\
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
    \n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 8 \"math/matrix/adjugate.hpp\"\
    \n\nnamespace m1une {\nnamespace matrix {\n\ntemplate <class T>\nMatrix<T> adjugate(Matrix<T>\
    \ matrix) {\n    assert(matrix.rows() == matrix.cols());\n    const int size =\
    \ matrix.rows();\n    Matrix<T> augmented(size, size * 2);\n    for (int row =\
    \ 0; row < size; row++) {\n        for (int col = 0; col < size; col++) {\n  \
    \          augmented[row][col] = matrix[row][col];\n        }\n        augmented[row][size\
    \ + row] = T(1);\n    }\n\n    std::vector<int> pivot_columns;\n    T pivot_product\
    \ = T(1);\n    bool negate = false;\n    for (int col = 0; col < size && int(pivot_columns.size())\
    \ < size; col++) {\n        const int pivot_row = int(pivot_columns.size());\n\
    \        int pivot = pivot_row;\n        while (pivot < size && augmented[pivot][col]\
    \ == T()) pivot++;\n        if (pivot == size) continue;\n        if (pivot !=\
    \ pivot_row) {\n            augmented.swap_rows(pivot, pivot_row);\n         \
    \   negate = !negate;\n        }\n\n        const T pivot_value = augmented[pivot_row][col];\n\
    \        pivot_product *= pivot_value;\n        const T inverse_pivot = T(1) /\
    \ pivot_value;\n        for (int index = col; index < size; index++) {\n     \
    \       augmented[pivot_row][index] *= inverse_pivot;\n        }\n        for\
    \ (int index = size; index < size * 2; index++) {\n            augmented[pivot_row][index]\
    \ *= inverse_pivot;\n        }\n\n        for (int row = 0; row < size; row++)\
    \ {\n            if (row == pivot_row || augmented[row][col] == T()) continue;\n\
    \            const T factor = augmented[row][col];\n            augmented[row][col]\
    \ = T();\n            for (int index = col + 1; index < size; index++) {\n   \
    \             augmented[row][index] -= factor * augmented[pivot_row][index];\n\
    \            }\n            for (int index = size; index < size * 2; index++)\
    \ {\n                augmented[row][index] -= factor * augmented[pivot_row][index];\n\
    \            }\n        }\n        pivot_columns.push_back(col);\n    }\n\n  \
    \  const int rank = int(pivot_columns.size());\n    Matrix<T> result(size, size);\n\
    \    if (rank + 1 < size) return result;\n\n    if (rank == size) {\n        const\
    \ T determinant = negate ? T() - pivot_product : pivot_product;\n        for (int\
    \ row = 0; row < size; row++) {\n            for (int col = 0; col < size; col++)\
    \ {\n                result[row][col] = determinant * augmented[row][size + col];\n\
    \            }\n        }\n        return result;\n    }\n\n    int free_column\
    \ = 0;\n    while (free_column < rank && pivot_columns[free_column] == free_column)\
    \ {\n        free_column++;\n    }\n    std::vector<T> right_null(size);\n   \
    \ right_null[free_column] = T(1);\n    for (int row = 0; row < rank; row++) {\n\
    \        right_null[pivot_columns[row]] = T() - augmented[row][free_column];\n\
    \    }\n\n    T scale = pivot_product;\n    if (negate != bool((size - 1 + free_column)\
    \ & 1)) scale = T() - scale;\n    for (int row = 0; row < size; row++) {\n   \
    \     for (int col = 0; col < size; col++) {\n            result[row][col] =\n\
    \                scale * right_null[row] * augmented[size - 1][size + col];\n\
    \        }\n    }\n    return result;\n}\n\n}  // namespace matrix\n}  // namespace\
    \ m1une\n\n\n#line 1 \"math/matrix/bit_matrix.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <bit>\n#line 9 \"math/matrix/bit_matrix.hpp\"\n#include <optional>\n\
    #include <string>\n#include <string_view>\n#line 14 \"math/matrix/bit_matrix.hpp\"\
    \n\nnamespace m1une {\nnamespace matrix {\n\nclass BitMatrix {\n   private:\n\
    \    int _rows;\n    int _cols;\n    int _blocks;\n    std::vector<std::uint64_t>\
    \ _data;\n\n    static int block_count(int cols) {\n        assert(cols >= 0);\n\
    \        return (cols + 63) / 64;\n    }\n\n    static std::size_t storage_size(int\
    \ rows, int blocks) {\n        assert(rows >= 0);\n        return std::size_t(rows)\
    \ * std::size_t(blocks);\n    }\n\n    std::size_t word_index(int row, int col)\
    \ const {\n        assert(0 <= row && row < _rows);\n        assert(0 <= col &&\
    \ col < _cols);\n        return std::size_t(row) * std::size_t(_blocks) +\n  \
    \             std::size_t(col / 64);\n    }\n\n    std::uint64_t trailing_mask()\
    \ const {\n        if ((_cols & 63) == 0) return ~std::uint64_t(0);\n        return\
    \ (std::uint64_t(1) << (_cols & 63)) - 1;\n    }\n\n   public:\n    class BitReference\
    \ {\n       private:\n        std::uint64_t* word;\n        std::uint64_t mask;\n\
    \n       public:\n        BitReference(std::uint64_t& word_value, std::uint64_t\
    \ mask_value)\n            : word(&word_value), mask(mask_value) {}\n\n      \
    \  operator bool() const {\n            return (*word & mask) != 0;\n        }\n\
    \n        BitReference& operator=(bool value) {\n            if (value) {\n  \
    \              *word |= mask;\n            } else {\n                *word &=\
    \ ~mask;\n            }\n            return *this;\n        }\n\n        BitReference&\
    \ operator=(const BitReference& other) {\n            return *this = bool(other);\n\
    \        }\n\n        void flip() {\n            *word ^= mask;\n        }\n \
    \   };\n\n    class RowReference {\n       private:\n        BitMatrix* matrix;\n\
    \        int row;\n\n       public:\n        RowReference(BitMatrix& matrix_value,\
    \ int row_value)\n            : matrix(&matrix_value), row(row_value) {}\n\n \
    \       BitReference operator[](int col) const {\n            return (*matrix)(row,\
    \ col);\n        }\n    };\n\n    class ConstRowReference {\n       private:\n\
    \        const BitMatrix* matrix;\n        int row;\n\n       public:\n      \
    \  ConstRowReference(const BitMatrix& matrix_value, int row_value)\n         \
    \   : matrix(&matrix_value), row(row_value) {}\n\n        bool operator[](int\
    \ col) const {\n            return (*matrix)(row, col);\n        }\n    };\n\n\
    \    BitMatrix() : _rows(0), _cols(0), _blocks(0) {}\n\n    BitMatrix(int rows,\
    \ int cols, bool value = false)\n        : _rows(rows),\n          _cols(cols),\n\
    \          _blocks(block_count(cols)),\n          _data(\n              storage_size(rows,\
    \ _blocks),\n              value ? ~std::uint64_t(0) : std::uint64_t(0)\n    \
    \      ) {\n        assert(rows >= 0);\n        if (value && _blocks > 0) {\n\
    \            const std::uint64_t mask = trailing_mask();\n            for (int\
    \ row = 0; row < _rows; row++) {\n                _data[\n                   \
    \ std::size_t(row + 1) * std::size_t(_blocks) - 1\n                ] &= mask;\n\
    \            }\n        }\n    }\n\n    int rows() const {\n        return _rows;\n\
    \    }\n\n    int cols() const {\n        return _cols;\n    }\n\n    int blocks_per_row()\
    \ const {\n        return _blocks;\n    }\n\n    bool empty() const {\n      \
    \  return _rows == 0 || _cols == 0;\n    }\n\n    RowReference operator[](int\
    \ row) {\n        assert(0 <= row && row < _rows);\n        return RowReference(*this,\
    \ row);\n    }\n\n    ConstRowReference operator[](int row) const {\n        assert(0\
    \ <= row && row < _rows);\n        return ConstRowReference(*this, row);\n   \
    \ }\n\n    BitReference operator()(int row, int col) {\n        const std::size_t\
    \ index = word_index(row, col);\n        return BitReference(_data[index], std::uint64_t(1)\
    \ << (col & 63));\n    }\n\n    bool operator()(int row, int col) const {\n  \
    \      const std::size_t index = word_index(row, col);\n        return (_data[index]\
    \ >> (col & 63)) & 1;\n    }\n\n    bool get(int row, int col) const {\n     \
    \   return (*this)(row, col);\n    }\n\n    void set(int row, int col, bool value\
    \ = true) {\n        (*this)(row, col) = value;\n    }\n\n    void reset(int row,\
    \ int col) {\n        set(row, col, false);\n    }\n\n    void flip(int row, int\
    \ col) {\n        (*this)(row, col).flip();\n    }\n\n    void clear() {\n   \
    \     std::fill(_data.begin(), _data.end(), std::uint64_t(0));\n    }\n\n    void\
    \ set_row(int row, std::string_view bits) {\n        assert(0 <= row && row <\
    \ _rows);\n        assert(int(bits.size()) == _cols);\n        const std::size_t\
    \ offset =\n            std::size_t(row) * std::size_t(_blocks);\n        std::fill(\n\
    \            _data.begin() + std::ptrdiff_t(offset),\n            _data.begin()\
    \ + std::ptrdiff_t(offset + std::size_t(_blocks)),\n            std::uint64_t(0)\n\
    \        );\n        for (int col = 0; col < _cols; col++) {\n            assert(bits[std::size_t(col)]\
    \ == '0' || bits[std::size_t(col)] == '1');\n            if (bits[std::size_t(col)]\
    \ == '1') set(row, col);\n        }\n    }\n\n    std::string row_string(int row)\
    \ const {\n        assert(0 <= row && row < _rows);\n        std::string result(std::size_t(_cols),\
    \ '0');\n        for (int col = 0; col < _cols; col++) {\n            if (get(row,\
    \ col)) result[std::size_t(col)] = '1';\n        }\n        return result;\n \
    \   }\n\n    static BitMatrix identity(int size) {\n        assert(size >= 0);\n\
    \        BitMatrix result(size, size);\n        for (int index = 0; index < size;\
    \ index++) result.set(index, index);\n        return result;\n    }\n\n    BitMatrix\
    \ transposed() const {\n        BitMatrix result(_cols, _rows);\n        for (int\
    \ row = 0; row < _rows; row++) {\n            for (int col = 0; col < _cols; col++)\
    \ {\n                if (get(row, col)) result.set(col, row);\n            }\n\
    \        }\n        return result;\n    }\n\n    void swap_rows(int first, int\
    \ second) {\n        assert(0 <= first && first < _rows);\n        assert(0 <=\
    \ second && second < _rows);\n        if (first == second) return;\n        const\
    \ std::size_t first_offset =\n            std::size_t(first) * std::size_t(_blocks);\n\
    \        const std::size_t second_offset =\n            std::size_t(second) *\
    \ std::size_t(_blocks);\n        for (int block = 0; block < _blocks; block++)\
    \ {\n            std::swap(\n                _data[first_offset + std::size_t(block)],\n\
    \                _data[second_offset + std::size_t(block)]\n            );\n \
    \       }\n    }\n\n    void xor_rows(int target, int source, int first_col =\
    \ 0) {\n        assert(0 <= target && target < _rows);\n        assert(0 <= source\
    \ && source < _rows);\n        assert(0 <= first_col && first_col <= _cols);\n\
    \        if (first_col == _cols) return;\n        const std::size_t target_offset\
    \ =\n            std::size_t(target) * std::size_t(_blocks);\n        const std::size_t\
    \ source_offset =\n            std::size_t(source) * std::size_t(_blocks);\n \
    \       const int first_block = first_col / 64;\n        const int first_bit =\
    \ first_col & 63;\n        if (first_bit != 0) {\n            const std::uint64_t\
    \ mask = ~std::uint64_t(0) << first_bit;\n            _data[target_offset + std::size_t(first_block)]\
    \ ^=\n                _data[source_offset + std::size_t(first_block)] & mask;\n\
    \        } else {\n            _data[target_offset + std::size_t(first_block)]\
    \ ^=\n                _data[source_offset + std::size_t(first_block)];\n     \
    \   }\n        for (int block = first_block + 1; block < _blocks; block++) {\n\
    \            _data[target_offset + std::size_t(block)] ^=\n                _data[source_offset\
    \ + std::size_t(block)];\n        }\n    }\n\n    BitMatrix& operator^=(const\
    \ BitMatrix& rhs) {\n        assert(_rows == rhs._rows && _cols == rhs._cols);\n\
    \        for (std::size_t index = 0; index < _data.size(); index++) {\n      \
    \      _data[index] ^= rhs._data[index];\n        }\n        return *this;\n \
    \   }\n\n    BitMatrix& operator+=(const BitMatrix& rhs) {\n        return *this\
    \ ^= rhs;\n    }\n\n    BitMatrix& operator-=(const BitMatrix& rhs) {\n      \
    \  return *this ^= rhs;\n    }\n\n    BitMatrix& operator*=(const BitMatrix& rhs)\
    \ {\n        return *this = *this * rhs;\n    }\n\n    friend BitMatrix operator^(BitMatrix\
    \ lhs, const BitMatrix& rhs) {\n        return lhs ^= rhs;\n    }\n\n    friend\
    \ BitMatrix operator+(BitMatrix lhs, const BitMatrix& rhs) {\n        return lhs\
    \ += rhs;\n    }\n\n    friend BitMatrix operator-(BitMatrix lhs, const BitMatrix&\
    \ rhs) {\n        return lhs -= rhs;\n    }\n\n    friend BitMatrix operator*(const\
    \ BitMatrix& lhs, const BitMatrix& rhs) {\n        assert(lhs._cols == rhs._rows);\n\
    \        BitMatrix result(lhs._rows, rhs._cols);\n        for (int row = 0; row\
    \ < lhs._rows; row++) {\n            const std::size_t lhs_offset =\n        \
    \        std::size_t(row) * std::size_t(lhs._blocks);\n            const std::size_t\
    \ result_offset =\n                std::size_t(row) * std::size_t(result._blocks);\n\
    \            for (int lhs_block = 0; lhs_block < lhs._blocks; lhs_block++) {\n\
    \                std::uint64_t word =\n                    lhs._data[lhs_offset\
    \ + std::size_t(lhs_block)];\n                while (word != 0) {\n          \
    \          const int bit = std::countr_zero(word);\n                    const\
    \ int middle = lhs_block * 64 + bit;\n                    const std::size_t rhs_offset\
    \ =\n                        std::size_t(middle) * std::size_t(rhs._blocks);\n\
    \                    for (int block = 0; block < rhs._blocks; block++) {\n   \
    \                     result._data[result_offset + std::size_t(block)] ^=\n  \
    \                          rhs._data[rhs_offset + std::size_t(block)];\n     \
    \               }\n                    word &= word - 1;\n                }\n\
    \            }\n        }\n        return result;\n    }\n\n    bool operator==(const\
    \ BitMatrix& rhs) const {\n        return\n            _rows == rhs._rows && _cols\
    \ == rhs._cols && _data == rhs._data;\n    }\n\n    bool operator!=(const BitMatrix&\
    \ rhs) const {\n        return !(*this == rhs);\n    }\n\n    BitMatrix pow(std::uint64_t\
    \ exponent) const {\n        assert(_rows == _cols);\n        BitMatrix result\
    \ = identity(_rows);\n        BitMatrix base = *this;\n        while (exponent\
    \ > 0) {\n            if (exponent & 1) result *= base;\n            exponent\
    \ >>= 1;\n            if (exponent > 0) base *= base;\n        }\n        return\
    \ result;\n    }\n};\n\nnamespace bit_matrix_detail {\n\ninline std::vector<int>\
    \ row_reduce(\n    BitMatrix& matrix,\n    int pivot_col_limit,\n    bool reduced\n\
    ) {\n    assert(0 <= pivot_col_limit && pivot_col_limit <= matrix.cols());\n \
    \   std::vector<int> pivot_columns;\n    int pivot_row = 0;\n    for (\n     \
    \   int col = 0;\n        col < pivot_col_limit && pivot_row < matrix.rows();\n\
    \        col++\n    ) {\n        int pivot = -1;\n        for (int row = pivot_row;\
    \ row < matrix.rows(); row++) {\n            if (matrix.get(row, col)) {\n   \
    \             pivot = row;\n                break;\n            }\n        }\n\
    \        if (pivot == -1) continue;\n        matrix.swap_rows(pivot_row, pivot);\n\
    \n        const int first_row = reduced ? 0 : pivot_row + 1;\n        for (int\
    \ row = first_row; row < matrix.rows(); row++) {\n            if (row != pivot_row\
    \ && matrix.get(row, col)) {\n                matrix.xor_rows(row, pivot_row,\
    \ col);\n            }\n        }\n        pivot_columns.push_back(col);\n   \
    \     pivot_row++;\n    }\n    return pivot_columns;\n}\n\n}  // namespace bit_matrix_detail\n\
    \nstruct BitRowReduction {\n    BitMatrix matrix;\n    std::vector<int> pivot_columns;\n\
    \n    int rank() const {\n        return int(pivot_columns.size());\n    }\n};\n\
    \ninline BitRowReduction reduced_row_echelon_form(BitMatrix matrix) {\n    BitRowReduction\
    \ result;\n    result.pivot_columns = bit_matrix_detail::row_reduce(\n       \
    \ matrix,\n        matrix.cols(),\n        true\n    );\n    result.matrix = std::move(matrix);\n\
    \    return result;\n}\n\ninline int matrix_rank(BitMatrix matrix) {\n    if (matrix.rows()\
    \ > matrix.cols()) matrix = matrix.transposed();\n    return int(bit_matrix_detail::row_reduce(\n\
    \        matrix,\n        matrix.cols(),\n        false\n    ).size());\n}\n\n\
    inline bool determinant(const BitMatrix& matrix) {\n    assert(matrix.rows() ==\
    \ matrix.cols());\n    return matrix_rank(matrix) == matrix.rows();\n}\n\ninline\
    \ std::optional<BitMatrix> inverse(const BitMatrix& matrix) {\n    assert(matrix.rows()\
    \ == matrix.cols());\n    const int size = matrix.rows();\n    BitMatrix augmented(size,\
    \ 2 * size);\n    for (int row = 0; row < size; row++) {\n        for (int col\
    \ = 0; col < size; col++) {\n            if (matrix.get(row, col)) augmented.set(row,\
    \ col);\n        }\n        augmented.set(row, size + row);\n    }\n\n    const\
    \ std::vector<int> pivots = bit_matrix_detail::row_reduce(\n        augmented,\n\
    \        size,\n        true\n    );\n    if (int(pivots.size()) != size) return\
    \ std::nullopt;\n\n    BitMatrix result(size, size);\n    for (int row = 0; row\
    \ < size; row++) {\n        for (int col = 0; col < size; col++) {\n         \
    \   if (augmented.get(row, size + col)) result.set(row, col);\n        }\n   \
    \ }\n    return result;\n}\n\nstruct BitLinearSystemResult {\n    bool consistent\
    \ = false;\n    std::vector<bool> particular_solution;\n    std::vector<std::vector<bool>>\
    \ nullspace_basis;\n    std::vector<int> pivot_columns;\n\n    int rank() const\
    \ {\n        return int(pivot_columns.size());\n    }\n\n    int nullity() const\
    \ {\n        return consistent ? int(nullspace_basis.size()) : 0;\n    }\n\n \
    \   bool has_unique_solution() const {\n        return consistent && nullspace_basis.empty();\n\
    \    }\n};\n\ninline BitLinearSystemResult solve_linear_system(\n    const BitMatrix&\
    \ coefficients,\n    const std::vector<bool>& constants\n) {\n    assert(coefficients.rows()\
    \ == int(constants.size()));\n    const int equation_count = coefficients.rows();\n\
    \    const int variable_count = coefficients.cols();\n    BitMatrix augmented(equation_count,\
    \ variable_count + 1);\n    for (int row = 0; row < equation_count; row++) {\n\
    \        for (int col = 0; col < variable_count; col++) {\n            if (coefficients.get(row,\
    \ col)) augmented.set(row, col);\n        }\n        if (constants[std::size_t(row)])\
    \ augmented.set(row, variable_count);\n    }\n\n    BitLinearSystemResult result;\n\
    \    result.pivot_columns = bit_matrix_detail::row_reduce(\n        augmented,\n\
    \        variable_count,\n        true\n    );\n    for (int row = result.rank();\
    \ row < equation_count; row++) {\n        if (augmented.get(row, variable_count))\
    \ return result;\n    }\n\n    result.consistent = true;\n    result.particular_solution.assign(std::size_t(variable_count),\
    \ false);\n    std::vector<bool> is_pivot(std::size_t(variable_count), false);\n\
    \    for (int row = 0; row < result.rank(); row++) {\n        const int col =\
    \ result.pivot_columns[std::size_t(row)];\n        is_pivot[std::size_t(col)]\
    \ = true;\n        result.particular_solution[std::size_t(col)] =\n          \
    \  augmented.get(row, variable_count);\n    }\n\n    for (int free_col = 0; free_col\
    \ < variable_count; free_col++) {\n        if (is_pivot[std::size_t(free_col)])\
    \ continue;\n        std::vector<bool> direction(std::size_t(variable_count),\
    \ false);\n        direction[std::size_t(free_col)] = true;\n        for (int\
    \ row = 0; row < result.rank(); row++) {\n            const int pivot_col = result.pivot_columns[std::size_t(row)];\n\
    \            direction[std::size_t(pivot_col)] = augmented.get(row, free_col);\n\
    \        }\n        result.nullspace_basis.push_back(std::move(direction));\n\
    \    }\n    return result;\n}\n\n}  // namespace matrix\n}  // namespace m1une\n\
    \n\n#line 1 \"math/matrix/characteristic_polynomial.hpp\"\n\n\n\n#line 8 \"math/matrix/characteristic_polynomial.hpp\"\
    \n\n#line 10 \"math/matrix/characteristic_polynomial.hpp\"\n\nnamespace m1une\
    \ {\nnamespace matrix {\n\ntemplate <class T>\nstd::vector<T> characteristic_polynomial(Matrix<T>\
    \ matrix) {\n    assert(matrix.rows() == matrix.cols());\n    const int size =\
    \ matrix.rows();\n\n    for (int col = 0; col + 2 < size; col++) {\n        int\
    \ pivot = col + 1;\n        while (pivot < size && matrix[pivot][col] == T())\
    \ pivot++;\n        if (pivot == size) continue;\n\n        if (pivot != col +\
    \ 1) {\n            matrix.swap_rows(pivot, col + 1);\n            for (int row\
    \ = 0; row < size; row++) {\n                std::swap(matrix[row][pivot], matrix[row][col\
    \ + 1]);\n            }\n        }\n\n        const T inverse_pivot = T(1) / matrix[col\
    \ + 1][col];\n        for (int row = col + 2; row < size; row++) {\n         \
    \   if (matrix[row][col] == T()) continue;\n            const T factor = matrix[row][col]\
    \ * inverse_pivot;\n            for (int j = col; j < size; j++) {\n         \
    \       matrix[row][j] -= factor * matrix[col + 1][j];\n            }\n      \
    \      for (int i = 0; i < size; i++) {\n                matrix[i][col + 1] +=\
    \ factor * matrix[i][row];\n            }\n        }\n    }\n\n    std::vector<std::vector<T>>\
    \ polynomial(std::size_t(size + 1));\n    polynomial[0].assign(1, T(1));\n   \
    \ for (int leading_size = 1; leading_size <= size; leading_size++) {\n       \
    \ const int last = leading_size - 1;\n        polynomial[std::size_t(leading_size)].assign(\n\
    \            std::size_t(leading_size + 1),\n            T()\n        );\n   \
    \     const std::vector<T>& previous =\n            polynomial[std::size_t(leading_size\
    \ - 1)];\n        std::vector<T>& current = polynomial[std::size_t(leading_size)];\n\
    \n        for (int degree = 0; degree < leading_size; degree++) {\n          \
    \  current[std::size_t(degree)] -=\n                previous[std::size_t(degree)]\
    \ * matrix[last][last];\n            current[std::size_t(degree + 1)] +=\n   \
    \             previous[std::size_t(degree)];\n        }\n\n        T subdiagonal_product\
    \ = T(1);\n        for (int row = last - 1; row >= 0; row--) {\n            subdiagonal_product\
    \ *= matrix[row + 1][row];\n            const T factor = subdiagonal_product *\
    \ matrix[row][last];\n            if (factor == T()) continue;\n            for\
    \ (int degree = 0; degree <= row; degree++) {\n                current[std::size_t(degree)]\
    \ -=\n                    factor * polynomial[std::size_t(row)][std::size_t(degree)];\n\
    \            }\n        }\n    }\n    return polynomial[std::size_t(size)];\n\
    }\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 1 \"math/matrix/determinant_mod.hpp\"\
    \n\n\n\n#line 7 \"math/matrix/determinant_mod.hpp\"\n\n#line 9 \"math/matrix/determinant_mod.hpp\"\
    \n\nnamespace m1une {\nnamespace matrix {\n\nnamespace detail {\n\ninline std::uint64_t\
    \ determinant_multiply_mod(std::uint64_t lhs,\n                              \
    \                std::uint64_t rhs,\n                                        \
    \      std::uint64_t modulus) {\n    return std::uint64_t(static_cast<unsigned\
    \ __int128>(lhs) * rhs % modulus);\n}\n\ninline std::uint64_t determinant_subtract_product_mod(\n\
    \    std::uint64_t value, std::uint64_t lhs, std::uint64_t rhs,\n    std::uint64_t\
    \ modulus) {\n    const std::uint64_t product = determinant_multiply_mod(lhs,\
    \ rhs, modulus);\n    return std::uint64_t((static_cast<unsigned __int128>(value)\
    \ + modulus - product) %\n                         modulus);\n}\n\ninline std::uint64_t\
    \ determinant_add_products_mod(\n    std::uint64_t first_lhs, std::uint64_t first_rhs,\n\
    \    std::uint64_t second_lhs, std::uint64_t second_rhs,\n    std::uint64_t modulus)\
    \ {\n    const std::uint64_t first =\n        determinant_multiply_mod(first_lhs,\
    \ first_rhs, modulus);\n    const std::uint64_t second =\n        determinant_multiply_mod(second_lhs,\
    \ second_rhs, modulus);\n    return std::uint64_t((static_cast<unsigned __int128>(first)\
    \ + second) % modulus);\n}\n\ntemplate <class Integer>\nstd::uint64_t determinant_normalize(Integer\
    \ value, std::uint64_t modulus) {\n    static_assert(std::is_integral_v<Integer>);\n\
    \    static_assert(sizeof(Integer) <= sizeof(std::uint64_t));\n    if constexpr\
    \ (std::is_signed_v<Integer>) {\n        __int128 residue = static_cast<__int128>(value)\
    \ % static_cast<__int128>(modulus);\n        if (residue < 0) residue += modulus;\n\
    \        return std::uint64_t(residue);\n    } else {\n        return std::uint64_t(static_cast<unsigned\
    \ __int128>(value) % modulus);\n    }\n}\n\n}  // namespace detail\n\ntemplate\
    \ <class Integer>\nstd::uint64_t determinant_mod(const Matrix<Integer>& matrix,\n\
    \                              std::uint64_t modulus) {\n    static_assert(std::is_integral_v<Integer>);\n\
    \    assert(matrix.rows() == matrix.cols());\n    assert(modulus > 0);\n    const\
    \ int size = matrix.rows();\n    if (size == 0) return std::uint64_t(1) % modulus;\n\
    \n    Matrix<std::uint64_t> reduced(size, size);\n    for (int row = 0; row <\
    \ size; row++) {\n        for (int col = 0; col < size; col++) {\n           \
    \ reduced[row][col] =\n                detail::determinant_normalize(matrix[row][col],\
    \ modulus);\n        }\n    }\n\n    std::uint64_t result = std::uint64_t(1) %\
    \ modulus;\n    bool negate = false;\n    for (int col = 0; col < size; col++)\
    \ {\n        int pivot = col;\n        while (pivot < size && reduced[pivot][col]\
    \ == 0) pivot++;\n        if (pivot == size) return 0;\n        if (pivot != col)\
    \ {\n            reduced.swap_rows(pivot, col);\n            negate = !negate;\n\
    \        }\n\n        for (int row = col + 1; row < size; row++) {\n         \
    \   std::uint64_t upper = reduced[col][col];\n            std::uint64_t lower\
    \ = reduced[row][col];\n            if (lower == 0) continue;\n\n            std::uint64_t\
    \ upper_upper = 1 % modulus;\n            std::uint64_t upper_lower = 0;\n   \
    \         std::uint64_t lower_upper = 0;\n            std::uint64_t lower_lower\
    \ = 1 % modulus;\n            while (upper != 0 && lower != 0) {\n           \
    \     if (upper < lower) {\n                    const std::uint64_t quotient =\
    \ lower / upper;\n                    lower -= quotient * upper;\n           \
    \         lower_upper = detail::determinant_subtract_product_mod(\n          \
    \              lower_upper, quotient, upper_upper, modulus);\n               \
    \     lower_lower = detail::determinant_subtract_product_mod(\n              \
    \          lower_lower, quotient, upper_lower, modulus);\n                } else\
    \ {\n                    const std::uint64_t quotient = upper / lower;\n     \
    \               upper -= quotient * lower;\n                    upper_upper =\
    \ detail::determinant_subtract_product_mod(\n                        upper_upper,\
    \ quotient, lower_upper, modulus);\n                    upper_lower = detail::determinant_subtract_product_mod(\n\
    \                        upper_lower, quotient, lower_lower, modulus);\n     \
    \           }\n            }\n\n            for (int index = col; index < size;\
    \ index++) {\n                const std::uint64_t old_upper = reduced[col][index];\n\
    \                const std::uint64_t old_lower = reduced[row][index];\n      \
    \          reduced[col][index] = detail::determinant_add_products_mod(\n     \
    \               upper_upper, old_upper, upper_lower, old_lower, modulus);\n  \
    \              reduced[row][index] = detail::determinant_add_products_mod(\n \
    \                   lower_upper, old_upper, lower_lower, old_lower, modulus);\n\
    \            }\n            if (upper == 0) {\n                reduced.swap_rows(col,\
    \ row);\n                negate = !negate;\n            }\n        }\n\n     \
    \   result = detail::determinant_multiply_mod(\n            result, reduced[col][col],\
    \ modulus);\n        if (result == 0) return 0;\n    }\n    return negate ? modulus\
    \ - result : result;\n}\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n\
    #line 1 \"math/matrix/hafnian.hpp\"\n\n\n\n#line 7 \"math/matrix/hafnian.hpp\"\
    \n\n#line 9 \"math/matrix/hafnian.hpp\"\n\nnamespace m1une {\nnamespace matrix\
    \ {\nnamespace internal {\n\ntemplate <class T>\nclass HafnianSolver {\n    using\
    \ Polynomial = std::vector<T>;\n    using PolynomialMatrix = std::vector<std::vector<Polynomial>>;\n\
    \n    int _degree;\n\n    void add_shifted_product(Polynomial& result, const Polynomial&\
    \ first,\n                             const Polynomial& second) const {\n   \
    \     for (int first_degree = 0; first_degree < _degree; first_degree++) {\n \
    \           for (int second_degree = 0;\n                 first_degree + second_degree\
    \ + 1 < _degree;\n                 second_degree++) {\n                result[first_degree\
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
    }\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 1 \"math/matrix/linear_algebra.hpp\"\
    \n\n\n\n#line 7 \"math/matrix/linear_algebra.hpp\"\n\n#line 9 \"math/matrix/linear_algebra.hpp\"\
    \n\nnamespace m1une {\nnamespace matrix {\n\ntemplate <class T>\nconstexpr T default_epsilon()\
    \ {\n    if constexpr (std::is_floating_point_v<T>) {\n        return T(1e-10);\n\
    \    } else {\n        return T();\n    }\n}\n\nnamespace detail {\n\ntemplate\
    \ <class T>\nT matrix_abs(T value) {\n    return value < T() ? T() - value : value;\n\
    }\n\ntemplate <class T>\nbool is_zero(const T& value, const T& eps) {\n    if\
    \ constexpr (std::is_floating_point_v<T>) {\n        return matrix_abs(value)\
    \ <= eps;\n    } else {\n        (void)eps;\n        return value == T();\n  \
    \  }\n}\n\ntemplate <class T>\nint choose_pivot(const Matrix<T>& matrix, int first_row,\
    \ int col, const T& eps) {\n    int pivot = -1;\n    if constexpr (std::is_floating_point_v<T>)\
    \ {\n        for (int row = first_row; row < matrix.rows(); row++) {\n       \
    \     if (is_zero(matrix[row][col], eps)) continue;\n            if (pivot ==\
    \ -1 || matrix_abs(matrix[pivot][col]) < matrix_abs(matrix[row][col])) {\n   \
    \             pivot = row;\n            }\n        }\n    } else {\n        for\
    \ (int row = first_row; row < matrix.rows(); row++) {\n            if (!is_zero(matrix[row][col],\
    \ eps)) {\n                pivot = row;\n                break;\n            }\n\
    \        }\n    }\n    return pivot;\n}\n\ntemplate <class T>\nstd::vector<int>\
    \ row_reduce(Matrix<T>& matrix, int pivot_col_limit, const T& eps,\n         \
    \                   bool reduced) {\n    std::vector<int> pivot_columns;\n   \
    \ int pivot_row = 0;\n    for (int col = 0; col < pivot_col_limit && pivot_row\
    \ < matrix.rows(); col++) {\n        int pivot = choose_pivot(matrix, pivot_row,\
    \ col, eps);\n        if (pivot == -1) continue;\n        matrix.swap_rows(pivot_row,\
    \ pivot);\n\n        const T pivot_value = matrix[pivot_row][col];\n        if\
    \ (reduced) {\n            for (int j = col; j < matrix.cols(); j++) matrix[pivot_row][j]\
    \ /= pivot_value;\n        }\n\n        const int first_row = reduced ? 0 : pivot_row\
    \ + 1;\n        for (int row = first_row; row < matrix.rows(); row++) {\n    \
    \        if (row == pivot_row || is_zero(matrix[row][col], eps)) continue;\n \
    \           T factor = matrix[row][col];\n            if (!reduced) factor /=\
    \ pivot_value;\n            matrix[row][col] = T();\n            for (int j =\
    \ col + 1; j < matrix.cols(); j++) {\n                matrix[row][j] -= factor\
    \ * matrix[pivot_row][j];\n            }\n        }\n\n        pivot_columns.push_back(col);\n\
    \        pivot_row++;\n    }\n\n    if constexpr (std::is_floating_point_v<T>)\
    \ {\n        for (T& value : matrix.data()) {\n            if (is_zero(value,\
    \ eps)) value = T();\n        }\n    }\n    return pivot_columns;\n}\n\n}  //\
    \ namespace detail\n\ntemplate <class T>\nstruct RowReduction {\n    Matrix<T>\
    \ matrix;\n    std::vector<int> pivot_columns;\n\n    int rank() const {\n   \
    \     return int(pivot_columns.size());\n    }\n};\n\ntemplate <class T>\nRowReduction<T>\
    \ reduced_row_echelon_form(Matrix<T> matrix,\n                               \
    \          T eps = default_epsilon<T>()) {\n    RowReduction<T> result;\n    result.pivot_columns\
    \ = detail::row_reduce(matrix, matrix.cols(), eps, true);\n    result.matrix =\
    \ std::move(matrix);\n    return result;\n}\n\ntemplate <class T>\nint matrix_rank(Matrix<T>\
    \ matrix, T eps = default_epsilon<T>()) {\n    return int(detail::row_reduce(matrix,\
    \ matrix.cols(), eps, false).size());\n}\n\ntemplate <class T>\nT determinant(Matrix<T>\
    \ matrix, T eps = default_epsilon<T>()) {\n    assert(matrix.rows() == matrix.cols());\n\
    \    const int size = matrix.rows();\n    T result = T(1);\n    bool negate =\
    \ false;\n\n    for (int col = 0; col < size; col++) {\n        int pivot = detail::choose_pivot(matrix,\
    \ col, col, eps);\n        if (pivot == -1) return T();\n        if (pivot !=\
    \ col) {\n            matrix.swap_rows(pivot, col);\n            negate = !negate;\n\
    \        }\n\n        const T pivot_value = matrix[col][col];\n        result\
    \ *= pivot_value;\n        for (int row = col + 1; row < size; row++) {\n    \
    \        if (detail::is_zero(matrix[row][col], eps)) continue;\n            const\
    \ T factor = matrix[row][col] / pivot_value;\n            matrix[row][col] = T();\n\
    \            for (int j = col + 1; j < size; j++) {\n                matrix[row][j]\
    \ -= factor * matrix[col][j];\n            }\n        }\n    }\n    return negate\
    \ ? T() - result : result;\n}\n\ntemplate <class T>\nstd::optional<Matrix<T>>\
    \ inverse(const Matrix<T>& matrix,\n                                 T eps = default_epsilon<T>())\
    \ {\n    assert(matrix.rows() == matrix.cols());\n    const int size = matrix.rows();\n\
    \    Matrix<T> augmented(size, size * 2);\n    for (int row = 0; row < size; row++)\
    \ {\n        for (int col = 0; col < size; col++) {\n            augmented[row][col]\
    \ = matrix[row][col];\n        }\n        augmented[row][size + row] = T(1);\n\
    \    }\n\n    const std::vector<int> pivots = detail::row_reduce(augmented, size,\
    \ eps, true);\n    if (int(pivots.size()) != size) return std::nullopt;\n\n  \
    \  Matrix<T> result(size, size);\n    for (int row = 0; row < size; row++) {\n\
    \        for (int col = 0; col < size; col++) {\n            result[row][col]\
    \ = augmented[row][size + col];\n        }\n    }\n    return result;\n}\n\ntemplate\
    \ <class T>\nstruct LinearSystemResult {\n    bool consistent = false;\n    std::vector<T>\
    \ particular_solution;\n    std::vector<std::vector<T>> nullspace_basis;\n   \
    \ std::vector<int> pivot_columns;\n\n    int rank() const {\n        return int(pivot_columns.size());\n\
    \    }\n\n    int nullity() const {\n        return consistent ? int(nullspace_basis.size())\
    \ : 0;\n    }\n\n    bool has_unique_solution() const {\n        return consistent\
    \ && nullspace_basis.empty();\n    }\n};\n\ntemplate <class T>\nLinearSystemResult<T>\
    \ solve_linear_system(const Matrix<T>& coefficients,\n                       \
    \                   const std::vector<T>& constants,\n                       \
    \                   T eps = default_epsilon<T>()) {\n    assert(coefficients.rows()\
    \ == int(constants.size()));\n    const int equation_count = coefficients.rows();\n\
    \    const int variable_count = coefficients.cols();\n    Matrix<T> augmented(equation_count,\
    \ variable_count + 1);\n    for (int row = 0; row < equation_count; row++) {\n\
    \        for (int col = 0; col < variable_count; col++) {\n            augmented[row][col]\
    \ = coefficients[row][col];\n        }\n        augmented[row][variable_count]\
    \ = constants[std::size_t(row)];\n    }\n\n    LinearSystemResult<T> result;\n\
    \    result.pivot_columns =\n        detail::row_reduce(augmented, variable_count,\
    \ eps, true);\n\n    for (int row = result.rank(); row < equation_count; row++)\
    \ {\n        bool zero_left = true;\n        for (int col = 0; col < variable_count;\
    \ col++) {\n            if (!detail::is_zero(augmented[row][col], eps)) {\n  \
    \              zero_left = false;\n                break;\n            }\n   \
    \     }\n        if (zero_left && !detail::is_zero(augmented[row][variable_count],\
    \ eps)) {\n            return result;\n        }\n    }\n\n    result.consistent\
    \ = true;\n    result.particular_solution.assign(std::size_t(variable_count),\
    \ T());\n    std::vector<bool> is_pivot(std::size_t(variable_count), false);\n\
    \    for (int row = 0; row < result.rank(); row++) {\n        const int col =\
    \ result.pivot_columns[std::size_t(row)];\n        is_pivot[std::size_t(col)]\
    \ = true;\n        result.particular_solution[std::size_t(col)] = augmented[row][variable_count];\n\
    \    }\n\n    for (int free_col = 0; free_col < variable_count; free_col++) {\n\
    \        if (is_pivot[std::size_t(free_col)]) continue;\n        std::vector<T>\
    \ direction(static_cast<std::size_t>(variable_count));\n        direction[std::size_t(free_col)]\
    \ = T(1);\n        for (int row = 0; row < result.rank(); row++) {\n         \
    \   const int pivot_col = result.pivot_columns[std::size_t(row)];\n          \
    \  direction[std::size_t(pivot_col)] = T() - augmented[row][free_col];\n     \
    \   }\n        result.nullspace_basis.push_back(std::move(direction));\n    }\n\
    \    return result;\n}\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n\
    #line 1 \"math/matrix/pfaffian.hpp\"\n\n\n\n#line 6 \"math/matrix/pfaffian.hpp\"\
    \n\n#line 8 \"math/matrix/pfaffian.hpp\"\n\nnamespace m1une {\nnamespace matrix\
    \ {\n\n// Returns the Pfaffian of an even-dimensional alternating matrix over\
    \ a field.\ntemplate <class T>\nT pfaffian(Matrix<T> matrix) {\n    assert(matrix.rows()\
    \ == matrix.cols());\n    const int size = matrix.rows();\n    assert(size % 2\
    \ == 0);\n\n#ifndef NDEBUG\n    for (int row = 0; row < size; row++) {\n     \
    \   assert(matrix[row][row] == T());\n        for (int col = row + 1; col < size;\
    \ col++) {\n            assert(matrix[row][col] == T() - matrix[col][row]);\n\
    \        }\n    }\n#endif\n\n    T result = T(1);\n    for (int first = 0; first\
    \ < size; first += 2) {\n        int pivot = first + 1;\n        while (pivot\
    \ < size && matrix[first][pivot] == T()) pivot++;\n        if (pivot == size)\
    \ return T();\n\n        if (pivot != first + 1) {\n            matrix.swap_rows(pivot,\
    \ first + 1);\n            for (int row = 0; row < size; row++) {\n          \
    \      std::swap(matrix[row][pivot], matrix[row][first + 1]);\n            }\n\
    \            result = T() - result;\n        }\n\n        const int second = first\
    \ + 1;\n        const T pivot_value = matrix[first][second];\n        result *=\
    \ pivot_value;\n        const T inverse_pivot = T(1) / pivot_value;\n\n      \
    \  for (int row = second + 1; row < size; row++) {\n            for (int col =\
    \ row + 1; col < size; col++) {\n                matrix[row][col] +=\n       \
    \             (matrix[second][row] * matrix[first][col] -\n                  \
    \   matrix[first][row] * matrix[second][col]) *\n                    inverse_pivot;\n\
    \                matrix[col][row] = T() - matrix[row][col];\n            }\n \
    \       }\n    }\n    return result;\n}\n\n}  // namespace matrix\n}  // namespace\
    \ m1une\n\n\n#line 1 \"math/matrix/sparse_determinant.hpp\"\n\n\n\n#line 8 \"\
    math/matrix/sparse_determinant.hpp\"\n\nnamespace m1une {\nnamespace matrix {\n\
    \ntemplate <class T>\nstruct SparseMatrixEntry {\n    int row;\n    int col;\n\
    \    T value;\n};\n\nnamespace internal {\n\nstruct SparseDeterminantRandom {\n\
    \    std::uint64_t state;\n\n    explicit SparseDeterminantRandom(std::uint64_t\
    \ seed) : state(seed) {}\n\n    std::uint64_t operator()() {\n        std::uint64_t\
    \ value = (state += 0x9e3779b97f4a7c15ULL);\n        value = (value ^ (value >>\
    \ 30)) * 0xbf58476d1ce4e5b9ULL;\n        value = (value ^ (value >> 27)) * 0x94d049bb133111ebULL;\n\
    \        return value ^ (value >> 31);\n    }\n};\n\ntemplate <class T>\nstd::vector<T>\
    \ berlekamp_massey(const std::vector<T>& sequence) {\n    std::vector<T> recurrence(1,\
    \ T(1));\n    std::vector<T> previous(1, T(1));\n    int degree = 0;\n    int\
    \ shift = 1;\n    T previous_discrepancy = T(1);\n\n    for (int index = 0; index\
    \ < int(sequence.size()); index++) {\n        T discrepancy = sequence[index];\n\
    \        for (int i = 1; i <= degree; i++) {\n            discrepancy += recurrence[i]\
    \ * sequence[index - i];\n        }\n        if (discrepancy == T()) {\n     \
    \       shift++;\n            continue;\n        }\n\n        const T factor =\
    \ discrepancy / previous_discrepancy;\n        std::vector<T> old_recurrence =\
    \ recurrence;\n        if (int(recurrence.size()) < int(previous.size()) + shift)\
    \ {\n            recurrence.resize(previous.size() + std::size_t(shift), T());\n\
    \        }\n        for (int i = 0; i < int(previous.size()); i++) {\n       \
    \     recurrence[i + shift] -= factor * previous[i];\n        }\n\n        if\
    \ (2 * degree <= index) {\n            degree = index + 1 - degree;\n        \
    \    previous = std::move(old_recurrence);\n            previous_discrepancy =\
    \ discrepancy;\n            shift = 1;\n        } else {\n            shift++;\n\
    \        }\n    }\n    recurrence.resize(std::size_t(degree + 1));\n    return\
    \ recurrence;\n}\n\n}  // namespace internal\n\n// Randomized black-box determinant\
    \ over a finite field. random_nonzero must\n// return independent nonzero field\
    \ elements.\ntemplate <class T, class RandomValue>\nT sparse_determinant_with_randomizer(\n\
    \    int size, const std::vector<SparseMatrixEntry<T>>& entries,\n    RandomValue\
    \ random_nonzero\n) {\n    assert(size >= 0);\n    for (const SparseMatrixEntry<T>&\
    \ entry : entries) {\n        assert(0 <= entry.row && entry.row < size);\n  \
    \      assert(0 <= entry.col && entry.col < size);\n    }\n    if (size == 0)\
    \ return T(1);\n\n    auto random_vector = [&]() {\n        std::vector<T> result(size);\n\
    \        for (T& value : result) {\n            value = random_nonzero();\n  \
    \          assert(value != T());\n        }\n        return result;\n    };\n\n\
    \    while (true) {\n        std::vector<T> diagonal = random_vector();\n    \
    \    std::vector<T> left = random_vector();\n        std::vector<T> state = random_vector();\n\
    \        std::vector<T> sequence(std::size_t(2 * size));\n\n        for (int step\
    \ = 0; step < 2 * size; step++) {\n            for (int i = 0; i < size; i++)\
    \ sequence[step] += left[i] * state[i];\n            for (int i = 0; i < size;\
    \ i++) state[i] *= diagonal[i];\n\n            std::vector<T> next(size);\n  \
    \          for (const SparseMatrixEntry<T>& entry : entries) {\n             \
    \   next[entry.row] += entry.value * state[entry.col];\n            }\n      \
    \      state = std::move(next);\n        }\n\n        std::vector<T> recurrence\
    \ = internal::berlekamp_massey(sequence);\n        if (recurrence.back() == T())\
    \ return T();\n        if (int(recurrence.size()) != size + 1) continue;\n\n \
    \       T determinant = recurrence.back();\n        if (size % 2 == 1) determinant\
    \ = T() - determinant;\n        for (const T& value : diagonal) determinant /=\
    \ value;\n        return determinant;\n    }\n}\n\ntemplate <class T>\nT sparse_determinant(\n\
    \    int size, const std::vector<SparseMatrixEntry<T>>& entries,\n    std::uint64_t\
    \ seed = 0x243f6a8885a308d3ULL\n) {\n    const std::uint64_t modulus = T::mod();\n\
    \    assert(modulus > 1);\n    internal::SparseDeterminantRandom random(seed);\n\
    \    auto random_nonzero = [&]() {\n        return T(1 + random() % (modulus -\
    \ 1));\n    };\n    return sparse_determinant_with_randomizer<T>(size, entries,\
    \ random_nonzero);\n}\n\n}  // namespace matrix\n}  // namespace m1une\n\n\n#line\
    \ 13 \"math/matrix/all.hpp\"\n\n\n#line 5 \"verify/math/matrix/matrix.test.cpp\"\
    \n\n#line 7 \"verify/math/matrix/matrix.test.cpp\"\n#include <cmath>\n#line 1\
    \ \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\n#include\
    \ <array>\n#include <cerrno>\n#include <charconv>\n#line 9 \"utilities/fast_io.hpp\"\
    \n#include <cstdio>\n#include <cstdlib>\n#line 12 \"utilities/fast_io.hpp\"\n\
    #include <cstring>\n#include <iterator>\n#line 15 \"utilities/fast_io.hpp\"\n\
    #include <sys/stat.h>\n#line 18 \"utilities/fast_io.hpp\"\n#include <unistd.h>\n\
    \nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect\
    \ std::begin(x), std::end(x).\ntemplate <class T, class = void>\nstruct is_range\
    \ : std::false_type {};\n\ntemplate <class T>\nstruct is_range<T, std::void_t<\n\
    \    decltype(std::begin(std::declval<T&>())),\n    decltype(std::end(std::declval<T&>()))\n\
    >> : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool is_range_v\
    \ = is_range<T>::value;\n\ntemplate <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
    \ntemplate <class T>\nusing range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;\n\
    \ntemplate <class T, class = void>\nstruct range_stored_value {\n    using type\
    \ = range_value_t<T>;\n};\n\ntemplate <class T>\nstruct range_stored_value<T,\
    \ std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>>\
    \ {\n    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;\n\
    };\n\ntemplate <class T>\nusing range_stored_value_t = typename range_stored_value<T>::type;\n\
    \n// Treat strings and C strings as scalar output objects, not as ranges.\ntemplate\
    \ <class T>\nstruct is_char_array : std::false_type {};\n\ntemplate <class T,\
    \ std::size_t N>\nstruct is_char_array<T[N]>\n    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>,\
    \ char>> {};\n\ntemplate <class T>\nstruct is_string_like\n    : std::bool_constant<\n\
    \          std::is_same_v<std::decay_t<T>, std::string>\n          || std::is_same_v<std::decay_t<T>,\
    \ const char*>\n          || std::is_same_v<std::decay_t<T>, char*>\n        \
    \  || is_char_array<std::remove_reference_t<T>>::value\n      > {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_string_like_v = is_string_like<T>::value;\n\
    \n// ModInt-like type: x.val() is printable, and x can be assigned from long long.\n\
    template <class T, class = void>\nstruct has_val_method : std::false_type {};\n\
    \ntemplate <class T>\nstruct has_val_method<T, std::void_t<decltype(std::declval<const\
    \ T&>().val())>>\n    : std::true_type {};\n\ntemplate <class T>\ninline constexpr\
    \ bool has_val_method_v = has_val_method<T>::value;\n\ntemplate <class T, class\
    \ = void>\nstruct has_static_mod_raw : std::false_type {};\n\ntemplate <class\
    \ T>\nstruct has_static_mod_raw<\n    T, std::void_t<decltype(T::mod()), decltype(T::raw(std::declval<uint32_t>()))>>\n\
    \    : std::true_type {};\n\ntemplate <class T>\ninline constexpr bool has_static_mod_raw_v\
    \ = has_static_mod_raw<T>::value;\n\n// libstdc++ before GCC 16 does not classify\
    \ __int128 as an integral type in\n// strict ISO modes such as -std=c++23. Keep\
    \ the fast-I/O interface independent\n// of that implementation detail.\ntemplate\
    \ <class T>\ninline constexpr bool is_integral_v =\n    std::is_integral_v<T>\n\
    \    || std::is_same_v<std::remove_cv_t<T>, __int128_t>\n    || std::is_same_v<std::remove_cv_t<T>,\
    \ __uint128_t>;\n\ntemplate <class T>\ninline constexpr bool is_signed_v =\n \
    \   std::is_signed_v<T>\n    || std::is_same_v<std::remove_cv_t<T>, __int128_t>;\n\
    \ntemplate <class T>\nstruct make_unsigned {\n    using type = std::make_unsigned_t<T>;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__int128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <>\nstruct make_unsigned<__uint128_t> {\n    using type = __uint128_t;\n\
    };\n\ntemplate <class T>\nusing make_unsigned_t = typename make_unsigned<std::remove_cv_t<T>>::type;\n\
    \n}  // namespace internal\n\nstruct FastInput {\n    static constexpr int buffer_size\
    \ = 1 << 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _length;\n    int _file_descriptor;\n    bool _streaming;\n\
    \n    bool refill() {\n        _position = 0;\n        if (_streaming) {\n   \
    \         ssize_t length;\n            do {\n                length = ::read(_file_descriptor,\
    \ _buffer, buffer_size);\n            } while (length < 0 && errno == EINTR);\n\
    \            if (length <= 0) {\n                _length = 0;\n              \
    \  return false;\n            }\n            _length = int(length);\n        }\
    \ else {\n            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n\
    \        }\n        return _length != 0;\n    }\n\n    template <class T>\n  \
    \  bool read_integer_from_stream(T& value) {\n        if (!skip_spaces()) return\
    \ false;\n        int c = read_char_raw();\n\n        bool negative = false;\n\
    \        if (c == '-') {\n            negative = true;\n            c = read_char_raw();\n\
    \        }\n\n        if constexpr (internal::is_signed_v<T>) {\n            T\
    \ result = 0;\n            while ('0' <= c && c <= '9') {\n                result\
    \ = negative ? result * 10 - (c - '0')\n                                  : result\
    \ * 10 + (c - '0');\n                c = read_char_raw();\n            }\n   \
    \         value = result;\n        } else {\n            T result = 0;\n     \
    \       while ('0' <= c && c <= '9') {\n                result = result * 10 +\
    \ T(c - '0');\n                c = read_char_raw();\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        return true;\n\
    \    }\n\n    bool prepare_number() {\n        if (_length - _position >= 64)\
    \ return true;\n        const int remaining = _length - _position;\n        if\
    \ (remaining > 0) std::memmove(_buffer, _buffer + _position, remaining);\n   \
    \     const int added = int(std::fread(_buffer + remaining, 1, buffer_size - remaining,\
    \ _stream));\n        _position = 0;\n        _length = remaining + added;\n \
    \       if (_length < buffer_size) _buffer[_length] = '\\0';\n        return _length\
    \ != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream),\n          _position(0),\n          _length(0),\n\
    \          _file_descriptor(::fileno(stream)),\n          _streaming([&] {\n \
    \             struct stat status;\n              return _file_descriptor >= 0\n\
    \                     && ::fstat(_file_descriptor, &status) == 0\n           \
    \          && !S_ISREG(status.st_mode);\n          }()) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length && !refill()) return\
    \ EOF;\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces()\
    \ {\n        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c\
    \ = read_char_raw();\n        if (c == EOF) return false;\n        --_position;\n\
    \        return true;\n    }\n\n    bool read(char& value) {\n        if (!skip_spaces())\
    \ return false;\n        value = char(read_char_raw());\n        return true;\n\
    \    }\n\n    bool read(std::string& value) {\n        if (!skip_spaces()) return\
    \ false;\n        value.clear();\n        while (true) {\n            const int\
    \ begin = _position;\n            while (_position < _length &&\n            \
    \       static_cast<unsigned char>(_buffer[_position]) > ' ') {\n            \
    \    ++_position;\n            }\n            value.append(_buffer + begin, _position\
    \ - begin);\n            if (_position < _length) {\n                ++_position;\n\
    \                return true;\n            }\n            if (!refill()) return\
    \ true;\n        }\n    }\n\n    bool read(bool& value) {\n        int x;\n  \
    \      if (!read(x)) return false;\n        value = x != 0;\n        return true;\n\
    \    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>,\n        bool\n    >\n    read(T& value) {\n        if (_streaming) return\
    \ read_integer_from_stream(value);\n        if (!prepare_number()) return false;\n\
    \        int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
    \ (c <= ' ') c = static_cast<unsigned char>(_buffer[_position++]);\n\n       \
    \ bool negative = false;\n        if (c == '-') {\n            negative = true;\n\
    \            c = static_cast<unsigned char>(_buffer[_position++]);\n        }\n\
    \n        if constexpr (internal::is_signed_v<T>) {\n            T result = 0;\n\
    \            while ('0' <= c && c <= '9') {\n                const int first =\
    \ c - '0';\n                const int second = static_cast<unsigned char>(_buffer[_position])\
    \ - '0';\n                if (0 <= second && second <= 9) {\n                \
    \    result = negative ? result * 100 - (first * 10 + second)\n              \
    \                        : result * 100 + (first * 10 + second);\n           \
    \         ++_position;\n                } else {\n                    result =\
    \ negative ? result * 10 - first : result * 10 + first;\n                }\n \
    \               c = static_cast<unsigned char>(_buffer[_position++]);\n      \
    \      }\n            value = result;\n        } else {\n            T result\
    \ = 0;\n            while ('0' <= c && c <= '9') {\n                const unsigned\
    \ first = unsigned(c - '0');\n                const int second = static_cast<unsigned\
    \ char>(_buffer[_position]) - '0';\n                if (0 <= second && second\
    \ <= 9) {\n                    result = result * 100 + T(first * 10 + unsigned(second));\n\
    \                    ++_position;\n                } else {\n                \
    \    result = result * 10 + T(first);\n                }\n                c =\
    \ static_cast<unsigned char>(_buffer[_position++]);\n            }\n         \
    \   value = negative ? T(0) - result : result;\n        }\n        if (_position\
    \ > _length) _position = _length;\n        return true;\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<std::is_floating_point_v<T>, bool>\n    read(T&\
    \ value) {\n        if (!skip_spaces()) return false;\n        int c = read_char_raw();\n\
    \        bool negative = false;\n        if (c == '-' || c == '+') {\n       \
    \     negative = c == '-';\n            c = read_char_raw();\n        }\n\n  \
    \      long double result = 0;\n        while ('0' <= c && c <= '9') {\n     \
    \       result = result * 10 + (c - '0');\n            c = read_char_raw();\n\
    \        }\n        if (c == '.') {\n            long double place = 0.1L;\n \
    \           c = read_char_raw();\n            while ('0' <= c && c <= '9') {\n\
    \                result += (c - '0') * place;\n                place *= 0.1L;\n\
    \                c = read_char_raw();\n            }\n        }\n        if (c\
    \ == 'e' || c == 'E') {\n            c = read_char_raw();\n            bool exponent_negative\
    \ = false;\n            if (c == '-' || c == '+') {\n                exponent_negative\
    \ = c == '-';\n                c = read_char_raw();\n            }\n         \
    \   int exponent = 0;\n            while ('0' <= c && c <= '9') {\n          \
    \      exponent = exponent * 10 + (c - '0');\n                c = read_char_raw();\n\
    \            }\n            long double scale = 1;\n            long double power\
    \ = 10;\n            while (exponent > 0) {\n                if (exponent & 1)\
    \ scale *= power;\n                power *= power;\n                exponent >>=\
    \ 1;\n            }\n            result = exponent_negative ? result / scale :\
    \ result * scale;\n        }\n        value = static_cast<T>(negative ? -result\
    \ : result);\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        if constexpr\
    \ (internal::has_static_mod_raw_v<T>) {\n            if (x >= 0 && uint64_t(x)\
    \ < uint64_t(T::mod())) {\n                value = T::raw(uint32_t(x));\n    \
    \        } else {\n                value = T(x);\n            }\n        } else\
    \ {\n            value = T(x);\n        }\n        return true;\n    }\n\n   \
    \ template <class First, class Second>\n    bool read(std::pair<First, Second>&\
    \ value) {\n        if (!read(value.first)) return false;\n        return read(value.second);\n\
    \    }\n\n    template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>,\n        bool\n    >\n   \
    \ read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n\n    template\
    \ <class T>\n    FastInput& operator>>(T& value) {\n        if (!read(value))\
    \ std::abort();\n        return *this;\n    }\n};\n\nstruct FastOutput {\n   \
    \ static constexpr int buffer_size = 1 << 20;\n\n   private:\n    inline static\
    \ const auto digit_quads = [] {\n        std::array<char, 40000> result{};\n \
    \       for (int i = 0; i < 10000; i++) {\n            int value = i;\n      \
    \      for (int j = 3; j >= 0; j--) {\n                result[4 * i + j] = char('0'\
    \ + value % 10);\n                value /= 10;\n            }\n        }\n   \
    \     return result;\n    }();\n\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n    int _precision;\n    std::chars_format _float_format;\n\
    \    char _range_separator;\n\n   public:\n    explicit FastOutput(std::FILE*\
    \ stream = stdout)\n        : _stream(stream),\n          _position(0),\n    \
    \      _precision(6),\n          _float_format(std::chars_format::general),\n\
    \          _range_separator(' ') {}\n\n    FastOutput(const FastOutput&) = delete;\n\
    \    FastOutput& operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n\
    \        flush();\n    }\n\n    void flush() {\n        if (_position != 0) {\n\
    \            std::fwrite(_buffer, 1, _position, _stream);\n            _position\
    \ = 0;\n        }\n        std::fflush(_stream);\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ std::size_t position = 0;\n        while (position < s.size()) {\n         \
    \   if (_position == buffer_size) flush();\n            const std::size_t copied\
    \ =\n                std::min<std::size_t>(buffer_size - _position, s.size() -\
    \ position);\n            std::memcpy(_buffer + _position, s.data() + position,\
    \ copied);\n            _position += int(copied);\n            position += copied;\n\
    \        }\n    }\n\n    void write(char c) {\n        write_char(c);\n    }\n\
    \n    void write(bool value) {\n        write_char(value ? '1' : '0');\n    }\n\
    \n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
    \    write(T value) {\n        char digits[128];\n        auto [end, error] =\
    \ std::to_chars(\n            digits,\n            digits + sizeof(digits),\n\
    \            value,\n            _float_format,\n            _precision\n    \
    \    );\n        if (error != std::errc()) std::abort();\n        for (const char*\
    \ pointer = digits; pointer != end; pointer++) {\n            write_char(*pointer);\n\
    \        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n        internal::is_integral_v<T>\n\
    \            && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = internal::make_unsigned_t<Raw>;\n\n        Unsigned\
    \ magnitude;\n        if constexpr (internal::is_signed_v<Raw>) {\n          \
    \  if (value < 0) {\n                write_char('-');\n                magnitude\
    \ = Unsigned(0) - Unsigned(value);\n            } else {\n                magnitude\
    \ = Unsigned(value);\n            }\n        } else {\n            magnitude =\
    \ value;\n        }\n\n        if (magnitude == 0) {\n            write_char('0');\n\
    \            return;\n        }\n\n        unsigned chunks[16];\n        int count\
    \ = 0;\n        while (magnitude >= 10000) {\n            const Unsigned quotient\
    \ = magnitude / 10000;\n            chunks[count++] = unsigned(magnitude - quotient\
    \ * 10000);\n            magnitude = quotient;\n        }\n        if (_position\
    \ > buffer_size - 64) flush();\n        const unsigned leading = unsigned(magnitude);\n\
    \        const char* first = digit_quads.data() + 4 * leading;\n        int skip\
    \ = leading < 10 ? 3 : leading < 100 ? 2 : leading < 1000 ? 1 : 0;\n        for\
    \ (; skip < 4; skip++) _buffer[_position++] = first[skip];\n        while (count--)\
    \ {\n            const char* digits = digit_quads.data() + 4 * chunks[count];\n\
    \            std::memcpy(_buffer + _position, digits, 4);\n            _position\
    \ += 4;\n        }\n    }\n\n    template <class T>\n    std::enable_if_t<\n \
    \       internal::has_val_method_v<T>\n            && !internal::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>\n    >\n    write(const T& value) {\n\
    \        write(value.val());\n    }\n\n    template <class First, class Second>\n\
    \    void write(const std::pair<First, Second>& value) {\n        write(value.first);\n\
    \        write_char(' ');\n        write(value.second);\n    }\n\n    template\
    \ <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : _range_separator);\n            first\
    \ = false;\n            if constexpr (std::is_same_v<StoredValue, bool> && !nested)\
    \ {\n                write(static_cast<bool>(value));\n            } else {\n\
    \                write(value);\n            }\n        }\n    }\n\n    template\
    \ <class First, class... Rest>\n    void print(const First& first, const Rest&...\
    \ rest) {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n\
    \    }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void\
    \ set_precision(int precision) {\n        _precision = precision;\n    }\n\n \
    \   void set_fixed(int precision = 6) {\n        _float_format = std::chars_format::fixed;\n\
    \        _precision = precision;\n    }\n\n    void set_general(int precision\
    \ = 6) {\n        _float_format = std::chars_format::general;\n        _precision\
    \ = precision;\n    }\n\n    void set_range_separator(char separator) {\n    \
    \    _range_separator = separator;\n    }\n\n    template <class... Args>\n  \
    \  void println(const Args&... args) {\n        print(args...);\n        write_char('\\\
    n');\n    }\n\n    template <class T>\n    FastOutput& operator<<(const T& value)\
    \ {\n        write(value);\n        return *this;\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 11 \"verify/math/matrix/matrix.test.cpp\"\
    \n\nnamespace {\n\nusing mint = m1une::math::modint998244353;\nusing m1une::matrix::Matrix;\n\
    \ntemplate <class T>\nvoid assert_product_is_identity(const Matrix<T>& first,\
    \ const Matrix<T>& second) {\n    assert(first.rows() == first.cols());\n    assert(first\
    \ * second == Matrix<T>::identity(first.rows()));\n}\n\nvoid test_construction_and_arithmetic()\
    \ {\n    Matrix<long long> first(2, 3);\n    long long value = 1;\n    for (int\
    \ row = 0; row < first.rows(); row++) {\n        for (int col = 0; col < first.cols();\
    \ col++) first[row][col] = value++;\n    }\n\n    Matrix<long long> second(3,\
    \ 2);\n    second[0][0] = 7;\n    second[0][1] = 8;\n    second[1][0] = 9;\n \
    \   second[1][1] = 10;\n    second[2][0] = 11;\n    second[2][1] = 12;\n\n   \
    \ Matrix<long long> product = first * second;\n    assert(product.rows() == 2);\n\
    \    assert(product.cols() == 2);\n    assert(product[0][0] == 58);\n    assert(product[0][1]\
    \ == 64);\n    assert(product[1][0] == 139);\n    assert(product[1][1] == 154);\n\
    \n    Matrix<long long> transposed = first.transposed();\n    assert(transposed.rows()\
    \ == 3);\n    assert(transposed.cols() == 2);\n    assert(transposed[2][1] ==\
    \ 6);\n\n    Matrix<long long> sum = first + first;\n    assert(sum[1][2] == 12);\n\
    \    assert((sum - first) == first);\n    assert((first * 3LL)[1][1] == 15);\n\
    \n    std::vector<long long> column = {1, 2, 3};\n    std::vector<long long> column_product\
    \ = first * column;\n    assert(column_product == std::vector<long long>({14,\
    \ 32}));\n    std::vector<long long> row = {2, -1};\n    std::vector<long long>\
    \ row_product = row * first;\n    assert(row_product == std::vector<long long>({-2,\
    \ -1, 0}));\n\n    Matrix<long long> flat(2, 2, std::vector<long long>({1, 2,\
    \ 3, 4}));\n    assert(flat[1][0] == 3);\n    Matrix<long long> zero_inner_left(2,\
    \ 0);\n    Matrix<long long> zero_inner_right(0, 3);\n    Matrix<long long> zero_product\
    \ = zero_inner_left * zero_inner_right;\n    assert(zero_product == Matrix<long\
    \ long>(2, 3));\n}\n\nvoid test_power() {\n    Matrix<mint> fibonacci(2, 2);\n\
    \    fibonacci[0][0] = 1;\n    fibonacci[0][1] = 1;\n    fibonacci[1][0] = 1;\n\
    \    assert(fibonacci.pow(0) == Matrix<mint>::identity(2));\n    Matrix<mint>\
    \ tenth = fibonacci.pow(10);\n    assert(tenth[0][1] == mint(55));\n    assert(tenth[0][0]\
    \ == mint(89));\n}\n\nvoid test_row_reduction() {\n    Matrix<mint> matrix(3,\
    \ 4);\n    matrix[0][0] = 1;\n    matrix[0][1] = 2;\n    matrix[0][2] = 1;\n \
    \   matrix[0][3] = 4;\n    matrix[1][0] = 2;\n    matrix[1][1] = 4;\n    matrix[1][2]\
    \ = 2;\n    matrix[1][3] = 8;\n    matrix[2][1] = 1;\n    matrix[2][2] = 1;\n\
    \    matrix[2][3] = 3;\n\n    assert(m1une::matrix::matrix_rank(matrix) == 2);\n\
    \    auto reduced = m1une::matrix::reduced_row_echelon_form(matrix);\n    assert(reduced.rank()\
    \ == 2);\n    assert(reduced.pivot_columns == std::vector<int>({0, 1}));\n   \
    \ assert(reduced.matrix[0][0] == mint(1));\n    assert(reduced.matrix[0][1] ==\
    \ mint(0));\n    assert(reduced.matrix[1][0] == mint(0));\n    assert(reduced.matrix[1][1]\
    \ == mint(1));\n}\n\nvoid test_determinant_and_inverse() {\n    Matrix<mint> matrix(3,\
    \ 3);\n    matrix[0][0] = 2;\n    matrix[0][1] = 1;\n    matrix[0][2] = 3;\n \
    \   matrix[1][0] = 1;\n    matrix[1][2] = 4;\n    matrix[2][0] = 5;\n    matrix[2][1]\
    \ = 2;\n    matrix[2][2] = 1;\n    assert(m1une::matrix::determinant(matrix) ==\
    \ mint(9));\n\n    auto inv = m1une::matrix::inverse(matrix);\n    assert(inv.has_value());\n\
    \    assert_product_is_identity(matrix, *inv);\n\n    Matrix<mint> singular(2,\
    \ 2);\n    singular[0][0] = 1;\n    singular[0][1] = 2;\n    singular[1][0] =\
    \ 2;\n    singular[1][1] = 4;\n    assert(m1une::matrix::determinant(singular)\
    \ == mint(0));\n    assert(!m1une::matrix::inverse(singular).has_value());\n \
    \   assert(m1une::matrix::determinant(Matrix<mint>(0, 0)) == mint(1));\n}\n\n\
    void test_linear_systems() {\n    Matrix<mint> unique(2, 2);\n    unique[0][0]\
    \ = 2;\n    unique[0][1] = 1;\n    unique[1][0] = 1;\n    unique[1][1] = 3;\n\
    \    auto solved = m1une::matrix::solve_linear_system(unique, std::vector<mint>({5,\
    \ 7}));\n    assert(solved.consistent);\n    assert(solved.has_unique_solution());\n\
    \    assert(unique * solved.particular_solution == std::vector<mint>({5, 7}));\n\
    \n    Matrix<mint> underdetermined(2, 3);\n    underdetermined[0][0] = 1;\n  \
    \  underdetermined[0][1] = 1;\n    underdetermined[0][2] = 1;\n    underdetermined[1][0]\
    \ = 2;\n    underdetermined[1][1] = 2;\n    underdetermined[1][2] = 2;\n    auto\
    \ many =\n        m1une::matrix::solve_linear_system(underdetermined, std::vector<mint>({3,\
    \ 6}));\n    assert(many.consistent);\n    assert(many.rank() == 1);\n    assert(many.nullity()\
    \ == 2);\n    assert(underdetermined * many.particular_solution == std::vector<mint>({3,\
    \ 6}));\n    for (const auto& direction : many.nullspace_basis) {\n        assert(underdetermined\
    \ * direction == std::vector<mint>({0, 0}));\n    }\n\n    auto none =\n     \
    \   m1une::matrix::solve_linear_system(underdetermined, std::vector<mint>({3,\
    \ 7}));\n    assert(!none.consistent);\n\n    Matrix<mint> no_equations(0, 3);\n\
    \    auto unconstrained =\n        m1une::matrix::solve_linear_system(no_equations,\
    \ std::vector<mint>());\n    assert(unconstrained.consistent);\n    assert(unconstrained.rank()\
    \ == 0);\n    assert(unconstrained.nullity() == 3);\n\n    Matrix<mint> no_variables(2,\
    \ 0);\n    auto empty_solution =\n        m1une::matrix::solve_linear_system(no_variables,\
    \ std::vector<mint>({0, 0}));\n    assert(empty_solution.has_unique_solution());\n\
    \    auto impossible =\n        m1une::matrix::solve_linear_system(no_variables,\
    \ std::vector<mint>({0, 1}));\n    assert(!impossible.consistent);\n}\n\nvoid\
    \ test_floating_point() {\n    Matrix<double> matrix(2, 2);\n    matrix[0][0]\
    \ = 1e-14;\n    matrix[0][1] = 1;\n    matrix[1][0] = 1;\n    matrix[1][1] = 1;\n\
    \    assert(m1une::matrix::matrix_rank(matrix) == 2);\n    assert(std::fabs(m1une::matrix::determinant(matrix)\
    \ + 1.0) < 1e-9);\n    auto inv = m1une::matrix::inverse(matrix);\n    assert(inv.has_value());\n\
    \    Matrix<double> product = matrix * *inv;\n    for (int row = 0; row < 2; row++)\
    \ {\n        for (int col = 0; col < 2; col++) {\n            const double expected\
    \ = row == col ? 1.0 : 0.0;\n            assert(std::fabs(product[row][col] -\
    \ expected) < 1e-9);\n        }\n    }\n}\n\nvoid test_randomized_exact() {\n\
    \    std::uint64_t state = 0x81a5b4c3d2e1f097ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 500; trial++) {\n        const\
    \ int size = 1 + int(random() % 6);\n        Matrix<mint> lower = Matrix<mint>::identity(size);\n\
    \        Matrix<mint> upper = Matrix<mint>::identity(size);\n        for (int\
    \ row = 0; row < size; row++) {\n            lower[row][row] = mint(1 + int(random()\
    \ % 100));\n            upper[row][row] = mint(1 + int(random() % 100));\n   \
    \         for (int col = 0; col < row; col++) {\n                lower[row][col]\
    \ = mint(int(random() % 21) - 10);\n            }\n            for (int col =\
    \ row + 1; col < size; col++) {\n                upper[row][col] = mint(int(random()\
    \ % 21) - 10);\n            }\n        }\n        Matrix<mint> matrix = lower\
    \ * upper;\n        auto inv = m1une::matrix::inverse(matrix);\n        assert(inv.has_value());\n\
    \        assert_product_is_identity(matrix, *inv);\n        assert(m1une::matrix::matrix_rank(matrix)\
    \ == size);\n        mint expected_determinant = 1;\n        for (int i = 0; i\
    \ < size; i++) {\n            expected_determinant *= lower[i][i] * upper[i][i];\n\
    \        }\n        assert(m1une::matrix::determinant(matrix) == expected_determinant);\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_construction_and_arithmetic();\n\
    \    test_power();\n    test_row_reduction();\n    test_determinant_and_inverse();\n\
    \    test_linear_systems();\n    test_floating_point();\n    test_randomized_exact();\n\
    \n    int size;\n    std::uint64_t exponent;\n    fast_input >> size >> exponent;\n\
    \    Matrix<mint> matrix(size, size);\n    for (int row = 0; row < size; row++)\
    \ {\n        for (int column = 0; column < size; column++) {\n            fast_input\
    \ >> matrix[row][column];\n        }\n    }\n\n    Matrix<mint> result = matrix.pow(exponent);\n\
    \    for (int row = 0; row < size; row++) {\n        for (int column = 0; column\
    \ < size; column++) {\n            if (column != 0) fast_output << ' ';\n    \
    \        fast_output << result[row][column];\n        }\n        fast_output <<\
    \ '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/pow_of_matrix\"\n\n#include\
    \ \"../../../math/modint.hpp\"\n#include \"../../../math/matrix/all.hpp\"\n\n\
    #include <cassert>\n#include <cmath>\n#include <cstdint>\n#include \"../../../utilities/fast_io.hpp\"\
    \n#include <vector>\n\nnamespace {\n\nusing mint = m1une::math::modint998244353;\n\
    using m1une::matrix::Matrix;\n\ntemplate <class T>\nvoid assert_product_is_identity(const\
    \ Matrix<T>& first, const Matrix<T>& second) {\n    assert(first.rows() == first.cols());\n\
    \    assert(first * second == Matrix<T>::identity(first.rows()));\n}\n\nvoid test_construction_and_arithmetic()\
    \ {\n    Matrix<long long> first(2, 3);\n    long long value = 1;\n    for (int\
    \ row = 0; row < first.rows(); row++) {\n        for (int col = 0; col < first.cols();\
    \ col++) first[row][col] = value++;\n    }\n\n    Matrix<long long> second(3,\
    \ 2);\n    second[0][0] = 7;\n    second[0][1] = 8;\n    second[1][0] = 9;\n \
    \   second[1][1] = 10;\n    second[2][0] = 11;\n    second[2][1] = 12;\n\n   \
    \ Matrix<long long> product = first * second;\n    assert(product.rows() == 2);\n\
    \    assert(product.cols() == 2);\n    assert(product[0][0] == 58);\n    assert(product[0][1]\
    \ == 64);\n    assert(product[1][0] == 139);\n    assert(product[1][1] == 154);\n\
    \n    Matrix<long long> transposed = first.transposed();\n    assert(transposed.rows()\
    \ == 3);\n    assert(transposed.cols() == 2);\n    assert(transposed[2][1] ==\
    \ 6);\n\n    Matrix<long long> sum = first + first;\n    assert(sum[1][2] == 12);\n\
    \    assert((sum - first) == first);\n    assert((first * 3LL)[1][1] == 15);\n\
    \n    std::vector<long long> column = {1, 2, 3};\n    std::vector<long long> column_product\
    \ = first * column;\n    assert(column_product == std::vector<long long>({14,\
    \ 32}));\n    std::vector<long long> row = {2, -1};\n    std::vector<long long>\
    \ row_product = row * first;\n    assert(row_product == std::vector<long long>({-2,\
    \ -1, 0}));\n\n    Matrix<long long> flat(2, 2, std::vector<long long>({1, 2,\
    \ 3, 4}));\n    assert(flat[1][0] == 3);\n    Matrix<long long> zero_inner_left(2,\
    \ 0);\n    Matrix<long long> zero_inner_right(0, 3);\n    Matrix<long long> zero_product\
    \ = zero_inner_left * zero_inner_right;\n    assert(zero_product == Matrix<long\
    \ long>(2, 3));\n}\n\nvoid test_power() {\n    Matrix<mint> fibonacci(2, 2);\n\
    \    fibonacci[0][0] = 1;\n    fibonacci[0][1] = 1;\n    fibonacci[1][0] = 1;\n\
    \    assert(fibonacci.pow(0) == Matrix<mint>::identity(2));\n    Matrix<mint>\
    \ tenth = fibonacci.pow(10);\n    assert(tenth[0][1] == mint(55));\n    assert(tenth[0][0]\
    \ == mint(89));\n}\n\nvoid test_row_reduction() {\n    Matrix<mint> matrix(3,\
    \ 4);\n    matrix[0][0] = 1;\n    matrix[0][1] = 2;\n    matrix[0][2] = 1;\n \
    \   matrix[0][3] = 4;\n    matrix[1][0] = 2;\n    matrix[1][1] = 4;\n    matrix[1][2]\
    \ = 2;\n    matrix[1][3] = 8;\n    matrix[2][1] = 1;\n    matrix[2][2] = 1;\n\
    \    matrix[2][3] = 3;\n\n    assert(m1une::matrix::matrix_rank(matrix) == 2);\n\
    \    auto reduced = m1une::matrix::reduced_row_echelon_form(matrix);\n    assert(reduced.rank()\
    \ == 2);\n    assert(reduced.pivot_columns == std::vector<int>({0, 1}));\n   \
    \ assert(reduced.matrix[0][0] == mint(1));\n    assert(reduced.matrix[0][1] ==\
    \ mint(0));\n    assert(reduced.matrix[1][0] == mint(0));\n    assert(reduced.matrix[1][1]\
    \ == mint(1));\n}\n\nvoid test_determinant_and_inverse() {\n    Matrix<mint> matrix(3,\
    \ 3);\n    matrix[0][0] = 2;\n    matrix[0][1] = 1;\n    matrix[0][2] = 3;\n \
    \   matrix[1][0] = 1;\n    matrix[1][2] = 4;\n    matrix[2][0] = 5;\n    matrix[2][1]\
    \ = 2;\n    matrix[2][2] = 1;\n    assert(m1une::matrix::determinant(matrix) ==\
    \ mint(9));\n\n    auto inv = m1une::matrix::inverse(matrix);\n    assert(inv.has_value());\n\
    \    assert_product_is_identity(matrix, *inv);\n\n    Matrix<mint> singular(2,\
    \ 2);\n    singular[0][0] = 1;\n    singular[0][1] = 2;\n    singular[1][0] =\
    \ 2;\n    singular[1][1] = 4;\n    assert(m1une::matrix::determinant(singular)\
    \ == mint(0));\n    assert(!m1une::matrix::inverse(singular).has_value());\n \
    \   assert(m1une::matrix::determinant(Matrix<mint>(0, 0)) == mint(1));\n}\n\n\
    void test_linear_systems() {\n    Matrix<mint> unique(2, 2);\n    unique[0][0]\
    \ = 2;\n    unique[0][1] = 1;\n    unique[1][0] = 1;\n    unique[1][1] = 3;\n\
    \    auto solved = m1une::matrix::solve_linear_system(unique, std::vector<mint>({5,\
    \ 7}));\n    assert(solved.consistent);\n    assert(solved.has_unique_solution());\n\
    \    assert(unique * solved.particular_solution == std::vector<mint>({5, 7}));\n\
    \n    Matrix<mint> underdetermined(2, 3);\n    underdetermined[0][0] = 1;\n  \
    \  underdetermined[0][1] = 1;\n    underdetermined[0][2] = 1;\n    underdetermined[1][0]\
    \ = 2;\n    underdetermined[1][1] = 2;\n    underdetermined[1][2] = 2;\n    auto\
    \ many =\n        m1une::matrix::solve_linear_system(underdetermined, std::vector<mint>({3,\
    \ 6}));\n    assert(many.consistent);\n    assert(many.rank() == 1);\n    assert(many.nullity()\
    \ == 2);\n    assert(underdetermined * many.particular_solution == std::vector<mint>({3,\
    \ 6}));\n    for (const auto& direction : many.nullspace_basis) {\n        assert(underdetermined\
    \ * direction == std::vector<mint>({0, 0}));\n    }\n\n    auto none =\n     \
    \   m1une::matrix::solve_linear_system(underdetermined, std::vector<mint>({3,\
    \ 7}));\n    assert(!none.consistent);\n\n    Matrix<mint> no_equations(0, 3);\n\
    \    auto unconstrained =\n        m1une::matrix::solve_linear_system(no_equations,\
    \ std::vector<mint>());\n    assert(unconstrained.consistent);\n    assert(unconstrained.rank()\
    \ == 0);\n    assert(unconstrained.nullity() == 3);\n\n    Matrix<mint> no_variables(2,\
    \ 0);\n    auto empty_solution =\n        m1une::matrix::solve_linear_system(no_variables,\
    \ std::vector<mint>({0, 0}));\n    assert(empty_solution.has_unique_solution());\n\
    \    auto impossible =\n        m1une::matrix::solve_linear_system(no_variables,\
    \ std::vector<mint>({0, 1}));\n    assert(!impossible.consistent);\n}\n\nvoid\
    \ test_floating_point() {\n    Matrix<double> matrix(2, 2);\n    matrix[0][0]\
    \ = 1e-14;\n    matrix[0][1] = 1;\n    matrix[1][0] = 1;\n    matrix[1][1] = 1;\n\
    \    assert(m1une::matrix::matrix_rank(matrix) == 2);\n    assert(std::fabs(m1une::matrix::determinant(matrix)\
    \ + 1.0) < 1e-9);\n    auto inv = m1une::matrix::inverse(matrix);\n    assert(inv.has_value());\n\
    \    Matrix<double> product = matrix * *inv;\n    for (int row = 0; row < 2; row++)\
    \ {\n        for (int col = 0; col < 2; col++) {\n            const double expected\
    \ = row == col ? 1.0 : 0.0;\n            assert(std::fabs(product[row][col] -\
    \ expected) < 1e-9);\n        }\n    }\n}\n\nvoid test_randomized_exact() {\n\
    \    std::uint64_t state = 0x81a5b4c3d2e1f097ULL;\n    auto random = [&state]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 500; trial++) {\n        const\
    \ int size = 1 + int(random() % 6);\n        Matrix<mint> lower = Matrix<mint>::identity(size);\n\
    \        Matrix<mint> upper = Matrix<mint>::identity(size);\n        for (int\
    \ row = 0; row < size; row++) {\n            lower[row][row] = mint(1 + int(random()\
    \ % 100));\n            upper[row][row] = mint(1 + int(random() % 100));\n   \
    \         for (int col = 0; col < row; col++) {\n                lower[row][col]\
    \ = mint(int(random() % 21) - 10);\n            }\n            for (int col =\
    \ row + 1; col < size; col++) {\n                upper[row][col] = mint(int(random()\
    \ % 21) - 10);\n            }\n        }\n        Matrix<mint> matrix = lower\
    \ * upper;\n        auto inv = m1une::matrix::inverse(matrix);\n        assert(inv.has_value());\n\
    \        assert_product_is_identity(matrix, *inv);\n        assert(m1une::matrix::matrix_rank(matrix)\
    \ == size);\n        mint expected_determinant = 1;\n        for (int i = 0; i\
    \ < size; i++) {\n            expected_determinant *= lower[i][i] * upper[i][i];\n\
    \        }\n        assert(m1une::matrix::determinant(matrix) == expected_determinant);\n\
    \    }\n}\n\n}  // namespace\n\nint main() {\n    m1une::utilities::FastInput\
    \ fast_input;\n    m1une::utilities::FastOutput fast_output;\n\n    test_construction_and_arithmetic();\n\
    \    test_power();\n    test_row_reduction();\n    test_determinant_and_inverse();\n\
    \    test_linear_systems();\n    test_floating_point();\n    test_randomized_exact();\n\
    \n    int size;\n    std::uint64_t exponent;\n    fast_input >> size >> exponent;\n\
    \    Matrix<mint> matrix(size, size);\n    for (int row = 0; row < size; row++)\
    \ {\n        for (int column = 0; column < size; column++) {\n            fast_input\
    \ >> matrix[row][column];\n        }\n    }\n\n    Matrix<mint> result = matrix.pow(exponent);\n\
    \    for (int row = 0; row < size; row++) {\n        for (int column = 0; column\
    \ < size; column++) {\n            if (column != 0) fast_output << ' ';\n    \
    \        fast_output << result[row][column];\n        }\n        fast_output <<\
    \ '\\n';\n    }\n}\n"
  dependsOn:
  - math/modint.hpp
  - math/matrix/all.hpp
  - math/matrix/adjugate.hpp
  - math/matrix/matrix.hpp
  - math/matrix/bit_matrix.hpp
  - math/matrix/characteristic_polynomial.hpp
  - math/matrix/determinant_mod.hpp
  - math/matrix/hafnian.hpp
  - math/matrix/linear_algebra.hpp
  - math/matrix/pfaffian.hpp
  - math/matrix/sparse_determinant.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/math/matrix/matrix.test.cpp
  requiredBy: []
  timestamp: '2026-07-21 21:50:16+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/math/matrix/matrix.test.cpp
layout: document
redirect_from:
- /verify/verify/math/matrix/matrix.test.cpp
- /verify/verify/math/matrix/matrix.test.cpp.html
title: verify/math/matrix/matrix.test.cpp
---
