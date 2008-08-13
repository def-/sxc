SUBDIRS = File
INCLUDES = $(GLOOX_CFLAGS)
LIBS = $(GLOOX_LIBS)

noinst_LTLIBRARIES = libControl.la
libControl_la_SOURCES = Control.cxx Error.cxx Roster.cxx
libControl_la_LIBADD = File/libControlFile.la ../Contact/libContact.la
