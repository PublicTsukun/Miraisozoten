//=============================================================================
//
// [EnemyPosData.h]
// Author : �v�F��
//
//=============================================================================
#include "EnemyPosData.h"

#include "enemyRE.h"

//*****************************************************************************
// �N���X��`
//*****************************************************************************
EnemyPosData::EnemyPosData()
{
	this->use = false;
}

void EnemyPosData::SetUse(bool use)
{
	this->use = use;
}

void EnemyPosData::SetPos(float x, float z)
{
	this->x = x;
	this->z = z;
}

bool EnemyPosData::GetUse(void)
{
	return this->use;
}

float EnemyPosData::GetPosX(void)
{
	return this->x;
}

float EnemyPosData::GetPosZ(void)
{
	return this->z;
}

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
EnemyPosData EnemyPosDataWk[ENEMYPOS_MAX];

//=============================================================================
// �擾
//=============================================================================
EnemyPosData *GetEnemyPosData(int no)
{
	return &EnemyPosDataWk[no];
}

//=============================================================================
// �������i�p�����[�^�ݒ�j
//=============================================================================
void InitEnemyPosData(void)
{
	int i = 0;
	float z = 0;

	EnemyPosDataWk[i].SetPos(-280, z); i++;
	EnemyPosDataWk[i].SetPos(-180, z); i++;
	EnemyPosDataWk[i].SetPos(-80, z); i++;
	EnemyPosDataWk[i].SetPos(20, z); i++;
	EnemyPosDataWk[i].SetPos(120, z); i++;
	EnemyPosDataWk[i].SetPos(220, z); i++;
	EnemyPosDataWk[i].SetPos(320, z); i++;
	z += 100;

	EnemyPosDataWk[i].SetPos(-280, z); i++;
	EnemyPosDataWk[i].SetPos(-180, z); i++;
	//EnemyPosDataWk[i].SetPos(-80, z); i++;
	//EnemyPosDataWk[i].SetPos(20, z); i++;
	//EnemyPosDataWk[i].SetPos(120, z); i++;
	EnemyPosDataWk[i].SetPos(220, z); i++;
	EnemyPosDataWk[i].SetPos(320, z); i++;
	z += 100;

	EnemyPosDataWk[i].SetPos(-280, z); i++;
	//EnemyPosDataWk[i].SetPos(-180, z); i++;
	//EnemyPosDataWk[i].SetPos(-80, z); i++;
	//EnemyPosDataWk[i].SetPos(20, z); i++;
	//EnemyPosDataWk[i].SetPos(120, z); i++;
	//EnemyPosDataWk[i].SetPos(220, z); i++;
	EnemyPosDataWk[i].SetPos(320, z); i++;
	z += 100;

	//EnemyPosDataWk[i].SetPos(-280, z); i++;
	EnemyPosDataWk[i].SetPos(-180, z); i++;
	EnemyPosDataWk[i].SetPos(-80, z); i++;
	EnemyPosDataWk[i].SetPos(20, z); i++;
	EnemyPosDataWk[i].SetPos(120, z); i++;
	EnemyPosDataWk[i].SetPos(220, z); i++;
	//EnemyPosDataWk[i].SetPos(320, z); i++;
	z += 100;

	EnemyPosDataWk[i].SetPos(-280, z); i++;
	//EnemyPosDataWk[i].SetPos(-180, z); i++;
	//EnemyPosDataWk[i].SetPos(-80, z); i++;
	//EnemyPosDataWk[i].SetPos(20, z); i++;
	//EnemyPosDataWk[i].SetPos(120, z); i++;
	//EnemyPosDataWk[i].SetPos(220, z); i++;
	EnemyPosDataWk[i].SetPos(320, z); i++;
	z += 100;

	EnemyPosDataWk[i].SetPos(-280, z); i++;
	//EnemyPosDataWk[i].SetPos(-180, z); i++;
	//EnemyPosDataWk[i].SetPos(-80, z); i++;
	//EnemyPosDataWk[i].SetPos(20, z); i++;
	//EnemyPosDataWk[i].SetPos(120, z); i++;
	//EnemyPosDataWk[i].SetPos(220, z); i++;
	EnemyPosDataWk[i].SetPos(320, z); i++;
	z += 100;

	//EnemyPosDataWk[i].SetPos(-280, z); i++;
	EnemyPosDataWk[i].SetPos(-180, z); i++;
	EnemyPosDataWk[i].SetPos(-80, z); i++;
	EnemyPosDataWk[i].SetPos(20, z); i++;
	EnemyPosDataWk[i].SetPos(120, z); i++;
	EnemyPosDataWk[i].SetPos(220, z); i++;
	//EnemyPosDataWk[i].SetPos(320, z); i++;
}
