if have_cppunit
SUBDIRS = Command CommandParser File Time
check_PROGRAMS = tests
TESTS = tests
tests_CPPFLAGS = $(CPPUNIT_CFLAGS) $(GLOOX_CFLAGS) $(LIBSXC_CFLAGS)
tests_CXXFLAGS = $(CPPUNIT_LIBS) $(GLOOX_LIBS) $(LIBSXC_LIBS)
tests_LDADD =\
    @top_srcdir@/tests/Command/libCommand.la\
    @top_srcdir@/tests/CommandParser/libCommandParser.la\
    @top_srcdir@/tests/File/libFile.la\
    @top_srcdir@/tests/Time/libTime.la\
    @top_srcdir@/src/libSrc.la
tests_SOURCES = main.cxx testRegistry.cxx
else
check:
	@echo "-------------------------------------------------"
	@echo " Cannot run tests."
	@echo " Check \"config.log\" for more information."
	@echo "-------------------------------------------------"
	@exit 1
endif
