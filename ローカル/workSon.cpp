//=============================================================================
//
//�v�S�����@workSon.cpp
//
//=============================================================================

//�K�{�C���N���[�h
#include <windows.h>
#include "workSon.h"
#include "SceneManager.h"


//�v�S�����C���N���[�h


//=============================================================================
//����������
//=============================================================================
HRESULT InitWorkSon(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg�������\�[�X��Init

		break;


	case SCENE_GAME://�Q�[���Ŏg�������\�[�X��Init

		break;


	case SCENE_RESULT://���U���g�Ŏg�������\�[�X��Init

		break;
	}

	return S_OK;
}

//=============================================================================
//�I�������@���L�ڏꏊ����
//=============================================================================
void UninitWorkSon(void)
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
void UpdateWorkSon(void)
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
void DrawWorkSon(void)
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