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
	../image_test.h

fdtoolstest_SOURCES = \
	../device_floppy_test.cpp \
	../image_d88_test.cpp \
	../image_raw_test.cpp \
	../config_test.cpp \
	../logic_test.cpp \
	../image_test_func.cpp \
	../device_test.cpp \
	../program_test.cpp \
	../image_hfe_test.cpp \
	../image_file_test.cpp \
	../device_floppy_params_test.cpp \
	../string_test.cpp \
	../sector_test.cpp \
	../main.cpp \
	../dictionary_test.cpp \
	../error_test.cpp \
	../list_test.cpp \
	../image_test.cpp

#if HAVE_LIBTOOL
#fdtoolstest_LDADD = ../../lib/unix/libfdtools.la
#else
fdtoolstest_LDADD = ../../lib/unix/libfdtools.a
#endif
