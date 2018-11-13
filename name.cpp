//*****************************************************::
// name.cpp
// ����� ���邿�イ
//*******************************************************

//�R�{�S�����C���N���[�h
#include "name.h"
#include <stdio.h>
#include "saveranking.h"
#include "score.h"
// ���C�u����
#include "Library/ObjectBase2D.h"
#include "Library/Common.h"
#include "Library/Input.h"
#include "Library/DebugProcess.h"


//*********************************************************
// Define
//*********************************************************

// ������
#define MOJI_Y_MAX		(5)		// 5�s�H
#define MOJI_X_MAX		(10)	// 10��H

// ���̐���
#define SPACE_ENTRY		(710)	// �X�y�[�X���͗p
#define EMPTY_NO		(99)	// �����͂�(�����l)

// ����
// 48+26
#define CHARS_MAX		(74)

// �Ƃ��ׂȂ�����
#define NO_ENTRY		(100)		// ���������͂���Ă��Ȃ�
#define BACK_CHAR		(101)		// �߂�{�^���������ꂽ

// �`�B�p
#define KEY_IRETEKUDASAI	(777)


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �����Ղ̕\���ʒu�����ɃJ�[�\���ʒu�����߂Ă��܂��B
// �J�[�\���̒l�͊�{�I�ɕύX���Ȃ��ł�������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �����΂�
#define MOJIBAN_TEX		("data/���/�����{�[�h.jpg")
#define MOJIBAN_WIDTH	(300.0)
#define MOJIBAN_HEIGHT	(300.0)
#define MOJIBAN_POS_X	(SCREEN_CENTER_X)						// CENTER_X�w��Ŏ����I�ɐ^�񒆂ɕ\�����Ă����(Draw?)
#define MOJIBAN_POS_Y	(SCREEN_CENTER_Y)
// �����Ղ̍ő�}�X��
#define MOJIBAN_MASUMAX_X	(9)
#define MOJIBAN_MASUMAX_Y	(9)

// �����΂�Q(�I�����ꂽ�������o���Ƃ��Ɏg����j
#define SENTAKUMOJI_TEX		("data/���/�����{�[�h.jpg")
#define SENTAKUMOJI_WIDTH	(70.0)
#define SENTAKUMOJI_HEIGHT	(70.0)
#define SENTAKUMOJI_POS_X	(100.0f)//(SCREEN_CENTER_X)						// CENTER_X�w��Ŏ����I�ɐ^�񒆂ɕ\�����Ă����(Draw?)
#define SENTAKUMOJI_POS_Y	(100.0f) //(SCREEN_CENTER_Y)




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �ȉ��̒l�͘M��Ȃ������c
#define CURSOLE_TEX		("data/�e�X�g�p�摜/�e�X�g�p�摜.png")
#define CURSOLE_SPACE	(2)					// ���̃}�X�Ɉړ����邽�߂ɃJ�[�\����X,Y�ɂ�����l
#define CURSOLE_WIDTH	(MOJIBAN_WIDTH/10)			// �����Ղ�10�����~10�����Ȃ̂�
#define CURSOLE_HEIGHT	(MOJIBAN_HEIGHT/10)
// �u���v�������ʒu��
#define CURSOLE_POS_X	(SCREEN_CENTER_X-CURSOLE_WIDTH - (CURSOLE_WIDTH*CURSOLE_SPACE*4))
#define CURSOLE_POS_Y	(SCREEN_CENTER_Y-CURSOLE_HEIGHT - (CURSOLE_WIDTH*CURSOLE_SPACE*4))





//*****************************************************************************
// ����[�΂�ւ񂷂�
//*****************************************************************************
int namechar;
int lastchar;		// ���[������Ă������łȂ񂾂����I
RANKDATA	rankdatawk[1];

C2DObject cursole;
C2DObject mojiban;
C2DObject moji[CHAR_MAX];
C2DObject select_moji[CHAR_MAX];		// �΂΁[��Ƃ����悤�̂��

// �����̉摜�e�N�X�`��(�����̉摜��1�����p�ӂ���ꍇ�A�g��Ȃ��Ȃ猈���Ă�k�j
char *Moji_FileName[]=
{
	"data/TEXTURE/01.png",
};
//*************************************************************************
// HRESULT Initname(void)
// �������͂̏�����
//*************************************************************************
HRESULT InitName(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	// ���O������
	for (int i = 0; i < NAMEMAX; i++)
	{
		rankdata[0].namechar[i] = EMPTY_NO;	// �S�Ă������l��
	}
	// �J�[�\���������ʒu��
	rankdata[0].cursole_X = 0;
	rankdata[0].cursole_Y = 0;
	namechar = 0;							// ���͍ϕ���
	// �摜�̏�����
	cursole.Init(CURSOLE_POS_X,CURSOLE_POS_Y,CURSOLE_WIDTH,CURSOLE_HEIGHT,CURSOLE_TEX);
	mojiban.Init(MOJIBAN_POS_X, MOJIBAN_POS_Y, MOJIBAN_WIDTH, MOJIBAN_HEIGHT, MOJIBAN_TEX);

	for (int i = 0; i < CHAR_MAX; i++)
	{
		//select_moji[i].Init(SENTAKUMOJI_POS_X, SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
	}
	return S_OK;
}

//**********************************************************
// �I������
//**********************************************************
void UninitName(void)
{
	// �e�摜���
	cursole.Release();
	mojiban.Release();
	//
	/*
	*/
}

	
//*************************************************************
// �`�揈��
//**************************************************************
void DrawName(void)
{
	RANKDATA *rankdata = &rankdatawk[0];

	mojiban.Draw();
	// �J�[�\�������o���̑O�ɏ�����
	cursole.Init(CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*rankdata[0].cursole_X), CURSOLE_POS_Y+((CURSOLE_HEIGHT*CURSOLE_SPACE)*rankdata[0].cursole_Y), CURSOLE_WIDTH, CURSOLE_HEIGHT, CURSOLE_TEX);
	cursole.Draw();
	//mojiban.Init(MOJIBAN_POS_X, MOJIBAN_POS_Y, MOJIBAN_WIDTH, MOJIBAN_HEIGHT, MOJIBAN_TEX);
	

	// �i�[���������o��
	for (int namechar = 0; namechar < NAMEMAX; namechar++)
	{

		// �e�N�X�`���̃Z�b�g
		//select_moji[namechar].Init(SENTAKUMOJI_POS_X + ((SENTAKUMOJI_WIDTH)*namechar), SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
		select_moji[namechar].SetTexture(rankdata[0].namechar[namechar], 10, 10);	//������ �܂��߂̐�X ��3 �܂��߂̐�Y
		select_moji[namechar].Draw();
	}
}


