#include "GamePause.h"
#include "Library\Common.h"
#include "Library\ObjectBase2D.h"
#include "Library\Input.h"
#include "startcount.h"
#include "GameSound.h"
#include "Library\DebugProcess.h"
#include "Option.h"

#define SOUND_POS_X		(RS_X(0.5f))
#define SOUND_POS_Y		(RS_Y(0.2f))
#define	SOUND_SIZE_X	(RS_X(0.15f))
#define	SOUND_SIZE_Y	(RS_Y(0.07f))
#define	BGMLOGO_POS_X	(RS_X(0.35f))
#define	BGMLOGO_POS_Y	(RS_Y(0.30f))
#define	BGMLOGO_SIZE_X	(RS_X(0.15f))
#define	BGMLOGO_SIZE_Y	(RS_Y(0.07f))
#define	BGMGAGE_POS_X	(RS_X(0.6f))
#define	BGMGAGE_POS_Y	(RS_Y(0.30f))
#define	BGMGAGE_SIZE_X	(RS_X(0.15f))
#define	BGMGAGE_SIZE_Y	(RS_Y(0.2f))

#define	SELOGO_POS_X	(RS_X(0.35f))
#define	SELOGO_POS_Y	(RS_Y(0.40f))
#define	SELOGO_SIZE_X	(RS_X(0.15f))
#define	SELOGO_SIZE_Y	(RS_Y(0.07f))
#define	SEGAGE_POS_X	(RS_X(0.6f))
#define	SEGAGE_POS_Y	(RS_Y(0.40f))
#define	SEGAGE_SIZE_X	(RS_X(0.15f))
#define	SEGAGE_SIZE_Y	(RS_Y(0.2f))

#define OPTIONBACK_POS_X	(RS_X(0.5f))
#define OPTIONBACK_POS_Y	(RS_Y(0.8f))
#define OPTIONBACK_SIZE_X	(RS_X(0.15f))
#define	OPTIONBACK_SIZE_Y	(RS_Y(0.07f))

enum {
	LOGO,
	GAGE,
	GAGE_FRAME,
	TUNE_MAX,
};
static C2DObject Sound;
static C2DObject BGMTune[TUNE_MAX];
static C2DObject SETune[TUNE_MAX];
static C2DObject OptionBack;


int		ChoiceNoS;
float	OptionBackScl;

void InitOption(void)
{
	Sound.Init(SOUND_POS_X, SOUND_POS_Y, SOUND_SIZE_X, SOUND_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/サウンド調整.png");

	BGMTune[LOGO].Init(BGMLOGO_POS_X, BGMLOGO_POS_Y, BGMLOGO_SIZE_X, BGMLOGO_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/BGM.png");
	BGMTune[GAGE].Init(BGMGAGE_POS_X, BGMGAGE_POS_Y, BGMGAGE_SIZE_X, BGMGAGE_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/音量中身.png");
	BGMTune[GAGE_FRAME].Init(BGMGAGE_POS_X, BGMGAGE_POS_Y, BGMGAGE_SIZE_X, BGMGAGE_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/音量バー.png");

	SETune[LOGO].Init(SELOGO_POS_X, SELOGO_POS_Y, SELOGO_SIZE_X, SELOGO_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/SE.png");
	SETune[GAGE].Init(SEGAGE_POS_X, SEGAGE_POS_Y, SEGAGE_SIZE_X, SEGAGE_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/音量中身.png");
	SETune[GAGE_FRAME].Init(SEGAGE_POS_X, SEGAGE_POS_Y, SEGAGE_SIZE_X, SEGAGE_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/音量バー.png");

	OptionBack.Init(OPTIONBACK_POS_X, OPTIONBACK_POS_Y, OPTIONBACK_SIZE_X, OPTIONBACK_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/もどる.png");

	ChoiceNoS = 0;
	OptionBackScl = 0.0f;

}

void UninitOption(void)
{
	Sound.Release();
	OptionBack.Release();
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
		OptionBack.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		OptionBack.SetStatus(1.0f, 0.0f);
		BGMVolumeTurning();
	}
	else if (ChoiceNoS == 1)
	{
		BGMTune[LOGO].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SETune[LOGO].SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		OptionBack.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		OptionBack.SetStatus(1.0f, 0.0f);
		SEVolumeTurning();
	}
	else if (ChoiceNoS == 2)
	{
		BGMTune[LOGO].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SETune[LOGO].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		OptionBack.SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

		float Scale;
		OptionBackScl += 0.05f;

		Scale = (sinf(OptionBackScl) / 8.0) + 1.125f;
		OptionBack.SetStatus(Scale, 0.0f);
		PrintDebugProcess("Scale %f\n", Scale);



	}

	//=======================================================================
	//ゲージ更新
	//=======================================================================
	float SESoundPer;
	Vector3 SEGagePos[2];

	SESoundPer = (SE_VOLUME_MIN - (float)VolumeCheckSE()) / (SE_VOLUME_MIN - SE_VOLUME_MAX);
	SEGagePos[0].y = SEGAGE_POS_Y - SEGAGE_SIZE_Y;
	SEGagePos[1].y = SEGAGE_POS_Y + SEGAGE_SIZE_Y;
	SEGagePos[0].x = (SEGAGE_POS_X - SEGAGE_SIZE_X) + SEGAGE_SIZE_X * 2 * SESoundPer;
	SEGagePos[1].x = (SEGAGE_POS_X - SEGAGE_SIZE_X) + SEGAGE_SIZE_X * 2 * SESoundPer;
	SEGagePos[0].z = 0.0f;
	SEGagePos[1].z = 0.0f;
	SETune[GAGE].SetVertex(1, SEGagePos[0]);
	SETune[GAGE].SetVertex(3, SEGagePos[1]);

	float BGMSoundPer;
	Vector3 BGMGagePos[2];

	BGMSoundPer = ((BGM_VOLUME_MIN ) - (float)VolumeCheckBGM()) / (BGM_VOLUME_MIN - BGM_VOLUME_MAX);
	BGMGagePos[0].y = BGMGAGE_POS_Y - BGMGAGE_SIZE_Y;
	BGMGagePos[1].y = BGMGAGE_POS_Y + BGMGAGE_SIZE_Y;
	BGMGagePos[0].x = (BGMGAGE_POS_X - BGMGAGE_SIZE_X) + BGMGAGE_SIZE_X * 2 * BGMSoundPer;
	BGMGagePos[1].x = (BGMGAGE_POS_X - BGMGAGE_SIZE_X) + BGMGAGE_SIZE_X * 2 * BGMSoundPer;
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
			OptionBack.Draw();
		}

}

int GetCursol(void)
{
	return ChoiceNoS;
}