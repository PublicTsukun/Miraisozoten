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
#define RESULT_LOGO_COLOR		(0xff112233)	//�u�肴��Ɓv�̕����F�ς���̂�������`
												//0x�͌Œ�@ff(�ŏ��̂Q��)�����l
												//			11(���̂Q��)��R
												//			22(���̂Q��)��G
												//			33(�Ō�̂Q��)��B
												//�l�b�g�Œ��ׂ��炢�������ɏo�Ă���Ǝv��
												//�P�U�i���Q���ł��ꂼ��̐F�����߂Ă�

#define	TEXTURE_SCORE		"data/TEXTURE/UI/�X�R�A����.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	RESULT_SCORE_SIZE_X		(46.0f*SCREEN_SCALE)							// �X�R�A�̐����̕�
#define	RESULT_SCORE_SIZE_Y		(70.0f*SCREEN_SCALE)						// �X�R�A�̐����̍���
//#define		RESULT_SCORE_SIZE_X		(92.0f*SCREEN_SCALE)
//#define		RESULT_SCORE_SIZE_Y		(140.0f*SCREEN_SCALE)

#define	RESULT_SCORE_INTERVAL_X	(0.0f)							// �X�R�A�̐����̕\���Ԋu

#define	NUM_PLACE			(5)							// �X�R�A�̌��� stage.h��MAX_PRICE�ƌ������킹�邱��

#define	RESULT_SCORE_POS_X			(SCREEN_CENTER_X-RESULT_SCORE_SIZE_X*4)						// �X�R�A�̕\����ʒu�w���W
#define	RESULT_SCORE_POS_Y			(SCREEN_HEIGHT-RESULT_SCORE_SIZE_Y-8.0f*SCREEN_SCALE)				// �X�R�A�̕\����ʒu�x���W
//#define RESULT_SCORE_POS_Y			(SCREEN_CENTER_Y)

#define SLOT_INTERVAL		(30)

#define DETAIL_MAX			(9)

#define	CLOSS_POS_X			(0.0f)	//�~�p�|�W�V�����@�w�i�Ƃ̑��΍��W
#define	CLOSS_POS_Y			(0.0f)

#define	EQUAL_POS_X			(0.0f)	//���p�|�W�V�����@�w�i�Ƃ̑��΍��W
#define	EQUAL_POS_Y			(0.0f)

#define CHAR_POS_X			(-320.0f)
#define CHAR_POS_Y			(-10.0f)

#define KNOCK_POS_X			(-147.0f)
#define KNOCK_POS_Y			(0.0f)
#define KNOCK_INTER			(73.0f)

#define GETPOINT_POS_X		(70.0f)
#define GETPOINT_POS_Y		(0.0f)
#define GETPOINT_INTER		(65.0f)


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResultlogo(void);
void UninitResultlogo(void);
void UpdateResultlogo(void);
void DrawResultlogo(void);


#endif
