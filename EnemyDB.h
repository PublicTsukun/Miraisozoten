//=============================================================================
//
// エネミーデータベース [EnemyDB.h]
// Author : 宋彦霖
//
//=============================================================================
#ifndef _ENEMYDB_INCLUDE_H_
#define _ENEMYDB_INCLUDE_H_

//*****************************************************************************
// クラス定義
//*****************************************************************************
class EnemyDB
{
private:
	int hp;
	int score;
	float bonus;
	
public:
	void SetHP(int hp);
	void SetScore(int score);
	void SetBonus(float bonus);

	int GetHP(void);
	int GetScore(void);
	float GetBonus(void);
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
EnemyDB *GetEnemyDB(int no);
void InitEnemyDB(void);

#endif