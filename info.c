#include "timetester.h"

int main(int argc, char *argv[])
{
  struct tm tm_var;

  printf("sizeof(time_t)=%d\n", (int)sizeof(time_t));
  printf("sizeof(struct tm.tm_year)=%d\n", (int)sizeof(tm_var.tm_year));
  printf("sizeof(int)=%d\n", (int)sizeof(int));
  printf("sizeof(long)=%d\n", (int)sizeof(long));
  return 0;
}
