SUBDIRS = File
check_PROGRAMS = tests

TESTS = tests
tests_CPPFLAGS = $(CPPUNIT_CFLAGS) $(GLOOX_CFLAGS) $(LIBSXC_CFLAGS)
tests_CXXFLAGS = $(CPPUNIT_LIBS) $(GLOOX_LIBS) $(LIBSXC_LIBS)
tests_LDADD = @top_srcdir@/tests/File/libFile.la @top_srcdir@/src/libSrc.la
tests_SOURCES = main.cxx testRegistry.cxx
