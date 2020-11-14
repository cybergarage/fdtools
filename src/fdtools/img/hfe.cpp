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

#include <stdio.h>
#include <string.h>

#include <fdtools/img/file.h>
#include <fdtools/util/string.h>

FdtHfeHeader* fdt_hfe_header_new(void)
{
  FdtHfeHeader* header = (FdtHfeHeader*)malloc(sizeof(FdtHfeHeader));
  if (!header) {
    return NULL;
  }
  fdt_image_header_init((FdtImageHeader*)header);
  return header;
}

bool fdt_hfe_header_load(FdtHfeHeader* header, FILE* fp)
{
  byte header_buf[sizeof(FdtHfeRawHeader)];
  if (!fdt_img_file_read(fp, header_buf, sizeof(header_buf)))
    return false;
  return fdt_hfe_header_parse(header, header_buf);
}

bool fdt_hfe_header_parse(FdtHfeHeader* header, byte* header_buf)
{
  FdtHfeRawHeader* raw_header = (FdtHfeRawHeader*)header_buf;
  fdt_hfe_raw_header_print(raw_header);
  return true;
}

void fdt_hfe_raw_header_print(FdtHfeRawHeader* header)
{
  printf("formatrevision:       %d\n", header->formatrevision);
  printf("number_of_track:      %d\n", header->number_of_track);
  printf("number_of_side:       %d\n", header->number_of_side);
  printf("track_encoding:       %d\n", header->track_encoding);
  printf("bitRate:              %d\n", header->bitRate);
  printf("floppyRPM:            %d\n", header->floppyRPM);
  printf("floppyinterfacemode:  %02X\n", header->floppyinterfacemode);
  printf("dnu:                  %d\n", header->dnu);
  printf("track_list_offset:    %d\n", header->track_list_offset);
  printf("write_allowed:        %d\n", header->write_allowed);
  printf("single_step:          %s\n", (header->single_step == HFE_SINGLE_STEP) ? "S" : "D");
  printf("track0s0_altencoding: %02X\n", header->track0s0_altencoding);
  printf("track0s0_encoding:    %02X\n", header->track0s0_encoding);
  printf("track0s1_altencoding: %02X\n", header->track0s1_altencoding);
  printf("track0s1_encoding:    %02X\n", header->track0s1_encoding);
}
