#include "voicetank.h"
#include "Library\Input.h"
#include "Library\/DebugProcess.h"
#include "MicTest.h"
#include "UIBonus.h"

#define VTG_MAX (1000)
#define VTG_ARG (30)

static Vector2 vtPosi   = Vector2(95, 550);
static float   vtScale  = 0.8f;
static float   vtValue  = 0.0f;
static int     vtVolume = 0;
static int     vtArg[VTG_ARG] = { 0 };

static Vector2 vtsBack = Vector2(70, 160);
static Vector2 vtsTank = Vector2(100, 200);
//static Vector2 vtsVolu = Vector2(59, 157);

void CEnergyTankUI::Init()
{
	MicTestInit();

	this->Back.Init(vtPosi.x, vtPosi.y, vtsBack.x, vtsBack.y);
	this->Back.SetVertex(0xFF888888L);

	this->Liquid.Init(vtPosi.x, vtPosi.y, vtsBack.x, vtsBack.y);
	this->Liquid.SetVertex(0xFF00FFFFL);

	this->Bubble[0].Init(vtPosi.x, vtPosi.y, vtsBack.x, vtsBack.y, "data/TEXTURE/UI/タンク/泡.png");
	this->Bubble[1].Init(vtPosi.x, vtPosi.y, vtsBack.x, vtsBack.y, "data/TEXTURE/UI/タンク/泡2.png");

	this->Tank.Init(    vtPosi.x, vtPosi.y, vtsTank.x, vtsTank.y, "data/TEXTURE/UI/タンク/ボイスタンク2.png");
	this->Volume.Init(  vtPosi.x, vtPosi.y, vtsTank.x, vtsTank.y, "data/TEXTURE/UI/タンク/ボイスゲージ.png");
	this->VoiceTen.Init(vtPosi.x, vtPosi.y, vtsTank.x, vtsTank.y, "data/TEXTURE/UI/タンク/ボイスゲージ枠.png");
}

