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

TESTS = fdtoolstest

check_PROGRAMS = fdtoolstest

AM_CPPFLAGS = -I$(top_builddir)/include -I../


fdtoolstest_SOURCES = \
	..//device_test.cpp \
	..//hfe_test.cpp \
	..//dictionary_test.cpp \
	..//string_test.cpp \
	..//program_test.cpp \
	..//file_test.cpp \
	..//d88_test.cpp \
	..//logic_test.cpp \
	..//raw_test.cpp \
	..//image_test.cpp \
	..//main.cpp \
	..//dev_floppy_test.cpp \
	..//error_test.cpp

#if HAVE_LIBTOOL
#fdtoolstest_LDADD = ../../lib/unix/libfdtools.la
#else
fdtoolstest_LDADD = ../../lib/unix/libfdtools.a
#endif
