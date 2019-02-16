AUTOMAKE_OPTIONS = foreign dist-zip dist-bzip2
ACLOCAL_AMFLAGS = -I m4
AM_CFLAGS =
AM_CXXFLAGS =
AM_CPPFLAGS =

pkgconfig_DATA = $(PACKAGE_NAME)-$(API_VERSION).pc
SUBDIRS = src
dist_data_DATA = $(PACKAGE_NAME).pc.in src/StringStuff.h
nodist_data_DATA = $(PACKAGE_NAME)-$(API_VERSION).pc

distclean-local:
	rm -rf $(PACKAGE_NAME)-*.pc
