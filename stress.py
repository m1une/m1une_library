#!/usr/bin/env python3
"""Differential testing of ordinary contest programs; Python standard library only."""

import argparse
from dataclasses import dataclass
import json
import math
import os
from pathlib import Path
import secrets
import shlex
import shutil
import signal
import subprocess
import sys
import tempfile


ROOT = Path(__file__).resolve().parent
DEFAULT_FLAGS = "-std=c++23 -O2 -gdwarf-3 -g -Wall -Wextra -ftrapv"
SEED_LIMIT = 1 << 64


@dataclass
class Result:
    output: bytes = b""
    error: bytes = b""
    status: str = "not run"

    @property
    def ok(self):
        return self.status == "exit 0"


def run(command, data, timeout):
    """Use real stdin/stdout, including for fread/read-based custom I/O."""
    try:
        process = subprocess.Popen(
            command, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            stderr=subprocess.PIPE, start_new_session=True,
        )
    except OSError as error:
        return Result(error=str(error).encode(), status="launch error")
    try:
        output, error = process.communicate(data, timeout=timeout)
    except (subprocess.TimeoutExpired, KeyboardInterrupt) as exception:
        # Also kill descendants that might keep the output pipes open.
        try:
            os.killpg(process.pid, signal.SIGKILL)
        except ProcessLookupError:
            pass
        output, error = process.communicate()
        if isinstance(exception, KeyboardInterrupt):
            raise
        return Result(output, error, f"timeout after {timeout:g}s")
    if process.returncode < 0:
        number = -process.returncode
        try:
            name = signal.Signals(number).name
        except ValueError:
            name = "unknown"
        status = f"signal {number} ({name})"
    else:
        status = f"exit {process.returncode}"
    return Result(output, error, status)


def default_compiler():
    if os.environ.get("CXX"):
        return os.environ["CXX"]
    homebrew = "/opt/homebrew/bin/g++-16"
    if Path(homebrew).is_file():
        return homebrew
    return shutil.which("g++-16") or "g++"


def prepare(path, name, directory, compiler, flags):
    path = path.resolve()
    if not path.is_file():
        raise ValueError(f"file not found: {path}")
    if path.suffix not in (".cpp", ".cc", ".cxx"):
        if not os.access(path, os.X_OK):
            raise ValueError(f"not executable: {path}")
        return [str(path)]
    executable = directory / name
    command = compiler + flags + ["-I", str(ROOT), str(path), "-o", str(executable)]
    print(f"Compiling {path.name}", flush=True)
    # Inherit compiler diagnostics. A compile failure never runs an old binary.
    if subprocess.run(command).returncode:
        raise ValueError(f"compilation failed: {path}")
    return [str(executable)]


def show(label, data):
    print(f"--- {label} ---")
    value = data.decode("utf-8", errors="replace")
    print(value, end="" if value.endswith("\n") else "\n")


def report_failure(args, seed, trial, case_seed, reason, results):
    directory = Path(tempfile.mkdtemp(prefix="stress-failure-", dir=Path.cwd()))
    generated, optimized, brute = results
    (directory / "input.txt").write_bytes(generated.output)
    for name, result in zip(("generator", "optimized", "brute"), results):
        (directory / f"{name}.out").write_bytes(result.output)
        (directory / f"{name}.err").write_bytes(result.error)
    metadata = dict(
        seed=seed, case=trial + 1, case_seed=case_seed, reason=reason,
        status=dict(zip(("generator", "optimized", "brute"),
                        (result.status for result in results))),
        command=[sys.executable, str(Path(__file__).resolve())] + args,
    )
    (directory / "report.json").write_text(json.dumps(metadata, indent=2) + "\n")
    print(f"FAIL: {reason}; case={trial + 1}, seed={seed}, case_seed={case_seed}")
    show("input", generated.output)
    show(f"optimized output ({optimized.status})", optimized.output)
    show(f"brute output ({brute.status})", brute.output)
    for name, result in zip(("generator", "optimized", "brute"), results):
        if result.error:
            show(f"{name} stderr ({result.status})", result.error)
    print(f"Saved: {directory}")
    replay = metadata["command"] + ["--seed", str(case_seed), "--cases", "1"]
    print(f"Replay: {shlex.join(replay)}")


def main(argv=None):
    argv = list(sys.argv[1:] if argv is None else argv)
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("solution", nargs="?", default="main.cpp")
    parser.add_argument("brute", nargs="?", default="brute.cpp")
    parser.add_argument("generator", nargs="?", default="gen.cpp")
    parser.add_argument("--seed", type=int, help="unsigned 64-bit first case seed (default: random)")
    parser.add_argument("--cases", type=int, default=1000, help="number of cases (default: 1000)")
    parser.add_argument("--timeout", type=float, default=2.0, help="seconds per program per case (default: 2)")
    parser.add_argument("--exact", action="store_true", help="compare bytes instead of whitespace-separated tokens")
    parser.add_argument("--cxx", default=default_compiler(), help="compiler command (default: CXX, Homebrew GCC 16, g++-16, g++)")
    parser.add_argument("--cxxflags", default=os.environ.get("CXXFLAGS", DEFAULT_FLAGS),
                        help="compiler flags; replaces defaults (also reads CXXFLAGS)")
    args = parser.parse_args(argv)
    if args.cases <= 0:
        parser.error("--cases must be positive")
    if args.seed is not None and not 0 <= args.seed < SEED_LIMIT:
        parser.error("--seed must be in [0, 2^64)")
    if not math.isfinite(args.timeout) or args.timeout <= 0:
        parser.error("--timeout must be finite and positive")
    seed = secrets.randbits(64) if args.seed is None else args.seed
    print(f"seed={seed}, cases={args.cases}, timeout={args.timeout:g}s", flush=True)
    try:
        with tempfile.TemporaryDirectory(prefix="m1une-stress-") as temporary:
            directory = Path(temporary)
            compiler, flags = shlex.split(args.cxx), shlex.split(args.cxxflags)
            if not compiler:
                raise ValueError("empty compiler command")
            solution = prepare(Path(args.solution), "optimized", directory, compiler, flags)
            brute = prepare(Path(args.brute), "brute", directory, compiler, flags)
            generator = prepare(Path(args.generator), "generator", directory, compiler, flags)
            for trial in range(args.cases):
                case_seed = (seed + trial) % SEED_LIMIT
                generated = run(generator + [str(case_seed)], b"", args.timeout)
                optimized, expected = Result(), Result()
                reason = None
                if not generated.ok:
                    reason = f"generator: {generated.status}"
                else:
                    optimized = run(solution, generated.output, args.timeout)
                    # Run both on this input, even after a crash, for diagnosis.
                    expected = run(brute, generated.output, args.timeout)
                    if not optimized.ok:
                        reason = f"optimized: {optimized.status}"
                    elif not expected.ok:
                        reason = f"brute: {expected.status}"
                    elif ((optimized.output != expected.output) if args.exact else
                          (optimized.output.split() != expected.output.split())):
                        reason = "output mismatch"
                if reason:
                    report_failure(argv, seed, trial, case_seed, reason,
                                   (generated, optimized, expected))
                    return 1
                if (trial + 1) % 100 == 0:
                    print(f"Passed {trial + 1} cases", flush=True)
            print(f"OK: {args.cases} cases, seed={seed}")
            return 0
    except (OSError, ValueError) as error:
        print(f"stress: {error}", file=sys.stderr)
        return 2
    except KeyboardInterrupt:
        print("\nstress: interrupted", file=sys.stderr)
        return 130


if __name__ == "__main__":
    sys.exit(main())
