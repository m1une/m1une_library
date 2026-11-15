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
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.14/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.14/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 96, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "#!/usr/bin/env python3\n\"\"\"Differential testing of ordinary contest programs;\
    \ Python standard library only.\"\"\"\n\nimport argparse\nfrom dataclasses import\
    \ dataclass\nimport json\nimport math\nimport os\nfrom pathlib import Path\nimport\
    \ secrets\nimport shlex\nimport shutil\nimport signal\nimport subprocess\nimport\
    \ sys\nimport tempfile\n\n\nROOT = Path(__file__).resolve().parent\nDEFAULT_FLAGS\
    \ = \"-std=c++23 -O2 -gdwarf-3 -g -Wall -Wextra -ftrapv\"\nSEED_LIMIT = 1 << 64\n\
    \n\n@dataclass\nclass Result:\n    output: bytes = b\"\"\n    error: bytes = b\"\
    \"\n    status: str = \"not run\"\n\n    @property\n    def ok(self):\n      \
    \  return self.status == \"exit 0\"\n\n\ndef run(command, data, timeout):\n  \
    \  \"\"\"Use real stdin/stdout, including for fread/read-based custom I/O.\"\"\
    \"\n    try:\n        process = subprocess.Popen(\n            command, stdin=subprocess.PIPE,\
    \ stdout=subprocess.PIPE,\n            stderr=subprocess.PIPE, start_new_session=True,\n\
    \        )\n    except OSError as error:\n        return Result(error=str(error).encode(),\
    \ status=\"launch error\")\n    try:\n        output, error = process.communicate(data,\
    \ timeout=timeout)\n    except (subprocess.TimeoutExpired, KeyboardInterrupt)\
    \ as exception:\n        # Also kill descendants that might keep the output pipes\
    \ open.\n        try:\n            os.killpg(process.pid, signal.SIGKILL)\n  \
    \      except ProcessLookupError:\n            pass\n        output, error = process.communicate()\n\
    \        if isinstance(exception, KeyboardInterrupt):\n            raise\n   \
    \     return Result(output, error, f\"timeout after {timeout:g}s\")\n    if process.returncode\
    \ < 0:\n        number = -process.returncode\n        try:\n            name =\
    \ signal.Signals(number).name\n        except ValueError:\n            name =\
    \ \"unknown\"\n        status = f\"signal {number} ({name})\"\n    else:\n   \
    \     status = f\"exit {process.returncode}\"\n    return Result(output, error,\
    \ status)\n\n\ndef default_compiler():\n    if os.environ.get(\"CXX\"):\n    \
    \    return os.environ[\"CXX\"]\n    homebrew = \"/opt/homebrew/bin/g++-16\"\n\
    \    if Path(homebrew).is_file():\n        return homebrew\n    return shutil.which(\"\
    g++-16\") or \"g++\"\n\n\ndef prepare(path, name, directory, compiler, flags):\n\
    \    path = path.resolve()\n    if not path.is_file():\n        raise ValueError(f\"\
    file not found: {path}\")\n    if path.suffix not in (\".cpp\", \".cc\", \".cxx\"\
    ):\n        if not os.access(path, os.X_OK):\n            raise ValueError(f\"\
    not executable: {path}\")\n        return [str(path)]\n    executable = directory\
    \ / name\n    command = compiler + flags + [\"-I\", str(ROOT), str(path), \"-o\"\
    , str(executable)]\n    print(f\"Compiling {path.name}\", flush=True)\n    # Inherit\
    \ compiler diagnostics. A compile failure never runs an old binary.\n    if subprocess.run(command).returncode:\n\
    \        raise ValueError(f\"compilation failed: {path}\")\n    return [str(executable)]\n\
    \n\ndef show(label, data):\n    print(f\"--- {label} ---\")\n    value = data.decode(\"\
    utf-8\", errors=\"replace\")\n    print(value, end=\"\" if value.endswith(\"\\\
    n\") else \"\\n\")\n\n\ndef report_failure(args, seed, trial, case_seed, reason,\
    \ results):\n    directory = Path(tempfile.mkdtemp(prefix=\"stress-failure-\"\
    , dir=Path.cwd()))\n    generated, optimized, brute = results\n    (directory\
    \ / \"input.txt\").write_bytes(generated.output)\n    for name, result in zip((\"\
    generator\", \"optimized\", \"brute\"), results):\n        (directory / f\"{name}.out\"\
    ).write_bytes(result.output)\n        (directory / f\"{name}.err\").write_bytes(result.error)\n\
    \    metadata = dict(\n        seed=seed, case=trial + 1, case_seed=case_seed,\
    \ reason=reason,\n        status=dict(zip((\"generator\", \"optimized\", \"brute\"\
    ),\n                        (result.status for result in results))),\n       \
    \ command=[sys.executable, str(Path(__file__).resolve())] + args,\n    )\n   \
    \ (directory / \"report.json\").write_text(json.dumps(metadata, indent=2) + \"\
    \\n\")\n    print(f\"FAIL: {reason}; case={trial + 1}, seed={seed}, case_seed={case_seed}\"\
    )\n    show(\"input\", generated.output)\n    show(f\"optimized output ({optimized.status})\"\
    , optimized.output)\n    show(f\"brute output ({brute.status})\", brute.output)\n\
    \    for name, result in zip((\"generator\", \"optimized\", \"brute\"), results):\n\
    \        if result.error:\n            show(f\"{name} stderr ({result.status})\"\
    , result.error)\n    print(f\"Saved: {directory}\")\n    replay = metadata[\"\
    command\"] + [\"--seed\", str(case_seed), \"--cases\", \"1\"]\n    print(f\"Replay:\
    \ {shlex.join(replay)}\")\n\n\ndef main(argv=None):\n    argv = list(sys.argv[1:]\
    \ if argv is None else argv)\n    parser = argparse.ArgumentParser(description=__doc__)\n\
    \    parser.add_argument(\"solution\", nargs=\"?\", default=\"main.cpp\")\n  \
    \  parser.add_argument(\"brute\", nargs=\"?\", default=\"brute.cpp\")\n    parser.add_argument(\"\
    generator\", nargs=\"?\", default=\"gen.cpp\")\n    parser.add_argument(\"--seed\"\
    , type=int, help=\"unsigned 64-bit first case seed (default: random)\")\n    parser.add_argument(\"\
    --cases\", type=int, default=1000, help=\"number of cases (default: 1000)\")\n\
    \    parser.add_argument(\"--timeout\", type=float, default=2.0, help=\"seconds\
    \ per program per case (default: 2)\")\n    parser.add_argument(\"--exact\", action=\"\
    store_true\", help=\"compare bytes instead of whitespace-separated tokens\")\n\
    \    parser.add_argument(\"--cxx\", default=default_compiler(), help=\"compiler\
    \ command (default: CXX, Homebrew GCC 16, g++-16, g++)\")\n    parser.add_argument(\"\
    --cxxflags\", default=os.environ.get(\"CXXFLAGS\", DEFAULT_FLAGS),\n         \
    \               help=\"compiler flags; replaces defaults (also reads CXXFLAGS)\"\
    )\n    args = parser.parse_args(argv)\n    if args.cases <= 0:\n        parser.error(\"\
    --cases must be positive\")\n    if args.seed is not None and not 0 <= args.seed\
    \ < SEED_LIMIT:\n        parser.error(\"--seed must be in [0, 2^64)\")\n    if\
    \ not math.isfinite(args.timeout) or args.timeout <= 0:\n        parser.error(\"\
    --timeout must be finite and positive\")\n    seed = secrets.randbits(64) if args.seed\
    \ is None else args.seed\n    print(f\"seed={seed}, cases={args.cases}, timeout={args.timeout:g}s\"\
    , flush=True)\n    try:\n        with tempfile.TemporaryDirectory(prefix=\"m1une-stress-\"\
    ) as temporary:\n            directory = Path(temporary)\n            compiler,\
    \ flags = shlex.split(args.cxx), shlex.split(args.cxxflags)\n            if not\
    \ compiler:\n                raise ValueError(\"empty compiler command\")\n  \
    \          solution = prepare(Path(args.solution), \"optimized\", directory, compiler,\
    \ flags)\n            brute = prepare(Path(args.brute), \"brute\", directory,\
    \ compiler, flags)\n            generator = prepare(Path(args.generator), \"generator\"\
    , directory, compiler, flags)\n            for trial in range(args.cases):\n \
    \               case_seed = (seed + trial) % SEED_LIMIT\n                generated\
    \ = run(generator + [str(case_seed)], b\"\", args.timeout)\n                optimized,\
    \ expected = Result(), Result()\n                reason = None\n             \
    \   if not generated.ok:\n                    reason = f\"generator: {generated.status}\"\
    \n                else:\n                    optimized = run(solution, generated.output,\
    \ args.timeout)\n                    # Run both on this input, even after a crash,\
    \ for diagnosis.\n                    expected = run(brute, generated.output,\
    \ args.timeout)\n                    if not optimized.ok:\n                  \
    \      reason = f\"optimized: {optimized.status}\"\n                    elif not\
    \ expected.ok:\n                        reason = f\"brute: {expected.status}\"\
    \n                    elif ((optimized.output != expected.output) if args.exact\
    \ else\n                          (optimized.output.split() != expected.output.split())):\n\
    \                        reason = \"output mismatch\"\n                if reason:\n\
    \                    report_failure(argv, seed, trial, case_seed, reason,\n  \
    \                                 (generated, optimized, expected))\n        \
    \            return 1\n                if (trial + 1) % 100 == 0:\n          \
    \          print(f\"Passed {trial + 1} cases\", flush=True)\n            print(f\"\
    OK: {args.cases} cases, seed={seed}\")\n            return 0\n    except (OSError,\
    \ ValueError) as error:\n        print(f\"stress: {error}\", file=sys.stderr)\n\
    \        return 2\n    except KeyboardInterrupt:\n        print(\"\\nstress: interrupted\"\
    , file=sys.stderr)\n        return 130\n\n\nif __name__ == \"__main__\":\n   \
    \ sys.exit(main())\n"
  dependsOn: []
  isVerificationFile: false
  path: stress.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: stress.py
layout: document
redirect_from:
- /library/stress.py
- /library/stress.py.html
title: stress.py
---
