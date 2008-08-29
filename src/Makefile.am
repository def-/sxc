SUBDIRS = Exception CommandParser File Contact Control

noinst_LTLIBRARIES = libSrc.la
libSrc_la_CPPFLAGS = $(GLOOX_CFLAGS)
libSrc_la_SOURCES = print.cxx generateErrorText.cxx

bin_PROGRAMS = sxc
sxc_CPPFLAGS = $(GLOOX_CFLAGS) $(LIBSXC_CFLAGS)
sxc_CXXFLAGS = $(GLOOX_LIBS) $(LIBSXC_LIBS)
sxc_LDADD =\
    Contact/libContact.la\
    Control/libControl.la\
    Exception/libException.la\
    CommandParser/libCommandParser.la\
    libSrc.la
sxc_SOURCES = main.cxx
