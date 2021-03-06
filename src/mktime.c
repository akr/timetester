/* localtime.c - call mktime() function.

Copyright (C) 2010 Tanaka Akira.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

 1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above
    copyright notice, this list of conditions and the following
    disclaimer in the documentation and/or other materials provided
    with the distribution.
 3. The name of the author may not be used to endorse or promote
    products derived from this software without specific prior
    written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "timetester.h"

int main(int argc, char *argv[])
{
  time_t t;
  struct tm tmarg, tmp;
  signed_time_t y;
  char *str;

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

  (void)((WITH_TM_GMTOFF(1) || WITH_TIMEZONE_ALTZONE(0 <= tmp.tm_isdst)) && putchar(' '));
  (void)(WITH_TM_GMTOFF(print_gmtoff(tmp.tm_gmtoff, 0)) ||
      WITH_TIMEZONE_ALTZONE(0 <= tmp.tm_isdst && print_gmtoff(tmp.tm_isdst ? altzone : timezone, 1)));

  printf(" %s", CHOOSE_ISDST(tmp.tm_isdst, "std", "dst", "std/dst"));

  (void)(WITH_TM_ZONE(putf(" %s", tmp.tm_zone)) ||
      WITH_TZNAME(0 <= tmp.tm_isdst && putf(" %s", tzname[tmp.tm_isdst ? 1 : 0])));

  printf(" tm_yday=%d", tmp.tm_yday);

  (str = weekday_str(tmp.tm_wday)) ? printf(" (%s)", str) :
                                     printf(" tm_wday=%d", tmp.tm_wday);
  
  printf("\n");

  return 0;
}

