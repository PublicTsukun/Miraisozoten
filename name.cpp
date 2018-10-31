//*****************************************************::
// name.cpp
// ����� ���邿�イ
//*******************************************************

//�R�{�S�����C���N���[�h
#include "name.h"
#include <stdio.h>


// ������
#define MOJI_Y_MAX		(5)		// 5�s�H
#define MOJI_X_MAX		(10)	// 10��H

#define EMPTY_NO		(99)	// �����͂�(�����l)

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
}

//**********************************************************


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
		if (tarinaimono = KEY_IRETEKUDASAI)
		{// �����
			rankdata[0].cursole_Y++;
			// �`�F�b�N
			if (rankdata[0].cursole_Y > MOJI_Y_MAX)
			{
				rankdata[0].cursole_Y = 0;
			}
		}
		else if (tarinaimono = KEY_IRETEKUDASAI)
		{	// �����L�[�������ꂽ
			rankdata[0].cursole_Y++;
			// �`�F�b�N
			if (rankdata[0].cursole_Y < 0)
			{
				rankdata[0].cursole_Y = MOJI_Y_MAX;
			}
		}
		else if (tarinaimono = KEY_IRETEKUDASAI)
		{
			// �E�L�[
			rankdata[0].cursole_X++;
			// �`�F�b�N
			if (rankdata[0].cursole_X > MOJI_X_MAX)
			{
				rankdata[0].cursole_X = 0;
			}
		}
		else if (tarinaimono = KEY_IRETEKUDASAI)
		{
			// ���L�[
			rankdata[0].cursole_X--;
			// �`�F�b�N
			if (rankdata[0].cursole_X < 0)
			{
				rankdata[0].cursole_X = MOJI_X_MAX;
			}
		}



		// �J�[�\���`�F�b�N
		if(tarinaimono = KEY_IRETEKUDASAI)

		if (tarinaimono = KEY_IRETEKUDASAI)	// ����{�^���������ꂽ
		{
			break;
		}
	}

	return tarinaimono;
}



