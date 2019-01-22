//=============================================================================
//
//�R���S�����@workYamaguchi.cpp
//
//=============================================================================

//�K�{�C���N���[�h
#include <windows.h>
#include "workYamaguchi.h"
#include "SceneManager.h"


//�R���S�����C���N���[�h
#include "field.h"
#include "timer.h"
#include "score.h"
#include "UIBonus.h"
#include "startcount.h"
#include "Resultlogo.h"
#include "StageSwitch.h"

//=============================================================================
//����������
//=============================================================================
HRESULT InitWorkYamaguchi(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg�������\�[�X��Init

		InitScore();
		break;


	case SCENE_GAME://�Q�[���Ŏg�������\�[�X��Init
		InitField();
		InitTimer();
		InitUIBonus();
		InitStartCount();
		InitStageSwitch();

		break;


	case SCENE_RESULT://���U���g�Ŏg�������\�[�X��Init
		InitResultlogo();
		break;
	}

	return S_OK;
}

//=============================================================================
//�I�������@���L�ڏꏊ����
//=============================================================================
void UninitWorkYamaguchi(void)
{

	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://���U���g�Ŏg�����\�[�X��Uninit
		UninitResultlogo();
		break;


	case SCENE_GAME://�^�C�g���Ŏg�����\�[�X��Uninit

		break;


	case SCENE_RESULT://�Q�[���Ŏg�����\�[�X��Uninit
		UninitField();
		UninitTimer();
		UninitScore();
		UninitUIBonus();
		UninitStartCount();
		UninitStageSwitch();

		break;
	}


}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateWorkYamaguchi(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg���\�[�X��Update

		break;


	case SCENE_GAME://�Q�[���Ŏg���\�[�X��Update
		UpdateTimer();
		UpdateScore();
		UpdateUIBonus();
		UpdateField();
		UpdateStageSwitch();
		UpdateStartCount();

		break;


	case SCENE_RESULT://���U���g�Ŏg���\�[�X��Update
		UpdateResultlogo();
		break;
	}


}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawWorkYamaguchi(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg���\�[�X��Draw

		break;


	case SCENE_PAUSE:
	case SCENE_GAME://�Q�[���Ŏg���\�[�X��Draw
		DrawField();
		DrawTimer();
		DrawScore();
		DrawUIBonus();
		DrawStartCount();

		break;


	case SCENE_RESULT://���U���g�Ŏg���\�[�X��Draw
		DrawResultlogo();

		break;
	}


}
//=============================================================================
//�`�揈��
//=============================================================================
void DrawWorkYamaguchi2(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg���\�[�X��Draw

		break;


	case SCENE_PAUSE:
	case SCENE_GAME://�Q�[���Ŏg���\�[�X��Draw
		DrawStageSwitch();

		break;


	case SCENE_RESULT://���U���g�Ŏg���\�[�X��Draw

		break;
	}


}