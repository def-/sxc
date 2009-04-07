SUBDIRS = Error Exit Time Exception Command CommandParser File Contact Account

noinst_LTLIBRARIES = libSrc.la
libSrc_la_CPPFLAGS = $(GLOOX_CFLAGS)
libSrc_la_LDFLAGS = -pthread
libSrc_la_SOURCES = \
    LogHandler.cxx \
    setupClient.cxx \
    KeepAlive.cxx \
    Subscriptions.cxx
noinst_HEADERS = \
    LogHandler.hxx \
    setupClient.hxx \
    KeepAlive.hxx \
    Subscriptions.hxx

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
    Command/libCommand.la \
    CommandParser/libCommandParser.la \
    libSrc.la
sxc_SOURCES = main.cxx
