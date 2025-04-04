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

#include <fdtools/plugins/fmt/cpm/cpm.h>

FdtFormat* fdt_cpm_new(void)
{
  FdtFormat* fmt = fdt_format_new();
  if (!fmt)
    return NULL;

  fmt->type = FDT_FORMAT_TYPE_CPM;

  fdt_format_setgettypeid(fmt, fdt_cpm_gettypeid);
  fdt_format_setformat(fmt, fdt_cpm_format);
  fdt_format_setlist(fmt, fdt_cpm_list);
  fdt_format_setadd(fmt, fdt_cpm_add);
  fdt_format_setdel(fmt, fdt_cpm_del);

  return fmt;
}

const char* fdt_cpm_gettypeid(FdtFormat* fmt, FdtError* err)
{
  return "CP/M";
}

bool fdt_cpm_format(FdtFormat* fmt)
{
  return false;
}

bool fdt_cpm_list(FdtFormat* fmt, FdtFiles* files, FdtError* err)
{
  FdtImage* img = fdt_format_getimage(fmt);

  size_t head_num = fdt_image_getnumberofhead(img);
  size_t sect_num = fdt_image_getnumberofsector(img);
  for (int t = FDT_CPM_DICTIONARY_START_TRACK_NO; t <= FDT_CPM_DICTIONARY_END_TRACK_NO; t++) {
    for (int h = 0; h < head_num; h++) {
      for (int s = 1; s <= sect_num; s++) {
        FdtImageSector* sector = fdt_image_getsector(img, t, h, s);
        if (!sector) {
          fdt_error_setmessage(err, fdt_cpm_DIRECTORY_SECTOR_NOT_FOUND, t, h, s);
          return false;
        }
        byte_t* sector_data = fdt_image_sector_getdata(sector);
        size_t sector_size = fdt_image_sector_getsize(sector);
        for (size_t offset = 0; offset < sector_size; offset += FDT_CPM_DICTIONARY_SIZE) {
          FdtCpmDirectory* dir = fdt_cpm_ditectory_new((sector_data + offset), (sector_size - offset));
          if (!dir)
            break;
          if (fdt_cpm_ditectory_isdeleted(dir))
            continue;
        }
      }
    }
  }

  return false;
}

bool fdt_cpm_add(FdtFormat* fmt, FdtFile* file, FdtError* err)
{
  return false;
}

bool fdt_cpm_del(FdtFormat* fmt, FdtFile* file, FdtError* err)
{
  return false;
}
