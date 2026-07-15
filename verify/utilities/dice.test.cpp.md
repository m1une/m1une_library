---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/dice.hpp
    title: Dice
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ITP1_11_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ITP1_11_A
  bundledCode: "#line 1 \"verify/utilities/dice.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ITP1_11_A\"\
    \n\n#line 1 \"utilities/dice.hpp\"\n\n\n\n#include <array>\n#include <cstddef>\n\
    #include <optional>\n#include <stdexcept>\n#include <string>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace utilities {\n\nenum class DiceFace\
    \ : std::size_t {\n    top,\n    bottom,\n    north,\n    south,\n    east,\n\
    \    west\n};\n\nenum class DiceDirection {\n    north,\n    south,\n    east,\n\
    \    west\n};\n\nconstexpr DiceFace opposite(DiceFace face) noexcept {\n    switch\
    \ (face) {\n        case DiceFace::top:\n            return DiceFace::bottom;\n\
    \        case DiceFace::bottom:\n            return DiceFace::top;\n        case\
    \ DiceFace::north:\n            return DiceFace::south;\n        case DiceFace::south:\n\
    \            return DiceFace::north;\n        case DiceFace::east:\n         \
    \   return DiceFace::west;\n        case DiceFace::west:\n            return DiceFace::east;\n\
    \    }\n    return DiceFace::top;\n}\n\nconstexpr DiceFace rotate_direction(\n\
    \    DiceFace direction,\n    DiceDirection rotation\n) noexcept {\n    switch\
    \ (rotation) {\n        case DiceDirection::north:\n            switch (direction)\
    \ {\n                case DiceFace::top:\n                    return DiceFace::north;\n\
    \                case DiceFace::north:\n                    return DiceFace::bottom;\n\
    \                case DiceFace::bottom:\n                    return DiceFace::south;\n\
    \                case DiceFace::south:\n                    return DiceFace::top;\n\
    \                default:\n                    return direction;\n           \
    \ }\n        case DiceDirection::south:\n            switch (direction) {\n  \
    \              case DiceFace::top:\n                    return DiceFace::south;\n\
    \                case DiceFace::south:\n                    return DiceFace::bottom;\n\
    \                case DiceFace::bottom:\n                    return DiceFace::north;\n\
    \                case DiceFace::north:\n                    return DiceFace::top;\n\
    \                default:\n                    return direction;\n           \
    \ }\n        case DiceDirection::east:\n            switch (direction) {\n   \
    \             case DiceFace::top:\n                    return DiceFace::east;\n\
    \                case DiceFace::east:\n                    return DiceFace::bottom;\n\
    \                case DiceFace::bottom:\n                    return DiceFace::west;\n\
    \                case DiceFace::west:\n                    return DiceFace::top;\n\
    \                default:\n                    return direction;\n           \
    \ }\n        case DiceDirection::west:\n            switch (direction) {\n   \
    \             case DiceFace::top:\n                    return DiceFace::west;\n\
    \                case DiceFace::west:\n                    return DiceFace::bottom;\n\
    \                case DiceFace::bottom:\n                    return DiceFace::east;\n\
    \                case DiceFace::east:\n                    return DiceFace::top;\n\
    \                default:\n                    return direction;\n           \
    \ }\n    }\n    return direction;\n}\n\nconstexpr DiceFace rotate_direction_clockwise(DiceFace\
    \ direction) noexcept {\n    switch (direction) {\n        case DiceFace::north:\n\
    \            return DiceFace::east;\n        case DiceFace::east:\n          \
    \  return DiceFace::south;\n        case DiceFace::south:\n            return\
    \ DiceFace::west;\n        case DiceFace::west:\n            return DiceFace::north;\n\
    \        default:\n            return direction;\n    }\n}\n\nconstexpr DiceFace\
    \ rotate_direction_counterclockwise(DiceFace direction) noexcept {\n    switch\
    \ (direction) {\n        case DiceFace::north:\n            return DiceFace::west;\n\
    \        case DiceFace::west:\n            return DiceFace::south;\n        case\
    \ DiceFace::south:\n            return DiceFace::east;\n        case DiceFace::east:\n\
    \            return DiceFace::north;\n        default:\n            return direction;\n\
    \    }\n}\n\ntemplate <typename T>\nclass Dice {\nprivate:\n    static constexpr\
    \ std::size_t face_count = 6;\n    std::array<T, face_count> faces_;\n\n    static\
    \ constexpr std::size_t index(DiceFace face) noexcept {\n        return static_cast<std::size_t>(face);\n\
    \    }\n\npublic:\n    constexpr Dice(\n        T top,\n        T bottom,\n  \
    \      T north,\n        T south,\n        T east,\n        T west\n    )\n  \
    \      : faces_{\n              std::move(top),\n              std::move(bottom),\n\
    \              std::move(north),\n              std::move(south),\n          \
    \    std::move(east),\n              std::move(west)\n          } {}\n\n    explicit\
    \ constexpr Dice(std::array<T, face_count> faces)\n        : faces_(std::move(faces))\
    \ {}\n\n    [[nodiscard]] constexpr const T& operator[](DiceFace face) const noexcept\
    \ {\n        return faces_[index(face)];\n    }\n\n    [[nodiscard]] constexpr\
    \ T& operator[](DiceFace face) noexcept {\n        return faces_[index(face)];\n\
    \    }\n\n    [[nodiscard]] constexpr const T& top() const noexcept {\n      \
    \  return (*this)[DiceFace::top];\n    }\n\n    [[nodiscard]] constexpr const\
    \ T& bottom() const noexcept {\n        return (*this)[DiceFace::bottom];\n  \
    \  }\n\n    [[nodiscard]] constexpr const T& north() const noexcept {\n      \
    \  return (*this)[DiceFace::north];\n    }\n\n    [[nodiscard]] constexpr const\
    \ T& south() const noexcept {\n        return (*this)[DiceFace::south];\n    }\n\
    \n    [[nodiscard]] constexpr const T& east() const noexcept {\n        return\
    \ (*this)[DiceFace::east];\n    }\n\n    [[nodiscard]] constexpr const T& west()\
    \ const noexcept {\n        return (*this)[DiceFace::west];\n    }\n\n    [[nodiscard]]\
    \ constexpr const std::array<T, face_count>& faces() const noexcept {\n      \
    \  return faces_;\n    }\n\n    constexpr Dice& roll_north() {\n        T old_top\
    \ = std::move((*this)[DiceFace::top]);\n        (*this)[DiceFace::top] = std::move((*this)[DiceFace::south]);\n\
    \        (*this)[DiceFace::south] = std::move((*this)[DiceFace::bottom]);\n  \
    \      (*this)[DiceFace::bottom] = std::move((*this)[DiceFace::north]);\n    \
    \    (*this)[DiceFace::north] = std::move(old_top);\n        return *this;\n \
    \   }\n\n    constexpr Dice& roll_south() {\n        T old_top = std::move((*this)[DiceFace::top]);\n\
    \        (*this)[DiceFace::top] = std::move((*this)[DiceFace::north]);\n     \
    \   (*this)[DiceFace::north] = std::move((*this)[DiceFace::bottom]);\n       \
    \ (*this)[DiceFace::bottom] = std::move((*this)[DiceFace::south]);\n        (*this)[DiceFace::south]\
    \ = std::move(old_top);\n        return *this;\n    }\n\n    constexpr Dice& roll_east()\
    \ {\n        T old_top = std::move((*this)[DiceFace::top]);\n        (*this)[DiceFace::top]\
    \ = std::move((*this)[DiceFace::west]);\n        (*this)[DiceFace::west] = std::move((*this)[DiceFace::bottom]);\n\
    \        (*this)[DiceFace::bottom] = std::move((*this)[DiceFace::east]);\n   \
    \     (*this)[DiceFace::east] = std::move(old_top);\n        return *this;\n \
    \   }\n\n    constexpr Dice& roll_west() {\n        T old_top = std::move((*this)[DiceFace::top]);\n\
    \        (*this)[DiceFace::top] = std::move((*this)[DiceFace::east]);\n      \
    \  (*this)[DiceFace::east] = std::move((*this)[DiceFace::bottom]);\n        (*this)[DiceFace::bottom]\
    \ = std::move((*this)[DiceFace::west]);\n        (*this)[DiceFace::west] = std::move(old_top);\n\
    \        return *this;\n    }\n\n    constexpr Dice& roll(DiceDirection direction)\
    \ {\n        switch (direction) {\n            case DiceDirection::north:\n  \
    \              return roll_north();\n            case DiceDirection::south:\n\
    \                return roll_south();\n            case DiceDirection::east:\n\
    \                return roll_east();\n            case DiceDirection::west:\n\
    \                return roll_west();\n        }\n        return *this;\n    }\n\
    \n    constexpr Dice& rotate_clockwise() {\n        T old_north = std::move((*this)[DiceFace::north]);\n\
    \        (*this)[DiceFace::north] = std::move((*this)[DiceFace::west]);\n    \
    \    (*this)[DiceFace::west] = std::move((*this)[DiceFace::south]);\n        (*this)[DiceFace::south]\
    \ = std::move((*this)[DiceFace::east]);\n        (*this)[DiceFace::east] = std::move(old_north);\n\
    \        return *this;\n    }\n\n    constexpr Dice& rotate_counterclockwise()\
    \ {\n        T old_north = std::move((*this)[DiceFace::north]);\n        (*this)[DiceFace::north]\
    \ = std::move((*this)[DiceFace::east]);\n        (*this)[DiceFace::east] = std::move((*this)[DiceFace::south]);\n\
    \        (*this)[DiceFace::south] = std::move((*this)[DiceFace::west]);\n    \
    \    (*this)[DiceFace::west] = std::move(old_north);\n        return *this;\n\
    \    }\n\n    [[nodiscard]] constexpr std::array<Dice, 24> orientations() const\
    \ {\n        Dice top_top = *this;\n        Dice north_top = *this;\n        north_top.roll_south();\n\
    \        Dice south_top = *this;\n        south_top.roll_north();\n        Dice\
    \ east_top = *this;\n        east_top.roll_west();\n        Dice west_top = *this;\n\
    \        west_top.roll_east();\n        Dice bottom_top = *this;\n        bottom_top.roll_north().roll_north();\n\
    \n        std::array<Dice, 6> top_orientations{\n            std::move(top_top),\n\
    \            std::move(north_top),\n            std::move(south_top),\n      \
    \      std::move(east_top),\n            std::move(west_top),\n            std::move(bottom_top)\n\
    \        };\n\n        std::array<Dice, 24> result{\n            *this, *this,\
    \ *this, *this, *this, *this,\n            *this, *this, *this, *this, *this,\
    \ *this,\n            *this, *this, *this, *this, *this, *this,\n            *this,\
    \ *this, *this, *this, *this, *this\n        };\n        std::size_t result_index\
    \ = 0;\n        for (Dice oriented : top_orientations) {\n            for (int\
    \ rotation = 0; rotation < 4; ++rotation) {\n                result[result_index++]\
    \ = oriented;\n                oriented.rotate_clockwise();\n            }\n \
    \       }\n        return result;\n    }\n\n    [[nodiscard]] constexpr std::optional<Dice>\
    \ orientation(\n        const T& top_value,\n        const T& south_value\n  \
    \  ) const {\n        for (const Dice& oriented : orientations()) {\n        \
    \    if (oriented.top() == top_value && oriented.south() == south_value) {\n \
    \               return oriented;\n            }\n        }\n        return std::nullopt;\n\
    \    }\n\n    [[nodiscard]] constexpr bool equivalent(const Dice& other) const\
    \ {\n        for (const Dice& oriented : orientations()) {\n            if (oriented\
    \ == other) {\n                return true;\n            }\n        }\n      \
    \  return false;\n    }\n\n    friend constexpr bool operator==(const Dice&, const\
    \ Dice&) = default;\n};\n\nclass ArrowDice {\nprivate:\n    struct Vector {\n\
    \        int x;\n        int y;\n        int z;\n\n        friend constexpr bool\
    \ operator==(const Vector&, const Vector&) = default;\n    };\n\n    struct Frame\
    \ {\n        Vector normal;\n        Vector up;\n        Vector right;\n\n   \
    \     friend constexpr bool operator==(const Frame&, const Frame&) = default;\n\
    \    };\n\n    Dice<DiceFace> arrows_;\n\n    static constexpr Vector negate(Vector\
    \ vector) noexcept {\n        return Vector{-vector.x, -vector.y, -vector.z};\n\
    \    }\n\n    static constexpr DiceFace vector_to_face(Vector vector) {\n    \
    \    if (vector == Vector{0, 0, 1}) return DiceFace::top;\n        if (vector\
    \ == Vector{0, 0, -1}) return DiceFace::bottom;\n        if (vector == Vector{0,\
    \ 1, 0}) return DiceFace::north;\n        if (vector == Vector{0, -1, 0}) return\
    \ DiceFace::south;\n        if (vector == Vector{1, 0, 0}) return DiceFace::east;\n\
    \        if (vector == Vector{-1, 0, 0}) return DiceFace::west;\n        throw\
    \ std::invalid_argument(\"vector is not a cube direction\");\n    }\n\n    static\
    \ constexpr Frame adjacent_frame(\n        const Frame& frame,\n        DiceDirection\
    \ direction\n    ) noexcept {\n        switch (direction) {\n            case\
    \ DiceDirection::north:\n                return Frame{frame.up, negate(frame.normal),\
    \ frame.right};\n            case DiceDirection::south:\n                return\
    \ Frame{negate(frame.up), frame.normal, frame.right};\n            case DiceDirection::east:\n\
    \                return Frame{frame.right, frame.up, negate(frame.normal)};\n\
    \            case DiceDirection::west:\n                return Frame{negate(frame.right),\
    \ frame.up, frame.normal};\n        }\n        return frame;\n    }\n\n    static\
    \ constexpr DiceFace arrow_from_character(\n        char arrow,\n        const\
    \ Frame& frame\n    ) {\n        if (arrow == '^') return vector_to_face(frame.up);\n\
    \        if (arrow == 'v') return vector_to_face(negate(frame.up));\n        if\
    \ (arrow == '>') return vector_to_face(frame.right);\n        if (arrow == '<')\
    \ return vector_to_face(negate(frame.right));\n        throw std::invalid_argument(\"\
    arrow dice net contains an invalid character\");\n    }\n\n    constexpr void\
    \ rotate_arrows(DiceDirection direction) noexcept {\n        for (DiceFace face\
    \ : all_faces()) {\n            arrows_[face] = rotate_direction(arrows_[face],\
    \ direction);\n        }\n    }\n\n    static constexpr std::array<DiceFace, 6>\
    \ all_faces() noexcept {\n        return std::array<DiceFace, 6>{\n          \
    \  DiceFace::top,\n            DiceFace::bottom,\n            DiceFace::north,\n\
    \            DiceFace::south,\n            DiceFace::east,\n            DiceFace::west\n\
    \        };\n    }\n\npublic:\n    constexpr ArrowDice(\n        DiceFace top,\n\
    \        DiceFace bottom,\n        DiceFace north,\n        DiceFace south,\n\
    \        DiceFace east,\n        DiceFace west\n    )\n        : arrows_(top,\
    \ bottom, north, south, east, west) {}\n\n    explicit constexpr ArrowDice(Dice<DiceFace>\
    \ arrows)\n        : arrows_(std::move(arrows)) {}\n\n    [[nodiscard]] constexpr\
    \ DiceFace arrow(DiceFace face) const noexcept {\n        return arrows_[face];\n\
    \    }\n\n    [[nodiscard]] constexpr const Dice<DiceFace>& arrows() const noexcept\
    \ {\n        return arrows_;\n    }\n\n    constexpr ArrowDice& roll(DiceDirection\
    \ direction) {\n        arrows_.roll(direction);\n        rotate_arrows(direction);\n\
    \        return *this;\n    }\n\n    constexpr ArrowDice& roll_north() {\n   \
    \     return roll(DiceDirection::north);\n    }\n\n    constexpr ArrowDice& roll_south()\
    \ {\n        return roll(DiceDirection::south);\n    }\n\n    constexpr ArrowDice&\
    \ roll_east() {\n        return roll(DiceDirection::east);\n    }\n\n    constexpr\
    \ ArrowDice& roll_west() {\n        return roll(DiceDirection::west);\n    }\n\
    \n    constexpr ArrowDice& rotate_clockwise() {\n        arrows_.rotate_clockwise();\n\
    \        for (DiceFace face : all_faces()) {\n            arrows_[face] = rotate_direction_clockwise(arrows_[face]);\n\
    \        }\n        return *this;\n    }\n\n    constexpr ArrowDice& rotate_counterclockwise()\
    \ {\n        arrows_.rotate_counterclockwise();\n        for (DiceFace face :\
    \ all_faces()) {\n            arrows_[face] = rotate_direction_counterclockwise(arrows_[face]);\n\
    \        }\n        return *this;\n    }\n\n    [[nodiscard]] constexpr std::array<ArrowDice,\
    \ 24> orientations() const {\n        ArrowDice top_top = *this;\n        ArrowDice\
    \ north_top = *this;\n        north_top.roll_south();\n        ArrowDice south_top\
    \ = *this;\n        south_top.roll_north();\n        ArrowDice east_top = *this;\n\
    \        east_top.roll_west();\n        ArrowDice west_top = *this;\n        west_top.roll_east();\n\
    \        ArrowDice bottom_top = *this;\n        bottom_top.roll_north().roll_north();\n\
    \n        std::array<ArrowDice, 6> top_orientations{\n            top_top,\n \
    \           north_top,\n            south_top,\n            east_top,\n      \
    \      west_top,\n            bottom_top\n        };\n        std::array<ArrowDice,\
    \ 24> result{\n            *this, *this, *this, *this, *this, *this,\n       \
    \     *this, *this, *this, *this, *this, *this,\n            *this, *this, *this,\
    \ *this, *this, *this,\n            *this, *this, *this, *this, *this, *this\n\
    \        };\n\n        std::size_t result_index = 0;\n        for (ArrowDice oriented\
    \ : top_orientations) {\n            for (int rotation = 0; rotation < 4; ++rotation)\
    \ {\n                result[result_index++] = oriented;\n                oriented.rotate_clockwise();\n\
    \            }\n        }\n        return result;\n    }\n\n    [[nodiscard]]\
    \ constexpr int difference(const ArrowDice& other) const noexcept {\n        int\
    \ result = 0;\n        for (DiceFace face : all_faces()) {\n            result\
    \ += arrow(face) != other.arrow(face);\n        }\n        return result;\n  \
    \  }\n\n    [[nodiscard]] constexpr int distance(const ArrowDice& other) const\
    \ {\n        int result = 6;\n        for (const ArrowDice& oriented : orientations())\
    \ {\n            int current = oriented.difference(other);\n            if (current\
    \ < result) result = current;\n        }\n        return result;\n    }\n\n  \
    \  [[nodiscard]] static ArrowDice from_net(\n        const std::vector<std::string>&\
    \ net,\n        char empty = '.'\n    ) {\n        if (net.empty()) {\n      \
    \      throw std::invalid_argument(\"arrow dice net is empty\");\n        }\n\
    \        std::size_t width = net.front().size();\n        if (width == 0) {\n\
    \            throw std::invalid_argument(\"arrow dice net is empty\");\n     \
    \   }\n        for (const std::string& row : net) {\n            if (row.size()\
    \ != width) {\n                throw std::invalid_argument(\"arrow dice net must\
    \ be rectangular\");\n            }\n        }\n\n        int height = static_cast<int>(net.size());\n\
    \        int integer_width = static_cast<int>(width);\n        std::vector<std::vector<std::optional<Frame>>>\
    \ frames(\n            net.size(),\n            std::vector<std::optional<Frame>>(width)\n\
    \        );\n        auto character_at = [&](int row, int column) -> char {\n\
    \            return net[static_cast<std::size_t>(row)]\n                     \
    \ [static_cast<std::size_t>(column)];\n        };\n        auto frame_at = [&](int\
    \ row, int column) -> std::optional<Frame>& {\n            return frames[static_cast<std::size_t>(row)]\n\
    \                         [static_cast<std::size_t>(column)];\n        };\n  \
    \      std::vector<std::pair<int, int>> queue;\n        int face_count = 0;\n\
    \        for (int row = 0; row < height; ++row) {\n            for (int column\
    \ = 0; column < integer_width; ++column) {\n                if (character_at(row,\
    \ column) != empty) {\n                    ++face_count;\n                   \
    \ if (queue.empty()) queue.emplace_back(row, column);\n                }\n   \
    \         }\n        }\n        if (face_count != 6) {\n            throw std::invalid_argument(\"\
    arrow dice net must contain six faces\");\n        }\n\n        Frame initial{\n\
    \            Vector{0, 0, 1},\n            Vector{0, 1, 0},\n            Vector{1,\
    \ 0, 0}\n        };\n        frame_at(queue.front().first, queue.front().second)\
    \ = initial;\n\n        constexpr std::array<int, 4> row_delta{-1, 1, 0, 0};\n\
    \        constexpr std::array<int, 4> column_delta{0, 0, 1, -1};\n        constexpr\
    \ std::array<DiceDirection, 4> directions{\n            DiceDirection::north,\n\
    \            DiceDirection::south,\n            DiceDirection::east,\n       \
    \     DiceDirection::west\n        };\n        for (std::size_t head = 0; head\
    \ < queue.size(); ++head) {\n            int row = queue[head].first;\n      \
    \      int column = queue[head].second;\n            Frame frame = *frame_at(row,\
    \ column);\n            for (std::size_t edge = 0; edge < directions.size(); ++edge)\
    \ {\n                int next_row = row + row_delta[edge];\n                int\
    \ next_column = column + column_delta[edge];\n                if (\n         \
    \           next_row < 0 || next_row >= height ||\n                    next_column\
    \ < 0 || next_column >= integer_width ||\n                    character_at(next_row,\
    \ next_column) == empty\n                ) {\n                    continue;\n\
    \                }\n\n                Frame next_frame = adjacent_frame(frame,\
    \ directions[edge]);\n                std::optional<Frame>& known = frame_at(next_row,\
    \ next_column);\n                if (!known.has_value()) {\n                 \
    \   known = next_frame;\n                    queue.emplace_back(next_row, next_column);\n\
    \                } else if (*known != next_frame) {\n                    throw\
    \ std::invalid_argument(\"arrow dice net folds inconsistently\");\n          \
    \      }\n            }\n        }\n        if (queue.size() != 6) {\n       \
    \     throw std::invalid_argument(\"arrow dice net is disconnected\");\n     \
    \   }\n\n        std::array<std::optional<DiceFace>, 6> arrows;\n        for (const\
    \ std::pair<int, int>& cell : queue) {\n            int row = cell.first;\n  \
    \          int column = cell.second;\n            Frame frame = *frame_at(row,\
    \ column);\n            DiceFace face = vector_to_face(frame.normal);\n      \
    \      std::optional<DiceFace>& slot =\n                arrows[static_cast<std::size_t>(face)];\n\
    \            if (slot.has_value()) {\n                throw std::invalid_argument(\"\
    arrow dice net overlaps when folded\");\n            }\n            slot = arrow_from_character(character_at(row,\
    \ column), frame);\n        }\n        for (const std::optional<DiceFace>& arrow\
    \ : arrows) {\n            if (!arrow.has_value()) {\n                throw std::invalid_argument(\"\
    arrow dice net does not form a cube\");\n            }\n        }\n\n        return\
    \ ArrowDice(\n            *arrows[static_cast<std::size_t>(DiceFace::top)],\n\
    \            *arrows[static_cast<std::size_t>(DiceFace::bottom)],\n          \
    \  *arrows[static_cast<std::size_t>(DiceFace::north)],\n            *arrows[static_cast<std::size_t>(DiceFace::south)],\n\
    \            *arrows[static_cast<std::size_t>(DiceFace::east)],\n            *arrows[static_cast<std::size_t>(DiceFace::west)]\n\
    \        );\n    }\n\n    friend constexpr bool operator==(const ArrowDice&, const\
    \ ArrowDice&) = default;\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\
    \n\n#line 4 \"verify/utilities/dice.test.cpp\"\n\n#line 6 \"verify/utilities/dice.test.cpp\"\
    \n#include <cassert>\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#line 5 \"utilities/fast_io.hpp\"\
    \n#include <charconv>\n#line 7 \"utilities/fast_io.hpp\"\n#include <cstdio>\n\
    #include <cstdlib>\n#include <cstdint>\n#include <cstring>\n#include <iterator>\n\
    #line 13 \"utilities/fast_io.hpp\"\n#include <type_traits>\n#line 15 \"utilities/fast_io.hpp\"\
    \n\nnamespace m1une {\nnamespace utilities {\nnamespace internal {\n\n// Detect\
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
    \    int _position;\n    int _length;\n\n    bool prepare_number() {\n       \
    \ if (_length - _position >= 64) return true;\n        const int remaining = _length\
    \ - _position;\n        if (remaining > 0) std::memmove(_buffer, _buffer + _position,\
    \ remaining);\n        const int added = int(std::fread(_buffer + remaining, 1,\
    \ buffer_size - remaining, _stream));\n        _position = 0;\n        _length\
    \ = remaining + added;\n        if (_length < buffer_size) _buffer[_length] =\
    \ '\\0';\n        return _length != 0;\n    }\n\n   public:\n    explicit FastInput(std::FILE*\
    \ stream = stdin)\n        : _stream(stream), _position(0), _length(0) {}\n\n\
    \    FastInput(const FastInput&) = delete;\n    FastInput& operator=(const FastInput&)\
    \ = delete;\n\n    int read_char_raw() {\n        if (_position == _length) {\n\
    \            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n  \
    \          _position = 0;\n            if (_length == 0) return EOF;\n       \
    \ }\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces() {\n\
    \        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c = read_char_raw();\n\
    \        if (c == EOF) return false;\n        --_position;\n        return true;\n\
    \    }\n\n    bool read(char& value) {\n        if (!skip_spaces()) return false;\n\
    \        value = char(read_char_raw());\n        return true;\n    }\n\n    bool\
    \ read(std::string& value) {\n        if (!skip_spaces()) return false;\n    \
    \    value.clear();\n        int c = read_char_raw();\n        while (c != EOF\
    \ && c > ' ') {\n            value.push_back(char(c));\n            c = read_char_raw();\n\
    \        }\n        return true;\n    }\n\n    bool read(bool& value) {\n    \
    \    int x;\n        if (!read(x)) return false;\n        value = x != 0;\n  \
    \      return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        if (!prepare_number()) return false;\n \
    \       int c = static_cast<unsigned char>(_buffer[_position++]);\n        while\
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
    \ template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
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
    \n   public:\n    explicit FastOutput(std::FILE* stream = stdout)\n        : _stream(stream),\n\
    \          _position(0),\n          _precision(6),\n          _float_format(std::chars_format::general)\
    \ {}\n\n    FastOutput(const FastOutput&) = delete;\n    FastOutput& operator=(const\
    \ FastOutput&) = delete;\n\n    ~FastOutput() {\n        flush();\n    }\n\n \
    \   void flush() {\n        if (_position == 0) return;\n        std::fwrite(_buffer,\
    \ 1, _position, _stream);\n        _position = 0;\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ for (char c : s) write_char(c);\n    }\n\n    void write(char c) {\n       \
    \ write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<std::is_floating_point_v<T>>\n\
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
    \        write(value.val());\n    }\n\n    template <class Range>\n    std::enable_if_t<\n\
    \        internal::is_range_v<Range>\n            && !internal::is_string_like_v<Range>\n\
    \    >\n    write(const Range& range) {\n        using StoredValue = internal::range_stored_value_t<const\
    \ Range>;\n        constexpr bool nested = internal::is_range_v<StoredValue>\n\
    \                                && !internal::is_string_like_v<StoredValue>;\n\
    \n        bool first = true;\n        for (const auto& value : range) {\n    \
    \        if (!first) write_char(nested ? '\\n' : ' ');\n            first = false;\n\
    \            if constexpr (std::is_same_v<StoredValue, bool> && !nested) {\n \
    \               write(static_cast<bool>(value));\n            } else {\n     \
    \           write(value);\n            }\n        }\n    }\n\n    template <class\
    \ First, class... Rest>\n    void print(const First& first, const Rest&... rest)\
    \ {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n \
    \   }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    void set_precision(int\
    \ precision) {\n        _precision = precision;\n    }\n\n    void set_fixed(int\
    \ precision = 6) {\n        _float_format = std::chars_format::fixed;\n      \
    \  _precision = precision;\n    }\n\n    void set_general(int precision = 6) {\n\
    \        _float_format = std::chars_format::general;\n        _precision = precision;\n\
    \    }\n\n    template <class... Args>\n    void println(const Args&... args)\
    \ {\n        print(args...);\n        write_char('\\n');\n    }\n\n    template\
    \ <class T>\n    FastOutput& operator<<(const T& value) {\n        write(value);\n\
    \        return *this;\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 8 \"verify/utilities/dice.test.cpp\"\n#include <set>\n#line\
    \ 10 \"verify/utilities/dice.test.cpp\"\n\nnamespace {\n\nusing m1une::utilities::Dice;\n\
    using m1une::utilities::DiceDirection;\nusing m1une::utilities::DiceFace;\n\n\
    void test_rolls() {\n    Dice<int> original(1, 6, 5, 2, 3, 4);\n\n    Dice<int>\
    \ north = original;\n    north.roll_north();\n    std::array<int, 6> expected_north{2,\
    \ 5, 1, 6, 3, 4};\n    assert(north.faces() == expected_north);\n    north.roll_south();\n\
    \    assert(north == original);\n\n    Dice<int> east = original;\n    east.roll_east();\n\
    \    std::array<int, 6> expected_east{4, 3, 5, 2, 1, 6};\n    assert(east.faces()\
    \ == expected_east);\n    east.roll_west();\n    assert(east == original);\n\n\
    \    Dice<int> cycle = original;\n    for (int step = 0; step < 4; ++step) cycle.roll(DiceDirection::north);\n\
    \    assert(cycle == original);\n    for (int step = 0; step < 4; ++step) cycle.rotate_clockwise();\n\
    \    assert(cycle == original);\n    cycle.rotate_clockwise().rotate_counterclockwise();\n\
    \    assert(cycle == original);\n}\n\nvoid test_orientations() {\n    Dice<int>\
    \ die(0, 1, 2, 3, 4, 5);\n    std::array<Dice<int>, 24> orientations = die.orientations();\n\
    \    std::set<std::array<int, 6>> distinct;\n    std::array<int, 6> top_count{};\n\
    \n    for (const Dice<int>& oriented : orientations) {\n        distinct.insert(oriented.faces());\n\
    \        ++top_count[static_cast<std::size_t>(oriented.top())];\n        assert(oriented[DiceFace::bottom]\
    \ == oriented.bottom());\n    }\n    assert(distinct.size() == 24);\n    for (int\
    \ count : top_count) assert(count == 4);\n\n    for (int top = 0; top < 6; ++top)\
    \ {\n        for (int south = 0; south < 6; ++south) {\n            bool are_opposite\
    \ =\n                (top == 0 && south == 1) ||\n                (top == 1 &&\
    \ south == 0) ||\n                (top == 2 && south == 3) ||\n              \
    \  (top == 3 && south == 2) ||\n                (top == 4 && south == 5) ||\n\
    \                (top == 5 && south == 4);\n            auto oriented = die.orientation(top,\
    \ south);\n            assert(oriented.has_value() == (top != south && !are_opposite));\n\
    \            if (oriented.has_value()) {\n                assert(oriented->top()\
    \ == top);\n                assert(oriented->south() == south);\n            }\n\
    \        }\n    }\n}\n\nvoid test_equivalence() {\n    Dice<std::string> first(\"\
    T\", \"B\", \"N\", \"S\", \"E\", \"W\");\n    Dice<std::string> rotated = first;\n\
    \    rotated.roll_north().roll_east().rotate_clockwise();\n    assert(first !=\
    \ rotated);\n    assert(first.equivalent(rotated));\n\n    Dice<std::string> reflected(\"\
    T\", \"B\", \"N\", \"S\", \"W\", \"E\");\n    assert(!first.equivalent(reflected));\n\
    \n    Dice<int> repeated(1, 1, 2, 2, 3, 3);\n    assert(repeated.orientations().size()\
    \ == 24);\n    assert(repeated.equivalent(repeated));\n}\n\nvoid test_opposites()\
    \ {\n    using m1une::utilities::opposite;\n    for (DiceFace face : {\n     \
    \        DiceFace::top,\n             DiceFace::bottom,\n             DiceFace::north,\n\
    \             DiceFace::south,\n             DiceFace::east,\n             DiceFace::west\n\
    \         }) {\n        assert(opposite(opposite(face)) == face);\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_rolls();\n    test_orientations();\n\
    \    test_equivalence();\n    test_opposites();\n\n    std::array<int, 6> input;\n\
    \    for (int& value : input) fast_input >> value;\n\n    Dice<int> die(\n   \
    \     input[0],\n        input[5],\n        input[4],\n        input[1],\n   \
    \     input[2],\n        input[3]\n    );\n\n    std::string commands;\n    fast_input\
    \ >> commands;\n    for (char command : commands) {\n        if (command == 'N')\
    \ die.roll_north();\n        if (command == 'S') die.roll_south();\n        if\
    \ (command == 'E') die.roll_east();\n        if (command == 'W') die.roll_west();\n\
    \    }\n    fast_output << die.top() << '\\n';\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ITP1_11_A\"\n\
    \n#include \"../../utilities/dice.hpp\"\n\n#include <array>\n#include <cassert>\n\
    #include \"../../utilities/fast_io.hpp\"\n#include <set>\n#include <string>\n\n\
    namespace {\n\nusing m1une::utilities::Dice;\nusing m1une::utilities::DiceDirection;\n\
    using m1une::utilities::DiceFace;\n\nvoid test_rolls() {\n    Dice<int> original(1,\
    \ 6, 5, 2, 3, 4);\n\n    Dice<int> north = original;\n    north.roll_north();\n\
    \    std::array<int, 6> expected_north{2, 5, 1, 6, 3, 4};\n    assert(north.faces()\
    \ == expected_north);\n    north.roll_south();\n    assert(north == original);\n\
    \n    Dice<int> east = original;\n    east.roll_east();\n    std::array<int, 6>\
    \ expected_east{4, 3, 5, 2, 1, 6};\n    assert(east.faces() == expected_east);\n\
    \    east.roll_west();\n    assert(east == original);\n\n    Dice<int> cycle =\
    \ original;\n    for (int step = 0; step < 4; ++step) cycle.roll(DiceDirection::north);\n\
    \    assert(cycle == original);\n    for (int step = 0; step < 4; ++step) cycle.rotate_clockwise();\n\
    \    assert(cycle == original);\n    cycle.rotate_clockwise().rotate_counterclockwise();\n\
    \    assert(cycle == original);\n}\n\nvoid test_orientations() {\n    Dice<int>\
    \ die(0, 1, 2, 3, 4, 5);\n    std::array<Dice<int>, 24> orientations = die.orientations();\n\
    \    std::set<std::array<int, 6>> distinct;\n    std::array<int, 6> top_count{};\n\
    \n    for (const Dice<int>& oriented : orientations) {\n        distinct.insert(oriented.faces());\n\
    \        ++top_count[static_cast<std::size_t>(oriented.top())];\n        assert(oriented[DiceFace::bottom]\
    \ == oriented.bottom());\n    }\n    assert(distinct.size() == 24);\n    for (int\
    \ count : top_count) assert(count == 4);\n\n    for (int top = 0; top < 6; ++top)\
    \ {\n        for (int south = 0; south < 6; ++south) {\n            bool are_opposite\
    \ =\n                (top == 0 && south == 1) ||\n                (top == 1 &&\
    \ south == 0) ||\n                (top == 2 && south == 3) ||\n              \
    \  (top == 3 && south == 2) ||\n                (top == 4 && south == 5) ||\n\
    \                (top == 5 && south == 4);\n            auto oriented = die.orientation(top,\
    \ south);\n            assert(oriented.has_value() == (top != south && !are_opposite));\n\
    \            if (oriented.has_value()) {\n                assert(oriented->top()\
    \ == top);\n                assert(oriented->south() == south);\n            }\n\
    \        }\n    }\n}\n\nvoid test_equivalence() {\n    Dice<std::string> first(\"\
    T\", \"B\", \"N\", \"S\", \"E\", \"W\");\n    Dice<std::string> rotated = first;\n\
    \    rotated.roll_north().roll_east().rotate_clockwise();\n    assert(first !=\
    \ rotated);\n    assert(first.equivalent(rotated));\n\n    Dice<std::string> reflected(\"\
    T\", \"B\", \"N\", \"S\", \"W\", \"E\");\n    assert(!first.equivalent(reflected));\n\
    \n    Dice<int> repeated(1, 1, 2, 2, 3, 3);\n    assert(repeated.orientations().size()\
    \ == 24);\n    assert(repeated.equivalent(repeated));\n}\n\nvoid test_opposites()\
    \ {\n    using m1une::utilities::opposite;\n    for (DiceFace face : {\n     \
    \        DiceFace::top,\n             DiceFace::bottom,\n             DiceFace::north,\n\
    \             DiceFace::south,\n             DiceFace::east,\n             DiceFace::west\n\
    \         }) {\n        assert(opposite(opposite(face)) == face);\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    m1une::utilities::FastInput fast_input;\n\
    \    m1une::utilities::FastOutput fast_output;\n\n    test_rolls();\n    test_orientations();\n\
    \    test_equivalence();\n    test_opposites();\n\n    std::array<int, 6> input;\n\
    \    for (int& value : input) fast_input >> value;\n\n    Dice<int> die(\n   \
    \     input[0],\n        input[5],\n        input[4],\n        input[1],\n   \
    \     input[2],\n        input[3]\n    );\n\n    std::string commands;\n    fast_input\
    \ >> commands;\n    for (char command : commands) {\n        if (command == 'N')\
    \ die.roll_north();\n        if (command == 'S') die.roll_south();\n        if\
    \ (command == 'E') die.roll_east();\n        if (command == 'W') die.roll_west();\n\
    \    }\n    fast_output << die.top() << '\\n';\n}\n"
  dependsOn:
  - utilities/dice.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/utilities/dice.test.cpp
  requiredBy: []
  timestamp: '2026-07-15 03:24:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/utilities/dice.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/dice.test.cpp
- /verify/verify/utilities/dice.test.cpp.html
title: verify/utilities/dice.test.cpp
---
