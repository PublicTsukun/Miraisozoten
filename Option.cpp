#include "GamePause.h"
#include "Library\Common.h"
#include "Library\ObjectBase2D.h"
#include "Library\Input.h"
#include "startcount.h"
#include "GameSound.h"
#include "Library\DebugProcess.h"
#include "Option.h"




enum {
	LOGO,
	GAGE,
	GAGE_FRAME,
	TUNE_MAX,
};
static C2DObject Sound;
static C2DObject BGMTune[TUNE_MAX];
static C2DObject SETune[TUNE_MAX];
static C2DObject SoundBack;


int		ChoiceNoS;
float	SoundBackScl;

void InitOption(void)
{
	Sound.Init(RS_X(0.5f), RS_Y(0.2f), RS_X(0.15f), RS_Y(0.07f), "data/TEXTURE/UI/ポーズ画面/サウンド調整.png");

	BGMTune[LOGO].Init(RS_X(0.35f), RS_Y(0.30f), RS_X(0.15f), RS_Y(0.07f), "data/TEXTURE/UI/ポーズ画面/BGM.png");
	BGMTune[GAGE].Init(RS_X(0.6f), RS_Y(0.30f), RS_X(0.15f), RS_Y(0.2f), "data/TEXTURE/UI/ポーズ画面/音量中身.png");
	BGMTune[GAGE_FRAME].Init(RS_X(0.6f), RS_Y(0.30f), RS_X(0.15f), RS_Y(0.2f), "data/TEXTURE/UI/ポーズ画面/音量バー.png");
	SETune[LOGO].Init(RS_X(0.35f), RS_Y(0.4f), RS_X(0.15f), RS_Y(0.07f), "data/TEXTURE/UI/ポーズ画面/SE.png");
	SETune[GAGE].Init(RS_X(0.6f), RS_Y(0.4f), RS_X(0.15f), RS_Y(0.2f), "data/TEXTURE/UI/ポーズ画面/音量中身.png");
	SETune[GAGE_FRAME].Init(RS_X(0.6f), RS_Y(0.4f), RS_X(0.15f), RS_Y(0.2f), "data/TEXTURE/UI/ポーズ画面/音量バー.png");

	SoundBack.Init(RS_X(0.5f), RS_Y(0.8f), RS_X(0.15f), RS_Y(0.07f), "data/TEXTURE/UI/ポーズ画面/もどる.png");

	ChoiceNoS = 0;
	SoundBackScl = 0.0f;

}

void UninitOption(void)
{
	Sound.Release();
	SoundBack.Release();
	for (int i = 0; i < TUNE_MAX; i++)
	{
		BGMTune[i].Release();
		SETune[i].Release();
	}

}

void UpdateOption(void)
{
	if (GetKeyboardTrigger(DIK_UP))
	{
		ChoiceNoS -= 1;
		PlaySE(CURSOL);
	}
	else if (GetKeyboardTrigger(DIK_DOWN))
	{
		ChoiceNoS += 1;
		PlaySE(CURSOL);
	}
	ChoiceNoS += 3;
	ChoiceNoS %= 3;

	if (ChoiceNoS == 0)
	{
		BGMTune[LOGO].SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		SETune[LOGO].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SoundBack.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SoundBack.SetStatus(1.0f, 0.0f);
		BGMVolumeTurning();
	}
	else if (ChoiceNoS == 1)
	{
		BGMTune[LOGO].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SETune[LOGO].SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		SoundBack.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SoundBack.SetStatus(1.0f, 0.0f);
		SEVolumeTurning();
	}
	else if (ChoiceNoS == 2)
	{
		BGMTune[LOGO].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SETune[LOGO].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SoundBack.SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

		float Scale;
		SoundBackScl += 0.05f;

		Scale = (sinf(SoundBackScl) / 8.0) + 1.125f;
		SoundBack.SetStatus(Scale, 0.0f);
		PrintDebugProcess("Scale %f\n", Scale);



	}

	//=======================================================================
	//ゲージ更新
	//=======================================================================
	float SESoundPer;
	Vector3 SEGagePos[2];

	SESoundPer = (SE_VOLUME_MIN - (float)VolumeCheckSE()) / (SE_VOLUME_MIN - SE_VOLUME_MAX);
	SEGagePos[0].y = RS_Y(0.4f) - RS_Y(0.2f);
	SEGagePos[1].y = RS_Y(0.4f) + RS_Y(0.2f);
	SEGagePos[0].x = (RS_X(0.6f) - RS_X(0.15f)) + RS_X(0.3)*SESoundPer;
	SEGagePos[1].x = (RS_X(0.6f) - RS_X(0.15f)) + RS_X(0.3)*SESoundPer;
	SEGagePos[0].z = 0.0f;
	SEGagePos[1].z = 0.0f;
	SETune[GAGE].SetVertex(1, SEGagePos[0]);
	SETune[GAGE].SetVertex(3, SEGagePos[1]);

	float BGMSoundPer;
	Vector3 BGMGagePos[2];

	BGMSoundPer = ((BGM_VOLUME_MIN ) - (float)VolumeCheckBGM()) / (BGM_VOLUME_MIN - BGM_VOLUME_MAX);
	BGMGagePos[0].y = RS_Y(0.3f) - RS_Y(0.2f);
	BGMGagePos[1].y = RS_Y(0.3f) + RS_Y(0.2f);
	BGMGagePos[0].x = (RS_X(0.6f) - RS_X(0.15f)) + RS_X(0.3)*BGMSoundPer;
	BGMGagePos[1].x = (RS_X(0.6f) - RS_X(0.15f)) + RS_X(0.3)*BGMSoundPer;
	BGMGagePos[0].z = 0.0f;
	BGMGagePos[1].z = 0.0f;
	BGMTune[GAGE].SetVertex(1, BGMGagePos[0]);
	BGMTune[GAGE].SetVertex(3, BGMGagePos[1]);
}

void DrawOption(void)
{
		Sound.Draw();
		for (int i = 0; i < TUNE_MAX; i++)
		{
			BGMTune[i].Draw();
			SETune[i].Draw();
			SoundBack.Draw();
		}

}

int GetCursol(void)
{
	return ChoiceNoS;
}