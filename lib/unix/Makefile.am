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
#
#if HAVE_LIBTOOL
#lib_LTLIBRARIES = libfdtools.la
#else
lib_LIBRARIES = libfdtools.a
#endif

AM_CFLAGS = -I$(top_builddir)/include
AM_CPPFLAGS = -I$(top_builddir)/include

fdtools_sources = \
	../../src/fdtools/util/program.cpp \
	../../src/fdtools/util/arguments.cpp \
	../../src/fdtools/util/string.cpp \
	../../src/fdtools/util/struct.cpp \
	../../src/fdtools/util/list.cpp \
	../../src/fdtools/util/argument.cpp \
	../../src/fdtools/util/option.cpp \
	../../src/fdtools/util/file.cpp \
	../../src/fdtools/util/string_func.cpp \
	../../src/fdtools/util/dictionary.cpp \
	../../src/fdtools/util/element.cpp \
	../../src/fdtools/util/hexdump.cpp \
	../../src/fdtools/img/d88.cpp \
	../../src/fdtools/img/image.cpp \
	../../src/fdtools/img/density.cpp \
	../../src/fdtools/img/config.cpp \
	../../src/fdtools/img/raw_exporter.cpp \
	../../src/fdtools/img/d88_exporter.cpp \
	../../src/fdtools/img/func.cpp \
	../../src/fdtools/img/hfe.cpp \
	../../src/fdtools/img/file.cpp \
	../../src/fdtools/img/sector.cpp \
	../../src/fdtools/img/raw.cpp \
	../../src/fdtools/img/sectors.cpp \
	../../src/fdtools/img/hfe_loader.cpp \
	../../src/fdtools/img/d88_loader.cpp \
	../../src/fdtools/img/raw_loader.cpp \
	../../src/fdtools/dev/image.cpp \
	../../src/fdtools/dev/floppy_linux.cpp \
	../../src/fdtools/dev/device_unix.cpp \
	../../src/fdtools/dev/device.cpp \
	../../src/fdtools/dev/device_linux.cpp \
	../../src/fdtools/dev/floppy.cpp \
	../../src/fdtools/error.cpp

libfdtoolsincludedir = $(includedir)/fdtools
nobase_libfdtoolsinclude_HEADERS =  \
        $(fdtools_headers)

#if HAVE_LIBTOOL
#libfdtools_la_SOURCES = \
#        $(fdtools_source)
#libfdtools_la_CFLAGS = $(AM_CFLAGS)
#else
libfdtools_a_SOURCES = \
        $(fdtools_sources)
libfdtools_a_CFLAGS = $(AM_CFLAGS)
#endif
