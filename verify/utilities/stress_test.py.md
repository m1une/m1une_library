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
  code: "\"\"\"Local/CI integration tests: python3 verify/utilities/stress_test.py.\"\
    \"\"\n\nimport json\nfrom pathlib import Path\nimport shlex\nimport shutil\nimport\
    \ subprocess\nimport sys\nimport tempfile\nimport unittest\n\nROOT = Path(__file__).resolve().parents[2]\n\
    sys.path.insert(0, str(ROOT))\nimport stress\n\n\nclass StressTest(unittest.TestCase):\n\
    \    @classmethod\n    def setUpClass(cls):\n        cls.build = tempfile.TemporaryDirectory(prefix=\"\
    stress build \")\n        cls.addClassCleanup(cls.build.cleanup)\n        cls.binaries\
    \ = {}\n        for name in (\"main\", \"brute\", \"gen\", \"wrong\"):\n     \
    \       cls.binaries[name] = stress.prepare(\n                ROOT / \"examples/stress\"\
    \ / f\"{name}.cpp\", name,\n                Path(cls.build.name), shlex.split(stress.default_compiler()),\n\
    \                shlex.split(stress.DEFAULT_FLAGS),\n            )[0]\n\n    def\
    \ setUp(self):\n        temporary = tempfile.TemporaryDirectory(prefix=\"stress\
    \ cases \")\n        self.addCleanup(temporary.cleanup)\n        self.directory\
    \ = Path(temporary.name)\n\n    def script(self, name, body):\n        path =\
    \ self.directory / name\n        path.write_text(f\"#!{sys.executable}\\nimport\
    \ sys, os, signal, time\\n{body}\\n\")\n        path.chmod(0o755)\n        return\
    \ str(path)\n\n    def invoke(self, solution, brute, generator, *options):\n \
    \       return subprocess.run(\n            [sys.executable, str(ROOT / \"stress.py\"\
    ), solution, brute, generator,\n             \"--seed\", \"42\", \"--cases\",\
    \ \"5\", *options],\n            cwd=self.directory, stdout=subprocess.PIPE, stderr=subprocess.PIPE,\n\
    \            text=True, timeout=60,\n        )\n\n    def failure(self, completed):\n\
    \        self.assertEqual(completed.returncode, 1, completed.stdout + completed.stderr)\n\
    \        directories = list(self.directory.glob(\"stress-failure-*\"))\n     \
    \   self.assertEqual(len(directories), 1)\n        directory = directories[0]\n\
    \        return directory, json.loads((directory / \"report.json\").read_text())\n\
    \n    def test_custom_io_example(self):\n        result = self.invoke(self.binaries[\"\
    main\"], self.binaries[\"brute\"],\n                             self.binaries[\"\
    gen\"], \"--cases\", \"100\")\n        self.assertEqual(result.returncode, 0,\
    \ result.stdout + result.stderr)\n        self.assertIn(\"OK: 100 cases, seed=42\"\
    , result.stdout)\n        self.assertFalse(list(self.directory.glob(\"stress-failure-*\"\
    )))\n\n    def test_default_source_workflow(self):\n        for name in (\"main\"\
    , \"brute\", \"gen\"):\n            shutil.copyfile(ROOT / \"examples/stress\"\
    \ / f\"{name}.cpp\",\n                            self.directory / f\"{name}.cpp\"\
    )\n        existing_binary = self.directory / \"a.out\"\n        existing_binary.write_bytes(b\"\
    keep the normal build\")\n        result = subprocess.run(\n            [sys.executable,\
    \ str(ROOT / \"stress.py\"), \"--seed\", \"42\", \"--cases\", \"10\"],\n     \
    \       cwd=self.directory, capture_output=True, text=True, timeout=60,\n    \
    \    )\n        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)\n\
    \        self.assertIn(\"OK: 10 cases, seed=42\", result.stdout)\n        self.assertEqual(existing_binary.read_bytes(),\
    \ b\"keep the normal build\")\n        self.assertFalse((self.directory / \"optimized\"\
    ).exists())\n\n    def test_deliberately_wrong_example(self):\n        result\
    \ = self.invoke(self.binaries[\"wrong\"], self.binaries[\"brute\"],\n        \
    \                     self.binaries[\"gen\"])\n        directory, metadata = self.failure(result)\n\
    \        self.assertEqual(metadata[\"reason\"], \"output mismatch\")\n       \
    \ self.assertIn(\"seed=42\", result.stdout)\n        self.assertIn(\"--- input\
    \ ---\", result.stdout)\n        self.assertIn(\"--- optimized output (exit 0)\
    \ ---\", result.stdout)\n        self.assertIn(\"--- brute output (exit 0) ---\"\
    , result.stdout)\n        self.assertNotEqual((directory / \"optimized.out\").read_bytes(),\n\
    \                            (directory / \"brute.out\").read_bytes())\n\n   \
    \ def test_stop_and_replay_later_case(self):\n        generator = self.script(\"\
    generator\", \"\"\"\nwith open('seeds.txt', 'a') as log:\n    log.write(sys.argv[1]\
    \ + '\\\\n')\nprint(sys.argv[1])\n\"\"\")\n        optimized = self.script(\"\
    optimized\", \"n = int(input()); print(n + (n == 9))\")\n        brute = self.script(\"\
    brute\", \"print(input())\")\n        result = self.invoke(optimized, brute, generator,\
    \ \"--seed\", \"7\", \"--cases\", \"10\")\n        directory, metadata = self.failure(result)\n\
    \        self.assertEqual((metadata[\"seed\"], metadata[\"case\"], metadata[\"\
    case_seed\"]),\n                         (7, 3, 9))\n        self.assertEqual((self.directory\
    \ / \"seeds.txt\").read_text(), \"7\\n8\\n9\\n\")\n        replay = next(line.removeprefix(\"\
    Replay: \") for line in result.stdout.splitlines()\n                      if line.startswith(\"\
    Replay: \"))\n        repeated = subprocess.run(shlex.split(replay), cwd=self.directory,\n\
    \                                  capture_output=True, text=True, timeout=10)\n\
    \        self.assertEqual(repeated.returncode, 1, repeated.stdout + repeated.stderr)\n\
    \        self.assertIn(\"case=1, seed=9, case_seed=9\", repeated.stdout)\n   \
    \     for other in self.directory.glob(\"stress-failure-*\"):\n            self.assertEqual((directory\
    \ / \"input.txt\").read_bytes(),\n                             (other / \"input.txt\"\
    ).read_bytes())\n\n    def test_tokens_and_exact_comparison(self):\n        optimized\
    \ = self.script(\"optimized\", \"print(' 1  2\\\\n')\")\n        brute = self.script(\"\
    brute\", \"print('1\\\\n2')\")\n        generator = self.script(\"generator\"\
    , \"print('input')\")\n        result = self.invoke(optimized, brute, generator)\n\
    \        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)\n\
    \        self.failure(self.invoke(optimized, brute, generator, \"--exact\"))\n\
    \n    def test_program_failures(self):\n        good = self.script(\"good\", \"\
    print('answer')\")\n        generator = self.script(\"generator\", \"print('input')\"\
    )\n        failures = (\n            (\"optimized\", \"print('partial', flush=True);\
    \ print('diagnostic', file=sys.stderr); sys.exit(7)\", \"exit 7\"),\n        \
    \    (\"optimized\", \"os.kill(os.getpid(), signal.SIGTERM)\", \"signal 15 (SIGTERM)\"\
    ),\n            (\"optimized\", \"print('partial', flush=True); time.sleep(10)\"\
    , \"timeout after 2s\"),\n            (\"brute\", \"sys.exit(9)\", \"exit 9\"\
    ),\n            (\"generator\", \"print('partial input', flush=True); sys.exit(8)\"\
    , \"exit 8\"),\n            (\"generator\", \"time.sleep(10)\", \"timeout after\
    \ 2s\"),\n        )\n        for index, (role, body, status) in enumerate(failures):\n\
    \            with self.subTest(role=role, status=status):\n                bad\
    \ = self.script(f\"bad{index}\", body)\n                programs = dict(optimized=good,\
    \ brute=good, generator=generator)\n                programs[role] = bad\n   \
    \             result = self.invoke(programs[\"optimized\"], programs[\"brute\"\
    ],\n                                     programs[\"generator\"], \"--timeout\"\
    , \"2\")\n                directory, metadata = self.failure(result)\n       \
    \         checked = self.directory / f\"checked-{index}\"\n                directory.rename(checked)\n\
    \                directory = checked\n                self.assertEqual(metadata[\"\
    reason\"], f\"{role}: {status}\")\n                if role == \"generator\":\n\
    \                    self.assertEqual(metadata[\"status\"][\"optimized\"], \"\
    not run\")\n                else:\n                    self.assertEqual((directory\
    \ / \"input.txt\").read_bytes(), b\"input\\n\")\n                if index == 0:\n\
    \                    self.assertEqual((directory / \"optimized.out\").read_bytes(),\
    \ b\"partial\\n\")\n                    self.assertIn(\"diagnostic\", result.stdout)\n\
    \                    self.assertEqual(metadata[\"status\"][\"brute\"], \"exit\
    \ 0\")\n\n    def test_compile_failure_and_invalid_arguments(self):\n        bad_source\
    \ = self.directory / \"broken.cpp\"\n        bad_source.write_text(\"this is not\
    \ C++\\n\")\n        result = self.invoke(str(bad_source), self.binaries[\"brute\"\
    ], self.binaries[\"gen\"])\n        self.assertEqual(result.returncode, 2)\n \
    \       self.assertIn(\"compilation failed\", result.stderr)\n        for option,\
    \ value in ((\"--cases\", \"0\"), (\"--seed\", \"-1\"),\n                    \
    \          (\"--seed\", str(1 << 64)), (\"--timeout\", \"nan\")):\n          \
    \  result = self.invoke(self.binaries[\"main\"], self.binaries[\"brute\"],\n \
    \                                self.binaries[\"gen\"], option, value)\n    \
    \        self.assertEqual(result.returncode, 2)\n\n    def test_seed_wraparound(self):\n\
    \        generator = self.script(\"generator\", \"\"\"\nwith open('seeds.txt',\
    \ 'a') as log:\n    log.write(sys.argv[1] + '\\\\n')\nprint('input')\n\"\"\")\n\
    \        good = self.script(\"good\", \"print('answer')\")\n        result = self.invoke(good,\
    \ good, generator, \"--seed\", str((1 << 64) - 1), \"--cases\", \"2\")\n     \
    \   self.assertEqual(result.returncode, 0, result.stdout + result.stderr)\n  \
    \      self.assertEqual((self.directory / \"seeds.txt\").read_text(), f\"{(1 <<\
    \ 64) - 1}\\n0\\n\")\n\n\nif __name__ == \"__main__\":\n    unittest.main()\n"
  dependsOn: []
  isVerificationFile: false
  path: verify/utilities/stress_test.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: verify/utilities/stress_test.py
layout: document
redirect_from:
- /library/verify/utilities/stress_test.py
- /library/verify/utilities/stress_test.py.html
title: verify/utilities/stress_test.py
---
