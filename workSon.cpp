//=============================================================================
//
//宋担当分　workSon.cpp
//
//=============================================================================

//必須インクルード
#include <windows.h>
#include "workSon.h"
#include "SceneManager.h"

// 宋担当分インクルード
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
// 初期化処理
//=============================================================================
HRESULT InitWorkSon(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使いたいソースのInit

		break;


	case SCENE_GAME://ゲームで使いたいソースのInit
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


	case SCENE_RESULT://リザルトで使いたいソースのInit

		break;
	}

	return S_OK;
}

//=============================================================================
// 終了処理　※記載場所注意
//=============================================================================
void UninitWorkSon(void)
{

	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://リザルトで使ったソースのUninit

		break;


	case SCENE_GAME://タイトルで使ったソースのUninit
		break;


	case SCENE_RESULT://ゲームで使ったソースのUninit
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
// 更新処理
//=============================================================================
void UpdateWorkSon(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使うソースのUpdate

		break;


	case SCENE_GAME://ゲームで使うソースのUpdate
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


	case SCENE_RESULT://リザルトで使うソースのUpdate

		break;
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawWorkSon(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使うソースのDraw

		break;

	case SCENE_PAUSE:
	case SCENE_GAME://ゲームで使うソースのDraw
		DrawVoiceten();
		//DrawMessagebox();
		DrawEnemyHP();
		DrawEnemyRE();
		DrawEffectVH();
		DrawEffectFB();
		break;


	case SCENE_RESULT://リザルトで使うソースのDraw

		break;
	}


}