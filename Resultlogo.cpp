//=============================================================================
//
// タイトル処理 [result.cpp]
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
// マクロ定義
//=============================================================================


//=============================================================================
// プロトタイプ宣言
//=============================================================================


//=============================================================================
// グローバル変数
//=============================================================================
C2DObject resultbg;		//タイトル背景
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
// 初期化処理
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
// 終了処理
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
// 描画処理
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
// 更新処理
//=============================================================================
void UpdateResultlogo(void)
{

	//===========================================================================
	//取得スコア表示
	//===========================================================================
	int slotadd = 0;		//スロット加算数

	slotTimer++;				//タイマー加算

	if (slotTimer > 60)
	{
		slotStart = true;//一定時間でスロットスタート
		slotTimer = 0;
	}
	if (slotStart == true)//スロットが動いてるとき
	{
		for (int i = 0; i < NUM_PLACE - slotCount; i++)//指定の桁をスロット
		{

			slotadd = (int)(powf(10.0f, (float)(NUM_PLACE - i - 1)));//スロット演出
			g_score += slotadd;
			if (g_score >= (int)(powf(10.0f, NUM_PLACE + 1)))
			{
				g_score = g_maxscore%(int)(powf(10.0f, slotCount));//オーバーフローする前に戻す
			}
		}

		int number;
		int number2;

		number = (g_score % (int)(powf(10.0f, (float)(slotCount + 1)))) / (int)(powf(10.0f, (float)(slotCount)));	//指定桁確認
		number2 = (g_maxscore % (int)(powf(10.0f, (float)(slotCount + 1)))) / (int)(powf(10.0f, (float)(slotCount)));//指定桁確認

		if (slotCount < NUM_PLACE)
		{
			if (slotTimer > SLOT_INTERVAL && number == number2)//演出ストップ処理
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
