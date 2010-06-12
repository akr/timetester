#include "config.h"

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

#if SIZEOF_TIME_T == SIZEOF_INT
  typedef unsigned int unsigned_time_t;
# define PRIdTIME "d"
#elif SIZEOF_TIME_T == SIZEOF_LONG
  typedef unsigned long unsigned_time_t;
# define PRIdTIME "ld"
#elif SIZEOF_TIME_T == SIZEOF_LONG_LONG
  typedef unsigned long long unsigned_time_t;
# define PRIdTIME "lld"
#else
# error cannot find integer type which size is same as time_t.
#endif

#define SIGNED_TIME_P (~(time_t)0 <= 0)

#define TIME_MAX (SIGNED_TIME_P ? (time_t)((~(unsigned_time_t)0) >> 1) : (time_t)(~(unsigned_time_t)0))
#define TIME_MIN (SIGNED_TIME_P ? (time_t)(((unsigned_time_t)1) << (sizeof(time_t) * CHAR_BIT - 1)) : (time_t)0)

#include "util.h"
