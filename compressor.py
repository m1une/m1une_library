#!/usr/bin/env python3
"""A small, dependency-free C++ source minifier for contest submissions.

The minifier removes comments and whitespace without changing the C++ token
stream.  By default it also shortens identifiers which look like variable
declarations.  Renaming is deliberately conservative: macros, types,
functions, labels, qualified names, and member names are left alone.
"""

from __future__ import annotations

import argparse
import re
import sys
from dataclasses import dataclass
from pathlib import Path


CPP_KEYWORDS = {
    "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand",
    "bitor", "bool", "break", "case", "catch", "char", "char8_t",
    "char16_t", "char32_t", "class", "compl", "concept", "const",
    "consteval", "constexpr", "constinit", "const_cast", "continue",
    "co_await", "co_return", "co_yield", "decltype", "default", "delete",
    "do", "double", "dynamic_cast", "else", "enum", "explicit", "export",
    "extern", "false", "float", "for", "friend", "goto", "if", "inline",
    "int", "long", "mutable", "namespace", "new", "noexcept", "not",
    "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected",
    "public", "register", "reinterpret_cast", "requires", "return", "short",
    "signed", "sizeof", "static", "static_assert", "static_cast", "struct",
    "switch", "template", "this", "thread_local", "throw", "true", "try",
    "typedef", "typeid", "typename", "union", "unsigned", "using", "virtual",
    "void", "volatile", "wchar_t", "while", "xor", "xor_eq", "import",
    "module",
}

BUILTIN_TYPES = {
    "auto", "bool", "char", "char8_t", "char16_t", "char32_t", "double",
    "float", "int", "long", "short", "signed", "unsigned", "void",
    "wchar_t", "size_t", "ptrdiff_t", "int8_t", "int16_t", "int32_t",
    "int64_t", "uint8_t", "uint16_t", "uint32_t", "uint64_t", "__int128",
    "__int128_t", "__uint128_t",
}

COMMON_TYPES = {
    "array", "bitset", "deque", "function", "initializer_list", "list",
    "map", "multimap", "multiset", "optional", "pair", "priority_queue",
    "queue", "set", "span", "stack", "string", "string_view", "tuple",
    "unordered_map", "unordered_multimap", "unordered_multiset",
    "unordered_set", "variant", "vector",
}

CV_AND_POINTER = {"const", "volatile", "constexpr", "static", "mutable", "*", "&", "&&"}

PUNCTUATORS = (
    "%:%:", "<<=", ">>=", "<=>", "->*", "...", "##", "::", ".*", "->",
    "++", "--", "<<", ">>", "<=", ">=", "==", "!=", "&&", "||", "*=",
    "/=", "%=", "+=", "-=", "&=", "^=", "|=", "<:", ":>", "<%", "%>",
    "%:", "{", "}", "[", "]", "(", ")", "#", ";", ":", "?", ".", "+",
    "-", "*", "/", "%", "^", "&", "|", "~", "!", "=", "<", ">", ",",
)


@dataclass(frozen=True)
class Token:
    kind: str
    text: str


def _is_identifier_start(ch: str) -> bool:
    # '$' is a widely supported GCC/Clang extension and is useful to recognize
    # even though portable C++ identifiers do not contain it.
    return ch in "_$" or ch.isalpha() or (ord(ch) >= 128 and not ch.isspace())


def _is_identifier_continue(ch: str) -> bool:
    return _is_identifier_start(ch) or ch.isdigit()


def _number_end(source: str, start: int) -> int:
    """Return the end of a preprocessing number starting at ``start``."""
    i = start + 1
    while i < len(source):
        current = source[i]
        if _is_identifier_continue(current) or current == ".":
            i += 1
        elif (
            current == "'"
            and i + 1 < len(source)
            and _is_identifier_continue(source[i + 1])
        ):
            i += 2
        elif current in "+-" and source[i - 1] in "eEpP":
            i += 1
        else:
            break
    return i


