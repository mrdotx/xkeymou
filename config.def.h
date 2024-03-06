/*
 * path:   /home/klassiker/.local/share/repos/xkeymou/config.def.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/xkeymou
 * date:   2024-03-06T07:56:30+0100
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
    /* key          button (1 = left, 2 = middle, 3 = right, 0 = dummy) */
    { XK_Menu,      1 },
    { XK_BackSpace, 1 },
    { XK_space,     1 },
    { XK_c,         2 },
    { XK_x,         3 },
    { XK_0,         0 },
};

static ScrollBinding scroll_bindings[] = {
    /* key          x       y */
    { XK_w,         0,    -25 },
    { XK_s,         0,     25 },
    { XK_a,       -25,      0 },
    { XK_d,        25,      0 },
    { XK_Prior,     0,    -80 },
    { XK_Next,      0,     80 },
};

static ShellBinding shell_bindings[] = {
    /* key          command */
    { XK_Menu,      "i3_mouse_move.sh ne" },
    { XK_Insert,    "i3_mouse_move.sh nw" },
    { XK_Home,      "i3_mouse_move.sh ne" },
    { XK_Delete,    "i3_mouse_move.sh sw" },
    { XK_End,       "i3_mouse_move.sh se" },
};

static ShellExec shell_exec[] = {
    /* point        command (1 = at start, 2 = on exit) */
    { 1,            "systemctl --user stop xbanish.service"                                                         },
    { 1,            "polybar_services.sh --update"                                                                  },
    { 1,            "notify-send -t 0 'xkeymou' 'active' -h string:x-canonical-private-synchronous:xkeymou"         },
    { 2,            "notify-send -t 2500 'xkeymou' 'deactivated' -h string:x-canonical-private-synchronous:xkeymou" },
    { 2,            "systemctl --user start xbanish.service"                                                        },
    { 2,            "polybar_services.sh --update"                                                                  },
};

static KeySym exit_keys[] = {
    XK_Menu,
    XK_BackSpace,
    XK_Escape,
    XK_q
};
