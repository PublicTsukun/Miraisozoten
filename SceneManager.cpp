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

	for (int i = 0; i < test_Max; i++)
	{
		PrintDebugProcess("�������� : %d\n", uiCnt[i]);
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
		uiCnt[TitleUninit]++;
		break;

	case SCENE_GAME:
		// �Q�[���V�[���̏I��
		UninitGame();
		GamePause::Uninit();
		uiCnt[GameUninit]++;

		break;

	case SCENE_RESULT:
		// ���U���g�V�[���̏I��
		UninitResult();
		uiCnt[ResultUninit]++;

		break;

	case SCENE_RANKING:
		// �����L���O�V�[���̏I��
		UninitRanking();
		uiCnt[RankingUninit]++;

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
		uiCnt[TitleInit]++;

		break;

	case SCENE_GAME:
		// �Q�[���V�[���̏�����
		InitGame();
		GamePause::Init();
		uiCnt[GameInit]++;

		break;

	case SCENE_RESULT:
		// ���U���g�V�[���̏�����
		InitResult();
		uiCnt[ResultInit]++;

		break;

	case SCENE_RANKING:
		// �����L���O�V�[���̏�����
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



