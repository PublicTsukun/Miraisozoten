//=============================================================================
//
// �X�R�A���� [score.h]
// Author : 
//
//=============================================================================
#ifndef _RESULT_LOGO_H_
#define _RESULT_LOGO_H_


#include <Windows.h>
#include "Library/Common.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/�X�R�A����.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_SCORE_SIZE_X		(50.0f*SCREEN_SCALE)							// �X�R�A�̐����̕�
#define	RESULT_SCORE_SIZE_Y		(75.0f*SCREEN_SCALE)						// �X�R�A�̐����̍���
#define	RESULT_SCORE_INTERVAL_X	(0.0f)							// �X�R�A�̐����̕\���Ԋu

#define	NUM_PLACE			(5)							// �X�R�A�̌��� stage.h��MAX_PRICE�ƌ������킹�邱��

#define	RESULT_SCORE_POS_X			(SCREEN_CENTER_X-RESULT_SCORE_SIZE_X*NUM_PLACE)						// �X�R�A�̕\����ʒu�w���W
#define	RESULT_SCORE_POS_Y			(RESULT_SCORE_SIZE_Y+(5.0f+RESULT_LOGO_SIZE_Y*2)*SCREEN_SCALE)				// �X�R�A�̕\����ʒu�x���W

#define SLOT_INTERVAL		(30)


#define	TEXTURE_RESULTBG		"data/TEXTURE/sgf01a201501112200.jpg"// �ǂݍ��ރe�N�X�`���̃t�@�C����

#define TEXTURE_RESULT_LOGO		"data/TEXTURE/ranking.jpg"
#define RESULT_LOGO_SIZE_X		(RelativeSX(0.75f)/2)
#define	RESULT_LOGO_SIZE_Y		(75.0f*SCREEN_SCALE)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResultlogo(void);
void UninitResultlogo(void);
void UpdateResultlogo(void);
void DrawResultlogo(void);


#endif
