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

void SetType(int ENo, int type);
void SetPos(int ENo, float x, float y, float z);
bool SetPosCheckX(float x);

void SetParameter00(void);

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

		(e + i)->type = 0;

		(e + i)->hp = ENEMY_HP;

		(e + i)->status = 0;

		(e + i)->score = 0;

		EnemyRE[i].Init((e + i)->pos, size);
		EnemyRE[i].LoadTexture(FileEnemy[0]);

	}

	ResetYouDefeated();

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

	PrintDebugProcess("���j��: %d\n", YOUDEFEATED);




#endif

			// �Փ˔���
			CollisionEnemyRE();

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
				//CollisionEnemyRE();
				break;

			case E_STATUS_DEFEATED:

				// �A�j���[�V����
				break;

			default:
				break;

			}


		}
	}

	PrintDebugProcess("00: %f\n", (e + 0)->pos.x);
	PrintDebugProcess("01: %f\n", (e + 1)->pos.x);
	PrintDebugProcess("02: %f\n", (e + 2)->pos.x);
	PrintDebugProcess("03: %f\n", (e + 3)->pos.x);
	PrintDebugProcess("04: %f\n", (e + 4)->pos.x);
	PrintDebugProcess("05: %f\n", (e + 5)->pos.x);
	PrintDebugProcess("06: %f\n", (e + 6)->pos.x);
	PrintDebugProcess("07: %f\n", (e + 7)->pos.x);
	PrintDebugProcess("08: %f\n", (e + 8)->pos.x);
	PrintDebugProcess("09: %f\n", (e + 9)->pos.x);

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
		v = GetVoiceten(0);

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

	// �_���[�W�v�Z
	(e + Eno)->hp -= (v + Vno)->atk;

	// ���j����
	if ((e + Eno)->hp <= 0 &&
		(e + Eno)->status == E_STATUS_NORMAL)
	{
		DefeatEnemyRE(Eno);
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
// ���j����
//=============================================================================
void DefeatEnemyRE(int no)
{
	ENEMY *e = GetEnemyRE(0);
	STAGE *s = GetStage();

	// ��ԕύX
	(e + no)->status = E_STATUS_DEFEATED;

	// �^�C�}�[�Đݒ�
	(e + no)->timer = 0;

	// �e�N�X�`���ύX
	EnemyRE[no].ChangeTexture(0, 1, 1, 2);

	// ����
	PlaySE(VIGOR);

	// �X�R�A�A�b�v
	AddScore((e + no)->score);

	// �Q�[�W�A�b�v
	AddGage(ENEMY_D_GAUGEBONUS);

	// ���j���J�E���g�A�b�v
	SetYouDefeated(1);

	// �Đ���
	TrapFactory02((s->timer + 120), (e + no)->type);

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
	(e + no)->status = E_STATUS_NORMAL;
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
		if ((e + i)->use == FALSE) continue;

		(e + i)->hp -= 32767;

		// ���j����
		if ((e + i)->hp <= 0 &&
			(e + i)->status == E_STATUS_NORMAL)
		{
			DefeatEnemyRE(i);
		}


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
	TrapFactory02(60, 0);
	TrapFactory02(90, 1);
	TrapFactory02(120, 2);
	TrapFactory02(150, 0);
	TrapFactory02(180, 2);
	TrapFactory02(210, 0);
	TrapFactory02(240, 1);
	TrapFactory02(270, 2);
	TrapFactory02(300, 0);
	TrapFactory02(330, 2);


	//ENEMY *e = GetEnemyRE(0);

	//float z1 = 0.0f;

	//SetType(0, E_TYPE_OTAKU);
	//SetPos(0, -280, 100, z1);
	//(e + 0)->apr = 0;

	//SetType(1, E_TYPE_OTAKU);
	//SetPos(1, -180, 100, z1);
	//(e + 1)->apr = 0;

	//SetType(2, E_TYPE_OTAKU);
	//SetPos(2, -80, 100, z1);
	//(e + 2)->apr = 0;

	//SetType(3, E_TYPE_OTAKU);
	//SetPos(3, 20, 100, z1);
	//(e + 3)->apr = 0;

	//SetType(4, E_TYPE_OTAKU);
	//SetPos(4, 120, 100, z1);
	//(e + 4)->apr = 0;

	//SetType(5, E_TYPE_OTAKU);
	//SetPos(5, 220, 100, z1);
	//(e + 5)->apr = 0;

	//SetType(6, E_TYPE_OTAKU);
	//SetPos(6, 320, 100, z1);
	//(e + 6)->apr = 0;

	//float z2 = 600.0f;

	//SetType(7, E_TYPE_OTAKU);
	//SetPos(7, -280, 100, z2);
	//(e + 7)->apr = 0;

	//SetType(8, E_TYPE_OTAKU);
	//SetPos(8, -180, 100, z2);
	//(e + 8)->apr = 0;

	//SetType(9, E_TYPE_OTAKU);
	//SetPos(9, -80, 100, z2);
	//(e + 9)->apr = 0;

	//SetType(10, E_TYPE_OTAKU);
	//SetPos(10, 20, 100, z2);
	//(e + 10)->apr = 0;

	//SetType(11, E_TYPE_OTAKU);
	//SetPos(11, 120, 100, z2);
	//(e + 11)->apr = 0;

	//SetType(12, E_TYPE_OTAKU);
	//SetPos(12, 220, 100, z2);
	//(e + 12)->apr = 0;

	//SetType(13, E_TYPE_OTAKU);
	//SetPos(13, 320, 100, z2);
	//(e + 13)->apr = 0;



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

bool SetPosCheckX(float x)
{
	ENEMY *e = GetEnemyRE(0);

	float v = 40.0f;
	bool check = FALSE;

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if ((e + i)->use == TRUE)
		{
			if (x <= ((e + i)->pos.x + v) &&
				x >= ((e + i)->pos.x - v)
				)
			{
				check = TRUE;
				break;
			}
			
		}
	}

	return check;
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

	float x = 0.0f;
	float z = 0.0f;

	// ���g�p�̃I�u�W�F�N�g��{��
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			if ((e + j)->apr == -1)
			{
				(e + j)->apr = apr;

				// ��ސݒ�
				(e + j)->type = num;
				SetType(j, (e + j)->type);

				// �ʒu�ݒ�
				x = float(rand() % 560 - 280);
				z = float(rand() % 600);
				SetPos(j, x, 100, z);

				// HP�ݒ�
				switch ((e + j)->type)
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

	switch ((e + no)->status)
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



