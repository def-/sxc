SUBDIRS = File

noinst_LTLIBRARIES = libControl.la
libControl_la_CPPFLAGS = $(GLOOX_CFLAGS) $(LIBSXC_CFLAGS)
libControl_la_LDFLAGS = -pthread
libControl_la_SOURCES = Control.cxx Roster.cxx Command.cxx
libControl_la_LIBADD = File/libControlFile.la ../Contact/libContact.la
