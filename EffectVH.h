//=============================================================================
//
// 命中エフェクト[EffectVH.h]
// Author : 宋彦霖
//
//=============================================================================
#ifndef _EFFECTVH_INCLUDE_H_
#define _EFFECTVH_INCLUDE_H_

#include "Library/Vector.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEffectVH(void);
void UninitEffectVH(void);
void UpdateEffectVH(void);
void DrawEffectVH(void);

void CallEffectVH(Vector3 pos);

#endif