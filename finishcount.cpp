//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#include "Library\Counter.h"
#include "finishcount.h"
#include "Library\ObjectBase2D.h"

#include "timer.h"
#include "GameSound.h"


class CountEff : public CountDown
{
public:
	bool Use;
	float FinishScale;

	int GetTime(void)
	{
		return this->Time;
	}

	void FinishCount(void)
	{
		this->Counter++;
		if (this->Counter >= this->Interval
			&&this->Time > 0)
		{
			this->Counter = 0;
			this->Time--;
			this->FinishScale = 0.0f;
			SetNumber(Time);

			if (this->Time == 0)
			{
				this->Use = false;
				PlaySE(FINISH);

			}

		}
	}


};
//*****************************************************************************
// グローバル変数
//*****************************************************************************
CountEff FinishCount;
C2DObject FinishLogo;


int FinishTimer;
bool FinishTimerUse;
float FinishAngle;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitFinishCount(void)
{

	FinishCount.Set(60, 5, SCREEN_CENTER_X, SCREEN_CENTER_Y, RS_X(0.1), RS_Y(0.4), FINISHCOUNT_TEX);
	FinishLogo.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, 650.0 , 150.0 , FINISHLOGO_TEX);
	FinishCount.Use = false;

	FinishTimer = 0;
	FinishTimerUse = false;
	FinishAngle = 0.0;
	FinishCount.FinishScale = 0.0f;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFinishCount(void)
{

	FinishCount.Release();
	FinishLogo.Release();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawFinishCount(void)
{
	if (FinishCount.Use)
	{
		FinishCount.Draw();
	}

	if (FinishTimerUse)
	{
		FinishLogo.Draw();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFinishCount(void)
{
	if (RestTimer() == 5)
	{
		FinishCount.Use=true;
	}

	if (FinishCount.Use)
	{
		FinishCount.FinishCount();
		FinishCount.FinishScale += 0.2f;
		if (FinishCount.FinishScale >= 1.0f)
		{
			FinishCount.FinishScale = 1.0f;
		}
			
		FinishAngle = (D3DX_PI / 8.0f) - (D3DX_PI / 4.0f)*(float)(FinishCount.GetTime() % 2);
		FinishCount.SetStatus(FinishCount.FinishScale, FinishAngle);
		FinishCount.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
	}

	if (FinishCount.ActiveCheck() == false)
	{
		FinishTimerUse = true;
	}

	if (FinishTimerUse)
	{

		FinishCount.FinishScale += 0.05f;
		if (FinishCount.FinishScale >= 1.0f)
		{
			FinishCount.FinishScale = 1.0f;
		}
		FinishLogo.SetStatus(FinishCount.FinishScale, 0.0f);
		FinishLogo.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
