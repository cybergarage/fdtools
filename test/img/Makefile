# Copyright (C) 2020 Satoshi Konno. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

SHELL := bash

all: raw

raw: 120m/x86BOOT.img 144m/x86BOOT.img
120m/x86BOOT.img: freedos
144m/x86BOOT.img: freedos

fdx: 120m/x86BOOT.fdx 144m/x86BOOT.fdx 720k/x86BOOT.fdx
120m/x86BOOT.fdx: 120m/x86BOOT.hfe
        ./fdxconv -i $< -o $@
144m/x86BOOT.fdx: 144m/x86BOOT.hfe
        ./fdxconv -i $< -o $@
720k/x86BOOT.fdx: 720k/x86BOOT.hfe
        ./fdxconv -i $< -o $@

freedos:
	@wget -c https://www.ibiblio.org/pub/micro/pc-stuff/freedos/files/distributions/1.3/official/FD13-FloppyEdition.zip
	unzip -o FD13-FloppyEdition.zip

samdisk: samdisk
	@wget -c https://simonowen.com/samdisk/samdisk-388-osx.zip
	unzip -o samdisk-388-osx.zip
