//=============================================================================
//
//�����S�����@workHagiwara.cpp
//
//=============================================================================

//�K�{�C���N���[�h
#include <windows.h>
#include "workHagiwara.h"
#include "SceneManager.h"


//�����S�����C���N���[�h
#include "score.h"


//=============================================================================
//����������
//=============================================================================
HRESULT InitWorkHagiwara(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg�������\�[�X��Init
		

		break;


	case SCENE_GAME://�Q�[���Ŏg�������\�[�X��Init
		InitScore();
		break;


	case SCENE_RESULT://���U���g�Ŏg�������\�[�X��Init

		break;
	}

	return S_OK;
}

//=============================================================================
//�I�������@���L�ڏꏊ����
//=============================================================================
void UninitWorkHagiwara(void)
{

	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://���U���g�Ŏg�����\�[�X��Uninit

		break;


	case SCENE_GAME://�^�C�g���Ŏg�����\�[�X��Uninit

		break;


	case SCENE_RESULT://�Q�[���Ŏg�����\�[�X��Uninit
		UninitScore();
		break;
	}


}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateWorkHagiwara(void)
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
void DrawWorkHagiwara(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg���\�[�X��Draw

		break;


	case SCENE_GAME://�Q�[���Ŏg���\�[�X��Draw
		DrawScore();
		break;


	case SCENE_RESULT://���U���g�Ŏg���\�[�X��Draw

		break;
	}


}