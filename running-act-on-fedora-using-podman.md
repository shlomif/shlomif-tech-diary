First, change the line in /etc/containers/registries.conf
to read:

```
short-name-mode="permissive"
```

Also run `sudo dnf install podman-docker`.

Per https://github.com/nektos/act/issues/303#issuecomment-882069025
run these commands:

```
systemctl enable --now --user podman.socket
systemctl start --user podman.socket
export DOCKER_HOST=unix://$XDG_RUNTIME_DIR/podman/podman.sock
```

Then you can invoke `act`.

**License:**

Except for the code from https://github.com/nektos/act/issues/303#issuecomment-882069025 , the authors (Shlomi Fish) hereby place this work, written in 2021, under [CC0 / Public Domain](https://creativecommons.org/choose/zero/).
