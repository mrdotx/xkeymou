/*
 * path:   /home/klassiker/.local/share/repos/xkeymou/xkeymou.c
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/xkeymou
 * date:   2022-07-05T01:09:04+0200
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XTest.h>

#include "util.h"

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

#include "config.h"

Display *dpy;
Window root;
pthread_t movethread;

static unsigned int speed;

struct {
    float x,
          y,
          speed_x,
          speed_y;
} mouseinfo;

struct {
    float x,
          y,
          speed_x,
          speed_y;
} scrollinfo;

void get_pointer();
void move_relative(float x, float y);
void click(unsigned int button, Bool is_press);
void click_full(unsigned int button);
void scroll(float x, float y);
void handle_key(KeyCode keycode, Bool is_press, int debug);
void init_x();
void close_x();

void get_pointer() {
    int x,
        y,
        di;
    unsigned int dui;
    Window dummy;
    XQueryPointer(dpy, root, &dummy, &dummy, &x, &y, &di, &di, &dui);
    mouseinfo.x = x;
    mouseinfo.y = y;
}

void move_relative(float x, float y) {
    mouseinfo.x += x;
    mouseinfo.y += y;
    XWarpPointer(dpy, None, root, 0, 0, 0, 0,
            (int) mouseinfo.x, (int) mouseinfo.y);
    XFlush(dpy);
}

void click(unsigned int button, Bool is_press) {
    XTestFakeButtonEvent(dpy, button, is_press, CurrentTime);
    XFlush(dpy);
}

void click_full(unsigned int button) {
    XTestFakeButtonEvent(dpy, button, 1, CurrentTime);
    XTestFakeButtonEvent(dpy, button, 0, CurrentTime);
    XFlush(dpy);
}

void scroll(float x, float y) {
    scrollinfo.x += x;
    scrollinfo.y += y;
    while (scrollinfo.y <= -0.51) {
        scrollinfo.y += 1;
        click_full(4);
    }
    while (scrollinfo.y >= 0.51) {
        scrollinfo.y -= 1;
        click_full(5);
    }
    while (scrollinfo.x <= -0.51) {
        scrollinfo.x += 1;
        click_full(6);
    }
    while (scrollinfo.x >= 0.51) {
        scrollinfo.x -= 1;
        click_full(7);
    }
}

void init_x() {
    int i,
        screen;

    /* initialize support for concurrent threads */
    XInitThreads();

    dpy = XOpenDisplay((char *) 0);
    screen = DefaultScreen(dpy);
    root = RootWindow(dpy, screen);

    /* turn auto key repeat off */
    XAutoRepeatOff(dpy);

    /* grab keys until success */
    for (i = 0; i < 100; i++) {
        if (XGrabKeyboard(dpy, root, False, GrabModeAsync,
                GrabModeAsync, CurrentTime) == GrabSuccess) {
            return;
        }
        sleep_ms(10);
    }

    printf("(EE) xkeymou: grab keyboard failed\n");
    close_x(EXIT_FAILURE);
}

void close_x(int exit_status) {
    /* turn auto repeat on again */
    XAutoRepeatOn(dpy);
    XUngrabKey(dpy, AnyKey, AnyModifier, root);
    XCloseDisplay(dpy);
    exit(exit_status);
}

void *move_forever(void *val) {
    /* this function is executed in a seperate thread */
    while (1) {
        /* move mouse? */
        if (mouseinfo.speed_x != 0 || mouseinfo.speed_y != 0) {
            move_relative((float) mouseinfo.speed_x * speed / move_rate,
                          (float) mouseinfo.speed_y * speed / move_rate);
        }
        /* scroll? */
        if (scrollinfo.speed_x != 0 || scrollinfo.speed_y != 0) {
            scroll((float) scrollinfo.speed_x / move_rate,
                   (float) scrollinfo.speed_y / move_rate);
        }
        sleep_ms(1000 / move_rate);
    }
}

