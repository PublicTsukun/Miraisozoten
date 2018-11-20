//=============================================================================
//
//�R�{�S�����@workYamamoto.cpp
//
//=============================================================================

//�K�{�C���N���[�h
#include <windows.h>
#include "workYamamoto.h"
#include "SceneManager.h"



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
		break;

	case SCENE_RANKING:

		InitName();
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
	case SCENE_RANKING:

		UninitName();
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

		// �������Ɉړ�
	case SCENE_RANKING:
		Update_Name();
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
	case SCENE_RANKING:
		DrawName();
		break;
	}


}

