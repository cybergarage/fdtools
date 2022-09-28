REM Copyright (C) 2020 Satoshi Konno. All rights reserved.
REM
REM Licensed under the Apache License, Version 2.0 (the "License");
REM you may not use this file except in compliance with the License.
REM You may obtain a copy of the License at
REM
REM    http://www.apache.org/licenses/LICENSE-2.0
REM
REM Unless required by applicable law or agreed to in writing, software
REM distributed under the License is distributed on an "AS IS" BASIS,
REM WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
REM See the License for the specific language governing permissions and
REM limitations under the License.

REM ---------------------------------------------------------------------------
REM -                   libhxcfe file type support list                       
REM ---------------------------------------------------------------------------
REM MODULE ID          ACCESS    DESCRIPTION                         Extension
REM
REM HXC_HFE;RW;SD Card HxCFE HFE file Loader;*.hfe;
REM MSX_DSK;R ;MSX DSK Loader;*.dsk;
REM NEC_D88;RW;NEC D88 Loader;*.d88;
REM RAW_IMG;R ;IBM PC IMG Loader;*.img;
REM RAW_LOADER;RW;RAW Sector loader;*.img;

REM ---------------------------------------------------------------------------
REM -                        File informations                                -
REM ---------------------------------------------------------------------------
REM File: 120m\x86BOOT.img
REM Checking 120m\x86BOOT.img
REM File loader found : RAW_IMG (IBM PC IMG Loader)
REM Loading 120m\x86BOOT.img
REM file loader found!
REM Image Size:1200kB, 80 tracks, 2 side(s), 15 sectors/track, interleave:1,rpm:360
REM track file successfully loaded and encoded!
REM 
REM File type : RAW_IMG - IBM PC IMG Loader
REM Floppy interface mode : IBMPC_HD_FLOPPYMODE - PC Interface (1.44MB/HD Disk)
REM Number of Track : 84
REM Number of Side : 2
REM Total Size : 1228800 Bytes, Number of sectors : 2400
REM
REM Input file : 120m\x86BOOT.img
REM Output file : 120m\x86BOOT.hfe
REM Checking 120m\x86BOOT.img
REM File loader found : RAW_IMG (IBM PC IMG Loader)
REM Loading 120m\x86BOOT.img
REM file loader found!
REM Image Size:1200kB, 80 tracks, 2 side(s), 15 sectors/track, interleave:1,rpm:360
REM track file successfully loaded and encoded!
REM Write HFE file 120m\x86BOOT.hfe for the standalone emulator.
REM Floppy interface mode IBMPC_HD_FLOPPYMODE (PC Interface (1.44MB/HD Disk))
REM 84 tracks written to the file

hxcfe.exe -conv:HXC_HFE -finput:120m\x86BOOT.img -foutput:120m\x86BOOT.hfe
hxcfe.exe -conv:NEC_D88 -finput:120m\x86BOOT.img -foutput:120m\x86BOOT.d88

REM ---------------------------------------------------------------------------
REM -                        File informations                                -
REM ---------------------------------------------------------------------------
REM File: 144m\x86BOOT.img
REM Checking 144m\x86BOOT.img
REM File loader found : RAW_IMG (IBM PC IMG Loader)
REM Loading 144m\x86BOOT.img
REM file loader found!
REM Image Size:1440kB, 80 tracks, 2 side(s), 18 sectors/track, interleave:1,rpm:300
REM track file successfully loaded and encoded!
REM 
REM File type : RAW_IMG - IBM PC IMG Loader
REM Floppy interface mode : IBMPC_HD_FLOPPYMODE - PC Interface (1.44MB/HD Disk)
REM Number of Track : 84
REM Number of Side : 2
REM Total Size : 1474560 Bytes, Number of sectors : 2880
REM 
REM Input file : 144m\x86BOOT.img
REM Output file : 144m\x86BOOT.hfe
REM Checking 144m\x86BOOT.img
REM File loader found : RAW_IMG (IBM PC IMG Loader)
REM Loading 144m\x86BOOT.img
REM file loader found!
REM Image Size:1440kB, 80 tracks, 2 side(s), 18 sectors/track, interleave:1,rpm:300
REM track file successfully loaded and encoded!
REM Write HFE file 144m\x86BOOT.hfe for the standalone emulator.
REM Floppy interface mode IBMPC_HD_FLOPPYMODE (PC Interface (1.44MB/HD Disk))
REM 84 tracks written to the file

hxcfe.exe -conv:HXC_HFE -finput:144m\x86BOOT.img -foutput:144m\x86BOOT.hfe
hxcfe.exe -conv:NEC_D88 -finput:144m\x86BOOT.img -foutput:144m\x86BOOT.d88

REM ---------------------------------------------------------------------------
REM -                        File informations                                -
REM ---------------------------------------------------------------------------
REM File: 720k\x86BOOT.img
REM Checking 720k\x86BOOT.img
REM File loader found : RAW_IMG (IBM PC IMG Loader)
REM Loading 720k\x86BOOT.img
REM file loader found!
REM Image Size:720kB, 80 tracks, 2 side(s), 9 sectors/track, interleave:1,rpm:300
REM track file successfully loaded and encoded!
REM 
REM File type : RAW_IMG - IBM PC IMG Loader
REM Floppy interface mode : IBMPC_DD_FLOPPYMODE - PC Interface (720KB/DD Disk)
REM Number of Track : 84
REM Number of Side : 2
REM Total Size : 737280 Bytes, Number of sectors : 1440
REM 
REM Input file : 720k\x86BOOT.img
REM Output file : 720k\x86BOOT.hfe
REM Checking 720k\x86BOOT.img
REM File loader found : RAW_IMG (IBM PC IMG Loader)
REM Loading 720k\x86BOOT.img
REM file loader found!
REM Image Size:720kB, 80 tracks, 2 side(s), 9 sectors/track, interleave:1,rpm:300
REM track file successfully loaded and encoded!
REM Write HFE file 720k\x86BOOT.hfe for the standalone emulator.
REM Floppy interface mode IBMPC_DD_FLOPPYMODE (PC Interface (720KB/DD Disk))
REM 84 tracks written to the file

hxcfe.exe -conv:HXC_HFE -finput:720k\x86BOOT.img -foutput:720k\x86BOOT.hfe
hxcfe.exe -conv:NEC_D88 -finput:720k\x86BOOT.img -foutput:720k\x86BOOT.d88
