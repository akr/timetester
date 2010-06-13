#include "timetester.h"

int opt_v = 0;

void usage(FILE *f, int status)
{
  fprintf(f,
      "usage: localtime [options] seconds-from-epoch...\n"
      );
  exit(status);
}

void do_localtime(time_t t)
{
  struct tm *tmp;
  long long y;
  int ret;

  tmp = localtime(&t);
  if (tmp == NULL) { fprintf(stderr, "localtime error\n"); exit(1); }

  y = (long long)tmp->tm_year + 1900;

  printf("%"PRIdTIME" -> %lld-%02d-%02d %02d:%02d:%02d",
    t,
    y, tmp->tm_mon + 1, tmp->tm_mday,
    tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

  if (opt_v) {
#ifdef HAVE_STRUCT_TM_TM_GMTOFF
    {
      char buf[16];
      ret = format_gmtoff(buf, sizeof(buf), tmp->tm_gmtoff);
      if (0 < ret && ret < sizeof(buf))
        printf(" %s", buf);
      else
        printf(" tm_gmtoff=%ld", tmp->tm_gmtoff);
    }
#endif

    printf(" tm_isdst=%s(%d)",
      tmp->tm_isdst > 0 ? "dst" : tmp->tm_isdst == 0 ? "std" : "unknown",
      tmp->tm_isdst);

#if HAVE_DECL_DAYLIGHT
    printf(" daylight=%d", daylight);
#endif

#if HAVE_DECL_TIMEZONE && !defined(HAVE_FUNC_TIMEZONE)
     
    {
      char buf[16];
      ret = format_gmtoff(buf, sizeof(buf), (int)-timezone);
      if (0 < ret && ret < sizeof(buf))
        printf(" timezone=%s(%"PRIdTIME")", buf, timezone);
      else
        printf(" timezone=%"PRIdTIME, timezone);
    }
#endif

#if HAVE_DECL_ALTZONE
    {
      char buf[16];
      ret = format_gmtoff(buf, sizeof(buf), (int)-altzone);
      if (0 < ret && ret < sizeof(buf))
        printf(" altzone=%s(%"PRIdTIME")", buf, altzone);
      else
        printf(" altzone=%"PRIdTIME, altzone);
    }
#endif

#if HAVE_DECL_TZNAME
    printf(" tzname=\"%s\",\"%s\"", tzname[0], tzname[1]);
#endif

  }
  else {
#ifdef HAVE_STRUCT_TM_TM_GMTOFF
    {
      char buf[16];
      ret = format_gmtoff(buf, sizeof(buf), tmp->tm_gmtoff);
      if (0 < ret && ret < sizeof(buf))
        printf(" %s", buf);
      else
        printf(" gmtoff=%ld", tmp->tm_gmtoff);
    }
#elif defined(HAVE_DECL_TIMEZONE) && defined(HAVE_DECL_ALTZONE)
    {
      char buf[16];
      time_t gmtoff = tmp->tm_isdst ? altzone : timezone;
      gmtoff = -gmtoff;
      ret = format_gmtoff(buf, sizeof(buf), (int)gmtoff);
      if (0 < ret && ret < sizeof(buf))
        printf(" %s", buf);
      else
        printf(" gmtoff=%"PRIdTIME, gmtoff);
    }
#endif

#ifdef HAVE_STRUCT_TM_TM_ZONE
    printf(" %s", tmp->tm_zone);
#elif HAVE_DECL_TZNAME
    if (tmp->tm_isdst)
      printf(" %s", tzname[1]);
    else
      printf(" %s", tzname[0]);
#endif
  }

  printf(" yday=%d", tmp->tm_yday);

  {
    char buf[16];
    ret = format_wday(buf, sizeof(buf), tmp->tm_wday);
    if (0 < ret && ret < sizeof(buf))
      printf(" %s", buf);
    else
      printf(" wday=%d", tmp->tm_wday);
  }

  printf("\n");
}

int main(int argc, char *argv[])
{
  int opt;

  while ((opt = getopt(argc, argv, "hv")) != -1) {
    switch (opt) {
    case 'h':
      usage(stdout, EXIT_SUCCESS);

    case 'v':
      opt_v++;
      break;

    case '?':
      exit(EXIT_FAILURE);
    }
  }

  for (; optind < argc; optind++) {
    const char *arg = argv[optind];
    time_t t;
    int ret;

    ret = timenum_parse(arg, &t);
    if (ret == -1) {
      printf("%s : %s\n", arg, strerror(errno));
      continue;
    }
    do_localtime(t);
  }

  return 0;
}

