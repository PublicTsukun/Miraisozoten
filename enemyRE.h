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
	//float wid;		// size Z

	int posData;

	int apr;		// �o���^�C�~���O

	int status;		// ���
	int timer;		// �^�C�}�[
	
	int type;		// ���
	int hp;			// HP
	int score;		// �_��
	float bonus;		// �{�[�i�X

} ENEMY;

//*****************************************************************************
// �񋓌^
//*****************************************************************************
enum E_TYPE
{
	E_TYPE_CHILD = 0,
	E_TYPE_OTAKU,
	E_TYPE_MAID,
	E_TYPE_AA,
	E_TYPE_JK,
	E_TYPE_AMERICAN,
	E_TYPE_UFO,
	E_TYPE_ASTRONAUT,
	E_TYPE_ALIEN,

	E_TYPE_MAX,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemyRE(void);
void UninitEnemyRE(void);
void UpdateEnemyRE(void);
void DrawEnemyRE(void);
ENEMY *GetEnemyRE(int no);

// �o��
void SetEnemyRE(int time);
void EnemyREOnStage(int no);

void ClearAllEnemyRE(void);
void ResetAllEnemyRE(void);

// �e�X�g�p
void VanisnAllEnenyRE(void);
void TesterAtkEnemyRE(void);


#endif