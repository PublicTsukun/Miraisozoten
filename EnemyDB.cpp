//=============================================================================
//
// エネミーデータベース [EnemyDB.cpp]
// Author : 宋彦霖
//
//=============================================================================
#include "EnemyDB.h"

#include "enemyRE.h"

//*****************************************************************************
// クラス定義
//*****************************************************************************
void EnemyDB::SetHP(int hp)
{
	this->hp = hp;
}

void EnemyDB::SetScore(int score)
{
	this->score = score;
}

int EnemyDB::GetHP(void)
{
	return this->hp;
}

int EnemyDB::GetScore(void) 
{
	return this->score;
}

//*****************************************************************************
// グローバル変数
//*****************************************************************************
EnemyDB EnemyDBWk[E_TYPE_MAX];

//=============================================================================
// 取得
//=============================================================================
EnemyDB *GetEnemyDB(int no)
{
	return &EnemyDBWk[no];
}

//=============================================================================
// 初期化（パラメータ設定）
//=============================================================================
void InitEnemyDB(void)
{
	EnemyDBWk[E_TYPE_CHILD].SetHP(5);
	EnemyDBWk[E_TYPE_CHILD].SetScore(100);

	EnemyDBWk[E_TYPE_MAID].SetHP(50);
	EnemyDBWk[E_TYPE_MAID].SetScore(1000);

	EnemyDBWk[E_TYPE_OTAKU].SetHP(15);
	EnemyDBWk[E_TYPE_OTAKU].SetScore(500);

	EnemyDBWk[E_TYPE_AA].SetHP(5);
	EnemyDBWk[E_TYPE_AA].SetScore(100);

	EnemyDBWk[E_TYPE_JK].SetHP(50);
	EnemyDBWk[E_TYPE_JK].SetScore(1000);

	EnemyDBWk[E_TYPE_AMERICAN].SetHP(15);
	EnemyDBWk[E_TYPE_AMERICAN].SetScore(500);

	EnemyDBWk[E_TYPE_ASTRONAUT].SetHP(5);
	EnemyDBWk[E_TYPE_ASTRONAUT].SetScore(100);

	EnemyDBWk[E_TYPE_ALIEN].SetHP(50);
	EnemyDBWk[E_TYPE_ALIEN].SetScore(1000);

	EnemyDBWk[E_TYPE_UFO].SetHP(15);
	EnemyDBWk[E_TYPE_UFO].SetScore(500);
}