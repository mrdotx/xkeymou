# xkeymou

This program is a replacement for the physical mouse in Linux on X11.

## Installation

Edit config.mk to match your local setup (xkeymou is installed into
the /usr/local namespace by default)

```bash
make clean install
```

If you are not using an Arch based distro you might have to install some headers,
e.g. on Debian based distros:

```bash
apt-get install libx11-dev libxtst-dev
```

## Run

```bash
xkeymou
```

## Manual

You can view the manual by running `man xkeymou` or `man xkeymoy.1`,
if you've already ran `make clean install`.

## Known issues

- not all clicks work in all applications
