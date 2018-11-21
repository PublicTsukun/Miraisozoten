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
#include "timer.h"
#include "score.h"
#include "UIBonus.h"
#include "startcount.h"
#include "finishcount.h"
#include "Resultlogo.h"


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
		InitField();
		InitTimer();
		InitScore();
		InitUIBonus();
		InitStartCount();
		InitFinishCount();

		break;


	case SCENE_RESULT://リザルトで使いたいソースのInit
		InitResultlogo();
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
		UninitResultlogo();
		break;


	case SCENE_GAME://タイトルで使ったソースのUninit

		break;


	case SCENE_RESULT://ゲームで使ったソースのUninit
		UninitField();
		UninitTimer();
		UninitScore();
		UninitUIBonus();
		UninitStartCount();
		UninitFinishCount();
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
		UpdateTimer();
		UpdateScore();
		UpdateUIBonus();
		UpdateStartCount();
		UpdateFinishCount();
		UpdateField();
		break;


	case SCENE_RESULT://リザルトで使うソースのUpdate
		UpdateResultlogo();
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
		DrawField();
		DrawTimer();
		DrawScore();
		DrawUIBonus();
		DrawStartCount();
		DrawFinishCount();
		break;


	case SCENE_RESULT://リザルトで使うソースのDraw
		DrawResultlogo();

		break;
	}


}