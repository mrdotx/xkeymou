/*
 * path:   /home/klassiker/.local/share/repos/xkeymou/util.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/xkeymou
 * date:   2022-07-05T09:32:01+0200
 */

/* macros */
#define LENGTH(X)   (sizeof X / sizeof X[0])

int nanosleep(const struct timespec *req, struct timespec *rem);
void sleep_ms(long ms);
