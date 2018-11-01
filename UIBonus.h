//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#ifndef _UI_BONUS_H_
#define _UI_BONUS_H_

#include "Library/Math.h"
#include <Windows.h>


#define	TEX_BONUSGAGE	("data/TEXTURE/ボーナスゲージ中.png")
#define TEX_BONUSGAGEFRAME	("data/TEXTURE/ボーナスゲージ枠.png")
#define TEX_GAGEVOICETEN	("data/TEXTURE/ボーナスゲージ用ボイステン.png")
#define TEX_GAGEEFF			("data/TEXTURE/ボーナスゲージ外枠.png")

#define BONUSGAGE_SIZE_X	(200)
#define BONUSGAGE_SIZE_Y	(28)

#define BONUSGAGE_POS_X		(25)
#define BONUSGAGE_POS_Y		(50)


#define FIRST_GAGE			(0.333f)
#define SECOND_GAGE			(0.666f)
#define LAST_GAGE			(1.0f)

#define POS_COR_ANG			((75.0f/180.0f)*PI)//頂点1&2の角度

#define VALUE_MAX			(1000)

#define GAGE_EFF_COR		(27.0f)
#define GAGE_EFF_SIZE_X		(222)
#define GAGE_EFF_SIZE_Y		(45)
#define GAGE_EFF_POS_X		(BONUSGAGE_POS_X+GAGE_EFF_SIZE_X-GAGE_EFF_COR)
#define GAGE_EFF_POS_Y		(BONUSGAGE_POS_Y)
//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitUIBonus(void);
void UninitUIBonus(void);
void DrawUIBonus(void);
void UpdateUIBonus(void);

void AddGage(int no);
bool GetFiver(void);

#endif