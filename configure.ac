#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([dhsp-wrapper], [0.3], [bird@dotty.su])
AC_CONFIG_SRCDIR([config.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_LN_S

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([limits.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strcasecmp strchr strdup strncasecmp strtol])
AC_DEFINE(__BSD_VISIBLE, 1, [Define on FreeBSD to activate all library features])
AM_INIT_AUTOMAKE([1.12 foreign no-define])

##########################################################################
# debug compilation support
##########################################################################


AC_MSG_CHECKING([whether to build with debug information])
AC_ARG_ENABLE([debug],
    [AS_HELP_STRING([--enable-debug],
        [enable debug data generation (def=no)])],
    [debugit="$enableval"],
    [debugit=no])
AC_MSG_RESULT([$debugit])

if test x"$debugit" = x"yes"; then
    AC_DEFINE([DEBUG],[],[Debug Mode])
    AM_CXXFLAGS="$AM_CXXFLAGS -g -Wall -Werror -Wno-uninitialized -O0"
else
    AC_DEFINE([NDEBUG],[],[No-debug Mode])
    AM_CXXFLAGS="$AM_CXXFLAGS -O3"
fi

nsupdate_full="/usr/bin/nsupdate -g"
AC_ARG_ENABLE(nsupdate,
  [  --enable-nsupdate="/usr/bin/nsupdate -g"],
  nsupdate_full=$enableval)

nsupdate_server="127.0.0.1"
AC_ARG_ENABLE(nsupdate_server,
  [  --enable-nsupdate_server="127.0.0.1"],
  nsupdate_server=$enableval)

nsupdate_end="send\n"
AC_ARG_ENABLE(nsupdate_end,
  [  --enable-nsupdate_end="send\n"],
  nsupdate_end=$enableval)

kini_cmd="/usr/bin/kinit"
AC_ARG_ENABLE(kini_cmd,
  [  --enable-kini_cmd="/usr/bin/kinit"],
  kini_cmd=$enableval)

AC_ARG_ENABLE(kini_pwd,
  [  --enable-kini_pwd="p@Ssw0rd"],
  kini_pwd=$enableval)

##########################################################################
# define
AC_DEFINE_UNQUOTED([NSUPDATE_FULL], "$nsupdate_full", [set nsupdate full path])
AC_DEFINE_UNQUOTED([NSUPDATE_SERVER], "$nsupdate_server", [set nsupdate server])
AC_DEFINE_UNQUOTED([NSUPDATE_END], "$nsupdate_end", [end for nsupdate)])
AC_DEFINE_UNQUOTED([KINIT_CMD], "$kini_cmd", [full kinit cmd])
AC_DEFINE_UNQUOTED([KINIT_PWD], "$kini_pwd", [password for kinit])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
