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
AM_CONFIG_HEADER(config.h)

AC_INIT([fdutils], [0.1])
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

##############################
# Debug
##############################

AC_ARG_ENABLE(
 	[debug],
	AC_HELP_STRING([--enable-debug], [ enable debugging (default = no) ]),
	[case "${enableval}" in
    	yes | no ) enable_debug="${enableval}" ;;
	esac],
	[]
)

if [ test "$enable_debug" = yes ]; then
	AC_DEFINE([DEBUG],1,[Define to 1 if you want to debug])
fi

##############################
# Makefiles
##############################

AC_OUTPUT([
Makefile
include/Makefile
lib/Makefile
lib/unix/Makefile
bin/Makefile
bin/fdwrite/Makefile
bin/fdwrite/unix/Makefile
bin/fdread/Makefile
bin/fdwrite/unix/Makefile
bin/fdinfo/Makefile
bin/fdinfo/unix/Makefile
])
