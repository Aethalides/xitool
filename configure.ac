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


AC_OUTPUT