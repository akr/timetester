#include "timetester.h"

int main(int argc, char *argv[])
{
  time_t t;
  struct tm tmarg, tmp;
  long long y;
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

  y = 1900 + (long long)tmarg.tm_year;
  printf("%lld-%02d-%02d %02d:%02d:%02d",
    y, tmarg.tm_mon + 1, tmarg.tm_mday,
    tmarg.tm_hour, tmarg.tm_min, tmarg.tm_sec);

  printf(" %s",
    0 < tmarg.tm_isdst ? "dst" : tmarg.tm_isdst == 0 ? "std" : "std|dst");

  printf(" ->");

  printf(" %"PRIdTIME, t);

  y = 1900 + (long long)tmp.tm_year;
  printf(" %lld-%02d-%02d %02d:%02d:%02d",
    y, tmp.tm_mon + 1, tmp.tm_mday,
    tmp.tm_hour, tmp.tm_min, tmp.tm_sec);

#ifdef HAVE_STRUCT_TM_TM_GMTOFF
  {
    char gmtoff_buf[16];
    ret = format_gmtoff(gmtoff_buf, sizeof(gmtoff_buf), tmp.tm_gmtoff);
    if (0 < ret && ret < sizeof(gmtoff_buf))
      printf(" %s", gmtoff_buf);
    else
      printf(" gmtoff=%ld", tmp.tm_gmtoff);
  }
#endif

  printf(" %s",
    0 < tmp.tm_isdst ? "dst" : tmp.tm_isdst == 0 ? "std" : "std|dst");

#ifdef HAVE_STRUCT_TM_TM_ZONE
  printf(" (%s)", tmp.tm_zone);
#endif

  printf(" yday=%d",
    tmp.tm_yday);

  {
    char buf[16];
    ret = format_wday(buf, sizeof(buf), tmp.tm_wday);
    if (0 < ret && ret < sizeof(buf))
      printf(" %s", buf);
    else
      printf(" wday=%d", tmp.tm_wday);
  }

  printf("\n");

  return 0;
}

