#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

#if SIZEOF_TIME_T == SIZEOF_LONG
typedef unsigned long unsigned_time_t;
#elif SIZEOF_TIME_T == SIZEOF_INT
typedef unsigned int unsigned_time_t;
#elif SIZEOF_TIME_T == SIZEOF_LONG_LONG
typedef unsigned long long unsigned_time_t;
#else
# error cannot find integer type which size is same as time_t.
#endif

#define SIGNED_TIME_P (~(time_t)0 <= 0)

#define TIME_MAX (SIGNED_TIME_P ? (time_t)((~(unsigned_time_t)0) >> 1) : (time_t)(~(unsigned_time_t)0))
#define TIME_MIN (SIGNED_TIME_P ? (time_t)(((unsigned_time_t)1) << (sizeof(time_t) * CHAR_BIT - 1)) : (time_t)0)

#include "util.h"
