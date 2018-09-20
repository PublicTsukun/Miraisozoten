//=============================================================================
//
// デバッグ表示処理 [DebugProcess.h]
//
//=============================================================================
#ifndef __DEBUGPROCESS_INCLUDE_H__
#define __DEBUGPROCESS_INCLUDE_H__


#define _CRT_SECURE_NO_WARNINGS		// warning防止


#include <Windows.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitDebugProcess(void);
void UninitDebugProcess(void);
void UpdateDebugProcess(void);
void DrawDebugProcess(void);

void PrintDebugProcess(const char *fmt,...);


#endif