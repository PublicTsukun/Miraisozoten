#include "SceneManager.h"
#include "Library\Input.h"
#include "Title.h"
#include "Game.h"
#include "GamePause.h"
#include "Result.h"
#include "Ranking.h"
#include "Library\DebugProcess.h"

SCENE SceneManager::GameScene = SCENE_MAX;

enum testInitCnt
{
	TitleInit,
	TitleUninit,
	GameInit,
	GameUninit,
	ResultInit,
	ResultUninit,
	RankingInit,
	RankingUninit,
	test_Max
};
static int uiCnt[test_Max] = { 0 };

//----更新--------
int  SceneManager::Update()
{
	switch (GameScene)
	{
	case SCENE_TITLE:
		// タイトルシーンの更新
		UpdateTitle();

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			//SetScene(SCENE_GAME);
		}
		break;

	case SCENE_GAME:
		// ゲームシーンの更新
		UpdateGame();

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetScene(SCENE_RESULT);
		}
		if (GetKeyboardTrigger(DIK_ESCAPE))
		{
			SetScene(SCENE_PAUSE);
		}
		break;

	case SCENE_RESULT:
		// リザルトシーンの更新
		UpdateResult();

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetScene(SCENE_TITLE);
		}
		break;

	case SCENE_RANKING:
		// ランキングシーンの更新
		UpdateRanking();

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetScene(SCENE_TITLE);
		}
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

	for (int i = 0; i < test_Max; i++)
	{
		PrintDebugProcess("初期化回数 : %d\n", uiCnt[i]);
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
}

//----ゲームシーンの更新・取得--------
SCENE SceneManager::SetScene(SCENE scene)
{
	/* 指定シーンが同じ場合は戻る */
	if (scene == SCENE_MAX)
	{
		return GameScene;
	}

	/* ポーズ画面は例外処理方式で */
	if (scene == SCENE_PAUSE)
	{
		scene = SCENE_PAUSE;
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

	/* 現在のシーンのお片付け */
	switch (GameScene)
	{
	case SCENE_TITLE:
		// タイトルシーンの終了
		UninitTitle();
		uiCnt[TitleUninit]++;
		break;

	case SCENE_GAME:
		// ゲームシーンの終了
		UninitGame();
		GamePause::Uninit();
		uiCnt[GameUninit]++;

		break;

	case SCENE_RESULT:
		// リザルトシーンの終了
		UninitResult();
		uiCnt[ResultUninit]++;

		break;

	case SCENE_RANKING:
		// ランキングシーンの終了
		UninitRanking();
		uiCnt[RankingUninit]++;

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
		uiCnt[TitleInit]++;

		break;

	case SCENE_GAME:
		// ゲームシーンの初期化
		InitGame();
		GamePause::Init();
		uiCnt[GameInit]++;

		break;

	case SCENE_RESULT:
		// リザルトシーンの初期化
		InitResult();
		uiCnt[ResultInit]++;

		break;

	case SCENE_RANKING:
		// ランキングシーンの初期化
		InitRanking();
		uiCnt[RankingInit]++;

		break;

	default:
		return GameScene;
		break;
	}

	return GameScene;
}

SCENE SceneManager::GetScene()
{
	return GameScene;
}



