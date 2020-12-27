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

#ifndef _FDTOOLS_DEVICE_IMAGE_H_
#define _FDTOOLS_DEVICE_IMAGE_H_

#include <fdtools/dev/device.h>
#include <fdtools/img/image.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FDT_ATTR_PACKED {
  FDT_IMAGE_STRUCT_MEMBERS
  FdtDevice* dev;
} FdtDeviceImage;

FdtImage* fdt_device_image_new(void);

#define fdt_device_image_isopened(img) fdt_device_isopened(img->dev)
#define fdt_device_image_generatesectors(img, err) fdt_image_generatesectors((FdtImage*)img, err)
#define fdt_device_image_getsectoroffset(img, sector) fdt_image_getsectoroffset((FdtImage*)img, sector)
#define fdt_device_image_getsectors(img) fdt_image_getsectors((FdtImage*)img)
#define fdt_device_image_getsector(img, c, h, n) fdt_image_getsector((FdtImage*)img, c, h, n)

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_DEVICE_IMAGE_H_ */
