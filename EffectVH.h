//=============================================================================
//
// �����G�t�F�N�g[EffectVH.h]
// Author : �v�F��
//
//=============================================================================
#ifndef _EFFECTVH_INCLUDE_H_
#define _EFFECTVH_INCLUDE_H_

#include "Library/Vector.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEffectVH(void);
void UninitEffectVH(void);
void UpdateEffectVH(void);
void DrawEffectVH(void);

void CallEffectVH(Vector3 pos);

#endif