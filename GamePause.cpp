#include "GamePause.h"
#include "Library\Common.h"
#include "Library\ObjectBase2D.h"


static C2DObject Back;
static C2DObject BackGame;
static C2DObject BackTitle;
static C2DObject BackCheck;
static C2DObject Yes;
static C2DObject No;

void GamePause::Init()
{
	Back.Init(     RS_X(0.5f), RS_Y(0.5f), RS_X(0.3f), RS_Y(0.4f), "data/TEXTURE/UI/PAUSE/");
	BackGame.Init( RS_X(0.5f), RS_Y(0.4f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/PAUSE/");
	BackTitle.Init(RS_X(0.5f), RS_Y(0.6f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/PAUSE/");
	BackCheck.Init(RS_X(0.5f), RS_Y(0.6f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/PAUSE/");
	Yes.Init(RS_X(0.5f), RS_Y(0.6f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/PAUSE/");
	No.Init( RS_X(0.5f), RS_Y(0.6f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/PAUSE/");
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
