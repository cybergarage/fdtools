// Copyright (C) 2020 Satoshi Konno. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use t file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#if defined(__linux__)

#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>

#include <fdtools/dev/error.h>
#include <fdtools/dev/floppy.h>
#include <fdtools/util/log.h>

bool fdt_floppy_struct_equals(struct floppy_struct* t, struct floppy_struct* o)
{
  if (t->size != o->size)
    return false;
  if (t->size != o->sect)
    return false;
  if (t->head != o->head)
    return false;
  if (t->track != o->track)
    return false;
  if (t->stretch != o->stretch)
    return false;
  if (t->gap != o->gap)
    return false;
  if (t->spec1 != o->spec1)
    return false;
  if (t->fmt_gap != o->fmt_gap)
    return false;

  return true;
}

bool fdt_floppy_struct_setfloppyparams(floppy_struct* fdparams, FdtFloppyParams* params, FdtError* err)
{
  if (!params->track || !params->head || !params->sect) {
    fdt_error_setmessage(err, FDT_DEVICE_FOLPPY_ERROR_INVALID_PARAMETORE_FORMAT, fdt_floppy_params_getdescription(params));
    return false;
  }

  fdparams->track = fdt_floppy_params_gettrack(params);
  fdparams->head = fdt_floppy_params_gethead(params);
  fdparams->sect = fdt_floppy_params_getsect(params);
  fdparams->size = fdt_floppy_params_getsize(params);

  if (fdparams->size <= 0) {
    fdt_error_setmessage(err, FDT_DEVICE_FOLPPY_ERROR_INVALID_PARAMETORE_FORMAT, fdt_floppy_params_getdescription(params));
    return false;
  }

  fdparams->stretch = fdt_floppy_params_getstretch(params);
  fdparams->gap = fdt_floppy_params_getgap1size(params);
  /*
        fdparams->rate =
  */
  fdparams->spec1 = 0;
  fdparams->fmt_gap = fdt_floppy_params_getgap2size(params);

  return true;
}

bool fdt_floppy_params_setstat(FdtFloppyParams* params, struct stat* stat, FdtError* err)
{
  if (!S_ISBLK(stat->st_mode) || major(stat->st_rdev) != FLOPPY_MAJOR) {
    fdt_error_setlasterror(err, "Not floppy device");
    return false;
  }

  int drive_no = minor(stat->st_rdev);
  drive_no = (drive_no & 3) + ((drive_no & 0x80) >> 5);

  fdt_floppy_params_setdeviceno(params, drive_no);

  fdt_log_info("stat major = %d, minor = %d, dn = %d", major(stat->st_rdev), minor(stat->st_rdev), drive_no);

  return true;
}

bool fdt_floppy_params_setfloppydriveparams(FdtFloppyParams* params, floppy_drive_params* fddprms, FdtError* err)
{
  if (!params || !fddprms)
    return false;

  int cmos = fddprms->cmos;
  switch (cmos) {
  case 1: // 5 1/4 DD
    fdt_floppy_params_setdrivetype(params, FDT_FLOPPY_DRIVE_525_DD, err);
    break;
  case 2: // 3 1/2 DD
    fdt_floppy_params_setdrivetype(params, FDT_FLOPPY_DRIVE_35_DD, err);
    break;
  case 3: // 5 1/4 HD
    fdt_floppy_params_setdrivetype(params, FDT_FLOPPY_DRIVE_525_HD, err);
    break;
  case 4: // 3 1/2 HD
    fdt_floppy_params_setdrivetype(params, FDT_FLOPPY_DRIVE_35_HD, err);
    break;
  case 5: // 3 1/2 ED
  case 6: // 3 1/2 ED
    fdt_floppy_params_setdrivetype(params, FDT_FLOPPY_DRIVE_35_ED, err);
    break;
  default:
    fdt_error_setmessage(err, FDT_DEVICE_FOLPPY_ERROR_UNKNOWN_CMOS_FORMAT, cmos);
    return false;
  }

  return true;
}

bool fdt_floppy_params_setfloppystruct(FdtFloppyParams* params, floppy_struct* fdprms, FdtError* err)
{
  if (!params || !fdprms)
    return false;

  fdt_floppy_params_setsect(params, fdprms->sect);
  fdt_floppy_params_sethead(params, fdprms->head);
  fdt_floppy_params_settrack(params, fdprms->track);
  fdt_floppy_params_setstretch(params, fdprms->stretch);
  fdt_floppy_params_setgap1size(params, fdprms->gap);
  fdt_floppy_params_setrate(params, fdprms->rate);
  fdt_floppy_params_setspec1(params, fdprms->spec1);
  fdt_floppy_params_setgap2size(params, fdprms->fmt_gap);

  return true;
}

bool fdt_floppy_rawcmd_readid(int fd, int drive, int rate, int track, floppy_raw_cmd* raw_cmd)
{
  raw_cmd->cmd_count = 2;
  raw_cmd->cmd[0] = FD_READID; /* format command */
  raw_cmd->cmd[1] = drive /* drive */;
  raw_cmd->flags = FD_RAW_INTR | FD_RAW_NEED_SEEK;
  raw_cmd->rate = rate;
  raw_cmd->track = track;

  int ret = ioctl(fd, FDRAWCMD, raw_cmd);

  fdt_log_info("readid(%d) dn = %d, rate = %d, track = %d", ret, drive, rate, track);

  return (ret == 0) ? true : false;
}

void fdt_floppy_rawcmd_print(floppy_raw_cmd* raw_cmd)
{
  int reply_cound = (int)raw_cmd->reply_count;
  printf("[%d] ", reply_cound);
  for (int n = 0; n < reply_cound; n++) {
    printf("%d ", raw_cmd->reply[n]);
  }
  printf("\n");
}

#endif /* __linux__ */
