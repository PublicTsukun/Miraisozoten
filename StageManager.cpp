//=============================================================================
//
// �X�e�[�W�Ǘ� [StageManager.cpp]
// Author : �v�F��
//
//=============================================================================
#include "StageManager.h"

#include "Library/DebugProcess.h"
#include "Library/Input.h"

#include "enemyRE.h"
#include "UIBonus.h"

#include "Library\Sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define STAGE00_TIMELIMIT	(3600)
#define STAGE01_TIMELIMIT	(180)
#define STAGE02_TIMELIMIT	(120)
#define FEVER_TIMELIMIT		(120)

//*****************************************************************************
// �񋓌^
//*****************************************************************************
//enum cursor
//{
//	SINGLE,
//	MULTI,
//	RANKING,
//	CURSORMAX
//
//};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//void NextStage(void);
void ResetStage(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
STAGE StageWk;		// ���[�N


#define GAME_SOUND_MAX	(2)
const char *GameSoundFile[]=
{
	"data/BGM/�H�t���X�e�[�W����.wav",
	"data/BGM/���C�u�n�E�X�X�e�[�W�����i�{�[�i�X�j.wav",
};
DirectSound GameSound[GAME_SOUND_MAX];

//=============================================================================
// �擾
//=============================================================================
STAGE *GetStage(void)
{
	return (&StageWk);
}

//=============================================================================
// ����������
//=============================================================================
void InitStage(void)
{
	STAGE *s = GetStage();

	s->no = 0;
	s->timer = 0;
	s->freeze = TRUE;
	s->end = FALSE;

	s->fever = FALSE;

	// �p�����[�^�ݒ�
	s->timerLimit[0] = STAGE00_TIMELIMIT;
	s->timerLimit[1] = STAGE01_TIMELIMIT;
	s->timerLimit[2] = STAGE02_TIMELIMIT;


	for (int i = 0; i < GAME_SOUND_MAX; i++)
	{
		GameSound[i].LoadSound(GameSoundFile[i]);
	}
	GameSound[0].Play(E_DS8_FLAG_LOOP, 0);
	GameSound[0].Volume(-1000);
}

//=============================================================================
// ����������
//=============================================================================
void UninitStage(void)
{

	GameSound[0].Stop();

	for (int i = 0; i < GAME_SOUND_MAX; i++)
	{
		GameSound[i].Release();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStage(void)
{
	STAGE *s = GetStage();

	// �|�[�X�A�e�X�g�p
	if (s->freeze == FALSE && s->end == FALSE)
	{
		// �|�[�X
		if (GetKeyboardTrigger(DIK_P))
		{
			FreezeStage();
		}

		// �^�C�}�[�J�E���g�A�b�v
		s->timer++;
	}
	else if (s->freeze == TRUE && s->end == FALSE)
	{
		// �ĊJ
		if (GetKeyboardTrigger(DIK_P))
		{
			UnFreezeStage();
		}

	}

	// �G�l�~�[�X�|�[��
	EnemySpawner();

	// �t�B�[�o�[�^�C��
	BasiliskTime();

	// �X�e�[�W�I���A�`�F�b�N
	EndOfStage();

	// �e�X�g�p
	PrintDebugProcess("No: %d\n", s->no);
	PrintDebugProcess("Timer: %d\n", s->timer);
	PrintDebugProcess("End: %d\n", s->end);

	PrintDebugProcess("Fever: %d\n", s->fever);


}

//=============================================================================
// ����
//=============================================================================
void FreezeStage(void)
{
	STAGE *s = GetStage();

	s->freeze = TRUE;
}

//=============================================================================
// ��
//=============================================================================
void UnFreezeStage(void)
{
	STAGE *s = GetStage();

	s->freeze = FALSE;
}

//=============================================================================
// �X�e�[�W�I��
//=============================================================================
void EndOfStage(void)
{
	STAGE *s = GetStage();
	
	if (s->end == FALSE)
	{
		// �I��������ݒ�@���F�^�C�����~�b�g
		switch (s->no)
		{
		case 0:
			if (s->timer == s->timerLimit[s->no])
			{
				s->freeze = TRUE;
				s->end = TRUE;
			}
			break;
		case 1:
			if (s->timer == s->timerLimit[s->no])
			{
				s->freeze = TRUE;
				s->end = TRUE;
			}
			break;
		case 2:
			if (s->timer == s->timerLimit[s->no])
			{
				s->freeze = TRUE;
				s->end = TRUE;
			}
			break;
		default:
			break;
		}
	}

	// ���̃X�e�[�W
	if (s->end == TRUE)
	{
		if (GetKeyboardTrigger(DIK_N))
		{
			// NEXT STAGE or GAME OVER
			s->no += 1;

			// �p�����[�^���Z�b�g
			ResetStage();

			// �ĊJ
			UnFreezeStage();
		}
	}
}

//=============================================================================
// ���Z�b�g
//=============================================================================
void ResetStage(void)
{
	STAGE *s = GetStage();

	s->timer = 0;
	s->end = FALSE;
	s->fever = FALSE;
}

//=============================================================================
// �X�e�[�W�ԍ��̐ݒ�i�������j
//=============================================================================
void SetStage(void)
{

}

//=============================================================================
// �t�B�[�o�[�^�C��
//=============================================================================
void BasiliskTime(void)
{
	STAGE *s = GetStage();

	s->fever = GetFiver();//�t�B�[�o�[��Ԃ̎擾

	//================================//================================
	// �ʏ�
	//================================
	
	// ���ʁA�����Œǉ�



	//================================//================================



	//================================//================================
	// �t�B�[�o�[
	//================================
	if (s->fever == TRUE)
	{
		// ���ʁA�����Œǉ�
		GameSound[1].Play(E_DS8_FLAG_LOOP, 0);
	}
	else
	{
		GameSound[1].Stop();
	}
	//================================//================================
}

//=============================================================================
// �G�l�~�[�X�|�[��
//=============================================================================
void EnemySpawner(void)
{
	ENEMY *e = GetEnemyRE(0);
	STAGE *s = GetStage();

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (s->timer == (e + i)->apr)
		{
			EnemyREOnStage(i);
		}
	}
}
