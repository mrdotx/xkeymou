/*
 * path:   /home/klassiker/.local/share/repos/xkeymou/util.c
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/xkeymou
 * date:   2022-07-16T14:05:12+0200
 */

#include <stdio.h>
#include <time.h>

#include "util.h"

void sleep_ms(long ms) {
    struct timespec remaining, request = {
        SECS_TO_SLEEP,
        NSEC_TO_SLEEP * ms
    };

    nanosleep(&request, &remaining);
}

const char *get_direction(int x, int y) {
    static char string[16];

    if (0 == x && 0 == y) sprintf(string, "STOPPED        ");

    if (0 == x && 0 > y) sprintf(string, "UP             ");
    if (0 == x && 0 < y) sprintf(string, "DOWN           ");
    if (0 > x && 0 == y) sprintf(string, "LEFT           ");
    if (0 < x && 0 == y) sprintf(string, "RIGHT          ");

    if (0 > x && 0 > y) sprintf(string, "UP-LEFT        ");
    if (0 < x && 0 > y) sprintf(string, "UP-RIGHT       ");
    if (0 > x && 0 < y) sprintf(string, "DOWN-LEFT      ");
    if (0 < x && 0 < y) sprintf(string, "DOWN-RIGHT     ");

    return string;
}

const char *get_button(int button, int is_press) {
    static char string[16];

    if (0 == button) sprintf(string, "DUMMY %s ", \
            is_press ? "pressed " : "released");

    if (1 == button) sprintf(string, "LEFT %s  ", \
            is_press ? "pressed " : "released");
    if (2 == button) sprintf(string, "MIDDLE %s", \
            is_press ? "pressed " : "released");
    if (3 == button) sprintf(string, "RIGHT %s ", \
            is_press ? "pressed " : "released");

    return string;
}
