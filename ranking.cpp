//=============================================================================
//
// �Q�[����ʏ��� [Ranking.cpp]
//
//=============================================================================
#include "Ranking.h"
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
<<<<<<< HEAD
//RANKING2DObject        Ranking2D;
RANKING			rankingWk[RANKING_MAX];				// �����L���O�i�[���[�N
int				rankCnt;							// �ǂݍ��񂾃����L���O�̐�
//BUF				bufWk[BUFC_MAX];

//=============================================================================
// �����L���O����
//=============================================================================
void Ranking(void)
{
	// �����L���O�pcsv�t�@�C���ǂݍ���
	LoadRankingCsv();
	// ID�̍ő�l�𒊏o����
	int max = rankingWk[0].id;	// id�ő�l�i�[�p
	for (int i = 1; i < RANKING_MAX - 1; i++)
	{
		if (max < rankingWk[1].id)max = rankingWk[i].id;
	}

	// �X�R�A���擾(�ꎞ�I�ɃX�R�A��6�ʂɂ���)
	rankingWk[SIXTH].score = Random(0,100000);//6�ʂ̃X�R�A�ɍ���̃X�R�A���Ԃ�����
	rankingWk[SIXTH].id = max + 1;
	// �X�R�A�����Ƃ�5�ʂ̃X�R�A�Ɣ�r���A5�ʂ̃X�R�A���Ⴏ��΃����L���O�X�V
	if (rankingWk[SIXTH].score >= rankingWk[FIFTH].score)
	{	// 5�ʂ��X�R�A��������΃����L���O�X�V���Ȃ�
		RankingSort();
		WriteRankingCsv();
	}
	// �����L���O�̕\��
	RANKING *ranking = &rankingWk[0];	// �|�C���^�[��������
	PrintDebugProcess("ID�\�� : (%d)\n", ranking->id);
	PrintDebugProcess("�����N�\�� : (%d)\n", ranking->rank);
	PrintDebugProcess("�X�R�A�\�� : (%d)\n", ranking->score);
}
=======
>>>>>>> a7f92b181e2235a7aa760ab3620164ba5260dc83


//=============================================================================
// ����������
//=============================================================================
HRESULT InitRanking(void)
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
void UninitRanking(void)
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
void UpdateRanking(void)
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
void DrawRanking(void)
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


