//=============================================================================
//
//初担当分　workTsu.cpp
//
//=============================================================================

//必須インクルード
#include <windows.h>
#include "workTsu.h"
#include "SceneManager.h"


//初担当分インクルード
#include "Library\Common.h"
#include "AimPointer.h"
#include "voicetank.h"
#include "finishcount.h"

static AimPointer AimPoint;
static CEnergyTankUI Tank;

//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitWorkTsu(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使いたいソースのInit

		break;


	case SCENE_GAME://ゲームで使いたいソースのInit
		AimPoint.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, 100, 100, "data/TEXTURE/UI/ターゲットカーソル.png");
		Tank.Init();
		InitFinishCount();

		break;


	case SCENE_RESULT://リザルトで使いたいソースのInit

		break;
	}

	return S_OK;
}

//=============================================================================
//終了処理　※記載場所注意
//=============================================================================
void UninitWorkTsu(void)
{

	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://リザルトで使ったソースのUninit

		break;


	case SCENE_GAME://タイトルで使ったソースのUninit
		Tank.Uninit();

		break;


	case SCENE_RESULT://ゲームで使ったソースのUninit
		AimPoint.Release();
		UninitFinishCount();

		break;
	}


}

//=============================================================================
//更新処理
//=============================================================================
void UpdateWorkTsu(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使うソースのUpdate

		break;


	case SCENE_GAME://ゲームで使うソースのUpdate
		AimPoint.Update();
		Tank.Update();
		UpdateFinishCount();
		break;


	case SCENE_RESULT://リザルトで使うソースのUpdate

		break;
	}


}

//=============================================================================
//描画処理
//=============================================================================
void DrawWorkTsu(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使うソースのDraw

		break;


	case SCENE_PAUSE:
	case SCENE_GAME://ゲームで使うソースのDraw
		AimPoint.Draw();
		Tank.Draw();
		DrawFinishCount();

		break;


	case SCENE_RESULT://リザルトで使うソースのDraw

		break;
	}


}
