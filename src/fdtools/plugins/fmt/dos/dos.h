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

#ifndef _FDTOOLS_DOS_FORMAT_H_
#define _FDTOOLS_DOS_FORMAT_H_

#include <fdtools/fmt/format.h>
#include <fdtools/plugins/fmt/dos/bpb.h>

#ifdef __cplusplus
extern "C" {
#endif

FdtFormat* fdt_dos_new(void);

const char* fdt_dos_gettypeid(FdtFormat*);
bool fdt_dos_format(FdtFormat*, FdtError*);
bool fdt_dos_list(FdtFormat*, FdtFiles*, FdtError*);
bool fdt_dos_add(FdtFormat*, FdtFile*, FdtError*);
bool fdt_dos_del(FdtFormat*, FdtFile*, FdtError*);

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_DOS_FORMAT_H_ */
