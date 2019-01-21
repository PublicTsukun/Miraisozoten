#include "SceneManager.h"
#include "Library\Input.h"
#include "Title.h"
#include "Game.h"
#include "GamePause.h"
#include "Result.h"
#include "Ranking.h"

#include "GameSound.h"

SCENE SceneManager::GameScene = SCENE_MAX;
SCENE SceneManager::FadeSceneKeep = SCENE_MAX;
FADE_CURTAIN_STATE SceneManager::InFade = SLEEP;	// フェード状態
FadeCurtain SceneManager::SceneFade;

//----更新--------
int  SceneManager::Update()
{
	switch (GameScene)
	{
	case SCENE_TITLE:
		// タイトルシーンの更新
		UpdateTitle();

		//if (GetKeyboardTrigger(DIK_RETURN))
		//{
		//	SetScene(SCENE_GAME);
		//}
		break;

	case SCENE_GAME:
		// ゲームシーンの更新
		UpdateGame();

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetScene(SCENE_RESULT);
		}
		if (GetKeyboardTrigger(DIK_ESCAPE) || IsButtonTriggered(BUTTON_DOWN))
		{
			SetScene(SCENE_PAUSE);
		}
		break;

	case SCENE_RESULT:
		// リザルトシーンの更新
		UpdateResult();

		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(BUTTON_UP))
		{
			//SetScene(SCENE_TITLE);
		}
		break;

	case SCENE_RANKING:
		// ランキングシーンの更新
		UpdateRanking();

		//if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(BUTTON_UP))
		//{
		//	SetScene(SCENE_RESULT);
		//}
		break;

	case SCENE_PAUSE:
		// ゲーム中ポーズの更新
		switch (GamePause::Update())
		{
		case GPR::BACKGAME:
			SetScene(SCENE_GAME);
			break;

		case GPR::BACKTITLE:
			SetScene(SCENE_TITLE);
			break;
		}

		break;
	}

	return 0;
}

//----描画--------
void SceneManager::Draw()
{
	switch (GameScene)
	{
	case SCENE_TITLE:
		// タイトルシーンの描画処理
		DrawTitle();

		break;

	case SCENE_GAME:
		// ゲームシーンの描画処理
		DrawGame();

		break;

	case SCENE_RESULT:
		// リザルトの描画処理
		DrawResult();

		break;

	case SCENE_RANKING:
		// ランキングの描画処理
		DrawRanking();

		break;

	case SCENE_PAUSE:
		// ゲームシーンの描画処理
		DrawGame();

		// ゲーム中ポーズの描画処理
		GamePause::Draw();

		break;
	}
	SceneFade.Draw();
}

//----ゲームシーンの更新・取得--------
SCENE SceneManager::SetScene(SCENE scene, bool set)
{
	/* 指定シーンが同じ場合は戻る */
	if (scene == SCENE_MAX)
	{
		return GameScene;
	}

	/* ポーズ画面は例外処理方式で */
	if (scene == SCENE_PAUSE)
	{
		GameScene = SCENE_PAUSE;
		return SCENE_PAUSE;
	}
	if (GameScene == SCENE_PAUSE)
	{
		GameScene = SCENE_GAME;
		if (scene == SCENE_GAME)
		{
			return SCENE_GAME;
		}
	}

	/* フェード設定 */
	bool fadeSE = false;
	if (set)
	{
		switch (InFade)
		{
		case CLOSS:
			scene = FadeSceneKeep;
			InFade = OPEN;
			SceneFade.SetFade(OPEN);
			fadeSE = true;
			if (scene == SCENE_TITLE)
			{
				PlaySE(THANKYOU);
			}
			break;
		case OPEN:
			break;
		case SLEEP:
			FadeSceneKeep = scene;
			InFade = CLOSS;
			SceneFade.SetFade(CLOSS);
			PlaySE(CURTAIN);

			return scene;
			break;
		}
	}

	/* 現在のシーンのお片付け */
	switch (GameScene)
	{
	case SCENE_TITLE:
		// タイトルシーンの終了
		UninitTitle();

		break;

	case SCENE_GAME:
		// ゲームシーンの終了
		UninitGame();
		GamePause::Uninit();

		break;

	case SCENE_RESULT:
		// リザルトシーンの終了
		UninitResult();

		break;

	case SCENE_RANKING:
		// ランキングシーンの終了
		UninitRanking();

		break;
	}

	/* シーンの切り替え */
	GameScene = scene;

	/* 次のシーンの準備 */
	switch (GameScene)
	{
	case SCENE_TITLE:
		// タイトルシーンの初期化
		InitTitle();

		break;

	case SCENE_GAME:
		// ゲームシーンの初期化
		InitGame();
		GamePause::Init();

		break;

	case SCENE_RESULT:
		// リザルトシーンの初期化
		InitResult();

		break;

	case SCENE_RANKING:
		// ランキングシーンの初期化
		InitRanking();

		break;

	default:
		return GameScene;
		break;
	}

	if (fadeSE)
	{// カーテンオープンSE
		PlaySE(CURTAIN);
	}

	return GameScene;
}
SCENE SceneManager::GetScene()
{
	return GameScene;
}

//----フェード状態--------
void SceneManager::SetFadeState(FADE_CURTAIN_STATE state)
{
	InFade = state;
}
FADE_CURTAIN_STATE SceneManager::GetFadeState()
{
	return InFade;
}

//----フェードを進める--------
bool SceneManager::UpdateFade()
{
	return SceneFade.Update() ? true : false;
}




