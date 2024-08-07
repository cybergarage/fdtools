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

AM_CFLAGS = -I$(top_builddir)/include -I$(top_builddir)/src
AM_CPPFLAGS = -I$(top_builddir)/include -I$(top_builddir)/src

fdtools_sources = \
	../../src/fdtools/util/struct.cpp \
	../../src/fdtools/util/program.cpp \
	../../src/fdtools/util/log.cpp \
	../../src/fdtools/util/string_func.cpp \
	../../src/fdtools/util/arguments.cpp \
	../../src/fdtools/util/strings.cpp \
	../../src/fdtools/util/bytes_le.cpp \
	../../src/fdtools/util/string.cpp \
	../../src/fdtools/util/bytes.cpp \
	../../src/fdtools/util/option.cpp \
	../../src/fdtools/util/file.cpp \
	../../src/fdtools/util/list.cpp \
	../../src/fdtools/util/hexdump_diff.cpp \
	../../src/fdtools/util/element.cpp \
	../../src/fdtools/util/argument.cpp \
	../../src/fdtools/util/hexdump.cpp \
	../../src/fdtools/util/dictionary.cpp \
	../../src/fdtools/error.cpp \
	../../src/fdtools/plugins/fmt/dos/func.cpp \
	../../src/fdtools/plugins/fmt/dos/fat.cpp \
	../../src/fdtools/plugins/fmt/dos/sector.cpp \
	../../src/fdtools/plugins/fmt/dos/bpb.cpp \
	../../src/fdtools/plugins/fmt/dos/dos.cpp \
	../../src/fdtools/plugins/fmt/dos/bpbex.cpp \
	../../src/fdtools/plugins/fmt/plugin.cpp \
	../../src/fdtools/plugins/fmt/plugins.cpp \
	../../src/fdtools/plugins/fmt/cpm/cpm.cpp \
	../../src/fdtools/plugins/fmt/cpm/directory.cpp \
	../../src/fdtools/plugins/fmt/x68/x68_img.cpp \
	../../src/fdtools/plugins/fmt/x68/x68.cpp \
	../../src/fdtools/plugins/fmt/loader.cpp \
	../../src/fdtools/plugins/img/func.cpp \
	../../src/fdtools/plugins/img/hfe/hfe_exporter.cpp \
	../../src/fdtools/plugins/img/hfe/hfe.cpp \
	../../src/fdtools/plugins/img/hfe/hfe_loader.cpp \
	../../src/fdtools/plugins/img/plugin.cpp \
	../../src/fdtools/plugins/img/d88/d88.cpp \
	../../src/fdtools/plugins/img/d88/d88_loader.cpp \
	../../src/fdtools/plugins/img/d88/d88_exporter.cpp \
	../../src/fdtools/plugins/img/plugins.cpp \
	../../src/fdtools/plugins/img/loader.cpp \
	../../src/fdtools/plugins/img/raw/raw_loader.cpp \
	../../src/fdtools/plugins/img/raw/raw.cpp \
	../../src/fdtools/plugins/img/raw/raw_exporter.cpp \
	../../src/fdtools/fmt/format.cpp \
	../../src/fdtools/fmt/file.cpp \
	../../src/fdtools/fmt/files.cpp \
	../../src/fdtools/img/image.cpp \
	../../src/fdtools/img/sector.cpp \
	../../src/fdtools/img/file.cpp \
	../../src/fdtools/img/config.cpp \
	../../src/fdtools/img/sectors.cpp \
	../../src/fdtools/img/density.cpp \
	../../src/fdtools/dev/device_unix.cpp \
	../../src/fdtools/dev/image.cpp \
	../../src/fdtools/dev/floppy_linux.cpp \
	../../src/fdtools/dev/device.cpp \
	../../src/fdtools/dev/device_linux.cpp \
	../../src/fdtools/dev/floppy.cpp

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
