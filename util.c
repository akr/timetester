#include "timetester.h"

int timenum_parse(const char *str, time_t *res)
{
#if SIZEOF_TIME_T <= SIZEOF_LONG
#   define CONVTYPE long
#   define CONVFUN_SIGNED(s,e,b) strtol(s,e,b)
#   define CONVFUN_UNSIGNED(s,e,b) strtoul(s,e,b)
#elif SIZEOF_TIME_T <= SIZEOF_LONG_LONG
#   define CONVTYPE long long
#   define CONVFUN_SIGNED(s,e,b) strtol(s,e,b)
#   define CONVFUN_UNSIGNED(s,e,b) strtoul(s,e,b)
#else
# error sizeof(time_t) unexpected.
#endif

#ifndef TIME_IS_SIGNED
  CONVTYPE v;
  errno = 0;
  v = CONVFUN_SIGNED(str, NULL, 0);
  if (errno)
    return -1;
  *res = v;
  return 0;
#else
  unsigned CONVTYPE v;
  errno = 0;
  v = CONVFUN_UNSIGNED(str, NULL, 0);
  if (errno)
    return -1;
  *res = v;
  return 0;
#endif
}

