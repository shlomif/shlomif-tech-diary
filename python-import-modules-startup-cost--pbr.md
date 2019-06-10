# Tip: For a fast startup time, make sure that Python imported modules and their ancestor namespaces are lightweight (note pbr users)

**TL;DR**: For a fast startup/load time of Python programs, make sure that Python imported modules and their ancestor namespaces are lightweight and free of fluff. This affects users of [pbr](https://github.com/openstack/cookiecutter) whose default `__init__.py` file contains `import pbr.version`.

# The longer story

A while ago I noticed that the test suite of [PySol FC](https://pysolfc.sourceforge.io/), a Python project I comaintain, [took longer than previously](https://github.com/shlomif/PySolFC/issues/119) to run - 51 seconds instead of 30 seconds. At first I suspected it was the fault of the low latency kernel I used, but the time did not improve much with the normal kernel. As an old commit ran fine, I did a git [bisect](https://en.wikipedia.org/wiki/Bisection_%28software_engineering%29) which pointed to [this commit](https://github.com/shlomif/PySolFC/commit/74441a1746dc81bd7f0b8eaab698a48c66605886), which replaced some functionality with a [PyPI module](https://pypi.org/project/pysol-cards/) I extracted.

I tried reverting the offending commit in a git branch (and fixing a small breakage), and it improved matters. So the problem was with importing the module.

At first I tried splitting the only used (so far) class into its own module avoiding some of the fluff of the rest of the original. It did not improve matters a lot.

Then I suspected that `__init__.py` was also being loaded and an [strace](https://en.wikipedia.org/wiki/Strace) session confirmed it.
