#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libmonograph], [0.1], [don@donm.cc])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([1.14 foreign subdir-objects -Wall -Werror])

AC_CONFIG_SRCDIR([src/monograph/graph.c])
AC_CONFIG_HEADERS([src/monograph/config.h])
AC_DEFINE_UNQUOTED([TEST_DATA_DIR], ["$srcdir/test/data"], [Location of test data files.])

# Checks for programs.
AM_PROG_AR
AC_PROG_CC_C99
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDBOOL
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([strdup])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
