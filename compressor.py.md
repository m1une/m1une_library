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
    \ for contest submissions.\n\nThe minifier removes comments and unnecessary whitespace.\
    \  By default it also\nshortens identifiers which look like variable declarations.\
    \  Renaming is\ndeliberately conservative: macros, types, functions, labels, qualified\
    \ names,\nand member names are left alone.\n\"\"\"\n\nfrom __future__ import annotations\n\
    \nimport argparse\nimport re\nimport sys\nfrom dataclasses import dataclass\n\
    from pathlib import Path\n\n\nCPP_KEYWORDS = {\n    \"alignas\", \"alignof\",\
    \ \"and\", \"and_eq\", \"asm\", \"auto\", \"bitand\",\n    \"bitor\", \"bool\"\
    , \"break\", \"case\", \"catch\", \"char\", \"char8_t\",\n    \"char16_t\", \"\
    char32_t\", \"class\", \"compl\", \"concept\", \"const\",\n    \"consteval\",\
    \ \"constexpr\", \"constinit\", \"const_cast\", \"continue\",\n    \"co_await\"\
    , \"co_return\", \"co_yield\", \"decltype\", \"default\", \"delete\",\n    \"\
    do\", \"double\", \"dynamic_cast\", \"else\", \"enum\", \"explicit\", \"export\"\
    ,\n    \"extern\", \"false\", \"float\", \"for\", \"friend\", \"goto\", \"if\"\
    , \"inline\",\n    \"int\", \"long\", \"mutable\", \"namespace\", \"new\", \"\
    noexcept\", \"not\",\n    \"not_eq\", \"nullptr\", \"operator\", \"or\", \"or_eq\"\
    , \"private\", \"protected\",\n    \"public\", \"register\", \"reinterpret_cast\"\
    , \"requires\", \"return\", \"short\",\n    \"signed\", \"sizeof\", \"static\"\
    , \"static_assert\", \"static_cast\", \"struct\",\n    \"switch\", \"template\"\
    , \"this\", \"thread_local\", \"throw\", \"true\", \"try\",\n    \"typedef\",\
    \ \"typeid\", \"typename\", \"union\", \"unsigned\", \"using\", \"virtual\",\n\
    \    \"void\", \"volatile\", \"wchar_t\", \"while\", \"xor\", \"xor_eq\",\n}\n\
    \nBUILTIN_TYPES = {\n    \"auto\", \"bool\", \"char\", \"char8_t\", \"char16_t\"\
    , \"char32_t\", \"double\",\n    \"float\", \"int\", \"long\", \"short\", \"signed\"\
    , \"unsigned\", \"void\",\n    \"wchar_t\", \"size_t\", \"ptrdiff_t\", \"int8_t\"\
    , \"int16_t\", \"int32_t\",\n    \"int64_t\", \"uint8_t\", \"uint16_t\", \"uint32_t\"\
    , \"uint64_t\", \"__int128\",\n    \"__int128_t\", \"__uint128_t\",\n}\n\nCOMMON_TYPES\
    \ = {\n    \"array\", \"bitset\", \"deque\", \"function\", \"initializer_list\"\
    , \"list\",\n    \"map\", \"multimap\", \"multiset\", \"optional\", \"pair\",\
    \ \"priority_queue\",\n    \"queue\", \"set\", \"span\", \"stack\", \"string\"\
    , \"string_view\", \"tuple\",\n    \"unordered_map\", \"unordered_multimap\",\
    \ \"unordered_multiset\",\n    \"unordered_set\", \"variant\", \"vector\",\n}\n\
    \nCV_AND_POINTER = {\"const\", \"volatile\", \"constexpr\", \"static\", \"mutable\"\
    , \"*\", \"&\", \"&&\"}\n\nPUNCTUATORS = (\n    \"%:%:\", \"<<=\", \">>=\", \"\
    <=>\", \"->*\", \"...\", \"##\", \"::\", \".*\", \"->\",\n    \"++\", \"--\",\
    \ \"<<\", \">>\", \"<=\", \">=\", \"==\", \"!=\", \"&&\", \"||\", \"*=\",\n  \
    \  \"/=\", \"%=\", \"+=\", \"-=\", \"&=\", \"^=\", \"|=\", \"<:\", \":>\", \"\
    <%\", \"%>\",\n    \"%:\", \"{\", \"}\", \"[\", \"]\", \"(\", \")\", \"#\", \"\
    ;\", \":\", \"?\", \".\", \"+\",\n    \"-\", \"*\", \"/\", \"%\", \"^\", \"&\"\
    , \"|\", \"~\", \"!\", \"=\", \"<\", \">\", \",\",\n)\n\nMULTI_PUNCTUATORS = {p\
    \ for p in PUNCTUATORS if len(p) > 1} | {\"//\", \"/*\"}\nPUNCTUATOR_PREFIXES\
    \ = {\n    p[:i] for p in MULTI_PUNCTUATORS for i in range(2, len(p) + 1)\n}\n\
    \n\n@dataclass(frozen=True)\nclass Token:\n    kind: str\n    text: str\n\n\n\
    def _quoted_end(source: str, start: int) -> int | None:\n    \"\"\"Return the\
    \ end of a string/character/raw literal starting at start.\"\"\"\n    prefixes\
    \ = (\"u8R\\\"\", \"uR\\\"\", \"UR\\\"\", \"LR\\\"\", \"R\\\"\")\n    raw_prefix\
    \ = next((p for p in prefixes if source.startswith(p, start)), None)\n    if raw_prefix\
    \ is not None:\n        delimiter_start = start + len(raw_prefix)\n        open_paren\
    \ = source.find(\"(\", delimiter_start)\n        if open_paren == -1 or open_paren\
    \ - delimiter_start > 16:\n            return None\n        delimiter = source[delimiter_start:open_paren]\n\
    \        if any(ch.isspace() or ch in \"()\\\\\" for ch in delimiter):\n     \
    \       return None\n        close = source.find(\")\" + delimiter + \"\\\"\"\
    , open_paren + 1)\n        return len(source) if close == -1 else close + len(delimiter)\
    \ + 2\n\n    prefixes = (\"u8\\\"\", \"u\\\"\", \"U\\\"\", \"L\\\"\", \"\\\"\"\
    , \"u'\", \"U'\", \"L'\", \"'\")\n    prefix = next((p for p in prefixes if source.startswith(p,\
    \ start)), None)\n    if prefix is None:\n        return None\n    quote = prefix[-1]\n\
    \    i = start + len(prefix)\n    while i < len(source):\n        if source[i]\
    \ == \"\\\\\":\n            i += 2\n        elif source[i] == quote:\n       \
    \     return i + 1\n        else:\n            i += 1\n    return len(source)\n\
    \n\ndef tokenize(source: str) -> list[Token]:\n    # C++ removes escaped newlines\
    \ before recognizing comments or tokens.\n    source = source.replace(\"\\\\\\\
    r\\n\", \"\").replace(\"\\\\\\n\", \"\")\n    tokens: list[Token] = []\n    i\
    \ = 0\n    at_line_start = True\n    n = len(source)\n\n    while i < n:\n   \
    \     ch = source[i]\n        if ch in \" \\t\\v\\f\\r\":\n            i += 1\n\
    \            continue\n        if ch == \"\\n\":\n            at_line_start =\
    \ True\n            i += 1\n            continue\n\n        if at_line_start and\
    \ ch == \"#\":\n            start = i\n            while i < n:\n            \
    \    newline = source.find(\"\\n\", i)\n                if newline == -1:\n  \
    \                  i = n\n                    break\n                backslashes\
    \ = 0\n                j = newline - 1\n                while j >= start and source[j]\
    \ == \"\\\\\":\n                    backslashes += 1\n                    j -=\
    \ 1\n                i = newline + 1\n                if backslashes % 2 == 0:\n\
    \                    break\n            tokens.append(Token(\"directive\", source[start:i].rstrip()))\n\
    \            at_line_start = True\n            continue\n\n        at_line_start\
    \ = False\n        if source.startswith(\"//\", i):\n            newline = source.find(\"\
    \\n\", i + 2)\n            i = n if newline == -1 else newline + 1\n         \
    \   at_line_start = True\n            continue\n        if source.startswith(\"\
    /*\", i):\n            close = source.find(\"*/\", i + 2)\n            if close\
    \ == -1:\n                i = n\n            else:\n                segment =\
    \ source[i:close + 2]\n                at_line_start = segment.endswith(\"\\n\"\
    )\n                i = close + 2\n            continue\n\n        literal_end\
    \ = _quoted_end(source, i)\n        if literal_end is not None:\n            tokens.append(Token(\"\
    literal\", source[i:literal_end]))\n            i = literal_end\n            continue\n\
    \n        if ch.isalpha() or ch == \"_\":\n            j = i + 1\n           \
    \ while j < n and (source[j].isalnum() or source[j] == \"_\"):\n             \
    \   j += 1\n            tokens.append(Token(\"identifier\", source[i:j]))\n  \
    \          i = j\n            continue\n\n        if ch.isdigit() or (ch == \"\
    .\" and i + 1 < n and source[i + 1].isdigit()):\n            j = i + 1\n     \
    \       while j < n:\n                current = source[j]\n                if\
    \ current.isalnum() or current in \"_.'\":\n                    j += 1\n     \
    \           elif current in \"+-\" and source[j - 1] in \"eEpP\":\n          \
    \          j += 1\n                else:\n                    break\n        \
    \    tokens.append(Token(\"number\", source[i:j]))\n            i = j\n      \
    \      continue\n\n        punctuator = next((p for p in PUNCTUATORS if source.startswith(p,\
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
    \ == \"directive\":\n            result.update(re.findall(r\"[A-Za-z_][A-Za-z_0-9]*\"\
    , token.text))\n    return result\n\n\ndef variable_renames(tokens: list[Token])\
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
    \ == \"directive\":\n        return False\n    if previous.text[-1].isalnum()\
    \ or previous.text[-1] == \"_\":\n        if current.text[0].isalnum() or current.text[0]\
    \ == \"_\":\n            return True\n    if previous.kind == \"number\" and current.kind\
    \ == \"identifier\":\n        return True\n    if previous.text == \".\" and current.text[0].isdigit():\n\
    \        return True\n    if previous.kind == \"number\" and current.text in {\"\
    +\", \"-\"} and previous.text[-1] in \"eEpP\":\n        return True\n    return\
    \ previous.text + current.text in PUNCTUATOR_PREFIXES\n\n\ndef minify(source:\
    \ str, rename: bool = True) -> tuple[str, dict[str, str]]:\n    tokens = tokenize(source)\n\
    \    renames = variable_renames(tokens) if rename else {}\n    output: list[str]\
    \ = []\n    previous: Token | None = None\n\n    for original in tokens:\n   \
    \     token = original\n        if token.kind == \"identifier\" and token.text\
    \ in renames:\n            token = Token(token.kind, renames[token.text])\n\n\
    \        if token.kind == \"directive\":\n            if output and not output[-1].endswith(\"\
    \\n\"):\n                output.append(\"\\n\")\n            output.append(token.text\
    \ + \"\\n\")\n            previous = None\n            continue\n        if previous\
    \ is not None and _needs_space(previous, token):\n            output.append(\"\
    \ \")\n        output.append(token.text)\n        previous = token\n\n    return\
    \ \"\".join(output).rstrip() + \"\\n\", renames\n\n\ndef main() -> int:\n    parser\
    \ = argparse.ArgumentParser(description=\"Minify C++ source code for contest submissions.\"\
    )\n    parser.add_argument(\"input\", nargs=\"?\", type=Path, help=\"input file\
    \ (default: stdin)\")\n    parser.add_argument(\"-o\", \"--output\", type=Path,\
    \ help=\"output file (default: stdout)\")\n    parser.add_argument(\"--no-rename\"\
    , action=\"store_true\", help=\"only remove comments and whitespace\")\n    parser.add_argument(\"\
    --stats\", action=\"store_true\", help=\"print size and rename statistics to stderr\"\
    )\n    args = parser.parse_args()\n\n    source = args.input.read_text(encoding=\"\
    utf-8\") if args.input else sys.stdin.read()\n    result, renames = minify(source,\
    \ rename=not args.no_rename)\n    if args.output:\n        args.output.write_text(result,\
    \ encoding=\"utf-8\")\n    else:\n        sys.stdout.write(result)\n\n    if args.stats:\n\
    \        reduction = 0.0 if not source else 100.0 * (len(source) - len(result))\
    \ / len(source)\n        print(\n            f\"{len(source)} -> {len(result)}\
    \ bytes ({reduction:.1f}% smaller), \"\n            f\"renamed {len(renames)}\
    \ identifiers\",\n            file=sys.stderr,\n        )\n    return 0\n\n\n\
    if __name__ == \"__main__\":\n    raise SystemExit(main())\n"
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
