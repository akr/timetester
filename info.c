#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
  printf("sizeof(time_t)=%d\n", (int)sizeof(time_t));
  printf("sizeof(int)=%d\n", (int)sizeof(int));
  printf("sizeof(long)=%d\n", (int)sizeof(long));
  return 0;
}
