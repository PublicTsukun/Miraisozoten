//=============================================================================
//
//木村担当分　workKimura.cpp
//　一年の時にやったmain.cppと同じやり方で
//=============================================================================

//必須インクルード
#include <windows.h>
#include "workKimura.h"
#include "SceneManager.h"


//木村担当分インクルード
#include "enemy.h"
#include "titlelogo.h"

//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitWorkKimura(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使いたいソースのInit
		InitTitlelogo();//タイトルロゴ
		break;

	case SCENE_PAUSE:
	case SCENE_GAME://ゲームで使いたいソースのInit
		InitENEMY();
		break;


	case SCENE_RESULT://リザルトで使いたいソースのInit

		break;
	}

	return S_OK;
}

//=============================================================================
//終了処理　※記載場所注意
//=============================================================================
void UninitWorkKimura(void)
{

	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://リザルトで使ったソースのUninit

		break;


	case SCENE_GAME://タイトルで使ったソースのUninit
		UninitTitlelogo();//タイトルロゴで使ったソースのUninitlogo
		break;


	case SCENE_RESULT://ゲームで使ったソースのUninit
		UninitENEMY();
		break;
	}


}

//=============================================================================
//更新処理
//=============================================================================
void UpdateWorkKimura(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使うソースのUpdate
		UpdateTitlelogo();
		break;


	case SCENE_GAME://ゲームで使うソースのUpdate
//		UpdateENEMY();
		break;


	case SCENE_RESULT://リザルトで使うソースのUpdate

		break;
	}


}

//=============================================================================
//描画処理
//=============================================================================
void DrawWorkKimura(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使うソースのDraw
		DrawTitlelogo();
		break;


	case SCENE_GAME://ゲームで使うソースのDraw
//		DrawENEMY();
		break;


	case SCENE_RESULT://リザルトで使うソースのDraw

		break;
	}


}