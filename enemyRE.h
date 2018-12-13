//=============================================================================
//
// enemy処理・改 [enemyRE.h]
// Author : 宋彦霖
//
//=============================================================================
#ifndef _ENEMYRE_INCLUDE_H_
#define _ENEMYRE_INCLUDE_H_

#include "Library/Vector.h"
#include <Windows.h>
#include <d3dx9.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENEMY_MAX (10)	// enemy最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	bool use;		// 使用しているかどうか
	Vector3 pos;	// 位置
	Vector3 rot;	// 回転

	float len;		// size X
	float hei;		// size Y
	float wid;		// size Z

	int timer;		// タイマー
	int ptn;		// 行動パターン

	int apr;		// 出現タイミング

	int type;		// 種類

	int hp;			// HP

	int status;		// 状態

	int score;		// 点数

} ENEMY;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemyRE(void);
void UninitEnemyRE(void);
void UpdateEnemyRE(void);
void DrawEnemyRE(void);

ENEMY *GetEnemyRE(int no);

void VanisnEnenyRE(int no);
void VanisnAllEnenyRE(void);

void EnemyREOnStage(int no);

void DefeatEnemyRE(int no);



int GetYouDefeated(void);
void SetYouDefeated(int value);
void ResetYouDefeated(void);

#endif