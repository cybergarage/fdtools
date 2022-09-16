###################################################################
#
# uecho-go
#
# Copyright (C) Satoshi Konno 2017
#
# This is licensed under BSD-style license, see file COPYING.
#
###################################################################

SHELL := bash

.PHONY: raw

all: raw

raw: 120m/x86BOOT.img 144m/x86BOOT.img
120m/x86BOOT.img: freedos
144m/x86BOOT.img: freedos

freedos: 120m/x86BOOT.img 144m/x86BOOT.img
	@wget -c https://www.ibiblio.org/pub/micro/pc-stuff/freedos/files/distributions/1.3/official/FD13-FloppyEdition.zip
	unzip -o FD13-FloppyEdition.zip