void CEnergyTankUI::Update()
{
	if (GetKeyboardTrigger(DIK_V))
	{
		if (GetKeyboardPress(DIK_LSHIFT))
		{
			MicReStart();
		}
	}

	int sum = 0;
	if (GetFiver())
	{
		vtArg[VTG_ARG - 1] = 3000;
	}
	else
	{
		vtArg[VTG_ARG - 1] = (int)Absolute(MicTest()) / 10;	// 後に追加 (30 = 値の調整 32,768 -> 1000)
	}
	for (int i = 0; i < VTG_ARG - 1; i++)
	{
		vtArg[i] = vtArg[i + 1];
		sum += vtArg[i];
	}
	vtVolume = sum / VTG_ARG;

#ifdef _DEBUG
	if (IsMouseLeftPressed()) vtVolume += (int)GetMouseY();
	if (IsMouseCenterPressed()) vtPosi += Vector2((float)GetMouseX(), (float)GetMouseY());
	vtScale += (float)GetMouseZ() / 1200.0f;
#endif // _DEBUG

	if (vtVolume <       0) vtVolume =       0;
	if (vtVolume > VTG_MAX) vtVolume = VTG_MAX;

	vtValue = -(float)vtVolume / VTG_MAX;
	vtValue = vtValue * vtsBack.y * 2.0f * vtScale + (vtsBack.y * vtScale);
	vtValue += vtPosi.y;

	this->Back.SetStatus(vtPosi, vtsBack, vtScale, 0.0f);
	this->Liquid.SetStatus(vtPosi, vtsBack, vtScale, 0.0f);
	this->Bubble[0].SetStatus(vtPosi, vtsBack, vtScale, 0.0f);
	this->Bubble[1].SetStatus(vtPosi, vtsBack, vtScale, 0.0f);
	this->Tank.SetStatus(vtPosi, vtsTank, vtScale, 0.0f);
	this->Volume.SetStatus(vtPosi, vtsTank, vtScale, 0.0f);
	this->VoiceTen.SetStatus(vtPosi, vtsTank, vtScale, 0.0f);


	BubbleState[0] += BubbleState[0] >= 1.0f ? -1.0f : 0.005f;;
	BubbleState[1] += BubbleState[1] >= 1.0f ? -1.0f : 0.0075f;;
	this->Bubble[0].SetTexture(2, 0.0f, 1.0f + BubbleState[0]);
	this->Bubble[0].SetTexture(3, 1.0f, 1.0f + BubbleState[0]);

	this->Bubble[1].SetTexture(2, 0.0f, 1.0f + BubbleState[1]);
	this->Bubble[1].SetTexture(3, 1.0f, 1.0f + BubbleState[1]);


	this->Liquid.SetVertex(0, Vector3(vtPosi.x - vtsBack.x * vtScale, vtValue, 0));
	this->Liquid.SetVertex(1, Vector3(vtPosi.x + vtsBack.x * vtScale, vtValue, 0));

	this->Bubble[0].SetVertex(0, Vector3(vtPosi.x - vtsBack.x * vtScale, vtValue, 0));
	this->Bubble[0].SetVertex(1, Vector3(vtPosi.x + vtsBack.x * vtScale, vtValue, 0));
	this->Bubble[0].SetTexture(0, 0.0f, (vtValue - (vtPosi.y - vtsBack.y)) / (vtsBack.y * 2.0f) + BubbleState[0]);
	this->Bubble[0].SetTexture(1, 1.0f, (vtValue - (vtPosi.y - vtsBack.y)) / (vtsBack.y * 2.0f) + BubbleState[0]);

	this->Bubble[1].SetVertex(0, Vector3(vtPosi.x - vtsBack.x * vtScale, vtValue, 0));
	this->Bubble[1].SetVertex(1, Vector3(vtPosi.x + vtsBack.x * vtScale, vtValue, 0));
	this->Bubble[1].SetTexture(0, 0.0f, (vtValue - (vtPosi.y - vtsBack.y)) / (vtsBack.y * 2.0f) + BubbleState[1]);
	this->Bubble[1].SetTexture(1, 1.0f, (vtValue - (vtPosi.y - vtsBack.y)) / (vtsBack.y * 2.0f) + BubbleState[1]);

	const float vtgPos[8] = {
		1.0f,
		0.78f,
		0.665f,
		0.56f,
		0.44f,
		0.322f,
		0.22f,
		0.0f
	};
	int rate;
	     if (vtVolume < 140 * 1) rate = 0;
	else if (vtVolume < 140 * 2) rate = 1;
	else if (vtVolume < 140 * 3) rate = 2;
	else if (vtVolume < 140 * 4) rate = 3;
	else if (vtVolume < 140 * 5) rate = 4;
	else if (vtVolume < 140 * 6) rate = 5;
	else if (vtVolume < 140 * 7) rate = 6;
	else                         rate = 7;

	this->Volume.SetVertex(0, Vector3(vtPosi.x - vtsTank.x * vtScale, (vtPosi.y - vtsTank.y * vtScale) + (vtsTank.y * vtScale * 2.0f) * vtgPos[rate], 0));
	this->Volume.SetVertex(1, Vector3(vtPosi.x + vtsTank.x * vtScale, (vtPosi.y - vtsTank.y * vtScale) + (vtsTank.y * vtScale * 2.0f) * vtgPos[rate], 0));
	this->Volume.SetTexture(0, 0.0f, vtgPos[rate]);
	this->Volume.SetTexture(1, 1.0f, vtgPos[rate]);
	PrintDebugProcess("位置とか : (%f, %f), %f\n", vtPosi.x, vtPosi.y, vtScale);
	PrintDebugProcess("volume : %d\n", vtVolume);
	PrintDebugProcess("vtg : %d, %f\n", rate, vtgPos[rate]);
}

void CEnergyTankUI::Draw()
{
	this->Back.Draw();
	this->Liquid.Draw();
	this->Bubble[0].Draw();
	this->Bubble[1].Draw();
	this->Tank.Draw();
	this->Volume.Draw();
	this->VoiceTen.Draw();
}

void CEnergyTankUI::Uninit()
{
	MicTestUninit();

	this->Back.Release();
	this->Liquid.Release();
	this->Bubble[0].Release();
	this->Bubble[1].Release();
	this->Tank.Release();
	this->Volume.Release();
	this->VoiceTen.Release();
}
