//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#include "timer.h"
#include "Library/ObjectBase2D.h"
#include "Library/Common.h"
#include "Library\Input.h"
#include "Library\DebugProcess.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
UI2DNumber number[MAX_DIGIT];	//タイマー数字
C2DObject frame;	//タイマーフレーム



//3桁バージョン
//const float NumberInter = NUMBER_SIZE_X * 2; //タイマー数字の間隔
//const float Digit1_posX = SCREEN_CENTER_X + NumberInter;
//const float Digit2_posX = SCREEN_CENTER_X;
//const float Digit3_posX = SCREEN_CENTER_X - NumberInter;

//2桁バージョン
const float NumberInter = NUMBER_SIZE_X ; //タイマー数字の間隔
const float Digit1_posX = SCREEN_CENTER_X + NumberInter;
const float Digit2_posX = SCREEN_CENTER_X - NumberInter;

const float FrameSizeX = MAX_DIGIT * NUMBER_SIZE_X+25;
const float FrameSizeY = NUMBER_SIZE_Y+20;

int Time;

int FrameCount;

int Timerf;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTimer(void)
{
	number[0].Init(Digit1_posX, NUMBER_POS_Y, NUMBER_SIZE_X, NUMBER_SIZE_Y, NUMBER_TEX);
	number[1].Init(Digit2_posX, NUMBER_POS_Y, NUMBER_SIZE_X, NUMBER_SIZE_Y, NUMBER_TEX);
	//number[2].Init(Digit3_posX, NUMBER_POS_Y, NUMBER_SIZE_X, NUMBER_SIZE_Y, NUMBER_TEX);

	frame.Init(SCREEN_CENTER_X, 50* SCREEN_SCALE, FrameSizeX, FrameSizeY, FRAME_TEX);


	TimerSet(RESET);
	TimerSet(STOP);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTimer(void)
{

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		number[i].Release();
	}

	frame.Release();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTimer(void)
{
	frame.Draw();

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		number[i].Draw();
	}

}


//=============================================================================
// 更新処理
//=============================================================================
void UpdateTimer(void)
{
	if (Timerf==COUNT)
	{
		FrameCount++;
		if (FrameCount > 60)
		{
			FrameCount = 0;
			Time--;

			if (Time < 0)
			{
				Time = 0;
			}
		}
	}

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		int num;

		num = (Time / (int)(pow(10, i)));
		num %= 10;


		number[i].SetNumber(num);


	}


}


//=======================================================
//タイマー起動管理
//========================================================
void TimerSet(int no)
{
		Timerf = no;

	switch (no)
	{
	case STOP:
		break;
	case RESET:
		Time = START_TIME;
		FrameCount=0;
		break;
	case COUNT:
		break;
	}
}