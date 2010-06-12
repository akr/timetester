/* ret==-1 : failure, ret==0 : success */
int timenum_parse(const char *str, time_t *res);

/* ret==-1 : failure, ret<bufsize : success, bufsize<=ret : truncated */
int format_gmtoff(char *buf, size_t bufsize, int gmtoff);

/* ret==-1 : failure, ret<bufsize : success, bufsize<=ret : truncated */
int format_wday(char *buf, size_t bufsize, int wday);
