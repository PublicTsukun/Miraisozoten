//=============================================================================
//
// [S-Tester.cpp]
// Author : �v�F��
//
//=============================================================================
#include "S-Tester.h"

#include "Library/DebugProcess.h"
#include "Library/Input.h"

#include "enemyRE.h"
#include "DefeatCounter.h"
#include "EnemyPosData.h"

//=============================================================================
// DefeatCounter
//=============================================================================
void TesterDC(void)
{
	DefeatCounter *DefeatCounter = GetDefeatCounter(0);

	// ���j���̎擾
	//// �^�C�v�w��
	PrintDebugProcess("CHILD: %d\n", (DefeatCounter + E_TYPE_CHILD)->GetCount());
	PrintDebugProcess("MAID: %d\n", (DefeatCounter + E_TYPE_MAID)->GetCount());
	PrintDebugProcess("OTAKU: %d\n", (DefeatCounter + E_TYPE_OTAKU)->GetCount());
	PrintDebugProcess("AA: %d\n", (DefeatCounter + E_TYPE_AA)->GetCount());
	//// �S��
	PrintDebugProcess("ALL: %d\n", GetAllDefeat());

	// ���j���̉��Z
	if (GetKeyboardTrigger(DIK_NUMPAD0))
	{
		(DefeatCounter + E_TYPE_CHILD)->CountUp();
	}

	if (GetKeyboardTrigger(DIK_NUMPAD1))
	{
		(DefeatCounter + E_TYPE_MAID)->CountUp();
	}

	if (GetKeyboardTrigger(DIK_NUMPAD2))
	{
		(DefeatCounter + E_TYPE_OTAKU)->CountUp();
	}

	if (GetKeyboardTrigger(DIK_NUMPAD3))
	{
		(DefeatCounter + E_TYPE_AA)->CountUp();
	}

	if (GetKeyboardTrigger(DIK_NUMPAD4))
	{
		(DefeatCounter + E_TYPE_JK)->CountUp();
	}

	if (GetKeyboardTrigger(DIK_NUMPAD5))
	{
		(DefeatCounter + E_TYPE_AMERICAN)->CountUp();
	}

	if (GetKeyboardTrigger(DIK_NUMPAD6))
	{
		(DefeatCounter + E_TYPE_ASTRONAUT)->CountUp();
	}

	if (GetKeyboardTrigger(DIK_NUMPAD7))
	{
		(DefeatCounter + E_TYPE_ALIEN)->CountUp();
	}

	if (GetKeyboardTrigger(DIK_NUMPAD8))
	{
		(DefeatCounter + E_TYPE_UFO)->CountUp();
	}
}

//=============================================================================
// DeirectAttack
//=============================================================================
void TesterAtk(void)
{
	ENEMY *enemy = GetEnemyRE(0);

	if (GetKeyboardTrigger(DIK_A))
	{
		TesterAtkEnemyRE();
	}

	if (GetKeyboardPress(DIK_NUMPAD3))
	{
		enemy->rot.y += 6 * (D3DX_PI / 180);
	}

	if (enemy->rot.y >= 90 * (D3DX_PI / 180))
	{
		enemy->rot.y = -(90 * (D3DX_PI / 180));
	}

	PrintDebugProcess("(%f)", enemy->rot.y);
}

//=============================================================================
// PosData
//=============================================================================
void TesterPD(void)
{
	ENEMY *enemy = GetEnemyRE(0);
	PrintDebugProcess("E PosData: %d\n", enemy->posData);

	EnemyPosData *ePosData = GetEnemyPosData(0);

	for (int i = 0; i < ENEMYPOS_MAX; i++)
	{
		PrintDebugProcess("PosData: %d\n", (ePosData + i)->GetUse());
		
	}
}