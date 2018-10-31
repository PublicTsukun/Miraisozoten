//*****************************************************::
// name.cpp
// 製作者 あるちゅう
//*******************************************************

//山本担当分インクルード
#include "name.h"
#include <stdio.h>


// 文字盤
#define MOJI_Y_MAX		(5)		// 5行？
#define MOJI_X_MAX		(10)	// 10列？

#define EMPTY_NO		(99)	// くうはく(初期値)

// とくべつなすうじ
#define NO_ENTRY		(100)		// 文字が入力されていない
#define BACK_CHAR		(101)		// 戻るボタンが押された

//*****************************************************************************
// ぐろーばるへんすう
//*****************************************************************************
int namechar;
int lastchar;		// かーそるってえいごでなんだっけ！
RANKDATA	rankdatawk[1];

//*************************************************************************
// void Initname(void)
// 文字入力の初期化
//*************************************************************************
void Initname(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	// 名前初期化
	for (int i = 0; i < NAMEMAX; i++)
	{
		rankdata[0].namechar[i] = EMPTY_NO;	// 全てを初期値に
	}
	// カーソルを初期位置に
	rankdata[0].cursole_X = 0;
	rankdata[0].cursole_Y = 0;
	namechar = 0;							// 入力済文字
	// 画像の初期化？
}

//**********************************************************


//**************************************************************************:
// void enter_name(void)
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

void enter_name(void)
{
	RANKDATA *rankdata = &rankdatawk[0];

	int namechar = 0;	// 現在の入力文字の初期化
						// 文字
	int playername = 0;

	//　文字入力処理
	while (1)
	{
		// 現在の入力文字数が最大でないか
		if (namechar < NAMEMAX)
		{
			rankdata[0].namechar[namechar] = get_char();
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
				case BACK_CHAR:
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
			check = get_char();
			if (check == BACK_CHAR)
			{
				rankdata[0].namechar[namechar] = EMPTY_NO;
				namechar--;
			}
		}


	}



}

//******************************************************************************
// int get_char(void)
// カーソルキーで文字を選んで選んだ文字を格納するやつ
// ぴのっきもん
//***************************************************************:
int get_char(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	int tarinaimono = EMPTY_NO;	// 選ばれた文字

	//　キー入力を受け取ってカーソルを上下に移動

	while (1)		// 決定キーが出るまで無限ループだよ
	{
		if (0)
		{// 上方向
			rankdata[0].cursole_Y++;
			// チェック
			if (rankdata[0].cursole_Y > MOJI_Y_MAX)
			{
				rankdata[0].cursole_Y = 0;
			}
		}
		else if (0)
		{	// したキーが押された
			rankdata[0].cursole_Y++;
			// チェック
			if (rankdata[0].cursole_Y < 0)
			{
				rankdata[0].cursole_Y = MOJI_Y_MAX;
			}
		}
		else if (0)
		{
			// 右キー
			rankdata[0].cursole_X++;
			// チェック
			if (rankdata[0].cursole_X > MOJI_X_MAX)
			{
				rankdata[0].cursole_X = 0;
			}
		}
		else if (0)
		{
			// 左キー
			rankdata[0].cursole_X--;
			// チェック
			if (rankdata[0].cursole_X < 0)
			{
				rankdata[0].cursole_X = MOJI_X_MAX;
			}
		}



		// カーソルチェック
		if(0)

		if (0)	// 決定ボタンが押された
		{
			break;
		}
	}

	return tarinaimono;
}



