SUBDIRS = File Exception

noinst_LTLIBRARIES = libAccount.la
libAccount_la_CPPFLAGS = $(GLOOX_CFLAGS) $(LIBSXC_CFLAGS)
libAccount_la_LDFLAGS = -pthread
libAccount_la_LIBADD = \
  File/libAccountFile.la \
  Exception/libAccountException.la \
  ../Contact/libContact.la
libAccount_la_SOURCES = Account.cxx Roster.cxx Command.cxx
noinst_HEADERS = Account.ixx Account.hxx Roster.hxx RosterType.hxx Command.hxx
