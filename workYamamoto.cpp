//=============================================================================
//
//山本担当分　workYamamoto.cpp
//
//=============================================================================

//必須インクルード
#include <windows.h>
#include "workYamamoto.h"
#include "SceneManager.h"


//山本担当分インクルード
#include "workYamamoto.h"
#include <stdio.h>


#define EMPTY_NO		(99)		// 

// 色々おしらせする為の数字
#define NO_ENTRY		(100)		// 文字が入力されていない
#define BACK_CHAR		(101)		// 戻るボタンが押された
//*****************************************************************************
// ぐろーばるへんすう
//*****************************************************************************

int namechar;
int lastchar;		// かーそるってえいごでなんだっけ！
RANKDATA	rankdatawk[1];
//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitWorkYamamoto(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使いたいソースのInit

		break;


	case SCENE_GAME://ゲームで使いたいソースのInit

		break;


	case SCENE_RESULT://リザルトで使いたいソースのInit
		void InitName(void);
		break;
	}

	return S_OK;
}

//=============================================================================
//終了処理　※記載場所注意
//=============================================================================
void UninitWorkYamamoto(void)
{

	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://リザルトで使ったソースのUninit

		break;


	case SCENE_GAME://タイトルで使ったソースのUninit

		break;


	case SCENE_RESULT://ゲームで使ったソースのUninit

		break;
	}


}

//=============================================================================
//更新処理
//=============================================================================
void UpdateWorkYamamoto(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使うソースのUpdate

		break;


	case SCENE_GAME://ゲームで使うソースのUpdate

		break;


	case SCENE_RESULT://リザルトで使うソースのUpdate

		break;
	}


}


//=============================================================================
//描画処理
//=============================================================================
void DrawWorkYamamoto(void)
{
	switch (Scene::SetScene(SCENE_MAX))
	{
	case SCENE_TITLE://タイトルで使うソースのDraw

		break;


	case SCENE_GAME://ゲームで使うソースのDraw

		break;


	case SCENE_RESULT://リザルトで使うソースのDraw

		break;
	}


}

//*******************************************************************
// void Initname(void)
//*************************************************************************
void Initname(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	// 名前初期化
	for (int i = 0; i < NAMEMAX; i++)
	{
		rankdata[0].namechar[i] = EMPTY_NO;
	}
	// カーソルを初期位置に
	rankdata[0].cursole_X = 0;
	rankdata[0].cursole_Y = 0;
	namechar = 0;
	// 画像の初期化？
}
//**************************************************************************:
// void pinokkimon(void)
// 文字入力処理
// ジュレイモン僕に足りないものって何だったの
//***************************************************************************

/*
文字入力の流れ
十字キーでカーソルの移動
Aで選択Bで戻る
何らかのキーで名前の確定
名前は5文字とする
*/

void pinokkimon(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	
	int namechar = 0;	// 現在の入力文字の初期化
	// 文字
	int playername = 0;

	//　文字入力処理
	while(1)
	{
		// 現在の入力文字数が最大でないか
		if (namechar < NAMEMAX)
		{
			rankdata[0].namechar[namechar] = jyureimon();
			// 受け取った値が文字か確認
			if (rankdata[0].namechar[namechar <= EMPTY_NO])
			{
				namechar++;
			}
			else
			{
				switch (rankdata[0].namechar[namechar])
				{
				case NO_ENTRY:		
					break;
				case BACK_CHAR :
					rankdata[0].namechar[namechar] = EMPTY_NO;
					namechar--;
					break;
				default:
					break;
				}
				
			}
		}
		else
		{
			int check = 0;
			// 戻るボタンのみ受け付け
			check = jyureimon();
			if (check == BACK_CHAR)
			{
				rankdata[0].namechar[namechar] = EMPTY_NO;
				namechar--;       
			}
		}

	
	}



}

//******************************************************************************
// int jyureimon(void)
// カーソルキーで文字を選んで選んだ文字を格納するやつ
//***************************************************************:
int jyureimon(void)
{
	int tarinaimono=EMPTY_NO;	// 選ばれた文字
	
	return tarinaimono;
}

