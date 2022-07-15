/*
 * path:   /home/klassiker/.local/share/repos/xkeymou/util.h
 * author: klassiker [mrdotx]
 * github: https://github.com/mrdotx/xkeymou
 * date:   2022-07-15T14:02:17+0200
 */

/* macros */
#define LENGTH(X)   (sizeof X / sizeof X[0])

int nanosleep(const struct timespec *req, struct timespec *rem);
void sleep_ms(long ms);
const char *get_direction(int x, int y);
const char *get_button(int button);
