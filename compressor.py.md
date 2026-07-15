---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 96, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "#!/usr/bin/env python3\n\"\"\"A small, dependency-free C++ source minifier\
    \ for contest submissions.\n\nThe minifier removes comments and whitespace without\
    \ changing the C++ token\nstream.  By default it also shortens identifiers which\
    \ look like variable\ndeclarations.  Renaming is deliberately conservative: macros,\
    \ types,\nfunctions, labels, qualified names, and member names are left alone.\n\
    \"\"\"\n\nfrom __future__ import annotations\n\nimport argparse\nimport re\nimport\
    \ sys\nfrom dataclasses import dataclass\nfrom pathlib import Path\n\n\nCPP_KEYWORDS\
    \ = {\n    \"alignas\", \"alignof\", \"and\", \"and_eq\", \"asm\", \"auto\", \"\
    bitand\",\n    \"bitor\", \"bool\", \"break\", \"case\", \"catch\", \"char\",\
    \ \"char8_t\",\n    \"char16_t\", \"char32_t\", \"class\", \"compl\", \"concept\"\
    , \"const\",\n    \"consteval\", \"constexpr\", \"constinit\", \"const_cast\"\
    , \"continue\",\n    \"co_await\", \"co_return\", \"co_yield\", \"decltype\",\
    \ \"default\", \"delete\",\n    \"do\", \"double\", \"dynamic_cast\", \"else\"\
    , \"enum\", \"explicit\", \"export\",\n    \"extern\", \"false\", \"float\", \"\
    for\", \"friend\", \"goto\", \"if\", \"inline\",\n    \"int\", \"long\", \"mutable\"\
    , \"namespace\", \"new\", \"noexcept\", \"not\",\n    \"not_eq\", \"nullptr\"\
    , \"operator\", \"or\", \"or_eq\", \"private\", \"protected\",\n    \"public\"\
    , \"register\", \"reinterpret_cast\", \"requires\", \"return\", \"short\",\n \
    \   \"signed\", \"sizeof\", \"static\", \"static_assert\", \"static_cast\", \"\
    struct\",\n    \"switch\", \"template\", \"this\", \"thread_local\", \"throw\"\
    , \"true\", \"try\",\n    \"typedef\", \"typeid\", \"typename\", \"union\", \"\
    unsigned\", \"using\", \"virtual\",\n    \"void\", \"volatile\", \"wchar_t\",\
    \ \"while\", \"xor\", \"xor_eq\", \"import\",\n    \"module\",\n}\n\nBUILTIN_TYPES\
    \ = {\n    \"auto\", \"bool\", \"char\", \"char8_t\", \"char16_t\", \"char32_t\"\
    , \"double\",\n    \"float\", \"int\", \"long\", \"short\", \"signed\", \"unsigned\"\
    , \"void\",\n    \"wchar_t\", \"size_t\", \"ptrdiff_t\", \"int8_t\", \"int16_t\"\
    , \"int32_t\",\n    \"int64_t\", \"uint8_t\", \"uint16_t\", \"uint32_t\", \"uint64_t\"\
    , \"__int128\",\n    \"__int128_t\", \"__uint128_t\",\n}\n\nCOMMON_TYPES = {\n\
    \    \"array\", \"bitset\", \"deque\", \"function\", \"initializer_list\", \"\
    list\",\n    \"map\", \"multimap\", \"multiset\", \"optional\", \"pair\", \"priority_queue\"\
    ,\n    \"queue\", \"set\", \"span\", \"stack\", \"string\", \"string_view\", \"\
    tuple\",\n    \"unordered_map\", \"unordered_multimap\", \"unordered_multiset\"\
    ,\n    \"unordered_set\", \"variant\", \"vector\",\n}\n\nCV_AND_POINTER = {\"\
    const\", \"volatile\", \"constexpr\", \"static\", \"mutable\", \"*\", \"&\", \"\
    &&\"}\n\nPUNCTUATORS = (\n    \"%:%:\", \"<<=\", \">>=\", \"<=>\", \"->*\", \"\
    ...\", \"##\", \"::\", \".*\", \"->\",\n    \"++\", \"--\", \"<<\", \">>\", \"\
    <=\", \">=\", \"==\", \"!=\", \"&&\", \"||\", \"*=\",\n    \"/=\", \"%=\", \"\
    +=\", \"-=\", \"&=\", \"^=\", \"|=\", \"<:\", \":>\", \"<%\", \"%>\",\n    \"\
    %:\", \"{\", \"}\", \"[\", \"]\", \"(\", \")\", \"#\", \";\", \":\", \"?\", \"\
    .\", \"+\",\n    \"-\", \"*\", \"/\", \"%\", \"^\", \"&\", \"|\", \"~\", \"!\"\
    , \"=\", \"<\", \">\", \",\",\n)\n\n\n@dataclass(frozen=True)\nclass Token:\n\
    \    kind: str\n    text: str\n\n\ndef _is_identifier_start(ch: str) -> bool:\n\
    \    # '$' is a widely supported GCC/Clang extension and is useful to recognize\n\
    \    # even though portable C++ identifiers do not contain it.\n    return ch\
    \ in \"_$\" or ch.isalpha() or (ord(ch) >= 128 and not ch.isspace())\n\n\ndef\
    \ _is_identifier_continue(ch: str) -> bool:\n    return _is_identifier_start(ch)\
    \ or ch.isdigit()\n\n\ndef _number_end(source: str, start: int) -> int:\n    \"\
    \"\"Return the end of a preprocessing number starting at ``start``.\"\"\"\n  \
    \  i = start + 1\n    while i < len(source):\n        current = source[i]\n  \
    \      if _is_identifier_continue(current) or current == \".\":\n            i\
    \ += 1\n        elif (\n            current == \"'\"\n            and i + 1 <\
    \ len(source)\n            and _is_identifier_continue(source[i + 1])\n      \
    \  ):\n            i += 2\n        elif current in \"+-\" and source[i - 1] in\
    \ \"eEpP\":\n            i += 1\n        else:\n            break\n    return\
    \ i\n\n\ndef _raw_literal_bounds(source: str, start: int) -> tuple[int, int, int]\
    \ | None:\n    \"\"\"Return ``(open_paren, close_paren, end)`` for a raw literal.\"\
    \"\"\n    prefixes = (\"u8R\\\"\", \"uR\\\"\", \"UR\\\"\", \"LR\\\"\", \"R\\\"\
    \")\n    raw_prefix = next((p for p in prefixes if source.startswith(p, start)),\
    \ None)\n    if raw_prefix is None:\n        return None\n    delimiter_start\
    \ = start + len(raw_prefix)\n    open_paren = source.find(\"(\", delimiter_start)\n\
    \    if open_paren == -1 or open_paren - delimiter_start > 16:\n        return\
    \ None\n    delimiter = source[delimiter_start:open_paren]\n    if any(ch.isspace()\
    \ or ch in \"()\\\\\" for ch in delimiter):\n        return None\n    close_paren\
    \ = source.find(\")\" + delimiter + \"\\\"\", open_paren + 1)\n    if close_paren\
    \ == -1:\n        return None\n    end = close_paren + len(delimiter) + 2\n  \
    \  while end < len(source) and _is_identifier_continue(source[end]):\n       \
    \ end += 1\n    return open_paren, close_paren, end\n\n\ndef _quoted_end(source:\
    \ str, start: int) -> int | None:\n    \"\"\"Return the end of a string/character/raw\
    \ literal starting at start.\n\n    An immediately adjacent user-defined-literal\
    \ suffix is part of the token.\n    \"\"\"\n    raw_bounds = _raw_literal_bounds(source,\
    \ start)\n    if raw_bounds is not None:\n        return raw_bounds[2]\n    if\
    \ any(source.startswith(p, start) for p in (\"u8R\\\"\", \"uR\\\"\", \"UR\\\"\"\
    , \"LR\\\"\", \"R\\\"\")):\n        # It looks like a raw literal but is malformed\
    \ or unterminated.  The\n        # compiler will diagnose it; treating the remainder\
    \ as one token keeps\n        # the minifier from compounding the error.\n   \
    \     return len(source)\n\n    prefixes = (\"u8\\\"\", \"u\\\"\", \"U\\\"\",\
    \ \"L\\\"\", \"\\\"\", \"u'\", \"U'\", \"L'\", \"'\")\n    prefix = next((p for\
    \ p in prefixes if source.startswith(p, start)), None)\n    if prefix is None:\n\
    \        return None\n    quote = prefix[-1]\n    i = start + len(prefix)\n  \
    \  while i < len(source):\n        if source[i] == \"\\\\\":\n            i +=\
    \ 2\n        elif source[i] == quote:\n            end = i + 1\n            while\
    \ end < len(source) and _is_identifier_continue(source[end]):\n              \
    \  end += 1\n            return end\n        else:\n            i += 1\n    return\
    \ len(source)\n\n\ndef _splice_lines(source: str) -> str:\n    \"\"\"Perform phase-2\
    \ line splicing while restoring raw-string contents.\"\"\"\n    spliced: list[str]\
    \ = []\n    origins: list[int] = []\n    i = 0\n    while i < len(source):\n \
    \       if source[i] == \"\\\\\":\n            if source.startswith(\"\\r\\n\"\
    , i + 1):\n                i += 3\n                continue\n            if i\
    \ + 1 < len(source) and source[i + 1] in \"\\r\\n\":\n                i += 2\n\
    \                continue\n        spliced.append(source[i])\n        origins.append(i)\n\
    \        i += 1\n\n    phase_two = \"\".join(spliced)\n    output: list[str] =\
    \ []\n    copied_until = 0\n    i = 0\n    while i < len(phase_two):\n       \
    \ if phase_two.startswith(\"//\", i):\n            newline = phase_two.find(\"\
    \\n\", i + 2)\n            i = len(phase_two) if newline == -1 else newline\n\
    \            continue\n        if phase_two.startswith(\"/*\", i):\n         \
    \   close = phase_two.find(\"*/\", i + 2)\n            i = len(phase_two) if close\
    \ == -1 else close + 2\n            continue\n        if phase_two[i].isdigit()\
    \ or (\n            phase_two[i] == \".\"\n            and i + 1 < len(phase_two)\n\
    \            and phase_two[i + 1].isdigit()\n        ):\n            i = _number_end(phase_two,\
    \ i)\n            continue\n\n        raw_bounds = _raw_literal_bounds(phase_two,\
    \ i)\n        if raw_bounds is not None:\n            open_paren, close_paren,\
    \ end = raw_bounds\n            output.append(phase_two[copied_until:open_paren\
    \ + 1])\n            original_open = origins[open_paren]\n            original_close\
    \ = origins[close_paren]\n            output.append(source[original_open + 1:original_close])\n\
    \            output.append(phase_two[close_paren:end])\n            copied_until\
    \ = end\n            i = end\n            continue\n\n        literal_end = _quoted_end(phase_two,\
    \ i)\n        if literal_end is not None:\n            i = literal_end\n     \
    \       continue\n        if _is_identifier_start(phase_two[i]):\n           \
    \ i += 1\n            while i < len(phase_two) and _is_identifier_continue(phase_two[i]):\n\
    \                i += 1\n            continue\n        i += 1\n\n    output.append(phase_two[copied_until:])\n\
    \    return \"\".join(output)\n\n\ndef _prepare_source(source: str) -> str:\n\
    \    \"\"\"Apply the translation phases needed before preprocessing-token lexing.\"\
    \"\"\n    # Line splicing precedes comment recognition.  C++ restores transformations\n\
    \    # within raw-string contents after recognizing the raw literal.\n    source\
    \ = source.replace(\"\\r\\n\", \"\\n\").replace(\"\\r\", \"\\n\")\n    source\
    \ = _splice_lines(source)\n\n    # Comments are replaced by one space in translation\
    \ phase 3.  In\n    # particular, newlines *inside* a block comment do not terminate\
    \ a\n    # preprocessing directive.\n    output: list[str] = []\n    i = 0\n \
    \   while i < len(source):\n        if source[i].isdigit() or (\n            source[i]\
    \ == \".\" and i + 1 < len(source) and source[i + 1].isdigit()\n        ):\n \
    \           end = _number_end(source, i)\n            output.append(source[i:end])\n\
    \            i = end\n            continue\n        literal_end = _quoted_end(source,\
    \ i)\n        if literal_end is not None:\n            output.append(source[i:literal_end])\n\
    \            i = literal_end\n            continue\n        if source.startswith(\"\
    //\", i):\n            output.append(\" \")\n            newline = source.find(\"\
    \\n\", i + 2)\n            i = len(source) if newline == -1 else newline\n   \
    \         continue\n        if source.startswith(\"/*\", i):\n            output.append(\"\
    \ \")\n            close = source.find(\"*/\", i + 2)\n            i = len(source)\
    \ if close == -1 else close + 2\n            continue\n        output.append(source[i])\n\
    \        i += 1\n    return \"\".join(output)\n\n\ndef _directive_end(source:\
    \ str, start: int) -> int:\n    \"\"\"Return the end of a preprocessing directive,\
    \ including its newline.\"\"\"\n    i = start\n    while i < len(source):\n  \
    \      if source[i] == \"\\n\":\n            return i + 1\n        if source[i].isdigit()\
    \ or (\n            source[i] == \".\" and i + 1 < len(source) and source[i +\
    \ 1].isdigit()\n        ):\n            i = _number_end(source, i)\n         \
    \   continue\n        literal_end = _quoted_end(source, i)\n        if literal_end\
    \ is not None:\n            i = literal_end\n            continue\n        if\
    \ _is_identifier_start(source[i]):\n            i += 1\n            while i <\
    \ len(source) and _is_identifier_continue(source[i]):\n                i += 1\n\
    \            continue\n        i += 1\n    return len(source)\n\n\ndef tokenize(source:\
    \ str) -> list[Token]:\n    source = _prepare_source(source)\n    tokens: list[Token]\
    \ = []\n    i = 0\n    at_line_start = True\n    n = len(source)\n\n    while\
    \ i < n:\n        ch = source[i]\n        if ch in \" \\t\\v\\f\\r\":\n      \
    \      i += 1\n            continue\n        if ch == \"\\n\":\n            at_line_start\
    \ = True\n            i += 1\n            continue\n\n        if at_line_start\
    \ and (ch == \"#\" or source.startswith(\"%:\", i)):\n            start = i\n\
    \            i = _directive_end(source, i)\n            tokens.append(Token(\"\
    directive\", source[start:i].rstrip()))\n            at_line_start = True\n  \
    \          continue\n\n        at_line_start = False\n        literal_end = _quoted_end(source,\
    \ i)\n        if literal_end is not None:\n            tokens.append(Token(\"\
    literal\", source[i:literal_end]))\n            i = literal_end\n            continue\n\
    \n        if _is_identifier_start(ch):\n            j = i + 1\n            while\
    \ j < n and _is_identifier_continue(source[j]):\n                j += 1\n    \
    \        tokens.append(Token(\"identifier\", source[i:j]))\n            i = j\n\
    \            continue\n\n        if ch.isdigit() or (ch == \".\" and i + 1 < n\
    \ and source[i + 1].isdigit()):\n            j = _number_end(source, i)\n    \
    \        tokens.append(Token(\"number\", source[i:j]))\n            i = j\n  \
    \          continue\n\n        punctuator = next((p for p in PUNCTUATORS if source.startswith(p,\
    \ i)), ch)\n        tokens.append(Token(\"punct\", punctuator))\n        i +=\
    \ len(punctuator)\n\n    return tokens\n\n\ndef _matching_left(tokens: list[Token],\
    \ right: int, opening: str, closing: str) -> int | None:\n    depth = 0\n    for\
    \ i in range(right, -1, -1):\n        if tokens[i].text == closing:\n        \
    \    depth += 1\n        elif tokens[i].text == opening:\n            depth -=\
    \ 1\n            if depth == 0:\n                return i\n    return None\n\n\
    \ndef _known_types(tokens: list[Token]) -> set[str]:\n    known = set(BUILTIN_TYPES)\
    \ | set(COMMON_TYPES)\n    for i, token in enumerate(tokens):\n        if token.kind\
    \ != \"identifier\":\n            continue\n        previous = tokens[i - 1].text\
    \ if i else \"\"\n        if previous in {\"class\", \"struct\", \"union\", \"\
    enum\", \"typename\"}:\n            known.add(token.text)\n        if previous\
    \ == \"using\" and i + 1 < len(tokens) and tokens[i + 1].text == \"=\":\n    \
    \        known.add(token.text)\n\n    # In a typedef declaration, the final identifier\
    \ is the new type name.\n    start = 0\n    for i, token in enumerate(tokens):\n\
    \        if token.text in {\";\", \"{\", \"}\"}:\n            statement = tokens[start:i]\n\
    \            if statement and statement[0].text == \"typedef\":\n            \
    \    identifiers = [t.text for t in statement if t.kind == \"identifier\"]\n \
    \               if identifiers:\n                    known.add(identifiers[-1])\n\
    \            start = i + 1\n    return known\n\n\ndef _type_before(tokens: list[Token],\
    \ index: int, known_types: set[str]) -> bool:\n    j = index - 1\n    while j\
    \ >= 0 and tokens[j].text in CV_AND_POINTER:\n        j -= 1\n    if j < 0:\n\
    \        return False\n    if tokens[j].text in BUILTIN_TYPES or tokens[j].text\
    \ in known_types:\n        return True\n    if tokens[j].text == \">\":\n    \
    \    left = _matching_left(tokens, j, \"<\", \">\")\n        return left is not\
    \ None and left > 0 and tokens[left - 1].kind == \"identifier\"\n    if tokens[j].text\
    \ == \")\":\n        left = _matching_left(tokens, j, \"(\", \")\")\n        return\
    \ left is not None and left > 0 and tokens[left - 1].text == \"decltype\"\n  \
    \  return False\n\n\ndef _directive_identifiers(tokens: list[Token]) -> set[str]:\n\
    \    result: set[str] = set()\n    for token in tokens:\n        if token.kind\
    \ == \"directive\":\n            result.update(re.findall(r\"(?:[^\\W\\d]|[_$])(?:\\\
    w|[$])*\", token.text))\n    return result\n\n\ndef variable_renames(tokens: list[Token])\
    \ -> dict[str, str]:\n    \"\"\"Build a conservative, global variable-name replacement\
    \ map.\"\"\"\n    known_types = _known_types(tokens)\n    candidates: set[str]\
    \ = set()\n    declaration_indices: list[int] = []\n\n    for i, token in enumerate(tokens):\n\
    \        if token.kind == \"identifier\" and token.text not in CPP_KEYWORDS:\n\
    \            if _type_before(tokens, i, known_types):\n                candidates.add(token.text)\n\
    \                declaration_indices.append(i)\n\n        # Structured bindings:\
    \ auto [long_name, other_name].\n        if token.text == \"[\":\n           \
    \ j = i - 1\n            while j >= 0 and tokens[j].text in CV_AND_POINTER:\n\
    \                j -= 1\n            if j >= 0 and tokens[j].text == \"auto\"\
    :\n                close = next((k for k in range(i + 1, len(tokens)) if tokens[k].text\
    \ == \"]\"), None)\n                if close is not None:\n                  \
    \  for item in tokens[i + 1:close]:\n                        if item.kind == \"\
    identifier\" and item.text not in CPP_KEYWORDS:\n                            candidates.add(item.text)\n\
    \n    # Add later declarators in declarations such as: int first = 0, second =\
    \ 1;\n    for declaration in declaration_indices:\n        paren = bracket = brace\
    \ = 0\n        i = declaration + 1\n        while i < len(tokens):\n         \
    \   text = tokens[i].text\n            if text == \"(\":\n                paren\
    \ += 1\n            elif text == \")\":\n                if paren == 0:\n    \
    \                break\n                paren -= 1\n            elif text == \"\
    [\":\n                bracket += 1\n            elif text == \"]\":\n        \
    \        bracket = max(0, bracket - 1)\n            elif text == \"{\":\n    \
    \            brace += 1\n            elif text == \"}\":\n                if brace\
    \ == 0:\n                    break\n                brace -= 1\n            elif\
    \ text == \";\" and paren == bracket == brace == 0:\n                break\n \
    \           elif text == \",\" and paren == bracket == brace == 0:\n         \
    \       j = i + 1\n                while j < len(tokens) and tokens[j].text in\
    \ CV_AND_POINTER:\n                    j += 1\n                if j < len(tokens)\
    \ and tokens[j].kind == \"identifier\":\n                    name = tokens[j].text\n\
    \                    if name not in known_types and name not in CPP_KEYWORDS:\n\
    \                        candidates.add(name)\n            i += 1\n\n    protected\
    \ = _directive_identifiers(tokens) | known_types | CPP_KEYWORDS | {\"main\"}\n\
    \    for i, token in enumerate(tokens):\n        if token.kind != \"identifier\"\
    :\n            continue\n        previous = tokens[i - 1].text if i else \"\"\n\
    \        following = tokens[i + 1].text if i + 1 < len(tokens) else \"\"\n   \
    \     if previous in {\".\", \"->\", \"::\", \"goto\", \"class\", \"struct\",\
    \ \"union\", \"enum\", \"namespace\", \"using\", \"typedef\"}:\n            protected.add(token.text)\n\
    \        if following in {\"::\", \":\"}:\n            protected.add(token.text)\n\
    \        if following == \"(\":\n            protected.add(token.text)\n     \
    \   if token.text.startswith(\"__\") or (token.text.startswith(\"_\") and len(token.text)\
    \ > 1 and token.text[1].isupper()):\n            protected.add(token.text)\n \
    \       if token.kind == \"identifier\" and previous and i > 0 and tokens[i -\
    \ 1].kind == \"literal\":\n            protected.add(token.text)\n\n    # A type\
    \ followed by name(...) is potentially a function declaration or a\n    # direct-initialization\
    \ ambiguity.  Leaving it untouched is the safe choice.\n    for i in declaration_indices:\n\
    \        if i + 1 < len(tokens) and tokens[i + 1].text == \"(\":\n           \
    \ protected.add(tokens[i].text)\n\n    candidates -= protected\n    counts: dict[str,\
    \ int] = {}\n    for token in tokens:\n        if token.kind == \"identifier\"\
    \ and token.text in candidates:\n            counts[token.text] = counts.get(token.text,\
    \ 0) + 1\n\n    unavailable = {\n        token.text for token in tokens if token.kind\
    \ == \"identifier\"\n    } | CPP_KEYWORDS\n\n    def short_names():\n        alphabet\
    \ = \"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\"\n        length =\
    \ 1\n        while True:\n            indices = [0] * length\n            while\
    \ True:\n                yield \"\".join(alphabet[index] for index in indices)\n\
    \                position = length - 1\n                while position >= 0 and\
    \ indices[position] == len(alphabet) - 1:\n                    indices[position]\
    \ = 0\n                    position -= 1\n                if position < 0:\n \
    \                   break\n                indices[position] += 1\n          \
    \  length += 1\n\n    names = short_names()\n    renames: dict[str, str] = {}\n\
    \    for old in sorted(candidates, key=lambda name: (-counts.get(name, 0), -len(name),\
    \ name)):\n        new = next(names)\n        while new in unavailable or new\
    \ in renames.values():\n            new = next(names)\n        if len(new) < len(old):\n\
    \            renames[old] = new\n    return renames\n\n\ndef _needs_space(previous:\
    \ Token, current: Token) -> bool:\n    if previous.kind == \"directive\" or current.kind\
    \ == \"directive\":\n        return False\n    # Re-lexing the boundary is more\
    \ reliable than maintaining a growing list\n    # of special cases for pp-numbers,\
    \ literal prefixes, digraphs, comments,\n    # and multi-character punctuators.\
    \  Each token participates in at most two\n    # such checks, so the total amount\
    \ of text examined remains linear.\n    combined = tokenize(previous.text + current.text)\n\
    \    return combined != [previous, current]\n\n\ndef minify(source: str, rename:\
    \ bool = True) -> tuple[str, dict[str, str]]:\n    tokens = tokenize(source)\n\
    \    renames = variable_renames(tokens) if rename else {}\n    output: list[str]\
    \ = []\n    previous: Token | None = None\n\n    for original in tokens:\n   \
    \     token = original\n        if token.kind == \"identifier\" and token.text\
    \ in renames:\n            token = Token(token.kind, renames[token.text])\n\n\
    \        if token.kind == \"directive\":\n            if output and not output[-1].endswith(\"\
    \\n\"):\n                output.append(\"\\n\")\n            output.append(token.text\
    \ + \"\\n\")\n            previous = None\n            continue\n        if previous\
    \ is not None and _needs_space(previous, token):\n            output.append(\"\
    \ \")\n        output.append(token.text)\n        previous = token\n\n    result\
    \ = \"\".join(output).rstrip()\n    return (result + \"\\n\" if result else \"\
    \"), renames\n\n\ndef main() -> int:\n    parser = argparse.ArgumentParser(description=\"\
    Minify C++ source code for contest submissions.\")\n    parser.add_argument(\"\
    input\", nargs=\"?\", type=Path, help=\"input file (default: stdin)\")\n    parser.add_argument(\"\
    -o\", \"--output\", type=Path, help=\"output file (default: stdout)\")\n    parser.add_argument(\"\
    --no-rename\", action=\"store_true\", help=\"only remove comments and whitespace\"\
    )\n    parser.add_argument(\"--stats\", action=\"store_true\", help=\"print size\
    \ and rename statistics to stderr\")\n    args = parser.parse_args()\n\n    source\
    \ = args.input.read_text(encoding=\"utf-8\") if args.input else sys.stdin.read()\n\
    \    result, renames = minify(source, rename=not args.no_rename)\n    if args.output:\n\
    \        args.output.write_text(result, encoding=\"utf-8\")\n    else:\n     \
    \   sys.stdout.write(result)\n\n    if args.stats:\n        source_size = len(source.encode(\"\
    utf-8\"))\n        result_size = len(result.encode(\"utf-8\"))\n        reduction\
    \ = 0.0 if not source_size else 100.0 * (source_size - result_size) / source_size\n\
    \        print(\n            f\"{source_size} -> {result_size} bytes ({reduction:.1f}%\
    \ smaller), \"\n            f\"renamed {len(renames)} identifiers\",\n       \
    \     file=sys.stderr,\n        )\n    return 0\n\n\nif __name__ == \"__main__\"\
    :\n    raise SystemExit(main())\n"
  dependsOn: []
  isVerificationFile: false
  path: compressor.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: compressor.py
layout: document
redirect_from:
- /library/compressor.py
- /library/compressor.py.html
title: compressor.py
---
