//=============================================================================
//
// voiceten���� [voiceten.cpp]
// Author : �v�F��
//
//=============================================================================
#include "voiceten.h"

#include "Library/ObjectBase3D.h"

#include "UIBonus.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define V_BLUE_ATK		(5)		// voiceten blue ATK 
#define V_YELLOW_ATK	(15)	// voiceten yellow ATK	
#define V_RED_ATK		(50)	// voiceten red ATK

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CVoiceten : public C3DPolygonObject
{
public:
	void ChangeTexture(float row, float col, float rowMax, float colMax);
	void SetTexture(void);
	void SetTexture(int no);
};

void CVoiceten::ChangeTexture(float row, float col, float rowMax, float colMax)
{
	const float rowN = (1.0f / rowMax);		// �s�𓙕��ɕ�����
	const float colN = (1.0f / colMax);		// ��𓙕��ɕ�����

	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^Set���擾
	VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].uv = Vector2(col * colN, row * rowN);
	pVtx[1].uv = Vector2((col + 1) * colN, row * rowN);
	pVtx[2].uv = Vector2(col * colN, ((row + 1) * rowN));
	pVtx[3].uv = Vector2((col + 1) * colN, ((row + 1) * rowN));

	// ���_�f�[�^���A�����b�N����
	VtxBuff->Unlock();
}

void CVoiceten::SetTexture(void)
{
	CVoiceten::ChangeTexture(0, 0, 1, 3);
}

void CVoiceten::SetTexture(int no)
{
	CVoiceten::ChangeTexture(0, float(no), 1, 3);
}

//*****************************************************************************
// �񋓌^
//*****************************************************************************
enum V_TYPE
{
	V_TYPE_BLUE = 0,
	V_TYPE_YELLOW,
	V_TYPE_RED,

