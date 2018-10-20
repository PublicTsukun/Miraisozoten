//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "Library/Math.h"
#include <Windows.h>

#define MAX_DIGIT		(3)

#define NUMBER_TEX		("data/TEXTURE/number16x32.png")

#define NUMBER_SIZE_X	(16)
#define NUMBER_SIZE_Y	(32)


//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitTimer(void);
void UninitTimer(void);
void DrawTimer(void);
void UpdateTimer(void);

#endif