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
#define ENEMY_MAX (3)	// enemy�ő吔

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

	int stage;
	int apr;

	int hp;			// HP

} ENEMY;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemyRE(void);
void UninitEnemyRE(void);
void UpdateEnemyRE(void);
void DrawEnemyRE(void);

ENEMY *GetEnemyRE(int no);

// �\��@�\�F�I�u�W�F�N�g�ݒu
// �\��@�\�F�I�u�W�F�N�g����
// �@�@�@�@���I�u�W�F�N�g�ď�����

#endif