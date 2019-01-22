//=============================================================================
//
// ステージ管理 [StageManager.cpp]
// Author : 宋彦霖
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
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 列挙型
//*****************************************************************************



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void EnemySpawner(void);

void CheckChangeStage(void);
void NextStageEfx(void);
void NextStage(void);
void NextStage01(void);
void GameOver(void);

void CountUpTimer(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
STAGE StageWk;		// ワーク

//=============================================================================
// 取得
//=============================================================================
STAGE *GetStage(void)
{
	return (&StageWk);
}

//=============================================================================
// 初期化処理
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
// 更新処理
//=============================================================================
void UpdateStage(void)
{
	// チェック
	CheckChangeStage();

	// エネミースポーン
	EnemySpawner();
	
	// カウントアップタイマー
	CountUpTimer();

	STAGE *stage = GetStage();	
	PrintDebugProcess("stage timer: %d\n", stage->timer);
	PrintDebugProcess("stage status: %d\n", stage->status);

}

//=============================================================================
// エネミーの生成
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
// 時間軸チェック（ステージ遷移関係）
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
// 次のステージに移行（演出効果）
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
// 次のステージに移行
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
// ゲームオーバー
//=============================================================================
void GameOver(void)
{
	STAGE *stage = GetStage();

	stage->status = STAGE_STATUS_END;
}

//=============================================================================
// カウントアップタイマー
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
// ゲームスタート
//=============================================================================
void GameStart(void)
{
	STAGE *stage = GetStage();

	stage->status = STAGE_STATUS_NORMAL;

}

//================================================================================
// ゲーム一時停止
//===============================================================================
void GameStop(void)
{
	STAGE *stage = GetStage();

	stage->status = STAGE_STATUS_NULL;

}