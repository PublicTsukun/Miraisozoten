//=============================================================================
//
// メイン処理 [main.h]
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_


//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <conio.h>

#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif




#endif