/*
 * path:   /home/klassiker/.local/share/repos/xkeymou/util.c
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/xkeymou
 * date:   2022-07-05T10:30:16+0200
 */

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
