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
#define	TEXTURE_RESULTBG		"data/TEXTURE/UI/���U���g/�肴��Ɣw�i.png"// �ǂݍ��ރe�N�X�`���̃t�@�C����

#define TEXTURE_RESULT_LOGO		"data/TEXTURE/UI/���U���g/�肴���.png"
#define RESULT_LOGO_SIZE_X		(260*SCREEN_SCALE)
#define	RESULT_LOGO_SIZE_Y		(65*SCREEN_SCALE)


#define	TEXTURE_SCORE		"data/TEXTURE/UI/�X�R�A����.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_SCORE_SIZE_X		(46.0f*SCREEN_SCALE)							// �X�R�A�̐����̕�
#define	RESULT_SCORE_SIZE_Y		(70.0f*SCREEN_SCALE)						// �X�R�A�̐����̍���
#define	RESULT_SCORE_INTERVAL_X	(0.0f)							// �X�R�A�̐����̕\���Ԋu

#define	NUM_PLACE			(5)							// �X�R�A�̌��� stage.h��MAX_PRICE�ƌ������킹�邱��

#define	RESULT_SCORE_POS_X			(SCREEN_CENTER_X-RESULT_SCORE_SIZE_X*4)						// �X�R�A�̕\����ʒu�w���W
#define	RESULT_SCORE_POS_Y			(SCREEN_HEIGHT-RESULT_SCORE_SIZE_Y-8.0f*SCREEN_SCALE)				// �X�R�A�̕\����ʒu�x���W

#define SLOT_INTERVAL		(30)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResultlogo(void);
void UninitResultlogo(void);
void UpdateResultlogo(void);
void DrawResultlogo(void);


#endif
