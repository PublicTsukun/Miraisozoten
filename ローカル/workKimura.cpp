<<<<<<< HEAD
//=============================================================================
//
//�ؑ��S�����@workKimura.cpp
//�@��N�̎��ɂ����main.cpp�Ɠ���������
//=============================================================================

//�K�{�C���N���[�h
#include <windows.h>
#include "workKimura.h"
#include "SceneManager.h"


//�ؑ��S�����C���N���[�h
#include "enemy.h"

//=============================================================================
//����������
//=============================================================================
HRESULT InitWorkKimura(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg�������\�[�X��Init

		break;


	case SCENE_GAME://�Q�[���Ŏg�������\�[�X��Init
		InitENEMY();
		break;


	case SCENE_RESULT://���U���g�Ŏg�������\�[�X��Init

		break;
	}

	return S_OK;
}

//=============================================================================
//�I�������@���L�ڏꏊ����
//=============================================================================
void UninitWorkKimura(void)
{

	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://���U���g�Ŏg�����\�[�X��Uninit

		break;


	case SCENE_GAME://�^�C�g���Ŏg�����\�[�X��Uninit
		
		break;


	case SCENE_RESULT://�Q�[���Ŏg�����\�[�X��Uninit
		UninitENEMY();
		break;
	}


}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateWorkKimura(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg���\�[�X��Update

		break;


	case SCENE_GAME://�Q�[���Ŏg���\�[�X��Update
		UpdateENEMY();
		break;


	case SCENE_RESULT://���U���g�Ŏg���\�[�X��Update

		break;
	}


}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawWorkKimura(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg���\�[�X��Draw

		break;


	case SCENE_GAME://�Q�[���Ŏg���\�[�X��Draw
		DrawENEMY();
		break;


	case SCENE_RESULT://���U���g�Ŏg���\�[�X��Draw

		break;
	}


=======
//=============================================================================
//
//�ؑ��S�����@workKimura.cpp
//�@��N�̎��ɂ����main.cpp�Ɠ���������
//=============================================================================

//�K�{�C���N���[�h
#include <windows.h>
#include "workKimura.h"
#include "SceneManager.h"


//�ؑ��S�����C���N���[�h
#include "enemy.h"

//=============================================================================
//����������
//=============================================================================
HRESULT InitWorkKimura(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg�������\�[�X��Init

		break;


	case SCENE_GAME://�Q�[���Ŏg�������\�[�X��Init
		InitENEMY();
		break;


	case SCENE_RESULT://���U���g�Ŏg�������\�[�X��Init

		break;
	}

	return S_OK;
}

//=============================================================================
//�I�������@���L�ڏꏊ����
//=============================================================================
void UninitWorkKimura(void)
{

	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://���U���g�Ŏg�����\�[�X��Uninit

		break;


	case SCENE_GAME://�^�C�g���Ŏg�����\�[�X��Uninit
		
		break;


	case SCENE_RESULT://�Q�[���Ŏg�����\�[�X��Uninit
		UninitENEMY();
		break;
	}


}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateWorkKimura(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg���\�[�X��Update

		break;


	case SCENE_GAME://�Q�[���Ŏg���\�[�X��Update
		UpdateENEMY();
		break;


	case SCENE_RESULT://���U���g�Ŏg���\�[�X��Update

		break;
	}


}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawWorkKimura(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg���\�[�X��Draw

		break;


	case SCENE_GAME://�Q�[���Ŏg���\�[�X��Draw
		DrawENEMY();
		break;


	case SCENE_RESULT://���U���g�Ŏg���\�[�X��Draw

		break;
	}


>>>>>>> 9d3e0b33906c3c66a5d911e8070648fe2bef2022
}