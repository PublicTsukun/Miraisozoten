#include "SceneManager.h"
#include "Library\Input.h"
#include "Title.h"
#include "Game.h"
#include "GamePause.h"
#include "Result.h"
#include "Ranking.h"


SCENE SceneManager::GameScene = SCENE_MAX;


//----�X�V--------
int  SceneManager::Update()
{
	switch (GameScene)
	{
	case SCENE_TITLE:
		// �^�C�g���V�[���̍X�V
		UpdateTitle();

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			//SetScene(SCENE_GAME);
		}
		break;

	case SCENE_GAME:
		// �Q�[���V�[���̍X�V
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
		// ���U���g�V�[���̍X�V
		UpdateResult();

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetScene(SCENE_TITLE);
		}
		break;

	case SCENE_RANKING:
		// �����L���O�V�[���̍X�V
		UpdateRanking();

		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetScene(SCENE_TITLE);
		}
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
}

//----�Q�[���V�[���̍X�V�E�擾--------
SCENE SceneManager::SetScene(SCENE scene)
{
	/* �w��V�[���������ꍇ�͖߂� */
	if (scene == SCENE_MAX)
	{
		return GameScene;
	}

	/* �|�[�Y��ʂ͗�O���������� */
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

	return GameScene;
}

SCENE SceneManager::GetScene()
{
	return GameScene;
}



