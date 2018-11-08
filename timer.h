//=============================================================================
//
// �t�B�[���h���� [field.cpp]
//
//=============================================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include "Library/Math.h"
#include "Library\Common.h"
#include <Windows.h>

#define MAX_DIGIT		(2)

#define NUMBER_TEX		("data/TEXTURE/�^�C�}�[����.png")

#define NUMBER_SIZE_X	(16*SCREEN_SCALE)
#define NUMBER_SIZE_Y	(32*SCREEN_SCALE)

#define NUMBER_POS_Y	(45*SCREEN_SCALE)

#define FRAME_TEX		("data/TEXTURE/�^�C�}�[�g(��).png")

#define START_TIME		(99)

enum
{
	STOP,
	RESET,
	COUNT,
};
//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitTimer(void);
void UninitTimer(void);
void DrawTimer(void);
void UpdateTimer(void);

void TimerSet(int no);

#endif