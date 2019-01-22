//=============================================================================
//
// ���j���v���� [DefeatCounter.cpp]
// Author : �v�F��
//
//=============================================================================
#include "DefeatCounter.h"

#include "enemyRE.h"

//*****************************************************************************
// �N���X��`
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

void DefeatCounter::SetCount(int value)
{
	this->count = value;
}

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
DefeatCounter DefeatCounterWk[E_TYPE_MAX];

//=============================================================================
// ������
//=============================================================================
void InitDefeatCounter(void)
{
	DefeatCounter *DefeatCounter = GetDefeatCounter(0);

	for (int i = 0; i < E_TYPE_MAX; i++)
	{
		(DefeatCounter + i)->SetCount(0);
	}
}

//=============================================================================
// �擾
//=============================================================================
DefeatCounter *GetDefeatCounter(int no)
{
	return &DefeatCounterWk[no];
}

//=============================================================================
// �擾�i���j�����a�j
//=============================================================================
int GetAllDefeat(void)
{
	DefeatCounter *DefeatCounter = GetDefeatCounter(0);
	int value = 0;
	for (int i = 0; i < E_TYPE_MAX; i++)
	{
		value += (DefeatCounter + i)->GetCount();
	}
	
	return value;
}