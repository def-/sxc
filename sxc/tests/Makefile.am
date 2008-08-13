SUBDIRS = Option
INCLUDES = $(CPPUNIT_CFLAGS)
LIBS = $(CPPUNIT_LIBS)

TESTS = tests
check_PROGRAMS = tests

tests_SOURCES = main.cpp testRegistry.cpp
tests_LDADD = @top_srcdir@/tests/Option/libOption.la
