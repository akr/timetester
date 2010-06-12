#include "timetester.h"

#define SIGNED_INTEGER_P(type) (~(type)0 <= 0 ? 1 : 0)
#define SIGNED_STR_OF_TYPE(type) (SIGNED_INTEGER_P(type) ? "signed" : "unsigned")

int main(int argc, char *argv[])
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

  tzset();

#if HAVE_DECL_DAYLIGHT
  printf("daylight\t: %d\n", daylight);
#endif

#if HAVE_DECL_TIMEZONE
  printf("timezone\t: %d\n", (int)timezone);
#endif

#if HAVE_DECL_ALTZONE
  printf("altzone\t\t: %d\n", (int)altzone);
#endif

#if HAVE_DECL_TZNAME
  printf("tzname\t\t: \"%s\", \"%s\"\n", tzname[0], tzname[1]);
#endif

  return 0;
}
