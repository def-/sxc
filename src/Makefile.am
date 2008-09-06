SUBDIRS = Time Exception CommandParser File Contact Control

noinst_LTLIBRARIES = libSrc.la
libSrc_la_CPPFLAGS = $(GLOOX_CFLAGS) $(SIGC_CFLAGS)
libSrc_la_SOURCES =\
    print.cxx\
    generateString.cxx\
    SignalHandler.cxx\
    LogHandler.cxx

bin_PROGRAMS = sxc
sxc_CPPFLAGS = $(GLOOX_CFLAGS) $(LIBSXC_CFLAGS) $(SIGC_CFLAGS)
sxc_CXXFLAGS = $(GLOOX_LIBS) $(LIBSXC_LIBS) $(SIGC_LIBS)
sxc_LDADD =\
    Time/libTime.la\
    Contact/libContact.la\
    Control/libControl.la\
    Exception/libException.la\
    CommandParser/libCommandParser.la\
    libSrc.la
sxc_SOURCES = main.cxx
