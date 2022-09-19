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
#include <fdtools/util/hexdump.h>
#include <fdtools/util/log.h>
#include <fdtools/util/program.h>
#include <fdtools/util/string.h>

const char* OPT_trackS = "c";
const char* OPT_HEADS = "h";
const char* OPT_SECTORS = "n";
const char* OPT_SSIZE = "s";
const char* OPT_VERBOSE = "v";
const char* OPT_DEBUG = "d";
const char* OPT_RETRY_PASSES = "r";

bool verbose_enabled = false;
bool debug_enabled = false;
time_t progress_start_time;
FdtString* msg_outbuf;

void flush_message()
{
  if (fdt_string_length(msg_outbuf) == 0)
    return;
  printf("%s", fdt_string_getvalue(msg_outbuf));
  fdt_string_clear(msg_outbuf);
}

void print_message2buffer(const char* msg)
{
  fdt_string_appendvalue(msg_outbuf, msg);
}

void print_lf2buffer()
{
  print_message2buffer("\n");
}

void print_message(const char* format, ...)
{
  if (!verbose_enabled)
    return;

  flush_message();

  char msg[512];
  va_list list;
  va_start(list, format);
  vsnprintf(msg, sizeof(msg), format, list);
  va_end(list);
  printf("%s\n", msg);

  fflush(stdout);
}

void print_usage(FdtProgram* prg)
{
  flush_message();

  printf("Usage: %s [OPTIONS] <source device or file name>\n", fdt_program_getname(prg));
  fdt_program_printoptionusages(prg);
}

void print_error(FdtError* err)
{
  flush_message();

  printf("%s\n", debug_enabled ? fdt_error_getdebugmessage(err) : fdt_error_getmessage(err));
  fflush(stdout);
}

void panic()
{
  exit(EXIT_FAILURE);
}

void exit_error(FdtError* err)
{
  print_error(err);
  exit(EXIT_FAILURE);
}

void cursor_setenabled(bool flag)
{
  if (flag)
    fputs("\e[?25h", stdout);
  else
    fputs("\e[?25l", stdout);
}

