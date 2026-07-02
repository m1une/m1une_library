#!/usr/bin/env python3
"""A small, dependency-free C++ source minifier for contest submissions.

The minifier removes comments and unnecessary whitespace.  By default it also
shortens identifiers which look like variable declarations.  Renaming is
deliberately conservative: macros, types, functions, labels, qualified names,
and member names are left alone.
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
    "void", "volatile", "wchar_t", "while", "xor", "xor_eq",
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

MULTI_PUNCTUATORS = {p for p in PUNCTUATORS if len(p) > 1} | {"//", "/*"}
PUNCTUATOR_PREFIXES = {
    p[:i] for p in MULTI_PUNCTUATORS for i in range(2, len(p) + 1)
}


@dataclass(frozen=True)
class Token:
    kind: str
    text: str


def _quoted_end(source: str, start: int) -> int | None:
    """Return the end of a string/character/raw literal starting at start."""
    prefixes = ("u8R\"", "uR\"", "UR\"", "LR\"", "R\"")
    raw_prefix = next((p for p in prefixes if source.startswith(p, start)), None)
    if raw_prefix is not None:
        delimiter_start = start + len(raw_prefix)
        open_paren = source.find("(", delimiter_start)
        if open_paren == -1 or open_paren - delimiter_start > 16:
            return None
        delimiter = source[delimiter_start:open_paren]
        if any(ch.isspace() or ch in "()\\" for ch in delimiter):
            return None
        close = source.find(")" + delimiter + "\"", open_paren + 1)
        return len(source) if close == -1 else close + len(delimiter) + 2

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
            return i + 1
        else:
            i += 1
    return len(source)


def tokenize(source: str) -> list[Token]:
    # C++ removes escaped newlines before recognizing comments or tokens.
    source = source.replace("\\\r\n", "").replace("\\\n", "")
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

        if at_line_start and ch == "#":
            start = i
            while i < n:
                newline = source.find("\n", i)
                if newline == -1:
                    i = n
                    break
                backslashes = 0
                j = newline - 1
                while j >= start and source[j] == "\\":
                    backslashes += 1
                    j -= 1
                i = newline + 1
                if backslashes % 2 == 0:
                    break
            tokens.append(Token("directive", source[start:i].rstrip()))
            at_line_start = True
            continue

        at_line_start = False
        if source.startswith("//", i):
            newline = source.find("\n", i + 2)
            i = n if newline == -1 else newline + 1
            at_line_start = True
            continue
        if source.startswith("/*", i):
            close = source.find("*/", i + 2)
            if close == -1:
                i = n
            else:
                segment = source[i:close + 2]
                at_line_start = segment.endswith("\n")
                i = close + 2
            continue

        literal_end = _quoted_end(source, i)
        if literal_end is not None:
            tokens.append(Token("literal", source[i:literal_end]))
            i = literal_end
            continue

        if ch.isalpha() or ch == "_":
            j = i + 1
            while j < n and (source[j].isalnum() or source[j] == "_"):
                j += 1
            tokens.append(Token("identifier", source[i:j]))
            i = j
            continue

        if ch.isdigit() or (ch == "." and i + 1 < n and source[i + 1].isdigit()):
            j = i + 1
            while j < n:
                current = source[j]
                if current.isalnum() or current in "_.'":
                    j += 1
                elif current in "+-" and source[j - 1] in "eEpP":
                    j += 1
                else:
                    break
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
            result.update(re.findall(r"[A-Za-z_][A-Za-z_0-9]*", token.text))
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
    if previous.text[-1].isalnum() or previous.text[-1] == "_":
        if current.text[0].isalnum() or current.text[0] == "_":
            return True
    if previous.kind == "number" and current.kind == "identifier":
        return True
    if previous.text == "." and current.text[0].isdigit():
        return True
    if previous.kind == "number" and current.text in {"+", "-"} and previous.text[-1] in "eEpP":
        return True
    return previous.text + current.text in PUNCTUATOR_PREFIXES


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

    return "".join(output).rstrip() + "\n", renames


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
        reduction = 0.0 if not source else 100.0 * (len(source) - len(result)) / len(source)
        print(
            f"{len(source)} -> {len(result)} bytes ({reduction:.1f}% smaller), "
            f"renamed {len(renames)} identifiers",
            file=sys.stderr,
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
