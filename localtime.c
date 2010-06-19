#include "timetester.h"

int opt_v = 0;
int opt_r = 0;

void usage(FILE *f, int status)
{
  fprintf(f,
      "usage: localtime [options] seconds-from-epoch...\n"
      "options:\n"
      "  -h : print this message\n"
      "  -v : verbose mode\n"
      "  -r : use localtime_r() instead of localtime()\n"
      );
  exit(status);
}

int pf(const char *format, ...)
{
  va_list ap;
  int ret;
  va_start(ap, format);
  ret = vfprintf(stdout, format, ap);
  va_end(ap);
  return 0 <= ret;
}

int ps(const char *string)
{
  int ret;
  ret = fputs(string, stdout);
  return 0 <= ret;
}

int po(long gmtoff, int negate_sign)
{
  return fprint_gmtoff(stdout, gmtoff, negate_sign);
}

void do_localtime(time_t t)
{
  struct tm *tmp, result;
  signed_time_t y;
  char *str;

  errno = 0;
  if (opt_r)
    tmp = localtime_r(&t, &result);
  else
    tmp = localtime(&t);
  if (tmp == NULL) {
    pf("%"PRIdTIME" : localtime: %s\n", t, strerror(errno));
    return;
  }

  y = 1900 + (signed_time_t)tmp->tm_year;

  pf("%"PRIdTIME" -> %"PRIdSTIME"-%02d-%02d %02d:%02d:%02d",
    t,
    y, tmp->tm_mon + 1, tmp->tm_mday,
    tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

  if (opt_v) {
    WITH_TM_GMTOFF(putchar(' '));
    WITH_TM_GMTOFF(po(tmp->tm_gmtoff, 0));

    pf(" tm_isdst=%s(%d)",
      CHOOSE_ISDST(tmp->tm_isdst, "std", "dst", "unknown"),
      tmp->tm_isdst);

    WITH_TIMEZONE(ps(" timezone="));
    WITH_TIMEZONE(po(timezone, 1));
    WITH_TIMEZONE(pf("(%"PRIdTIME")", timezone));

    WITH_ALTZONE(ps(" altzone="));
    WITH_ALTZONE(po(altzone, 1));
    WITH_ALTZONE(pf("(%"PRIdTIME")", altzone));

    WITH_TM_ZONE(pf(" tm_zone=%s", tmp->tm_zone));

    WITH_TZNAME(pf(" tzname=[%s,%s]", tzname[0], tzname[1]));

    WITH_DAYLIGHT(pf(" daylight=%d", daylight));
  }
  else {
    if (!WITH_TM_GMTOFF(ps(" ")))
      WITH_TIMEZONE_ALTZONE(0 <= tmp->tm_isdst && ps(" "));
    if (!WITH_TM_GMTOFF(po(tmp->tm_gmtoff, 0)))
      WITH_TIMEZONE_ALTZONE(0 <= tmp->tm_isdst && po(tmp->tm_isdst ? altzone : timezone, 1));

    if (!WITH_TM_ZONE(pf(" %s", tmp->tm_zone)))
        WITH_TZNAME(0 <= tmp->tm_isdst && pf(" %s", tzname[tmp->tm_isdst ? 1 : 0]));
  }

  (str = weekday_str(tmp->tm_wday)) ? pf(" (%s)", str) :
                                      pf(" tm_wday=%d", tmp->tm_wday);

  ps("\n");
}

int main(int argc, char *argv[])
{
  int opt;
  getopt_t g;
  int i;

  getopt_init(&g, argc, argv, "hvr");
  while ((opt = getopt_next(&g)) != -1) {
    switch (opt) {
    case 'h':
      usage(stdout, EXIT_SUCCESS);

    case 'v':
      opt_v++;
      break;

    case 'r':
      opt_r++;
      break;

    case '?':
      exit(EXIT_FAILURE);
    }
  }

  for (i = g.optind; i < argc; i++) {
    const char *arg = argv[i];
    time_t t;
    int ret;

    ret = timenum_parse(arg, &t);
    if (ret == -1) {
      printf("%s : string-to-time_t: %s\n", arg, strerror(errno));
      continue;
    }
    do_localtime(t);
  }

  return 0;
}

