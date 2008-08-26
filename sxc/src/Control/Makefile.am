SUBDIRS = File
AM_CPPFLAGS = $(GLOOX_CFLAGS)
LIBS = $(GLOOX_LIBS)

noinst_LTLIBRARIES = libControl.la
libControl_la_SOURCES = Control.cxx Roster.cxx
libControl_la_LIBADD = File/libControlFile.la ../Contact/libContact.la
