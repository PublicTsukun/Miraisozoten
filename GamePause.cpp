#include "GamePause.h"
#include "Library\Common.h"
#include "Library\ObjectBase2D.h"
#include "Library\Input.h"
#include "SceneManager.h"
#include "startcount.h"
#include "GameSound.h"

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
int		ChoiceNo;
int		ChoiceNoT;

void GamePause::Init()
{
	PauseFade.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_CENTER_X, SCREEN_CENTER_Y);
	PauseFade.SetVertex(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f));
	Back.Init(RS_X(0.5f), RS_Y(0.5f), RS_X(0.3f), RS_Y(0.4f), "data/TEXTURE/UI/ポーズ画面/バック白枠.png");
	Back.SetVertex(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
	BackGame.Init(RS_X(0.5f), RS_Y(0.3f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/ゲームにもどる.png");
	BackTitle.Init(RS_X(0.5f), RS_Y(0.5f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/タイトルにもどる.png");
	Option.Init(RS_X(0.5f), RS_Y(0.7f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/おぷしょん.png");
	BackCheck.Init(RS_X(0.5f), RS_Y(0.4f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/ほんとにもどる.png");
	Yes.Init(RS_X(0.35f), RS_Y(0.6f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/もどる.png");
	No.Init(RS_X(0.6f), RS_Y(0.6f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/やめとく.png");

	BackTitleF = false;
	BackCheckF = false;
	ChoiceNo = 0;
	ChoiceNoT = 0;
}

GPR GamePause::Update()
{
	//========================================================
	//タイトルに戻る　ゲームに戻る　オプション
	//========================================================
	if (!BackTitleF
		&& !BackCheckF)
	{
		if (GetKeyboardTrigger(DIK_UP))
		{
			ChoiceNo += 1;
			PlaySE(CURSOL);
		}
		else if (GetKeyboardTrigger(DIK_DOWN))
		{
			ChoiceNo -= 1;
			PlaySE(CURSOL);

		}
		ChoiceNo += 2;
		ChoiceNo %= 2;

		if (ChoiceNo == 0)
		{
			BackGame.SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			BackTitle.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			if (GetKeyboardTrigger(DIK_RETURN))
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
			if (GetKeyboardTrigger(DIK_RETURN))
			{
				PlaySE(DECIDE);
				BackTitleF = true;
				BackCheckF = true;
			}
		}
	}

	//==============================================================
	//はい　いいえ
	//==============================================================
	else if (BackTitleF)
	{
		if (GetKeyboardTrigger(DIK_RIGHT))
		{
			ChoiceNoT += 1;
			PlaySE(CURSOL);
		}
		else if (GetKeyboardTrigger(DIK_LEFT))
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
			if (GetKeyboardTrigger(DIK_RETURN))
			{

				PlaySE(DECIDE);
				Scene::SetScene(SCENE_TITLE,true);
			}
		}
		else if (ChoiceNoT == 0)
		{
			No.SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
			Yes.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			if (GetKeyboardTrigger(DIK_RETURN))
			{
				PlaySE(DECIDE);
				BackTitleF = false;
				BackCheckF = false;
			}

		}
	}
	return GPR::GAMEPAUSERESULT_MAX;
}


void GamePause::Draw()
{
	PauseFade.Draw();
	Back.Draw();

	if (	!BackTitleF
		&&	!BackCheckF)
	{
		BackGame.Draw();
		BackTitle.Draw();
		//Option.Draw();
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

}
