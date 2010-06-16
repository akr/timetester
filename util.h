/* ret==-1 : failure, ret==0 : success */
int timenum_parse(const char *str, time_t *res);

/* ret==-1 : failure, ret<bufsize : success, bufsize<=ret : truncated */
int format_gmtoff(char *buf, size_t bufsize, long gmtoff, int negate_sign);

/* ret==-1 : failure, ret<bufsize : success, bufsize<=ret : truncated */
int format_wday(char *buf, size_t bufsize, int wday);

/* success:1, failure:0 */
int print_gmtoff(long gmtoff, int negate_sign);

/* success:1, failure:0 */
int print_wday(int wday);
