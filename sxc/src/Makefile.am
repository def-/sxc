SUBDIRS = Exception File Contact Control Option
AM_CPPFLAGS = $(GLOOX_CFLAGS)
LIBS = $(GLOOX_LIBS)

noinst_LTLIBRARIES = libSrc.la
libSrc_la_SOURCES = print.cxx generateErrorText.cxx

bin_PROGRAMS = sxc
sxc_SOURCES = main.cxx
sxc_LDADD = Contact/libContact.la Control/libControl.la Exception/libException.la Option/libOption.la libSrc.la
