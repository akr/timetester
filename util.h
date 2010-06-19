/* util.h - header for utility functions.

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

/* ret==-1 : failure, ret==0 : success */
int timenum_parse(const char *str, time_t *res);

/* ret==-1 : failure, ret<bufsize : success, bufsize<=ret : truncated */
int format_gmtoff(char *buf, size_t bufsize, long gmtoff, int negate_sign);

/* success:non-NULL failure:NULL */
char *weekday_str(int wday);

/* ret==-1 : failure, ret<bufsize : success, bufsize<=ret : truncated */
int format_wday(char *buf, size_t bufsize, int wday);

/* success:1, failure:0 */
int putf(const char *format, ...);

/* success:1, failure:0 */
int print_gmtoff(long gmtoff, int negate_sign);
int fprint_gmtoff(FILE *f, long gmtoff, int negate_sign);

/* success:1, failure:0 */
int print_wday(int wday);
int fprint_wday(FILE *f, int wday);

int zero();
int one();

typedef struct
{
  int argc;
  char * const *argv;
  const char *optstring;

  char *optarg;
  int optind;
  int opterr;
  int optopt;
  int optsubind;
} getopt_t;

void getopt_init(getopt_t *, int argc, char * const argv[], const char *optstring);
int getopt_next(getopt_t *);

