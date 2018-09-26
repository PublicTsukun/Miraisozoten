//=============================================================================
//
// �Q�[����ʏ��� [Game.cpp]
//
//=============================================================================
#include "Game.h"
#include "Library/Input.h"
#include "Library/Fade.h"
#include "Library/ObjectBase2D.h"
#include "Library/ObjectBase3D.h"


//���[�N�̃C���N���[�h
#include "workHagiwara.h"
#include "workKimura.h"
#include "workSato.h"
#include "workSon.h"
#include "workTsu.h"
#include "workUtsugi.h"
#include "workYamaguchi.h"
#include "workYamamoto.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
C2DObject        TestPlayer2D;
C3DPolygonObject TestPlayer3D;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
	TestPlayer2D.Init(100, 100, 50, 50, "data/TEXTURE/Player.jpg");

	TestPlayer3D.Init(Vector3(200, 0, 200), Vector2(50, 50));
	TestPlayer3D.LoadTexture("data/TEXTURE/Player.jpg");

	InitWorkHagiwara();
	InitWorkKimura();
	InitWorkSato();
	InitWorkSon();
	InitWorkTsu();
	InitWorkUtsugi();
	InitWorkYamaguchi();
	InitWorkYamamoto();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	TestPlayer2D.Release();

	TestPlayer3D.Release();

	UninitWorkHagiwara();
	UninitWorkKimura();
	UninitWorkSato();
	UninitWorkSon();
	UninitWorkTsu();
	UninitWorkUtsugi();
	UninitWorkYamaguchi();
	UninitWorkYamamoto();

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	UpdateWorkHagiwara();
	UpdateWorkKimura();
	UpdateWorkSato();
	UpdateWorkSon();
	UpdateWorkTsu();
	UpdateWorkUtsugi();
	UpdateWorkYamaguchi();
	UpdateWorkYamamoto();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	TestPlayer2D.Draw();

	TestPlayer3D.Draw();

	DrawWorkHagiwara();
	DrawWorkKimura();
	DrawWorkSato();
	DrawWorkSon();
	DrawWorkTsu();
	DrawWorkUtsugi();
	DrawWorkYamaguchi();
	DrawWorkYamamoto();

}


