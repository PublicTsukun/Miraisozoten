//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#include "Library\Counter.h"
#include "startcount.h"
#include "Library\ObjectBase2D.h"

#include "timer.h"

#include "StageManager.h"
#include "GameSound.h"


//*****************************************************************************
// グローバル変数
//*****************************************************************************
CountDown StartCount;
C2DObject StartLogo;

int LogoTimer;
bool LogoTimerUse;
float LogoAlpha;
float LogoScale;

int SoundCount;
int CountInter;

bool Timer;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStartCount(void)
{

	StartCount.Set(60, 3, SCREEN_CENTER_X, SCREEN_CENTER_Y, RS_X(0.1), RS_Y(0.2), STARTCOUNT_TEX);
	StartLogo.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, 650.0 / 2, 150.0 / 2, STARTLOGO_TEX);

	LogoTimer = 0;
	LogoTimerUse = false;
	LogoAlpha = 1.0;
	LogoScale = 0.0f;
	
	Timer = false;

	SoundCount = 4;
	CountInter = 10;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStartCount(void)
{

	StartCount.Release();
	StartLogo.Release();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStartCount(void)
{
	if (StartCount.ActiveCheck())
	{
		StartCount.Draw();
	}

	if (LogoTimerUse)
	{
		StartLogo.Draw();
		GameStart();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStartCount(void)
{
	StartCount.Animation();

	if (SoundCount)
	{
		CountInter--;
	}
	if (CountInter == 0)
	{
		SoundCount--;
		CountInter = 60;
		PlaySE(START + SoundCount);
	}

	if (StartCount.ActiveCheck() == false)
	{
		if (!Timer)
		{
			TimerSet(COUNT);
			Timer = true;
		}
		LogoTimerUse = true;
	}
	else
	{
		TimerSet(STOP);
	}

	if (LogoTimerUse)
	{
		
		LogoAlpha -= 0.015f;
		LogoScale += 0.05f;
		StartLogo.SetStatus(LogoScale, 0.0f);
		StartLogo.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, LogoAlpha));

		if (LogoAlpha <= 0.0f)
		{
			LogoTimerUse = false;
		}
	}
}

void SetStartCount(int no)
{
	StartCount.Set(60, no, RS_X(0.1), RS_Y(0.2));
	SoundCount = 4;
	LogoAlpha = 1.0;
	LogoScale = 0.0f;
	CountInter = 10;
	Timer = false;

}

bool CheckLogoUse(void)
{
	return LogoTimerUse;
}
bool CheckCountActive(void)
{
	return StartCount.ActiveCheck();
}