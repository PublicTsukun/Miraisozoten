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

#define SCORE_TEX		("data/TEXTURE/UI/�X�R�A����.png")

#define SCORE_SIZE_X	(12*SCREEN_SCALE)
#define SCORE_SIZE_Y	(24*SCREEN_SCALE)

#define SCORE_POS_X	(SCREEN_WIDTH-SCORE_SIZE_X-50*SCREEN_SCALE)
#define SCORE_POS_Y	(40*SCREEN_SCALE)


#define SCORE_FRAME_TEX	("data/TEXTURE/UI/�^�C�}�[�E�X�R�A�p�g_��.png")
#define SCORE_FRAME_POS	(SCORE_POS_X-SCORE_SIZE_X*4)

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