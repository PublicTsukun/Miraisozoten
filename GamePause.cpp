#include "GamePause.h"
#include "Library\Common.h"
#include "Library\ObjectBase2D.h"
#include "Library\Input.h"
#include "SceneManager.h"
#include "startcount.h"
#include "GameSound.h"
#include "Library\DebugProcess.h"
#include "Option.h"

static C2DObject PauseFade;
static C2DObject Back;
static C2DObject BackGame;
static C2DObject BackTitle;
static C2DObject BackCheck;
static C2DObject Yes;
static C2DObject No;
static C2DObject Option;



bool	BackTitleF;
bool	BackCheckF;
bool	OptionF;
int		ChoiceNo;
int		ChoiceNoT;

float	BackTitleScl;
float	BackGameScl;
float	OptionScl;
float	YesScl;
float	NoScl;

void GamePause::Init()
{
	PauseFade.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_CENTER_X, SCREEN_CENTER_Y);
	PauseFade.SetVertex(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f));
	Back.Init(RS_X(0.5f), RS_Y(0.5f), RS_X(0.3f), RS_Y(0.45f), "data/TEXTURE/UI/ポーズ画面/バック白枠.png");
	Back.SetVertex(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	BackGame.Init(RS_X(0.5f), RS_Y(0.3f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/ゲームにもどる.png");
	BackTitle.Init(RS_X(0.5f), RS_Y(0.5f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/タイトルにもどる.png");
	Option.Init(RS_X(0.5f), RS_Y(0.7f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/おぷしょん.png");
	BackCheck.Init(RS_X(0.5f), RS_Y(0.4f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/ほんとにもどる.png");
	Yes.Init(RS_X(0.35f), RS_Y(0.6f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/もどる.png");
	No.Init(RS_X(0.6f), RS_Y(0.6f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/やめとく.png");

	BackTitleF = false;
	BackCheckF = false;
	OptionF = false;
	ChoiceNo = 0;
	ChoiceNoT = 0;

	BackTitleScl = 0.0f;
	BackGameScl = 0.0f;
	YesScl = 0.0f;
	NoScl = 0.0f;

	InitOption();

}

GPR GamePause::Update()
{
	//========================================================
	//タイトルに戻る　ゲームに戻る　オプション
	//========================================================
	if (!BackTitleF
		&& !BackCheckF
		&& !OptionF)
	{
		if (GetKeyboardTrigger(DIK_UP) || IsButtonTriggered(LSTICK_UP))
		{
			ChoiceNo -= 1;
			PlaySE(CURSOL);
		}
		else if (GetKeyboardTrigger(DIK_DOWN) || IsButtonTriggered(LSTICK_DOWN))
		{
			ChoiceNo += 1;
			PlaySE(CURSOL);

		}
		ChoiceNo += 6;
		ChoiceNo %= 6;

		if (ChoiceNo == 0)
		{
			BackGame.SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			BackTitle.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			Option.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			float Scale;
			BackGameScl += 0.05f;
			BackTitleScl = 0.0f;
			OptionScl = 0.0f;

			Scale = (sinf(BackGameScl) / 8.0f) + 1.125f;
			BackGame.SetStatus(Scale, 0.0f);
			BackTitle.SetStatus(1.0f, 0.0f);
			Option.SetStatus(1.0f, 0.0f);

			PrintDebugProcess("Scale %f\n", Scale);

			if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(BUTTON_UP))
			{
				PlaySE(DECIDE);
				Scene::SetScene(SCENE_GAME,false);
				
				if (!CheckLogoUse()&&!CheckCountActive())
				{
					SetStartCount(3);
				}
			}
		}
		else if (ChoiceNo == 1)
		{
			BackTitle.SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			BackGame.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			Option.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			float Scale;
			BackTitleScl += 0.05f;
			BackGameScl = 0.0f;
			OptionScl = 0.0f;

			Scale = (sinf(BackTitleScl) / 8.0f) + 1.125f;
			BackTitle.SetStatus(Scale, 0.0f);
			BackGame.SetStatus(1.0f, 0.0f);
			Option.SetStatus(1.0f, 0.0f);

			PrintDebugProcess("Scale %f\n", Scale);

			if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(BUTTON_UP))
			{
				PlaySE(DECIDE);
				BackTitleF = true;
				BackCheckF = true;
			}
		}
		else if (ChoiceNo == 2)
		{
			BackTitle.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			BackGame.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			Option.SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

			float Scale;
			BackTitleScl = 0.0f;
			BackGameScl = 0.0f;
			OptionScl += 0.05f;

			Scale = (sinf(OptionScl) / 8.0f) + 1.125f;
			BackTitle.SetStatus(1.0f, 0.0f);
			BackGame.SetStatus(1.0f, 0.0f);
			Option.SetStatus(Scale, 0.0f);

			PrintDebugProcess("Scale %f\n", Scale);

			if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(BUTTON_UP))
			{

				PlaySE(DECIDE);
				OptionF = true;
			}


		}
	}

	//==============================================================
	//はい　いいえ
	//==============================================================
	else if (BackTitleF)
	{
		if (GetKeyboardTrigger(DIK_RIGHT) || IsButtonTriggered(LSTICK_RIGHT))
		{
			ChoiceNoT += 1;
			PlaySE(CURSOL);
		}
		else if (GetKeyboardTrigger(DIK_LEFT) || IsButtonTriggered(LSTICK_LEFT))
		{
			ChoiceNoT -= 1;
			PlaySE(CURSOL);
		}
		ChoiceNoT += 2;
		ChoiceNoT %= 2;

		if (ChoiceNoT == 1)
		{
			Yes.SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			No.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			float Scale;
			YesScl += 0.05f;
			NoScl = 0.0f;

			Scale = (sinf(YesScl) / 8.0f) + 1.125f;
			Yes.SetStatus(Scale, 0.0f);
			No.SetStatus(1.0f, 0.0f);
			PrintDebugProcess("Scale %f\n", Scale);


			if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(BUTTON_UP))
			{

				PlaySE(DECIDE);
				Scene::SetScene(SCENE_TITLE,true);
			}
		}
		else if (ChoiceNoT == 0)
		{
			float Scale;
			NoScl += 0.05f;
			YesScl = 0.0f;

			Scale = (sinf(NoScl) / 8.0f) + 1.125f;
			No.SetStatus(Scale, 0.0f);
			Yes.SetStatus(1.0f, 0.0f);
			PrintDebugProcess("Scale %f\n", Scale);

			No.SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			Yes.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(BUTTON_UP))
			{
				PlaySE(DECIDE);
				BackTitleF = false;
				BackCheckF = false;
			}

		}
	}

	//==============================================================
	//音調整
	//==============================================================
	else if (OptionF)
	{
		if ((GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(BUTTON_UP))&& GetCursol()==5)
		{
			PlaySE(DECIDE);
			OptionF = false;
		}
			UpdateOption();

	}
	return GPR::GAMEPAUSERESULT_MAX;
}


void GamePause::Draw()
{
	PauseFade.Draw();
	Back.Draw();

	if (	!BackTitleF
		&&	!BackCheckF
		&&	!OptionF)
	{
		BackGame.Draw();
		BackTitle.Draw();
		Option.Draw();
	}
	if (BackTitleF)
	{
		BackCheck.Draw();
	}

	if (BackCheckF)
	{
		Yes.Draw();
		No.Draw();
	}

	if (OptionF)
	{
		DrawOption();

	}
}


void GamePause::Uninit()
{
	PauseFade.Release();
	Back.Release();
	BackGame.Release();
	BackTitle.Release();
	Option.Release();
	BackCheck.Release();
	Yes.Release();
	No.Release();
	
	UninitOption();

}
