INCLUDES = $(DEPS_CFLAGS)
LIBS = $(DEPS_LIBS)

SUBDIRS = Contact Control Exception File Option tests
sxc_LDADD = Contact/libContact.a Control/libControl.a Exception/libException.a Option/libOption.a

bin_PROGRAMS = sxc
sxc_SOURCES = main.cpp generateErrorText.cpp
