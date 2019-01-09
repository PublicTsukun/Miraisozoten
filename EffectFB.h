//=============================================================================
//
// 撃破エフェクト[EffectFB.h]
// Author : 宋彦霖
//
//=============================================================================
#ifndef _EFFECTFB_INCLUDE_H_
#define _EFFECTFB_INCLUDE_H_

#include "Library/Vector.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEffectFB(void);
void UninitEffectFB(void);
void UpdateEffectFB(void);
void DrawEffectFB(void);

void CallEffectFB(Vector3 pos);

#endif