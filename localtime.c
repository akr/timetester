#include "timetester.h"

int main(int argc, char *argv[])
{
  time_t t;
  struct tm *tmp;
  int res;
  long long y;

  res = str2time(argv[1], &t);
  if (res == -1) { perror("str2time"); exit(1); }

  tmp = localtime(&t);
  if (tmp == NULL) { fprintf(stderr, "localtime error\n"); exit(1); }

  y = (long long)tmp->tm_year + 1900;
  printf("localtime: %"PRIdTIME" -> %lld-%02d-%02d %02d:%02d:%02d %s",
    t,
    y, tmp->tm_mon + 1, tmp->tm_mday,
    tmp->tm_hour, tmp->tm_min, tmp->tm_sec,
    tmp->tm_isdst > 0 ? "dst" : tmp->tm_isdst == 0 ? "std" : "unknown");

#ifdef HAVE_STRUCT_TM_TM_ZONE
  printf(" zone=%s", tmp->tm_zone);
#endif

#ifdef HAVE_STRUCT_TM_TM_GMTOFF
  printf(" gmtoff=%ld", tmp->tm_gmtoff);
#endif

  printf("\n");

  return 0;
}

