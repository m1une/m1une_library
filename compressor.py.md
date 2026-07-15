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
    \ changing the C++ token\nstream.  By default it also shortens file-owned variables,\
    \ fields, types,\nnamespaces, and unqualified functions, and introduces aliases\
    \ when their\ndeclaration cost is profitable.  Macros, reserved names, external\
    \ qualified\nnames and member calls, contract functions, and labels remain protected.\n\
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
    &&\"}\n\nCONVENTIONAL_EXTERNAL_DOT_MEMBERS = {\"first\", \"second\"}\nCONVENTIONAL_EXTERNAL_QUALIFIED_MEMBERS\
    \ = {\"type\", \"value\"}\n\nTYPE_ALIAS_PATTERNS = (\n    (\"unsigned\", \"long\"\
    , \"long\", \"int\"),\n    (\"signed\", \"long\", \"long\", \"int\"),\n    (\"\
    unsigned\", \"long\", \"long\"),\n    (\"signed\", \"long\", \"long\"),\n    (\"\
    long\", \"long\", \"int\"),\n    (\"long\", \"long\"),\n    (\"unsigned\", \"\
    long\", \"int\"),\n    (\"signed\", \"long\", \"int\"),\n    (\"unsigned\", \"\
    short\", \"int\"),\n    (\"signed\", \"short\", \"int\"),\n    (\"short\", \"\
    int\"),\n    (\"long\", \"int\"),\n    (\"unsigned\", \"char\"),\n    (\"signed\"\
    , \"char\"),\n    (\"unsigned\", \"long\"),\n    (\"signed\", \"long\"),\n   \
    \ (\"unsigned\", \"short\"),\n    (\"signed\", \"short\"),\n    (\"unsigned\"\
    , \"int\"),\n    (\"signed\", \"int\"),\n    (\"long\", \"double\"),\n    (\"\
    void\",),\n    (\"bool\",),\n    (\"char\",),\n    (\"char8_t\",),\n    (\"char16_t\"\
    ,),\n    (\"char32_t\",),\n    (\"wchar_t\",),\n    (\"short\",),\n    (\"int\"\
    ,),\n    (\"long\",),\n    (\"signed\",),\n    (\"unsigned\",),\n    (\"float\"\
    ,),\n    (\"double\",),\n    (\"__int128\",),\n    (\"__int128_t\",),\n    (\"\
    __uint128_t\",),\n)\n\nTYPE_SPECIFIER_WORDS = {\n    word for pattern in TYPE_ALIAS_PATTERNS\
    \ for word in pattern\n}\n\nSTD_PACK_ALIAS_TEMPLATES = {\n    \"allocator\": \"\
    memory\",\n    \"basic_string\": \"string\",\n    \"basic_string_view\": \"string_view\"\
    ,\n    \"complex\": \"complex\",\n    \"deque\": \"deque\",\n    \"forward_list\"\
    : \"forward_list\",\n    \"function\": \"functional\",\n    \"list\": \"list\"\
    ,\n    \"map\": \"map\",\n    \"multimap\": \"map\",\n    \"multiset\": \"set\"\
    ,\n    \"optional\": \"optional\",\n    \"pair\": \"utility\",\n    \"priority_queue\"\
    : \"queue\",\n    \"queue\": \"queue\",\n    \"set\": \"set\",\n    \"shared_ptr\"\
    : \"memory\",\n    \"stack\": \"stack\",\n    \"tuple\": \"tuple\",\n    \"unique_ptr\"\
    : \"memory\",\n    \"unordered_map\": \"unordered_map\",\n    \"unordered_multimap\"\
    : \"unordered_map\",\n    \"unordered_multiset\": \"unordered_set\",\n    \"unordered_set\"\
    : \"unordered_set\",\n    \"valarray\": \"valarray\",\n    \"variant\": \"variant\"\
    ,\n    \"vector\": \"vector\",\n    \"weak_ptr\": \"memory\",\n}\n\nSTD_NAMESPACE_HEADERS\
    \ = set(STD_PACK_ALIAS_TEMPLATES.values()) | {\n    \"algorithm\", \"any\", \"\
    array\", \"atomic\", \"barrier\", \"bit\", \"bitset\",\n    \"charconv\", \"chrono\"\
    , \"compare\", \"concepts\", \"condition_variable\",\n    \"coroutine\", \"exception\"\
    , \"execution\", \"filesystem\", \"format\",\n    \"fstream\", \"future\", \"\
    initializer_list\", \"iomanip\", \"ios\", \"iosfwd\",\n    \"iostream\", \"istream\"\
    , \"iterator\", \"latch\", \"limits\", \"locale\",\n    \"mutex\", \"new\", \"\
    numbers\", \"numeric\", \"ostream\", \"random\", \"ranges\",\n    \"ratio\", \"\
    regex\", \"scoped_allocator\", \"semaphore\", \"source_location\",\n    \"span\"\
    , \"sstream\", \"stdexcept\", \"stop_token\", \"streambuf\", \"syncstream\",\n\
    \    \"system_error\", \"thread\", \"type_traits\", \"typeindex\", \"typeinfo\"\
    ,\n}\n\nPUNCTUATORS = (\n    \"%:%:\", \"<<=\", \">>=\", \"<=>\", \"->*\", \"\
    ...\", \"##\", \"::\", \".*\", \"->\",\n    \"++\", \"--\", \"<<\", \">>\", \"\
    <=\", \">=\", \"==\", \"!=\", \"&&\", \"||\", \"*=\",\n    \"/=\", \"%=\", \"\
    +=\", \"-=\", \"&=\", \"^=\", \"|=\", \"<:\", \":>\", \"<%\", \"%>\",\n    \"\
    %:\", \"{\", \"}\", \"[\", \"]\", \"(\", \")\", \"#\", \";\", \":\", \"?\", \"\
    .\", \"+\",\n    \"-\", \"*\", \"/\", \"%\", \"^\", \"&\", \"|\", \"~\", \"!\"\
    , \"=\", \"<\", \">\", \",\",\n)\n\n\n@dataclass(frozen=True)\nclass Token:\n\
    \    kind: str\n    text: str\n\n\n@dataclass(frozen=True)\nclass Alias:\n   \
    \ kind: str\n    original: tuple[str, ...]\n    name: str\n    positions: frozenset[int]\n\
    \    parameter: str = \"\"\n    insertion: int = -1\n\n\ndef _short_names():\n\
    \    alphabet = \"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\"\n   \
    \ length = 1\n    while True:\n        indices = [0] * length\n        while True:\n\
    \            yield \"\".join(alphabet[index] for index in indices)\n         \
    \   position = length - 1\n            while position >= 0 and indices[position]\
    \ == len(alphabet) - 1:\n                indices[position] = 0\n             \
    \   position -= 1\n            if position < 0:\n                break\n     \
    \       indices[position] += 1\n        length += 1\n\n\ndef _is_identifier_start(ch:\
    \ str) -> bool:\n    # '$' is a widely supported GCC/Clang extension and is useful\
    \ to recognize\n    # even though portable C++ identifiers do not contain it.\n\
    \    return ch in \"_$\" or ch.isalpha() or (ord(ch) >= 128 and not ch.isspace())\n\
    \n\ndef _is_identifier_continue(ch: str) -> bool:\n    return _is_identifier_start(ch)\
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
    \ndef _matching_template_left(tokens: list[Token], right: int) -> int | None:\n\
    \    \"\"\"Match a closing template bracket, including lexed ``>>`` tokens.\"\"\
    \"\n    depth = 0\n    for i in range(right, -1, -1):\n        if tokens[i].text\
    \ == \">\":\n            depth += 1\n        elif tokens[i].text == \">>\":\n\
    \            depth += 2\n        elif tokens[i].text == \"<\":\n            depth\
    \ -= 1\n            if depth == 0:\n                return i\n    return None\n\
    \n\ndef _qualified_owner_name(tokens: list[Token], member: int) -> str:\n    \"\
    \"\"Return the identifier naming the qualifier before ``::member``.\"\"\"\n  \
    \  owner = member - 2\n    if owner < 0:\n        return \"\"\n    if tokens[owner].text\
    \ in {\">\", \">>\"}:\n        left = _matching_template_left(tokens, owner)\n\
    \        owner = -1 if left is None else left - 1\n    if owner >= 0 and tokens[owner].kind\
    \ == \"identifier\":\n        return tokens[owner].text\n    return \"\"\n\n\n\
    def _known_types(tokens: list[Token]) -> set[str]:\n    known = set(BUILTIN_TYPES)\
    \ | set(COMMON_TYPES) | _declared_type_names(tokens)\n    for i, token in enumerate(tokens):\n\
    \        if token.kind != \"identifier\":\n            continue\n        previous\
    \ = tokens[i - 1].text if i else \"\"\n        if previous in {\"class\", \"struct\"\
    , \"union\", \"enum\", \"typename\"}:\n            known.add(token.text)\n   \
    \     if previous == \"using\" and i + 1 < len(tokens) and tokens[i + 1].text\
    \ == \"=\":\n            known.add(token.text)\n\n    # In a typedef declaration,\
    \ the final identifier is the new type name.\n    start = 0\n    for i, token\
    \ in enumerate(tokens):\n        if token.text in {\";\", \"{\", \"}\"}:\n   \
    \         statement = tokens[start:i]\n            if statement and statement[0].text\
    \ == \"typedef\":\n                identifiers = [t.text for t in statement if\
    \ t.kind == \"identifier\"]\n                if identifiers:\n               \
    \     known.add(identifiers[-1])\n            start = i + 1\n    return known\n\
    \n\ndef _declared_type_names(tokens: list[Token]) -> set[str]:\n    \"\"\"Collect\
    \ types declared by this translation unit and safe to rename.\"\"\"\n    result:\
    \ set[str] = set()\n    for i, token in enumerate(tokens):\n        if token.kind\
    \ != \"identifier\":\n            continue\n        previous = tokens[i - 1].text\
    \ if i else \"\"\n        following = tokens[i + 1].text if i + 1 < len(tokens)\
    \ else \"\"\n        if previous in {\"class\", \"struct\", \"union\", \"enum\"\
    }:\n            result.add(token.text)\n        if previous == \"using\" and following\
    \ == \"=\":\n            result.add(token.text)\n\n    start = 0\n    for i, token\
    \ in enumerate(tokens):\n        if token.text in {\";\", \"{\", \"}\"}:\n   \
    \         statement = tokens[start:i]\n            if statement and statement[0].text\
    \ == \"typedef\":\n                identifiers = [t.text for t in statement if\
    \ t.kind == \"identifier\"]\n                if identifiers:\n               \
    \     result.add(identifiers[-1])\n            start = i + 1\n    return result\n\
    \n\ndef _declared_namespace_names(tokens: list[Token]) -> set[str]:\n    \"\"\"\
    Collect namespace definitions owned by the translation unit.\"\"\"\n    result:\
    \ set[str] = set()\n    for i, token in enumerate(tokens[:-1]):\n        if token.text\
    \ != \"namespace\":\n            continue\n        j = i + 1\n        components:\
    \ list[str] = []\n        while j < len(tokens):\n            if tokens[j].kind\
    \ == \"identifier\":\n                components.append(tokens[j].text)\n    \
    \            j += 1\n                if j < len(tokens) and tokens[j].text ==\
    \ \"::\":\n                    j += 1\n                    continue\n        \
    \    break\n        # A namespace alias such as ``namespace s=std`` does not own\
    \ members of\n        # its target and must not make ``s::external_name`` eligible\
    \ to rename.\n        if j < len(tokens) and tokens[j].text == \"{\":\n      \
    \      result.update(components)\n    result.discard(\"std\")\n    return result\n\
    \n\ndef _direct_class_context(tokens: list[Token]) -> list[bool]:\n    \"\"\"\
    Mark tokens whose innermost brace is a class/struct/union body.\"\"\"\n    result\
    \ = [False] * len(tokens)\n    stack: list[str] = []\n    statement_start = 0\n\
    \    for i, token in enumerate(tokens):\n        result[i] = bool(stack and stack[-1]\
    \ == \"class\")\n        if token.text == \"{\":\n            prefix = tokens[statement_start:i]\n\
    \            class_keywords = [\n                j for j, item in enumerate(prefix)\n\
    \                if item.text in {\"class\", \"struct\", \"union\"}\n        \
    \    ]\n            is_class = bool(class_keywords) and not any(\n           \
    \     item.text == \")\" for item in prefix[class_keywords[-1] + 1:]\n       \
    \     )\n            kind = \"class\" if is_class else \"other\"\n           \
    \ stack.append(kind)\n            statement_start = i + 1\n        elif token.text\
    \ == \"}\":\n            if stack:\n                stack.pop()\n            statement_start\
    \ = i + 1\n        elif token.text == \";\":\n            statement_start = i\
    \ + 1\n    return result\n\n\ndef _direct_namespace_context(tokens: list[Token])\
    \ -> list[bool]:\n    \"\"\"Mark tokens whose innermost brace is an owned namespace\
    \ body.\"\"\"\n    result = [False] * len(tokens)\n    stack: list[str] = []\n\
    \    statement_start = 0\n    for i, token in enumerate(tokens):\n        result[i]\
    \ = bool(stack and stack[-1] == \"namespace\")\n        if token.text == \"{\"\
    :\n            prefix = tokens[statement_start:i]\n            is_namespace =\
    \ any(item.text == \"namespace\" for item in prefix)\n            stack.append(\"\
    namespace\" if is_namespace else \"other\")\n            statement_start = i +\
    \ 1\n        elif token.text == \"}\":\n            if stack:\n              \
    \  stack.pop()\n            statement_start = i + 1\n        elif token.text ==\
    \ \";\":\n            statement_start = i + 1\n    return result\n\n\ndef _parenthesis_depth(tokens:\
    \ list[Token]) -> list[int]:\n    result: list[int] = []\n    depth = 0\n    for\
    \ token in tokens:\n        result.append(depth)\n        if token.text == \"\
    (\":\n            depth += 1\n        elif token.text == \")\":\n            depth\
    \ = max(0, depth - 1)\n    return result\n\n\ndef _declared_enum_members(tokens:\
    \ list[Token]) -> set[str]:\n    \"\"\"Collect enumerators declared by enums in\
    \ this translation unit.\"\"\"\n    result: set[str] = set()\n    for i, token\
    \ in enumerate(tokens):\n        if token.text != \"enum\":\n            continue\n\
    \        opening = i + 1\n        while opening < len(tokens) and tokens[opening].text\
    \ not in {\"{\", \";\"}:\n            opening += 1\n        if opening >= len(tokens)\
    \ or tokens[opening].text != \"{\":\n            continue\n        brace = paren\
    \ = bracket = 0\n        expect_name = True\n        j = opening\n        while\
    \ j < len(tokens):\n            text = tokens[j].text\n            if text ==\
    \ \"{\":\n                brace += 1\n            elif text == \"}\":\n      \
    \          brace -= 1\n                if brace == 0:\n                    break\n\
    \            elif brace == 1:\n                if text == \"(\":\n           \
    \         paren += 1\n                elif text == \")\":\n                  \
    \  paren = max(0, paren - 1)\n                elif text == \"[\":\n          \
    \          bracket += 1\n                elif text == \"]\":\n               \
    \     bracket = max(0, bracket - 1)\n                elif text == \",\" and paren\
    \ == bracket == 0:\n                    expect_name = True\n                elif\
    \ (\n                    expect_name\n                    and tokens[j].kind ==\
    \ \"identifier\"\n                    and text not in CPP_KEYWORDS\n         \
    \       ):\n                    result.add(text)\n                    expect_name\
    \ = False\n            j += 1\n    return result\n\n\ndef _type_before(tokens:\
    \ list[Token], index: int, known_types: set[str]) -> bool:\n    j = index - 1\n\
    \    while j >= 0 and tokens[j].text in CV_AND_POINTER:\n        j -= 1\n    if\
    \ j < 0:\n        return False\n    if tokens[j].text in BUILTIN_TYPES or tokens[j].text\
    \ in known_types:\n        return True\n    if tokens[j].text in {\">\", \">>\"\
    }:\n        left = _matching_template_left(tokens, j)\n        return left is\
    \ not None and left > 0 and tokens[left - 1].kind == \"identifier\"\n    if (\n\
    \        tokens[j].kind == \"identifier\"\n        and j > 0\n        and tokens[j\
    \ - 1].text == \"::\"\n    ):\n        return True\n    if tokens[j].text == \"\
    )\":\n        left = _matching_left(tokens, j, \"(\", \")\")\n        return left\
    \ is not None and left > 0 and tokens[left - 1].text == \"decltype\"\n    return\
    \ False\n\n\ndef _directive_identifiers(tokens: list[Token]) -> set[str]:\n  \
    \  result: set[str] = set()\n    for token in tokens:\n        if token.kind ==\
    \ \"directive\":\n            result.update(re.findall(r\"(?:[^\\W\\d]|[_$])(?:\\\
    w|[$])*\", token.text))\n    return result\n\n\ndef _directive_macro_names(tokens:\
    \ list[Token]) -> set[str]:\n    result: set[str] = set()\n    for token in tokens:\n\
    \        if token.kind != \"directive\":\n            continue\n        match\
    \ = re.match(\n            r\"(?:#|%:)\\s*(?:define|undef)\\s+\"\n           \
    \ r\"((?:[^\\W\\d]|[_$])(?:\\w|[$])*)\",\n            token.text,\n        )\n\
    \        if match is not None:\n            result.add(match.group(1))\n    return\
    \ result\n\n\ndef _is_line_control_directive(token: Token) -> bool:\n    if token.kind\
    \ != \"directive\":\n        return False\n    return re.match(\n        r\"(?:#|%:)\\\
    s*(?:line\\b|[0-9]+(?:\\s|$))\", token.text\n    ) is not None\n\n\ndef _directive_keyword(text:\
    \ str) -> str:\n    match = re.match(r\"(?:#|%:)\\s*([A-Za-z_][A-Za-z_0-9]*)\"\
    , text)\n    return match.group(1) if match else \"\"\n\n\ndef _direct_include_operand(text:\
    \ str) -> str | None:\n    match = re.match(\n        r'(?:#|%:)\\s*include\\\
    s*(<[^>\\n]+>|\"(?:\\\\.|[^\"\\n])+\")\\s*$',\n        text,\n    )\n    return\
    \ match.group(1) if match else None\n\n\ndef _filter_directives(tokens: list[Token])\
    \ -> list[Token]:\n    \"\"\"Drop line controls and duplicate unconditional direct\
    \ includes.\"\"\"\n    result: list[Token] = []\n    seen_includes: set[str] =\
    \ set()\n    conditional_depth = 0\n    for token in tokens:\n        if _is_line_control_directive(token):\n\
    \            continue\n        if token.kind != \"directive\":\n            result.append(token)\n\
    \            continue\n\n        keyword = _directive_keyword(token.text)\n  \
    \      if keyword == \"endif\":\n            conditional_depth = max(0, conditional_depth\
    \ - 1)\n\n        if keyword == \"include\" and conditional_depth == 0:\n    \
    \        operand = _direct_include_operand(token.text)\n            if operand\
    \ is not None:\n                if operand in seen_includes:\n               \
    \     continue\n                seen_includes.add(operand)\n\n        result.append(token)\n\
    \        if keyword in {\"if\", \"ifdef\", \"ifndef\"}:\n            conditional_depth\
    \ += 1\n    return result\n\n\ndef _variable_rename_plan(\n    tokens: list[Token],\n\
    ) -> tuple[dict[str, str], frozenset[int]]:\n    \"\"\"Build replacements and\
    \ positions that refer to external names.\"\"\"\n    known_types = _known_types(tokens)\n\
    \    declared_types = _declared_type_names(tokens)\n    declared_namespaces =\
    \ _declared_namespace_names(tokens)\n    enum_members = _declared_enum_members(tokens)\n\
    \    class_context = _direct_class_context(tokens)\n    namespace_context = _direct_namespace_context(tokens)\n\
    \    parenthesis_depth = _parenthesis_depth(tokens)\n    candidates: set[str]\
    \ = set()\n    declaration_indices: list[int] = []\n    field_names: set[str]\
    \ = set()\n\n    for i, token in enumerate(tokens):\n        if token.kind ==\
    \ \"identifier\" and token.text not in CPP_KEYWORDS:\n            if _type_before(tokens,\
    \ i, known_types):\n                candidates.add(token.text)\n             \
    \   declaration_indices.append(i)\n                if (\n                    class_context[i]\n\
    \                    and parenthesis_depth[i] == 0\n                    and (i\
    \ + 1 >= len(tokens) or tokens[i + 1].text != \"(\")\n                ):\n   \
    \                 field_names.add(token.text)\n\n        # Structured bindings:\
    \ auto [long_name, other_name].\n        if token.text == \"[\":\n           \
    \ j = i - 1\n            while j >= 0 and tokens[j].text in CV_AND_POINTER:\n\
    \                j -= 1\n            if j >= 0 and tokens[j].text == \"auto\"\
    :\n                close = next((k for k in range(i + 1, len(tokens)) if tokens[k].text\
    \ == \"]\"), None)\n                if close is not None:\n                  \
    \  for item in tokens[i + 1:close]:\n                        if item.kind == \"\
    identifier\" and item.text not in CPP_KEYWORDS:\n                            candidates.add(item.text)\n\
    \n    candidates.update(declared_types)\n    candidates.update(declared_namespaces)\n\
    \    candidates.update(enum_members)\n    function_names = {\n        tokens[i].text\
    \ for i in declaration_indices\n        if i + 1 < len(tokens) and tokens[i +\
    \ 1].text == \"(\"\n    }\n    namespace_variables = {\n        tokens[i].text\
    \ for i in declaration_indices\n        if namespace_context[i]\n        and (i\
    \ + 1 >= len(tokens) or tokens[i + 1].text != \"(\")\n    }\n\n    # Add later\
    \ declarators in declarations such as: int first = 0, second = 1;\n    for declaration\
    \ in declaration_indices:\n        paren = bracket = brace = 0\n        i = declaration\
    \ + 1\n        while i < len(tokens):\n            text = tokens[i].text\n   \
    \         if text == \"(\":\n                paren += 1\n            elif text\
    \ == \")\":\n                if paren == 0:\n                    break\n     \
    \           paren -= 1\n            elif text == \"[\":\n                bracket\
    \ += 1\n            elif text == \"]\":\n                bracket = max(0, bracket\
    \ - 1)\n            elif text == \"{\":\n                brace += 1\n        \
    \    elif text == \"}\":\n                if brace == 0:\n                   \
    \ break\n                brace -= 1\n            elif text == \";\" and paren\
    \ == bracket == brace == 0:\n                break\n            elif text == \"\
    ,\" and paren == bracket == brace == 0:\n                j = i + 1\n         \
    \       while j < len(tokens) and tokens[j].text in CV_AND_POINTER:\n        \
    \            j += 1\n                if j < len(tokens) and tokens[j].kind ==\
    \ \"identifier\":\n                    name = tokens[j].text\n               \
    \     if name not in known_types and name not in CPP_KEYWORDS:\n             \
    \           candidates.add(name)\n                        if class_context[declaration]:\n\
    \                            field_names.add(name)\n            i += 1\n\n   \
    \ protected = (\n        _directive_identifiers(tokens)\n        | (known_types\
    \ - declared_types)\n        | CPP_KEYWORDS\n        | {\"main\"}\n    )\n   \
    \ protected.update(\n        field_names\n        & (\n            CONVENTIONAL_EXTERNAL_DOT_MEMBERS\n\
    \            | CONVENTIONAL_EXTERNAL_QUALIFIED_MEMBERS\n        )\n    )\n   \
    \ protected.update(\n        (declared_types | enum_members)\n        & CONVENTIONAL_EXTERNAL_QUALIFIED_MEMBERS\n\
    \    )\n    excluded_positions: set[int] = set()\n    for i, token in enumerate(tokens):\n\
    \        if token.kind != \"identifier\":\n            continue\n        previous\
    \ = tokens[i - 1].text if i else \"\"\n        following = tokens[i + 1].text\
    \ if i + 1 < len(tokens) else \"\"\n        owned_type = token.text in declared_types\n\
    \        owned_namespace = token.text in declared_namespaces\n        owned_field\
    \ = token.text in field_names\n        owned_member = owned_field or token.text\
    \ in enum_members\n        owned_function = token.text in function_names\n   \
    \     if previous in {\".\", \"->\"} and (\n            token.text in CONVENTIONAL_EXTERNAL_DOT_MEMBERS\n\
    \            or not (owned_field or owned_type)\n        ):\n            excluded_positions.add(i)\n\
    \        if previous in {\".\", \"->\"} and following == \"(\":\n            excluded_positions.add(i)\n\
    \            if owned_function:\n                # Without receiver-type information,\
    \ a locally declared method\n                # cannot be distinguished from an\
    \ external method at call sites.\n                protected.add(token.text)\n\
    \        if previous == \"::\":\n            qualifier = _qualified_owner_name(tokens,\
    \ i)\n            qualifier_owned = (\n                qualifier in declared_types\
    \ or qualifier in declared_namespaces\n            )\n            conventional_external\
    \ = (\n                token.text in CONVENTIONAL_EXTERNAL_QUALIFIED_MEMBERS\n\
    \                and qualifier not in declared_namespaces\n            )\n   \
    \         if conventional_external or not qualifier_owned or not (\n         \
    \       owned_type\n                or owned_namespace\n                or owned_member\n\
    \                or owned_function\n                or token.text in namespace_variables\n\
    \            ):\n                excluded_positions.add(i)\n        if previous\
    \ in {\"goto\", \"typedef\"}:\n            protected.add(token.text)\n       \
    \ if previous in {\"class\", \"struct\", \"union\", \"enum\"} and not owned_type:\n\
    \            excluded_positions.add(i)\n        if previous == \"namespace\" and\
    \ not owned_namespace:\n            excluded_positions.add(i)\n        if previous\
    \ == \"using\" and not (owned_type or owned_namespace):\n            excluded_positions.add(i)\n\
    \        if following == \"::\" and not (owned_type or owned_namespace):\n   \
    \         excluded_positions.add(i)\n        if following == \":\" and token.text\
    \ not in candidates:\n            protected.add(token.text)\n        if following\
    \ == \"(\" and not (\n            owned_type or owned_member or owned_function\
    \ or token.text in candidates\n        ):\n            excluded_positions.add(i)\n\
    \        if token.text.startswith(\"__\") or (token.text.startswith(\"_\") and\
    \ len(token.text) > 1 and token.text[1].isupper()):\n            protected.add(token.text)\n\
    \n    # Keep declarations whose spelling participates in an external contract.\n\
    \    for i in declaration_indices:\n        start = i - 1\n        while start\
    \ >= 0 and tokens[start].text not in {\";\", \"{\", \"}\"}:\n            start\
    \ -= 1\n        prefix = tokens[start + 1:i]\n        if any(token.text == \"\
    extern\" for token in prefix):\n            protected.add(tokens[i].text)\n  \
    \      if i + 1 >= len(tokens) or tokens[i + 1].text != \"(\":\n            continue\n\
    \        end = i + 1\n        while end < len(tokens) and tokens[end].text not\
    \ in {\";\", \"{\"}:\n            end += 1\n        declaration = tokens[start\
    \ + 1:end]\n        if any(token.text in {\"override\", \"final\"} for token in\
    \ declaration):\n            protected.add(tokens[i].text)\n\n    candidates -=\
    \ protected\n    counts: dict[str, int] = {}\n    for i, token in enumerate(tokens):\n\
    \        if (\n            i not in excluded_positions\n            and token.kind\
    \ == \"identifier\"\n            and token.text in candidates\n        ):\n  \
    \          counts[token.text] = counts.get(token.text, 0) + 1\n\n    unavailable\
    \ = {\n        token.text for token in tokens if token.kind == \"identifier\"\n\
    \    } | CPP_KEYWORDS\n\n    names = _short_names()\n    renames: dict[str, str]\
    \ = {}\n    for old in sorted(candidates, key=lambda name: (-counts.get(name,\
    \ 0), -len(name), name)):\n        new = next(names)\n        while new in unavailable\
    \ or new in renames.values():\n            new = next(names)\n        if len(new)\
    \ < len(old):\n            renames[old] = new\n    return renames, frozenset(excluded_positions)\n\
    \n\ndef variable_renames(tokens: list[Token]) -> dict[str, str]:\n    \"\"\"Return\
    \ the spelling map for file-owned C++ names.\"\"\"\n    return _variable_rename_plan(tokens)[0]\n\
    \n\ndef _pattern_positions(tokens: list[Token], pattern: tuple[str, ...]) -> list[int]:\n\
    \    \"\"\"Find maximal builtin type spellings equal to ``pattern``.\"\"\"\n \
    \   result: list[int] = []\n    width = len(pattern)\n    for i in range(len(tokens)\
    \ - width + 1):\n        if tuple(token.text for token in tokens[i:i + width])\
    \ != pattern:\n            continue\n        previous = tokens[i - 1].text if\
    \ i else \"\"\n        following = tokens[i + width].text if i + width < len(tokens)\
    \ else \"\"\n        if previous in TYPE_SPECIFIER_WORDS or following in TYPE_SPECIFIER_WORDS:\n\
    \            continue\n        result.append(i)\n    return result\n\n\ndef _qualified_template_positions(tokens:\
    \ list[Token], name: str) -> list[int]:\n    pattern = (\"std\", \"::\", name,\
    \ \"<\")\n    return [\n        i for i in range(len(tokens) - len(pattern) +\
    \ 1)\n        if tuple(token.text for token in tokens[i:i + len(pattern)]) ==\
    \ pattern\n    ]\n\n\ndef _standard_header_insertions(tokens: list[Token]) ->\
    \ dict[str, int]:\n    \"\"\"Return safe global insertion points after unconditional\
    \ angle includes.\"\"\"\n    result: dict[str, int] = {}\n    conditional_depth\
    \ = 0\n    brace_depth = 0\n    for i, token in enumerate(tokens):\n        if\
    \ token.kind == \"directive\":\n            keyword = _directive_keyword(token.text)\n\
    \            if keyword == \"endif\":\n                conditional_depth = max(0,\
    \ conditional_depth - 1)\n            if (\n                keyword == \"include\"\
    \n                and conditional_depth == 0\n                and brace_depth\
    \ == 0\n            ):\n                operand = _direct_include_operand(token.text)\n\
    \                if operand is not None and operand.startswith(\"<\"):\n     \
    \               result.setdefault(operand[1:-1], i + 1)\n            if keyword\
    \ in {\"if\", \"ifdef\", \"ifndef\"}:\n                conditional_depth += 1\n\
    \            continue\n        if token.text == \"{\":\n            brace_depth\
    \ += 1\n        elif token.text == \"}\":\n            brace_depth = max(0, brace_depth\
    \ - 1)\n    return result\n\n\ndef _leading_directive_end(tokens: list[Token])\
    \ -> tuple[int, bool, bool]:\n    \"\"\"Return the initial directive-block end\
    \ and namespace-alias safety.\"\"\"\n    i = 0\n    saw_include = False\n    conditional\
    \ = False\n    while i < len(tokens) and tokens[i].kind == \"directive\":\n  \
    \      directive = tokens[i].text\n        match = re.match(r\"(?:#|%:)\\s*([A-Za-z_][A-Za-z_0-9]*)\"\
    , directive)\n        keyword = match.group(1) if match else \"\"\n        saw_include\
    \ |= keyword == \"include\"\n        conditional |= keyword in {\"if\", \"ifdef\"\
    , \"ifndef\", \"elif\", \"else\", \"endif\"}\n        i += 1\n    return i, saw_include\
    \ and not conditional, not conditional\n\n\ndef _compression_aliases(\n    tokens:\
    \ list[Token], renames: dict[str, str]\n) -> tuple[list[Alias], int, int]:\n \
    \   \"\"\"Choose profitable type aliases and well-known namespace aliases.\"\"\
    \"\n    # Declarations before/among module directives have strict placement rules.\n\
    \    if any(token.text == \"module\" for token in tokens):\n        return [],\
    \ 0, 0\n    directive_names = _directive_identifiers(tokens)\n    macro_names\
    \ = _directive_macro_names(tokens)\n    candidates: list[\n        tuple[str,\
    \ tuple[str, ...], list[int], int, int, str, int]\n    ] = []\n\n    for pattern\
    \ in TYPE_ALIAS_PATTERNS:\n        if any(word in directive_names for word in\
    \ pattern):\n            continue\n        positions = _pattern_positions(tokens,\
    \ pattern)\n        if not positions:\n            continue\n        spelling_length\
    \ = sum(map(len, pattern)) + len(pattern) - 1\n        candidates.append(\n  \
    \          (\n                \"type\", pattern, positions, spelling_length,\n\
    \                7 + spelling_length, \"\", -1,\n            )\n        )\n\n\
    \    leading_end, _, type_aliases_safe = _leading_directive_end(tokens)\n    header_insertions\
    \ = _standard_header_insertions(tokens)\n    umbrella_insertions = [\n       \
    \ header_insertions[header]\n        for header in (\"bits/stdc++.h\", \"bits/extc++.h\"\
    )\n        if header in header_insertions\n    ]\n    parameter = next(\n    \
    \    name for name in (\"T\", \"U\", \"V\", \"X\", \"_\")\n        if name not\
    \ in directive_names\n    )\n    for template_name, header in STD_PACK_ALIAS_TEMPLATES.items():\n\
    \        if template_name in macro_names or \"std\" in macro_names:\n        \
    \    continue\n        insertions = list(umbrella_insertions)\n        if header\
    \ in header_insertions:\n            insertions.append(header_insertions[header])\n\
    \        if not insertions:\n            continue\n        insertion = min(insertions)\n\
    \        positions = [\n            position\n            for position in _qualified_template_positions(tokens,\
    \ template_name)\n            if position >= insertion\n        ]\n        if\
    \ not positions:\n            continue\n        original = (\"std\", \"::\", template_name)\n\
    \        spelling_length = len(\"std::\") + len(template_name)\n        declaration_without_name\
    \ = (\n            f\"template<class...{parameter}>using \"\n            f\"=std::{template_name}<{parameter}...>;\"\
    \n        )\n        candidates.append(\n            (\n                \"template\"\
    ,\n                original,\n                positions,\n                spelling_length,\n\
    \                len(declaration_without_name),\n                parameter,\n\
    \                insertion,\n            )\n        )\n\n    namespace_insertions\
    \ = {\n        \"std\": [\n            insertion for header, insertion in header_insertions.items()\n\
    \            if header in STD_NAMESPACE_HEADERS\n            or header in {\"\
    bits/stdc++.h\", \"bits/extc++.h\"}\n        ],\n        \"boost\": [\n      \
    \      insertion for header, insertion in header_insertions.items()\n        \
    \    if header.startswith(\"boost/\")\n        ],\n    }\n    for namespace in\
    \ (\"std\", \"boost\"):\n        if namespace in macro_names or not namespace_insertions[namespace]:\n\
    \            continue\n        all_positions = [\n            i for i, token in\
    \ enumerate(tokens)\n            if token.kind == \"identifier\" and token.text\
    \ == namespace\n        ]\n        if not all_positions or any(\n            i\
    \ + 1 >= len(tokens) or tokens[i + 1].text != \"::\"\n            for i in all_positions\n\
    \        ):\n            continue\n        insertion = min(namespace_insertions[namespace])\n\
    \        positions = [position for position in all_positions if position >= insertion]\n\
    \        if not positions:\n            continue\n        candidates.append(\n\
    \            (\n                \"namespace\", (namespace,), positions,\n    \
    \            len(namespace), 12 + len(namespace), \"\", insertion,\n         \
    \   )\n        )\n\n    occupied = {\n        token.text for token in tokens if\
    \ token.kind == \"identifier\"\n    } | directive_names | CPP_KEYWORDS | set(renames.values())\n\
    \    names = _short_names()\n    aliases: list[Alias] = []\n    while candidates:\n\
    \        name = next(names)\n        while name in occupied:\n            name\
    \ = next(names)\n        best_index = -1\n        best_saving = 0\n        for\
    \ i, candidate in enumerate(candidates):\n            _, _, positions, spelling_length,\
    \ declaration_base, _, _ = candidate\n            saving = (\n               \
    \ len(positions) * (spelling_length - len(name))\n                - declaration_base\n\
    \                - len(name)\n            )\n            if saving > best_saving:\n\
    \                best_saving = saving\n                best_index = i\n      \
    \  if best_index == -1:\n            break\n        kind, original, positions,\
    \ _, _, parameter, insertion = candidates.pop(\n            best_index\n     \
    \   )\n        aliases.append(\n            Alias(\n                kind, original,\
    \ name, frozenset(positions), parameter, insertion\n            )\n        )\n\
    \        occupied.add(name)\n\n    template_positions = {\n        position for\
    \ alias in aliases if alias.kind == \"template\"\n        for position in alias.positions\n\
    \    }\n    adjusted: list[Alias] = []\n    for alias in aliases:\n        if\
    \ alias.kind != \"namespace\" or alias.original != (\"std\",):\n            adjusted.append(alias)\n\
    \            continue\n        positions = alias.positions - template_positions\n\
    \        declaration_length = 12 + len(alias.name) + len(alias.original[0])\n\
    \        saving = len(positions) * (len(\"std\") - len(alias.name))\n        if\
    \ saving > declaration_length:\n            adjusted.append(\n               \
    \ Alias(\n                    alias.kind, alias.original, alias.name, positions,\n\
    \                    alias.parameter, alias.insertion,\n                )\n  \
    \          )\n    aliases = adjusted\n\n    type_insert = leading_end if type_aliases_safe\
    \ else 0\n    namespace_insert = leading_end\n    return aliases, type_insert,\
    \ namespace_insert\n\n\ndef _alias_declaration(alias: Alias) -> list[Token]:\n\
    \    original = \" \".join(alias.original)\n    if alias.kind == \"namespace\"\
    :\n        return tokenize(f\"namespace {alias.name}={original};\")\n    if alias.kind\
    \ == \"template\":\n        template_name = alias.original[-1]\n        parameter\
    \ = alias.parameter\n        return tokenize(\n            f\"template<class...{parameter}>using\
    \ {alias.name}=\"\n            f\"std::{template_name}<{parameter}...>;\"\n  \
    \      )\n    return tokenize(f\"using {alias.name}={original};\")\n\n\ndef _alias_key(alias:\
    \ Alias) -> str:\n    if alias.kind == \"template\":\n        return \"\".join(alias.original)\n\
    \    return \" \".join(alias.original)\n\n\ndef _transform_tokens(\n    tokens:\
    \ list[Token], renames: dict[str, str], aliases: list[Alias],\n    type_insert:\
    \ int, namespace_insert: int,\n    rename_exclusions: frozenset[int] = frozenset(),\n\
    ) -> list[Token]:\n    injections: dict[int, list[Token]] = {}\n    for alias\
    \ in aliases:\n        index = (\n            alias.insertion\n            if\
    \ alias.insertion >= 0\n            else namespace_insert\n            if alias.kind\
    \ in {\"namespace\", \"template\"}\n            else type_insert\n        )\n\
    \        injections.setdefault(index, []).extend(_alias_declaration(alias))\n\n\
    \    type_at: dict[int, Alias] = {}\n    namespace_at: dict[int, Alias] = {}\n\
    \    for alias in aliases:\n        destination = namespace_at if alias.kind ==\
    \ \"namespace\" else type_at\n        for position in alias.positions:\n     \
    \       destination[position] = alias\n\n    result: list[Token] = []\n    i =\
    \ 0\n    while i < len(tokens):\n        result.extend(injections.get(i, ()))\n\
    \        if i in type_at:\n            alias = type_at[i]\n            result.append(Token(\"\
    identifier\", alias.name))\n            i += len(alias.original)\n           \
    \ continue\n\n        token = tokens[i]\n        if i in namespace_at:\n     \
    \       token = Token(\"identifier\", namespace_at[i].name)\n        elif (\n\
    \            i not in rename_exclusions\n            and token.kind == \"identifier\"\
    \n            and token.text in renames\n        ):\n            token = Token(token.kind,\
    \ renames[token.text])\n        result.append(token)\n        i += 1\n    result.extend(injections.get(len(tokens),\
    \ ()))\n    return result\n\n\ndef _needs_space(previous: Token, current: Token)\
    \ -> bool:\n    if previous.kind == \"directive\" or current.kind == \"directive\"\
    :\n        return False\n    # Re-lexing the boundary is more reliable than maintaining\
    \ a growing list\n    # of special cases for pp-numbers, literal prefixes, digraphs,\
    \ comments,\n    # and multi-character punctuators.  Each token participates in\
    \ at most two\n    # such checks, so the total amount of text examined remains\
    \ linear.\n    combined = tokenize(previous.text + current.text)\n    return combined\
    \ != [previous, current]\n\n\ndef minify(source: str, rename: bool = True) ->\
    \ tuple[str, dict[str, str]]:\n    tokens = _filter_directives(tokenize(source))\n\
    \    rename_exclusions: frozenset[int] = frozenset()\n    if rename:\n       \
    \ renames, rename_exclusions = _variable_rename_plan(tokens)\n    else:\n    \
    \    renames = {}\n    aliases: list[Alias] = []\n    type_insert = namespace_insert\
    \ = 0\n    if rename:\n        aliases, type_insert, namespace_insert = _compression_aliases(tokens,\
    \ renames)\n        tokens = _transform_tokens(\n            tokens, renames,\
    \ aliases, type_insert, namespace_insert,\n            rename_exclusions,\n  \
    \      )\n        for alias in aliases:\n            renames[_alias_key(alias)]\
    \ = alias.name\n    output: list[str] = []\n    previous: Token | None = None\n\
    \n    for token in tokens:\n        if token.kind == \"directive\":\n        \
    \    if output and not output[-1].endswith(\"\\n\"):\n                output.append(\"\
    \\n\")\n            output.append(token.text + \"\\n\")\n            previous\
    \ = None\n            continue\n        if previous is not None and _needs_space(previous,\
    \ token):\n            output.append(\" \")\n        output.append(token.text)\n\
    \        previous = token\n\n    result = \"\".join(output).rstrip()\n    return\
    \ (result + \"\\n\" if result else \"\"), renames\n\n\ndef main() -> int:\n  \
    \  parser = argparse.ArgumentParser(description=\"Minify C++ source code for contest\
    \ submissions.\")\n    parser.add_argument(\"input\", nargs=\"?\", type=Path,\
    \ help=\"input file (default: stdin)\")\n    parser.add_argument(\"-o\", \"--output\"\
    , type=Path, help=\"output file (default: stdout)\")\n    parser.add_argument(\"\
    --no-rename\", action=\"store_true\", help=\"only remove comments and whitespace\"\
    )\n    parser.add_argument(\"--stats\", action=\"store_true\", help=\"print size\
    \ and name-compression statistics to stderr\")\n    args = parser.parse_args()\n\
    \n    source = args.input.read_text(encoding=\"utf-8\") if args.input else sys.stdin.read()\n\
    \    result, renames = minify(source, rename=not args.no_rename)\n    if args.output:\n\
    \        args.output.write_text(result, encoding=\"utf-8\")\n    else:\n     \
    \   sys.stdout.write(result)\n\n    if args.stats:\n        source_size = len(source.encode(\"\
    utf-8\"))\n        result_size = len(result.encode(\"utf-8\"))\n        reduction\
    \ = 0.0 if not source_size else 100.0 * (source_size - result_size) / source_size\n\
    \        print(\n            f\"{source_size} -> {result_size} bytes ({reduction:.1f}%\
    \ smaller), \"\n            f\"renamed/aliased {len(renames)} names\",\n     \
    \       file=sys.stderr,\n        )\n    return 0\n\n\nif __name__ == \"__main__\"\
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
