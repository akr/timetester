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

