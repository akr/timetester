#include "timetester.h"

int timenum_parse(const char *str, time_t *res)
{
#if SIZEOF_TIME_T <= SIZEOF_LONG
#   ifdef TIME_IS_SIGNED
#       define CONVTYPE long
#       define CONVFUN(s,e,b) strtol(s,e,b)
#   else
#       define CONVTYPE unsigned long
#       define CONVFUN(s,e,b) strtoul(s,e,b)
#   endif
#elif SIZEOF_TIME_T <= SIZEOF_LONG_LONG
#   ifdef TIME_IS_SIGNED
#       define CONVTYPE long long
#       define CONVFUN(s,e,b) strtoll(s,e,b)
#   else
#       define CONVTYPE unsigned long long
#       define CONVFUN(s,e,b) strtoull(s,e,b)
#   endif
#else
#   error sizeof(time_t) unexpected.
#endif

  CONVTYPE v;
  errno = 0;
  v = CONVFUN(str, NULL, 0);
  if (errno)
    return -1;
  *res = v;
  return 0;

#undef CONVTYPE
#undef CONVFUN
}

int format_gmtoff(char *buf, size_t bufsize, int gmtoff)
{
  int sign, t, h, m, s;
  int ret;
  t = gmtoff;
  sign = 1;
  if (gmtoff < 0) {
    sign = -1;
    t = -t;
  }
  s = t % 60;
  t = t / 60;
  m = t % 60;
  h = t / 60;
  if (s == 0)
    ret = snprintf(buf, bufsize, "%c%02d:%02d", sign < 0 ? '-' : '+', h, m);
  else
    ret = snprintf(buf, bufsize, "%c%02d:%02d:%02d", sign < 0 ? '-' : '+', h, m, s);
  return ret;
}

