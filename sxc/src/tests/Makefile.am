INCLUDES = $(DEPS_CFLAGS)
LIBS = $(DEPS_LIBS)

TESTS = tests
check_PROGRAMS = tests

#tests_SOURCES = OptionMain.cpp OptionTest.h ../Exception/Exception.cpp ../Exception/OptionException.cpp ../Option/OptionBase.cpp ../Option/Option.cpp ../Option/OptionPort.cpp ../Option/Parser.cpp
tests_SOURCES = OptionMain.cpp OptionTest.h
#tests_CXXFLAGS = $(CPPUNIT_CFLAGS)
tests_LDFLAGS = -lcppunit -ldl

LDADD = ../Contact/libContact.a ../Control/libControl.a ../Exception/libException.a ../Option/libOption.a
