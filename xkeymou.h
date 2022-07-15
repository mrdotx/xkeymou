/*
 * path:   /home/klassiker/.local/share/repos/xkeymou/xkeymou.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/xkeymou
 * date:   2022-07-15T13:04:48+0200
 */

#include <X11/XKBlib.h>

typedef struct {
    KeySym keysym;
    float x,
          y;
} MoveBinding;

typedef struct {
    KeySym keysym;
    unsigned int button;
} ClickBinding;

typedef struct {
    KeySym keysym;
    float x,
          y;
} ScrollBinding;

typedef struct {
    KeySym keysym;
    unsigned int speed;
} SpeedBinding;

typedef struct {
    KeySym keysym;
    char *command;
} ShellBinding;

typedef struct {
    int point;
    char *command;
} ShellExec;

void shell_execute(int point, int is_debug);
void get_pointer();
void move_relative(float x, float y);
void click(unsigned int button, int is_press);
void click_full(unsigned int button);
void scroll(float x, float y);
void handle_key(KeyCode keycode, int is_press, int is_debug);
void init_x();
void close_x();
