#ifndef _MANAGER_SCENE_H_INCLUDE_
#define _MANAGER_SCENE_H_INCLUDE_


#include "FadeCurtain.h"


/* �Q�[����Ԃ̎�� */
enum SCENE
{
	SCENE_TITLE = 0,	// �^�C�g�����
	SCENE_GAME,			// ���C���Q�[��
	SCENE_RESULT,		// ���U���g���
	SCENE_RANKING,		// �����L���O���
	SCENE_MAX,
	SCENE_PAUSE, // �Q�[�����|�[�Y���
	SCENE_END, // �A�v���I��
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
