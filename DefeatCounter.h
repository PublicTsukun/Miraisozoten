//=============================================================================
//
// ���j���v���� [DefeatCounter.h]
// Author : �v�F��
//
//=============================================================================
#ifndef _DEFEATCOUNTER_INCLUDE_H_
#define _DEFEATCOUNTER_INCLUDE_H_

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class DefeatCounter
{
private:
	int count;
	
public:
	DefeatCounter();

	void CountUp(void);
	int GetCount(void);
	void SetCount(int value);

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
DefeatCounter *GetDefeatCounter(int no);
int GetAllDefeat(void);

#endif