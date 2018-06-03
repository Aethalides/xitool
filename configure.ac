AC_INIT([xitool], [0.0.1], [https://github.com/Aethalides/xitool/], [xitool])
AC_PROG_CC_C99
AC_CONFIG_FILES([Makefile src/Makefile])

AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([-Wall foreign dist-bzip2])

m4_ifndef([XORG_MACROS_VERSION],
          [m4_fatal([xorg-util-macros is required])])
XORG_MACROS_VERSION(1.15)
XORG_DEFAULT_OPTIONS

PKG_CHECK_MODULES(
	XINPUT, x11 xext [xi >= 1.5] [inputproto >= 1.9]
	xrandr xinerama 
);

AC_ARG_ENABLE(debug,
    AC_HELP_STRING(--enable-debug, [Debug compilation (Default = no)]),
    enable_debug=$enableval, enable_debug=no)

if test "$enable_debug" = "yes" ; then
    CFLAGS="$CFLAGS  -g -O2 -Wall -Wpointer-arith -Wmissing-declarations -Wformat=2 -Wstrict-prototypes -Wmissing-prototypes -Wnested-externs -Wbad-function-cast -Wold-style-definition -Wdeclaration-after-statement -Wunused -Wuninitialized -Wshadow -Wmissing-noreturn -Wmissing-format-attribute -Wredundant-decls -Wlogical-op -Werror=implicit -Werror=nonnull -Werror=init-self -Werror=main -Werror=missing-braces -Werror=sequence-point -Werror=return-type -Werror=trigraphs -Werror=array-bounds -Werror=write-strings -Werror=address -Werror=int-to-pointer-cast -Werror=pointer-to-int-cast -fno-strict-aliasing  -pedantic -Werror -Werror=attributes"
    CXXFLAGS="$CXXFLAGS -g -O2 -Wall -Wpointer-arith -Wmissing-declarations -Wformat=2 -Wstrict-prototypes -Wmissing-prototypes -Wnested-externs -Wbad-function-cast -Wold-style-definition -Wdeclaration-after-statement -Wunused -Wuninitialized -Wshadow -Wmissing-noreturn -Wmissing-format-attribute -Wredundant-decls -Wlogical-op -Werror=implicit -Werror=nonnull -Werror=init-self -Werror=main -Werror=missing-braces -Werror=sequence-point -Werror=return-type -Werror=trigraphs -Werror=array-bounds -Werror=write-strings -Werror=address -Werror=int-to-pointer-cast -Werror=pointer-to-int-cast -fno-strict-aliasing  -pedantic -Werror -Werror=attributes"
fi

AC_DEFINE([_GNU_SOURCE], [0],[Disables GNU extensions])

AC_ARG_ENABLE(gnu,
	AS_HELP_STRING([--disable-gnu], [Disable GNU extensions]),
	enable_gnu=$enableval, enable_gnu=no)

if test "$enable_gnu" = "yes"; then
  AC_DEFINE([_GNU_SOURCE], [1],[Enables GNU extensions])
fi

AC_OUTPUT