//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#include "timer.h"
#include "Library/ObjectBase2D.h"
#include "Library/Common.h"



//*****************************************************************************
// グローバル変数
//*****************************************************************************
UI2DNumber number[MAX_DIGIT];	//タイマー数字
C2DObject frame;	//タイマーフレーム

const float NumberInter = NUMBER_SIZE_X * 2; //タイマー数字の間隔

const float Digit1_posX = SCREEN_CENTER_X - NumberInter;
const float Digit2_posX = SCREEN_CENTER_X;
const float Digit3_posX = SCREEN_CENTER_X + NumberInter;


int Time;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTimer(void)
{
	number[0].Init(Digit1_posX, 10, NUMBER_SIZE_X, NUMBER_SIZE_Y, NUMBER_TEX);
	number[1].Init(Digit2_posX, 10, NUMBER_SIZE_X, NUMBER_SIZE_Y, NUMBER_TEX);
	number[2].Init(Digit3_posX, 10, NUMBER_SIZE_X, NUMBER_SIZE_Y, NUMBER_TEX);


	Time = 123;
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

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTimer(void)
{

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

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		int num;

		num = (Time / (pow(10, i)));
		num %= 10;


		number[i].SetNumber(num);
	}


}