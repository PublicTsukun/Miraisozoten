//=============================================================================
//
//山本担当分　workYamamoto.cpp
//
//=============================================================================

//必須インクルード
#include <windows.h>
#include "workYamamoto.h"
#include "SceneManager.h"



//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitWorkYamamoto(void)
{
	 
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使いたいソースのInit

		break;


	case SCENE_GAME://ゲームで使いたいソースのInit
		break;


	case SCENE_RESULT://リザルトで使いたいソースのInit
		break;

	case SCENE_RANKING:

		InitName();
		break;
	}

	return S_OK;
}

//=============================================================================
//終了処理　※記載場所注意
//=============================================================================
void UninitWorkYamamoto(void)
{

	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://リザルトで使ったソースのUninit

		break;


	case SCENE_GAME://タイトルで使ったソースのUninit

		break;


	case SCENE_RESULT://ゲームで使ったソースのUninit
		break;
	case SCENE_RANKING:

		UninitName();
		break;
	}


}

//=============================================================================
//更新処理
//=============================================================================
void UpdateWorkYamamoto(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使うソースのUpdate

		break;


	case SCENE_GAME://ゲームで使うソースのUpdate

		break;


	case SCENE_RESULT://リザルトで使うソースのUpdate

		break;

		// こっちに移動
	case SCENE_RANKING:
		Update_Name();
		break;

	}
}


//=============================================================================
//描画処理
//=============================================================================
void DrawWorkYamamoto(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使うソースのDraw

		break;


	case SCENE_GAME://ゲームで使うソースのDraw

		break;


	case SCENE_RESULT://リザルトで使うソースのDraw
		break;
	case SCENE_RANKING:
		DrawName();
		break;
	}


}

