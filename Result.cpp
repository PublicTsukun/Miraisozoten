//=============================================================================
//
// ���U���g��ʏ��� [result.cpp]
//
//=============================================================================
#include "result.h"
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


//=============================================================================
// ����������
//=============================================================================
HRESULT InitResult(void)
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
// �I������
//=============================================================================
void UninitResult(void)
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
void UpdateResult(void)
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
void DrawResult(void)
{
	DrawWorkHagiwara();
	DrawWorkKimura();
	DrawWorkSato();
	DrawWorkSon();
	DrawWorkTsu();
	DrawWorkUtsugi();
	DrawWorkYamaguchi();
	DrawWorkYamamoto();

}


