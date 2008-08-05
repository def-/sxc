SUBDIRS = Exception File Contact Control Option tests
INCLUDES = $(GLOOX_CFLAGS)
LIBS = $(GLOOX_LIBS)

bin_PROGRAMS = sxc
sxc_SOURCES = main.cpp generateErrorText.cpp
sxc_LDADD = Contact/libContact.la Control/libControl.la Exception/libException.la Option/libOption.la
