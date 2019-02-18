include _Sources.mk

AUTOMAKE_OPTIONS = foreign

AM_CXXFLAGS =
AM_CPPFLAGS =
lib@PACKAGE_NAME@_@API_VERSION@_la_LDFLAGS = -no-undefined -Wl,-rpath -Wl,LIBDIR -fPIC -version-number $(PACKAGE_VERSION_MAJOR):$(PACKAGE_VERSION_MINOR):$(PACKAGE_VERSION_MICRO)
if DEBUG
AM_CXXFLAGS += -g3 -D_GLIBCXX_DEBUG
AM_CPPFLAGS += -DDEBUG
else
AM_CXXFLAGS += -O3 -s
AM_CPPFLAGS += -DPREFIX='"$(PREFIX)"'
endif

#otherincludedir = $(pkgincludedir)-@API_VERSION@

lib_LTLIBRARIES = lib@PACKAGE_NAME@-@API_VERSION@.la
lib@PACKAGE_NAME@_@API_VERSION@_la_dir = $(pkgdatadir)
lib@PACKAGE_NAME@_@API_VERSION@_la_LIBADD =
lib@PACKAGE_NAME@_@API_VERSION@_la_SOURCES = $(CLAB_SOURCES)
otherinclude_HEADERS = Atom.h Node.h Notype.h String.h Integer.h Float.h TestMachine.h

noinst_PROGRAMS = @PACKAGE_NAME@test
@PACKAGE_NAME@test_SOURCES = $(CLAB_TEST_SOURCES)
@PACKAGE_NAME@test_LDFLAGS = -static
@PACKAGE_NAME@test_LDADD = -l@PACKAGE_NAME@-0

install-data-hook:

uninstall-hook:
	rm -rf $(otherincludedir)

clean-local:
	-rm -rf *.gcda gmon.out