def _raw_literal_bounds(source: str, start: int) -> tuple[int, int, int] | None:
    """Return ``(open_paren, close_paren, end)`` for a raw literal."""
    prefixes = ("u8R\"", "uR\"", "UR\"", "LR\"", "R\"")
    raw_prefix = next((p for p in prefixes if source.startswith(p, start)), None)
    if raw_prefix is None:
        return None
    delimiter_start = start + len(raw_prefix)
    open_paren = source.find("(", delimiter_start)
    if open_paren == -1 or open_paren - delimiter_start > 16:
        return None
    delimiter = source[delimiter_start:open_paren]
    if any(ch.isspace() or ch in "()\\" for ch in delimiter):
        return None
    close_paren = source.find(")" + delimiter + "\"", open_paren + 1)
    if close_paren == -1:
        return None
    end = close_paren + len(delimiter) + 2
    while end < len(source) and _is_identifier_continue(source[end]):
        end += 1
    return open_paren, close_paren, end


def _quoted_end(source: str, start: int) -> int | None:
    """Return the end of a string/character/raw literal starting at start.

    An immediately adjacent user-defined-literal suffix is part of the token.
    """
    raw_bounds = _raw_literal_bounds(source, start)
    if raw_bounds is not None:
        return raw_bounds[2]
    if any(source.startswith(p, start) for p in ("u8R\"", "uR\"", "UR\"", "LR\"", "R\"")):
        # It looks like a raw literal but is malformed or unterminated.  The
        # compiler will diagnose it; treating the remainder as one token keeps
        # the minifier from compounding the error.
        return len(source)

    prefixes = ("u8\"", "u\"", "U\"", "L\"", "\"", "u'", "U'", "L'", "'")
    prefix = next((p for p in prefixes if source.startswith(p, start)), None)
    if prefix is None:
        return None
    quote = prefix[-1]
    i = start + len(prefix)
    while i < len(source):
        if source[i] == "\\":
            i += 2
        elif source[i] == quote:
            end = i + 1
            while end < len(source) and _is_identifier_continue(source[end]):
                end += 1
            return end
        else:
            i += 1
    return len(source)


def _splice_lines(source: str) -> str:
    """Perform phase-2 line splicing while restoring raw-string contents."""
    spliced: list[str] = []
    origins: list[int] = []
    i = 0
    while i < len(source):
        if source[i] == "\\":
            if source.startswith("\r\n", i + 1):
                i += 3
                continue
            if i + 1 < len(source) and source[i + 1] in "\r\n":
                i += 2
                continue
        spliced.append(source[i])
        origins.append(i)
        i += 1

    phase_two = "".join(spliced)
    output: list[str] = []
    copied_until = 0
    i = 0
    while i < len(phase_two):
        if phase_two.startswith("//", i):
            newline = phase_two.find("\n", i + 2)
            i = len(phase_two) if newline == -1 else newline
            continue
        if phase_two.startswith("/*", i):
            close = phase_two.find("*/", i + 2)
            i = len(phase_two) if close == -1 else close + 2
            continue
        if phase_two[i].isdigit() or (
            phase_two[i] == "."
            and i + 1 < len(phase_two)
            and phase_two[i + 1].isdigit()
        ):
            i = _number_end(phase_two, i)
            continue

        raw_bounds = _raw_literal_bounds(phase_two, i)
        if raw_bounds is not None:
            open_paren, close_paren, end = raw_bounds
            output.append(phase_two[copied_until:open_paren + 1])
            original_open = origins[open_paren]
            original_close = origins[close_paren]
            output.append(source[original_open + 1:original_close])
            output.append(phase_two[close_paren:end])
            copied_until = end
            i = end
            continue

        literal_end = _quoted_end(phase_two, i)
        if literal_end is not None:
            i = literal_end
            continue
        if _is_identifier_start(phase_two[i]):
            i += 1
            while i < len(phase_two) and _is_identifier_continue(phase_two[i]):
                i += 1
            continue
        i += 1

    output.append(phase_two[copied_until:])
    return "".join(output)


