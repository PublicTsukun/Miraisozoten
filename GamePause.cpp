#include "GamePause.h"
#include "Library\Common.h"
#include "Library\ObjectBase2D.h"


static C2DObject Back;
static C2DObject BackGame;
static C2DObject BackTitle;
static C2DObject BackCheck;
static C2DObject Yes;
static C2DObject No;
static C2DObject Option;

void GamePause::Init()
{
	Back.Init(     RS_X(0.5f), RS_Y(0.5f), RS_X(0.3f), RS_Y(0.4f), "data/TEXTURE/UI/ポーズ画面/バック白枠.png");
	BackGame.Init( RS_X(0.5f), RS_Y(0.3f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/ゲームにもどる.png");
	BackTitle.Init(RS_X(0.5f), RS_Y(0.5f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/タイトルにもどる.png");
	Option.Init(   RS_X(0.5f), RS_Y(0.7f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/おぷしょん.png");
	BackCheck.Init(RS_X(0.5f), RS_Y(0.6f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/ほんとにもどる.png");
	Yes.Init(RS_X(0.5f), RS_Y(0.6f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/もどる.png");
	No.Init( RS_X(0.5f), RS_Y(0.6f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/ポーズ画面/やめとく.png");
}

GPR GamePause::Update()
{
	return GPR::GAMEPAUSERESULT_MAX;
}


void GamePause::Draw()
{
	
}

void GamePause::Uninit()
{

}
