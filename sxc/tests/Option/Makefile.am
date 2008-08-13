INCLUDES = $(GLOOX_CFLAGS) $(CPPUNIT_CFLAGS)
LIBS = $(GLOOX_LIBS) $(CPPUNIT_LIBS)

noinst_LTLIBRARIES = libOption.la
libOption_la_SOURCES = OptionTest.cpp OptionTest.h
libOption_la_LIBADD = @top_srcdir@/src/Contact/libContact.la @top_srcdir@/src/Control/libControl.la @top_srcdir@/src/Exception/libException.la @top_srcdir@/src/Option/libOption.la