	V_TYPE_MAX,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void UpdateVoiMove(void);
void UpdateVoiMoveY(int no);

void CheckUptimeVoi(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
VOICETEN VoicetenWk[VOICETEN_MAX];		// ���[�N

char *FileVoiceten[] =
{
	"data/TEXTURE/UI/voiceten.png",

};

CVoiceten Voiceten[VOICETEN_MAX];

//=============================================================================
// ����������
//=============================================================================
void InitVoiceten(void)
{
	VOICETEN *v = GetVoiceten(0);

	const Vector2 size = Vector2(20.5, 21.5);

	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		(v + i)->use = FALSE;
		(v + i)->pos = Vector3(0.0f, 0.0f, 0.0f);
		(v + i)->rot = Vector3(0.0f, 0.0f, 0.0f);

		(v + i)->vel = 2.0f;

		(v + i)->timer = 0;

		(v + i)->start = Vector3(0.0f, 0.0f, 0.0f);
		(v + i)->tgt = Vector3(0.0f, 0.0f, 0.0f);
		(v + i)->dura = 60;

		(v + i)->nor = Vector3(0.0f, 0.0f, 0.0f);

		(v + i)->atk = 1;

		Voiceten[i].Init((v + i)->pos, size);
		Voiceten[i].LoadTexture(FileVoiceten[0]);
		
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitVoiceten(void)
{
	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		Voiceten[i].Release();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateVoiceten(void)
{
	VOICETEN *v = GetVoiceten(0);

	UpdateVoiMove();

	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		if ((v + i)->use == TRUE)
		{
			// �X�V�����i�ʒu�A��]�j
			Voiceten[i].LoadObjectStatus((v + i)->pos, (v + i)->rot);

			// �^�C�}�[�@�J�E���g�A�b�v
			(v + i)->timer++;

			// �ғ����Ԍ���
			CheckUptimeVoi(i);

			// ����
			//VanishVoiceten(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawVoiceten(void)
{
	VOICETEN *v = GetVoiceten(0);

	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		if ((v + i)->use == TRUE)
		{
			Voiceten[i].Draw();
		}

	}
}

//=============================================================================
// �擾
//=============================================================================
VOICETEN *GetVoiceten(int no)
{
	return (&VoicetenWk[no]);
}

//=============================================================================
// �ړ�
//=============================================================================
void UpdateVoiMove(void)
{
	VOICETEN *v = GetVoiceten(0);

	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		if ((v + i)->use == TRUE)
		{
			//// ���
			//(v + i)->pos.x -= sinf((v + i)->rot.y) * (v + i)->vel;
			//(v + i)->pos.z -= cosf((v + i)->rot.y) * (v + i)->vel;

			// �ڕW�w��
			(v + i)->pos.x += (v + i)->nor.x;
			(v + i)->pos.y += (v + i)->nor.y;
			(v + i)->pos.z += (v + i)->nor.z;

			UpdateVoiMoveY(i);

		}
	}
}

//=============================================================================
// �ړ�Y
//=============================================================================
void UpdateVoiMoveY(int no)
{
	VOICETEN *v = GetVoiceten(0);

	// ���������p
	const float value = 20.0;

	// ��
	// �������� 60 / �i�� 20 = 3.0
	// �x�W�F�Ȑ� 4�|�C���g (0, 0) (2, 8) (4, 8) (8, 8) Y�������g�p

	if (((v + no)->timer) >= 0 && ((v + no)->timer) < 3) { (v + no)->pos.y +=   float((1.14 - 0)    / 3.0 * value); }
	if (((v + no)->timer) >= 3 && ((v + no)->timer) < 6) { (v + no)->pos.y +=   float((2.16 - 1.14) / 3.0 * value); }
	if (((v + no)->timer) >= 6 && ((v + no)->timer) < 9) { (v + no)->pos.y +=   float((3.06 - 2.16) / 3.0 * value); }
	if (((v + no)->timer) >= 9 && ((v + no)->timer) < 12) { (v + no)->pos.y +=  float((3.84 - 3.06) / 3.0 * value); }
	if (((v + no)->timer) >= 12 && ((v + no)->timer) < 15) { (v + no)->pos.y += float((4.50 - 3.84) / 3.0 * value); }
	if (((v + no)->timer) >= 15 && ((v + no)->timer) < 18) { (v + no)->pos.y += float((5.04 - 4.50) / 3.0 * value); }
	if (((v + no)->timer) >= 18 && ((v + no)->timer) < 21) { (v + no)->pos.y += float((5.46 - 5.04) / 3.0 * value); }
	if (((v + no)->timer) >= 21 && ((v + no)->timer) < 24) { (v + no)->pos.y += float((5.76 - 5.46) / 3.0 * value); }
	if (((v + no)->timer) >= 24 && ((v + no)->timer) < 27) { (v + no)->pos.y += float((5.94 - 5.76) / 3.0 * value); }
	if (((v + no)->timer) >= 27 && ((v + no)->timer) < 30) { (v + no)->pos.y += float((6.0 - 5.94)  / 3.0 * value); }

	if (((v + no)->timer) >= 30 && ((v + no)->timer) < 33) { (v + no)->pos.y += float((5.94 - 6.0)  / 3.0 * value); }
	if (((v + no)->timer) >= 33 && ((v + no)->timer) < 36) { (v + no)->pos.y += float((5.76 - 5.94) / 3.0 * value); }
	if (((v + no)->timer) >= 36 && ((v + no)->timer) < 39) { (v + no)->pos.y += float((5.46 - 5.76) / 3.0 * value); }
	if (((v + no)->timer) >= 39 && ((v + no)->timer) < 42) { (v + no)->pos.y += float((5.04 - 5.46) / 3.0 * value); }
	if (((v + no)->timer) >= 42 && ((v + no)->timer) < 45) { (v + no)->pos.y += float((4.50 - 5.04) / 3.0 * value); }
	if (((v + no)->timer) >= 45 && ((v + no)->timer) < 48) { (v + no)->pos.y += float((3.84 - 4.50) / 3.0 * value); }
	if (((v + no)->timer) >= 48 && ((v + no)->timer) < 51) { (v + no)->pos.y += float((3.06 - 3.84) / 3.0 * value); }
	if (((v + no)->timer) >= 51 && ((v + no)->timer) < 54) { (v + no)->pos.y += float((2.16 - 3.06) / 3.0 * value); }
	if (((v + no)->timer) >= 54 && ((v + no)->timer) < 57) { (v + no)->pos.y += float((1.14 - 2.16) / 3.0 * value); }
	if (((v + no)->timer) >= 57 && ((v + no)->timer) < 60) { (v + no)->pos.y += float((0.0 - 1.14)  / 3.0 * value); }

}

//=============================================================================
// �ݒu
//=============================================================================
void SetVoiceten(Vector3 Self, Vector3 Tgt)
{
	VOICETEN *v = GetVoiceten(0);

	// ���g�p�̃I�u�W�F�N�g��{��
	// �g�p�X�C�b�`�I��
	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		if ((v + i)->use == FALSE)
		{
			// ���B���v����
			(v + i)->dist =
				sqrt(
					pow((Tgt.x - Self.x), 2) +
					pow((Tgt.y - Self.y), 2) +
					pow((Tgt.z - Self.z), 2)
					);

			// ���B���v�����̐��K��
			(v + i)->nor = (Tgt - Self) / float((v + i)->dura);

			// ���x
			(v + i)->vel =
				sqrt(
					pow(((v + i)->nor.x), 2) +
					pow(((v + i)->nor.y), 2) +
					pow(((v + i)->nor.z), 2)
					);

			// �ʒu������
			(v + i)->pos = Self;
			Voiceten[i].LoadObjectStatus((v + i)->pos);

			// �e�N�X�`���ݒ�i�Q�[�W�̏�ԂɈˑ��j
			switch (GetGauge())
			{
			case 0:
				Voiceten[i].SetTexture(V_TYPE_BLUE);
				(v + i)->atk = V_BLUE_ATK;
				break;
			case 1:
				Voiceten[i].SetTexture(V_TYPE_YELLOW);
				(v + i)->atk = V_YELLOW_ATK;
				break;
			case 2:
				Voiceten[i].SetTexture(V_TYPE_RED);
				(v + i)->atk = V_RED_ATK;
				break;
			default:
				Voiceten[i].SetTexture(V_TYPE_BLUE);
				(v + i)->atk = V_BLUE_ATK;
				break;
			}

			// ����
			(v + i)->use = TRUE;

			break;
		}
	}

}

//=============================================================================
// ����
//=============================================================================
void VanishVoiceten(int no)
{
	VOICETEN *v = GetVoiceten(0);

	//if ((v + no)->timer >= (v + no)->dura)
	//{

	//}

	// ����
	(v + no)->use = FALSE;

	// ������
	(v + no)->pos = Vector3(0.0f, 0.0f, 0.0f);
	(v + no)->nor = Vector3(0.0f, 0.0f, 0.0f);
	(v + no)->timer = 0;

	Voiceten[no].LoadObjectStatus((v + no)->pos);

}

//=============================================================================
// �ғ����Ԍ���
//=============================================================================
void CheckUptimeVoi(int no)
{
	VOICETEN *v = GetVoiceten(0);

	const int Uptime = 60;

	if ((v + no)->timer >= Uptime)
	{
		VanishVoiceten(no);
	}

}