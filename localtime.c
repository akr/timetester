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
    printf("%"PRIdTIME" : localtime: %s\n", t, strerror(errno));
    return;
  }

  y = 1900 + (signed_time_t)tmp->tm_year;

  printf("%"PRIdTIME" -> %"PRIdSTIME"-%02d-%02d %02d:%02d:%02d",
    t,
    y, tmp->tm_mon + 1, tmp->tm_mday,
    tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

  if (opt_v) {
    (void)WITH_TM_GMTOFF(putchar(' '));
    (void)WITH_TM_GMTOFF(print_gmtoff(tmp->tm_gmtoff, 0));

    printf(" tm_isdst=%s(%d)",
      CHOOSE_ISDST(tmp->tm_isdst, "std", "dst", "unknown"),
      tmp->tm_isdst);

    (void)WITH_DAYLIGHT(printf(" daylight=%d", daylight));

    (void)WITH_TIMEZONE(printf(" timezone="));
    (void)WITH_TIMEZONE(print_gmtoff(timezone, 1));
    (void)WITH_TIMEZONE(printf("(%"PRIdTIME")", timezone));

    (void)WITH_ALTZONE(printf(" altzone="));
    (void)WITH_ALTZONE(print_gmtoff(altzone, 1));
    (void)WITH_ALTZONE(printf("(%"PRIdTIME")", altzone));

    (void)WITH_TZNAME(printf(" tzname=[%s,%s]", tzname[0], tzname[1]));
  }
  else {
    (void)((WITH_TM_GMTOFF(1) || WITH_TIMEZONE_ALTZONE(0 <= tmp->tm_isdst)) && putchar(' '));
    (void)(WITH_TM_GMTOFF(print_gmtoff(tmp->tm_gmtoff, 0)) ||
        WITH_TIMEZONE_ALTZONE((0 <= tmp->tm_isdst) && print_gmtoff(tmp->tm_isdst ? altzone : timezone, 1)));

    if (WITH_TM_GMTOFF(putf(" ")))
      WITH_TIMEZONE_ALTZONE(0 <= tmp->tm_isdst && putf(" "));
    if (!WITH_TM_GMTOFF(print_gmtoff(tmp->tm_gmtoff, 0)))
      WITH_TIMEZONE_ALTZONE(0 <= tmp->tm_isdst && print_gmtoff(tmp->tm_isdst ? altzone : timezone, 1));

    (void)(WITH_TM_ZONE(putf(" %s", tmp->tm_zone)) ||
        WITH_TZNAME(0 <= tmp->tm_isdst && putf(" %s", tzname[tmp->tm_isdst ? 1 : 0])));
  }

  (str = weekday_str(tmp->tm_wday)) ? printf(" (%s)", str) :
                                      printf(" tm_wday=%d", tmp->tm_wday);

  printf("\n");
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

