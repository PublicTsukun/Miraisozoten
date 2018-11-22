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

class ScoreDetailMove : public C2DObject
{
public:
	void MoveY(float move)
	{
		this->Position.y += move;
		this->SetVertex();
	}

	void MoveX(float move)
	{
		this->Position.x += move;
		this->SetVertex();
	}

	bool Use;
	bool Move;

	Vector2 GetPosition(void)
	{
		return this->Position;
	}
};

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
C2DObject resultbg[2];		//�^�C�g���w�i
C2DObject resultscr[NUM_PLACE];
C2DObject resultlogo;
					
RenderBuffer DetailWindow;
C2DObject	Detail;
ScoreDetailMove	ScoreDetail[DETAIL_MAX];
const char *ScoreDetailTex[] = {
	"data/TEXTURE/UI/�^�C�g��/���j���[���_��.png",
	"data/TEXTURE/UI/�^�C�g��/���j���[���_��.png",
	"data/TEXTURE/UI/�^�C�g��/���j���[���_��.png",
};
int DrawCount ;
int DetailCount;

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
	DetailWindow.Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_X8R8G8B8);
	Detail.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, RS_X(0.6f/2.0f), RS_Y(0.6f/2.0f));

	resultbg[0].Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, TEXTURE_RESULTBG);
	resultbg[1].Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_WIDTH*1.67f/ 2, SCREEN_HEIGHT*1.67/ 2, TEXTURE_RESULTBG);


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
	

	for (int i = 0; i < DETAIL_MAX; i++)
	{
		ScoreDetail[i].Init(SCREEN_WIDTH+400.0, 140 + 200.0*i, 400.0, 100.0, ScoreDetailTex[i%3]);
		ScoreDetail[i].Use = true;
		ScoreDetail[i].Move = false;
	}
	DrawCount = 0;

	DetailCount = 0;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResultlogo(void)
{
	resultbg[0].Release();
	resultbg[1].Release();

		for (int i = 0; i < NUM_PLACE; i++)
		{
			resultscr[i].Release();
		}
		resultlogo.Release();
		DetailWindow.Release();

		for (int i = 0; i < DETAIL_MAX; i++)
		{
			ScoreDetail[i].Release();
		}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResultlogo(void)
{
		resultbg[0].Draw();
		for (int i = 0; i < NUM_PLACE; i++)
		{
			resultscr[i].Draw();
		}
		resultlogo.Draw();

		DetailWindow.BeginDraw();
		//resultbg[1].Draw();

		for (int i = 0; i < DETAIL_MAX; i++)
		{
			//ScoreDetail[i].Draw();
		}

		DetailWindow.EndDraw();

		//Detail.Draw(DetailWindow.GetTexture());
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

	//if (DetailCount == DETAIL_MAX && !slotStart)
	if (slotTimer>=60)
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
				g_score = g_maxscore % (int)(powf(10.0f, slotCount));//�I�[�o�[�t���[����O�ɖ߂�
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

				if (slotCount == 5)
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

	//===========================================================================
	//�X�R�A�ڍ�
	//===========================================================================
	for (int i = 0; i < DETAIL_MAX; i++)
	{
		if (GetMouseZ() > 0)
		{
			if (ScoreDetail[0].GetPosition().y < 140.0)
			{
				ScoreDetail[DETAIL_MAX - i - 1].MoveY(GetMouseZ());
			}
		}
		else if (GetMouseZ() < 0)
		{
			if (ScoreDetail[DETAIL_MAX - 1].GetPosition().y > SCREEN_HEIGHT - 140.0)

				ScoreDetail[i].MoveY(GetMouseZ());

		}
		if (ScoreDetail[i].Move)
		{
			ScoreDetail[i].MoveX(-30.0);

			if (ScoreDetail[i].GetPosition().x <= SCREEN_CENTER_X)
			{
				ScoreDetail[i].Move = false;

				if (ScoreDetail[i + 1].Use && ((i + 1) < DETAIL_MAX))
				{
					ScoreDetail[i + 1].Move = true;
					DrawCount++;
				}
				DetailCount++;
			}
		}
	}


	if (DrawCount >= 3)
	{
		for (int j = 0; j < DETAIL_MAX; j++)
		{
			ScoreDetail[j].MoveY(-200.0);

		}
		DrawCount--;

	}
}
