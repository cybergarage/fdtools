# Fdtools

Fdtools is a utility package for floppy disk drives and images on multi-platform. The package includes the following commands:

- fddump: dumps an image from floppy disk drives or image files, and copies the images to other target devices or files. It supports to dump a file image to other images, and so you can use the utility as a floppy image converters too.

- fdinfo: shows the current floppy disk paramters or floppy disk image infomation.

Note these utilities access read floppy drives directly, and so these might not work for USB floppy drives when you specify the physical floppy drive options.

## Installation

Fdtools is distributed as a Snap package in the Snap Store, and so you can install it by running:

```
sudo snap install fdtools
```
