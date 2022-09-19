# Copyright (C) 2020 Satoshi Konno. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

AC_CONFIG_AUX_DIR(config)
AC_CONFIG_HEADERS(config.h)

AC_INIT([fdtools],[0.9.0])
AC_CONFIG_SRCDIR([include/fdtools/typedef.h])
AM_INIT_AUTOMAKE([subdir-objects])

##############################
# Checks for programs.
##############################

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_AWK
AC_PROG_RANLIB

##############################
# Checks for header files.
##############################

AC_CHECK_HEADERS([stdbool.h])
AC_CHECK_HEADERS([stdint.h])

##############################
# Testing
##############################

AC_ARG_ENABLE(
        [test],
        AS_HELP_STRING([--enable-test],[ build tests (default = no) ]),
        [case "${enableval}" in
        yes | no ) build_test="${enableval}" ;;
        esac],
        []
)

AM_CONDITIONAL(FDTOOLS_ENABLE_TEST,test "$build_test" = yes)
if [ test "$build_test" = yes ]; then
        AC_CHECK_LIB([boost_system-mt],[main],,
                [AC_CHECK_LIB([boost_system],[main],,[AC_MSG_ERROR(fdtools needs boost::system)])])
        AC_CHECK_LIB([boost_unit_test_framework-mt],[main],,
                [AC_CHECK_LIB([boost_unit_test_framework],[main],,[AC_MSG_ERROR(fdtools needs boost::unit_test_framework)])])
        AC_CHECK_LIB([boost_filesystem-mt],[main],,
                [AC_CHECK_LIB([boost_filesystem],[main],,[AC_MSG_ERROR(fdtools needs boost::filesystem)])])
fi

##############################
# Debug
##############################

AC_ARG_ENABLE(
 	[debug],
	AS_HELP_STRING([--enable-debug],[ enable debugging (default = no) ]),
	[case "${enableval}" in
    	yes | no ) enable_debug="${enableval}" ;;
	esac],
	[]
)

if [ test "$enable_debug" = yes ]; then
	AC_DEFINE([DEBUG],1,[Define to 1 if you want to debug])
        AS_VAR_APPEND([CFLAGS], [" -O0"])
        AS_VAR_APPEND([CPPFLAGS], [" -O0"])
fi

##############################
# Makefiles
##############################

AC_CONFIG_FILES([
Makefile
include/Makefile
lib/Makefile
lib/unix/Makefile
bin/Makefile
bin/fdcopy/Makefile
bin/fdcopy/unix/Makefile
bin/fdinfo/Makefile
bin/fdinfo/unix/Makefile
bin/fddump/Makefile
bin/fddump/unix/Makefile
bin/cpmls/Makefile
bin/cpmls/unix/Makefile
test/Makefile
test/unix/Makefile
])
AC_OUTPUT
