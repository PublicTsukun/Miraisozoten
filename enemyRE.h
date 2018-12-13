//=============================================================================
//
// enemy�����E�� [enemyRE.h]
// Author : �v�F��
//
//=============================================================================
#ifndef _ENEMYRE_INCLUDE_H_
#define _ENEMYRE_INCLUDE_H_

#include "Library/Vector.h"
#include <Windows.h>
#include <d3dx9.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_MAX (10)	// enemy�ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	bool use;		// �g�p���Ă��邩�ǂ���
	Vector3 pos;	// �ʒu
	Vector3 rot;	// ��]

	float len;		// size X
	float hei;		// size Y
	float wid;		// size Z

	int timer;		// �^�C�}�[
	int ptn;		// �s���p�^�[��

	int apr;		// �o���^�C�~���O

	int type;		// ���

	int hp;			// HP

	int status;		// ���

	int score;		// �_��

} ENEMY;

//*****************************************************************************
// �v���g�^�C�v�錾
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