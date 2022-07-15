/*
 * path:   /home/klassiker/.local/share/repos/xkeymou/util.c
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/xkeymou
 * date:   2022-07-15T14:02:45+0200
 */

#include <stdio.h>
#include <time.h>

#include "util.h"

enum {
    SECS_TO_SLEEP = 0,
    NSEC_TO_SLEEP = 1000000
};

void sleep_ms(long ms) {
    struct timespec remaining, request = {
        SECS_TO_SLEEP,
        NSEC_TO_SLEEP * ms
    };

    nanosleep(&request, &remaining);
}

const char *get_direction(int x, int y) {
    static char string[11];

    if (0 == x && 0 == y) sprintf(string, "STOPPED");

    if (0 == x && 0 > y) sprintf(string, "UP");
    if (0 == x && 0 < y) sprintf(string, "DOWN");
    if (0 > x && 0 == y) sprintf(string, "LEFT");
    if (0 < x && 0 == y) sprintf(string, "RIGHT");

    if (0 > x && 0 > y) sprintf(string, "UP-LEFT");
    if (0 < x && 0 > y) sprintf(string, "UP-RIGHT");
    if (0 > x && 0 < y) sprintf(string, "DOWN-LEFT");
    if (0 < x && 0 < y) sprintf(string, "DOWN-RIGHT");

    return string;
}

const char *get_button(int button) {
    static char string[7];

    if (0 == button) sprintf(string, "DUMMY");

    if (1 == button) sprintf(string, "LEFT");
    if (2 == button) sprintf(string, "MIDDLE");
    if (3 == button) sprintf(string, "RIGHT");

    return string;
}
