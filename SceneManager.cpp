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
FADE_CURTAIN_STATE SceneManager::InFade = SLEEP;	// �t�F�[�h���
FadeCurtain SceneManager::SceneFade;

//----�X�V--------
int  SceneManager::Update()
{
	switch (GameScene)
	{
	case SCENE_TITLE:
		// �^�C�g���V�[���̍X�V
		UpdateTitle();

		//if (GetKeyboardTrigger(DIK_RETURN))
		//{
		//	SetScene(SCENE_GAME);
		//}
		break;

	case SCENE_GAME:
		// �Q�[���V�[���̍X�V
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
		// ���U���g�V�[���̍X�V
		UpdateResult();

		if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(BUTTON_UP))
		{
			//SetScene(SCENE_TITLE);
		}
		break;

	case SCENE_RANKING:
		// �����L���O�V�[���̍X�V
		UpdateRanking();

		//if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(BUTTON_UP))
		//{
		//	SetScene(SCENE_RESULT);
		//}
		break;

	case SCENE_PAUSE:
		// �Q�[�����|�[�Y�̍X�V
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

//----�`��--------
void SceneManager::Draw()
{
	switch (GameScene)
	{
	case SCENE_TITLE:
		// �^�C�g���V�[���̕`�揈��
		DrawTitle();

		break;

	case SCENE_GAME:
		// �Q�[���V�[���̕`�揈��
		DrawGame();

		break;

	case SCENE_RESULT:
		// ���U���g�̕`�揈��
		DrawResult();

		break;

	case SCENE_RANKING:
		// �����L���O�̕`�揈��
		DrawRanking();

		break;

	case SCENE_PAUSE:
		// �Q�[���V�[���̕`�揈��
		DrawGame();

		// �Q�[�����|�[�Y�̕`�揈��
		GamePause::Draw();

		break;
	}
	SceneFade.Draw();
}

//----�Q�[���V�[���̍X�V�E�擾--------
SCENE SceneManager::SetScene(SCENE scene, bool set)
{
	/* �w��V�[���������ꍇ�͖߂� */
	if (scene == SCENE_MAX)
	{
		return GameScene;
	}

	/* �|�[�Y��ʂ͗�O���������� */
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

	/* �t�F�[�h�ݒ� */
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

	/* ���݂̃V�[���̂��Еt�� */
	switch (GameScene)
	{
	case SCENE_TITLE:
		// �^�C�g���V�[���̏I��
		UninitTitle();

		break;

	case SCENE_GAME:
		// �Q�[���V�[���̏I��
		UninitGame();
		GamePause::Uninit();

		break;

	case SCENE_RESULT:
		// ���U���g�V�[���̏I��
		UninitResult();

		break;

	case SCENE_RANKING:
		// �����L���O�V�[���̏I��
		UninitRanking();

		break;
	}

	/* �V�[���̐؂�ւ� */
	GameScene = scene;

	/* ���̃V�[���̏��� */
	switch (GameScene)
	{
	case SCENE_TITLE:
		// �^�C�g���V�[���̏�����
		InitTitle();

		break;

	case SCENE_GAME:
		// �Q�[���V�[���̏�����
		InitGame();
		GamePause::Init();

		break;

	case SCENE_RESULT:
		// ���U���g�V�[���̏�����
		InitResult();

		break;

	case SCENE_RANKING:
		// �����L���O�V�[���̏�����
		InitRanking();

		break;

	default:
		return GameScene;
		break;
	}

	if (fadeSE)
	{// �J�[�e���I�[�v��SE
		PlaySE(CURTAIN);
	}

	return GameScene;
}
SCENE SceneManager::GetScene()
{
	return GameScene;
}

//----�t�F�[�h���--------
void SceneManager::SetFadeState(FADE_CURTAIN_STATE state)
{
	InFade = state;
}
FADE_CURTAIN_STATE SceneManager::GetFadeState()
{
	return InFade;
}

//----�t�F�[�h��i�߂�--------
bool SceneManager::UpdateFade()
{
	return SceneFade.Update() ? true : false;
}




