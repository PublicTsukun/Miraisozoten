//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#include "score.h"
#include "Library/ObjectBase2D.h"
#include "Library\Input.h"
#include "Library\DebugProcess.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
UI2DNumber score[SCORE_DIGIT];	//タイマー数字
C2DObject ScoreFrame;

int ScoreInter = (int)SCORE_SIZE_X * 2;


int Score;
int DrawScr;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitScore(void)
{
	
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		score[i].Init((float)(SCORE_POS_X - ScoreInter*i), SCORE_POS_Y, SCORE_SIZE_X, SCORE_SIZE_Y, SCORE_TEX);
	}

	Score = 0;
	DrawScr = 0;

	ScoreFrame.Init(SCORE_FRAME_POS, SCORE_POS_Y, SCORE_SIZE_X * SCORE_DIGIT+20.0*SCREEN_SCALE, SCORE_SIZE_Y + 5 * SCREEN_SCALE, SCORE_FRAME_TEX);
	ScoreFrame.SetVertex(0xff33ccff);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{

	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		score[i].Release();
	}

	ScoreFrame.Release();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	ScoreFrame.Draw();

	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		score[i].Draw();
	}

}


//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
	if (Score < DrawScr)
	{
		DrawScr -= 19;

		if (Score > DrawScr)
		{
			DrawScr = Score;
		}
	}
	else if (Score > DrawScr)
	{
		DrawScr += 19;

		if (Score < DrawScr)
		{
			DrawScr = Score;
		}
	}

	int num;
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		num = (DrawScr / (int)(pow(10, i)));
		num %= 10;
		score[i].SetNumber(num);
	}

}


//========================================================================
//スコア加算関数
//========================================================================
void AddScore(int num)
{
	Score += num;

	if (Score > pow(10, SCORE_DIGIT))
	{
		Score = (int)pow(10, SCORE_DIGIT) - 1;
	}
	else if (Score < 0)
	{
		Score = 0;
	}
}


//========================================================================
//スコア取得関数
//========================================================================
int GetScore(void)
{
	return Score;
}