def _prepare_source(source: str) -> str:
    """Apply the translation phases needed before preprocessing-token lexing."""
    # Line splicing precedes comment recognition.  C++ restores transformations
    # within raw-string contents after recognizing the raw literal.
    source = source.replace("\r\n", "\n").replace("\r", "\n")
    source = _splice_lines(source)

    # Comments are replaced by one space in translation phase 3.  In
    # particular, newlines *inside* a block comment do not terminate a
    # preprocessing directive.
    output: list[str] = []
    i = 0
    while i < len(source):
        if source[i].isdigit() or (
            source[i] == "." and i + 1 < len(source) and source[i + 1].isdigit()
        ):
            end = _number_end(source, i)
            output.append(source[i:end])
            i = end
            continue
        literal_end = _quoted_end(source, i)
        if literal_end is not None:
            output.append(source[i:literal_end])
            i = literal_end
            continue
        if source.startswith("//", i):
            output.append(" ")
            newline = source.find("\n", i + 2)
            i = len(source) if newline == -1 else newline
            continue
        if source.startswith("/*", i):
            output.append(" ")
            close = source.find("*/", i + 2)
            i = len(source) if close == -1 else close + 2
            continue
        output.append(source[i])
        i += 1
    return "".join(output)


def _directive_end(source: str, start: int) -> int:
    """Return the end of a preprocessing directive, including its newline."""
    i = start
    while i < len(source):
        if source[i] == "\n":
            return i + 1
        if source[i].isdigit() or (
            source[i] == "." and i + 1 < len(source) and source[i + 1].isdigit()
        ):
            i = _number_end(source, i)
            continue
        literal_end = _quoted_end(source, i)
        if literal_end is not None:
            i = literal_end
            continue
        if _is_identifier_start(source[i]):
            i += 1
            while i < len(source) and _is_identifier_continue(source[i]):
                i += 1
            continue
        i += 1
    return len(source)


def tokenize(source: str) -> list[Token]:
    source = _prepare_source(source)
    tokens: list[Token] = []
    i = 0
    at_line_start = True
    n = len(source)

    while i < n:
        ch = source[i]
        if ch in " \t\v\f\r":
            i += 1
            continue
        if ch == "\n":
            at_line_start = True
            i += 1
            continue

        if at_line_start and (ch == "#" or source.startswith("%:", i)):
            start = i
            i = _directive_end(source, i)
            tokens.append(Token("directive", source[start:i].rstrip()))
            at_line_start = True
            continue

        at_line_start = False
        literal_end = _quoted_end(source, i)
        if literal_end is not None:
            tokens.append(Token("literal", source[i:literal_end]))
            i = literal_end
            continue

        if _is_identifier_start(ch):
            j = i + 1
            while j < n and _is_identifier_continue(source[j]):
                j += 1
            tokens.append(Token("identifier", source[i:j]))
            i = j
            continue

        if ch.isdigit() or (ch == "." and i + 1 < n and source[i + 1].isdigit()):
            j = _number_end(source, i)
            tokens.append(Token("number", source[i:j]))
            i = j
            continue

        punctuator = next((p for p in PUNCTUATORS if source.startswith(p, i)), ch)
        tokens.append(Token("punct", punctuator))
        i += len(punctuator)

    return tokens


def _matching_left(tokens: list[Token], right: int, opening: str, closing: str) -> int | None:
    depth = 0
    for i in range(right, -1, -1):
        if tokens[i].text == closing:
            depth += 1
        elif tokens[i].text == opening:
            depth -= 1
            if depth == 0:
                return i
    return None


