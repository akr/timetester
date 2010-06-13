#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
AC_INIT([timetest], [0.1])

AC_CONFIG_SRCDIR([README])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_USE_SYSTEM_EXTENSIONS

# Checks for libraries.

# Checks for header files.

AC_HEADER_TIME
AC_CHECK_HEADERS([sys/time.h errno.h limits.h sys/limits.h])

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
#if HAVE_ERRNO_H
# include <errno.h>
#endif
#if HAVE_LIMITS_H
# include <limits.h>
#endif
#if HAVE_SYS_LIMITS_H
# include <sys/limits.h>
#endif
"

# Checks for typedefs, structures, and compiler characteristics.
AC_STRUCT_TIMEZONE
AC_CHECK_MEMBERS([struct tm.tm_gmtoff],,,[$incs])

AC_CHECK_TYPES(long long)
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(long long)
AC_CHECK_SIZEOF(time_t)

AC_MSG_CHECKING([for time_t is signed])
AC_RUN_IFELSE(AC_LANG_PROGRAM(
  [$incs],
  [exit((~(time_t)0 <= 0) ? EXIT_SUCCESS : EXIT_FAILURE);]),
  [AC_MSG_RESULT(yes); AC_DEFINE(TIME_IS_SIGNED, [Define to 1 if time_t is signed type.])],
  [AC_MSG_RESULT(no)])

# Checks for library functions.
AC_CHECK_FUNCS([mktime strtoll])

AC_CHECK_DECLS([tzname, timezone, daylight, altzone],,,[$incs])

AC_MSG_CHECKING([for timezone(zone,dst) function])
AC_COMPILE_IFELSE(AC_LANG_PROGRAM(
    [$incs],
    [timezone(0,0);]),
  [AC_MSG_RESULT(yes); AC_DEFINE(HAVE_FUNC_TIMEZONE, [], [Define to 1 if the function timezone() is available.])],
  [AC_MSG_RESULT(no)])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
