AC_INIT([sxc], [0.0-prealpha], [sxc team])
AM_INIT_AUTOMAKE
AC_DEFINE_UNQUOTED(
    COPYRIGHT,
    ["2008 Andreas Waidler, Dennis Felsing"],
    [Copyright information.])

AC_CONFIG_SRCDIR([src/main.cpp])
AM_CONFIG_HEADER([src/config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

AC_CHECK_PROG([have_doxygen], [doxygen], [yes], [no])
if test "x${have_doxygen}" = xno; then
    echo \
"-------------------------------------------------
 Unable to find Doxygen.
 \"make doxygen\" will not work.
-------------------------------------------------"
fi

AC_PATH_PROG([perl_path], [perl], [no])
AC_SUBST(perl_path)
if test "x${perl_path}" = xno; then
    echo \
"-------------------------------------------------
 Unable to find Perl.
 \"make doxygen\" will not work.
-------------------------------------------------"
fi

AC_ARG_WITH(
    [dot],
    [dnl
  --without-dot           disable graph generation using dot (make doxygen)
                          @<:@default=use@:>@],
    [with_dot=${withval}],
    [with_dot=yes])
AC_SUBST(with_dot)

AC_ARG_WITH(
    [dot-multi-targets],
    [dnl
  --without-dot-multi-targets
                          disable dot's output to multiple files in one run
                          (make doxygen) @<:@default=use@:>@],
    [with_dot_multi_targets=${withval}],
    [with_dot_multi_targets=yes])
AC_SUBST(with_dot_multi_targets)

AC_ARG_WITH(
    [htags],
    [dnl
  --with-htags            enable the htags (GNU GLOBAL) source browser
                          (make doxygen) @<:@default=no@:>@],
    [with_htags=${withval}],
    [with_htags=no])
AC_SUBST(with_htags)

if test "x${have_doxygen}" = xyes -a "x${perl_path}" != xno; then
    if test "x${with_dot}" = xyes; then
        AC_CHECK_PROG([with_dot], [dot], [yes], [no])
        if test "x${with_dot}" = xno; then
            echo \
"-------------------------------------------------
 Unable to find dot.
 \"make doxygen\" will not build powerful graphs.
-------------------------------------------------"
        else
            if test "x${with_dot_multi_targets}" = xyes; then
                AC_MSG_CHECKING([for dot > 1.8.10])
                dot_version=`dot -V 2>&1 | \
                    sed -e 's/.*version //' | sed -e 's/ .*//'`
                # Requires AX_COMPARE_VERSION from the Autoconf Macro Archive
                AX_COMPARE_VERSION(
                    [$dot_version],
                    [gt],
                    [1.8.10],
                    [],
                    [with_dot_multi_targets=no])
                AC_MSG_RESULT([$with_dot_multi_targets])
                if test "x${with_dot_multi_targets}" = xno; then
                    echo \
"-------------------------------------------------
 Unable to find dot > 1.8.10.
 \"make doxygen\" will not enable dot to output
 multiple files in one run. Therefore it will run
 slower.
-------------------------------------------------"
                fi
            fi
        fi
    else
        with_dot_multi_targets=no
    fi

    if test "x${with_htags}" = xyes; then
        AC_MSG_CHECKING([for htags >= 4.8.6])
        htags_version=`htags --version |
            sed -ne 1p | sed -e 's/.* //'`
        # Requires AX_COMPARE_VERSION from the Autoconf Macro Archive
        AX_COMPARE_VERSION(
            [$htags_version],
            [ge],
            [4.8.6],
            [],
            [with_htags=no])
        AC_MSG_RESULT([$with_htags])
        if test "x${with_htags}" = xno; then
            echo \
"-------------------------------------------------
 Unable to find htags (GNU GLOBAL) >= 4.8.6.
 \"make doxygen\" will not use htags as the
 source browser.
-------------------------------------------------"
        fi
    fi
else
    with_dot=no
    with_dot_multi_targets=no
    with_htags=no
fi

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

PKG_CHECK_MODULES(
    [CPPUNIT],
    [cppunit >= 1.12.0],
    [have_cppunit=yes],
    [have_cppunit=no])
AC_SUBST(CPPUNIT_CFLAGS)
AC_SUBST(CPPUNIT_LIBS)
if test "x${have_cppunit}" = xno; then
    echo \
"-------------------------------------------------
 Unable to find CppUnit >= 1.12.0.
 \"make check\" will not work.
-------------------------------------------------"
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE

# Checks for library functions.
AC_FUNC_STAT
AC_CHECK_FUNCS([mkfifo])

AC_CONFIG_FILES([
    Makefile
    Doxyfile
    src/Makefile
    src/Contact/Makefile
    src/Control/Makefile
    src/Control/File/Makefile
    src/Exception/Makefile
    src/File/Makefile
    src/Option/Makefile
    tests/Makefile
])

AC_OUTPUT

echo \
"-------------------------------------------------

 ${PACKAGE_NAME} ${PACKAGE_VERSION}

 Prefix: '${prefix}'.
 Compiler: '${CC} ${CFLAGS} ${CPPFLAGS}'

 Package features:
  make doxygen:
   doxygen (needed)  : ${have_doxygen}
   Perl (needed)     : ${perl_path}
   dot               : ${with_dot}
   dot multi targets : ${with_dot_multi_targets}
   htags             : ${with_htags}
  make check:
   cppunit (needed)  : ${have_cppunit}

 Now type 'make @<:@<target>@:>@'
 where the optional <target> is:
  all                - build all binaries
  check              - run unittests
  doxygen            - build the documentation
  install            - install everything
  uninstall          - uninstall everything

-------------------------------------------------"