def _known_types(tokens: list[Token]) -> set[str]:
    known = set(BUILTIN_TYPES) | set(COMMON_TYPES)
    for i, token in enumerate(tokens):
        if token.kind != "identifier":
            continue
        previous = tokens[i - 1].text if i else ""
        if previous in {"class", "struct", "union", "enum", "typename"}:
            known.add(token.text)
        if previous == "using" and i + 1 < len(tokens) and tokens[i + 1].text == "=":
            known.add(token.text)

    # In a typedef declaration, the final identifier is the new type name.
    start = 0
    for i, token in enumerate(tokens):
        if token.text in {";", "{", "}"}:
            statement = tokens[start:i]
            if statement and statement[0].text == "typedef":
                identifiers = [t.text for t in statement if t.kind == "identifier"]
                if identifiers:
                    known.add(identifiers[-1])
            start = i + 1
    return known


def _type_before(tokens: list[Token], index: int, known_types: set[str]) -> bool:
    j = index - 1
    while j >= 0 and tokens[j].text in CV_AND_POINTER:
        j -= 1
    if j < 0:
        return False
    if tokens[j].text in BUILTIN_TYPES or tokens[j].text in known_types:
        return True
    if tokens[j].text == ">":
        left = _matching_left(tokens, j, "<", ">")
        return left is not None and left > 0 and tokens[left - 1].kind == "identifier"
    if tokens[j].text == ")":
        left = _matching_left(tokens, j, "(", ")")
        return left is not None and left > 0 and tokens[left - 1].text == "decltype"
    return False


def _directive_identifiers(tokens: list[Token]) -> set[str]:
    result: set[str] = set()
    for token in tokens:
        if token.kind == "directive":
            result.update(re.findall(r"(?:[^\W\d]|[_$])(?:\w|[$])*", token.text))
    return result


def variable_renames(tokens: list[Token]) -> dict[str, str]:
    """Build a conservative, global variable-name replacement map."""
    known_types = _known_types(tokens)
    candidates: set[str] = set()
    declaration_indices: list[int] = []

    for i, token in enumerate(tokens):
        if token.kind == "identifier" and token.text not in CPP_KEYWORDS:
            if _type_before(tokens, i, known_types):
                candidates.add(token.text)
                declaration_indices.append(i)

        # Structured bindings: auto [long_name, other_name].
        if token.text == "[":
            j = i - 1
            while j >= 0 and tokens[j].text in CV_AND_POINTER:
                j -= 1
            if j >= 0 and tokens[j].text == "auto":
                close = next((k for k in range(i + 1, len(tokens)) if tokens[k].text == "]"), None)
                if close is not None:
                    for item in tokens[i + 1:close]:
                        if item.kind == "identifier" and item.text not in CPP_KEYWORDS:
                            candidates.add(item.text)

    # Add later declarators in declarations such as: int first = 0, second = 1;
    for declaration in declaration_indices:
        paren = bracket = brace = 0
        i = declaration + 1
        while i < len(tokens):
            text = tokens[i].text
            if text == "(":
                paren += 1
            elif text == ")":
                if paren == 0:
                    break
                paren -= 1
            elif text == "[":
                bracket += 1
            elif text == "]":
                bracket = max(0, bracket - 1)
            elif text == "{":
                brace += 1
            elif text == "}":
                if brace == 0:
                    break
                brace -= 1
            elif text == ";" and paren == bracket == brace == 0:
                break
            elif text == "," and paren == bracket == brace == 0:
                j = i + 1
                while j < len(tokens) and tokens[j].text in CV_AND_POINTER:
                    j += 1
                if j < len(tokens) and tokens[j].kind == "identifier":
                    name = tokens[j].text
                    if name not in known_types and name not in CPP_KEYWORDS:
                        candidates.add(name)
            i += 1

    protected = _directive_identifiers(tokens) | known_types | CPP_KEYWORDS | {"main"}
    for i, token in enumerate(tokens):
        if token.kind != "identifier":
            continue
        previous = tokens[i - 1].text if i else ""
        following = tokens[i + 1].text if i + 1 < len(tokens) else ""
        if previous in {".", "->", "::", "goto", "class", "struct", "union", "enum", "namespace", "using", "typedef"}:
            protected.add(token.text)
        if following in {"::", ":"}:
            protected.add(token.text)
        if following == "(":
            protected.add(token.text)
        if token.text.startswith("__") or (token.text.startswith("_") and len(token.text) > 1 and token.text[1].isupper()):
            protected.add(token.text)
        if token.kind == "identifier" and previous and i > 0 and tokens[i - 1].kind == "literal":
            protected.add(token.text)

    # A type followed by name(...) is potentially a function declaration or a
    # direct-initialization ambiguity.  Leaving it untouched is the safe choice.
    for i in declaration_indices:
        if i + 1 < len(tokens) and tokens[i + 1].text == "(":
            protected.add(tokens[i].text)

    candidates -= protected
    counts: dict[str, int] = {}
    for token in tokens:
        if token.kind == "identifier" and token.text in candidates:
            counts[token.text] = counts.get(token.text, 0) + 1

    unavailable = {
        token.text for token in tokens if token.kind == "identifier"
    } | CPP_KEYWORDS

    def short_names():
        alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
        length = 1
        while True:
            indices = [0] * length
            while True:
                yield "".join(alphabet[index] for index in indices)
                position = length - 1
                while position >= 0 and indices[position] == len(alphabet) - 1:
                    indices[position] = 0
                    position -= 1
                if position < 0:
                    break
                indices[position] += 1
            length += 1

    names = short_names()
    renames: dict[str, str] = {}
    for old in sorted(candidates, key=lambda name: (-counts.get(name, 0), -len(name), name)):
        new = next(names)
        while new in unavailable or new in renames.values():
            new = next(names)
        if len(new) < len(old):
            renames[old] = new
    return renames


