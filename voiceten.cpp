//=============================================================================
//
// voiceten���� [voiceten.cpp]
// Author : �v�F��
//
//=============================================================================
#include "voiceten.h"

#include "Library/ObjectBase3D.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void UpdateVoiMove(void);
float DirectionCalc(D3DXVECTOR3 Self, D3DXVECTOR3 Tgt);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
VOICETEN VoicetenWk[VOICETEN_MAX];		// ���[�N

char *FileVoiceten[] =
{
	"data/���/�e�X�g�摜02.jpg",
};

C3DPolygonObject Voiceten[VOICETEN_MAX];

//=============================================================================
// ����������
//=============================================================================
void InitVoiceten(void)
{
	VOICETEN *v = GetVoiceten(0);

	const Vector2 size = Vector2(48, 48);

	for (int i = 0; i < VOICETEN_MAX; i++)
	{
		(v + i)->use = FALSE;
		(v + i)->pos = Vector3(0.0f, 0.0f, 0.0f);
		(v + i)->rot = Vector3(0.0f, 0.0f, 0.0f);

		(v + i)->vel = 4.0f;

		(v + i)->timer = 0;

		(v + i)->start = Vector3(0.0f, 0.0f, 0.0f);
		(v + i)->tgt = Vector3(0.0f, 0.0f, 0.0f);
		(v + i)->dura = 60;

		(v + i)->nor = Vector3(0.0f, 0.0f, 0.0f);

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

			// ����
			VanishVoiceten(i);
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
			(v + i)->pos.z += (v + i)->nor.z;

			// ��s���x
			(v + i)->pos.y =
				((v + i)->vel * (v + i)->timer) - 
				(0.5 * 0.15 * (v + i)->timer * (v + i)->timer);

		}

	}
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
			// ���B���v�����̐��K��
			(v + i)->nor = Tgt - Self / float((v + i)->dura);

			// ��s���x�̐��K��

			(v + i)->pos = Self;

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

	if ((v + no)->timer >= (v + no)->dura)
	{
		// ����
		(v + no)->use = FALSE;

		// ������
		(v + no)->timer = 0;
	}
}