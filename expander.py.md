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
  code: "import os\nimport re\nimport sys\n\nLIBRARY_ROOT = os.path.abspath(os.path.dirname(__file__))\n\
    LIBRARY_PARENT = os.path.dirname(LIBRARY_ROOT)\nINCLUDE_PATHS = ('.', LIBRARY_ROOT,\
    \ LIBRARY_PARENT)\nvisited = set()\n\n\ndef line_marker_name(display_name):\n\
    \    \"\"\"\n    Builds a diagnostic filename that is safe for syntax highlighters.\n\
    \n    Ace misparses a #line filename containing a path separator and can treat\
    \ the\n    following source line as part of a string. The filename is only used\
    \ for\n    diagnostics, so keep its path context with a separator that cannot\
    \ trigger\n    that tokenizer bug.\n    \"\"\"\n    return re.sub(r'[/\\\\]+',\
    \ '::', display_name).replace('\"', \"'\")\n\n\ndef resolve_include(header, current_file_dir):\n\
    \    \"\"\"\n    Finds the absolute path for a given header file.\n    It first\
    \ checks relative to the current file's directory,\n    then checks the global\
    \ include paths.\n    \"\"\"\n    relative_path = os.path.join(current_file_dir,\
    \ header)\n    if os.path.isfile(relative_path):\n        return os.path.abspath(relative_path)\n\
    \n    for path in INCLUDE_PATHS:\n        full_path = os.path.join(path, header)\n\
    \        if os.path.isfile(full_path):\n            return os.path.abspath(full_path)\n\
    \    return None\n\n\ndef expand_file(path, display_name=None):\n    \"\"\"\n\
    \    Recursively expands a C++ file by inlining its local #include directives.\n\
    \    It removes include guards and skips #ifdef LOCAL blocks.\n    \"\"\"\n  \
    \  abs_path = os.path.abspath(path)\n    if abs_path in visited:\n        return\n\
    \    visited.add(abs_path)\n\n    if display_name is None:\n        display_name\
    \ = os.path.relpath(path, LIBRARY_ROOT)\n    marker_name = line_marker_name(display_name)\n\
    \n    print(f'// BEGIN: {display_name}')\n\n    with open(path, encoding='utf-8')\
    \ as f:\n        lines = f.readlines()\n\n    # --- Pre-processing Step: Identify\
    \ lines to skip ---\n    lines_to_skip = set()\n\n    # Identify and mark include\
    \ guards for removal\n    if lines:\n        # Method 1: #pragma once\n      \
    \  for i, line in enumerate(lines):\n            if line.strip() == \"#pragma\
    \ once\":\n                lines_to_skip.add(i)\n                break\n\n   \
    \     # Method 2: #ifndef/#define/#endif guards\n        if not lines_to_skip\
    \ and len(lines) >= 2:\n            first_line_idx, first_line = -1, \"\"\n  \
    \          for i, line in enumerate(lines):\n                if line.strip():\n\
    \                    first_line_idx, first_line = i, line\n                  \
    \  break\n\n            second_line_idx, second_line = -1, \"\"\n            if\
    \ first_line_idx != -1:\n                for i in range(first_line_idx + 1, len(lines)):\n\
    \                    if lines[i].strip():\n                        second_line_idx,\
    \ second_line = i, lines[i]\n                        break\n\n            last_endif_idx\
    \ = -1\n            for i in range(len(lines) - 1, -1, -1):\n                if\
    \ lines[i].strip().startswith('#endif'):\n                    last_endif_idx =\
    \ i\n                    break\n\n            if first_line_idx != -1 and second_line_idx\
    \ != -1 and last_endif_idx != -1:\n                ifndef_match = re.match(r'#\\\
    s*ifndef\\s+([A-Z0-9_]+)\\s*', first_line)\n                if ifndef_match:\n\
    \                    guard_macro = ifndef_match.group(1)\n                   \
    \ define_pattern = r'#\\s*define\\s+' + re.escape(guard_macro)\n             \
    \       if re.match(define_pattern, second_line.strip()):\n                  \
    \      lines_to_skip.add(first_line_idx)\n                        lines_to_skip.add(second_line_idx)\n\
    \                        lines_to_skip.add(last_endif_idx)\n\n    # --- Main Processing\
    \ Loop ---\n    first_line_emitted = False\n    conditional_depth = 0\n    local_block_depth\
    \ = None\n    skipping_local_branch = False\n    current_file_dir = os.path.dirname(path)\n\
    \n    for i, line in enumerate(lines):\n        stripped_line = line.strip()\n\
    \n        is_conditional_start = re.match(r'#\\s*(?:if|ifdef|ifndef)\\b', stripped_line)\n\
    \        is_local_start = re.match(\n            r'#\\s*(?:ifdef\\s+LOCAL\\b|if\\\
    s+defined\\s*(?:\\(\\s*LOCAL\\s*\\)|LOCAL\\b))',\n            stripped_line,\n\
    \        )\n        if is_conditional_start:\n            if local_block_depth\
    \ is None and is_local_start:\n                local_block_depth = conditional_depth\n\
    \                skipping_local_branch = True\n                conditional_depth\
    \ += 1\n                continue\n            conditional_depth += 1\n       \
    \ elif (\n            re.match(r'#\\s*else\\b', stripped_line)\n            and\
    \ local_block_depth is not None\n            and conditional_depth == local_block_depth\
    \ + 1\n        ):\n            skipping_local_branch = False\n            continue\n\
    \        elif re.match(r'#\\s*endif\\b', stripped_line):\n            if (\n \
    \               local_block_depth is not None\n                and conditional_depth\
    \ == local_block_depth + 1\n            ):\n                conditional_depth\
    \ -= 1\n                local_block_depth = None\n                skipping_local_branch\
    \ = False\n                continue\n            conditional_depth = max(0, conditional_depth\
    \ - 1)\n\n        if skipping_local_branch:\n            continue\n\n        if\
    \ i in lines_to_skip:\n            continue\n\n        if not first_line_emitted:\n\
    \            print(f'#line {i + 1} \"{marker_name}\"')\n            first_line_emitted\
    \ = True\n\n        m = re.match(r'#\\s*include\\s*\"([^\"]+)\"', stripped_line)\n\
    \        if m:\n            header = m.group(1)\n            resolved = resolve_include(header,\
    \ current_file_dir)\n            if resolved:\n                expand_file(resolved,\
    \ header)\n                print(f'#line {i + 2} \"{marker_name}\"')\n       \
    \     else:\n                print(f'// [warning] include not found: {header}')\n\
    \                print(line, end='')\n        else:\n            print(line, end='')\n\
    \n    print(f'// END: {display_name}')\n\n\nif __name__ == '__main__':\n    if\
    \ len(sys.argv) != 2:\n        print(\"Usage: python3 expander.py <main_file.cpp>\
    \ > bundled_file.cpp\", file=sys.stderr)\n        sys.exit(1)\n\n    visited.clear()\n\
    \    expand_file(sys.argv[1])\n"
  dependsOn: []
  isVerificationFile: false
  path: expander.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: expander.py
layout: document
redirect_from:
- /library/expander.py
- /library/expander.py.html
title: expander.py
---