void print_progress(FdtDeviceImage* img, FdtImageSector* sector, size_t dev_read_sector_cnt, size_t dev_sector_cnt)
{
  if (dev_sector_cnt <= 0)
    return;

  printf("\e[2K\e[G");
  if (verbose_enabled) {
    printf("\e[1A\e[2K\e[G");
    printf("\e[1A\e[2K\e[G");
  }

  int PROGRESS_BLOCK_MAX = 40;
  if (verbose_enabled) {
    PROGRESS_BLOCK_MAX = 60;
  }

  int read_percent = (dev_read_sector_cnt * 100) / dev_sector_cnt;
  printf("T:%03ld:%03ld H:%ld [", fdt_image_sector_gettracknumber(sector), fdt_image_sector_getnumber(sector), fdt_image_sector_getheadnumber(sector));
  for (int n = 0; n < PROGRESS_BLOCK_MAX; n++) {
    int block_percent = (n * 100) / PROGRESS_BLOCK_MAX;
    printf("%c", ((block_percent <= read_percent) ? '#' : ' '));
  }
  printf("] (%d%%)", read_percent);

  if (verbose_enabled) {
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

void exit_program()
{
  cursor_setenabled(true);
}

int main(int argc, char* argv[])
{
  atexit(exit_program);
  cursor_setenabled(false);

  FdtError* err = fdt_error_new();
  msg_outbuf = fdt_string_new();
  if (!err || !msg_outbuf) {
    panic();
  }

  // Parses command line arguments

  FdtProgram* prg = fdt_program_new();
  if (!prg) {
    panic();
  }
  fdt_program_addoption(prg, OPT_trackS, "number of tracks", true, "");
  fdt_program_addoption(prg, OPT_HEADS, "number of heads", true, "");
  fdt_program_addoption(prg, OPT_SECTORS, "number of sectors", true, "");
  fdt_program_addoption(prg, OPT_SSIZE, "sector size", true, "");
  fdt_program_addoption(prg, OPT_RETRY_PASSES, "number of retry passes", false, "");
  fdt_program_addoption(prg, OPT_VERBOSE, "enable verbose messages", false, "");
  fdt_program_addoption(prg, OPT_DEBUG, "enable debug messages", false, "");

  if (!fdt_program_parse(prg, argc, argv, err)) {
    print_error(err);
    print_usage(prg);
    return EXIT_FAILURE;
  }

  if (fdt_program_getnarguments(prg) < 1) {
    print_usage(prg);
    return EXIT_FAILURE;
  }

  // Sets command line options

  if (fdt_program_isoptionenabled(prg, OPT_VERBOSE)) {
    verbose_enabled = true;
  }
  if (fdt_program_isoptionenabled(prg, OPT_DEBUG)) {
    debug_enabled = true;
    fdt_log_setlevel(FDT_LOG_DEBUG);
  }

  // Loads source file image

  const char* img_name = fdt_program_getargument(prg, 0);

  FdtImage* img = fdt_image_plugins_create(img_name, err);
  if (!img) {
    exit_error(err);
  }

  if (fdt_image_isdevice(img)) {
    // Gets current device parameters, and set the parameters to image.
    FdtDevice* dev = fdt_device_new();
    fdt_device_setname(dev, img_name);
    FdtFloppyParams* fdparams = fdt_floppy_params_new();
    if (!dev || !fdparams) {
      panic();
    }
    if (!fdt_device_getfloppyparameters(dev, fdparams, err)) {
      exit_error(err);
    }
    if (!fdt_device_image_setfloppyparams(img, fdparams, err)) {
      exit_error(err);
    }
    fdt_device_delete(dev);
    fdt_floppy_params_delete(fdparams);
  }

  if (fdt_image_isdevice(img)) {
    // Shows progress infomation for device image types
    // TODO: Sets image parameters to device
    FdtDeviceImage* dev_img = (FdtDeviceImage*)img;
    if (!fdt_device_image_open(dev_img, img_name, FDT_FILE_READ, err)) {
      exit_error(err);
    }
    if (!fdt_device_image_generatesectors(dev_img, err)) {
      exit_error(err);
    }
    size_t dev_sector_cnt = fdt_device_image_getnsectors(dev_img);
    size_t dev_read_sector_cnt = 0;
    progress_start_time = time(NULL);
    FdtImageSector* sector = fdt_device_image_geterrorsector(dev_img);
    FdtImageSector* last_sector;
    while (sector) {
      last_sector = sector;
      print_progress(dev_img, sector, dev_read_sector_cnt, dev_sector_cnt);
      if (fdt_device_image_readsector(dev_img, sector, err)) {
        dev_read_sector_cnt++;
      }
      sector = fdt_device_image_geterrorsector(dev_img);
    }
    if (last_sector) {
      print_progress(dev_img, last_sector, dev_read_sector_cnt, dev_sector_cnt);
    }
    if (!fdt_device_image_close(dev_img, err)) {
      exit_error(err);
    }
  }
  else {
    if (!fdt_image_load(img, err)) {
      exit_error(err);
    }
  }

  // Print line field to message buffer

  print_lf2buffer();

  // Sets command line options

  int head_start_no = 0;
  int head_end_no = fdt_image_getnumberofhead(img) - 1;
  if (2 <= fdt_program_getnarguments(prg)) {
    head_start_no = head_end_no = fdt_str2int(fdt_program_getargument(prg, 1));
  }

  int cyclinder_start_no = 0;
  int cyclinder_end_no = fdt_image_getnumberofsector(img) - 1;
  if (3 <= fdt_program_getnarguments(prg)) {
    cyclinder_start_no = cyclinder_end_no = fdt_str2int(fdt_program_getargument(prg, 2));
  }

  int sector_start_no = 1;
  int sector_end_no = fdt_image_getnumberofcylinder(img);
  if (3 <= fdt_program_getnarguments(prg)) {
    sector_start_no = sector_end_no = fdt_str2int(fdt_program_getargument(prg, 3));
  }

  // Dumps sector bytes

  for (int c = cyclinder_start_no; c <= cyclinder_end_no; c++) {
    for (int h = head_start_no; h <= head_end_no; h++) {
      for (int s = sector_start_no; s <= sector_end_no; s++) {
        FdtImageSector* sector = fdt_image_getsector(img, c, h, s);
        if (!sector)
          continue;
        printf("cyl:%d head:%d sect:%d\n", c, h, s);
        size_t sector_size = fdt_image_sector_getsize(sector);
        byte_t* sector_data = fdt_image_sector_getdata(sector);
        fdt_hexdump_print(sector_data, sector_size);
        flush_message();
      }
    }
  }
  // Sets command line options

  fdt_image_delete(img);

  // Cleanups

  flush_message();
  fdt_program_delete(prg);
  fdt_error_delete(err);
  fdt_string_delete(msg_outbuf);

  return 0;
}