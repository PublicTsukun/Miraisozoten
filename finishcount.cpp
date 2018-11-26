//=============================================================================
//
// �t�B�[���h���� [field.cpp]
//
//=============================================================================
#include "Library\Counter.h"
#include "finishcount.h"
#include "Library\ObjectBase2D.h"

#include "timer.h"
#include "GameSound.h"
#include "SceneManager.h"

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
			else
			{
				PlaySE(FINISH_COUNT);
			}

		}
	}


};
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CountEff FinishCount;
C2DObject FinishLogo;


int FinishTimer;
bool FinishTimerUse;
float FinishAngle;

int ChangeCount;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitFinishCount(void)
{

	FinishCount.Set(60, 6, SCREEN_CENTER_X, SCREEN_CENTER_Y, RS_X(0.1), RS_Y(0.4), FINISHCOUNT_TEX);
	FinishLogo.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, 650.0 , 150.0 , FINISHLOGO_TEX);
	FinishCount.Use = false;

	FinishTimer = 0;
	FinishTimerUse = false;
	FinishAngle = 0.0;
	FinishCount.FinishScale = 0.0f;


	ChangeCount = 0;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFinishCount(void)
{

	FinishCount.Release();
	FinishLogo.Release();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawFinishCount(void)
{
	if (FinishCount.Use&&RestTimer()<=5)
	{
		FinishCount.Draw();
	}

	if (FinishTimerUse)
	{
		FinishLogo.Draw();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFinishCount(void)
{
	if (RestTimer() == 6)
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

	if (FinishTimerUse&&RestTimer() <= 0)
	{
		ChangeCount++;
		if (ChangeCount > 180)
		{
			Scene::SetScene(SCENE_RESULT);
		}
	}
}