void handle_key(KeyCode keycode, Bool is_press, int debug) {
    unsigned int i;
    KeySym keysym;

    keysym = XkbKeycodeToKeysym(dpy, keycode, 0, 0);

    /* move bindings */
    for (i = 0; i < LENGTH(move_bindings); i++) {
        if (move_bindings[i].keysym == keysym) {
            int sign = is_press ? 1 : -1;
            mouseinfo.speed_x += sign * move_bindings[i].x;
            mouseinfo.speed_y += sign * move_bindings[i].y;
            if (debug == 1) \
                printf("(II) xkeymou: move x=%.0f y=%.0f\n", \
                        mouseinfo.speed_x, mouseinfo.speed_y);
        }
    }

    /* click bindings */
    for (i = 0; i < LENGTH(click_bindings); i++) {
        if (click_bindings[i].keysym == keysym) {
            click(click_bindings[i].button, is_press);
            if (debug == 1) \
                printf("(II) xkeymou: button %i %s\n", \
                        click_bindings[i].button, \
                        is_press ? "pressed" : "released");
        }
    }

    /* speed bindings */
    for (i = 0; i < LENGTH(speed_bindings); i++) {
        if (speed_bindings[i].keysym == keysym) {
            speed = is_press ? speed_bindings[i].speed : default_speed;
            if (debug == 1) \
                printf("(II) xkeymou: speed %i\n", speed);
        }
    }

    /* scroll bindings */
    for (i = 0; i < LENGTH(scroll_bindings); i++) {
        if (scroll_bindings[i].keysym == keysym) {
            int sign = is_press ? 1 : -1,
                scroll_x = 0,
                scroll_y = 0;

            scrollinfo.speed_x += sign * scroll_bindings[i].x;
            scrollinfo.speed_y += sign * scroll_bindings[i].y;

            if (scrollinfo.speed_x < 0) scroll_x = -1;
            if (scrollinfo.speed_x > 0) scroll_x = 1;
            if (scrollinfo.speed_y < 0) scroll_y = -1;
            if (scrollinfo.speed_y > 0) scroll_y = 1;

            scroll(scroll_x, scroll_y);
            if (debug == 1) \
                printf("(II) xkeymou: scroll x=%0.f y=%0.f\n", \
                        scrollinfo.speed_x, scrollinfo.speed_y);
        }
    }

    /* shell and exit bindings only on key release */
    if (!is_press) {
        /* shell bindings */
        for (i = 0; i < LENGTH(shell_bindings); i++) {
            if (shell_bindings[i].keysym == keysym) {
                if (debug == 1) \
                    printf("(II) xkeymou: exec \"%s\"\n", \
                            shell_bindings[i].command);
                if (fork() == 0) {
                    system(shell_bindings[i].command);
                    exit(EXIT_SUCCESS);
                }
            }
        }

        /* exit */
        for (i = 0; i < LENGTH(exit_keys); i++) {
            if (exit_keys[i] == keysym) {
                close_x(EXIT_SUCCESS);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    char keys_return[32];
    int debug = 0,
        rc,
        i,
        j;

    if (1 < argc) {
        if (0 == strcmp(argv[1], "-d")) {
            debug = 1;
        } else if (0 == strcmp(argv[1], "-i")) {
            puts("xkeymou-"VERSION);
            return EXIT_SUCCESS;
        } else {
            puts("usage: xkeymou [-d] [-i]");
            return EXIT_SUCCESS;
        }
    }

    init_x();

    get_pointer();
    mouseinfo.speed_x = 0;
    mouseinfo.speed_y = 0;
    speed = default_speed;

    scrollinfo.x = 0;
    scrollinfo.y = 0;
    scrollinfo.speed_x = 0;
    scrollinfo.speed_y = 0;

    /* start the thread for mouse movement and scrolling */
    rc = pthread_create(&movethread, NULL, &move_forever, NULL);
    if( rc != 0 ) {
        printf("(EE) xkeymou: unable to start thread.\n");
        return EXIT_FAILURE;
    }

    /* get the initial state of all keys */
    XQueryKeymap(dpy, keys_return);
    for (i = 0; i < 32; i++) {
        for (j = 0; j < 8; j++) {
            if (keys_return[i] & (1<<j)) {
                handle_key(8 * i + j, 1, debug);
            }
        }
    }

    /* handle key presses and releases */
    while(1) {
        XEvent event;
        XNextEvent(dpy, &event);

        switch (event.type) {
            case KeyPress:
            case KeyRelease:
                get_pointer();
                handle_key(event.xkey.keycode, \
                        event.xkey.type == KeyPress, debug);
                break;
        }
    }
}