//*******************************************************:::

//**************************************************************************:
// void enter_name(void)
// �������͏���
// �W�����C�����l�ɑ���Ȃ����̂��ĉ���������
//***************************************************************************

/*
�������̗͂���
�\���L�[�ŃJ�[�\���̈ړ�
A�őI��B�Ŗ߂�
���炩�̃L�[�Ŗ��O�̊m��
���O��5�����Ƃ���
*/

void Update_Name(void)
{
	RANKDATA *rankdata = &rankdatawk[0];

	// �J�[�\���ړ�
	if (GetKeyboardTrigger(DIK_W))
	{
		rankdata[0].cursole_Y--;
		if (rankdata[0].cursole_Y < 0)
		{
			rankdata[0].cursole_Y = MOJIBAN_MASUMAX_Y;
		}
	}
	else if (GetKeyboardTrigger(DIK_S))
	{	// �����L�[�������ꂽ
		rankdata[0].cursole_Y++;
		// �`�F�b�N
		if (rankdata[0].cursole_Y > MOJIBAN_MASUMAX_Y)
		{
			rankdata[0].cursole_Y = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_D))
	{
		// �E�L�[
		rankdata[0].cursole_X++;
		// �`�F�b�N
		if (rankdata[0].cursole_X >MOJIBAN_MASUMAX_X)
		{
			rankdata[0].cursole_X = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_A))
	{
		// ���L�[
		rankdata[0].cursole_X--;
		// �`�F�b�N
		if (rankdata[0].cursole_X < 0)
		{
			rankdata[0].cursole_X = MOJIBAN_MASUMAX_X;
		}
	}

	// ����L�[�����͂��ꂽ�ꍇ���̃J�[�\���ʒu�̕������i�[
	if (GetKeyboardTrigger(DIK_SPACE))
	{	// �����ŕ������i�[
		rankdata[0].namechar[namechar] = rankdata[0].cursole_X + (rankdata[0].cursole_Y * 10);
		namechar++;
		// �e�N�X�`���̃Z�b�g
		select_moji[namechar].Init(SENTAKUMOJI_POS_X, SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
		select_moji[namechar].SetTexture(rankdata[0].namechar[namechar], 10, 10);	//������ �܂��߂̐�X ��3 �܂��߂̐�Y
		// �󔒕����̏ꍇ�̏���(�󔒕������͂ł��邩�킩��Ȃ��̂ŕۗ�)
	}

	// �������͂̏I��
	if (GetKeyboardTrigger(DIK_Z))
	{
		int player_score = GetScore();
		// �����܂��͂��炩�Ȃ�������
		long long name_number = (rankdata[0].namechar[4] * 100000000) + (rankdata[0].namechar[3] * 1000000) + (rankdata[0].namechar[2] * 10000) + (rankdata[0].namechar[1] * 100) + rankdata[0].namechar[0];
		SaveRanking(player_score,name_number);
	}

	// �폜�L�[�����͂��ꂽ�ꍇ1�����߂�
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{
		rankdata[0].namechar[namechar] = EMPTY_NO;
		namechar--;
	}
	// 00�����@01����
	//mojiban.SetTexture(1,10,10);
}


//***************************************************************************************
// void DrawChar(long long char)
// �摜�̈ꕔ����؂����ĕ\������
//***************************************************************************************