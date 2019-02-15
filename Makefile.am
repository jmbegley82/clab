AUTOMAKE_OPTIONS = foreign dist-zip dist-bzip2
ACLOCAL_AMFLAGS = -I m4
AM_CFLAGS =
AM_CXXFLAGS =
AM_CPPFLAGS =

pkgconfig_DATA = clab-$(API_VERSION).pc
SUBDIRS = src

distclean-local:
	rm -rf clab-*.pc
