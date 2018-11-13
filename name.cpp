//*****************************************************::
// name.cpp
// 製作者 あるちゅう
//*******************************************************

//山本担当分インクルード
#include "name.h"
#include <stdio.h>
#include "saveranking.h"
#include "score.h"
// ライブラリ
#include "Library/ObjectBase2D.h"
#include "Library/Common.h"
#include "Library/Input.h"
#include "Library/DebugProcess.h"


//*********************************************************
// Define
//*********************************************************

// 文字盤
#define MOJI_Y_MAX		(5)		// 5行？
#define MOJI_X_MAX		(10)	// 10列？

// 仮の数字
#define SPACE_ENTRY		(710)	// スペース入力用
#define EMPTY_NO		(99)	// くうはく(初期値)

// 文字
// 48+26
#define CHARS_MAX		(74)

// とくべつなすうじ
#define NO_ENTRY		(100)		// 文字が入力されていない
#define BACK_CHAR		(101)		// 戻るボタンが押された

// 伝達用
#define KEY_IRETEKUDASAI	(777)


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 文字盤の表示位置を元にカーソル位置を決めています。
// カーソルの値は基本的に変更しないでください
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// もじばん
#define MOJIBAN_TEX		("data/作業/文字ボード.jpg")
#define MOJIBAN_WIDTH	(300.0)
#define MOJIBAN_HEIGHT	(300.0)
#define MOJIBAN_POS_X	(SCREEN_CENTER_X)						// CENTER_X指定で自動的に真ん中に表示してくれる(Draw?)
#define MOJIBAN_POS_Y	(SCREEN_CENTER_Y)
// 文字盤の最大マス目
#define MOJIBAN_MASUMAX_X	(9)
#define MOJIBAN_MASUMAX_Y	(9)

// もじばん２(選択された文字を出すときに使うやつ）
#define SENTAKUMOJI_TEX		("data/作業/文字ボード.jpg")
#define SENTAKUMOJI_WIDTH	(70.0)
#define SENTAKUMOJI_HEIGHT	(70.0)
#define SENTAKUMOJI_POS_X	(100.0f)//(SCREEN_CENTER_X)						// CENTER_X指定で自動的に真ん中に表示してくれる(Draw?)
#define SENTAKUMOJI_POS_Y	(100.0f) //(SCREEN_CENTER_Y)




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 以下の値は弄らない方が…
#define CURSOLE_TEX		("data/テスト用画像/テスト用画像.png")
#define CURSOLE_SPACE	(2)					// 次のマスに移動するためにカーソルのX,Yにかける値
#define CURSOLE_WIDTH	(MOJIBAN_WIDTH/10)			// 文字盤が10文字×10文字なので
#define CURSOLE_HEIGHT	(MOJIBAN_HEIGHT/10)
// 「あ」を初期位置に
#define CURSOLE_POS_X	(SCREEN_CENTER_X-CURSOLE_WIDTH - (CURSOLE_WIDTH*CURSOLE_SPACE*4))
#define CURSOLE_POS_Y	(SCREEN_CENTER_Y-CURSOLE_HEIGHT - (CURSOLE_WIDTH*CURSOLE_SPACE*4))





//*****************************************************************************
// ぐろーばるへんすう
//*****************************************************************************
int namechar;
int lastchar;		// かーそるってえいごでなんだっけ！
RANKDATA	rankdatawk[1];

C2DObject cursole;
C2DObject mojiban;
C2DObject moji[CHAR_MAX];
C2DObject select_moji[CHAR_MAX];		// ばばーんとだすようのやつだ

// 文字の画像テクスチャ(文字の画像を1枚ずつ用意する場合、使わないなら決しておk）
char *Moji_FileName[]=
{
	"data/TEXTURE/01.png",
};
//*************************************************************************
// HRESULT Initname(void)
// 文字入力の初期化
//*************************************************************************
HRESULT InitName(void)
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
	// 画像の初期化
	cursole.Init(CURSOLE_POS_X,CURSOLE_POS_Y,CURSOLE_WIDTH,CURSOLE_HEIGHT,CURSOLE_TEX);
	mojiban.Init(MOJIBAN_POS_X, MOJIBAN_POS_Y, MOJIBAN_WIDTH, MOJIBAN_HEIGHT, MOJIBAN_TEX);

	for (int i = 0; i < CHAR_MAX; i++)
	{
		//select_moji[i].Init(SENTAKUMOJI_POS_X, SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
	}
	return S_OK;
}

