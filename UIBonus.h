//=============================================================================
//
// �t�B�[���h���� [field.cpp]
//
//=============================================================================
#ifndef _UI_BONUS_H_
#define _UI_BONUS_H_

#include "Library/Math.h"
#include <Windows.h>


#define	TEX_BONUSGAGE	("data/TEXTURE/�����.png")
#define TEX_BONUSGAGEFRAME	("data/TEXTURE/�^�C�}�[�g(��).png")

#define BONUSGAGE_SIZE_X	(150)
#define BONUSGAGE_SIZE_Y	(40)

#define BONUSGAGE_POS_X		(50)
#define BONUSGAGE_POS_Y		(50)


#define FIRST_GAGE			(0.333f)
#define SECOND_GAGE			(0.666f)
#define LAST_GAGE			(1.0f)

#define POS_COR_ANG			((float)(45/180)*PI)


//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
HRESULT InitUIBonus(void);
void UninitUIBonus(void);
void DrawUIBonus(void);
void UpdateUIBonus(void);

#endif