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

#include <fdtools/img/file.h>
#include <fdtools/plugins/hfe/hfe.h>
#include <fdtools/util/hexdump.h>
#include <fdtools/util/logic.h>
#include <fdtools/util/string.h>

bool fdt_hfe_header_parse(FdtHfeHeader* header, byte_t* header_buf);
bool fdt_image_sethfeheaderinfo(FdtFileImage* img, FdtHfeHeader* header);
void fdt_hfe_header_print(FdtHfeTrackOffsets*, size_t);
void fdt_hfe_track_print(byte_t* track_buf, size_t track_len);

bool fdt_hfe_image_load(FdtFileImage* img, FdtError* err)
{
  if (!img)
    return false;

  FILE* fp = fdt_image_file_getfile(img);
  if (!fp)
    return false;

  // First part : 0x0000-0x0200 (512 bytes) : File header

  byte_t header_buf[sizeof(FdtHfeHeader)];
  if (!fdt_file_read(fp, header_buf, sizeof(header_buf)))
    return false;

  FdtHfeHeader hfe_header;
  if (!fdt_hfe_header_parse(&hfe_header, header_buf))
    return false;
  if (!fdt_image_sethfeheaderinfo(img, &hfe_header))
    return false;

  //fdt_hfe_header_print(&hfe_header);

  // Second part : (up to 1024 bytes) : Track offset LUT

  size_t track_list_offset = hfe_header.track_list_offset * HFE_TRACK_BLOCK_SIZE;
  if (!fdt_file_seek(fp, track_list_offset, SEEK_SET))
    return false;

  size_t number_of_track = hfe_header.number_of_track;
  size_t number_of_head = hfe_header.number_of_side;

  size_t track_offsets_buf_size = sizeof(FdtHfeTrackOffsets) * number_of_track;
  FdtHfeTrackOffsets* hfe_track_offsets = (FdtHfeTrackOffsets*)malloc(track_offsets_buf_size);
  if (!hfe_track_offsets)
    return false;
  if (!fdt_file_read(fp, hfe_track_offsets, track_offsets_buf_size)) {
    free(hfe_track_offsets);
    return false;
  }

  //fdt_hfe_header_print(hfe_track_offsets, number_of_track);

  // Third part : Track data

  for (size_t t = 0; t < number_of_track; t++) {
    size_t track_offset = hfe_track_offsets[t].offset;
    size_t track_data_offset = track_offset * HFE_TRACK_BLOCK_SIZE;
    if (!fdt_file_seek(fp, track_data_offset, SEEK_SET))
      return false;

    byte_t track_block_data[HFE_TRACK_BLOCK_SIZE];
    size_t track_block_data_offset = 0;
    while (track_block_data_offset < hfe_track_offsets[t].track_len) {
      if (!fdt_file_read(fp, track_block_data, HFE_TRACK_BLOCK_SIZE)) {
        return false;
      }

      for (size_t h = 0; h < number_of_head; h++) {
        FdtImageSector* sector = fdt_image_sector_new();
        if (!sector) {
          return false;
        }

        size_t sector_data_size = HFE_TRACK_BLOCK_SIZE / 2;
        byte_t* sector_data = (byte_t*)malloc(sector_data_size);
        if (!sector_data) {
          fdt_image_sector_delete(sector);
          return false;
        }

        byte_t* track_block_sector_data = track_block_data + (sector_data_size * h);
        for (size_t b = 0; b < sector_data_size; b++) {
          sector_data[b] = fdt_byte_reverse(track_block_sector_data[b]);
        }

        fdt_image_sector_setcylindernumber(sector, t);
        fdt_image_sector_setheadnumber(sector, h);
        fdt_image_sector_setnumber(sector, 0 /*TODO*/);
        fdt_image_sector_setsize(sector, sector_data_size);
        fdt_image_sector_setdata(sector, sector_data);

        fdt_image_addsector(img, sector);

        //fdt_hexdump_print(sector_data, sector_data_size);
      }

      track_block_data_offset += HFE_TRACK_BLOCK_SIZE;
    }
  }

  return true;
}

bool fdt_hfe_header_parse(FdtHfeHeader* header, byte_t* header_buf)
{
  memcpy(header, header_buf, sizeof(FdtHfeHeader));
  return true;
}

bool fdt_image_sethfeheaderinfo(FdtFileImage* img, FdtHfeHeader* header)
{
  fdt_image_setwriteprotectenabled(img, header->write_allowed ? true : false);
  fdt_image_setnumberofcylinder(img, header->number_of_track);
  fdt_image_setnumberofhead(img, header->number_of_side);
  fdt_image_setbitrate(img, header->bitRate);
  fdt_image_setrpm(img, header->floppyRPM);

  return true;
}

void fdt_hfe_header_print(FdtHfeHeader* header)
{
  printf("formatrevision:       %d\n", header->formatrevision);
  printf("number_of_track:      %d\n", header->number_of_track);
  printf("number_of_head:       %d\n", header->number_of_side);
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
