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

#ifndef _FDTOOLS_DEV_ERROR_H_
#define _FDTOOLS_DEV_ERROR_H_

#include <fdtools/error.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FDT_DEVICE_FOLPPY_ERROR_UNKNOWN_CMOS_FORMAT "Unknown CMOS type: %d"
#define FDT_DEVICE_FOLPPY_ERROR_UNKNOWN_DRIVE_TYPE_FORMAT "Unknown drive type: %d"
#define FDT_DEVICE_FOLPPY_ERROR_INVALID_PARAMETORE_FORMAT "Invalid floppy parameters: %s"
#define FDT_DEVICE_FOLPPY_ERROR_UNKNOWN_DATA_TRANSFER_RATE_TYPE_FORMAT "Unknown data transfer rate type: %d"

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_DEV_ERROR_H_ */
