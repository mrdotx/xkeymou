# path:   /home/klassiker/.local/share/repos/xkeymou/config.mk
# author: klassiker [mrdotx]
# github: https://github.com/mrdotx/xkeymou
# date:   2024-05-13T08:50:08+0200

# tool info
NAME = xkeymou
VERSION = 0.1.5

# paths
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/share/man

CPPFLAGS = -DVERSION=\"$(VERSION)\" -D_DEFAULT_SOURCE
# if your system is not POSIX, add -std=c99 to CFLAGS
CFLAGS  = -Wall -g
LDFLAGS = -lX11 -lXtst -lpthread

# compiler and linker
# CC = c99
