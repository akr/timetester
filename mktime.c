#include "timetester.h"

char *weekday(int wday)
{
  switch (wday) {
    case 0: return "Sun";
    case 1: return "Mon";
    case 2: return "Tue";
    case 3: return "Wed";
    case 4: return "Thu";
    case 5: return "Fri";
    case 6: return "Sat";
    default: return "unexpected-weekday-number";
  }
}

int main(int argc, char *argv[])
{
  time_t t;
  struct tm tmarg, tmp;

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
  if (t == (time_t)-1) { fprintf(stderr, "mktime error (-1 is returned)\n"); exit(1); }

  printf("mktime: %d-%02d-%02d %02d:%02d:%02d (isdst=%d) -> %d-%02d-%02d %02d:%02d:%02d %s (isdst=%d yday=%d) %ld\n",
    tmarg.tm_year + 1900, tmarg.tm_mon + 1, tmarg.tm_mday,
    tmarg.tm_hour, tmarg.tm_min, tmarg.tm_sec,
    tmarg.tm_isdst,
    tmp.tm_year + 1900, tmp.tm_mon + 1, tmp.tm_mday,
    tmp.tm_hour, tmp.tm_min, tmp.tm_sec,
    weekday(tmp.tm_wday),
    tmp.tm_isdst, tmp.tm_yday,
    t);

  return 0;
}

