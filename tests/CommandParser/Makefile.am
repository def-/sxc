noinst_LTLIBRARIES = libCommandParser.la
libCommandParser_la_CPPFLAGS = $(CPPUNIT_CFLAGS) $(GLOOX_CFLAGS)
libCommandParser_la_CXXFLAGS = $(CPPUNIT_LIBS) $(GLOOX_LIBS)
libCommandParser_la_LIBADD  = @top_srcdir@/src/Exception/libException.la @top_srcdir@/src/CommandParser/libCommandParser.la
libCommandParser_la_SOURCES = CommandParserDummy.cxx TestCommandParser.cxx TestNoCommandParser.cxx TestInvalidCommandParser.cxx
noinst_HEADERS = CommandParserDummy.hxx TestCommandParser.hxx TestNoCommandParser.hxx TestInvalidCommandParser.hxx
