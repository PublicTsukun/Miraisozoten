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
	//float wid;		// size Z

	int apr;		// 出現タイミング（再）

	int status;		// 状態
	int timer;		// タイマー
	
	int type;		// 種類
	int hp;			// HP
	int score;		// 点数

	

} ENEMY;

//*****************************************************************************
// 列挙型
//*****************************************************************************
enum E_TYPE
{
	E_TYPE_CHILD = 0,
	E_TYPE_MAID,
	E_TYPE_OTAKU,
	E_TYPE_AA,
	E_TYPE_JK,
	E_TYPE_AMERICAN,
	E_TYPE_ASTRONAUT,
	E_TYPE_ALIEN,
	E_TYPE_UFO,

	E_TYPE_MAX,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemyRE(void);
void UninitEnemyRE(void);
void UpdateEnemyRE(void);
void DrawEnemyRE(void);
ENEMY *GetEnemyRE(int no);

// 登場／退場
void EnemyREOnStage(int no);

// 撃破数
int GetYouDefeated(void);
void SetYouDefeated(int value);
void ResetYouDefeated(void);

// テスト用
void VanisnAllEnenyRE(void);

#endif