def _needs_space(previous: Token, current: Token) -> bool:
    if previous.kind == "directive" or current.kind == "directive":
        return False
    # Re-lexing the boundary is more reliable than maintaining a growing list
    # of special cases for pp-numbers, literal prefixes, digraphs, comments,
    # and multi-character punctuators.  Each token participates in at most two
    # such checks, so the total amount of text examined remains linear.
    combined = tokenize(previous.text + current.text)
    return combined != [previous, current]


def minify(source: str, rename: bool = True) -> tuple[str, dict[str, str]]:
    tokens = tokenize(source)
    renames = variable_renames(tokens) if rename else {}
    output: list[str] = []
    previous: Token | None = None

    for original in tokens:
        token = original
        if token.kind == "identifier" and token.text in renames:
            token = Token(token.kind, renames[token.text])

        if token.kind == "directive":
            if output and not output[-1].endswith("\n"):
                output.append("\n")
            output.append(token.text + "\n")
            previous = None
            continue
        if previous is not None and _needs_space(previous, token):
            output.append(" ")
        output.append(token.text)
        previous = token

    result = "".join(output).rstrip()
    return (result + "\n" if result else ""), renames


def main() -> int:
    parser = argparse.ArgumentParser(description="Minify C++ source code for contest submissions.")
    parser.add_argument("input", nargs="?", type=Path, help="input file (default: stdin)")
    parser.add_argument("-o", "--output", type=Path, help="output file (default: stdout)")
    parser.add_argument("--no-rename", action="store_true", help="only remove comments and whitespace")
    parser.add_argument("--stats", action="store_true", help="print size and rename statistics to stderr")
    args = parser.parse_args()

    source = args.input.read_text(encoding="utf-8") if args.input else sys.stdin.read()
    result, renames = minify(source, rename=not args.no_rename)
    if args.output:
        args.output.write_text(result, encoding="utf-8")
    else:
        sys.stdout.write(result)

    if args.stats:
        source_size = len(source.encode("utf-8"))
        result_size = len(result.encode("utf-8"))
        reduction = 0.0 if not source_size else 100.0 * (source_size - result_size) / source_size
        print(
            f"{source_size} -> {result_size} bytes ({reduction:.1f}% smaller), "
            f"renamed {len(renames)} identifiers",
            file=sys.stderr,
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
