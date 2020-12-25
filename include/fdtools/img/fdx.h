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

#ifndef _FDTOOLS_IMG_FDX_H_
#define _FDTOOLS_IMG_FDX_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FDX_IMAGE_HEADER_SIGNATURE "FDX"

typedef struct {
  BYTE signature[3]; // 識別子('F','D','X')
  BYTE revision; // リビジョン(3)
  BYTE name[60]; // ディスク名
  BYTE pad[4]; // パディング
  int type; // タイプ(0:2D 1:2DD 2:2HD 9:RAW)
  int cylinders; // シリンダー数
  int heads; // ヘッド数
  int rate; // 転送レート(クロック込み)[500|1000]
  int rpm; // RPM[300|360]
  BOOL writeprotect; // ライトプロテクト(0: OFF 1:ON)
  DWORD option; // 動作オプション
  DWORD unused; // 未使用
  int tracksiz; // トラックデータのブロック長
  BYTE reserve[152]; // リザーブ(ヘッダー全体256バイトに調整)
} FDX_HEADER;

typedef struct {
  int cylinder; // シリンダー
  int head; // ヘッド
  int index; // インデックスホール位置(ビット数)
  int length; // トラックデータ長(ビット数)
  BYTE data[???];		// データバッファ(可変長)
} FDX_TRACK;

#ifdef __cplusplus
} /* extern C */
#endif

#endif /* _FDTOOLS_IMG_FDX_H_ */
