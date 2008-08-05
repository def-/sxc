AC_INIT([sxc], [0.0-prealpha], [TODO@mail])
AM_INIT_AUTOMAKE
AC_DEFINE_UNQUOTED(COPYRIGHT, ["2008 Andreas Waidler, Dennis Felsing"], [Copyright information.])

AM_CONFIG_HEADER(src/config.h)

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Checks for language.
AC_LANG([C++])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([pthread.h], [have_pthreads=yes], [have_pthreads=no])

# Checks for libraries.
AC_SEARCH_LIBS([pthread_create], [pthread], [], [have_pthreads=no])
if test "x${have_pthreads}" = xno; then
    echo \
"-------------------------------------------------
 Unable to find Pthreads. Stopping.
 Check \"config.log\" for more information.
-------------------------------------------------"
    (exit 1); exit 1
fi

PKG_CHECK_MODULES([GLOOX], [gloox >= 0.9], [have_gloox=yes], [have_gloox=no])
AC_SUBST(GLOOX_CFLAGS)
AC_SUBST(GLOOX_LIBS)
if test "x${have_gloox}" = xno; then
    echo \
"-------------------------------------------------
 Unable to find gloox >= 0.9. Stopping
 Check \"config.log\" for more information.
-------------------------------------------------"
    (exit 1); exit 1
fi

PKG_CHECK_MODULES([CPPUNIT], [cppunit >= 1.12.0], [have_cppunit=yes], [have_cppunit=no])
AC_SUBST(CPPUNIT_CFLAGS)
AC_SUBST(CPPUNIT_LIBS)
if test "x${have_cppunit}" = xno; then
    echo \
"-------------------------------------------------
 Unable to find CppUnit >= 1.12.0.
 \"make check\" will not work.
-------------------------------------------------"
fi

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/Contact/Makefile
    src/Control/Makefile
    src/Control/File/Makefile
    src/Exception/Makefile
    src/File/Makefile
    src/Option/Makefile
    src/tests/Makefile
])

AC_OUTPUT

echo \
"-------------------------------------------------

 ${PACKAGE_NAME} ${PACKAGE_VERSION}

 Prefix: '${prefix}'.
 Compiler: '${CC} ${CFLAGS} ${CPPFLAGS}'

 Package features:

 Now type 'make @<:@<target>@:>@'
 where the optional <target> is:
     all                - build all binaries
     check              - run unittests
     install            - install everything
     uninstall          - uninstall everything

-------------------------------------------------"
