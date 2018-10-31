//=============================================================================
//
// �t�B�[���h���� [field.cpp]
//
//=============================================================================
#ifndef _UI_BONUS_H_
#define _UI_BONUS_H_

#include "Library/Math.h"
#include <Windows.h>


#define	TEX_BONUSGAGE	("data/TEXTURE/�{�[�i�X�Q�[�W��.png")
#define TEX_BONUSGAGEFRAME	("data/TEXTURE/�{�[�i�X�Q�[�W�g.png")
#define TEX_GAGEVOICETEN	("data/TEXTURE/�{�[�i�X�Q�[�W�p�{�C�X�e��.png")

#define BONUSGAGE_SIZE_X	(200)
#define BONUSGAGE_SIZE_Y	(28)

#define BONUSGAGE_POS_X		(25)
#define BONUSGAGE_POS_Y		(50)


#define FIRST_GAGE			(0.333f)
#define SECOND_GAGE			(0.666f)
#define LAST_GAGE			(1.0f)

#define POS_COR_ANG			((75.0f/180.0f)*PI)//���_1&2�̊p�x

#define VALUE_MAX			(1000)

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitUIBonus(void);
void UninitUIBonus(void);
void DrawUIBonus(void);
void UpdateUIBonus(void);

void AddGage(int no);
bool GetFiver(void);

#endif