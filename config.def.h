/*
 * path:   /home/klassiker/.local/share/repos/xkeymou/config.def.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/xkeymou
 * date:   2022-07-03T21:11:19+0200
 */

static const unsigned int move_rate = 50;

static const unsigned int default_speed = 500;

static SpeedBinding speed_bindings[] = {
    /* key          speed */
    { XK_v,         2000 },
    { XK_z,         50   },
};

static MoveBinding move_bindings[] = {
    /* key          x       y */
    { XK_k,         0,     -1 },
    { XK_j,         0,      1 },
    { XK_h,        -1,      0 },
    { XK_l,         1,      0 },
    { XK_Up,        0,     -1 },
    { XK_Down,      0,      1 },
    { XK_Left,     -1,      0 },
    { XK_Right,     1,      0 },
};

static ClickBinding click_bindings[] = {
    /* key          button (1 = left, 2 = middle, 3 = right) */
    { XK_Menu,      1 },
    { XK_space,     1 },
    { XK_c,         2 },
    { XK_x,         3 },
};

static ScrollBinding scroll_bindings[] = {
    /* key          x       y */
    { XK_d,         0,    -25 },
    { XK_s,         0,     25 },
    { XK_a,       -25,      0 },
    { XK_f,        25,      0 },
    { XK_Prior,     0,    -80 },
    { XK_Next,      0,     80 },
};

static ShellBinding shell_bindings[] = {
    /* key          command */
    { XK_Menu,      "i3_macros.sh --mousemove topright"    },
    { XK_Insert,    "i3_macros.sh --mousemove topleft"     },
    { XK_Home,      "i3_macros.sh --mousemove topright"    },
    { XK_Delete,    "i3_macros.sh --mousemove bottomleft"  },
    { XK_End,       "i3_macros.sh --mousemove bottomright" },
};

static KeySym exit_keys[] = {
    XK_Menu,
    XK_Escape,
    XK_q
};
