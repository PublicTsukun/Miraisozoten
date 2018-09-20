#include "SceneManager.h"
#include "Result.h"
#include "Title.h"


SCENE SceneManager::GameScene = SCENE_MAX;


//----更新--------
int  SceneManager::Update()
{
	switch (GameScene)
	{
	case SCENE_TITLE:

		// タイトルシーンの更新処理


		if (false)
		{
			Scene::SetScene(SCENE_GAME);
		}

		break;

	case SCENE_GAME:

		// ゲームシーンの更新


		if (false)
		{
			Scene::SetScene(SCENE_RESULT);
		}

		break;

	case SCENE_RESULT:

		// リザルトシーンの更新処理


		if (false)
		{
			Scene::SetScene(SCENE_TITLE);
		}

		break;

	default:
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


		break;

	case SCENE_GAME:

		// ゲームシーンの描画処理


		break;

	case SCENE_RESULT:

		// リザルトの描画処理


		break;

	default:
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

	/* 現在のシーンのお片付け */
	switch (GameScene)
	{
	case SCENE_TITLE:

		// タイトルシーンの終了処理


		break;

	case SCENE_GAME:

		// ゲームシーンの終了処理 リザルトに統一
		//UninitGame();

		// ポーズシーンの終了処理

		// カットインシーンの終了処理

		break;

	case SCENE_RESULT:

		// リザルトシーンの終了処理


		// ゲームシーンの終了処理


		break;

	default:
		break;
	}

	/* 次のシーンの準備 */
	switch (scene)
	{
	case SCENE_TITLE:

		// タイトルシーンの初期化


		GameScene = SCENE_TITLE;

		break;

	case SCENE_GAME:

		// ゲームシーンの初期化


		GameScene = SCENE_GAME;

		break;

	case SCENE_RESULT:

		// リザルトシーンの初期化


		GameScene = SCENE_RESULT;

		break;

	default:
		return GameScene;
		break;
	}

	GameScene = scene;

	return GameScene;
}



