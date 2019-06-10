# Tip: For a fast startup time, make sure that Python imported modules and their ancestor namespaces are lightweight (note pbr users)

**TL;DR**: For a fast startup/load time of Python programs, make sure that Python imported modules and their ancestor namespaces are lightweight and free of fluff. This affects users of [pbr](https://github.com/openstack/cookiecutter) whose default `__init__.py` file contains `import pbr.version`.

# The longer story

A while ago I noticed that the test suite of [PySol FC](https://pysolfc.sourceforge.io/), a Python project I comaintain, [took longer than previously](https://github.com/shlomif/PySolFC/issues/119) to run - 51 seconds instead of 30 seconds. At first I suspected it was the fault of the low latency kernel I used, but the time did not improve much with the normal kernel. As an old commit ran fine, I did a git [bisect](https://en.wikipedia.org/wiki/Bisection_%28software_engineering%29) which pointed to [this commit](https://github.com/shlomif/PySolFC/commit/74441a1746dc81bd7f0b8eaab698a48c66605886), which replaced some functionality with a [PyPI module](https://pypi.org/project/pysol-cards/) I extracted.

I tried reverting the offending commit in a git branch (and fixing a small breakage), and it improved matters. So the problem was with importing the module.

At first I tried splitting the only used (so far) class into its own module avoiding some of the fluff of the rest of the original. It did not improve matters a lot.

Then I suspected that the upper `pysol_cards/__init__.py` was also being loaded and an [strace](https://en.wikipedia.org/wiki/Strace) session confirmed it. I looked into its contents and saw this:

```python
# -*- coding: utf-8 -*-

# Licensed under the Apache License, Version 2.0 (the "License"); you may
# not use this file except in compliance with the License. You may obtain
# a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations
# under the License.

import pbr.version


__version__ = pbr.version.VersionInfo(
    'pysol_cards').version_string()

```

I suspected that it was costly startup time-wise and emptied the file. And that indeed turned out to be the cause of the slowdown, and the test suite's
time was reduced to 30-35 seconds.

One note is that one peculiar trait of the test suite that may have contributed to the slowdown is that we [test](https://github.com/shlomif/PySolFC/blob/master/scripts/gen_individual_importing_tests.py) that individually importing each module is working in its own program, which used to be broken for some modules in older versions of PySolFC.

Also of note is [“Why Userspace Sucks”](https://www.kernel.org/doc/ols/2006/ols2006v1-pages-441-450.pdf) by Dave Jones which pinpoints various misbehaviours that make software applications slower.
