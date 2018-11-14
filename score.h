//=============================================================================
//
// �t�B�[���h���� [field.cpp]
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "Library/Math.h"
#include "Library/Common.h"
#include <Windows.h>

#define SCORE_DIGIT		(5)

#define SCORE_TEX		("data/TEXTURE/�X�R�A����.png")

#define SCORE_SIZE_X	(12*SCREEN_SCALE)
#define SCORE_SIZE_Y	(24*SCREEN_SCALE)

#define SCORE_POS_X	(SCREEN_WIDTH-SCORE_SIZE_X-25*SCREEN_SCALE)
#define SCORE_POS_Y	(30*SCREEN_SCALE)

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitScore(void);
void UninitScore(void);
void DrawScore(void);
void UpdateScore(void);

void AddScore(int num);
int GetScore(void);


#endif