// Copyright (C) 2020 Satoshi Konno. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <fdtools/dev/device.h>
#include <fdtools/dev/image.h>
#include <fdtools/img/image.h>
#include <fdtools/plugins/image.h>
#include <fdtools/util/log.h>
#include <fdtools/util/program.h>
#include <fdtools/util/string.h>

#include "console.h"
#include "program.h"

extern bool program_verbose_enabled;
extern bool program_debug_enabled;

time_t progress_start_time;
FdtString* msg_outbuf;

void fdu_cursor_setenabled(bool flag)
{
  if (flag)
    fputs("\e[?25h", stdout);
  else
    fputs("\e[?25l", stdout);
}

void console_stop()
{
  fdt_string_delete(msg_outbuf);
  fdu_cursor_setenabled(true);
}

void fdu_console_enabled()
{
  msg_outbuf = fdt_string_new();
  if (!msg_outbuf) {
    panic();
  }
  progress_start_time = time(NULL);
  atexit(console_stop);
  fdu_cursor_setenabled(false);
}

void fdu_console_refresh_progresstime()
{
  progress_start_time = time(NULL);
}

void fdu_console_flush()
{
  if (fdt_string_length(msg_outbuf) == 0)
    return;
  printf("%s", fdt_string_getvalue(msg_outbuf));
  fdt_string_clear(msg_outbuf);
}

void fdu_console_message2buffer(const char* msg)
{
  fdt_string_appendvalue(msg_outbuf, msg);
}

void fdu_console_lf()
{
  fdu_console_message2buffer("\n");
}

void fdu_console_message(const char* format, ...)
{
  if (!program_verbose_enabled)
    return;

  fdu_console_flush();

  char msg[512];
  va_list list;
  va_start(list, format);
  vsnprintf(msg, sizeof(msg), format, list);
  va_end(list);
  printf("%s\n", msg);

  fflush(stdout);
}

void fdu_console_updatedeviceprogress(FdtDeviceImage* img, FdtImageSector* sector, size_t dev_read_sector_cnt, size_t dev_sector_cnt)
{
  if (dev_sector_cnt <= 0)
    return;

  printf("\e[2K\e[G");
  if (program_verbose_enabled) {
    printf("\e[1A\e[2K\e[G");
    printf("\e[1A\e[2K\e[G");
  }

  int PROGRESS_BLOCK_MAX = 40;
  if (program_verbose_enabled) {
    PROGRESS_BLOCK_MAX = 60;
  }

  int read_percent = (dev_read_sector_cnt * 100) / dev_sector_cnt;
  printf("T:%03ld:%03ld H:%ld [", fdt_image_sector_getcylindernumber(sector), fdt_image_sector_getnumber(sector), fdt_image_sector_getheadnumber(sector));
  for (int n = 0; n < PROGRESS_BLOCK_MAX; n++) {
    int block_percent = (n * 100) / PROGRESS_BLOCK_MAX;
    printf("%c", ((block_percent <= read_percent) ? '#' : ' '));
  }
  printf("] (%d%%)", read_percent);

  if (program_verbose_enabled) {
    int read_sector_cnt = 0;
    int err_sector_cnt = 0;
    int error_cnt = 0;
    for (FdtImageSectors* sector = fdt_device_image_getsectors(img); sector; sector = fdt_image_sector_next(sector)) {
      if (fdt_image_sector_hasdata(sector)) {
        read_sector_cnt++;
      }
      int sector_err_cnt = fdt_image_sector_geterrorcount(sector);
      if (0 < sector_err_cnt) {
        err_sector_cnt++;
        error_cnt += sector_err_cnt;
      }
    }
    time_t elapsed_time = time(NULL) - progress_start_time;
    printf("\ncyl=%ld, head=%ld, sect=%ld, ssize=%ld", fdt_image_getnumberofcylinder(img), fdt_image_getnumberofhead(img), fdt_image_getnumberofsector(img), fdt_image_getsectorsize(img));
    printf("\nruntime: % 4lds,   read sectors: % 4d,   error sectors: % 4d,   read errors: % 4d", elapsed_time, read_sector_cnt, err_sector_cnt, error_cnt);
  }

  fflush(stdout);
}
