#include "timetester.h"

int opt_v = 0;

void usage(FILE *f, int status)
{
  fprintf(f,
      "usage: localtime [options] seconds-from-epoch...\n"
      "options:\n"
      "  -h : print this message\n"
      "  -v : verbose mode\n"
      );
  exit(status);
}

int print_gmtoff(long gmtoff, int negate_sign)
{
  char buf[16];
  format_gmtoff(buf, sizeof(buf), gmtoff, negate_sign);
  fputs(buf, stdout);
  return 0;
}

#define CHOOSE_ISDST(isdst, std, dst, unknown) ((isdst) == 0 ? (std) : (isdst) > 0 ? (dst) : (unknown))

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

void do_localtime(time_t t)
{
  struct tm *tmp;
  long long y;
  int ret;

  tmp = localtime(&t);
  if (tmp == NULL) { fprintf(stderr, "localtime error\n"); exit(1); }

  y = (long long)tmp->tm_year + 1900;

  printf("%"PRIdTIME" -> %lld-%02d-%02d %02d:%02d:%02d",
    t,
    y, tmp->tm_mon + 1, tmp->tm_mday,
    tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

  if (opt_v) {
    WITH_TM_GMTOFF(putchar(' '));
    WITH_TM_GMTOFF(print_gmtoff(tmp->tm_gmtoff, 0));

    printf(" tm_isdst=%s(%d)",
      CHOOSE_ISDST(tmp->tm_isdst, "std", "dst", "unknown"),
      tmp->tm_isdst);

    WITH_DAYLIGHT(printf(" daylight=%d", daylight));

    WITH_TIMEZONE(printf(" timezone="));
    WITH_TIMEZONE(print_gmtoff(timezone, 1));
    WITH_TIMEZONE(printf("(%"PRIdTIME")", timezone));

    WITH_ALTZONE(printf(" altzone="));
    WITH_ALTZONE(print_gmtoff(altzone, 1));
    WITH_ALTZONE(printf("(%"PRIdTIME")", altzone));

    WITH_TZNAME(printf(" tzname=[%s,%s]", tzname[0], tzname[1]));
  }
  else {
    (WITH_TM_GMTOFF(1) || WITH_TIMEZONE_ALTZONE(0 <= tmp->tm_isdst)) && putchar(' ');
    WITH_TM_GMTOFF(print_gmtoff(tmp->tm_gmtoff, 0)) ||
      WITH_TIMEZONE_ALTZONE((0 <= tmp->tm_isdst) && print_gmtoff(tmp->tm_isdst ? altzone : timezone, 1));

    WITH_TM_ZONE(0 <= printf(" %s", tmp->tm_zone)) ||
      WITH_TZNAME(0 <= tmp->tm_isdst && 0 <= printf(" %s", tzname[tmp->tm_isdst ? 1 : 0]));
  }

  putchar(' ');
  print_wday(tmp->tm_wday);

  printf("\n");
}

int main(int argc, char *argv[])
{
  int opt;

  while ((opt = getopt(argc, argv, "hv")) != -1) {
    switch (opt) {
    case 'h':
      usage(stdout, EXIT_SUCCESS);

    case 'v':
      opt_v++;
      break;

    case '?':
      exit(EXIT_FAILURE);
    }
  }

  for (; optind < argc; optind++) {
    const char *arg = argv[optind];
    time_t t;
    int ret;

    ret = timenum_parse(arg, &t);
    if (ret == -1) {
      printf("%s : %s\n", arg, strerror(errno));
      continue;
    }
    do_localtime(t);
  }

  return 0;
}

