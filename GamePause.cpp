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
	Back.Init(     RS_X(0.5f), RS_Y(0.5f), RS_X(0.3f), RS_Y(0.4f), "data/TEXTURE/UI/�|�[�Y���/�o�b�N���g.png");
	BackGame.Init( RS_X(0.5f), RS_Y(0.3f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/�|�[�Y���/�Q�[���ɂ��ǂ�.png");
	BackTitle.Init(RS_X(0.5f), RS_Y(0.5f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/�|�[�Y���/�^�C�g���ɂ��ǂ�.png");
	Option.Init(   RS_X(0.5f), RS_Y(0.7f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/�|�[�Y���/���Ղ����.png");
	BackCheck.Init(RS_X(0.5f), RS_Y(0.6f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/�|�[�Y���/�ق�Ƃɂ��ǂ�.png");
	Yes.Init(RS_X(0.5f), RS_Y(0.6f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/�|�[�Y���/���ǂ�.png");
	No.Init( RS_X(0.5f), RS_Y(0.6f), RS_X(0.2f), RS_Y(0.1f), "data/TEXTURE/UI/�|�[�Y���/��߂Ƃ�.png");
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
