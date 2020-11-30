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

bool fdt_hfe_header_parse(FdtHfeHeader* header, byte* header_buf);
bool fdt_image_sethfeheaderinfo(FdtImage* img, FdtHfeHeader* header);
void fdt_hfe_header_print(FdtHfeTrackOffsets*, size_t);
void fdt_hfe_track_print(byte* track_buf, size_t track_len);

bool fdt_hfe_image_load(FdtImage* img, FILE* fp, FdtError* err)
{
  // Read first part: File header

  byte header_buf[sizeof(FdtHfeHeader)];
  if (!fdt_file_read(fp, header_buf, sizeof(header_buf)))
    return false;

  FdtHfeHeader hfe_header;
  if (!fdt_hfe_header_parse(&hfe_header, header_buf))
    return false;
  if (!fdt_image_sethfeheaderinfo(img, &hfe_header))
    return false;

  fdt_hfe_header_print(&hfe_header);

  // Read second part: Track offset LUT

  size_t track_list_offset = hfe_header.track_list_offset * 512;
  if (!fdt_file_seek(fp, track_list_offset, SEEK_SET))
    return false;
  
  size_t number_of_track = hfe_header.number_of_track;
  size_t number_of_head = hfe_header.number_of_side;
  //size_t number_of_all_track = number_of_track * number_of_head;
  size_t track_offsets_buf_size = sizeof(FdtHfeTrackOffsets) * number_of_track;
  FdtHfeTrackOffsets* hfe_track_offsets = (FdtHfeTrackOffsets*)malloc(track_offsets_buf_size);
  if (!hfe_track_offsets)
    return false;
  if (!fdt_file_read(fp, hfe_track_offsets, track_offsets_buf_size)) {
    free(hfe_track_offsets);
    return false;
  }

  fdt_hfe_header_print(hfe_track_offsets, number_of_track);

  // Read third part: Track data
  
  for (size_t n = 0; n < number_of_track; n++) {
    size_t track_offset = hfe_track_offsets[n].offset;
    size_t track_data_offset = 512 * track_offset;
    if (!fdt_file_seek(fp, track_data_offset, SEEK_SET))
      return false;
    size_t track_len = hfe_track_offsets[n].track_len;
    byte* track_buf = (byte*)malloc(track_len);
    if (fdt_file_read(fp, track_buf, track_len)) {
      //fdt_hfe_track_print(track_buf, track_len);
    }
    free(track_buf);
  }

  return true;
}

bool fdt_hfe_header_parse(FdtHfeHeader* header, byte* header_buf)
{
  // TODO: Support Big-endian architecture
  memcpy(header, header_buf, sizeof(FdtHfeHeader));
  //fdt_hfe_header_print(header);
  return true;
}

bool fdt_image_sethfeheaderinfo(FdtImage* img, FdtHfeHeader* header)
{
  fdt_image_setwriteprotect(img, header->write_allowed ? true : false);
  fdt_image_setnumberofcylinder(img, header->number_of_track);
  fdt_image_setnumberofhead(img, header->number_of_side);
  fdt_image_setrpm(img, header->floppyRPM);

  return true;
}

void fdt_hfe_header_print(FdtHfeHeader* header)
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

void fdt_hfe_header_print(FdtHfeTrackOffsets* track_offsets, size_t number_of_track)
{
  for (size_t n = 0; n < number_of_track; n++) {
    printf("[%02ld] %04X %d\n", n, track_offsets[n].offset, track_offsets[n].track_len);
  }
}

void fdt_hfe_track_print(byte* track_buf, size_t track_len)
{
  for (size_t n = 0; n < track_len; n++) {
    printf("%02X", track_buf[n]);
  }
  printf("\n");
}
