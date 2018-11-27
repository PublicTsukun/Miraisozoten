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

#include "GameSound.h"

#include "StageManager.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENEMY_HP			(2)		// �������p
#define ENEMY_SCOREBONUS	(1)
#define ENEMY_GAUGEBONUS	(50)
#define ENEMY_D_SCOREBONUS	(10)
#define ENEMY_D_GAUGEBONUS	(200)

#define ENEMY_COLI_LEN		(48.0f)	// �����蔻�� x
#define ENEMY_COLI_HEI		(48.0f)	// �����蔻�� y
#define ENEMY_COLI_WID		(10.0f)	// �����蔻�� z

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
enum E_TYPE
{
	E_TYPE_CHILD = 0,
	E_TYPE_MAID,
	E_TYPE_OTAKU,

	E_TYPE_MAX,
};

enum E_STATUS
{
	E_STATUS_NULL = 0,
	E_STATUS_NORMAL,
	E_STATUS_DEFEATED,

	E_STATUS_MAX,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void CollisionEnemyRE(void);
void DamageDealEnemyRE(int Eno, int Vno);
//void ResetEnemyRE(void);

void SetType(int ENo, int type);
void SetPos(int ENo, float x, float y, float z);
void SetAppear(int ENo, int time);
void SetParameter00(void);
//void SetParameter01(void);

void TestEnemyRE(void);
void TrapFactory(int apr, int num);
void TrapFactory02(int apr, int num);

void CheckUptime(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
char *FileEnemy[] =
{
	"data/TEXTURE/character/01_01_child.png",
	"data/TEXTURE/character/01_02_maid.png",
	"data/TEXTURE/character/01_03_otaku.png",
};

// Enemy HP Database�AE_TYPE�ɑΉ�
int EnemyHp[] =
{
	5,		// CHILD
	50,		// MAID
	15,		// OTAKU
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

		(e + i)->status = 0;

		(e + i)->score = 0;

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

#ifdef _DEBUG

	TestEnemyRE();

#endif

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if ((e + i)->use == TRUE)
		{
			// �X�V�����i�ʒu�A��]�j
			EnemyRE[i].LoadObjectStatus((e + i)->pos, (e + i)->rot);
			
			// �^�C�}�[�J�E���g�A�b�v
			(e + i)->timer++;

			// �ғ����Ԍ���
			CheckUptime(i);

			switch ((e + i)->status)
			{
			case E_STATUS_NULL:
				break;

			case E_STATUS_NORMAL:

				// �Փ˔���
				CollisionEnemyRE();
				break;

			case E_STATUS_DEFEATED:

				// �A�j���[�V����
				break;

			default:
				break;

			}


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


				if (e->status == E_STATUS_NORMAL)
				{
					// �e����
					VanishVoiceten(j);
				}

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
	STAGE *s = GetStage();

	// �_���[�W�v�Z
	(e + Eno)->hp -= (v + Vno)->atk;

	// ���j����
	if ((e + Eno)->hp <= 0 &&
		(e + Eno)->status == E_STATUS_NORMAL)
	{
		(e + Eno)->status = E_STATUS_DEFEATED;

		(e + Eno)->timer = 0;

		// �e�N�X�`���ύX
		EnemyRE[Eno].ChangeTexture(0, 1, 1, 2);

		PlaySE(VIGOR);

		//================================
		// �{�[�i�X
		//================================
		// �X�R�A�A�b�v
		AddScore((e + Eno)->score);

		// �Q�[�W�A�b�v
		AddGage(ENEMY_D_GAUGEBONUS);

		SetYouDefeated(1);

		//================================
		// �Đ���
		//================================
		TrapFactory02((s->timer + 120), (e + Eno)->type);
	}
	else
	{
#ifdef _DEBUG
		// �X�R�A�A�b�v
		AddScore(ENEMY_SCOREBONUS);
#endif
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
}

//=============================================================================
// �S���N���A
//=============================================================================
void VanisnAllEnenyRE(void)
{
	ENEMY *e = GetEnemyRE(0);
	STAGE *s = GetStage();

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//// ����
		//(e + i)->use = FALSE;

		//// ������
		//(e + i)->hp = ENEMY_HP;
		//(e + i)->timer = 0;

		if ((e + i)->use == FALSE) continue;

		(e + i)->hp -= 32767;

		// ���j����
		if ((e + i)->hp <= 0)
		{
			//VanisnEnenyRE(Eno);

			(e + i)->status = E_STATUS_DEFEATED;

			(e + i)->timer = 0;

			// �e�N�X�`���ύX
			EnemyRE[i].ChangeTexture(0, 1, 1, 2);

			PlaySE(VIGOR);
			
			TrapFactory02((s->timer + 120), (e + i)->type);

		}

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
	(e + no)->status = E_STATUS_NORMAL;
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

	// srand()�̓��C���Ɉڂ��܂���

	//TrapFactory(120, 1);
	//TrapFactory(240, 1);
	//TrapFactory(360, 1);
	//TrapFactory(480, 1);
	//TrapFactory(600, 1);

	//TrapFactory(720, 1);
	//TrapFactory(840, 2);

	//TrapFactory(1080, 1);
	//TrapFactory(1200, 2);

	//TrapFactory(1440, 1);
	//TrapFactory(1560, 2);

	//TrapFactory(1800, 1);
	//TrapFactory(1920, 2);

	//TrapFactory(2160, 1);
	//TrapFactory(2280, 4);

	//TrapFactory(2520, 1);
	//TrapFactory(2580, 1);
	//TrapFactory(2640, 1);
	//TrapFactory(2700, 1);

	//TrapFactory(2760, 1);
	//TrapFactory(2820, 1);
	//TrapFactory(2880, 1);
	//TrapFactory(2940, 1);
	//TrapFactory(3000, 1);

	//TrapFactory(3240, 4);
	//TrapFactory(3480, 8);

	TrapFactory02(60, 0);
	TrapFactory02(90, 1);
	TrapFactory02(120, 2);

	//TrapFactory02(360, 0);
	//TrapFactory02(390, 1);
	//TrapFactory02(420, 2);

	//TrapFactory02(660, 0);
	//TrapFactory02(690, 1);
	//TrapFactory02(720, 2);

	//TrapFactory02(960, 0);
	//TrapFactory02(990, 1);
	//TrapFactory02(1020, 2);

	//TrapFactory02(1260, 0);
	//TrapFactory02(1290, 1);
	//TrapFactory02(1320, 2);

	//TrapFactory02(1560, 0);
	//TrapFactory02(1590, 1);
	//TrapFactory02(1620, 2);

	//TrapFactory02(1860, 0);
	//TrapFactory02(1890, 1);
	//TrapFactory02(1920, 2);

	//TrapFactory02(1860, 0);
	//TrapFactory02(1890, 1);
	//TrapFactory02(1920, 2);

	//TrapFactory02(2160, 0);
	//TrapFactory02(2190, 1);
	//TrapFactory02(2220, 2);

	//TrapFactory02(2460, 0);
	//TrapFactory02(2490, 1);
	//TrapFactory02(2520, 2);

	//TrapFactory02(2760, 0);
	//TrapFactory02(2790, 1);
	//TrapFactory02(2820, 2);

	//TrapFactory02(3060, 0);
	//TrapFactory02(3090, 1);
	//TrapFactory02(3120, 2);

	//TrapFactory02(3360, 0);
	//TrapFactory02(3390, 1);
	//TrapFactory02(3420, 2);



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
	EnemyRE[ENo].LoadObjectStatus((e + ENo)->pos, (e + ENo)->rot);

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

				// ��ސݒ�
				type = rand() % E_TYPE_MAX;
				SetType(j, type);		

				// �ʒu�ݒ�
				x = float(rand() % 560 - 280);
				z = float(rand() % 600);
				SetPos(j, x, 100, z);	

				// HP�ݒ�
				switch (type)
				{
				case E_TYPE_CHILD:
					(e + j)->hp = EnemyHp[E_TYPE_CHILD];
					(e + j)->score = 500;
					break;
				case E_TYPE_MAID:
					(e + j)->hp = EnemyHp[E_TYPE_MAID];
					(e + j)->score = 100;
					break;
				case E_TYPE_OTAKU:
					(e + j)->hp = EnemyHp[E_TYPE_OTAKU];
					(e + j)->score = 1000;
					break;
				default:
					(e + j)->hp = ENEMY_HP;
					break;
				}

				break;
			}
		}
	}

}

//=============================================================================
// �G�l�~�[�����i���}�[�u�j
//============================================================================='
void TrapFactory02(int apr, int num)
{
	ENEMY *e = GetEnemyRE(0);

	int type;
	float x;
	float z;

	// ���g�p�̃I�u�W�F�N�g��{��
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			if ((e + j)->apr == -1)
			{
				(e + j)->apr = apr;

				// ��ސݒ�
				type = num;
				SetType(j, type);

				// �ʒu�ݒ�
				x = float(rand() % 560 - 280);
				z = float(rand() % 600);
				SetPos(j, x, 100, z);

				// HP�ݒ�
				switch (type)
				{
				case E_TYPE_CHILD:
					(e + j)->hp = EnemyHp[E_TYPE_CHILD];
					(e + j)->score = 500;
					break;
				case E_TYPE_MAID:
					(e + j)->hp = EnemyHp[E_TYPE_MAID];
					(e + j)->score = 100;
					break;
				case E_TYPE_OTAKU:
					(e + j)->hp = EnemyHp[E_TYPE_OTAKU];
					(e + j)->score = 1000;
					break;
				default:
					(e + j)->hp = ENEMY_HP;
					(e + j)->score = 0;
					break;
				}

				break;
			}
	}

}


