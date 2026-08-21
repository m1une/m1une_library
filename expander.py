import argparse
import os
import re

LIBRARY_ROOT = os.path.abspath(os.path.dirname(__file__))
LIBRARY_PARENT = os.path.dirname(LIBRARY_ROOT)
INCLUDE_PATHS = ('.', LIBRARY_ROOT, LIBRARY_PARENT)
GITHUB_SOURCE_ROOT = 'https://github.com/m1une/m1une_library/blob/main'
visited = set()
skipped_defined_macros = {'LOCAL'}


def line_marker_name(display_name):
    """
    Builds a diagnostic filename that is safe for syntax highlighters.

    Ace misparses a #line filename containing a path separator and can treat the
    following source line as part of a string. The filename is only used for
    diagnostics, so keep its path context with a separator that cannot trigger
    that tokenizer bug.
    """
    return re.sub(r'[/\\]+', '::', display_name).replace('"', "'")


def resolve_include(header, current_file_dir):
    """
    Finds the absolute path for a given header file.
    It first checks relative to the current file's directory,
    then checks the global include paths.
    """
    relative_path = os.path.join(current_file_dir, header)
    if os.path.isfile(relative_path):
        return os.path.abspath(relative_path)

    for path in INCLUDE_PATHS:
        full_path = os.path.join(path, header)
        if os.path.isfile(full_path):
            return os.path.abspath(full_path)
    return None


def library_source_url(path):
    """Returns the GitHub URL for a file inside this library repository."""
    relative_path = os.path.relpath(os.path.abspath(path), LIBRARY_ROOT)
    if relative_path == os.pardir or relative_path.startswith(os.pardir + os.sep):
        return None
    return f'{GITHUB_SOURCE_ROOT}/{relative_path.replace(os.sep, "/")}'


def expand_file(path, display_name=None, mention_source=False):
    """
    Recursively expands a C++ file by inlining its local #include directives.
    It removes include guards and skips blocks guarded by a macro configured as
    unavailable for the generated submission.
    """
    abs_path = os.path.abspath(path)
    if abs_path in visited:
        return
    visited.add(abs_path)

    if display_name is None:
        display_name = os.path.relpath(path, LIBRARY_ROOT)
    marker_name = line_marker_name(display_name)

    print(f'// BEGIN: {display_name}')
    if mention_source:
        source_url = library_source_url(abs_path)
        if source_url:
            print(f'// Source: {source_url}')

    with open(path, encoding='utf-8') as f:
        lines = f.readlines()

    # --- Pre-processing Step: Identify lines to skip ---
    lines_to_skip = set()

    # Identify and mark include guards for removal
    if lines:
        # Method 1: #pragma once
        for i, line in enumerate(lines):
            if line.strip() == "#pragma once":
                lines_to_skip.add(i)
                break

        # Method 2: #ifndef/#define/#endif guards
        if not lines_to_skip and len(lines) >= 2:
            first_line_idx, first_line = -1, ""
            for i, line in enumerate(lines):
                if line.strip():
                    first_line_idx, first_line = i, line
                    break

            second_line_idx, second_line = -1, ""
            if first_line_idx != -1:
                for i in range(first_line_idx + 1, len(lines)):
                    if lines[i].strip():
                        second_line_idx, second_line = i, lines[i]
                        break

            last_endif_idx = -1
            for i in range(len(lines) - 1, -1, -1):
                if lines[i].strip().startswith('#endif'):
                    last_endif_idx = i
                    break

            if first_line_idx != -1 and second_line_idx != -1 and last_endif_idx != -1:
                ifndef_match = re.match(r'#\s*ifndef\s+([A-Z0-9_]+)\s*', first_line)
                if ifndef_match:
                    guard_macro = ifndef_match.group(1)
                    define_pattern = r'#\s*define\s+' + re.escape(guard_macro)
                    if re.match(define_pattern, second_line.strip()):
                        lines_to_skip.add(first_line_idx)
                        lines_to_skip.add(second_line_idx)
                        lines_to_skip.add(last_endif_idx)

    # --- Main Processing Loop ---
    first_line_emitted = False
    conditional_depth = 0
    skipped_block_depth = None
    skipping_guarded_branch = False
    current_file_dir = os.path.dirname(path)

    for i, line in enumerate(lines):
        stripped_line = line.strip()

        is_conditional_start = re.match(r'#\s*(?:if|ifdef|ifndef)\b', stripped_line)
        is_skipped_start = any(
            re.match(
                r'#\s*(?:ifdef\s+' + re.escape(macro)
                + r'\b|if\s+defined\s*(?:\(\s*' + re.escape(macro)
                + r'\s*\)|' + re.escape(macro) + r'\b))',
                stripped_line,
            )
            for macro in skipped_defined_macros
        )
        if is_conditional_start:
            if skipped_block_depth is None and is_skipped_start:
                skipped_block_depth = conditional_depth
                skipping_guarded_branch = True
                conditional_depth += 1
                continue
            conditional_depth += 1
        elif (
            re.match(r'#\s*else\b', stripped_line)
            and skipped_block_depth is not None
            and conditional_depth == skipped_block_depth + 1
        ):
            skipping_guarded_branch = False
            continue
        elif re.match(r'#\s*endif\b', stripped_line):
            if (
                skipped_block_depth is not None
                and conditional_depth == skipped_block_depth + 1
            ):
                conditional_depth -= 1
                skipped_block_depth = None
                skipping_guarded_branch = False
                continue
            conditional_depth = max(0, conditional_depth - 1)

        if skipping_guarded_branch:
            continue

        if i in lines_to_skip:
            continue

        if not first_line_emitted:
            print(f'#line {i + 1} "{marker_name}"')
            first_line_emitted = True

        m = re.match(r'#\s*include\s*"([^"]+)"', stripped_line)
        if m:
            header = m.group(1)
            resolved = resolve_include(header, current_file_dir)
            if resolved:
                expand_file(resolved, header, mention_source=True)
                print(f'#line {i + 2} "{marker_name}"')
            else:
                print(f'// [warning] include not found: {header}')
                print(line, end='')
        else:
            print(line, end='')

    print(f'// END: {display_name}')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Inline local C++ headers into a submission source.'
    )
    parser.add_argument(
        '--no-x86-simd',
        action='store_true',
        help='omit code guarded by M1UNE_FPS_HAS_X86_SIMD',
    )
    parser.add_argument('main_file', help='the C++ source file to expand')
    arguments = parser.parse_args()

    if arguments.no_x86_simd:
        skipped_defined_macros.add('M1UNE_FPS_HAS_X86_SIMD')
        print('#define M1UNE_FPS_DISABLE_X86_SIMD 1')

    visited.clear()
    expand_file(arguments.main_file)

    if arguments.no_x86_simd:
        print('#undef M1UNE_FPS_DISABLE_X86_SIMD')
