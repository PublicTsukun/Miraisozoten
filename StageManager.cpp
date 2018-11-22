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

#include "Library\Sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define STAGE00_TIMELIMIT	(3600)
#define STAGE01_TIMELIMIT	(180)
#define STAGE02_TIMELIMIT	(120)
#define FEVER_TIMELIMIT		(120)

//*****************************************************************************
// 列挙型
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
// プロトタイプ宣言
//*****************************************************************************
//void NextStage(void);
void ResetStage(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
STAGE StageWk;		// ワーク


#define GAME_SOUND_MAX	(2)
const char *GameSoundFile[]=
{
	"data/BGM/秋葉原ステージ音源.wav",
	"data/BGM/ライブハウスステージ音源（ボーナス）.wav",
};
DirectSound GameSound[GAME_SOUND_MAX];

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
	s->freeze = TRUE;
	s->end = FALSE;

	s->fever = FALSE;

	// パラメータ設定
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
// 初期化処理
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
// 更新処理
//=============================================================================
void UpdateStage(void)
{
	STAGE *s = GetStage();

	// ポース、テスト用
	if (s->freeze == FALSE && s->end == FALSE)
	{
		// ポース
		if (GetKeyboardTrigger(DIK_P))
		{
			FreezeStage();
		}

		// タイマーカウントアップ
		s->timer++;
	}
	else if (s->freeze == TRUE && s->end == FALSE)
	{
		// 再開
		if (GetKeyboardTrigger(DIK_P))
		{
			UnFreezeStage();
		}

	}

	// エネミースポーン
	EnemySpawner();

	// フィーバータイム
	BasiliskTime();

	// ステージ終了、チェック
	EndOfStage();

	// テスト用
	PrintDebugProcess("No: %d\n", s->no);
	PrintDebugProcess("Timer: %d\n", s->timer);
	PrintDebugProcess("End: %d\n", s->end);

	PrintDebugProcess("Fever: %d\n", s->fever);


}

//=============================================================================
// 凍結
//=============================================================================
void FreezeStage(void)
{
	STAGE *s = GetStage();

	s->freeze = TRUE;
}

//=============================================================================
// 解凍
//=============================================================================
void UnFreezeStage(void)
{
	STAGE *s = GetStage();

	s->freeze = FALSE;
}

//=============================================================================
// ステージ終了
//=============================================================================
void EndOfStage(void)
{
	STAGE *s = GetStage();
	
	if (s->end == FALSE)
	{
		// 終了条件を設定　現：タイムリミット
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

	// 次のステージ
	if (s->end == TRUE)
	{
		if (GetKeyboardTrigger(DIK_N))
		{
			// NEXT STAGE or GAME OVER
			s->no += 1;

			// パラメータリセット
			ResetStage();

			// 再開
			UnFreezeStage();
		}
	}
}

//=============================================================================
// リセット
//=============================================================================
void ResetStage(void)
{
	STAGE *s = GetStage();

	s->timer = 0;
	s->end = FALSE;
	s->fever = FALSE;
}

//=============================================================================
// ステージ番号の設定（未完成）
//=============================================================================
void SetStage(void)
{

}

//=============================================================================
// フィーバータイム
//=============================================================================
void BasiliskTime(void)
{
	STAGE *s = GetStage();

	s->fever = GetFiver();//フィーバー状態の取得

	//================================//================================
	// 通常
	//================================
	
	// 効果、ここで追加



	//================================//================================



	//================================//================================
	// フィーバー
	//================================
	if (s->fever == TRUE)
	{
		// 効果、ここで追加
		GameSound[1].Play(E_DS8_FLAG_LOOP, 0);
	}
	else
	{
		GameSound[1].Stop();
	}
	//================================//================================
}

//=============================================================================
// エネミースポーン
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
