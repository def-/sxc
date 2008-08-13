INCLUDES = $(GLOOX_CFLAGS) $(CPPUNIT_CFLAGS)
LIBS = $(GLOOX_LIBS) $(CPPUNIT_LIBS)

TESTS = tests
check_PROGRAMS = tests

tests_SOURCES = main.cpp OptionTest.cpp OptionTest.h testRegistry.cpp
tests_LDADD = @top_srcdir@/src/Contact/libContact.la @top_srcdir@/src/Control/libControl.la @top_srcdir@/src/Exception/libException.la @top_srcdir@/src/Option/libOption.la
