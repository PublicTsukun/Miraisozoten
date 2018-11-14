//=============================================================================
//
// enemy�����E�� [enemyRE.cpp]
// Author : �v�F��
//
//=============================================================================
#include "enemyRE.h"

#include "Library/ObjectBase3D.h"
#include "HitCheck.h"

#include "Library/DebugProcess.h"
#include "voiceten.h"
#include "score.h"
#include "UIBonus.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_HP			(2)
#define ENEMY_SCOREBONUS	(1)
#define ENEMY_GAUGEBONUS	(50)
#define ENEMY_D_SCOREBONUS	(10)
#define ENEMY_D_GAUGEBONUS	(200)

#define ENEMY_COLI_LEN		(24.0f)
#define ENEMY_COLI_HEI		(24.0f)
#define ENEMY_COLI_WID		(5.0f)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CEnemyRE : public C3DPolygonObject
{
public:
	void ChangeTexture(float row, float col, float rowMax, float colMax);
};

void CEnemyRE::ChangeTexture(float row, float col, float rowMax, float colMax)
{
	const float rowN = (1.0f / rowMax);		// �s�𓙕��ɕ�����
	const float colN = (1.0f / colMax);		// ��𓙕��ɕ�����

	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].uv = Vector2(col * colN, row * rowN);
	pVtx[1].uv = Vector2((col + 1) * colN, row * rowN);
	pVtx[2].uv = Vector2(col * colN, ((row + 1) * rowN));
	pVtx[3].uv = Vector2((col + 1) * colN, ((row + 1) * rowN));

	// ���_�f�[�^���A�����b�N����
	VtxBuff->Unlock();
}

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CollisionEnemyRE(void);
void DamageDealEnemyRE(int Eno, int Vno);
void ResetEnemyRE(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
ENEMY EnemyREWk[ENEMY_MAX];		// ���[�N

char *FileEnemy[] =
{
	"data/���/boss.png",
	"data/���/tttt.png",
};

CEnemyRE EnemyRE[ENEMY_MAX];

int YOUDEFEATED;



//=============================================================================
// ����������
//=============================================================================
void InitEnemyRE(void)
{
	ENEMY *e = GetEnemyRE(0);

	// �������p�ϐ�
	const Vector2 size = Vector2(48, 48);

	// �S�p�����[�^������
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		(e + i)->use = FALSE;
		(e + i)->pos = Vector3(0.0f, 0.0f, 0.0f);
		(e + i)->rot = Vector3(0.0f, 0.0f, 0.0f);

		(e + i)->timer = 0;
		(e + i)->ptn = 0;

		(e + i)->apr = -1;

		(e + i)->hp = ENEMY_HP;

		EnemyRE[i].Init((e + i)->pos, size);
		EnemyRE[i].LoadTexture(FileEnemy[0]);

	}

	ResetYouDefeated();

	// �ʃp�����[�^�ݒ�
	//(e + 0)->use = TRUE;
	//(e + 0)->pos = Vector3(-300.0f, 100.0f, 0.0f);

	//(e + 1)->use = TRUE;
	//(e + 1)->pos = Vector3(-400.0f, 150.0f, -50.0f);
	//EnemyRE[1].LoadTexture(FileEnemy[1]);

	//(e + 2)->use = TRUE;
	//(e + 2)->pos = Vector3(-200.0f, 50.0f, 50.0f);
	//EnemyRE[2].LoadTexture(FileEnemy[1]);

	(e + 0)->apr = 30;
	(e + 0)->pos = Vector3(-300.0f, 100.0f, 0.0f);
	EnemyRE[0].LoadObjectStatus((e + 0)->pos, (e + 0)->rot);
	EnemyRE[0].LoadObjectStatus((e + 0)->pos, (e + 0)->rot);
	EnemyRE[0].ChangeTexture(0, 0, 2, 2);

	(e + 1)->apr = 60;
	(e + 1)->pos = Vector3(-400.0f, 150.0f, -50.0f);
	EnemyRE[1].LoadTexture(FileEnemy[1]);
	EnemyRE[1].LoadObjectStatus((e + 1)->pos, (e + 1)->rot);
	EnemyRE[1].ChangeTexture(0, 0, 2, 2);


	(e + 2)->apr = 90;
	(e + 2)->pos = Vector3(-200.0f, 50.0f, 50.0f);
	EnemyRE[2].LoadTexture(FileEnemy[1]);
	EnemyRE[2].LoadObjectStatus((e + 2)->pos, (e + 2)->rot);
	EnemyRE[2].ChangeTexture(0, 0, 2, 2);



}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemyRE(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		EnemyRE[i].Release();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemyRE(void)
{
	ENEMY *e = GetEnemyRE(0);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if ((e + i)->use == TRUE)
		{
			// �Փ˔���
			CollisionEnemyRE();

			// �X�V�����i�ʒu�A��]�j
			EnemyRE[i].LoadObjectStatus((e + i)->pos, (e + i)->rot);
			
			// �^�C�}�[�J�E���g�A�b�v
			(e + i)->timer++;

		}
	}

	PrintDebugProcess("���j��: %d\n", YOUDEFEATED);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemyRE(void)
{
	ENEMY *e = GetEnemyRE(0);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if ((e + i)->use == TRUE)
		{
			EnemyRE[i].Draw();
		}

	}
}

