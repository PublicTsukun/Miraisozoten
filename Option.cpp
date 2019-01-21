#include "Option.h"
#include "GamePause.h"
#include "Library\Common.h"
#include "Library\ObjectBase2D.h"
#include "Library\Input.h"
#include "startcount.h"
#include "GameSound.h"
#include "Library\DebugProcess.h"
#include "AimPointer.h"


#define SOUND_POS_X		(RS_X(0.5f))
#define SOUND_POS_Y		(RS_Y(0.15f))
#define	SOUND_SIZE_X	(13 * 12.0f)
#define	SOUND_SIZE_Y	( 3 * 12.0f)

#define JOYCON_POS_X	(RS_X(0.5f))
#define JOYCON_POS_Y	(RS_Y(0.45f))
#define	JOYCON_SIZE_X	(13 * 14.0f)
#define	JOYCON_SIZE_Y	( 3 * 14.0f)

#define	BGMLOGO_POS_X	(RS_X(0.30f))
#define	BGMLOGO_POS_Y	(RS_Y(0.24f))
#define	BGMLOGO_SIZE_X	(13 * 10.0f)
#define	BGMLOGO_SIZE_Y	( 3 * 10.0f)
#define	BGMGAGE_POS_X	(RS_X(0.55f))
#define	BGMGAGE_POS_Y	(RS_Y(0.24f))

#define	SELOGO_POS_X	(RS_X(0.30f))
#define	SELOGO_POS_Y	(RS_Y(0.32f))
#define	SELOGO_SIZE_X	(13 * 10.0f)
#define	SELOGO_SIZE_Y	( 3 * 10.0f)
#define	SEGAGE_POS_X	(RS_X(0.55f))
#define	SEGAGE_POS_Y	(RS_Y(0.32f))

#define	GAGE_SIZE_X (200.0f)
#define	GAGE_SIZE_Y ( 20.0f)

#define OPTIONBACK_POS_X	(RS_X(0.5f))
#define OPTIONBACK_POS_Y	(RS_Y(0.85f))
#define OPTIONBACK_SIZE_X	(13 * 12.0f)
#define	OPTIONBACK_SIZE_Y	( 3 * 12.0f)


class AdjustmentGauge
{
	class GaugePorygon : public C2DObject
	{
	public:
		void SetFPVertex(float value)
		{// value : 0.0f ～ 1.0f
			float x = -Size.x + (Size.x * 2.0f * value);
			this->Vertex[0].coord = Vector3(-Size.x + Position.x, -Size.y + Position.y, 0.0f);
			this->Vertex[1].coord = Vector3(      x + Position.x, -Size.y + Position.y, 0.0f);
			this->Vertex[2].coord = Vector3(-Size.x + Position.x,  Size.y + Position.y, 0.0f);
			this->Vertex[3].coord = Vector3(      x + Position.x,  Size.y + Position.y, 0.0f);
		}
	};

private:
	C2DObject    Name;
	C2DObject    Frame;
	GaugePorygon Gage;
	float Min;
	float Max;

public:
	void Init(float posX, float posY, float sizX, float sizY, float min, float max);
	void Draw(int type = 0);
	void Uninit();
	void SetNameTag(float posX, float posY, float sizX, float sizY, const char *texture);

	void SetValue(float value);
	void SetColor(DxColor color);
};

void AdjustmentGauge::Init(float posX, float posY, float sizX, float sizY, float min, float max)
{
	this->Frame.Init(posX, posY, sizX, sizY, "data/TEXTURE/UI/ポーズ画面/ゲージ枠.png");
	this->Gage.Init(posX, posY, sizX - sizY * 0.05f, sizY * 0.95f);
	this->Gage.SetVertex(0xFFFFAFDD);
	this->Min = min;
	this->Max = max;
}
void AdjustmentGauge::Draw(int type)
{
	if (type)
		this->Name.Draw();
	this->Gage.Draw();
	this->Frame.Draw();
}
void AdjustmentGauge::Uninit()
{
	this->Frame.Release();
	this->Gage.Release();
}
void AdjustmentGauge::SetNameTag(float posX, float posY, float sizX, float sizY, const char *texture)
{
	this->Name.Init(posX, posY, sizX, sizY, texture);
}
void AdjustmentGauge::SetValue(float value)
{
	if (value > Max) value = Max;
	if (value < Min) value = Min;
	this->Gage.SetFPVertex((value - Min) / (Max - Min));
}
void AdjustmentGauge::SetColor(DxColor color)
{
	this->Name.SetVertex(color);
}


