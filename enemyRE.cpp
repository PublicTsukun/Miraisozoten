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

#include "Library\Input.h"

#include <time.h>


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
	void SetTexture(void);
	void ChangeTexture(void);
	void ResetTexture(void);
};

void CEnemyRE::ChangeTexture(float row, float col, float rowMax, float colMax)
{
	const float rowN = (1.0f / rowMax);		// �s�𓙕��ɕ�����
	const float colN = (1.0f / colMax);		// ��𓙕��ɕ�����

	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].uv = Vector2(col * colN			, row * rowN);
	pVtx[1].uv = Vector2((col + 1) * colN	, row * rowN);
	pVtx[2].uv = Vector2(col * colN			, ((row + 1) * rowN));
	pVtx[3].uv = Vector2((col + 1) * colN	, ((row + 1) * rowN));

	// ���_�f�[�^���A�����b�N����
	VtxBuff->Unlock();
}

void CEnemyRE::SetTexture(void)
{
	CEnemyRE::ChangeTexture(0, 0, 1, 2);
}

void CEnemyRE::ChangeTexture(void)
{
	CEnemyRE::ChangeTexture(0, 1, 1, 2);
}

void CEnemyRE::ResetTexture(void)
{
	CEnemyRE::SetTexture();
}

//*****************************************************************************
// �񋓌^
//*****************************************************************************
enum E_TEX
{
	E_TEX_CHILD = 0,
	E_TEX_MAID,
	E_TEX_OTAKU,

	E_TEX_MAX,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CollisionEnemyRE(void);
void DamageDealEnemyRE(int Eno, int Vno);
void ResetEnemyRE(void);

void SetType(int ENo, int type);
void SetPos(int ENo, float x, float y, float z);
void SetAppear(int ENo, int time);
void SetParameter00(void);
void SetParameter01(void);

void TestEnemyRE(void);
void TrapFactory(int apr, int num);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
char *FileEnemy[] =
{
	"data/TEXTURE/character/01_01_child.png",
	"data/TEXTURE/character/01_02_maid.png",
	"data/TEXTURE/character/01_03_otaku.png",
};

ENEMY EnemyREWk[ENEMY_MAX];		// ���[�N
CEnemyRE EnemyRE[ENEMY_MAX];

int YOUDEFEATED;

//=============================================================================
// ����������
//=============================================================================
void InitEnemyRE(void)
{
	ENEMY *e = GetEnemyRE(0);

	// �������p�ϐ�
	const Vector2 size = Vector2(96, 96);

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

	//(e + 1)->pos = Vector3(-400.0f, 150.0f, -50.0f);
	//(e + 2)->pos = Vector3(-200.0f, 50.0f, 50.0f);

	SetParameter00();

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

	TestEnemyRE();


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
		EnemyRE[Eno].ChangeTexture(0, 1, 1, 2);

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

//=============================================================================
// �p�����[�^�ݒ�i�����Œ����j
//============================================================================='
void SetParameter00(void)
{
	//int ENo;	// �G�l�~�[�ԍ�

	//int apr;	// �o���^�C�~���O
	//int type;	// 0 - E_TEX_MAX
	//float x;	// -280 - 280
	//float z;	// 0 - 600

	////================================//================================
	//ENo = 0;					// �w��
	//apr = 30;
	//type = rand() % E_TEX_MAX;



	//SetType(ENo, type);	// ��ސݒ�
	//SetPos(ENo, -260, 100, 0);	// �ʒu�ݒ�
	//SetAppear(ENo, apr);			// �o���^�C�~���O�ݒ�
	////================================

	srand((unsigned)time(NULL));

	TrapFactory(30, 4);
	TrapFactory(60, 2);


}

//=============================================================================
// �e�N�X�`���^�C�v�ݒ�
//============================================================================='
void SetType(int ENo, int type)
{
	ENEMY *e = GetEnemyRE(0);

	EnemyRE[ENo].LoadTexture(FileEnemy[type]);
	EnemyRE[ENo].SetTexture();

}

//=============================================================================
// �ʒu�ݒ�
//============================================================================='
void SetPos(int ENo, float x, float y, float z)
{
	ENEMY *e = GetEnemyRE(0);

	(e + ENo)->pos = Vector3(x, y, z);
	EnemyRE[ENo].LoadObjectStatus((e + 0)->pos, (e + 0)->rot);

}

//=============================================================================
// �o���^�C�~���O�ݒ�
//============================================================================='
void SetAppear(int ENo, int time)
{
	ENEMY *e = GetEnemyRE(0);

	(e + ENo)->apr = time;
}

//=============================================================================
// �G�l�~�[�����i���}�[�u�j
//============================================================================='
void TrapFactory(int apr, int num)
{
	ENEMY *e = GetEnemyRE(0);

	int type;
	float x;
	float z;

	// ���g�p�̃I�u�W�F�N�g��{��
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			if ((e + j)->apr == -1)
			{
				(e + j)->apr = apr;

				type = rand() % E_TEX_MAX;
				SetType(j, type);		// ��ސݒ�

				x = float(rand() % 560 - 280);
				z = float(rand() % 600);
				SetPos(j, x, 100, z);	// �ʒu�ݒ�
				break;
			}
		}
	}

}


//=============================================================================
// �e�X�g�p
//============================================================================='
void TestEnemyRE(void)
{
	ENEMY *e = GetEnemyRE(0);

	float vel = 10.0f;

	if (GetKeyboardPress(DIK_NUMPAD8))
	{
		e->pos.z += vel;
	}


	if (GetKeyboardPress(DIK_NUMPAD5))
	{
		e->pos.z -= vel;

	}

	if (GetKeyboardPress(DIK_NUMPAD4))
	{
		e->pos.x -= vel;

	}

	if (GetKeyboardPress(DIK_NUMPAD6))
	{
		e->pos.x += vel;

	}

	if (GetKeyboardPress(DIK_NUMPAD7))
	{
		e->pos.y -= vel;
	}

	if (GetKeyboardPress(DIK_NUMPAD9))
	{
		e->pos.y += vel;
	}

	PrintDebugProcess("pos: %f %f %f\n", e->pos.x, e->pos.y, e->pos.z);
	PrintDebugProcess("pos: %f %f %f\n", (e + 1)->pos.x, (e + 1)->pos.y, (e + 1)->pos.z);
	PrintDebugProcess("pos: %f %f %f\n", (e + 2)->pos.x, (e + 2)->pos.y, (e + 2)->pos.z);

}



