//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
//
//=============================================================================
#include "title.h"
#include "Library/Input.h"
#include "Library/Fade.h"
#include "Library/ObjectBase2D.h"


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
C2DObject TestPlayer;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(void)
{
	TestPlayer.Init(100, 100, 50, 50, "data/TEXTURE/player.png");

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
void UninitTitle(void)
{
	TestPlayer.Release();

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
void UpdateTitle(void)
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
void DrawTitle(void)
{
	TestPlayer.Draw();

	DrawWorkHagiwara();
	DrawWorkKimura();
	DrawWorkSato();
	DrawWorkSon();
	DrawWorkTsu();
	DrawWorkUtsugi();
	DrawWorkYamaguchi();
	DrawWorkYamamoto();

}

