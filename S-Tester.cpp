//=============================================================================
//
// [S-Tester.cpp]
// Author : ‘v•FèÁ
//
//=============================================================================
#include "S-Tester.h"

#include "Library/DebugProcess.h"
#include "Library/Input.h"

#include "enemyRE.h"
#include "DefeatCounter.h"





//=============================================================================
// DefeatCounter
//=============================================================================
void TesterDC(void)
{
	DefeatCounter *DefeatCounter = GetDefeatCounter(0);

	// Œ‚”j”‚ÌŽæ“¾
	//// ƒ^ƒCƒvŽw’è
	PrintDebugProcess("CHILD: %d\n", (DefeatCounter + E_TYPE_CHILD)->GetCount());
	PrintDebugProcess("MAID: %d\n", (DefeatCounter + E_TYPE_MAID)->GetCount());
	PrintDebugProcess("OTAKU: %d\n", (DefeatCounter + E_TYPE_OTAKU)->GetCount());
	PrintDebugProcess("AA: %d\n", (DefeatCounter + E_TYPE_AA)->GetCount());
	//// ‘S•”
	PrintDebugProcess("ALL: %d\n", GetAllDefeated());

	// Œ‚”j”‚Ì‰ÁŽZ
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
