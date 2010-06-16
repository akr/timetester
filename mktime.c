#include "timetester.h"

int main(int argc, char *argv[])
{
  time_t t;
  struct tm tmarg, tmp;
  signed_time_t y;
  int ret;

  if (argc <= 1) {
    fprintf(stderr, "usage: mktime year [mon [day [hour [min [sec [isdst]]]]]]\n");
    exit(1);
  }

  tmarg.tm_year = atoi(argv[1]) - 1900;
  tmarg.tm_mon = 2 < argc ? atoi(argv[2]) - 1 : 0;
  tmarg.tm_mday = 3 < argc ? atoi(argv[3]) : 1;
  tmarg.tm_hour = 4 < argc ? atoi(argv[4]) : 0;
  tmarg.tm_min = 5 < argc ? atoi(argv[5]) : 0;
  tmarg.tm_sec = 6 < argc ? atoi(argv[6]) : 0;
  tmarg.tm_isdst = 7 < argc ? atoi(argv[7]) : -1;

  tmp = tmarg;

  t = mktime(&tmp);
  if (t == (time_t)-1) { fprintf(stderr, "mktime returns -1 (error)\n"); exit(1); }

  y = 1900 + (signed_time_t)tmarg.tm_year;
  printf("%"PRIdSTIME"-%02d-%02d %02d:%02d:%02d",
    y, tmarg.tm_mon + 1, tmarg.tm_mday,
    tmarg.tm_hour, tmarg.tm_min, tmarg.tm_sec);

  printf(" %s", CHOOSE_ISDST(tmarg.tm_isdst, "std", "dst", "std/dst"));

  printf(" ->");

  printf(" %"PRIdTIME, t);

  y = 1900 + (signed_time_t)tmp.tm_year;
  printf(" %"PRIdSTIME"-%02d-%02d %02d:%02d:%02d",
    y, tmp.tm_mon + 1, tmp.tm_mday,
    tmp.tm_hour, tmp.tm_min, tmp.tm_sec);

  (WITH_TM_GMTOFF(1) || WITH_TIMEZONE_ALTZONE(0 <= tmp->tm_isdst)) && putchar(' ');
  WITH_TM_GMTOFF(print_gmtoff(tmp.tm_gmtoff, 0)) ||
    WITH_TIMEZONE_ALTZONE(0 <= tmp.tm_isdst && print_gmtoff(tmp.tm_isdst ? altzone : timezone, 1));

  printf(" %s", CHOOSE_ISDST(tmp.tm_isdst, "std", "dst", "std/dst"));

  WITH_TM_ZONE(0 <= printf(" %s", tmp.tm_zone)) ||
    WITH_TZNAME(0 <= tmp.tm_isdst && 0 <= printf(" %s", tzname[tmp.tm_isdst ? 1 : 0]));

  printf(" tm_yday=%d", tmp.tm_yday);

  printf(" (");
  print_wday(tmp.tm_wday);
  printf(")");

  printf("\n");

  return 0;
}

