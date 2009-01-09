SUBDIRS = Exception

noinst_LTLIBRARIES = libFile.la
libFile_la_CPPFLAGS = $(GLOOX_CFLAGS)
libFile_la_LDFLAGS = -pthread
libFile_la_LIBADD = Exception/libFileException.la
libFile_la_SOURCES = AbcInfo.cxx AbcInput.cxx AbcOutput.cxx createDir.cxx remove.cxx
