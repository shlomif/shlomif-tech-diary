# Tip: For a fast startup time, make sure that Python imported modules and their ancestor namespaces are lightweight (note pbr users)

**TL;DR**: For a fast startup/load time of Python programs, make sure that Python imported modules and their ancestor namespaces are lightweight and free of fluff. This affects users of [pbr](https://github.com/openstack/cookiecutter) whose default `__init__.py` file contains `import pbr.version`.


