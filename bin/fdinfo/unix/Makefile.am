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

bin_PROGRAMS = fdinfo

AM_CFLAGS = -I$(top_builddir)/include -I../ -I../../
AM_CPPFLAGS = -I$(top_builddir)/include -I../ -I../../

fdinfo_SOURCES = \
	../../fdutils/program.cpp \
	../../fdutils/console.cpp \
	../../fdutils/device.cpp \
	..//main.cpp

#if HAVE_LIBTOOL
#fdinfo_LDADD = ../../../lib/unix/libfdtools.la
#else
fdinfo_LDADD = ../../../lib/unix/libfdtools.a
#endif
