INCLUDES = $(DEPS_CFLAGS)
LIBS = $(DEPS_LIBS)

TESTS = tests
check_PROGRAMS = tests
#test_PROGRAMS = tests
#testdir = ../..

tests_SOURCES = main.cpp OptionTest.h
tests_LDFLAGS = -lcppunit -ldl

tests_LDADD = ../Contact/libContact.a ../Control/libControl.a ../Exception/libException.a ../Option/libOption.a
