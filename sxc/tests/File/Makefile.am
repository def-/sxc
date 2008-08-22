INCLUDES = $(GLOOX_CFLAGS) $(CPPUNIT_CFLAGS)
LIBS = $(GLOOX_LIBS) $(CPPUNIT_LIBS)

noinst_LTLIBRARIES = libFile.la
libFile_la_SOURCES = InputDummy.cxx TestInputDummy.cxx
libFile_la_LIBADD  = @top_srcdir@/src/Exception/libException.la @top_srcdir@/src/File/libFile.la

