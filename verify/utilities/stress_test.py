"""Local/CI integration tests: python3 verify/utilities/stress_test.py."""

import json
from pathlib import Path
import shlex
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
import stress


class StressTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.build = tempfile.TemporaryDirectory(prefix="stress build ")
        cls.addClassCleanup(cls.build.cleanup)
        cls.binaries = {}
        for name in ("main", "brute", "gen", "wrong"):
            cls.binaries[name] = stress.prepare(
                ROOT / "examples/stress" / f"{name}.cpp", name,
                Path(cls.build.name), shlex.split(stress.default_compiler()),
                shlex.split(stress.DEFAULT_FLAGS),
            )[0]

    def setUp(self):
        temporary = tempfile.TemporaryDirectory(prefix="stress cases ")
        self.addCleanup(temporary.cleanup)
        self.directory = Path(temporary.name)

    def script(self, name, body):
        path = self.directory / name
        path.write_text(f"#!{sys.executable}\nimport sys, os, signal, time\n{body}\n")
        path.chmod(0o755)
        return str(path)

    def invoke(self, solution, brute, generator, *options):
        return subprocess.run(
            [sys.executable, str(ROOT / "stress.py"), solution, brute, generator,
             "--seed", "42", "--cases", "5", *options],
            cwd=self.directory, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
            text=True, timeout=60,
        )

    def failure(self, completed):
        self.assertEqual(completed.returncode, 1, completed.stdout + completed.stderr)
        directories = list(self.directory.glob("stress-failure-*"))
        self.assertEqual(len(directories), 1)
        directory = directories[0]
        return directory, json.loads((directory / "report.json").read_text())

    def test_custom_io_example(self):
        result = self.invoke(self.binaries["main"], self.binaries["brute"],
                             self.binaries["gen"], "--cases", "100")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn("OK: 100 cases, seed=42", result.stdout)
        self.assertFalse(list(self.directory.glob("stress-failure-*")))

    def test_default_source_workflow(self):
        for name in ("main", "brute", "gen"):
            shutil.copyfile(ROOT / "examples/stress" / f"{name}.cpp",
                            self.directory / f"{name}.cpp")
        existing_binary = self.directory / "a.out"
        existing_binary.write_bytes(b"keep the normal build")
        result = subprocess.run(
            [sys.executable, str(ROOT / "stress.py"), "--seed", "42", "--cases", "10"],
            cwd=self.directory, capture_output=True, text=True, timeout=60,
        )
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn("OK: 10 cases, seed=42", result.stdout)
        self.assertEqual(existing_binary.read_bytes(), b"keep the normal build")
        self.assertFalse((self.directory / "optimized").exists())

    def test_deliberately_wrong_example(self):
        result = self.invoke(self.binaries["wrong"], self.binaries["brute"],
                             self.binaries["gen"])
        directory, metadata = self.failure(result)
        self.assertEqual(metadata["reason"], "output mismatch")
        self.assertIn("seed=42", result.stdout)
        self.assertIn("--- input ---", result.stdout)
        self.assertIn("--- optimized output (exit 0) ---", result.stdout)
        self.assertIn("--- brute output (exit 0) ---", result.stdout)
        self.assertNotEqual((directory / "optimized.out").read_bytes(),
                            (directory / "brute.out").read_bytes())

    def test_stop_and_replay_later_case(self):
        generator = self.script("generator", """
with open('seeds.txt', 'a') as log:
    log.write(sys.argv[1] + '\\n')
print(sys.argv[1])
""")
        optimized = self.script("optimized", "n = int(input()); print(n + (n == 9))")
        brute = self.script("brute", "print(input())")
        result = self.invoke(optimized, brute, generator, "--seed", "7", "--cases", "10")
        directory, metadata = self.failure(result)
        self.assertEqual((metadata["seed"], metadata["case"], metadata["case_seed"]),
                         (7, 3, 9))
        self.assertEqual((self.directory / "seeds.txt").read_text(), "7\n8\n9\n")
        replay = next(line.removeprefix("Replay: ") for line in result.stdout.splitlines()
                      if line.startswith("Replay: "))
        repeated = subprocess.run(shlex.split(replay), cwd=self.directory,
                                  capture_output=True, text=True, timeout=10)
        self.assertEqual(repeated.returncode, 1, repeated.stdout + repeated.stderr)
        self.assertIn("case=1, seed=9, case_seed=9", repeated.stdout)
        for other in self.directory.glob("stress-failure-*"):
            self.assertEqual((directory / "input.txt").read_bytes(),
                             (other / "input.txt").read_bytes())

    def test_tokens_and_exact_comparison(self):
        optimized = self.script("optimized", "print(' 1  2\\n')")
        brute = self.script("brute", "print('1\\n2')")
        generator = self.script("generator", "print('input')")
        result = self.invoke(optimized, brute, generator)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.failure(self.invoke(optimized, brute, generator, "--exact"))

    def test_program_failures(self):
        good = self.script("good", "print('answer')")
        generator = self.script("generator", "print('input')")
        failures = (
            ("optimized", "print('partial', flush=True); print('diagnostic', file=sys.stderr); sys.exit(7)", "exit 7"),
            ("optimized", "os.kill(os.getpid(), signal.SIGTERM)", "signal 15 (SIGTERM)"),
            ("optimized", "print('partial', flush=True); time.sleep(10)", "timeout after 2s"),
            ("brute", "sys.exit(9)", "exit 9"),
            ("generator", "print('partial input', flush=True); sys.exit(8)", "exit 8"),
            ("generator", "time.sleep(10)", "timeout after 2s"),
        )
        for index, (role, body, status) in enumerate(failures):
            with self.subTest(role=role, status=status):
                bad = self.script(f"bad{index}", body)
                programs = dict(optimized=good, brute=good, generator=generator)
                programs[role] = bad
                result = self.invoke(programs["optimized"], programs["brute"],
                                     programs["generator"], "--timeout", "2")
                directory, metadata = self.failure(result)
                checked = self.directory / f"checked-{index}"
                directory.rename(checked)
                directory = checked
                self.assertEqual(metadata["reason"], f"{role}: {status}")
                if role == "generator":
                    self.assertEqual(metadata["status"]["optimized"], "not run")
                else:
                    self.assertEqual((directory / "input.txt").read_bytes(), b"input\n")
                if index == 0:
                    self.assertEqual((directory / "optimized.out").read_bytes(), b"partial\n")
                    self.assertIn("diagnostic", result.stdout)
                    self.assertEqual(metadata["status"]["brute"], "exit 0")

    def test_compile_failure_and_invalid_arguments(self):
        bad_source = self.directory / "broken.cpp"
        bad_source.write_text("this is not C++\n")
        result = self.invoke(str(bad_source), self.binaries["brute"], self.binaries["gen"])
        self.assertEqual(result.returncode, 2)
        self.assertIn("compilation failed", result.stderr)
        for option, value in (("--cases", "0"), ("--seed", "-1"),
                              ("--seed", str(1 << 64)), ("--timeout", "nan")):
            result = self.invoke(self.binaries["main"], self.binaries["brute"],
                                 self.binaries["gen"], option, value)
            self.assertEqual(result.returncode, 2)

    def test_seed_wraparound(self):
        generator = self.script("generator", """
with open('seeds.txt', 'a') as log:
    log.write(sys.argv[1] + '\\n')
print('input')
""")
        good = self.script("good", "print('answer')")
        result = self.invoke(good, good, generator, "--seed", str((1 << 64) - 1), "--cases", "2")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertEqual((self.directory / "seeds.txt").read_text(), f"{(1 << 64) - 1}\n0\n")


if __name__ == "__main__":
    unittest.main()
