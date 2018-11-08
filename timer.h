//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "Library/Math.h"
#include "Library\Common.h"
#include <Windows.h>

#define MAX_DIGIT		(2)

#define NUMBER_TEX		("data/TEXTURE/タイマー数字.png")

#define NUMBER_SIZE_X	(16*SCREEN_SCALE)
#define NUMBER_SIZE_Y	(32*SCREEN_SCALE)

#define NUMBER_POS_Y	(45*SCREEN_SCALE)

#define FRAME_TEX		("data/TEXTURE/タイマー枠(仮).png")

#define START_TIME		(99)

enum
{
	STOP,
	RESET,
	COUNT,
};
//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitTimer(void);
void UninitTimer(void);
void DrawTimer(void);
void UpdateTimer(void);

void TimerSet(int no);

#endif