SUBDIRS = File

noinst_LTLIBRARIES = libAccount.la
libAccount_la_CPPFLAGS = $(GLOOX_CFLAGS) $(LIBSXC_CFLAGS)
libAccount_la_LDFLAGS = -pthread
libAccount_la_SOURCES = Account.cxx Roster.cxx Command.cxx
libAccount_la_LIBADD = File/libAccountFile.la ../Contact/libContact.la
