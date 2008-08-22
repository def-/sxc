SUBDIRS = Option File
INCLUDES = $(CPPUNIT_CFLAGS)
LIBS = $(CPPUNIT_LIBS)

TESTS = tests
check_PROGRAMS = tests

tests_SOURCES = main.cxx testRegistry.cxx
tests_LDADD = @top_srcdir@/tests/Option/libOption.la File/libFile.la