//=============================================================================
// �ғ����Ԍ���
//============================================================================='
void CheckUptime(int no)
{
	ENEMY *e = GetEnemyRE(0);

	int Uptime = -1;

	switch (e->status)
	{
	case 0:
		break;
	case E_STATUS_NORMAL:
		break;
	case E_STATUS_DEFEATED:
		Uptime = 120;

		if ((e + no)->timer >= Uptime)
		{
			VanisnEnenyRE(no);
		}

		break;
	default:
		break;
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

	if (GetKeyboardPress(DIK_NUMPAD3))
	{
		e->rot.y += 0.2f;
	}


	//if (GetKeyboardPress(DIK_NUMPAD3))
	//{
	//	tx->rot.y += 6 * (D3DX_PI / 180);
	//}

	//if (tx->rot.y >= 90 * (D3DX_PI / 180))
	//{
	//	tx->rot.y = -(90 * (D3DX_PI / 180));
	//}

	// 0 -> 90	-90 -> 90   -90 > 0
	// 90 180 90
	// 360 / vel = time
	// if time rot = 0


	PrintDebugProcess("pos: %f %f %f\n", e->pos.x, e->pos.y, e->pos.z);
	PrintDebugProcess("pos: %f %f %f\n", (e + 1)->pos.x, (e + 1)->pos.y, (e + 1)->pos.z);
	PrintDebugProcess("pos: %f %f %f\n", (e + 2)->pos.x, (e + 2)->pos.y, (e + 2)->pos.z);

}



