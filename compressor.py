#!/usr/bin/env python3
"""A small, dependency-free C++ source minifier for contest submissions.

The minifier removes comments and whitespace without changing the C++ token
stream.  By default it also shortens file-owned variables, fields, types,
namespaces, and unqualified functions, and introduces aliases when their
declaration cost is profitable.  Macros, reserved names, external qualified
names and member calls, contract functions, and labels remain protected.
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

CONVENTIONAL_EXTERNAL_DOT_MEMBERS = {"first", "second"}
CONVENTIONAL_EXTERNAL_QUALIFIED_MEMBERS = {"type", "value"}

TYPE_ALIAS_PATTERNS = (
    ("unsigned", "long", "long", "int"),
    ("signed", "long", "long", "int"),
    ("unsigned", "long", "long"),
    ("signed", "long", "long"),
    ("long", "long", "int"),
    ("long", "long"),
    ("unsigned", "long", "int"),
    ("signed", "long", "int"),
    ("unsigned", "short", "int"),
    ("signed", "short", "int"),
    ("short", "int"),
    ("long", "int"),
    ("unsigned", "char"),
    ("signed", "char"),
    ("unsigned", "long"),
    ("signed", "long"),
    ("unsigned", "short"),
    ("signed", "short"),
    ("unsigned", "int"),
    ("signed", "int"),
    ("long", "double"),
    ("void",),
    ("bool",),
    ("char",),
    ("char8_t",),
    ("char16_t",),
    ("char32_t",),
    ("wchar_t",),
    ("short",),
    ("int",),
    ("long",),
    ("signed",),
    ("unsigned",),
    ("float",),
    ("double",),
    ("__int128",),
    ("__int128_t",),
    ("__uint128_t",),
)

TYPE_SPECIFIER_WORDS = {
    word for pattern in TYPE_ALIAS_PATTERNS for word in pattern
}

STD_PACK_ALIAS_TEMPLATES = {
    "allocator": "memory",
    "basic_string": "string",
    "basic_string_view": "string_view",
    "complex": "complex",
    "deque": "deque",
    "forward_list": "forward_list",
    "function": "functional",
    "list": "list",
    "map": "map",
    "multimap": "map",
    "multiset": "set",
    "optional": "optional",
    "pair": "utility",
    "priority_queue": "queue",
    "queue": "queue",
    "set": "set",
    "shared_ptr": "memory",
    "stack": "stack",
    "tuple": "tuple",
    "unique_ptr": "memory",
    "unordered_map": "unordered_map",
    "unordered_multimap": "unordered_map",
    "unordered_multiset": "unordered_set",
    "unordered_set": "unordered_set",
    "valarray": "valarray",
    "variant": "variant",
    "vector": "vector",
    "weak_ptr": "memory",
}

STD_NAMESPACE_HEADERS = set(STD_PACK_ALIAS_TEMPLATES.values()) | {
    "algorithm", "any", "array", "atomic", "barrier", "bit", "bitset",
    "charconv", "chrono", "compare", "concepts", "condition_variable",
    "coroutine", "exception", "execution", "filesystem", "format",
    "fstream", "future", "initializer_list", "iomanip", "ios", "iosfwd",
    "iostream", "istream", "iterator", "latch", "limits", "locale",
    "mutex", "new", "numbers", "numeric", "ostream", "random", "ranges",
    "ratio", "regex", "scoped_allocator", "semaphore", "source_location",
    "span", "sstream", "stdexcept", "stop_token", "streambuf", "syncstream",
    "system_error", "thread", "type_traits", "typeindex", "typeinfo",
}

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


@dataclass(frozen=True)
class Alias:
    kind: str
    original: tuple[str, ...]
    name: str
    positions: frozenset[int]
    parameter: str = ""
    insertion: int = -1


def _short_names():
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


def _matching_template_left(tokens: list[Token], right: int) -> int | None:
    """Match a closing template bracket, including lexed ``>>`` tokens."""
    depth = 0
    for i in range(right, -1, -1):
        if tokens[i].text == ">":
            depth += 1
        elif tokens[i].text == ">>":
            depth += 2
        elif tokens[i].text == "<":
            depth -= 1
            if depth == 0:
                return i
    return None


def _qualified_owner_name(tokens: list[Token], member: int) -> str:
    """Return the identifier naming the qualifier before ``::member``."""
    owner = member - 2
    if owner < 0:
        return ""
    if tokens[owner].text in {">", ">>"}:
        left = _matching_template_left(tokens, owner)
        owner = -1 if left is None else left - 1
    if owner >= 0 and tokens[owner].kind == "identifier":
        return tokens[owner].text
    return ""


def _known_types(tokens: list[Token]) -> set[str]:
    known = set(BUILTIN_TYPES) | set(COMMON_TYPES) | _declared_type_names(tokens)
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


def _declared_type_names(tokens: list[Token]) -> set[str]:
    """Collect types declared by this translation unit and safe to rename."""
    result: set[str] = set()
    for i, token in enumerate(tokens):
        if token.kind != "identifier":
            continue
        previous = tokens[i - 1].text if i else ""
        following = tokens[i + 1].text if i + 1 < len(tokens) else ""
        if previous in {"class", "struct", "union", "enum"}:
            result.add(token.text)
        if previous == "using" and following == "=":
            result.add(token.text)

    start = 0
    for i, token in enumerate(tokens):
        if token.text in {";", "{", "}"}:
            statement = tokens[start:i]
            if statement and statement[0].text == "typedef":
                identifiers = [t.text for t in statement if t.kind == "identifier"]
                if identifiers:
                    result.add(identifiers[-1])
            start = i + 1
    return result


def _declared_namespace_names(tokens: list[Token]) -> set[str]:
    """Collect namespace definitions owned by the translation unit."""
    result: set[str] = set()
    for i, token in enumerate(tokens[:-1]):
        if token.text != "namespace":
            continue
        j = i + 1
        components: list[str] = []
        while j < len(tokens):
            if tokens[j].kind == "identifier":
                components.append(tokens[j].text)
                j += 1
                if j < len(tokens) and tokens[j].text == "::":
                    j += 1
                    continue
            break
        # A namespace alias such as ``namespace s=std`` does not own members of
        # its target and must not make ``s::external_name`` eligible to rename.
        if j < len(tokens) and tokens[j].text == "{":
            result.update(components)
    result.discard("std")
    return result


def _direct_class_context(tokens: list[Token]) -> list[bool]:
    """Mark tokens whose innermost brace is a class/struct/union body."""
    result = [False] * len(tokens)
    stack: list[str] = []
    statement_start = 0
    for i, token in enumerate(tokens):
        result[i] = bool(stack and stack[-1] == "class")
        if token.text == "{":
            prefix = tokens[statement_start:i]
            class_keywords = [
                j for j, item in enumerate(prefix)
                if item.text in {"class", "struct", "union"}
            ]
            is_class = bool(class_keywords) and not any(
                item.text == ")" for item in prefix[class_keywords[-1] + 1:]
            )
            kind = "class" if is_class else "other"
            stack.append(kind)
            statement_start = i + 1
        elif token.text == "}":
            if stack:
                stack.pop()
            statement_start = i + 1
        elif token.text == ";":
            statement_start = i + 1
    return result


def _direct_namespace_context(tokens: list[Token]) -> list[bool]:
    """Mark tokens whose innermost brace is an owned namespace body."""
    result = [False] * len(tokens)
    stack: list[str] = []
    statement_start = 0
    for i, token in enumerate(tokens):
        result[i] = bool(stack and stack[-1] == "namespace")
        if token.text == "{":
            prefix = tokens[statement_start:i]
            is_namespace = any(item.text == "namespace" for item in prefix)
            stack.append("namespace" if is_namespace else "other")
            statement_start = i + 1
        elif token.text == "}":
            if stack:
                stack.pop()
            statement_start = i + 1
        elif token.text == ";":
            statement_start = i + 1
    return result


def _parenthesis_depth(tokens: list[Token]) -> list[int]:
    result: list[int] = []
    depth = 0
    for token in tokens:
        result.append(depth)
        if token.text == "(":
            depth += 1
        elif token.text == ")":
            depth = max(0, depth - 1)
    return result


def _declared_enum_members(tokens: list[Token]) -> set[str]:
    """Collect enumerators declared by enums in this translation unit."""
    result: set[str] = set()
    for i, token in enumerate(tokens):
        if token.text != "enum":
            continue
        opening = i + 1
        while opening < len(tokens) and tokens[opening].text not in {"{", ";"}:
            opening += 1
        if opening >= len(tokens) or tokens[opening].text != "{":
            continue
        brace = paren = bracket = 0
        expect_name = True
        j = opening
        while j < len(tokens):
            text = tokens[j].text
            if text == "{":
                brace += 1
            elif text == "}":
                brace -= 1
                if brace == 0:
                    break
            elif brace == 1:
                if text == "(":
                    paren += 1
                elif text == ")":
                    paren = max(0, paren - 1)
                elif text == "[":
                    bracket += 1
                elif text == "]":
                    bracket = max(0, bracket - 1)
                elif text == "," and paren == bracket == 0:
                    expect_name = True
                elif (
                    expect_name
                    and tokens[j].kind == "identifier"
                    and text not in CPP_KEYWORDS
                ):
                    result.add(text)
                    expect_name = False
            j += 1
    return result


def _type_before(tokens: list[Token], index: int, known_types: set[str]) -> bool:
    j = index - 1
    while j >= 0 and tokens[j].text in CV_AND_POINTER:
        j -= 1
    if j < 0:
        return False
    if tokens[j].text in BUILTIN_TYPES or tokens[j].text in known_types:
        return True
    if tokens[j].text in {">", ">>"}:
        left = _matching_template_left(tokens, j)
        return left is not None and left > 0 and tokens[left - 1].kind == "identifier"
    if (
        tokens[j].kind == "identifier"
        and j > 0
        and tokens[j - 1].text == "::"
    ):
        return True
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


def _directive_macro_names(tokens: list[Token]) -> set[str]:
    result: set[str] = set()
    for token in tokens:
        if token.kind != "directive":
            continue
        match = re.match(
            r"(?:#|%:)\s*(?:define|undef)\s+"
            r"((?:[^\W\d]|[_$])(?:\w|[$])*)",
            token.text,
        )
        if match is not None:
            result.add(match.group(1))
    return result


def _is_line_control_directive(token: Token) -> bool:
    if token.kind != "directive":
        return False
    return re.match(
        r"(?:#|%:)\s*(?:line\b|[0-9]+(?:\s|$))", token.text
    ) is not None


def _directive_keyword(text: str) -> str:
    match = re.match(r"(?:#|%:)\s*([A-Za-z_][A-Za-z_0-9]*)", text)
    return match.group(1) if match else ""


def _direct_include_operand(text: str) -> str | None:
    match = re.match(
        r'(?:#|%:)\s*include\s*(<[^>\n]+>|"(?:\\.|[^"\n])+")\s*$',
        text,
    )
    return match.group(1) if match else None


def _filter_directives(tokens: list[Token]) -> list[Token]:
    """Drop line controls and duplicate unconditional direct includes."""
    result: list[Token] = []
    seen_includes: set[str] = set()
    conditional_depth = 0
    for token in tokens:
        if _is_line_control_directive(token):
            continue
        if token.kind != "directive":
            result.append(token)
            continue

        keyword = _directive_keyword(token.text)
        if keyword == "endif":
            conditional_depth = max(0, conditional_depth - 1)

        if keyword == "include" and conditional_depth == 0:
            operand = _direct_include_operand(token.text)
            if operand is not None:
                if operand in seen_includes:
                    continue
                seen_includes.add(operand)

        result.append(token)
        if keyword in {"if", "ifdef", "ifndef"}:
            conditional_depth += 1
    return result


def _variable_rename_plan(
    tokens: list[Token],
) -> tuple[dict[str, str], frozenset[int]]:
    """Build replacements and positions that refer to external names."""
    known_types = _known_types(tokens)
    declared_types = _declared_type_names(tokens)
    declared_namespaces = _declared_namespace_names(tokens)
    enum_members = _declared_enum_members(tokens)
    class_context = _direct_class_context(tokens)
    namespace_context = _direct_namespace_context(tokens)
    parenthesis_depth = _parenthesis_depth(tokens)
    candidates: set[str] = set()
    declaration_indices: list[int] = []
    field_names: set[str] = set()

    for i, token in enumerate(tokens):
        if token.kind == "identifier" and token.text not in CPP_KEYWORDS:
            if _type_before(tokens, i, known_types):
                candidates.add(token.text)
                declaration_indices.append(i)
                if (
                    class_context[i]
                    and parenthesis_depth[i] == 0
                    and (i + 1 >= len(tokens) or tokens[i + 1].text != "(")
                ):
                    field_names.add(token.text)

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

    candidates.update(declared_types)
    candidates.update(declared_namespaces)
    candidates.update(enum_members)
    function_names = {
        tokens[i].text for i in declaration_indices
        if i + 1 < len(tokens) and tokens[i + 1].text == "("
    }
    namespace_variables = {
        tokens[i].text for i in declaration_indices
        if namespace_context[i]
        and (i + 1 >= len(tokens) or tokens[i + 1].text != "(")
    }

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
                        if class_context[declaration]:
                            field_names.add(name)
            i += 1

    protected = (
        _directive_identifiers(tokens)
        | (known_types - declared_types)
        | CPP_KEYWORDS
        | {"main"}
    )
    protected.update(
        field_names
        & (
            CONVENTIONAL_EXTERNAL_DOT_MEMBERS
            | CONVENTIONAL_EXTERNAL_QUALIFIED_MEMBERS
        )
    )
    protected.update(
        (declared_types | enum_members)
        & CONVENTIONAL_EXTERNAL_QUALIFIED_MEMBERS
    )
    excluded_positions: set[int] = set()
    for i, token in enumerate(tokens):
        if token.kind != "identifier":
            continue
        previous = tokens[i - 1].text if i else ""
        following = tokens[i + 1].text if i + 1 < len(tokens) else ""
        owned_type = token.text in declared_types
        owned_namespace = token.text in declared_namespaces
        owned_field = token.text in field_names
        owned_member = owned_field or token.text in enum_members
        owned_function = token.text in function_names
        if previous in {".", "->"} and (
            token.text in CONVENTIONAL_EXTERNAL_DOT_MEMBERS
            or not (owned_field or owned_type)
        ):
            excluded_positions.add(i)
        if previous in {".", "->"} and following == "(":
            excluded_positions.add(i)
            if owned_function:
                # Without receiver-type information, a locally declared method
                # cannot be distinguished from an external method at call sites.
                protected.add(token.text)
        if previous == "::":
            qualifier = _qualified_owner_name(tokens, i)
            qualifier_owned = (
                qualifier in declared_types or qualifier in declared_namespaces
            )
            conventional_external = (
                token.text in CONVENTIONAL_EXTERNAL_QUALIFIED_MEMBERS
                and qualifier not in declared_namespaces
            )
            if conventional_external or not qualifier_owned or not (
                owned_type
                or owned_namespace
                or owned_member
                or owned_function
                or token.text in namespace_variables
            ):
                excluded_positions.add(i)
        if previous in {"goto", "typedef"}:
            protected.add(token.text)
        if previous in {"class", "struct", "union", "enum"} and not owned_type:
            excluded_positions.add(i)
        if previous == "namespace" and not owned_namespace:
            excluded_positions.add(i)
        if previous == "using" and not (owned_type or owned_namespace):
            excluded_positions.add(i)
        if following == "::" and not (owned_type or owned_namespace):
            excluded_positions.add(i)
        if following == ":" and token.text not in candidates:
            protected.add(token.text)
        if following == "(" and not (
            owned_type or owned_member or owned_function or token.text in candidates
        ):
            excluded_positions.add(i)
        if token.text.startswith("__") or (token.text.startswith("_") and len(token.text) > 1 and token.text[1].isupper()):
            protected.add(token.text)

    # Keep declarations whose spelling participates in an external contract.
    for i in declaration_indices:
        start = i - 1
        while start >= 0 and tokens[start].text not in {";", "{", "}"}:
            start -= 1
        prefix = tokens[start + 1:i]
        if any(token.text == "extern" for token in prefix):
            protected.add(tokens[i].text)
        if i + 1 >= len(tokens) or tokens[i + 1].text != "(":
            continue
        end = i + 1
        while end < len(tokens) and tokens[end].text not in {";", "{"}:
            end += 1
        declaration = tokens[start + 1:end]
        if any(token.text in {"override", "final"} for token in declaration):
            protected.add(tokens[i].text)

    candidates -= protected
    counts: dict[str, int] = {}
    for i, token in enumerate(tokens):
        if (
            i not in excluded_positions
            and token.kind == "identifier"
            and token.text in candidates
        ):
            counts[token.text] = counts.get(token.text, 0) + 1

    unavailable = {
        token.text for token in tokens if token.kind == "identifier"
    } | CPP_KEYWORDS

    names = _short_names()
    renames: dict[str, str] = {}
    for old in sorted(candidates, key=lambda name: (-counts.get(name, 0), -len(name), name)):
        new = next(names)
        while new in unavailable or new in renames.values():
            new = next(names)
        if len(new) < len(old):
            renames[old] = new
    return renames, frozenset(excluded_positions)


def variable_renames(tokens: list[Token]) -> dict[str, str]:
    """Return the spelling map for file-owned C++ names."""
    return _variable_rename_plan(tokens)[0]


def _pattern_positions(tokens: list[Token], pattern: tuple[str, ...]) -> list[int]:
    """Find maximal builtin type spellings equal to ``pattern``."""
    result: list[int] = []
    width = len(pattern)
    for i in range(len(tokens) - width + 1):
        if tuple(token.text for token in tokens[i:i + width]) != pattern:
            continue
        previous = tokens[i - 1].text if i else ""
        following = tokens[i + width].text if i + width < len(tokens) else ""
        if previous in TYPE_SPECIFIER_WORDS or following in TYPE_SPECIFIER_WORDS:
            continue
        result.append(i)
    return result


def _qualified_template_positions(tokens: list[Token], name: str) -> list[int]:
    pattern = ("std", "::", name, "<")
    return [
        i for i in range(len(tokens) - len(pattern) + 1)
        if tuple(token.text for token in tokens[i:i + len(pattern)]) == pattern
    ]


def _standard_header_insertions(tokens: list[Token]) -> dict[str, int]:
    """Return safe global insertion points after unconditional angle includes."""
    result: dict[str, int] = {}
    conditional_depth = 0
    brace_depth = 0
    for i, token in enumerate(tokens):
        if token.kind == "directive":
            keyword = _directive_keyword(token.text)
            if keyword == "endif":
                conditional_depth = max(0, conditional_depth - 1)
            if (
                keyword == "include"
                and conditional_depth == 0
                and brace_depth == 0
            ):
                operand = _direct_include_operand(token.text)
                if operand is not None and operand.startswith("<"):
                    result.setdefault(operand[1:-1], i + 1)
            if keyword in {"if", "ifdef", "ifndef"}:
                conditional_depth += 1
            continue
        if token.text == "{":
            brace_depth += 1
        elif token.text == "}":
            brace_depth = max(0, brace_depth - 1)
    return result


def _leading_directive_end(tokens: list[Token]) -> tuple[int, bool, bool]:
    """Return the initial directive-block end and namespace-alias safety."""
    i = 0
    saw_include = False
    conditional = False
    while i < len(tokens) and tokens[i].kind == "directive":
        directive = tokens[i].text
        match = re.match(r"(?:#|%:)\s*([A-Za-z_][A-Za-z_0-9]*)", directive)
        keyword = match.group(1) if match else ""
        saw_include |= keyword == "include"
        conditional |= keyword in {"if", "ifdef", "ifndef", "elif", "else", "endif"}
        i += 1
    return i, saw_include and not conditional, not conditional


def _compression_aliases(
    tokens: list[Token], renames: dict[str, str]
) -> tuple[list[Alias], int, int]:
    """Choose profitable type aliases and well-known namespace aliases."""
    # Declarations before/among module directives have strict placement rules.
    if any(token.text == "module" for token in tokens):
        return [], 0, 0
    directive_names = _directive_identifiers(tokens)
    macro_names = _directive_macro_names(tokens)
    candidates: list[
        tuple[str, tuple[str, ...], list[int], int, int, str, int]
    ] = []

    for pattern in TYPE_ALIAS_PATTERNS:
        if any(word in directive_names for word in pattern):
            continue
        positions = _pattern_positions(tokens, pattern)
        if not positions:
            continue
        spelling_length = sum(map(len, pattern)) + len(pattern) - 1
        candidates.append(
            (
                "type", pattern, positions, spelling_length,
                7 + spelling_length, "", -1,
            )
        )

    leading_end, _, type_aliases_safe = _leading_directive_end(tokens)
    header_insertions = _standard_header_insertions(tokens)
    umbrella_insertions = [
        header_insertions[header]
        for header in ("bits/stdc++.h", "bits/extc++.h")
        if header in header_insertions
    ]
    parameter = next(
        name for name in ("T", "U", "V", "X", "_")
        if name not in directive_names
    )
    for template_name, header in STD_PACK_ALIAS_TEMPLATES.items():
        if template_name in macro_names or "std" in macro_names:
            continue
        insertions = list(umbrella_insertions)
        if header in header_insertions:
            insertions.append(header_insertions[header])
        if not insertions:
            continue
        insertion = min(insertions)
        positions = [
            position
            for position in _qualified_template_positions(tokens, template_name)
            if position >= insertion
        ]
        if not positions:
            continue
        original = ("std", "::", template_name)
        spelling_length = len("std::") + len(template_name)
        declaration_without_name = (
            f"template<class...{parameter}>using "
            f"=std::{template_name}<{parameter}...>;"
        )
        candidates.append(
            (
                "template",
                original,
                positions,
                spelling_length,
                len(declaration_without_name),
                parameter,
                insertion,
            )
        )

    namespace_insertions = {
        "std": [
            insertion for header, insertion in header_insertions.items()
            if header in STD_NAMESPACE_HEADERS
            or header in {"bits/stdc++.h", "bits/extc++.h"}
        ],
        "boost": [
            insertion for header, insertion in header_insertions.items()
            if header.startswith("boost/")
        ],
    }
    for namespace in ("std", "boost"):
        if namespace in macro_names or not namespace_insertions[namespace]:
            continue
        all_positions = [
            i for i, token in enumerate(tokens)
            if token.kind == "identifier" and token.text == namespace
        ]
        if not all_positions or any(
            i + 1 >= len(tokens) or tokens[i + 1].text != "::"
            for i in all_positions
        ):
            continue
        insertion = min(namespace_insertions[namespace])
        positions = [position for position in all_positions if position >= insertion]
        if not positions:
            continue
        candidates.append(
            (
                "namespace", (namespace,), positions,
                len(namespace), 12 + len(namespace), "", insertion,
            )
        )

    occupied = {
        token.text for token in tokens if token.kind == "identifier"
    } | directive_names | CPP_KEYWORDS | set(renames.values())
    names = _short_names()
    aliases: list[Alias] = []
    while candidates:
        name = next(names)
        while name in occupied:
            name = next(names)
        best_index = -1
        best_saving = 0
        for i, candidate in enumerate(candidates):
            _, _, positions, spelling_length, declaration_base, _, _ = candidate
            saving = (
                len(positions) * (spelling_length - len(name))
                - declaration_base
                - len(name)
            )
            if saving > best_saving:
                best_saving = saving
                best_index = i
        if best_index == -1:
            break
        kind, original, positions, _, _, parameter, insertion = candidates.pop(
            best_index
        )
        aliases.append(
            Alias(
                kind, original, name, frozenset(positions), parameter, insertion
            )
        )
        occupied.add(name)

    template_positions = {
        position for alias in aliases if alias.kind == "template"
        for position in alias.positions
    }
    adjusted: list[Alias] = []
    for alias in aliases:
        if alias.kind != "namespace" or alias.original != ("std",):
            adjusted.append(alias)
            continue
        positions = alias.positions - template_positions
        declaration_length = 12 + len(alias.name) + len(alias.original[0])
        saving = len(positions) * (len("std") - len(alias.name))
        if saving > declaration_length:
            adjusted.append(
                Alias(
                    alias.kind, alias.original, alias.name, positions,
                    alias.parameter, alias.insertion,
                )
            )
    aliases = adjusted

    type_insert = leading_end if type_aliases_safe else 0
    namespace_insert = leading_end
    return aliases, type_insert, namespace_insert


def _alias_declaration(alias: Alias) -> list[Token]:
    original = " ".join(alias.original)
    if alias.kind == "namespace":
        return tokenize(f"namespace {alias.name}={original};")
    if alias.kind == "template":
        template_name = alias.original[-1]
        parameter = alias.parameter
        return tokenize(
            f"template<class...{parameter}>using {alias.name}="
            f"std::{template_name}<{parameter}...>;"
        )
    return tokenize(f"using {alias.name}={original};")


def _alias_key(alias: Alias) -> str:
    if alias.kind == "template":
        return "".join(alias.original)
    return " ".join(alias.original)


def _transform_tokens(
    tokens: list[Token], renames: dict[str, str], aliases: list[Alias],
    type_insert: int, namespace_insert: int,
    rename_exclusions: frozenset[int] = frozenset(),
) -> list[Token]:
    injections: dict[int, list[Token]] = {}
    for alias in aliases:
        index = (
            alias.insertion
            if alias.insertion >= 0
            else namespace_insert
            if alias.kind in {"namespace", "template"}
            else type_insert
        )
        injections.setdefault(index, []).extend(_alias_declaration(alias))

    type_at: dict[int, Alias] = {}
    namespace_at: dict[int, Alias] = {}
    for alias in aliases:
        destination = namespace_at if alias.kind == "namespace" else type_at
        for position in alias.positions:
            destination[position] = alias

    result: list[Token] = []
    i = 0
    while i < len(tokens):
        result.extend(injections.get(i, ()))
        if i in type_at:
            alias = type_at[i]
            result.append(Token("identifier", alias.name))
            i += len(alias.original)
            continue

        token = tokens[i]
        if i in namespace_at:
            token = Token("identifier", namespace_at[i].name)
        elif (
            i not in rename_exclusions
            and token.kind == "identifier"
            and token.text in renames
        ):
            token = Token(token.kind, renames[token.text])
        result.append(token)
        i += 1
    result.extend(injections.get(len(tokens), ()))
    return result


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
    tokens = _filter_directives(tokenize(source))
    rename_exclusions: frozenset[int] = frozenset()
    if rename:
        renames, rename_exclusions = _variable_rename_plan(tokens)
    else:
        renames = {}
    aliases: list[Alias] = []
    type_insert = namespace_insert = 0
    if rename:
        aliases, type_insert, namespace_insert = _compression_aliases(tokens, renames)
        tokens = _transform_tokens(
            tokens, renames, aliases, type_insert, namespace_insert,
            rename_exclusions,
        )
        for alias in aliases:
            renames[_alias_key(alias)] = alias.name
    output: list[str] = []
    previous: Token | None = None

    for token in tokens:
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
    parser.add_argument("--stats", action="store_true", help="print size and name-compression statistics to stderr")
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
            f"renamed/aliased {len(renames)} names",
            file=sys.stderr,
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
