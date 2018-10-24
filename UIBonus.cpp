//=============================================================================
//
// �t�B�[���h���� [field.cpp]
//
//=============================================================================
#include "UIBonus.h"
#include "Library/ObjectBase2D.h"
#include "Library/Common.h"
#include "Library\Input.h"
#include "Library\DebugProcess.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
UI2DPercentGauge	BonusGage;	//�{�[�i�X�Q�[�W



//=============================================================================
// ����������
//=============================================================================
HRESULT InitUIBonus(void)
{
	BonusGage.Init(TEX_BONUSGAGEFRAME, TEX_BONUSGAGE);
	BonusGage.Init(BONUSGAGE_SIZE_X, BONUSGAGE_SIZE_Y, BONUSGAGE_POS_X, BONUSGAGE_POS_Y);
		
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitUIBonus(void)
{
	BonusGage.Uninit();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawUIBonus(void)
{
	BonusGage.Draw();
}

float gagelong = 0.5f;
//=============================================================================
// �X�V����
//=============================================================================
void UpdateUIBonus(void)
{

	if (GetKeyboardPress(DIK_0))
	{
		gagelong += 0.01f;
		if (gagelong >= 1.0f)
		{
			gagelong = 1.0f;
		}
	}
	if (GetKeyboardPress(DIK_9))
	{
		gagelong -= 0.01f;
		if (gagelong <= 0.0f)
		{
			gagelong = 0.0f;
		}

	}
	BonusGage.Update(gagelong);
}
