//=============================================================================
//
// [EnemyPosData.h]
// Author : 宋彦霖
//
//=============================================================================
#include "EnemyPosData.h"

#include "enemyRE.h"

//*****************************************************************************
// クラス定義
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
// グローバル変数
//*****************************************************************************
EnemyPosData EnemyPosDataWk[ENEMYPOS_MAX];

//=============================================================================
// 取得
//=============================================================================
EnemyPosData *GetEnemyPosData(int no)
{
	return &EnemyPosDataWk[no];
}

//=============================================================================
// 初期化（パラメータ設定）
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
