#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])

m4_define([package_version_major],[0])
m4_define([package_version_minor],[0])
m4_define([package_version_micro],[1])

AC_INIT([clab], [package_version_major.package_version_minor.package_version_micro], [jmbegley@gmx.com])
#AC_CANONICAL_HOST
#AC_CONFIG_SRCDIR([src/config.h.in])

AC_CONFIG_MACRO_DIR([m4])
AH_TOP([
#ifndef CONFIG_H
#define CONFIG_H
])
AH_BOTTOM([
#endif //CONFIG_H
])
AM_INIT_AUTOMAKE([dist-bzip2])

#sane defaults:
#: ${CFLAGS=""}
: ${CXXFLAGS=""}

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_EXEEXT
AC_OBJEXT
AM_SILENT_RULES
PKG_PROG_PKG_CONFIG
PKG_INSTALLDIR

AC_ENABLE_STATIC
AC_ENABLE_SHARED
LT_INIT

#AC_SUBST(CFLAGS)
AC_SUBST(CXXFLAGS)

# Checks for header files.
#AC_CHECK_HEADERS([string.h])

# Checks for typedefs, structures, and compiler characteristics.
#AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_STRTOD
AC_CHECK_FUNCS([atexit memset])

# SDL and friends
AM_PATH_SDL2([2.0], , AC_MSG_ERROR([Please install libsdl2 >= 2.0]))
PKG_CHECK_MODULES(SDL_image, SDL2_image)
AC_SUBST(SDL_image_CFLAGS)
AC_SUBST(SDL_image_LIBS)
PKG_CHECK_MODULES(SDL_ttf, SDL2_ttf)
AC_SUBST(SDL_ttf_CFLAGS)
AC_SUBST(SDL_ttf_LIBS)
PKG_CHECK_MODULES(SDL_mixer, SDL2_mixer)
AC_SUBST(SDL_mixer_CFLAGS)
AC_SUBST(SDL_mixer_LIBS)


#User options:
if test "x$prefix" = "xNONE" ; then
	prefix="/usr/local"
fi
if test "x$exec_prefix" = "xNONE" ; then
	exec_prefix=$prefix
fi
PREFIX=$prefix
AC_SUBST(PREFIX)
AC_SUBST([otherincludedir],['${pkgincludedir}-${PACKAGE_VERSION_MAJOR}'])

AC_SUBST([PACKAGE_VERSION_MAJOR],package_version_major)
AC_SUBST([PACKAGE_VERSION_MINOR],package_version_minor)
AC_SUBST([PACKAGE_VERSION_MICRO],package_version_micro)
AC_SUBST([API_VERSION],package_version_major)

AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
               [enable debugging, default: no]),
[case "${enableval}" in
             yes) debug=true ;;
             no)  debug=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[debug=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")

AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([$PACKAGE_NAME-$API_VERSION.pc:$PACKAGE_NAME.pc.in
		 Makefile
                 src/Makefile], [], [API_VERSION='$API_VERSION'])
AC_OUTPUT
