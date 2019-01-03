//=============================================================================
//
// �G�l�~�[�f�[�^�x�[�X [EnemyDB.h]
// Author : �v�F��
//
//=============================================================================
#ifndef _ENEMYDB_INCLUDE_H_
#define _ENEMYDB_INCLUDE_H_

//*****************************************************************************
// �N���X��`
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
// �v���g�^�C�v�錾
//*****************************************************************************
EnemyDB *GetEnemyDB(int no);
void InitEnemyDB(void);

#endif