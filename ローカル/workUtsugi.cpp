<<<<<<< HEAD
//=============================================================================
//
//�F�s�ؒS�����@workUtsugi.cpp
//
//=============================================================================

//�K�{�C���N���[�h
#include <windows.h>
#include "workUtsugi.h"
#include "SceneManager.h"


//�F�s�ؒS�����C���N���[�h


//=============================================================================
//����������
//=============================================================================
HRESULT InitWorkUtsugi(void)
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
void UninitWorkUtsugi(void)
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
void UpdateWorkUtsugi(void)
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
void DrawWorkUtsugi(void)
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


=======
//=============================================================================
//
//�F�s�ؒS�����@workUtsugi.cpp
//
//=============================================================================

//�K�{�C���N���[�h
#include <windows.h>
#include "workUtsugi.h"
#include "SceneManager.h"


//�F�s�ؒS�����C���N���[�h


//=============================================================================
//����������
//=============================================================================
HRESULT InitWorkUtsugi(void)
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
void UninitWorkUtsugi(void)
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
void UpdateWorkUtsugi(void)
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
void DrawWorkUtsugi(void)
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


>>>>>>> 9d3e0b33906c3c66a5d911e8070648fe2bef2022
}