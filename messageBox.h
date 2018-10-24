//=============================================================================
//
// message box処理 [messageBox.h]
// Author : 宋彦霖
//
//=============================================================================
#ifndef _MESSAGEBOX_INCLUDE_H_
#define _MESSAGEBOX_INCLUDE_H_

#include "Library/Vector.h"
#include <Windows.h>
#include <d3dx9.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESSAGEBOX_MAX (1)		// 最大数
#define MESSAGEBOX_EFX_MAX (1)	// 最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	bool use;		// 使用しているかどうか

	Vector2 pos;	// 位置

	float len;		// 長さ
	float wid;		// 寛さ

	bool efx;		

} MESSAGEBOX;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitMessageBox(void);
void UninitMessageBox(void);
void DrawMessagebox(void);
void UpdateMessageBox(void);

void SetMessageboxEfxOn(int no);
void SetMessageboxEfxOff(int no);

MESSAGEBOX *GetMessageBox(int no);
MESSAGEBOX *GetMessageBoxEfx(int no);


#endif