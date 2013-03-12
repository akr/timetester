/* info.c - show environment information.

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

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "timetester.h"

#define SIGNED_INTEGER_P(type) (~(type)0 <= 0 ? 1 : 0)
#define SIGNED_STR_OF_TYPE(type) (SIGNED_INTEGER_P(type) ? "signed" : "unsigned")

void info_static(void)
{
  printf("time_t\t\t: %s %dbit\n", SIGNED_STR_OF_TYPE(time_t), CHAR_BIT * (int)sizeof(time_t));
  printf("char\t\t: %s %dbit\n", SIGNED_STR_OF_TYPE(char), CHAR_BIT * (int)sizeof(char));
  printf("int\t\t: %dbit\n", CHAR_BIT * (int)sizeof(int));
  printf("long\t\t: %dbit\n", CHAR_BIT * (int)sizeof(long));
#ifdef HAVE_LONG_LONG
  printf("long long\t: %dbit\n", CHAR_BIT * (int)sizeof(long long));
#endif

  printf("\n");

  {
    struct tm v;
    memset((void*)&v, 0xff, sizeof(v));
    printf("struct tm\n");
    printf("  tm_year\t: %s %dbit\n", v.tm_year <= 0 ? "signed" : "unsigned", CHAR_BIT * (int)sizeof(v.tm_year));
    printf("  tm_mon\t: %s %dbit\n", v.tm_mon <= 0 ? "signed" : "unsigned", CHAR_BIT * (int)sizeof(v.tm_mon));
    printf("  tm_mday\t: %s %dbit\n", v.tm_mday <= 0 ? "signed" : "unsigned", CHAR_BIT * (int)sizeof(v.tm_mday));
    printf("  tm_hour\t: %s %dbit\n", v.tm_hour <= 0 ? "signed" : "unsigned", CHAR_BIT * (int)sizeof(v.tm_hour));
    printf("  tm_min\t: %s %dbit\n", v.tm_min <= 0 ? "signed" : "unsigned", CHAR_BIT * (int)sizeof(v.tm_min));
    printf("  tm_sec\t: %s %dbit\n", v.tm_sec <= 0 ? "signed" : "unsigned", CHAR_BIT * (int)sizeof(v.tm_sec));
    printf("  tm_wday\t: %s %dbit\n", v.tm_wday <= 0 ? "signed" : "unsigned", CHAR_BIT * (int)sizeof(v.tm_wday));
    printf("  tm_yday\t: %s %dbit\n", v.tm_yday <= 0 ? "signed" : "unsigned", CHAR_BIT * (int)sizeof(v.tm_yday));
    printf("  tm_isdst\t: %s %dbit\n", v.tm_isdst <= 0 ? "signed" : "unsigned", CHAR_BIT * (int)sizeof(v.tm_isdst));
#ifdef HAVE_STRUCT_TM_TM_GMTOFF
    printf("  tm_gmtoff\t: %s %dbit\n", v.tm_gmtoff <= 0 ? "signed" : "unsigned", CHAR_BIT * (int)sizeof(v.tm_gmtoff));
#endif
#ifdef HAVE_STRUCT_TM_TM_ZONE
    printf("  tm_zone\t: %dbit\n", CHAR_BIT * (int)sizeof(v.tm_zone));
#endif
  }

  printf("\n");
}


void info_dynamic(void)
{
#if HAVE_DECL_DAYLIGHT
  printf("daylight\t: %d\n", daylight);
#endif

#if HAVE_DECL_TIMEZONE && !defined(HAVE_FUNC_TIMEZONE)
  /* timezone variable is not exist if timezone function exists.
     timezone function is available on Version 7 AT&T UNIX and FreeBSD 8.0. */
  {
    int ret;
    char buf[16];
    ret = format_gmtoff(buf, sizeof(buf), -timezone, 0);
    if (0 < ret && ret < (int)sizeof(buf))
      printf("timezone\t: %s (%d)\n", buf, (int)timezone);
    else
      printf("timezone\t: %d\n", (int)timezone);
  }
#endif

#if HAVE_DECL_ALTZONE
  {
    int ret;
    char buf[16];
    ret = format_gmtoff(buf, sizeof(buf), -altzone, 0);
    if (0 < ret && ret < sizeof(buf))
      printf("altzone\t\t: %s (%d)\n", buf, (int)altzone);
    else
      printf("altzone\t\t: %d\n", (int)altzone);
  }
#endif

#if HAVE_DECL_TZNAME
  printf("tzname\t\t: [%s,%s]\n", tzname[0], tzname[1]);
#endif
}

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;

  info_static();

  tzset();
  info_dynamic();

  return 0;
}
