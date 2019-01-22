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

#include "S-Editor.h"

#include "StageSwitch.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �񋓌^
//*****************************************************************************



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void EnemySpawner(void);

void CheckChangeStage(void);
void NextStageEfx(void);
void NextStage(void);
void NextStage01(void);
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
	STAGE *stage = GetStage();

	stage->no = 0;

	stage->timer = 0;
	stage->timerEfx = 0;

	stage->status = STAGE_STATUS_NULL;

	SetEnemyRE(stage->timer);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStage(void)
{
	// �`�F�b�N
	CheckChangeStage();

	// �G�l�~�[�X�|�[��
	EnemySpawner();
	
	// �J�E���g�A�b�v�^�C�}�[
	CountUpTimer();

	STAGE *stage = GetStage();	
	PrintDebugProcess("stage timer: %d\n", stage->timer);
	PrintDebugProcess("stage status: %d\n", stage->status);

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
	int CheckDefeat = GetAllDefeat();

	STAGE *stage = GetStage();

	if (CheckDefeat >= STAGE_NORMA_01 &&
		stage->no == STAGE_01_AKIBA)
	{
		NextStageEfx();
	}

	if (CheckDefeat >= STAGE_NORMA_02 &&
		stage->no == STAGE_02_USA)
	{
		NextStageEfx();
	}

	if (stage->timerEfx == STAGE_CHANGE_EFX_TIME_01)
	{
		NextStage();
	}

	if (stage->timerEfx == STAGE_CHANGE_EFX_TIME_02)
	{
		NextStage01();
	}

	if (stage->timer >= STAGE_TIME)
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
		
		CameraShutter(stage->no+1);

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

		//stage->status = STAGE_STATUS_NORMAL;
		//stage->timerEfx = 0;
	}
}

void NextStage01(void)
{
	STAGE *stage = GetStage();

	if (stage->status == STAGE_STATUS_CHANGING)
	{
		stage->status = STAGE_STATUS_NORMAL;
		stage->timerEfx = 0;
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

	if (stage->status == STAGE_STATUS_NORMAL)
	{
		stage->timer++;
	}

	if (stage->status == STAGE_STATUS_CHANGING)
	{
		stage->timerEfx++;
	}
}

//=============================================================================
// �Q�[���X�^�[�g
//=============================================================================
void GameStart(void)
{
	STAGE *stage = GetStage();

	stage->status = STAGE_STATUS_NORMAL;

}

//================================================================================
// �Q�[���ꎞ��~
//===============================================================================
void GameStop(void)
{
	STAGE *stage = GetStage();

	stage->status = STAGE_STATUS_NULL;

}