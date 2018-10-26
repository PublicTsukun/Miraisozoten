//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#ifndef _UI_BONUS_H_
#define _UI_BONUS_H_

#include "Library/Math.h"
#include <Windows.h>


#define	TEX_BONUSGAGE	("data/TEXTURE/左矢印.png")
#define TEX_BONUSGAGEFRAME	("data/TEXTURE/タイマー枠(仮).png")

#define BONUSGAGE_SIZE_X	(150)
#define BONUSGAGE_SIZE_Y	(40)

#define BONUSGAGE_POS_X		(50)
#define BONUSGAGE_POS_Y		(50)


#define FIRST_GAGE			(0.333f)
#define SECOND_GAGE			(0.666f)
#define LAST_GAGE			(1.0f)

#define POS_COR_ANG			((float)(45/180)*PI)


//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitUIBonus(void);
void UninitUIBonus(void);
void DrawUIBonus(void);
void UpdateUIBonus(void);

#endif