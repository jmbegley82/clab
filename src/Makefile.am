include _Sources.mk

AUTOMAKE_OPTIONS = foreign

AM_CFLAGS =
AM_CXXFLAGS =
AM_CPPFLAGS =
lib@PACKAGE_NAME@_@API_VERSION@_la_LDFLAGS = -no-undefined -Wl,-rpath -Wl,LIBDIR -fPIC -version-number $(PACKAGE_VERSION_MAJOR):$(PACKAGE_VERSION_MINOR):$(PACKAGE_VERSION_MICRO)
if DEBUG
AM_CFLAGS   += -g
AM_CXXFLAGS += -g
AM_CPPFLAGS += -DDEBUG
else
AM_CPPFLAGS += -DPREFIX='"$(PREFIX)"'
endif

#otherincludedir = $(pkgincludedir)-@API_VERSION@

lib_LTLIBRARIES = lib@PACKAGE_NAME@-@API_VERSION@.la
lib@PACKAGE_NAME@_@API_VERSION@_la_dir = $(pkgdatadir)
#com_CFLAGS =
#AM_CFLAGS += $(com_CFLAGS)
#AM_CXXFLAGS += $(com_CFLAGS)
lib@PACKAGE_NAME@_@API_VERSION@_la_LIBADD =
lib@PACKAGE_NAME@_@API_VERSION@_la_SOURCES = $(CLAB_SOURCES)
otherinclude_HEADERS = Atom.h Node.h Notype.h String.h Integer.h Float.h

noinst_PROGRAMS = clabtest
clabtest_SOURCES = $(CLAB_TEST_SOURCES)
clabtest_LDFLAGS = -static
clabtest_LDADD = -lclab-0

install-data-hook:

uninstall-hook:
	rm -rf $(otherincludedir)

clean-local:
	-rm -rf *.gcda gmon.out

