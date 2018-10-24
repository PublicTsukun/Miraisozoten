//=============================================================================
//
//�R�{�S�����@workYamamoto.cpp
//
//=============================================================================

//�K�{�C���N���[�h
#include <windows.h>
#include "workYamamoto.h"
#include "SceneManager.h"


//�R�{�S�����C���N���[�h
#include "workYamamoto.h"
#include <stdio.h>


#define EMPTY_NO		(99)		// 

// �F�X�����点����ׂ̐���
#define NO_ENTRY		(100)		// ���������͂���Ă��Ȃ�
#define BACK_CHAR		(101)		// �߂�{�^���������ꂽ
//*****************************************************************************
// ����[�΂�ւ񂷂�
//*****************************************************************************

int namechar;
int lastchar;		// ���[������Ă������łȂ񂾂����I
RANKDATA	rankdatawk[1];
//=============================================================================
//����������
//=============================================================================
HRESULT InitWorkYamamoto(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg�������\�[�X��Init

		break;


	case SCENE_GAME://�Q�[���Ŏg�������\�[�X��Init

		break;


	case SCENE_RESULT://���U���g�Ŏg�������\�[�X��Init
		void InitName(void);
		break;
	}

	return S_OK;
}

//=============================================================================
//�I�������@���L�ڏꏊ����
//=============================================================================
void UninitWorkYamamoto(void)
{

	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://���U���g�Ŏg�����\�[�X��Uninit

		break;


	case SCENE_GAME://�^�C�g���Ŏg�����\�[�X��Uninit

		break;


	case SCENE_RESULT://�Q�[���Ŏg�����\�[�X��Uninit

		break;
	}


}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateWorkYamamoto(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg���\�[�X��Update

		break;


	case SCENE_GAME://�Q�[���Ŏg���\�[�X��Update

		break;


	case SCENE_RESULT://���U���g�Ŏg���\�[�X��Update

		break;
	}


}


//=============================================================================
//�`�揈��
//=============================================================================
void DrawWorkYamamoto(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg���\�[�X��Draw

		break;


	case SCENE_GAME://�Q�[���Ŏg���\�[�X��Draw

		break;


	case SCENE_RESULT://���U���g�Ŏg���\�[�X��Draw

		break;
	}


}

//*******************************************************************
// void Initname(void)
//*************************************************************************
void Initname(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	// ���O������
	for (int i = 0; i < NAMEMAX; i++)
	{
		rankdata[0].namechar[i] = EMPTY_NO;
	}
	// �J�[�\���������ʒu��
	rankdata[0].cursole_X = 0;
	rankdata[0].cursole_Y = 0;
	namechar = 0;
	// �摜�̏������H
}
//**************************************************************************:
// void pinokkimon(void)
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

void pinokkimon(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	
	int namechar = 0;	// ���݂̓��͕����̏�����
	// ����
	int playername = 0;

	//�@�������͏���
	while(1)
	{
		// ���݂̓��͕��������ő�łȂ���
		if (namechar < NAMEMAX)
		{
			rankdata[0].namechar[namechar] = jyureimon();
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
				case BACK_CHAR :
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
			check = jyureimon();
			if (check == BACK_CHAR)
			{
				rankdata[0].namechar[namechar] = EMPTY_NO;
				namechar--;       
			}
		}

	
	}



}

//******************************************************************************
// int jyureimon(void)
// �J�[�\���L�[�ŕ�����I��őI�񂾕������i�[������
//***************************************************************:
int jyureimon(void)
{
	int tarinaimono=EMPTY_NO;	// �I�΂ꂽ����
	
	return tarinaimono;
}

