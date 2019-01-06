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
#include "field.h"

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


//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
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
//�e�N�X�`���ǂݍ���
//=============================================================================
void LoadTexture(void)
{
	LoadFieldTex();

}

//=============================================================================
//�e�N�X�`�������[�X
//=============================================================================
void ReleaseTexture(void)
{
	ReleaseTex();

}


//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
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
	DrawWorkHagiwara();
	DrawWorkKimura();
	DrawWorkSato();
	DrawWorkSon();
	DrawWorkUtsugi();
	DrawWorkYamaguchi();
	DrawWorkYamamoto();
	DrawWorkTsu();

}


