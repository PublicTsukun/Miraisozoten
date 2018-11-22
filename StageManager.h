//=============================================================================
//
// ステージ管理 [StageManager.h]
// Author : 宋彦霖
//
//=============================================================================
#ifndef _STAGEMENEGER_INCLUDE_H_
#define _STAGEMENEGER_INCLUDE_H_

#include "Library/Vector.h"
#include <Windows.h>
#include <d3dx9.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define STAGE_MAX (3)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	int no;
	int timer;
	bool freeze;
	bool end;
	int timerLimit[STAGE_MAX];

	//int timerF;
	bool fever;

} STAGE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
STAGE *GetStage(void);

void InitStage(void);
void UpdateStage(void);

void FreezeStage(void);
void UnFreezeStage(void);

void EndOfStage(void);

void SetStage(void);

void BasiliskTime(void);

void EnemySpawner(void);

#endif