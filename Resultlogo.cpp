//=============================================================================
//
// �^�C�g������ [result.cpp]
//
//=============================================================================
#include "Resultlogo.h"
#include "Library/ObjectBase2D.h"
#include "Library/Input.h"
#include "Library/DebugProcess.h"
#include "SceneManager.h"
#include "score.h"
#include "Library/MultiRendering.h" 
//=============================================================================
// �}�N����`
//=============================================================================


//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
C2DObject resultbg;		//�^�C�g���w�i
C2DObject resultscr[NUM_PLACE];
C2DObject resultlogo;
					
RenderBuffer DetailWindow;
C2DObject	Detail;

int g_maxscore;

int slotTimer;
bool slotStart;
int slotCount;
int g_score;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitResultlogo(void)
{
	DetailWindow.Init(RS_X(0.75), RS_Y(0.5), RS_X(0.75), RS_Y(0.5), RS_X(0.75), RS_Y(0.5), D3DFMT_X8R8G8B8);
	Detail.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, RS_X(0.6f/2.0f), RS_Y(0.6f/2.0f));

	resultbg.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, TEXTURE_RESULTBG);


	for (int i = 0; i < NUM_PLACE; i++)
	{
		resultscr[i].Init(RESULT_SCORE_POS_X +i*	RESULT_SCORE_SIZE_X*2, RESULT_SCORE_POS_Y, RESULT_SCORE_SIZE_X, RESULT_SCORE_SIZE_Y,TEXTURE_SCORE);
	}

	slotTimer = 0;
	slotStart = false;
	slotCount = 0;
	g_score = 0;
	g_maxscore = GetScore();

	resultlogo.Init(SCREEN_CENTER_X, RESULT_LOGO_SIZE_Y + 10.0f, RESULT_LOGO_SIZE_X, RESULT_LOGO_SIZE_Y, TEXTURE_RESULT_LOGO);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResultlogo(void)
{
		resultbg.Release();

		for (int i = 0; i < NUM_PLACE; i++)
		{
			resultscr[i].Release();
		}
		resultlogo.Release();
		DetailWindow.Release();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResultlogo(void)
{
		resultbg.Draw();
		for (int i = 0; i < NUM_PLACE; i++)
		{
			resultscr[i].Draw();
		}
		resultlogo.Draw();

		DetailWindow.BeginDraw();

		DetailWindow.EndDraw();

		Detail.Draw(DetailWindow.GetTexture());
}


//=============================================================================
// �X�V����
//=============================================================================
void UpdateResultlogo(void)
{

	//===========================================================================
	//�擾�X�R�A�\��
	//===========================================================================
	int slotadd = 0;		//�X���b�g���Z��

	slotTimer++;				//�^�C�}�[���Z

	if (slotTimer > 60)
	{
		slotStart = true;//��莞�ԂŃX���b�g�X�^�[�g
		slotTimer = 0;
	}
	if (slotStart == true)//�X���b�g�������Ă�Ƃ�
	{
		for (int i = 0; i < NUM_PLACE - slotCount; i++)//�w��̌����X���b�g
		{

			slotadd = (int)(powf(10.0f, (float)(NUM_PLACE - i - 1)));//�X���b�g���o
			g_score += slotadd;
			if (g_score >= (int)(powf(10.0f, NUM_PLACE + 1)))
			{
				g_score = g_maxscore%(int)(powf(10.0f, slotCount));//�I�[�o�[�t���[����O�ɖ߂�
			}
		}

		int number;
		int number2;

		number = (g_score % (int)(powf(10.0f, (float)(slotCount + 1)))) / (int)(powf(10.0f, (float)(slotCount)));	//�w�茅�m�F
		number2 = (g_maxscore % (int)(powf(10.0f, (float)(slotCount + 1)))) / (int)(powf(10.0f, (float)(slotCount)));//�w�茅�m�F

		if (slotCount < NUM_PLACE)
		{
			if (slotTimer > SLOT_INTERVAL && number == number2)//���o�X�g�b�v����
			{
				slotCount++;
				slotTimer = 0;

				if(slotCount==5)
				{
					int a = 0;
				}
			}
		}
		else if (slotCount == NUM_PLACE)
		{
			g_score = g_maxscore;
			slotStart = false;
		}

	}
	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		int number;

		number = (g_score % (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace - 1)));
		resultscr[nCntPlace].SetTexture(number, 10, 1);
	}

}
