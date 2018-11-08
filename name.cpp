//*****************************************************::
// name.cpp
// ����� ���邿�イ
//*******************************************************

//�R�{�S�����C���N���[�h
#include "name.h"
#include <stdio.h>

// ���C�u����
#include "Library/ObjectBase2D.h"
#include "Library/Common.h"
#include "Library/Input.h"
#include "Library/DebugProcess.h"


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

//*****************************************************************************
// ����[�΂�ւ񂷂�
//*****************************************************************************
int namechar;
int lastchar;		// ���[������Ă������łȂ񂾂����I
RANKDATA	rankdatawk[1];

C2DObject cursole;
C2DObject mojiban;
C2DObject moji[CHAR_MAX];

// �����̉摜�e�N�X�`��(�w�b�_�[�Ɉڂ��H�H�H�j
char *Moji_FileName[]=
{
	"data/TEXTURE/01.png",
};
//*************************************************************************
// void Initname(void)
// �������͂̏�����
//*************************************************************************
void InitName(void)
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
	// �摜�̏������H
	cursole.Init(CURSOLE_POS_X,CURSOLE_POS_Y,CURSOLE_WIDTH,CURSOLE_HEIGHT,CURSOLE_TEX);
	mojiban.Init(MOJIBAN_POS_X, MOJIBAN_POS_Y, MOJIBAN_WIDTH, MOJIBAN_HEIGHT, MOJIBAN_TEX);

	// �e�����������̏�����
	for (int i = 0; i < CHARS_MAX; i++)
	{
		moji[i].Init(CURSOLE_POS_X, CURSOLE_POS_Y, CURSOLE_WIDTH, CURSOLE_HEIGHT, Moji_FileName[i]);
	}
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
	cursole.Draw();
	mojiban.Draw();

	// �i�[���������o��
	for (int namechar = 0; namechar < NAMEMAX; namechar++)
	{
		// �����ʒu�̏�����
		//moji[i].Init()
		moji[rankdata[0].namechar[namechar]].Draw();
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

	int namechar = 0;	// ���݂̓��͕����̏�����
						// ����
	int playername = 0;

	//�@�������͏���
	while (1)
	{
		// ���݂̓��͕��������ő�łȂ���
		if (namechar < NAMEMAX)
		{
			rankdata[0].namechar[namechar] = get_char();
			// �󂯎�����l���������m�F
			if (rankdata[0].namechar[namechar <= EMPTY_NO])
			{
				namechar++;
			}
			else
			{
				switch (rankdata[0].namechar[namechar])
				{
				case NO_ENTRY:
					break;
				case BACK_CHAR:
					rankdata[0].namechar[namechar] = EMPTY_NO;
					namechar--;
					break;
				default:
					break;
				}

			}
		}
		else
		{
			int check = 0;
			// �߂�{�^���̂ݎ󂯕t��
			check = get_char();
			if (check == BACK_CHAR)
			{
				rankdata[0].namechar[namechar] = EMPTY_NO;
				namechar--;
			}
		}


	}



}

//******************************************************************************
// int get_char(void)
// �J�[�\���L�[�ŕ�����I��őI�񂾕������i�[������
// �҂̂�������
//***************************************************************:
int get_char(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	int tarinaimono = EMPTY_NO;	// �I�΂ꂽ����

	//�@�L�[���͂��󂯎���ăJ�[�\�����㉺�Ɉړ�

	while (1)		// ����L�[���o��܂Ŗ������[�v����
	{
		if (GetKeyboardPress(DIK_W))
		{// �����
			rankdata[0].cursole_Y++;
			// �`�F�b�N
			if (rankdata[0].cursole_Y > MOJI_Y_MAX)
			{
				rankdata[0].cursole_Y = 0;
			}
		}
		else if (GetKeyboardPress(DIK_S))
		{	// �����L�[�������ꂽ
			rankdata[0].cursole_Y--;
			// �`�F�b�N
			if (rankdata[0].cursole_Y < 0)
			{
				rankdata[0].cursole_Y = MOJI_Y_MAX;
			}
		}
		else if (GetKeyboardPress(DIK_D))
		{
			// �E�L�[
			rankdata[0].cursole_X++;
			// �`�F�b�N
			if (rankdata[0].cursole_X > MOJI_X_MAX)
			{
				rankdata[0].cursole_X = 0;
			}
		}
		else if (GetKeyboardPress(DIK_A))
		{
			// ���L�[
			rankdata[0].cursole_X--;
			// �`�F�b�N
			if (rankdata[0].cursole_X < 0)
			{
				rankdata[0].cursole_X = MOJI_X_MAX;
			}
		}



		// �������͏������I������
		if (GetKeyboardPress(DIK_SPACE))	// ����{�^���������ꂽ
		{
			tarinaimono = rankdata[0].cursole_X + (rankdata[0].cursole_Y * 10);
			// �������󔒂�����
			if (tarinaimono == SPACE_ENTRY)
			{
				tarinaimono = EMPTY_NO;
			}
			break;
		}

		// �o�b�N�X�y�[�X(�����Ղɂ��邩���j
		else if (GetKeyboardPress(DIK_BACKSPACE))
		{
			tarinaimono = BACK_CHAR;
			break;
		}
	}
	return tarinaimono;
	
}



