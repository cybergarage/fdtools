# D88 Image Format

```
D88_image :
  D88_Header 
  D88_Track 

```
## D88_Header

The D88 header is static size.

|  Offset  |  Size  | Description |　Notes |
| ---- | ---- | ---- | ---- |
|  0x0000  |  17  | Disk name | 
|  TD  |  TD  | Reserved　| 
|  TD  |  TD  | Write Protect　|  0x00: Disabled, 0x10 Enabled |
|  TD  |  TD  | Write Protect　|  0x00: 2D, 0x10: 2DD, 0x20: 2HD |
|  TD  |  TD  | Disk Size　|  0x02B0 + 0x00: 2D, 0x10: 2DD, 0x20: 2HD |
|  TD  |  4 * 164  | Offset Table　|  From 0 +  or Zero |

## D88_Track

track


|  Offset  |  TH  |
| ---- | ---- |
|  TD  |  TD  |
|  TD  |  TD  |

### DITT

D88 might have extra sector data, 16 + 18

DITT   ,,,, cylinder, head 0 or 1

## References

- [D88形式フォーマット | HuDisk](https://boukichi.github.io/HuDisk/DISK.html)
- [wii88/FORMAT.TXT](https://github.com/jpzm/wii88/blob/master/document/FORMAT.TXT)
- [.D88形式のフロッピーディスクイメージフォーマット - （仮）](http://gra4.hatenadiary.jp/entry/20171108/1510096429)
- [D88形式フォーマット](https://github.com/BouKiCHi/HuDisk/blob/master/docs/DISK.md)