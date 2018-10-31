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
#define ENEMY_MAX (128)	// enemy�ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	bool use;		// �g�p���Ă��邩�ǂ���
	Vector3 pos;	// �ʒu
	Vector3 rot;	// ��]

	int timer;		// �^�C�}�[
	int ptn;		// �s���p�^�[��

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

void SetEnemyRE(Vector3 Self, Vector3 Tgt);
void VanishEnemyRE(int no);


#endif