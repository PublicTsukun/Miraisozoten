//=============================================================================
//
// パラメータ管理 [S-Editor.h]
// Author : 宋彦霖
//
//=============================================================================
#ifndef _SEDITOR_INCLUDE_H_
#define _SEDITOR_INCLUDE_H_

#include "Library/Vector.h"
#include <d3dx9.h>
#include <Windows.h>
#include "timer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

// 発射所要音量
#define VOICETEN_SHOT_VOL		(ENERGY_MIN)	

// Voiceten Type 音量設定
#define VOICETEN_TYPE_VOL_01	(ENERGY_CORD * 3)

// Voiceten Type 音量設定
#define VOICETEN_TYPE_VOL_02	(ENERGY_CORD * 6)

// 間隔で敵を生成（frame）
#define ENEMY_SPAWN_DELAY_01	(60)

// 間隔で敵を生成（frame）
#define ENEMY_SPAWN_DELAY_02	(120)

// 間隔で敵を再生成（frame）
#define ENEMY_DEFEAT_DELAY		(120)

// 間隔で敵を再生成（フィーバー状態）（frame）
#define ENEMY_DEFEAT_FEVER		(ENEMY_DEFEAT_DELAY / 2)

// ステージ最大時間（frame）
#define STAGE_TIME				(START_TIME * 60)

// ステージ01クリア条件（撃破数）
#define STAGE_NORMA_01			(10)

// ステージ02クリア条件（撃破数）
#define STAGE_NORMA_02			(25)

// 命中エフェクトの大きさ
#define EFX_SIZE_HIT			(96.0f)

// 撃破エフェクトの大きさ
#define EFX_SIZE_DEFEAT			(96.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

#endif