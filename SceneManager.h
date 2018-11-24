#ifndef _MANAGER_SCENE_H_INCLUDE_
#define _MANAGER_SCENE_H_INCLUDE_


#include "FadeCurtain.h"


/* ゲーム状態の種類 */
enum SCENE
{
	SCENE_TITLE = 0,	// タイトル画面
	SCENE_GAME,			// メインゲーム
	SCENE_RESULT,		// リザルト画面
	SCENE_RANKING,		// ランキング画面
	SCENE_MAX,
	SCENE_PAUSE, // ゲーム中ポーズ画面
	SCENE_END, // アプリ終了
};


typedef class SceneManager
{
	static SCENE GameScene;
	static SCENE FadeSceneKeep;
	static FADE_CURTAIN_STATE InFade;
	static FadeCurtain SceneFade;

public:
	static int  Update();
	static void Draw();
	static SCENE SetScene(SCENE scene, bool set = true);
	static SCENE GetScene();

	static void SetFadeState(FADE_CURTAIN_STATE state);
	static FADE_CURTAIN_STATE GetFadeState();
	static bool UpdateFade();

}Scene;


#endif // !_MANAGER_SCENE_H_INCLUDE_
