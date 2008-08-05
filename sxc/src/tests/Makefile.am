INCLUDES = $(GLOOX_CFLAGS) $(CPPUNIT_CFLAGS)
LIBS = $(GLOOX_LIBS) $(CPPUNIT_LIBS)

TESTS = tests
check_PROGRAMS = tests

tests_SOURCES = main.cpp OptionTest.cpp
tests_LDADD = ../Contact/libContact.la ../Control/libControl.la ../Exception/libException.la ../Option/libOption.la
