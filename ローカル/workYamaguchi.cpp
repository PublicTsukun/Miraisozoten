//=============================================================================
//
//山口担当分　workYamaguchi.cpp
//
//=============================================================================

//必須インクルード
#include <windows.h>
#include "workYamaguchi.h"
#include "SceneManager.h"


//山口担当分インクルード
#include "field.h"

//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitWorkYamaguchi(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使いたいソースのInit

		break;


	case SCENE_GAME://ゲームで使いたいソースのInit
		InitFeild();
		break;


	case SCENE_RESULT://リザルトで使いたいソースのInit

		break;
	}

	return S_OK;
}

//=============================================================================
//終了処理　※記載場所注意
//=============================================================================
void UninitWorkYamaguchi(void)
{

	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://リザルトで使ったソースのUninit

		break;


	case SCENE_GAME://タイトルで使ったソースのUninit

		break;


	case SCENE_RESULT://ゲームで使ったソースのUninit
		UninitFeild();
		break;
	}


}

//=============================================================================
//更新処理
//=============================================================================
void UpdateWorkYamaguchi(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使うソースのUpdate

		break;


	case SCENE_GAME://ゲームで使うソースのUpdate

		break;


	case SCENE_RESULT://リザルトで使うソースのUpdate

		break;
	}


}

//=============================================================================
//描画処理
//=============================================================================
void DrawWorkYamaguchi(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使うソースのDraw

		break;


	case SCENE_GAME://ゲームで使うソースのDraw
		DrawFeild();
		break;


	case SCENE_RESULT://リザルトで使うソースのDraw

		break;
	}


}