//=============================================================================
//
// Œ‚”j”Œv”Ší [DefeatCounter.cpp]
// Author : ‘v•FèÁ
//
//=============================================================================
#include "DefeatCounter.h"

#include "enemyRE.h"

//*****************************************************************************
// ƒNƒ‰ƒX’è‹`
//*****************************************************************************
DefeatCounter::DefeatCounter()
{
	this->count = 0;
}

void DefeatCounter::CountUp(void)
{
	this->count++;
}

int DefeatCounter::GetCount(void)
{
	return this->count;
}

//*****************************************************************************
// ƒOƒ[ƒoƒ‹•Ï”
//*****************************************************************************
DefeatCounter DefeatCounterWk[E_TYPE_MAX];

//=============================================================================
// æ“¾
//=============================================================================
DefeatCounter *GetDefeatCounter(int no)
{
	return &DefeatCounterWk[no];
}

//=============================================================================
// æ“¾iŒ‚”j”‘˜aj
//=============================================================================
int GetAllDefeated(void)
{
	DefeatCounter *DefeatCounter = GetDefeatCounter(0);
	int value = 0;
	for (int i = 0; i < E_TYPE_MAX; i++)
	{
		value += (DefeatCounter + i)->GetCount();
	}
	
	return value;
}