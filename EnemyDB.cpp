//=============================================================================
//
// �G�l�~�[�f�[�^�x�[�X [EnemyDB.cpp]
// Author : �v�F��
//
//=============================================================================
#include "EnemyDB.h"

#include "enemyRE.h"

//*****************************************************************************
// �N���X��`
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
// �O���[�o���ϐ�
//*****************************************************************************
EnemyDB EnemyDBWk[E_TYPE_MAX];

//=============================================================================
// �擾
//=============================================================================
EnemyDB *GetEnemyDB(int no)
{
	return &EnemyDBWk[no];
}

//=============================================================================
// �������i�p�����[�^�ݒ�j
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