noinst_LTLIBRARIES = libMock.la
libMock_la_CPPFLAGS = $(CPPUNIT_CFLAGS) $(GLOOX_CFLAGS) $(LIBSXC_CFLAGS)
libMock_la_CXXFLAGS = $(CPPUNIT_LIBS) $(GLOOX_LIBS) $(LIBSXC_LIBS)
libMock_la_SOURCES = NoOp.cxx OneParamSwitch.cxx
libMock_la_LIBADD  = @top_srcdir@/src/Command/libCommand.la
