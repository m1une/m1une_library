---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/matrix_tree_theorem.hpp
    title: Matrix-Tree Theorem
  - icon: ':heavy_check_mark:'
    path: math/matrix/linear_algebra.hpp
    title: Matrix Linear Algebra
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
    PROBLEM: https://judge.yosupo.jp/problem/counting_spanning_tree_directed
    links:
    - https://judge.yosupo.jp/problem/counting_spanning_tree_directed
  bundledCode: "#line 1 \"verify/graph/counting_spanning_tree_directed.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/counting_spanning_tree_directed\"\
    \n\n#line 1 \"graph/matrix_tree_theorem.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <utility>\n#include <vector>\n\n#line 1 \"math/matrix/linear_algebra.hpp\"\n\
    \n\n\n#include <optional>\n#include <type_traits>\n#line 7 \"math/matrix/linear_algebra.hpp\"\
    \n\n#line 1 \"math/matrix/matrix.hpp\"\n\n\n\n#line 5 \"math/matrix/matrix.hpp\"\
    \n#include <cstddef>\n#include <cstdint>\n#line 9 \"math/matrix/matrix.hpp\"\n\
    \nnamespace m1une {\nnamespace matrix {\n\ntemplate <class T>\nclass Matrix {\n\
    \   private:\n    int _rows;\n    int _cols;\n    std::vector<T> _data;\n\n  \
    \  static std::size_t storage_size(int rows, int cols) {\n        assert(rows\
    \ >= 0);\n        assert(cols >= 0);\n        return std::size_t(rows) * std::size_t(cols);\n\
    \    }\n\n   public:\n    using value_type = T;\n\n    Matrix() : _rows(0), _cols(0)\
    \ {}\n\n    Matrix(int rows, int cols, const T& value = T())\n        : _rows(rows),\
    \ _cols(cols), _data(storage_size(rows, cols), value) {}\n\n    Matrix(int rows,\
    \ int cols, std::vector<T> values)\n        : _rows(rows), _cols(cols), _data(std::move(values))\
    \ {\n        assert(rows >= 0);\n        assert(cols >= 0);\n        assert(_data.size()\
    \ == std::size_t(rows) * std::size_t(cols));\n    }\n\n    explicit Matrix(const\
    \ std::vector<std::vector<T>>& values)\n        : _rows(int(values.size())), _cols(values.empty()\
    \ ? 0 : int(values[0].size())),\n          _data(storage_size(_rows, _cols)) {\n\
    \        for (int row = 0; row < _rows; row++) {\n            assert(int(values[std::size_t(row)].size())\
    \ == _cols);\n            for (int col = 0; col < _cols; col++) {\n          \
    \      (*this)[row][col] = values[std::size_t(row)][std::size_t(col)];\n     \
    \       }\n        }\n    }\n\n    int rows() const {\n        return _rows;\n\
    \    }\n\n    int cols() const {\n        return _cols;\n    }\n\n    bool empty()\
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
    \n}  // namespace matrix\n}  // namespace m1une\n\n\n#line 9 \"math/matrix/linear_algebra.hpp\"\
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
    #line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une\
    \ {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using cost_type\
    \ = T;\n\n    int from;\n    int to;\n    T cost;\n    int id;\n    bool alive;\n\
    \n    Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int\
    \ from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ = true)\n        :\
    \ from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}\n\n    int other(int\
    \ v) const {\n        assert(v == from || v == to);\n        return from ^ to\
    \ ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct Graph {\n    using edge_type\
    \ = Edge<T>;\n    using cost_type = T;\n\n   private:\n    int _n;\n    int _edge_count;\n\
    \    std::vector<std::vector<edge_type>> _g;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> _edge_positions;\n\n   public:\n    Graph() : _n(0), _edge_count(0) {}\n\
    \    explicit Graph(int n) : _n(n), _edge_count(0), _g(n) {\n        assert(0\
    \ <= n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    int edge_count() const\
    \ {\n        return _edge_count;\n    }\n\n    int add_vertex() {\n        _g.emplace_back();\n\
    \        return _n++;\n    }\n\n    int add_directed_edge(int from, int to, T\
    \ cost = T(1)) {\n        assert(0 <= from && from < _n);\n        assert(0 <=\
    \ to && to < _n);\n        int id = _edge_count++;\n        int idx = int(_g[from].size());\n\
    \        _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({from, idx});\n        return id;\n\
    \    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0 <=\
    \ u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        _g[u].push_back(edge_type(u,\
    \ v, cost, id));\n        int v_idx = int(_g[v].size());\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({u,\
    \ u_idx});\n        _edge_positions.back().push_back({v, v_idx});\n        return\
    \ id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0\
    \ <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
    \ {\n            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n\
    \        auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
    \    }\n\n    const std::vector<edge_type>& operator[](int v) const {\n      \
    \  assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool include_inactive\
    \ = false) const {\n        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (!include_inactive && !e.alive) continue;\n                if (0 <= e.id &&\
    \ e.id < _edge_count) {\n                    if (used[e.id]) continue;\n     \
    \               used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        result._edge_positions.assign(_edge_count, {});\n        for (int v =\
    \ 0; v < _n; v++) {\n            for (const auto& e : _g[v]) {\n             \
    \   int idx = int(result._g[e.to].size());\n                result._g[e.to].push_back(edge_type(e.to,\
    \ e.from, e.cost, e.id, e.alive));\n                if (0 <= e.id && e.id < _edge_count)\
    \ result._edge_positions[e.id].push_back({e.to, idx});\n            }\n      \
    \  }\n        return result;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 10 \"graph/matrix_tree_theorem.hpp\"\n\nnamespace m1une {\n\
    namespace graph {\n\nnamespace matrix_tree_detail {\n\ninline int minor_index(int\
    \ vertex, int removed) {\n    assert(vertex != removed);\n    return vertex <\
    \ removed ? vertex : vertex - 1;\n}\n\ntemplate <class Weight>\nvoid assert_edge_incidence(const\
    \ Graph<Weight>& graph, int expected) {\n#ifndef NDEBUG\n    std::vector<int>\
    \ incidence(graph.edge_count(), 0);\n    for (int vertex = 0; vertex < graph.size();\
    \ vertex++) {\n        for (const Edge<Weight>& edge : graph[vertex]) {\n    \
    \        if (!edge.alive) continue;\n            assert(0 <= edge.id && edge.id\
    \ < graph.edge_count());\n            incidence[edge.id]++;\n        }\n    }\n\
    \    for (int count : incidence) {\n        if (count != 0) assert(count == expected);\n\
    \    }\n#else\n    (void)graph;\n    (void)expected;\n#endif\n}\n\ntemplate <class\
    \ Field, class Weight>\nField count_arborescences(\n    const Graph<Weight>& graph,\n\
    \    int root,\n    bool outward\n) {\n    const int n = graph.size();\n    assert(0\
    \ <= root && root < n);\n    assert_edge_incidence(graph, 1);\n\n    matrix::Matrix<Field>\
    \ minor(n - 1, n - 1);\n    for (int vertex = 0; vertex < n; vertex++) {\n   \
    \     for (const Edge<Weight>& edge : graph[vertex]) {\n            if (!edge.alive\
    \ || edge.from == edge.to) continue;\n            const int row = outward ? edge.to\
    \ : edge.from;\n            const int col = outward ? edge.from : edge.to;\n \
    \           if (row == root) continue;\n\n            const Field weight(edge.cost);\n\
    \            const int reduced_row = minor_index(row, root);\n            minor[reduced_row][reduced_row]\
    \ += weight;\n            if (col != root) {\n                minor[reduced_row][minor_index(col,\
    \ root)] -= weight;\n            }\n        }\n    }\n    return matrix::determinant(std::move(minor));\n\
    }\n\n}  // namespace matrix_tree_detail\n\n// Returns the total weight of all\
    \ undirected spanning trees. The weight of a\n// tree is the product of its edge\
    \ costs.\ntemplate <class Field, class Weight>\nField count_spanning_trees(const\
    \ Graph<Weight>& graph) {\n    const int n = graph.size();\n    assert(n > 0);\n\
    \    matrix_tree_detail::assert_edge_incidence(graph, 2);\n\n    const int removed\
    \ = n - 1;\n    matrix::Matrix<Field> minor(n - 1, n - 1);\n    for (int vertex\
    \ = 0; vertex < n; vertex++) {\n        for (const Edge<Weight>& edge : graph[vertex])\
    \ {\n            if (!edge.alive || edge.from >= edge.to) continue;\n        \
    \    const int from = edge.from;\n            const int to = edge.to;\n      \
    \      const Field weight(edge.cost);\n\n            if (from != removed) {\n\
    \                const int reduced_from = matrix_tree_detail::minor_index(from,\
    \ removed);\n                minor[reduced_from][reduced_from] += weight;\n  \
    \          }\n            if (to != removed) {\n                const int reduced_to\
    \ = matrix_tree_detail::minor_index(to, removed);\n                minor[reduced_to][reduced_to]\
    \ += weight;\n            }\n            if (from != removed && to != removed)\
    \ {\n                const int reduced_from = matrix_tree_detail::minor_index(from,\
    \ removed);\n                const int reduced_to = matrix_tree_detail::minor_index(to,\
    \ removed);\n                minor[reduced_from][reduced_to] -= weight;\n    \
    \            minor[reduced_to][reduced_from] -= weight;\n            }\n     \
    \   }\n    }\n    return matrix::determinant(std::move(minor));\n}\n\n// Counts\
    \ directed spanning trees whose edges point away from root, so every\n// vertex\
    \ is reachable from root.\ntemplate <class Field, class Weight>\nField count_out_arborescences(const\
    \ Graph<Weight>& graph, int root) {\n    return matrix_tree_detail::count_arborescences<Field>(graph,\
    \ root, true);\n}\n\n// Counts directed spanning trees whose edges point toward\
    \ root, so root is\n// reachable from every vertex.\ntemplate <class Field, class\
    \ Weight>\nField count_in_arborescences(const Graph<Weight>& graph, int root)\
    \ {\n    return matrix_tree_detail::count_arborescences<Field>(graph, root, false);\n\
    }\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 1 \"math/modint.hpp\"\
    \n\n\n\n#line 6 \"math/modint.hpp\"\n#include <iostream>\n#line 9 \"math/modint.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\ntemplate <uint32_t Modulus>\nstruct\
    \ ModInt {\n    static_assert(0 < Modulus, \"Modulus must be positive\");\n\n\
    \   private:\n    uint32_t _v;\n\n   public:\n    static constexpr uint32_t mod()\
    \ {\n        return Modulus;\n    }\n\n    static constexpr ModInt raw(uint32_t\
    \ v) noexcept {\n        ModInt x;\n        x._v = v;\n        return x;\n   \
    \ }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    template <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    constexpr ModInt(Integer\
    \ v) noexcept {\n        if constexpr (std::is_signed_v<Integer>) {\n        \
    \    int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(Modulus);\n  \
    \          if (x < 0) x += Modulus;\n            _v = static_cast<uint32_t>(x);\n\
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
    \n\n#line 5 \"verify/graph/counting_spanning_tree_directed.test.cpp\"\n\n#include\
    \ <bit>\n#line 9 \"verify/graph/counting_spanning_tree_directed.test.cpp\"\n#include\
    \ <random>\n#line 11 \"verify/graph/counting_spanning_tree_directed.test.cpp\"\
    \n\nusing mint = m1une::math::modint998244353;\n\nbool all_reachable(\n    int\
    \ n,\n    int root,\n    const std::vector<std::vector<int>>& adjacency\n) {\n\
    \    std::vector<char> visited(n, false);\n    std::vector<int> stack;\n    stack.push_back(root);\n\
    \    visited[root] = true;\n    while (!stack.empty()) {\n        int vertex =\
    \ stack.back();\n        stack.pop_back();\n        for (int to : adjacency[vertex])\
    \ {\n            if (visited[to]) continue;\n            visited[to] = true;\n\
    \            stack.push_back(to);\n        }\n    }\n    for (char value : visited)\
    \ {\n        if (!value) return false;\n    }\n    return true;\n}\n\nmint naive_count(\n\
    \    const m1une::graph::Graph<int>& graph,\n    int root,\n    bool outward\n\
    ) {\n    const int n = graph.size();\n    const std::vector<m1une::graph::Edge<int>>\
    \ edges = graph.edges();\n    mint answer = 0;\n    for (unsigned mask = 0; mask\
    \ < (1U << edges.size()); mask++) {\n        if (std::popcount(mask) != n - 1)\
    \ continue;\n        std::vector<int> constrained_degree(n, 0);\n        std::vector<std::vector<int>>\
    \ adjacency(n);\n        mint weight = 1;\n        for (int edge_id = 0; edge_id\
    \ < int(edges.size()); edge_id++) {\n            if (((mask >> edge_id) & 1U)\
    \ == 0) continue;\n            const auto& edge = edges[edge_id];\n          \
    \  constrained_degree[outward ? edge.to : edge.from]++;\n            int from\
    \ = outward ? edge.from : edge.to;\n            int to = outward ? edge.to : edge.from;\n\
    \            adjacency[from].push_back(to);\n            weight *= mint(edge.cost);\n\
    \        }\n\n        bool valid_degree = constrained_degree[root] == 0;\n   \
    \     for (int vertex = 0; vertex < n; vertex++) {\n            if (vertex !=\
    \ root) valid_degree = valid_degree && constrained_degree[vertex] == 1;\n    \
    \    }\n        if (valid_degree && all_reachable(n, root, adjacency)) answer\
    \ += weight;\n    }\n    return answer;\n}\n\nvoid run_focused_tests() {\n   \
    \ std::mt19937 random(987654321);\n    for (int test = 0; test < 200; test++)\
    \ {\n        int n = 1 + int(random() % 5);\n        int edge_count = int(random()\
    \ % 9);\n        int root = int(random() % unsigned(n));\n        m1une::graph::Graph<int>\
    \ graph(n);\n        for (int edge = 0; edge < edge_count; edge++) {\n       \
    \     int from = int(random() % unsigned(n));\n            int to = int(random()\
    \ % unsigned(n));\n            int weight = int(random() % 5);\n            graph.add_directed_edge(from,\
    \ to, weight);\n        }\n        assert(\n            m1une::graph::count_out_arborescences<mint>(graph,\
    \ root) ==\n            naive_count(graph, root, true)\n        );\n        assert(\n\
    \            m1une::graph::count_in_arborescences<mint>(graph, root) ==\n    \
    \        naive_count(graph, root, false)\n        );\n    }\n}\n\nint main() {\n\
    \    run_focused_tests();\n\n    int vertex_count, edge_count, root;\n    std::cin\
    \ >> vertex_count >> edge_count >> root;\n    m1une::graph::Graph<int> graph(vertex_count);\n\
    \    for (int edge = 0; edge < edge_count; edge++) {\n        int from, to;\n\
    \        std::cin >> from >> to;\n        graph.add_directed_edge(from, to);\n\
    \    }\n    std::cout << m1une::graph::count_out_arborescences<mint>(graph, root)\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/counting_spanning_tree_directed\"\
    \n\n#include \"../../graph/matrix_tree_theorem.hpp\"\n#include \"../../math/modint.hpp\"\
    \n\n#include <bit>\n#include <cassert>\n#include <iostream>\n#include <random>\n\
    #include <vector>\n\nusing mint = m1une::math::modint998244353;\n\nbool all_reachable(\n\
    \    int n,\n    int root,\n    const std::vector<std::vector<int>>& adjacency\n\
    ) {\n    std::vector<char> visited(n, false);\n    std::vector<int> stack;\n \
    \   stack.push_back(root);\n    visited[root] = true;\n    while (!stack.empty())\
    \ {\n        int vertex = stack.back();\n        stack.pop_back();\n        for\
    \ (int to : adjacency[vertex]) {\n            if (visited[to]) continue;\n   \
    \         visited[to] = true;\n            stack.push_back(to);\n        }\n \
    \   }\n    for (char value : visited) {\n        if (!value) return false;\n \
    \   }\n    return true;\n}\n\nmint naive_count(\n    const m1une::graph::Graph<int>&\
    \ graph,\n    int root,\n    bool outward\n) {\n    const int n = graph.size();\n\
    \    const std::vector<m1une::graph::Edge<int>> edges = graph.edges();\n    mint\
    \ answer = 0;\n    for (unsigned mask = 0; mask < (1U << edges.size()); mask++)\
    \ {\n        if (std::popcount(mask) != n - 1) continue;\n        std::vector<int>\
    \ constrained_degree(n, 0);\n        std::vector<std::vector<int>> adjacency(n);\n\
    \        mint weight = 1;\n        for (int edge_id = 0; edge_id < int(edges.size());\
    \ edge_id++) {\n            if (((mask >> edge_id) & 1U) == 0) continue;\n   \
    \         const auto& edge = edges[edge_id];\n            constrained_degree[outward\
    \ ? edge.to : edge.from]++;\n            int from = outward ? edge.from : edge.to;\n\
    \            int to = outward ? edge.to : edge.from;\n            adjacency[from].push_back(to);\n\
    \            weight *= mint(edge.cost);\n        }\n\n        bool valid_degree\
    \ = constrained_degree[root] == 0;\n        for (int vertex = 0; vertex < n; vertex++)\
    \ {\n            if (vertex != root) valid_degree = valid_degree && constrained_degree[vertex]\
    \ == 1;\n        }\n        if (valid_degree && all_reachable(n, root, adjacency))\
    \ answer += weight;\n    }\n    return answer;\n}\n\nvoid run_focused_tests()\
    \ {\n    std::mt19937 random(987654321);\n    for (int test = 0; test < 200; test++)\
    \ {\n        int n = 1 + int(random() % 5);\n        int edge_count = int(random()\
    \ % 9);\n        int root = int(random() % unsigned(n));\n        m1une::graph::Graph<int>\
    \ graph(n);\n        for (int edge = 0; edge < edge_count; edge++) {\n       \
    \     int from = int(random() % unsigned(n));\n            int to = int(random()\
    \ % unsigned(n));\n            int weight = int(random() % 5);\n            graph.add_directed_edge(from,\
    \ to, weight);\n        }\n        assert(\n            m1une::graph::count_out_arborescences<mint>(graph,\
    \ root) ==\n            naive_count(graph, root, true)\n        );\n        assert(\n\
    \            m1une::graph::count_in_arborescences<mint>(graph, root) ==\n    \
    \        naive_count(graph, root, false)\n        );\n    }\n}\n\nint main() {\n\
    \    run_focused_tests();\n\n    int vertex_count, edge_count, root;\n    std::cin\
    \ >> vertex_count >> edge_count >> root;\n    m1une::graph::Graph<int> graph(vertex_count);\n\
    \    for (int edge = 0; edge < edge_count; edge++) {\n        int from, to;\n\
    \        std::cin >> from >> to;\n        graph.add_directed_edge(from, to);\n\
    \    }\n    std::cout << m1une::graph::count_out_arborescences<mint>(graph, root)\
    \ << '\\n';\n}\n"
  dependsOn:
  - graph/matrix_tree_theorem.hpp
  - math/matrix/linear_algebra.hpp
  - math/matrix/matrix.hpp
  - graph/graph.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/graph/counting_spanning_tree_directed.test.cpp
  requiredBy: []
  timestamp: '2026-07-14 04:31:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/counting_spanning_tree_directed.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/counting_spanning_tree_directed.test.cpp
- /verify/verify/graph/counting_spanning_tree_directed.test.cpp.html
title: verify/graph/counting_spanning_tree_directed.test.cpp
---
