#include "SceneManager.h"
#include "Result.h"
#include "Title.h"


SCENE SceneManager::GameScene = SCENE_MAX;


//----�X�V--------
int  SceneManager::Update()
{
	switch (GameScene)
	{
	case SCENE_TITLE:

		// �^�C�g���V�[���̍X�V����


		if (false)
		{
			Scene::SetScene(SCENE_GAME);
		}

		break;

	case SCENE_GAME:

		// �Q�[���V�[���̍X�V


		if (false)
		{
			Scene::SetScene(SCENE_RESULT);
		}

		break;

	case SCENE_RESULT:

		// ���U���g�V�[���̍X�V����


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

//----�`��--------
void SceneManager::Draw()
{
	switch (GameScene)
	{
	case SCENE_TITLE:

		// �^�C�g���V�[���̕`�揈��


		break;

	case SCENE_GAME:

		// �Q�[���V�[���̕`�揈��


		break;

	case SCENE_RESULT:

		// ���U���g�̕`�揈��


		break;

	default:
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

	/* ���݂̃V�[���̂��Еt�� */
	switch (GameScene)
	{
	case SCENE_TITLE:

		// �^�C�g���V�[���̏I������


		break;

	case SCENE_GAME:

		// �Q�[���V�[���̏I������ ���U���g�ɓ���
		//UninitGame();

		// �|�[�Y�V�[���̏I������

		// �J�b�g�C���V�[���̏I������

		break;

	case SCENE_RESULT:

		// ���U���g�V�[���̏I������


		// �Q�[���V�[���̏I������


		break;

	default:
		break;
	}

	/* ���̃V�[���̏��� */
	switch (scene)
	{
	case SCENE_TITLE:

		// �^�C�g���V�[���̏�����


		GameScene = SCENE_TITLE;

		break;

	case SCENE_GAME:

		// �Q�[���V�[���̏�����


		GameScene = SCENE_GAME;

		break;

	case SCENE_RESULT:

		// ���U���g�V�[���̏�����


		GameScene = SCENE_RESULT;

		break;

	default:
		return GameScene;
		break;
	}

	GameScene = scene;

	return GameScene;
}



