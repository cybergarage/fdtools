# fdtools

![GitHub tag (latest SemVer)](https://img.shields.io/github/v/tag/cybergarage/fdtools)
[![test](https://github.com/cybergarage/fdtools/actions/workflows/make.yml/badge.svg)](https://github.com/cybergarage/fdtools/actions/workflows/make.yml)
[![doxygen](https://github.com/cybergarage/fdtools/actions/workflows/doxygen.yml/badge.svg)](https://cybergarage.github.io/fdtools/)

The fdtools is a multi-platform framework for easy development of floppy disk utilities. The fdtools abstracts floppy disk layers such as the floppy disk image layer and disk format layer.

![](doc/img/framework.png)

The package includes the following commands:

- [fdcopy](doc/ffdump.md): dumps an image from floppy disk drives or image files, and copies the images to other target devices or files. It supports to dump a file image to other images, and so you can use the utility as a floppy image converters too.

- [fdinfo](doc/fdinfo.md): shows the current floppy disk paramters or floppy disk image infomation.

Note these utilities access read floppy drives directly, and so these might not work for USB floppy drives when you specify the physical floppy drive options.

<!--
## Installation

Fdtools is distributed as a Snap package in the Snap Store, and so you can install it by running:

```
sudo snap install fdtools
```
-->
