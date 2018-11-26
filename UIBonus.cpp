//=============================================================================
//
// �t�B�[���h���� [field.cpp]
//
//=============================================================================
#include "UIBonus.h"
#include "Library/ObjectBase2D.h"
#include "Library/Common.h"
#include "Library\Input.h"
#include "Library\DebugProcess.h"
#include "Library\Color.h"
#include "timer.h"
#include "GameSound.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
UI2DPercentGauge	BonusGage;	//�{�[�i�X�Q�[�W
C2DObject			Voiceten[3];
C2DObject			GageEff;

int		gagenum = 0;
float	gageper = 0.0f;
int		gagelong = 0;
bool fiverf = false;


const Vector2 FirstPos = Vector2(169.0f*SCREEN_SCALE, BONUSGAGE_POS_Y+10.0f*SCREEN_SCALE);
const Vector2 SecondPos = Vector2(295.0f*SCREEN_SCALE, BONUSGAGE_POS_Y);
const Vector2 ThirdPos = Vector2(420.0f*SCREEN_SCALE, BONUSGAGE_POS_Y-10.0f*SCREEN_SCALE);

//=============================================================================
// ����������
//=============================================================================
HRESULT InitUIBonus(void)
{
	BonusGage.Init(TEX_BONUSGAGEFRAME, TEX_BONUSGAGE);
	BonusGage.Init(BONUSGAGE_POS_X, BONUSGAGE_POS_Y, BONUSGAGE_SIZE_X, BONUSGAGE_SIZE_Y);



	Vector2 pos;
	pos = FirstPos;
	Voiceten[0].Init(pos.x, pos.y, 40 * SCREEN_SCALE, 40 * SCREEN_SCALE, TEX_GAGEVOICETEN);
	pos = SecondPos;
	Voiceten[1].Init(pos.x, pos.y, 40 * SCREEN_SCALE, 40 * SCREEN_SCALE, TEX_GAGEVOICETEN);
	pos = ThirdPos;
	Voiceten[2].Init(pos.x, pos.y, 40 * SCREEN_SCALE, 40 * SCREEN_SCALE, TEX_GAGEVOICETEN);

	GageEff.Init(GAGE_EFF_POS_X, GAGE_EFF_POS_Y, GAGE_EFF_SIZE_X, GAGE_EFF_SIZE_Y, TEX_GAGEEFF);

	gagenum = 0;
	gageper = 0.0f;
	gagelong = 0;
	fiverf = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitUIBonus(void)
{
	BonusGage.Uninit();

	for (int i = 0; i < 3; i++)
	{
		Voiceten[i].Release();
	}

	GageEff.Release();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawUIBonus(void)
{
	GageEff.Draw();

	BonusGage.Draw();

	for (int i = 0; i < 3; i++)
	{
		Voiceten[i].Draw();
	}
}

float effa=0.0f;
//=============================================================================
// �X�V����
//=============================================================================
void UpdateUIBonus(void)
{
	if (StateTimer() == COUNT)
	{

		if (GetKeyboardPress(DIK_9) && fiverf == false)
		{
			AddGage(50);//�X��������Ă���Ƃ��̓Q�[�W��L�΂�
		}
		//else
		{
			AddGage(-1);//�Q�[�W���k�߂�

			if (fiverf == true)
			{
				AddGage(-1);//�t�B�[�o�[��ԂȂ�����ƌ��炷
			}
		}

		if (GetKeyboardTrigger(DIK_8) && gagenum == 3)
		{
			fiverf = true;
		}
	}
		PrintDebugProcess("�t���O%d", gagenum);


		if (GetKeyboardTrigger(DIK_0))//0�������ꂽ��
		{
			gagenum--;//�t���O���ЂƂO��
		}

		BonusGage.Update(gageper);//�Q�[�W�̍X�V

		for (int i = 0; i < 3; i++)//�{�C�X�e���̍X�V����
		{
			Voiceten[i].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//��{�̓���0.2��

			if (i <= gagenum - 1 || fiverf == true)//�����Q�[�W�����܂��Ă�����
			{
				Voiceten[i].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//���܂����Ƃ���܂Ń{�C�X�e�������点��
			}
			Voiceten[i].SetTexture(i, 3, 1);

		}

	
		float cor;

		cor = (BONUSGAGE_SIZE_Y * 2) / (tanf(POS_COR_ANG));//�����l�̎Y�o

		Vector3 pos;
		Vector3 poseff;

		pos.x = BONUSGAGE_POS_X + ((BONUSGAGE_SIZE_X) * 2 * gageper) + cor;//X���W�͒���
		pos.y = BONUSGAGE_POS_Y - (BONUSGAGE_SIZE_Y);//Y�͂��̂܂�
		pos.z = 0.0f;
		BonusGage.Gage.SetVertex(1, pos);//���_1�̒���
		poseff.x = GAGE_EFF_POS_X + ((GAGE_EFF_SIZE_X)) + cor*1.6f;
		poseff.y = BONUSGAGE_POS_Y - (GAGE_EFF_SIZE_Y);//Y�͂��̂܂�
		poseff.z = 0.0f;
		GageEff.SetVertex(1, poseff);//���_1�̒���

		pos.x = BONUSGAGE_POS_X + cor;//X���Ē���
		BonusGage.Gage.SetVertex(0, pos);//���_0�𒲐�
		poseff.x = GAGE_EFF_POS_X - ((GAGE_EFF_SIZE_X)) + cor*1.6f;
		poseff.z = 0.0f;
		GageEff.SetVertex(0, poseff);//���_1�̒���

		pos.x = BONUSGAGE_POS_X + ((BONUSGAGE_SIZE_X) * 2) + cor;//X���W�͒���
		pos.y = BONUSGAGE_POS_Y - (BONUSGAGE_SIZE_Y);//Y�͂��̂܂�
		BonusGage.Frame.SetVertex(1, pos);//���_1�̒���

		pos.x = BONUSGAGE_POS_X + cor;//X���Ē���
		BonusGage.Frame.SetVertex(0, pos);//���_0�𒲐�


		if (gagenum == 3 || fiverf == true)
		{
			effa += 0.06f;
			GageEff.SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, fabs(sinf(effa)) + 0.2f));
		}
		else
		{
			GageEff.SetVertex(D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.0f));
		}
		BonusGage.Gage.SetTexture(1, gageper, 0.0f);//�e�N�X�`�����W�������ɉ����Đݒ�
		BonusGage.Gage.SetTexture(3, gageper, 1.0f);
	}