//=============================================================================
// �擾
//=============================================================================
ENEMY *GetEnemyRE(int no)
{
	return (&EnemyREWk[no]);
}

//=============================================================================
// �Փ˔���
//=============================================================================
void CollisionEnemyRE(void)
{
	VOICETEN *v = GetVoiceten(0);
	ENEMY *e = GetEnemyRE(0);

	// �Փ˔͈͐ݒ�(1)
	const float len = ENEMY_COLI_LEN;
	const float hei = ENEMY_COLI_HEI;
	const float wid = ENEMY_COLI_WID;

	for(int i = 0; i < ENEMY_MAX; i++, e++)
	{
		if (e->use == FALSE) continue;

		for (int j = 0; j < VOICETEN_MAX; j++, v++)
		{
			if (v->use == FALSE) continue;

			// �Փ˔͈͐ݒ�(2)
			Vector3 vA1 = v->pos;
			Vector3 vA2 = v->pos;
			Vector3 vB1 = e->pos;
			Vector3 vB2 = e->pos;

			vA1.x = v->pos.x - len;		// ��
			vA1.y = v->pos.y + hei;		// ��
			vA1.z = v->pos.z - wid;		// �O

			vA2.x = v->pos.x + len;		// �E
			vA2.y = v->pos.y - hei;		// ��
			vA2.z = v->pos.z + wid;		// ��

			vB1.x = e->pos.x - len;		// ��
			vB1.y = e->pos.y + hei;		// ��
			vB1.z = e->pos.z - wid;		// �O

			vB2.x = e->pos.x + len;		// �E
			vB2.y = e->pos.y - hei;		// ��
			vB2.z = e->pos.z + wid;		// ��

			// �`�F�b�N
			if ((vA2.x > vB1.x)
				&& (vB2.x > vA1.x)
				&& (vA2.y < vB1.y)
				&& (vB2.y < vA1.y)
				&& (vA2.z > vB1.z)
				&& (vB2.z > vA1.z)
				)
			{
				// �_���[�W�v�Z
				DamageDealEnemyRE(i, j);

				// �e����
				VanishVoiceten(j);

			}

		}
		
	}

}

//=============================================================================
// �_���[�W�v�Z
//=============================================================================
void DamageDealEnemyRE(int Eno, int Vno)
{
	VOICETEN *v = GetVoiceten(0);
	ENEMY *e = GetEnemyRE(0);

	// �_���[�W�v�Z
	(e + Eno)->hp -= (v + Vno)->atk;

	// ���j����
	if ((e + Eno)->hp <= 0)
	{
		VanisnEnenyRE(Eno);
	}
	else
	{
		// �e�N�X�`���ύX
		EnemyRE[Eno].ChangeTexture(1, 0, 2, 2);

		// �X�R�A�A�b�v
		AddScore(ENEMY_SCOREBONUS);

		// �Q�[�W�A�b�v
		AddGage(ENEMY_GAUGEBONUS);
	}

}

//=============================================================================
// ����
//=============================================================================
void VanisnEnenyRE(int no)
{
	ENEMY *e = GetEnemyRE(0);

	// ����
	(e + no)->use = FALSE;

	// ������
	(e + no)->hp = ENEMY_HP;
	(e + no)->timer = 0;

	//================================
	// �{�[�i�X
	//================================
	// �X�R�A�A�b�v
	AddScore(ENEMY_D_SCOREBONUS);

	// �Q�[�W�A�b�v
	AddGage(ENEMY_D_GAUGEBONUS);

	SetYouDefeated(1);
}

//=============================================================================
// �S���N���A
//=============================================================================
void VanisnAllEnenyRE(void)
{
	ENEMY *e = GetEnemyRE(0);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		// ����
		(e + i)->use = FALSE;

		// ������
		(e + i)->hp = ENEMY_HP;
		(e + i)->timer = 0;

	}

}

//=============================================================================
// �p�����[�^�ݒ�
//=============================================================================
void SetEnemyRE(int StageNO)
{
	ENEMY *e = GetEnemyRE(0);

	switch (StageNO)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}

}

//=============================================================================
// �o��
//=============================================================================
void EnemyREOnStage(int no)
{
	ENEMY *e = GetEnemyRE(0);

	(e + no)->use = TRUE;
}

//=============================================================================
// ���j���擾
//=============================================================================
int GetYouDefeated(void)
{
	return YOUDEFEATED;
}

//=============================================================================
// ���j���ݒ�
//=============================================================================
void SetYouDefeated(int value)
{
	YOUDEFEATED += value;
}

//=============================================================================
// ���j�����Z�b�g
//=============================================================================
void ResetYouDefeated(void) 
{
	SetYouDefeated(0);
}
