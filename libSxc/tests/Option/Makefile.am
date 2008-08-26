INCLUDES = -I$(top_srcdir)/include $(GLOOX_CFLAGS) $(CPPUNIT_CFLAGS)
LIBS = $(GLOOX_LIBS) $(CPPUNIT_LIBS)

noinst_LTLIBRARIES = libOption.la
libOption_la_SOURCES = OptionTest.cxx OptionTest.hxx
libOption_la_LIBADD = $(top_srcdir)/src/Option/libOption.la $(top_srcdir)/src/Exception/libException.la
