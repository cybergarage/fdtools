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
#include <math.h>

bool fdt_hfe_header_setconfig(FdtHfeHeader* hfe_header, FdtImage* img, FdtError* err);

bool fdt_hfe_image_export(FdtFileImage* img, FdtError* err)
{
  if (!img)
    return false;

  FILE* fp = fdt_image_file_getfile(img);
  if (!fp)
    return false;

  size_t number_of_track = fdt_image_getnumberoftrack(img);
  size_t number_of_head = fdt_image_getnumberofhead(img);

  // First part : 0x0000-0x0200 (512 bytes) : File header

  byte_t hfe_header_buf[HFE_HEADER_BLOCK_SIZE];
  memset(hfe_header_buf, 0x00, sizeof(hfe_header_buf));

  FdtHfeHeader* hfe_header = (FdtHfeHeader*)hfe_header_buf;
  if (!fdt_hfe_header_setconfig(hfe_header, (FdtImage*)img, err))
    return false;

  if (!fdt_file_write(fp, hfe_header_buf, sizeof(hfe_header_buf))) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  // Second part : (up to 1024 bytes) : Track offset LUT

  size_t track_offset_lut_size = HFE_TRACK_OFFSET_LUT_SIZE;
  size_t track_offset_lut_track_max = track_offset_lut_size / sizeof(FdtHfeTrackOffsets);
  if (track_offset_lut_track_max < number_of_track) { // Up to 1024 ?
    track_offset_lut_size += HFE_TRACK_OFFSET_LUT_SIZE;
    track_offset_lut_track_max = track_offset_lut_size / sizeof(FdtHfeTrackOffsets);
    if (track_offset_lut_track_max < number_of_track) {
      fdt_error_setmessage(err, "number of track is so big (%d)", number_of_track);
      return false;
    }
  }

  byte_t track_offset_lut_buf[track_offset_lut_size];
  memset(hfe_header_buf, 0x00, sizeof(track_offset_lut_buf));
  FdtHfeTrackOffsets* track_offsets = (FdtHfeTrackOffsets*)track_offset_lut_buf;

  size_t track_offset_block_no = (HFE_HEADER_BLOCK_SIZE + track_offset_lut_size) / 512;
  for (size_t t = 0; t < number_of_track; t++) {
    track_offsets[t].offset = track_offset_block_no;
    size_t track_max_size = 0;
    for (size_t h = 0; h < number_of_head; h++) {
      size_t track_size = fdt_image_gettracksize(img, t, h);
      track_max_size = (track_max_size < track_size) ? track_size : track_max_size;
    }
    track_offsets[t].track_len = track_max_size * 2;
    track_offset_block_no += size_t(ceil((double)track_offsets[t].track_len / 512.0));
  }

  if (!fdt_file_write(fp, track_offset_lut_buf, sizeof(track_offset_lut_buf))) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  // Third part : Track data

  for (size_t t = 0; t < number_of_track; t++) {
    size_t track_sizes[number_of_head];
    byte_t* track_bytes[number_of_head];
    for (size_t h = 0; h < number_of_head; h++) {
      track_sizes[h] = fdt_image_gettracksize(img, t, h);
      track_bytes[h] = fdt_image_gettrackbytes(img, t, h);
    }

    byte_t track_block[512];
    size_t track_block_count = size_t(ceil((double)track_offsets[t].track_len / (double)HFE_TRACK_BLOCK_SIDE_SIZE));
    for (size_t b = 0; b < track_block_count; b++) {
      memset(track_block, 0, sizeof(track_block));
      for (size_t h = 0; ((h < number_of_head) && (h < 2)); h++) {
        size_t left_bytes = track_sizes[h] - (b * HFE_TRACK_BLOCK_SIDE_SIZE);
        memcpy(track_block + (h * HFE_TRACK_BLOCK_SIDE_SIZE), track_bytes[h] + (b * HFE_TRACK_BLOCK_SIDE_SIZE), ((HFE_TRACK_BLOCK_SIDE_SIZE <= left_bytes) ?HFE_TRACK_BLOCK_SIDE_SIZE : left_bytes));
      }

      for (size_t n = 0; n < sizeof(track_block); n++) {
        track_block[n] = fdt_byte_reverse(track_block[n]);
      }

      if (!fdt_file_write(fp, track_block, sizeof(track_block))) {
        fdt_error_setlasterror(err, "");
        return false;
      }
    }

    for (size_t h = 0; h < number_of_head; h++) {
      free(track_bytes[h]);
    }
  }

  return true;
}

bool fdt_hfe_header_setconfig(FdtHfeHeader* hfe_header, FdtImage* img, FdtError* err)
{
  memcpy(hfe_header->HEADERSIGNATURE, HFE_IMAGE_HEADER_SIGNATURE, 8);
  hfe_header->formatrevision = 0;
  hfe_header->number_of_track = fdt_image_getnumberoftrack(img);
  hfe_header->number_of_side = fdt_image_getnumberofhead(img);
  hfe_header->track_encoding = HFE_ISOIBM_MFM_ENCODING;
  hfe_header->bitRate = fdt_image_getbitrate(img);
  hfe_header->floppyRPM = fdt_image_getrpm(img);
  switch (fdt_image_getdensity(img)) {
  case FDT_IMAGE_DENSITY_HD:
    hfe_header->floppyinterfacemode = HFE_IBMPC_HD_FLOPPYMODE;
  default:
    hfe_header->floppyinterfacemode = HFE_GENERIC_SHUGGART_DD_FLOPPYMODE;
  }
  hfe_header->dnu = 0x01; /* Undifined? */
  hfe_header->track_list_offset = 1; /* 0x200 */
  hfe_header->write_allowed = fdt_image_iswriteprotectenabled(img) ? 0x00 : 0xFF;
  hfe_header->single_step = HFE_SINGLE_STEP;
  hfe_header->track0s0_altencoding = HFE_UNKNOWN_ENCODING;
  hfe_header->track0s0_encoding = HFE_UNKNOWN_ENCODING;
  hfe_header->track0s1_altencoding = HFE_UNKNOWN_ENCODING;
  hfe_header->track0s1_encoding = HFE_UNKNOWN_ENCODING;

  return true;
}
