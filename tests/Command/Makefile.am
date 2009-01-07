SUBDIRS = Mock
noinst_LTLIBRARIES = libCommand.la
libCommand_la_CPPFLAGS = $(CPPUNIT_CFLAGS) $(GLOOX_CFLAGS) $(LIBSXC_CFLAGS)
libCommand_la_CXXFLAGS = $(CPPUNIT_LIBS) $(GLOOX_LIBS) $(LIBSXC_LIBS)
# FIXME!
# libCommand_la_SOURCES = TestCommand.cxx FailCommand.cxx
libCommand_la_SOURCES = TestCommand.cxx 
libCommand_la_LIBADD  = @top_srcdir@/src/Command/libCommand.la Mock/libMock.la
