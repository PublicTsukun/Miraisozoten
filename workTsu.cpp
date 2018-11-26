//=============================================================================
//
//���S�����@workTsu.cpp
//
//=============================================================================

//�K�{�C���N���[�h
#include <windows.h>
#include "workTsu.h"
#include "SceneManager.h"


//���S�����C���N���[�h
#include "Library\Common.h"
#include "AimPointer.h"
#include "voicetank.h"
#include "finishcount.h"

static AimPointer AimPoint;
static CEnergyTankUI Tank;

//=============================================================================
//����������
//=============================================================================
HRESULT InitWorkTsu(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg�������\�[�X��Init

		break;


	case SCENE_GAME://�Q�[���Ŏg�������\�[�X��Init
		AimPoint.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, 100, 100, "data/TEXTURE/UI/�^�[�Q�b�g�J�[�\��.png");
		Tank.Init();
		InitFinishCount();

		break;


	case SCENE_RESULT://���U���g�Ŏg�������\�[�X��Init

		break;
	}

	return S_OK;
}

//=============================================================================
//�I�������@���L�ڏꏊ����
//=============================================================================
void UninitWorkTsu(void)
{

	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://���U���g�Ŏg�����\�[�X��Uninit

		break;


	case SCENE_GAME://�^�C�g���Ŏg�����\�[�X��Uninit
		Tank.Uninit();

		break;


	case SCENE_RESULT://�Q�[���Ŏg�����\�[�X��Uninit
		AimPoint.Release();
		UninitFinishCount();

		break;
	}


}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateWorkTsu(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg���\�[�X��Update

		break;


	case SCENE_GAME://�Q�[���Ŏg���\�[�X��Update
		AimPoint.Update();
		Tank.Update();
		UpdateFinishCount();
		break;


	case SCENE_RESULT://���U���g�Ŏg���\�[�X��Update

		break;
	}


}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawWorkTsu(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg���\�[�X��Draw

		break;


	case SCENE_PAUSE:
	case SCENE_GAME://�Q�[���Ŏg���\�[�X��Draw
		AimPoint.Draw();
		Tank.Draw();
		DrawFinishCount();

		break;


	case SCENE_RESULT://���U���g�Ŏg���\�[�X��Draw

		break;
	}


}
