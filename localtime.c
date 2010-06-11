#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
  time_t t;
  struct tm *tmp;

  t = atol(argv[1]);

  tmp = localtime(&t);
  if (tmp == NULL) { fprintf(stderr, "localtime error\n"); exit(1); }

  printf("localtime: %ld -> %d-%02d-%02d %02d:%02d:%02d %s %s (%ld) %ld\n",
    t,
    tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday,
    tmp->tm_hour, tmp->tm_min, tmp->tm_sec,
    tmp->tm_isdst > 0 ? "dst" : tmp->tm_isdst == 0 ? "std" : "unknown",
    tmp->tm_zone, tmp->tm_gmtoff);

  return 0;
}

