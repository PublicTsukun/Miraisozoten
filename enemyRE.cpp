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

#include "EnemyDB.h"
#include "EnemyPosData.h"
#include "EnemyHP.h"

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
//=================
// �Փ˔���A���j
//=================
void CollisionEnemyRE(void);
void DamageDealEnemyRE(int Eno, int Vno);
void DefeatEnemyRE(int no);
void VanisnEnenyRE(int no);

//=================
// ����
//=================
void SetParameter01(void);

void TrapFactory03(int no, int apr);

void TF_Type(int no);
void TF_Pos(int no);

//=================
// ���o
//=================
void CheckUptime(int no);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
char *FileEnemy[] =
{
	"data/TEXTURE/Character/00_child.png",
	"data/TEXTURE/Character/01_maid.png",
	"data/TEXTURE/Character/02_otaku.png",
	"data/TEXTURE/Character/03_aa.png",
	"data/TEXTURE/Character/04_jk.png",
	"data/TEXTURE/Character/05_american.png",
	"data/TEXTURE/Character/06_astronaut.png",
	"data/TEXTURE/Character/07_alien.png",
	"data/TEXTURE/Character/08_ufo.png",
};

// ���[�N
ENEMY EnemyREWk[ENEMY_MAX];		
CEnemyRE EnemyRE[ENEMY_MAX];

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
		(e + i)->pos = Vector3(0.0f, float(size.y / 2), 0.0f);
		(e + i)->rot = Vector3(0.0f, 0.0f, 0.0f);

		(e + i)->timer = 0;

		(e + i)->apr = -1;

		(e + i)->type = 0;

		(e + i)->hp = ENEMY_HP;

		(e + i)->status = 0;

		(e + i)->score = 0;

		EnemyRE[i].Init((e + i)->pos, size);
	}
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

	// HP�C��
	if ((e + Eno)->hp < 0)
	{
		(e + Eno)->hp = 0;
	}
	
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

	// �Đ���
	TrapFactory03(no, s->timer + 120);

}

//=============================================================================
// ����
//=============================================================================
void VanisnEnenyRE(int no)
{
	ENEMY *e = GetEnemyRE(0);
	EnemyPosData *ePosData = GetEnemyPosData(0);

	// ����
	(e + no)->use = FALSE;
	(ePosData + no)->SetUse(false);

	// ������
	(e + no)->timer = 0;
	(e + no)->apr = -1;
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
// �ݒu
//=============================================================================
void SetEnemyRE(int time)
{
	ENEMY *enemy = GetEnemyRE(0);

	time += 60;

	for (int i = 0; i < ENEMY_MAX; i++, time += 120)
	{
		TrapFactory03(i, time);
	}
}

//=============================================================================
// �o��
//=============================================================================
void EnemyREOnStage(int no)
{
	ENEMY *e = GetEnemyRE(0);
	EnemyHP *EnemyHP = GetEnemyHP(0);

	(e + no)->use = TRUE;
	(e + no)->status = E_STATUS_NORMAL;

	(EnemyHP + no)->Enable();
}

//=============================================================================
// �N���A�i�X�e�[�W�J�ڂ̉��o�j
//=============================================================================
void ClearAllEnemyRE(void)
{
	ENEMY *enemy = GetEnemyRE(0);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if ((enemy + i)->status = E_STATUS_NORMAL)
		{
			(enemy + i)->use = FALSE;
			(enemy + i)->status = E_STATUS_NULL;
		}
	}

}

//=============================================================================
// �p�����[�^���Z�b�g
//=============================================================================
void ResetAllEnemyRE(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		VanisnEnenyRE(i);
	}
}

//=============================================================================
// �p�����[�^�ݒ�
//============================================================================='
void SetParameter01(void)
{
	int i = 0;
	int j = 60;

	TrapFactory03(i, j); i++; j += 30;
	TrapFactory03(i, j); i++; j += 30;
	TrapFactory03(i, j); i++; j += 30;
	TrapFactory03(i, j); i++; j += 30;
	TrapFactory03(i, j); i++; j += 30;

	TrapFactory03(i, j); i++; j += 30;
	TrapFactory03(i, j); i++; j += 30;
	TrapFactory03(i, j); i++; j += 30;
	TrapFactory03(i, j); i++; j += 30;
	TrapFactory03(i, j);
}

