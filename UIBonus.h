//=============================================================================
//
// �t�B�[���h���� [field.cpp]
//
//=============================================================================
#ifndef _UI_BONUS_H_
#define _UI_BONUS_H_

#include "Library/Math.h"
#include <Windows.h>


#define	TEX_BONUSGAGE		("data/TEXTURE/UI/�Q�[�W/�{�[�i�X�Q�[�W��.png")
#define TEX_BONUSGAGEFRAME	("data/TEXTURE/UI/�Q�[�W/�{�[�i�X�Q�[�W�g.png")
#define TEX_GAGEVOICETEN	("data/TEXTURE/UI/�Q�[�W/�{�[�i�X�Q�[�W�p�{�C�X�e��.png")
#define TEX_GAGEEFF			("data/TEXTURE/UI/�Q�[�W/�{�[�i�X�Q�[�W�O�g.png")

#define BONUSGAGE_SIZE_X	(200*SCREEN_SCALE)
#define BONUSGAGE_SIZE_Y	(28*SCREEN_SCALE)

#define BONUSGAGE_POS_X		(25*SCREEN_SCALE)
#define BONUSGAGE_POS_Y		(50*SCREEN_SCALE)


#define FIRST_GAGE			(0.333f)
#define SECOND_GAGE			(0.666f)
#define LAST_GAGE			(1.0f)

#define POS_COR_ANG			((75.0f/180.0f)*PI)//���_1&2�̊p�x

#define VALUE_MAX			(3000)

#define GAGE_EFF_COR		(27.0f*SCREEN_SCALE)
#define GAGE_EFF_SIZE_X		(222*SCREEN_SCALE)
#define GAGE_EFF_SIZE_Y		(45*SCREEN_SCALE)
#define GAGE_EFF_POS_X		(BONUSGAGE_POS_X+GAGE_EFF_SIZE_X-GAGE_EFF_COR)
#define GAGE_EFF_POS_Y		(BONUSGAGE_POS_Y)
//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitUIBonus(void);
void UninitUIBonus(void);
void DrawUIBonus(void);
void UpdateUIBonus(void);

void AddGage(int no);
bool GetFiver(void);

int GetGauge(void);

#endif