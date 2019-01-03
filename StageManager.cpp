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

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 列挙型
//*****************************************************************************
enum EN_STAGE_STATUS
{
	STAGE_STATUS_NULL = 0,
	STAGE_STATUS_NORMAL,
	STAGE_STATUS_CHANGING,
	STAGE_STATUS_END,

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetEnemy(int no);

void EnemySpawner(void);

void CheckChangeStage(void);
void NextStageEfx(void);
void NextStage(void);
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
	STAGE *s = GetStage();

	s->no = 0;

	s->timer = 0;
	s->nextStage = -1;

	s->status = STAGE_STATUS_NORMAL;

	SetEnemyRE(s->timer + 180);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStage(void)
{
	STAGE *stage = GetStage();

	// チェック
	CheckChangeStage();

	// エネミースポーン
	EnemySpawner();
	
	// カウントアップタイマー
	CountUpTimer();

	//PrintDebugProcess("stage status: %d\n", stage->status);
	//PrintDebugProcess("stage timer: %d\n", stage->timer);
	//PrintDebugProcess("stage next: %d\n", stage->nextStage);

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
// 次のステージに移行（演出効果）
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

		stage->status = STAGE_STATUS_NORMAL;
		stage->nextStage = -1;
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

	if (stage->status == STAGE_STATUS_NORMAL ||
		stage->status == STAGE_STATUS_CHANGING)
	{
		stage->timer++;
	}
}