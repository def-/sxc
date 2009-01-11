SUBDIRS = Exception

noinst_LTLIBRARIES = libCommandParser.la
libCommandParser_la_CPPFLAGS = $(GLOOX_CFLAGS) $(LIBSXC_CFLAGS)
libCommandParser_la_LIBADD = \
  ../Exception/libException.la \
  Exception/libCommandParserException.la
libCommandParser_la_SOURCES = AbcCommandParser.cxx
noinst_HEADERS = AbcCommandParser.hxx