//=============================================================================
//�Q�[�W���Z�֐�
//=============================================================================
void AddGage(int no)
{

	if (no < 0)//no���}�C�i�X�̏ꍇ
	{
		if (fiverf == false)//�t�B�[�o�[��ԂłȂ����
		{
			PrintDebugProcess("%f ", VALUE_MAX * 3 * 0.33f);
			if ((float)(gagelong + no) > (float)(VALUE_MAX*gagenum*0.333)
				&&gagenum!=0 && gagenum!=3)//���|�C���g�������Ă����
			{
				gagelong += no;//���Z
			}
			else if (gagenum == 0)
			{
				gagelong += no;
			}
		}
		else
		{
			gagelong += no;//�t�B�[�o�[��ԂȂ�ⓚ���p�ŉ��Z

		}
	}
	else
	{
		if (fiverf == false)//�t�B�[�o�[��ԂłȂ����
		{
			if ((int)(((gagelong + no)/(float)VALUE_MAX) / 0.333f) > (int)(((gagelong) / (float)VALUE_MAX) / 0.333f))
			{
				gagenum++;
				if (gagenum < 3)
				{
					PlaySE(GAGE_1ST2ND);
				}
				else if (gagenum >= 3)
				{
					PlaySE(GAGE_LAST);
				}
			}

			gagelong += no;//�v���X�ł��ⓚ���p�ŉ��Z
		}
	}
	gageper = gagelong / (float)VALUE_MAX;//�ő�ƌ��݂̒������犄���̎Z�o

	if (gageper >= LAST_GAGE)//100%�ȏ�Ȃ�
	{
		gageper = LAST_GAGE;//100%�ɒ�������
		gagelong = VALUE_MAX;
		gagenum = 3;
		//fiverf = true;//�t�B�[�o�[��ԂɈڍs
	}
	else if (gageper <= 0.0f)//0%�ȉ��Ȃ�
	{
		gageper = 0.0f;//0%�ɒ�������
		gagelong = 0;
		fiverf = false;//�t�B�[�o�[��ԏI��
		gagenum = 0;
	}
	PrintDebugProcess("�t�B�[�o�[��ԁ@[%d]\n", fiverf);
	PrintDebugProcess("gageper [%d]\n", gagelong);
}

//=============================================================================
//�t�B�[�o�[��Ԏ擾�֐�
//=============================================================================
bool GetFiver(void)
{
	return fiverf;
}

//=============================================================================
// �擾�֐�
//=============================================================================
int GetGauge(void)
{
	return gagenum;
}