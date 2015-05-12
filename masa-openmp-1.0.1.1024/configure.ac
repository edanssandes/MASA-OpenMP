AC_PREREQ([2.63])
AC_INIT([MASA-OpenMP], [1.0.1.1024], [edans.sandes@gmail.com], [masa-openmp], [https://github.com/edanssandes/MASA-OpenMP])
AC_CONFIG_AUX_DIR(admin)
AM_INIT_AUTOMAKE([-Wall -Werror])
m4_include([m4/ax_check_compile_flag.m4])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_FILES([Makefile])

AC_CONFIG_SUBDIRS([libs/masa-core])

AC_PROG_CXX

LIBMASA_PATH="libs/masa-core"

AC_CHECK_FILES(
	[$LIBMASA_PATH $LIBMASA_PATH/src],
	,
	AC_MSG_ERROR([
		MASA-Core source directory was not found: $LIBMASA_PATH/src.
	])
)

# Checks for header files.
AC_CHECK_HEADERS([omp.h],,
	AC_MSG_ERROR([Missing required header files.]))


OPTIMIZATION="-O3"

AC_ARG_ENABLE([debug],
	AC_HELP_STRING([--enable-debug],[enable GDB debug]),
	[DEBUG="-ggdb"; OPTIMIZATION=""]
)

#default: 64bit
AC_ARG_ENABLE([32bit],
	AC_HELP_STRING([--enable-32bit],[force compilation in 32 bit mode.]),
	[ARCH="386"; PLATFORM="-m32";
		AC_MSG_NOTICE([Enabling 32bit compilation])
	],
	[ARCH="x86_64"; PLATFORM="-m64";
		AC_MSG_NOTICE([Enabling 64bit compilation])	
	]
)

AX_CHECK_COMPILE_FLAG([-fopenmp],	[COMMONFLAGS="$COMMONFLAGS -fopenmp"],
	AC_MSG_ERROR([Compiler does not support OpenMP. GCC suports it since 4.2]))
	
CXXFLAGS="-DUNIX $COMMONFLAGS $PLATFORM $OPTIMIZATION $DEBUG -I$LIBMASA_PATH/src"

AC_SUBST(LIBMASA_PATH)
AC_SUBST(CXXFLAGS)

AC_OUTPUT
