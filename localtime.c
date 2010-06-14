#include "timetester.h"

int opt_v = 0;

void usage(FILE *f, int status)
{
  fprintf(f,
      "usage: localtime [options] seconds-from-epoch...\n"
      );
  exit(status);
}

int print_gmtoff(long gmtoff)
{
  char buf[16];
  format_gmtoff(buf, sizeof(buf), gmtoff, 0);
  fputs(buf, stdout);
  return 0;
}

#define CHOOSE_ISDST(isdst, std, dst, unknown) ((isdst) == 0 ? (std) : (isdst) > 0 ? (dst) : (unknown))

int print_wday(int wday)
{
  char buf[16];
  int ret;
  ret = format_wday(buf, sizeof(buf), wday);
  if (0 < ret && ret < sizeof(buf))
    printf("%s", buf);
  else
    printf("wday=%d", wday);
  return 0;
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
    putchar(' ');
    print_gmtoff(tmp->tm_gmtoff);
#endif

    printf(" tm_isdst=%s(%d)",
      CHOOSE_ISDST(tmp->tm_isdst, "std", "dst", "unknown"),
      tmp->tm_isdst);

#if HAVE_DECL_DAYLIGHT
    printf(" daylight=%d", daylight);
#endif

#ifdef HAVE_VAR_TIMEZONE
    printf(" timezone=");
    print_gmtoff(-timezone);
    printf("(%"PRIdTIME")", timezone);
#endif

#if HAVE_DECL_ALTZONE
    printf(" altzone=");
    print_gmtoff(-altzone);
    printf("(%"PRIdTIME")", altzone);
#endif

#if HAVE_DECL_TZNAME
    printf(" tzname=[%s,%s]", tzname[0], tzname[1]);
#endif

  }
  else {
#ifdef HAVE_STRUCT_TM_TM_GMTOFF
    putchar(' ');
    print_gmtoff(tmp->tm_gmtoff);
#elif defined(HAVE_VAR_TIMEZONE) && defined(HAVE_DECL_ALTZONE)
    if (0 <= tmp->tm_isdst) {
      putchar(' ');
      print_gmtoff(tmp->tm_isdst ? -altzone : -timezone);
    }
#endif

#ifdef HAVE_STRUCT_TM_TM_ZONE
    printf(" %s", tmp->tm_zone);
#elif HAVE_DECL_TZNAME
    if (0 <= tmp->tm_isdst)
      printf(" %s", tzname[tmp->tm_isdst ? 1 : 0]);
#endif
  }

  putchar(' ');
  print_wday(tmp->tm_wday);

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

