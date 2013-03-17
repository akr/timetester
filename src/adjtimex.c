/* adjtimex.c - call adjtimex() function.

Copyright (C) 2010-2013 Tanaka Akira.  All rights reserved.

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

int main(int argc, char *argv[])
{
#ifdef HAVE_ADJTIMEX
  struct timex tx;
  int ret;

  tx.modes = 0;

  ret = adjtimex(&tx);
  if (ret == -1) { perror("adjtimex"); exit(1); }

  printf("return = %d\n", ret);
  printf("offset = %ld (usec)\n", tx.offset);
  printf("freq = %ld (scaled ppm)\n", tx.freq);
  printf("maxerror = %ld (usec)\n", tx.maxerror);
  printf("esterror = %ld (usec)\n", tx.esterror);
  printf("status = %d\n", tx.status);
  printf("constant = %ld\n", tx.constant);
  printf("precision = %ld (usec)\n", tx.precision);
  printf("tolerance = %ld (ppm)\n", tx.tolerance);
  printf("time = %"PRIdTIME".%06ld\n", tx.time.tv_sec, (long)tx.time.tv_usec);
  printf("tick = %ld\n", tx.tick);

  return 0;
#else
  fprintf(stderr, "adjtimex() not available.\n");
  return EXIT_FAILURE;
#endif
}
