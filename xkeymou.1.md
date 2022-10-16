% XKEYMOU(1) Version\-VERSION | xkeymou Manual

# NAME

xkeymou - keyboard mouse for Linux on X11

# SYNOPSIS

**xkeymou** [**-d**] [**-i**]

# DESCRIPTION

**xkeymou** is a replacement for the physical mouse in Linux with the following features:

- move the mouse with different speeds
- click and grab
- scroll
- execute shell commands

# OPTIONS

Without given settings, start **xkeymou**.

**-d**
: Starts **xkeymou** and prints debug messages about move, click, speed, scroll, execution to stdout.

**-i**
: Prints the version number to stdout.

# CUSTOMIZATION

**xkeymou** can be customized by creating/editing a custom config.h and (re-)compiling the source code. The default values are as follows:

**move_rate** = *50*
: The rate at which the mouse moves in Hz (Does not change its speed).

**default_speed** = *500*
: The default speed of the mouse pointer in pixels per second.

***speed_bindings\****
: Keybindings to change the speed of the mouse pointer.

    | keybinding | speed |
    | :--------- | ----: |
    | v          | 2000  |
    | z          | 50    |

***move_bindings\****
: Keybindings to move the mouse pointer. It can also any other direction added (e.g. diagonals).

    | keybinding | x  | y  | move  |
    | :--------- | -: | -: | :---- |
    | k          | 0  | -1 | up    |
    | j          | 0  | 1  | down  |
    | h          | -1 | 0  | left  |
    | l          | 1  | 0  | right |
    | up         | 0  | -1 | up    |
    | down       | 0  | 1  | down  |
    | left       | -1 | 0  | left  |
    | right      | 1  | 0  | right |

***click_bindings\****
: Keybindings to click the mouse buttons.

    | keybinding | button* |
    | :--------- | :-----: |
    | menu       | 1       |
    | backspace  | 1       |
    | space      | 1       |
    | c          | 2       |
    | x          | 3       |
    | 0          | 0       |

    \* 1 = left, 2 = middle, 3 = right, 0 = dummy (in debug mode print the position without click)

***scroll_bindings\****
: Keybindings to scroll (A higher value scolls faster).

    | keybinding | x   | y   | scroll |
    | :--------- | --: | --: | :----- |
    | w          | 0   | -25 | up     |
    | s          | 0   | 25  | down   |
    | a          | -25 | 0   | left   |
    | d          | 25  | 0   | right  |
    | page up    | 0   | -80 | up     |
    | page down  | 0   | 80  | down   |

***shell_bindings\****
: Keybindings to execute shell command.

    | keybinding | command                               |
    | :--------- | :------------------------------------ |
    | menu       | i3_macros.sh \--movemouse topright    |
    | insert     | i3_macros.sh \--movemouse topleft     |
    | home       | i3_macros.sh \--movemouse topright    |
    | delete     | i3_macros.sh \--movemouse bottomleft  |
    | end        | i3_macros.sh \--movemouse bottomright |

***shell_exec\****
: Execute shell command at start or on exit.

    | point* | command                                                                                           |
    | :----: | :------------------------------------------------------------------------------------------------ |
    | 1      | systemctl \--user stop xbanish.service                                                            |
    | 1      | polybar_services.sh \--update                                                                     |
    | 1      | notify-send -t 0 \'xkeymou\' \'active\' -h string:x-canonical-private-synchronous:xkeymou         |
    | 2      | notify-send -t 2500 \'xkeymou\' \'deactivated\' -h string:x-canonical-private-synchronous:xkeymou |
    | 2      | systemctl \--user start xbanish.service                                                           |
    | 2      | polybar_services.sh \--update                                                                     |

    \* 1 = at start, 2 = on exit

***exit_keys\****
: Keybindings to exit on key release. This allows to click, execute shell command and exit with one key press/release.

    | keybinding | function                               |
    | :--------- | :------------------------------------- |
    | menu       | click left, moves the pointer and exit |
    | backspace  | click left and exit                    |
    | escape     | exit                                   |
    | q          | exit                                   |

# USAGE

When starting **xkeymou**, it grabs the keyboard with all defined bindings. When pressing an exit key, the program exits.

The usage is quite intuitive and with some practice, the pointer can be moved to a certain position very fast. Basically the mouse is controlled by pressing some keys that are defined in the config.h file, which are described in the *CUSTOMIZATION* section.

# EXAMPLES

| **xkeymou**
| **xkeymou** -d
| **xkeymou** -i

# BUGS

See GitHub Issues: *https://github.com/mrdotx/xkeymou/issues*

# AUTHORS

| **xkeymou** is a fork of **xmouseless** <*https://github.com/jbensmann/xmouseless*>.
| **xkeymou** was written by mrdotx <*klassiker@gmx.de*>

# SEE ALSO

**xmouseless**(1), **mouseless**(1)

# LICENSE

See the *LICENSE.md* file for the terms of redistribution.
