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
#define ENEMY_MAX (128)	// enemy最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	bool use;		// 使用しているかどうか
	Vector3 pos;	// 位置
	Vector3 rot;	// 回転

	int timer;		// タイマー
	int ptn;		// 行動パターン

	int hp;			// HP

} ENEMY;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemyRE(void);
void UninitEnemyRE(void);
void UpdateEnemyRE(void);
void DrawEnemyRE(void);

ENEMY *GetEnemyRE(int no);

void SetEnemyRE(Vector3 Self, Vector3 Tgt);
void VanishEnemyRE(int no);


#endif