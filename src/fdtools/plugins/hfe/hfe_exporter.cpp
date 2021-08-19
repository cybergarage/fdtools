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

bool fdt_hfe_header_setconfig(FdtHfeHeader* hfe_header, FdtImage* img, FdtError* err);

bool fdt_hfe_image_export(FdtFileImage* img, FdtError* err)
{
  if (!img)
    return false;

  FILE* fp = fdt_image_file_getfile(img);
  if (!fp)
    return false;

  FdtHfeHeader hfe_header;
  if (!fdt_hfe_header_setconfig(&hfe_header, (FdtImage*)img, err))
    return false;

  if (!fdt_file_write(fp, &hfe_header, sizeof(hfe_header))) {
    fdt_error_setlasterror(err, "");
    return false;
  }

  return false;
}

bool fdt_hfe_header_setconfig(FdtHfeHeader* hfe_header, FdtImage* img, FdtError* err)
{
  memcpy(hfe_header->HEADERSIGNATURE, HFE_IMAGE_HEADER_SIGNATURE, 8);
  hfe_header->formatrevision = 0;
  hfe_header->number_of_track = fdt_image_getnumberofcylinder(img);
  hfe_header->number_of_side = fdt_image_getnumberofhead(img);
  hfe_header->track_encoding = HFE_ISOIBM_MFM_ENCODING;
  hfe_header->bitRate = 0; // TODO
  hfe_header->floppyRPM = fdt_image_getrpm(img);
  switch (fdt_image_getdensity(img)) {
  case FDT_IMAGE_DENSITY_HD:
    hfe_header->floppyinterfacemode = HFE_IBMPC_HD_FLOPPYMODE;
  default:
    hfe_header->floppyinterfacemode = HFE_GENERIC_SHUGGART_DD_FLOPPYMODE;
  }
  hfe_header->dnu = 0x01; /* Undifined? */
  hfe_header->track_list_offset = 1; /* 0x200 */
  hfe_header->write_allowed = fdt_image_getwriteprotect(img) ? 0x00 : 0xFF;
  hfe_header->single_step = HFE_SINGLE_STEP;
  hfe_header->track0s0_altencoding = HFE_UNKNOWN_ENCODING;
  hfe_header->track0s0_encoding = 0x00;
  hfe_header->track0s1_altencoding = HFE_UNKNOWN_ENCODING;
  hfe_header->track0s1_encoding = 0x00;

  return true;
}
