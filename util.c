/*
 * path:   /home/klassiker/.local/share/repos/xkeymou/util.c
 * author: klassiker [mrdotx]
 * url:    https://github.com/mrdotx/xkeymou
 * date:   2025-08-08T05:31:04+0200
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

    char *status = is_press ? "pressed " : "released";

    switch(button) {
        case 0:
            sprintf(string, "DUMMY %s ", status);
            break;
        case 1:
            sprintf(string, "LEFT %s  ", status);
            break;
        case 2:
            sprintf(string, "MIDDLE %s", status);
            break;
        case 3:
            sprintf(string, "RIGHT %s ", status);
            break;
    }

    return string;
}
