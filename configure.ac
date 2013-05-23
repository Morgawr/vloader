AC_INIT([vloader], [0.01], [morgawr@gmail.com], [vloader], [https://github.com/Morgawr/vloader])
AC_PREREQ([2.69])

AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_HEADERS([include/config.h])

#C compiler
AC_PROG_CC
AM_PROG_CC_C_O

#assembler
AM_PROG_AS

#Check architecture
AC_CANONICAL_HOST

if test "$(cd $srcdir; /bin/pwd)" = "$(/bin/pwd)"; then
  AC_MSG_ERROR([you must configure in a separate build directory])
fi

AS_CASE([$host_cpu],
	[i?86], [ARCH=i386],
	[x86_64], [ARCH=x86_64],
	[AC_MSG_ERROR("No assembler code for CPU $host_cpu")]
)
AC_SUBST([ARCH])

AC_CONFIG_SRCDIR(main/vloader.c)


AC_CONFIG_FILES([Makefile])
AC_OUTPUT
