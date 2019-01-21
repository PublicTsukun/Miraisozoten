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
// 列挙型
//*****************************************************************************
enum EN_STAGE
{
	STAGE_01_AKIBA = 0,
	STAGE_02_USA,
	STAGE_03_SPACE,

	STAGE_MAX,
};

enum EN_STAGE_STATUS
{
	STAGE_STATUS_NULL = 0,
	STAGE_STATUS_NORMAL,
	STAGE_STATUS_CHANGING,
	STAGE_STATUS_END,

};

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	int no;

	// 時間制御系
	int timer;
	int timerEfx;
	int nextStage;

	// 状態制御系
	int status;

} STAGE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
STAGE *GetStage(void);

void InitStage(void);
void UpdateStage(void);

void GameStart(void);
void GameStop(void);

#endif