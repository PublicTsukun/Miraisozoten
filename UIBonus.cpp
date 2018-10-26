//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#include "UIBonus.h"
#include "Library/ObjectBase2D.h"
#include "Library/Common.h"
#include "Library\Input.h"
#include "Library\DebugProcess.h"
#include "Library\Color.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
UI2DPercentGauge	BonusGage;	//ボーナスゲージ
C2DObject				a;

int		gagenum=0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitUIBonus(void)
{
	BonusGage.Init(TEX_BONUSGAGEFRAME, TEX_BONUSGAGE);
	BonusGage.Init(BONUSGAGE_POS_X, BONUSGAGE_POS_Y, BONUSGAGE_SIZE_X, BONUSGAGE_SIZE_Y);
		
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitUIBonus(void)
{
	BonusGage.Uninit();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawUIBonus(void)
{
	BonusGage.Draw();
}

float gagelong = 0.5f;
//=============================================================================
// 更新処理
//=============================================================================
void UpdateUIBonus(void)
{

	if (GetKeyboardPress(DIK_0))
	{
		gagelong += 0.01f;
		if (gagelong >= LAST_GAGE)
		{
			gagelong = LAST_GAGE;
		}

		if (gagelong >= FIRST_GAGE)
		{
			gagenum = 1;
			if (gagelong >= SECOND_GAGE)
			{
				gagenum = 2;
				if (gagelong >= LAST_GAGE)
				{
					gagenum = 3;
				}
			}
		}
	}
	if (GetKeyboardPress(DIK_9))
	{
		gagelong -= 0.01f;
		if (gagelong <= (gagenum)*0.333f)
		{
			gagelong = (gagenum)*0.333f;
		}
	}

	if (GetKeyboardTrigger(DIK_8))
	{
		gagenum = 0;
	}
	BonusGage.Update(gagelong);


	float cor=0.0f;

	//cor = BONUSGAGE_SIZE_Y / (tanf(POS_COR_ANG));

	Vector3 pos;
	pos.x = BONUSGAGE_POS_X + ((BONUSGAGE_SIZE_X-6.0f) * 2 * gagelong)+cor;
	pos.y = BONUSGAGE_POS_Y - (BONUSGAGE_SIZE_Y-6.0f);
	pos.z = 0.0f;
	BonusGage.Gage.SetVertex(1,pos);


	BonusGage.Gage.SetTexture(1, gagelong, 0.0f);
	BonusGage.Gage.SetTexture(3, gagelong, 1.0f);
}
