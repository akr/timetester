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
  if ((time_t)v != v) {
    errno = ERANGE;
    return -1;
  }
  *res = v;
  return 0;

#undef CONVTYPE
#undef CONVFUN
}

int format_gmtoff(char *buf, size_t bufsize, long gmtoff, int negate_sign)
{
  int sign, m, s;
  unsigned long t, h;
  int ret;
  if (gmtoff == 0) {
    sign = 0;
    t = 0;
  }
  else if (gmtoff < 0) {
    sign = -1;
    t = -gmtoff;
  }
  else {
    sign = 1;
    t = gmtoff;
  }
  if (negate_sign)
    sign = -sign;
  s = t % 60;
  t = t / 60;
  m = t % 60;
  h = t / 60;
  if (s == 0)
    ret = snprintf(buf, bufsize, "%c%02lu:%02d", sign < 0 ? '-' : '+', h, m);
  else
    ret = snprintf(buf, bufsize, "%c%02lu:%02d:%02d", sign < 0 ? '-' : '+', h, m, s);
  return ret;
}

static char *weekday(int wday)
{
  switch (wday) {
    case 0: return "Sun";
    case 1: return "Mon";
    case 2: return "Tue";
    case 3: return "Wed";
    case 4: return "Thu";
    case 5: return "Fri";
    case 6: return "Sat";
    default: return NULL;
  }
}

int format_wday(char *buf, size_t bufsize, int wday)
{
  char *s = weekday(wday);
  int ret;
  if (s)
    ret = snprintf(buf, bufsize, "%s", s);
  else
    ret = snprintf(buf, bufsize, "wday=%d", wday);
  return ret;
}

int print_gmtoff(long gmtoff, int negate_sign)
{
  char buf[16];
  format_gmtoff(buf, sizeof(buf), gmtoff, negate_sign);
  fputs(buf, stdout);
  return 0;
}

int print_wday(int wday)
{
  char buf[16];
  int ret;
  ret = format_wday(buf, sizeof(buf), wday);
  if (0 < ret && ret < sizeof(buf))
    printf("%s", buf);
  else
    printf("wday=%d", wday);
  return 0;
}

char *myoptarg;
int myoptind = 1;
int myopterr = 1;
int myoptopt;
static int myoptsubind = 0;

int mygetopt(int argc, char * const argv[], const char *optstring)
{
  int opt;
  const char *p;

  if (myoptsubind == 0) {
    if (argv[myoptind] == NULL)
      return -1;

    if (argv[myoptind][0] != '-')
      return -1;

    if (argv[myoptind][1] == '\0')
      return -1;

    if (argv[myoptind][1] == '-' && argv[myoptind][2] == '\0') {
      myoptind++;
      return -1;
    }

    myoptsubind = 1;
  }

  opt = (unsigned char)argv[myoptind][myoptsubind];

  if (!isalpha(opt)) {
    if (myopterr)
      fprintf(stderr, "%s: invalid option -- %c\n", argv[0], opt);
    return '?';
  }

  p = strchr(optstring, opt);
  if (!p) {
    if (myopterr)
      fprintf(stderr, "%s: invalid option -- %c\n", argv[0], opt);
    return '?';
  }

  if (p[1] == ':') {
    if (argv[myoptind][myoptsubind+1] != '\0') {
      myoptarg = &argv[myoptind][myoptsubind+1];
      myoptind++;
      myoptsubind = 0;
      return opt;
    }
    else {
      if (!argv[myoptind+1]) {
        myoptopt = opt;
        if (*optstring == ':')
          return ':';
        else {
          if (myopterr)
            fprintf(stderr, "%s: option requires an argument -- %c\n", argv[0], opt);
          return '?';
        }
      }
      myoptarg = argv[myoptind+1];
      myoptind += 2;
      myoptsubind = 0;
      return opt;
    }
  }
  else {
    if (argv[myoptind][myoptsubind+1] == '\0') {
      myoptind++;
      myoptsubind = 0;
    }
    else {
      myoptsubind++;
    }
    return opt;
  }
}
