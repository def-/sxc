SUBDIRS = File
AM_CPPFLAGS = $(CPPUNIT_CFLAGS)
LIBS = $(CPPUNIT_LIBS)

TESTS = tests
check_PROGRAMS = tests

tests_SOURCES = main.cxx testRegistry.cxx
tests_LDADD = @top_srcdir@/tests/File/libFile.la @top_srcdir@/src/libSrc.la
