/* stat.c - call stat() function.

Copyright (C) 2013 Tanaka Akira.  All rights reserved.

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

void test_stat(char *filename)
{
  int ret;
  struct stat statbuf;

  ret = stat(filename, &statbuf);
  if (ret == -1) { perror("stat"); exit(EXIT_FAILURE); }

#ifdef HAVE_STRUCT_STAT_ST_ATIM
  printf("atime = %"PRIdTIME".%09d\n",
      statbuf.st_atim.tv_sec, statbuf.st_atim.tv_nsec);
#else
  printf("atime = %"PRIdTIME"\n", statbuf.st_atime);
#endif

#ifdef HAVE_STRUCT_STAT_ST_MTIM
  printf("mtime = %"PRIdTIME".%09d\n",
      statbuf.st_mtim.tv_sec, statbuf.st_mtim.tv_nsec);
#else
  printf("mtime = %"PRIdTIME"\n", statbuf.st_mtime);
#endif

#ifdef HAVE_STRUCT_STAT_ST_CTIM
  printf("ctime = %"PRIdTIME".%09d\n",
      statbuf.st_ctim.tv_sec, statbuf.st_ctim.tv_nsec);
#else
  printf("ctime = %"PRIdTIME"\n", statbuf.st_ctime);
#endif
}

int main(int argc, char *argv[])
{
  int i;

  for (i = 1; i < argc; i++) {
    test_stat(argv[i]);
  }
}