enum {
	LOGO,
	GAGE,
	GAGE_FRAME,
	TUNE_MAX,
};
static C2DObject OptionBack;
static C2DObject Sound;
static C2DObject JoyCon;
static C2DObject BGMTune[TUNE_MAX];
static C2DObject SETune[TUNE_MAX];
static AdjustmentGauge GyroSensitivityX;
static AdjustmentGauge GyroSensitivityY;
static AdjustmentGauge GyroCorrection;

int		ChoiceNoS;
float	OptionBackScl;

void InitOption(void)
{
	Sound.Init(SOUND_POS_X, SOUND_POS_Y, SOUND_SIZE_X, SOUND_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/サウンド調整.png");

	BGMTune[LOGO].Init(BGMLOGO_POS_X, BGMLOGO_POS_Y, BGMLOGO_SIZE_X, BGMLOGO_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/BGM.png");
	BGMTune[GAGE].Init(BGMGAGE_POS_X, BGMGAGE_POS_Y, GAGE_SIZE_X, GAGE_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/音量中身.png");
	BGMTune[GAGE_FRAME].Init(BGMGAGE_POS_X, BGMGAGE_POS_Y, GAGE_SIZE_X, GAGE_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/ゲージ枠.png");

	SETune[LOGO].Init(SELOGO_POS_X, SELOGO_POS_Y, SELOGO_SIZE_X, SELOGO_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/SE.png");
	SETune[GAGE].Init(SEGAGE_POS_X, SEGAGE_POS_Y, GAGE_SIZE_X, GAGE_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/音量中身.png");
	SETune[GAGE_FRAME].Init(SEGAGE_POS_X, SEGAGE_POS_Y, GAGE_SIZE_X, GAGE_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/ゲージ枠.png");

	JoyCon.Init(JOYCON_POS_X, JOYCON_POS_Y, JOYCON_SIZE_X, JOYCON_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/コントローラー調整.png");

	GyroSensitivityX.Init(RS_X(0.55f), RS_Y(0.54f), 200, 20, 0, 10);
	GyroSensitivityY.Init(RS_X(0.55f), RS_Y(0.62f), 200, 20, 0, 10);
	GyroCorrection.Init(  RS_X(0.55f), RS_Y(0.70f), 200, 20, 0, 10);
	GyroSensitivityX.SetNameTag(RS_X(0.30f), RS_Y(0.54f), 130, 30, "data/TEXTURE/UI/ポーズ画面/感度X.png");
	GyroSensitivityY.SetNameTag(RS_X(0.30f), RS_Y(0.62f), 130, 30, "data/TEXTURE/UI/ポーズ画面/感度Y.png");
	GyroCorrection.SetNameTag(  RS_X(0.30f), RS_Y(0.70f), 130, 30, "data/TEXTURE/UI/ポーズ画面/補正.png");
	float *correct = AimPointer::GetCorrection();
	Vector2 *sense = AimPointer::GetSensitivity();
	GyroSensitivityX.SetValue(sense->x);
	GyroSensitivityY.SetValue(sense->y);
	GyroCorrection.SetValue(*correct);

	OptionBack.Init(OPTIONBACK_POS_X, OPTIONBACK_POS_Y, OPTIONBACK_SIZE_X, OPTIONBACK_SIZE_Y, "data/TEXTURE/UI/ポーズ画面/もどる.png");

	ChoiceNoS = 0;
	OptionBackScl = 0.0f;
}

void UninitOption(void)
{
	Sound.Release();
	JoyCon.Release();
	OptionBack.Release();
	for (int i = 0; i < TUNE_MAX; i++)
	{
		BGMTune[i].Release();
		SETune[i].Release();
	}
	GyroSensitivityX.Uninit();
	GyroSensitivityY.Uninit();
	GyroCorrection.Uninit();

}

void UpdateOption(void)
{
	if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(LSTICK_UP))
	{
		ChoiceNoS -= 1;
		PlaySE(CURSOL);
	}
	else if (GetKeyboardTrigger(DIK_DOWN) || IsButtonTriggered(LSTICK_DOWN))
	{
		ChoiceNoS += 1;
		PlaySE(CURSOL);
	}
	ChoiceNoS += 6;
	ChoiceNoS %= 6;

	if (ChoiceNoS == 0)
	{// BGM
		BGMTune[LOGO].SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		SETune[LOGO].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		OptionBack.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		OptionBack.SetStatus(1.0f, 0.0f);
		BGMVolumeTurning();
	}
	else if (ChoiceNoS == 1)
	{// SE
		BGMTune[LOGO].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SETune[LOGO].SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		GyroSensitivityX.SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SEVolumeTurning();
	}
	else if (ChoiceNoS == 2)
	{// 感度X
		Vector2 *sense = AimPointer::GetSensitivity();
		SETune[LOGO].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		GyroSensitivityX.SetColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		GyroSensitivityY.SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		if (GetKeyboardPress(DIK_LEFT))  sense->x -= 0.1f;
		if (GetKeyboardPress(DIK_RIGHT)) sense->x += 0.1f;
		if (sense->x <  0.0f) sense->x = 0.0f;
		if (sense->x > 10.0f) sense->x = 10.0f;
		GyroSensitivityX.SetValue(sense->x);
	}
	else if (ChoiceNoS == 3)
	{// 感度Y
		Vector2 *sense = AimPointer::GetSensitivity();
		GyroSensitivityX.SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		GyroSensitivityY.SetColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		GyroCorrection.SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		if (GetKeyboardPress(DIK_LEFT))  sense->y -= 0.1f;
		if (GetKeyboardPress(DIK_RIGHT)) sense->y += 0.1f;
		if (sense->y <  0.0f) sense->y = 0.0f;
		if (sense->y > 10.0f) sense->y = 10.0f;
		GyroSensitivityY.SetValue(sense->y);
	}
	else if (ChoiceNoS == 4)
	{// 補正
		float *correct = AimPointer::GetCorrection();
		GyroSensitivityY.SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		GyroCorrection.SetColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		OptionBack.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		OptionBack.SetStatus(1.0f, 0.0f);

		if (GetKeyboardPress(DIK_LEFT))  *correct -= 0.1f;
		if (GetKeyboardPress(DIK_RIGHT)) *correct += 0.1f;
		if (*correct <  0.0f) *correct = 0.0f;
		if (*correct > 10.0f) *correct = 10.0f;
		GyroCorrection.SetValue(*correct);
	}
	else if (ChoiceNoS == 5)
	{// 戻る
		BGMTune[LOGO].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		SETune[LOGO].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		OptionBack.SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		GyroCorrection.SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

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
	SEGagePos[0].y = SEGAGE_POS_Y - GAGE_SIZE_Y;
	SEGagePos[1].y = SEGAGE_POS_Y + GAGE_SIZE_Y;
	SEGagePos[0].x = (SEGAGE_POS_X - GAGE_SIZE_X) + GAGE_SIZE_X * 2 * SESoundPer;
	SEGagePos[1].x = (SEGAGE_POS_X - GAGE_SIZE_X) + GAGE_SIZE_X * 2 * SESoundPer;
	SEGagePos[0].z = 0.0f;
	SEGagePos[1].z = 0.0f;
	SETune[GAGE].SetVertex(1, SEGagePos[0]);
	SETune[GAGE].SetVertex(3, SEGagePos[1]);

	float BGMSoundPer;
	Vector3 BGMGagePos[2];

	BGMSoundPer = ((BGM_VOLUME_MIN ) - (float)VolumeCheckBGM()) / (BGM_VOLUME_MIN - BGM_VOLUME_MAX);
	BGMGagePos[0].y = BGMGAGE_POS_Y - GAGE_SIZE_Y;
	BGMGagePos[1].y = BGMGAGE_POS_Y + GAGE_SIZE_Y;
	BGMGagePos[0].x = (BGMGAGE_POS_X - GAGE_SIZE_X) + GAGE_SIZE_X * 2 * BGMSoundPer;
	BGMGagePos[1].x = (BGMGAGE_POS_X - GAGE_SIZE_X) + GAGE_SIZE_X * 2 * BGMSoundPer;
	BGMGagePos[0].z = 0.0f;
	BGMGagePos[1].z = 0.0f;
	BGMTune[GAGE].SetVertex(1, BGMGagePos[0]);
	BGMTune[GAGE].SetVertex(3, BGMGagePos[1]);
}

void DrawOption(void)
{
	Sound.Draw();
	OptionBack.Draw();
	JoyCon.Draw();
	for (int i = 0; i < TUNE_MAX; i++)
	{
		BGMTune[i].Draw();
		SETune[i].Draw();
	}
	GyroSensitivityX.Draw(1);
	GyroSensitivityY.Draw(1);
	GyroCorrection.Draw(1);
}

int GetCursol(void)
{
	return ChoiceNoS;
}

