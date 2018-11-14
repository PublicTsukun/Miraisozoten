//=============================================================================
//
//�ؑ��S�����@workenemy.cpp
//�@��N�̎��ɂ����main.cpp�Ɠ���������
// 
// �E�ҏW : [2018/11/11 - ��]
//   >> �{�ԗp�ɏ��������܂���
//=============================================================================

//�K�{�C���N���[�h
#include <windows.h>
#include "enemy.h"


//�ؑ��S�����C���N���[�h

// ���S�����C���N���[�h
#include "HitCheck.h"

// �萔��`
#define ENEMY_MAX (16)
#define ENEMY_SIZE_X (100)
#define ENEMY_SIZE_Y (100)


// �N���X�݌v
Dx9Texture CEnemy::EnemyTexture[ENEMYTYPE_MAX];

void CEnemy::ChangeTexture(float side)
{
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].uv = Vector2(side        * 0.5f, 0.0f);
	pVtx[1].uv = Vector2(side        * 0.5f, 0.0f);
	pVtx[2].uv = Vector2(side + 1.0f * 0.5f, 1.0f);
	pVtx[3].uv = Vector2(side + 1.0f * 0.5f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	VtxBuff->Unlock();
}
void CEnemy::Move(Vector3 v)
{
	this->Position += v;
}
inline void CEnemy::CheckHit(Vector3 pos, Vector3 box, int atk)
{
	if (Collision::AABB(pos - box, pos + box,
		this->Position - Vector3(this->Size.x, this->Size.y, this->Size.x) * this->Scale,
		this->Position + Vector3(this->Size.x, this->Size.y, this->Size.x) * this->Scale))
	{
		this->HP -= atk;
	}

	if (this->HP <= 0)
	{
		this->ChangeTexture(1);
	}
}

//�O���[�o���錾
CEnemy *EnemyList[ENEMY_MAX] = { NULL };

//=============================================================================
//����������
//=============================================================================
HRESULT InitENEMY(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		EnemyList[i] = NULL;
	}
	for (int i = 0; i < ENEMYTYPE_MAX; i++)
	{
		CEnemy::EnemyTexture[i].LoadTexture(EnemyTextureName[i]);
	}

	return S_OK;
}

//=============================================================================
//�I�������@���L�ڏꏊ����
//=============================================================================
void UninitENEMY(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		Dx9SafeRelease(EnemyList[i]);
	}
	for (int i = 0; i < ENEMYTYPE_MAX; i++)
	{
		CEnemy::EnemyTexture[i].Release();
	}

}

//=============================================================================
//�X�V����
//=============================================================================
void UpdateENEMY(void)
{

}

//=============================================================================
//�`�揈��
//=============================================================================
void DrawENEMY(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (EnemyList[i] != NULL)
		{
			EnemyList[i]->Draw();
		}
	}
}

//=============================================================================
// �G�l�~�[�ǉ�����
//=============================================================================
int SetEnemy(ENEMYTYPE type, int hp, Vector3 pos)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (EnemyList[i] == NULL)
		{
			EnemyList[i] = new CEnemy;
			EnemyList[i]->Init(pos, Vector2(ENEMY_SIZE_X, ENEMY_SIZE_Y));
			EnemyList[i]->LoadTexture(CEnemy::EnemyTexture[type]);
			EnemyList[i]->ChangeTexture(0);
			return i;
		}
	}
	return -1;
}

//=============================================================================
// �G�l�~�[�폜���� (�����蔻��)
//=============================================================================
void CheckHit(Vector3 pos, Vector2 box, int atk)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		EnemyList[i]->CheckHit(pos, Vector3(box.x, box.y, box.x), atk);
	}
}

//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
CEnemy *GetEnemy(int handle)
{
	return EnemyList[handle];
}

