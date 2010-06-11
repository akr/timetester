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
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_STRUCT_TIMEZONE
AC_CHECK_MEMBERS([struct tm.tm_gmtoff],,,[#include <time.h>])

AC_CHECK_TYPES(long long)
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(long long)
AC_CHECK_SIZEOF(time_t)

# Checks for library functions.
AC_CHECK_FUNCS([mktime strtoll])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
