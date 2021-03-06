/* localtime.c - utility functions.

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

int timenum_parse(const char *str, time_t *res)
{
#if SIZEOF_TIME_T <= SIZEOF_LONG
#   ifdef TIME_IS_SIGNED
#       define CONVTYPE long
#       define CONVFUN(s,e,b) strtol(s,e,b)
#   else
#       define CONVTYPE unsigned long
#       define CONVFUN(s,e,b) strtoul(s,e,b)
#   endif
#elif SIZEOF_TIME_T <= SIZEOF_LONG_LONG
#   ifdef TIME_IS_SIGNED
#       define CONVTYPE long long
#       define CONVFUN(s,e,b) strtoll(s,e,b)
#   else
#       define CONVTYPE unsigned long long
#       define CONVFUN(s,e,b) strtoull(s,e,b)
#   endif
#else
#   error sizeof(time_t) unexpected.
#endif

  CONVTYPE v;
  char *e;
  errno = 0;
  v = CONVFUN(str, &e, 0);
  if (errno)
    return -1;
  if ((time_t)v != v) {
    errno = ERANGE;
    return -1;
  }
  if (*e != '\0') {
    errno = EINVAL;
    return -1;
  }

  *res = v;
  return 0;

#undef CONVTYPE
#undef CONVFUN
}

int format_gmtoff(char *buf, size_t bufsize, long gmtoff, int negate_sign)
{
  int sign, m, s;
  unsigned long t, h;
  int ret;
  if (gmtoff == 0) {
    sign = 0;
    t = 0;
  }
  else if (gmtoff < 0) {
    sign = -1;
    t = -gmtoff;
  }
  else {
    sign = 1;
    t = gmtoff;
  }
  if (negate_sign)
    sign = -sign;
  s = t % 60;
  t = t / 60;
  m = t % 60;
  h = t / 60;
  if (s == 0)
    ret = snprintf(buf, bufsize, "%c%02lu:%02d", sign < 0 ? '-' : '+', h, m);
  else
    ret = snprintf(buf, bufsize, "%c%02lu:%02d:%02d", sign < 0 ? '-' : '+', h, m, s);
  return ret;
}

char *weekday_str(int wday)
{
  switch (wday) {
    case 0: return "Sun";
    case 1: return "Mon";
    case 2: return "Tue";
    case 3: return "Wed";
    case 4: return "Thu";
    case 5: return "Fri";
    case 6: return "Sat";
    default: return NULL;
  }
}

int format_wday(char *buf, size_t bufsize, int wday)
{
  char *s = weekday_str(wday);
  int ret;
  if (s)
    ret = snprintf(buf, bufsize, "%s", s);
  else
    ret = snprintf(buf, bufsize, "wday=%d", wday);
  return ret;
}

int putf(const char *format, ...)
{
  va_list ap;
  int ret;
  va_start(ap, format);
  ret = vprintf(format, ap);
  va_end(ap);
  return 0 <= ret;
}

int fprint_gmtoff(FILE *f, long gmtoff, int negate_sign)
{
  char buf[16];
  format_gmtoff(buf, sizeof(buf), gmtoff, negate_sign);
  fputs(buf, f);
  return 0;
}

int print_gmtoff(long gmtoff, int negate_sign)
{
  return fprint_gmtoff(stdout, gmtoff, negate_sign);
}

int fprint_wday(FILE *f, int wday)
{
  char buf[16];
  int ret;
  ret = format_wday(buf, sizeof(buf), wday);
  if (0 < ret && ret < (int)sizeof(buf))
    fprintf(f, "%s", buf);
  else
    fprintf(f, "wday=%d", wday);
  return 0;
}

int print_wday(int wday)
{
  return fprint_wday(stdout, wday);
}

int zero()
{
  return 0;
}

int one()
{
  return 1;
}

void getopt_init(getopt_t *g, int argc, char * const argv[], const char *optstring)
{
  g->argc = argc;
  g->argv = argv;
  g->optstring = optstring;

  g->optarg = NULL;
  g->optind = 1;
  g->opterr = 1;
  g->optopt = 0;
  g->optsubind = 0;
}

int getopt_next(getopt_t *g)
{
  int opt;
  const char *p;

  if (g->optsubind == 0) {
    if (g->argv[g->optind] == NULL)
      return -1;

    if (g->argv[g->optind][0] != '-')
      return -1;

    if (g->argv[g->optind][1] == '\0')
      return -1;

    if (isdigit(g->argv[g->optind][1]))
      return -1;

    if (g->argv[g->optind][1] == '-' && g->argv[g->optind][2] == '\0') {
      g->optind++;
      return -1;
    }

    g->optsubind = 1;
  }

  opt = (unsigned char)g->argv[g->optind][g->optsubind];

  if (!isalpha(opt)) {
    if (g->opterr)
      fprintf(stderr, "%s: invalid option -- %c\n", g->argv[0], opt);
    return '?';
  }

  p = strchr(g->optstring, opt);
  if (!p) {
    if (g->opterr)
      fprintf(stderr, "%s: invalid option -- %c\n", g->argv[0], opt);
    return '?';
  }

  if (p[1] == ':') {
    if (g->argv[g->optind][g->optsubind+1] != '\0') {
      g->optarg = &g->argv[g->optind][g->optsubind+1];
      g->optind++;
      g->optsubind = 0;
      return opt;
    }
    else {
      if (!g->argv[g->optind+1]) {
        g->optopt = opt;
        if (*g->optstring == ':')
          return ':';
        else {
          if (g->opterr)
            fprintf(stderr, "%s: option requires an argument -- %c\n", g->argv[0], opt);
          return '?';
        }
      }
      g->optarg = g->argv[g->optind+1];
      g->optind += 2;
      g->optsubind = 0;
      return opt;
    }
  }
  else {
    if (g->argv[g->optind][g->optsubind+1] == '\0') {
      g->optind++;
      g->optsubind = 0;
    }
    else {
      g->optsubind++;
    }
    return opt;
  }
}
