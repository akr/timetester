/* timetester.h - timetester header file.

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

#include "config.h"

#if HAVE_DECL_TIMEZONE && !defined(HAVE_FUNC_TIMEZONE)
# define HAVE_VAR_TIMEZONE 1
#endif

#include <stdio.h>
#if HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif
#if HAVE_SYS_STAT_H
# include <sys/stat.h>
#endif
#if STDC_HEADERS
# include <stdlib.h>
# include <stddef.h>
#else
# if HAVE_STDLIB_H
#  include <stdlib.h>
# endif
#endif
#if HAVE_STRING_H
# if !STDC_HEADERS && HAVE_MEMORY_H
#  include <memory.h>
# endif
# include <string.h>
#endif
#if HAVE_STRINGS_H
# include <strings.h>
#endif
#if HAVE_INTTYPES_H
# include <inttypes.h>
#else
# if HAVE_STDINT_H
#  include <stdint.h>
# endif
#endif
#if HAVE_UNISTD_H
# include <unistd.h>
#endif
#if TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif
#if HAVE_ERRNO_H
# include <errno.h>
#endif
#if HAVE_LIMITS_H
# include <limits.h>
#endif
#if HAVE_SYS_LIMITS_H
# include <sys/limits.h>
#endif
#if HAVE_STDARG_H
# include <stdarg.h>
#endif
#include <ctype.h>

#ifdef HAVE_STRUCT_TM_TM_GMTOFF
# define WITH_TM_GMTOFF(x) (x)
#else
# define WITH_TM_GMTOFF(x) (zero())
#endif

#ifdef HAVE_STRUCT_TM_TM_ZONE
# define WITH_TM_ZONE(x) (x)
#else
# define WITH_TM_ZONE(x) (zero())
#endif

#if HAVE_DECL_DAYLIGHT
# define WITH_DAYLIGHT(x) (x)
#else
# define WITH_DAYLIGHT(x) (zero())
#endif

#if defined(HAVE_VAR_TIMEZONE) && HAVE_DECL_ALTZONE
# define WITH_TIMEZONE_ALTZONE(x) (x)
#else
# define WITH_TIMEZONE_ALTZONE(x) (zero())
#endif

#if defined(HAVE_VAR_TIMEZONE)
# define WITH_TIMEZONE(x) (x)
#else
# define WITH_TIMEZONE(x) (zero())
#endif

#if HAVE_DECL_ALTZONE
# define WITH_ALTZONE(x) (x)
#else
# define WITH_ALTZONE(x) (zero())
#endif

#if HAVE_DECL_TZNAME
# define WITH_TZNAME(x) (x)
#else
# define WITH_TZNAME(x) (zero())
#endif

#define CHOOSE_ISDST(isdst, std, dst, unknown) \
  ((isdst) == 0 ? (std) : (isdst) > 0 ? (dst) : (unknown))

#if SIZEOF_TIME_T == SIZEOF_INT && SIZEOF_INT == SIZEOF_LONG && defined(__FreeBSD__)
# define PREFER_INT_TIME_T
#endif

#if SIZEOF_TIME_T == SIZEOF_INT && defined(PREFER_INT_TIME_T)
  typedef int signed_time_t;
  typedef unsigned int unsigned_time_t;
# ifdef TIME_IS_SIGNED
#   define PRIdTIME "d"
# else
#   define PRIdTIME "u"
# endif
# define PRIdSTIME "d"
# define PRIdUTIME "u"
#elif SIZEOF_TIME_T == SIZEOF_LONG
  typedef long signed_time_t;
  typedef unsigned long unsigned_time_t;
# ifdef TIME_IS_SIGNED
#   define PRIdTIME "ld"
# else
#   define PRIdTIME "lu"
# endif
# define PRIdSTIME "ld"
# define PRIdUTIME "lu"
#elif SIZEOF_TIME_T == SIZEOF_LONG_LONG
  typedef long long signed_time_t;
  typedef unsigned long long unsigned_time_t;
# ifdef TIME_IS_SIGNED
#   define PRIdTIME "lld"
# else
#   define PRIdTIME "llu"
# endif
# define PRIdSTIME "lld"
# define PRIdUTIME "llu"
#else
# error cannot find integer type which size is same as time_t.
#endif

#ifdef TIME_IS_SIGNED
# define TIME_MAX ((time_t)((~(unsigned_time_t)0) >> 1))
# define TIME_MIN ((time_t)(((unsigned_time_t)1) << (sizeof(time_t) * CHAR_BIT - 1)))
#else
# define TIME_MAX ((time_t)(~(unsigned_time_t)0))
# define TIME_MIN ((time_t)0)
#endif

#include "util.h"
