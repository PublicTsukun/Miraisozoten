//=============================================================================
//
// ���j�G�t�F�N�g[EffectFB.h]
// Author : �v�F��
//
//=============================================================================
#ifndef _EFFECTFB_INCLUDE_H_
#define _EFFECTFB_INCLUDE_H_

#include "Library/Vector.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEffectFB(void);
void UninitEffectFB(void);
void UpdateEffectFB(void);
void DrawEffectFB(void);

void CallEffectFB(Vector3 pos);

#endif