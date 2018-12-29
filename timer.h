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

#define NUMBER_TEX		("data/TEXTURE/UI/�^�C�}�[����.png")

#define NUMBER_SIZE_X	(19.2*SCREEN_SCALE)
#define NUMBER_SIZE_Y	(38.4*SCREEN_SCALE)

#define NUMBER_POS_Y	(54*SCREEN_SCALE)

#define FRAME_TEX		("data/TEXTURE/UI/�^�C�}�[�E�X�R�A�p�g2_��.png")

#define START_TIME		(90)

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
int StateTimer(void);
int RestTimer(void);


#endif