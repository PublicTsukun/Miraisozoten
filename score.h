//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "Library/Math.h"
#include "Library/Common.h"
#include <Windows.h>

#define SCORE_DIGIT		(5)

#define SCORE_TEX		("data/TEXTURE/number16x32.png")

#define SCORE_SIZE_X	(12)
#define SCORE_SIZE_Y	(24)

#define SCORE_POS_X	(SCREEN_WIDTH-SCORE_SIZE_X-25)
#define SCORE_POS_Y	(30)

//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitScore(void);
void UninitScore(void);
void DrawScore(void);
void UpdateScore(void);

void AddScore(int num);

#endif