//=============================================================================
// �G�l�~�[����
//============================================================================='
void TrapFactory03(int no, int apr)
{
	// �o���^�C�~���O
	ENEMY *e = GetEnemyRE(no);
	e->apr = apr;

	// �^�C�v
	TF_Type(no);

	// �ʒu
	TF_Pos(no);

	// �p�[�c�EHP�Q�[�W
	EnemyHP *EnemyHP = GetEnemyHP(no);
	Vector3 tempPos = e->pos;
	//// �ʒu����
	tempPos.x += -32.0f;
	tempPos.y += -88.0f;
	//// �ʒu�ݒ�
	EnemyHP->LoadObjectStatus(tempPos);

}

//=============================================================================
// �G�l�~�[�����F�^�C�v�ݒ�
//============================================================================='
void TF_Type(int no)
{
	ENEMY *e = GetEnemyRE(no);
	EnemyDB *EnemyDB = GetEnemyDB(0);
	STAGE *s = GetStage();
	int stage = s->no;
	int temp = -1;

	// �^�C�v�ݒ�
	switch (stage)
	{
	case STAGE_01_AKIBA:
		temp = int(rand() % 10);
		if (temp == 0) e->type = E_TYPE_CHILD;
		if (temp == 1) e->type = E_TYPE_CHILD;
		if (temp == 2) e->type = E_TYPE_CHILD;
		if (temp == 3) e->type = E_TYPE_CHILD;
		if (temp == 4) e->type = E_TYPE_CHILD;
		if (temp == 5) e->type = E_TYPE_MAID;
		if (temp == 6) e->type = E_TYPE_MAID;
		if (temp == 7) e->type = E_TYPE_OTAKU;
		if (temp == 8) e->type = E_TYPE_OTAKU;
		if (temp == 9) e->type = E_TYPE_OTAKU;
		break;

	case STAGE_02_USA:
		temp = int(rand() % 10);
		if (temp == 0) e->type = E_TYPE_AA;
		if (temp == 1) e->type = E_TYPE_AA;
		if (temp == 2) e->type = E_TYPE_AA;
		if (temp == 3) e->type = E_TYPE_AA;
		if (temp == 4) e->type = E_TYPE_AA;
		if (temp == 5) e->type = E_TYPE_JK;
		if (temp == 6) e->type = E_TYPE_JK;
		if (temp == 7) e->type = E_TYPE_AMERICAN;
		if (temp == 8) e->type = E_TYPE_AMERICAN;
		if (temp == 9) e->type = E_TYPE_AMERICAN;
		break;

	case STAGE_03_SPACE:
		temp = int(rand() % 10);
		if (temp == 0) e->type = E_TYPE_ASTRONAUT;
		if (temp == 1) e->type = E_TYPE_ASTRONAUT;
		if (temp == 2) e->type = E_TYPE_ASTRONAUT;
		if (temp == 3) e->type = E_TYPE_ASTRONAUT;
		if (temp == 4) e->type = E_TYPE_ASTRONAUT;
		if (temp == 5) e->type = E_TYPE_ALIEN;
		if (temp == 6) e->type = E_TYPE_ALIEN;
		if (temp == 7) e->type = E_TYPE_UFO;
		if (temp == 8) e->type = E_TYPE_UFO;
		if (temp == 9) e->type = E_TYPE_UFO;
		break;

	default:
		break;
	}

	// �e�N�X�`���ݒ�
	EnemyRE[no].LoadTexture(FileEnemy[e->type]);
	EnemyRE[no].SetTexture();

	// �p�����[�^�ݒ�
	EnemyDB = GetEnemyDB(e->type);
	e->hp = EnemyDB->GetHP();
	e->score = EnemyDB->GetScore();
	
}

//=============================================================================
// �G�l�~�[�����F�o���ʒu�ݒ�
//============================================================================='
void TF_Pos(int no)
{
	ENEMY *e = GetEnemyRE(no);
	EnemyPosData *ePosData = GetEnemyPosData(0);

	// �ʒu�ݒ�
	int valueP = ENEMYPOS_MAX;
	int tempP = -1;

	do
	{
		tempP = (rand() % valueP);
		ePosData = GetEnemyPosData(tempP);
	} while (ePosData->GetUse() == true);

	e->pos.x = ePosData->GetPosX();
	e->pos.z = ePosData->GetPosZ();
	ePosData->SetUse(true);

	// ������
	const int value = 20;
	float tempX = float(rand() % value) - (value / 2);
	float tempZ = float(rand() % value) - (value / 2);
	e->pos.x += tempX;
	e->pos.z += tempZ;

	// ���f
	EnemyRE[no].LoadObjectStatus(e->pos, e->rot);
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
