//=============================================================================
//
// �t�B�[���h���� [field.cpp]
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "Library/Math.h"
#include <Windows.h>

#define MAX_DIGIT		(2)

#define NUMBER_TEX		("data/TEXTURE/�^�C�}�[����.png")

#define NUMBER_SIZE_X	(16)
#define NUMBER_SIZE_Y	(32)

#define NUMBER_POS_Y	(45)

#define FRAME_TEX		("data/TEXTURE/�^�C�}�[�g(��).png")
//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitTimer(void);
void UninitTimer(void);
void DrawTimer(void);
void UpdateTimer(void);

#endif