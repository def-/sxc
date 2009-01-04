SUBDIRS = Error Time Exception CommandParser File Contact Account

noinst_LTLIBRARIES = libSrc.la
libSrc_la_CPPFLAGS = $(GLOOX_CFLAGS)
libSrc_la_SOURCES = \
    LogHandler.cxx \
    setupClient.cxx

bin_PROGRAMS = sxc
sxc_CPPFLAGS = $(GLOOX_CFLAGS) $(LIBSXC_CFLAGS)
sxc_LDFLAGS = -pthread
sxc_CXXFLAGS = $(GLOOX_LIBS) $(LIBSXC_LIBS)
sxc_LDADD = \
    Time/libTime.la \
    Contact/libContact.la \
    Account/libAccount.la \
    Error/libError.la \
    Exception/libException.la \
    CommandParser/libCommandParser.la \
    libSrc.la
sxc_SOURCES = main.cxx
