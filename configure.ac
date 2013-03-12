# configure.ac - the source of configure.
#
# Copyright (C) 2010 Tanaka Akira.  All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  1. Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above
#     copyright notice, this list of conditions and the following
#     disclaimer in the documentation and/or other materials provided
#     with the distribution.
#  3. The name of the author may not be used to endorse or promote
#     products derived from this software without specific prior
#     written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
# GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

AC_PREREQ([2.61])
AC_INIT([timetester], [0.1])

AC_CONFIG_SRCDIR([README])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_USE_SYSTEM_EXTENSIONS

# Checks for libraries.

# Checks for header files.

AC_HEADER_TIME
AC_CHECK_HEADERS([sys/time.h sys/timex.h \
                  errno.h limits.h sys/limits.h stdarg.h])

incs="AC_INCLUDES_DEFAULT
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
#if HAVE_SYS_TIMEX_H
# include <sys/timex.h>
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
#if HAVE_STDARG
# include <stdarg.h>
#endif
#include <ctype.h>
"

# Checks for typedefs, structures, and compiler characteristics.
AC_STRUCT_TIMEZONE
AC_CHECK_MEMBERS([struct tm.tm_gmtoff],,,[$incs])

AC_CHECK_TYPES(long long)
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(long long)
AC_CHECK_SIZEOF(time_t)

AC_CHECK_MEMBERS([struct stat.st_atim],,,[$incs])
AC_CHECK_MEMBERS([struct stat.st_mtim],,,[$incs])
AC_CHECK_MEMBERS([struct stat.st_ctim],,,[$incs])

AC_DEFUN([TIMETEST_CHECK_SIGNED_TIME_T],
[AC_CACHE_CHECK([for time_t is signed], [timetest_cv_signed_time_t],
  AC_RUN_IFELSE([AC_LANG_PROGRAM(
    [$incs],
    [exit((~(time_t)0 <= 0) ? EXIT_SUCCESS : EXIT_FAILURE);])],
    [timetest_cv_signed_time_t=yes],
    [timetest_cv_signed_time_t=no]))
if test "x$timetest_cv_signed_time_t" = xyes; then
  AC_DEFINE([TIME_IS_SIGNED], [1],
            [Define to 1 if time_t is signed type.])
fi])
TIMETEST_CHECK_SIGNED_TIME_T

# Checks for library functions.
AC_CHECK_FUNCS([mktime strtoll])

AC_CHECK_DECLS([tzname, timezone, daylight, altzone],,,[$incs])

AC_DEFUN([TIMETEST_CHECK_TIMEZONE_FUNCTION],
[AC_CACHE_CHECK([for timezone(zone,dst) function], [timetest_cv_timezone_function],
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM(
      [$incs],
      [timezone(0,0);])],
    [timetest_cv_timezone_function=yes],
    [timetest_cv_timezone_function=no]))
if test "x$timetest_cv_timezone_function" = xyes; then
  AC_DEFINE(HAVE_FUNC_TIMEZONE, [1],
            [Define to 1 if the function timezone() is available.])
fi])
TIMETEST_CHECK_TIMEZONE_FUNCTION

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
