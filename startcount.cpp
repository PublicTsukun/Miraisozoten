//=============================================================================
//
// �t�B�[���h���� [field.cpp]
//
//=============================================================================
#include "Library\Counter.h"
#include "startcount.h"
#include "Library\ObjectBase2D.h"

#include "timer.h"

#include "StageManager.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CountDown StartCount;
C2DObject StartLogo;


int LogoTimer;
bool LogoTimerUse;
float LogoAlpha;
float LogoScale;


//=============================================================================
// ����������
//=============================================================================
HRESULT InitStartCount(void)
{

	StartCount.Set(60, 3, SCREEN_CENTER_X, SCREEN_CENTER_Y, RS_X(0.1), RS_Y(0.2), STARTCOUNT_TEX);
	StartLogo.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, 650.0 / 2, 150.0 / 2, STARTLOGO_TEX);

	LogoTimer = 0;
	LogoTimerUse = false;
	LogoAlpha = 1.0;
	LogoScale = 0.0f;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitStartCount(void)
{

	StartCount.Release();
	StartLogo.Release();

}

//=============================================================================
// �`�揈��
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
		UnFreezeStage();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStartCount(void)
{

	StartCount.Animation();

	if (StartCount.ActiveCheck() == false)
	{
		TimerSet(COUNT);
		LogoTimerUse = true;
	}

	if (LogoTimerUse)
	{
		
		LogoAlpha -= 0.015;
		LogoScale += 0.05f;
		StartLogo.SetStatus(LogoScale, 0.0f);
		StartLogo.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, LogoAlpha));
	}
}
