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

#include "field.h"

#include "DefeatCounter.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �񋓌^
//*****************************************************************************
enum EN_STAGE_STATUS
{
	STAGE_STATUS_NULL = 0,
	STAGE_STATUS_NORMAL,
	STAGE_STATUS_CHANGING,
	STAGE_STATUS_END,

};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void SetEnemy(int no);

void EnemySpawner(void);

void CheckChangeStage(void);
void NextStageEfx(void);
void NextStage(void);
void GameOver(void);

void CountUpTimer(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
STAGE StageWk;		// ���[�N

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
	s->nextStage = -1;

	s->status = STAGE_STATUS_NORMAL;

	SetEnemyRE(s->timer + 180);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStage(void)
{
	STAGE *stage = GetStage();

	// �`�F�b�N
	CheckChangeStage();

	// �G�l�~�[�X�|�[��
	EnemySpawner();
	
	// �J�E���g�A�b�v�^�C�}�[
	CountUpTimer();

	//PrintDebugProcess("stage status: %d\n", stage->status);
	//PrintDebugProcess("stage timer: %d\n", stage->timer);
	//PrintDebugProcess("stage next: %d\n", stage->nextStage);

}

//=============================================================================
// �G�l�~�[�̐���
//=============================================================================
void EnemySpawner(void)
{
	ENEMY *e = GetEnemyRE(0);
	STAGE *s = GetStage();

	if (s->status == STAGE_STATUS_NORMAL)
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (s->timer == (e + i)->apr)
			{
				EnemyREOnStage(i);
			}
		}
	}

}

//=============================================================================
// ���Ԏ��`�F�b�N�i�X�e�[�W�J�ڊ֌W�j
//=============================================================================
void CheckChangeStage(void)
{
	DefeatCounter *DefeatCounter = GetDefeatCounter(0);
	int CheckDefeat = GetAllDefeat();

	STAGE *stage = GetStage();

	if (CheckDefeat == 1 &&
		stage->no == 0)
	{
		NextStageEfx();
	}

	if (CheckDefeat == 2 &&
		stage->no == 1)
	{
		NextStageEfx();
	}

	if (stage->timer == stage->nextStage)
	{
		NextStage();
	}

	if (stage->timer >= 5400)
	{
		GameOver();
	}

}

//=============================================================================
// ���̃X�e�[�W�Ɉڍs�i���o���ʁj
//=============================================================================
void NextStageEfx(void)
{
	STAGE *stage = GetStage();

	if (stage->status == STAGE_STATUS_NORMAL)
	{
		stage->status = STAGE_STATUS_CHANGING;

		stage->nextStage = stage->timer + 120;

		ClearAllEnemyRE();
	}

}

//=============================================================================
// ���̃X�e�[�W�Ɉڍs
//=============================================================================
void NextStage(void)
{
	STAGE *stage = GetStage();

	if (stage->status == STAGE_STATUS_CHANGING)
	{
		stage->no += 1;
		stage->no %= 3;
		SetFeildTex(stage->no);

		ResetAllEnemyRE();
		SetEnemyRE(stage->timer);

		stage->status = STAGE_STATUS_NORMAL;
		stage->nextStage = -1;
	}

}

//=============================================================================
// �Q�[���I�[�o�[
//=============================================================================
void GameOver(void)
{
	STAGE *stage = GetStage();

	stage->status = STAGE_STATUS_END;
}

//=============================================================================
// �J�E���g�A�b�v�^�C�}�[
//=============================================================================
void CountUpTimer(void)
{
	STAGE *stage = GetStage();

	if (stage->status == STAGE_STATUS_NORMAL ||
		stage->status == STAGE_STATUS_CHANGING)
	{
		stage->timer++;
	}
}