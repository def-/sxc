SUBDIRS = File
INCLUDES = $(GLOOX_CFLAGS)
LIBS = $(GLOOX_LIBS)

noinst_LTLIBRARIES = libControl.la
libControl_la_SOURCES = Control.cpp Error.cpp Roster.cpp
libControl_la_LIBADD = File/libControlFile.la ../Contact/libContact.la
