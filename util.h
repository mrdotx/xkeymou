/*
 * path:   /home/klassiker/.local/share/repos/xkeymou/util.h
 * author: klassiker [mrdotx]
 * url:    https://github.com/mrdotx/xkeymou
 * date:   2025-08-08T05:31:08+0200
 */

/* macros */
#define LENGTH(X)   (sizeof X / sizeof X[0])

enum {
    SECS_TO_SLEEP = 0,
    NSEC_TO_SLEEP = 1000000
};

int nanosleep(const struct timespec *req, struct timespec *rem);
void sleep_ms(long ms);
const char *get_direction(int x, int y);
const char *get_button(int button, int is_press);
