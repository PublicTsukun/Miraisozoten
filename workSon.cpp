//=============================================================================
//
//�v�S�����@workSon.cpp
//
//=============================================================================

//�K�{�C���N���[�h
#include <windows.h>
#include "workSon.h"
#include "SceneManager.h"

// �v�S�����C���N���[�h
#include "voiceten.h"
#include "voicetenTest.h"
#include "messageBox.h"
#include "enemyRE.h"
#include "StageManager.h"
#include "VLauncher.h"
#include "EnemyDB.h"
#include "EnemyPosData.h"
#include "EnemyHP.h"
#include "EffectVH.h"
#include "EffectFB.h"

#include "S-Tester.h"

//=============================================================================
// ����������
//=============================================================================
HRESULT InitWorkSon(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg�������\�[�X��Init

		break;


	case SCENE_GAME://�Q�[���Ŏg�������\�[�X��Init
		InitVoiceten();
		//InitMessageBox();
		InitEnemyPosData();
		InitEnemyDB();
		InitEnemyHP();
		InitEnemyRE();
		InitStage();
		InitEffectVH();
		InitEffectFB();
		break;


	case SCENE_RESULT://���U���g�Ŏg�������\�[�X��Init

		break;
	}

	return S_OK;
}

//=============================================================================
// �I�������@���L�ڏꏊ����
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
		UninitVoiceten();
		//UninitMessageBox();
		UninitEnemyHP();
		UninitEnemyRE();
		UninitEffectVH();
		UninitEffectFB();
		break;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWorkSon(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg���\�[�X��Update

		break;


	case SCENE_GAME://�Q�[���Ŏg���\�[�X��Update
		UpdateVoiceten();
		//UpdateMessageBox();
		UpdateEnemyHP();
		UpdateEnemyRE();
		UpdateStage();
		UpdateVLauncher();
		UpdateEffectVH();
		UpdateEffectFB();

		#ifdef _DEBUG
		//TesterDC();
		//TestVL();
		//TestMB();
		//TestCO();
		TesterAtk();
		//TesterPD();
		//TesterEFVH();
		#endif
		break;


	case SCENE_RESULT://���U���g�Ŏg���\�[�X��Update

		break;
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWorkSon(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://�^�C�g���Ŏg���\�[�X��Draw

		break;

	case SCENE_PAUSE:
	case SCENE_GAME://�Q�[���Ŏg���\�[�X��Draw
		DrawVoiceten();
		//DrawMessagebox();
		DrawEnemyHP();
		DrawEnemyRE();
		DrawEffectVH();
		DrawEffectFB();
		break;


	case SCENE_RESULT://���U���g�Ŏg���\�[�X��Draw

		break;
	}


}