//**********************************************************
// 終了処理
//**********************************************************
void UninitName(void)
{
	// 各画像解放
	cursole.Release();
	mojiban.Release();
	//
	/*
	*/
}

	
//*************************************************************
// 描画処理
//**************************************************************
void DrawName(void)
{
	RANKDATA *rankdata = &rankdatawk[0];

	mojiban.Draw();
	// カーソル書き出しの前に初期化
	cursole.Init(CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*rankdata[0].cursole_X), CURSOLE_POS_Y+((CURSOLE_HEIGHT*CURSOLE_SPACE)*rankdata[0].cursole_Y), CURSOLE_WIDTH, CURSOLE_HEIGHT, CURSOLE_TEX);
	cursole.Draw();
	//mojiban.Init(MOJIBAN_POS_X, MOJIBAN_POS_Y, MOJIBAN_WIDTH, MOJIBAN_HEIGHT, MOJIBAN_TEX);
	

	// 格納文字書き出し
	for (int namechar = 0; namechar < NAMEMAX; namechar++)
	{

		// テクスチャのセット
		//select_moji[namechar].Init(SENTAKUMOJI_POS_X + ((SENTAKUMOJI_WIDTH)*namechar), SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
		select_moji[namechar].SetTexture(rankdata[0].namechar[namechar], 10, 10);	//第二引数 ますめの数X 第3 ますめの数Y
		select_moji[namechar].Draw();
	}
}


//*******************************************************:::

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

void Update_Name(void)
{
	RANKDATA *rankdata = &rankdatawk[0];

	// カーソル移動
	if (GetKeyboardTrigger(DIK_W))
	{
		rankdata[0].cursole_Y--;
		if (rankdata[0].cursole_Y < 0)
		{
			rankdata[0].cursole_Y = MOJIBAN_MASUMAX_Y;
		}
	}
	else if (GetKeyboardTrigger(DIK_S))
	{	// したキーが押された
		rankdata[0].cursole_Y++;
		// チェック
		if (rankdata[0].cursole_Y > MOJIBAN_MASUMAX_Y)
		{
			rankdata[0].cursole_Y = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_D))
	{
		// 右キー
		rankdata[0].cursole_X++;
		// チェック
		if (rankdata[0].cursole_X >MOJIBAN_MASUMAX_X)
		{
			rankdata[0].cursole_X = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_A))
	{
		// 左キー
		rankdata[0].cursole_X--;
		// チェック
		if (rankdata[0].cursole_X < 0)
		{
			rankdata[0].cursole_X = MOJIBAN_MASUMAX_X;
		}
	}

	// 決定キーが入力された場合今のカーソル位置の文字を格納
	if (GetKeyboardTrigger(DIK_SPACE))
	{	// 数字で文字を格納
		rankdata[0].namechar[namechar] = rankdata[0].cursole_X + (rankdata[0].cursole_Y * 10);
		namechar++;
		// テクスチャのセット
		select_moji[namechar].Init(SENTAKUMOJI_POS_X, SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
		select_moji[namechar].SetTexture(rankdata[0].namechar[namechar], 10, 10);	//第二引数 ますめの数X 第3 ますめの数Y
		// 空白文字の場合の処理(空白文字入力できるかわからないので保留)
	}

	// 文字入力の終了
	if (GetKeyboardTrigger(DIK_Z))
	{
		int player_score = GetScore();
		// あたまがはたらかなかった↓
		long long name_number = (rankdata[0].namechar[4] * 100000000) + (rankdata[0].namechar[3] * 1000000) + (rankdata[0].namechar[2] * 10000) + (rankdata[0].namechar[1] * 100) + rankdata[0].namechar[0];
		SaveRanking(player_score,name_number);
	}

	// 削除キーが入力された場合1文字戻る
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{
		rankdata[0].namechar[namechar] = EMPTY_NO;
		namechar--;
	}
	// 00があ　01がい
	//mojiban.SetTexture(1,10,10);
}


//***************************************************************************************
// void DrawChar(long long char)
// 画像の一部分を切り取って表示する
//***************************************************************************************