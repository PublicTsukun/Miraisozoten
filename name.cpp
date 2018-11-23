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

#define ALPHA_Y_MAX		(2)
#define ALPHA_X_MAX		(13)

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
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// もじばん
#define MOJIBAN_TEX		("data/テスト用画像/文字ボード.jpg")
#define MOJIBAN_WIDTH	(400.0)
#define MOJIBAN_HEIGHT	(200.0)
#define MOJIBAN_POS_X	(SCREEN_CENTER_X)						// CENTER_X指定で自動的に真ん中に表示してくれる(Draw?)
#define MOJIBAN_POS_Y	(SCREEN_CENTER_Y + MOJIBAN_HEIGHT/2)
// 文字盤の最大マス目
#define MOJIBAN_MASUMAX_X	(9)
#define MOJIBAN_MASUMAX_Y	(4)


// もじばん２(選択された文字を出すときに使うやつ）
#define SENTAKUMOJI_TEX		("data/テスト用画像/文字ボード.jpg")
#define SENTAKUMOJI_WIDTH	(70.0)
#define SENTAKUMOJI_HEIGHT	(70.0)
#define SENTAKUMOJI_POS_X	(SCREEN_CENTER_X-(SENTAKUMOJI_WIDTH*4))//(SCREEN_CENTER_X)						// CENTER_X指定で自動的に真ん中に表示してくれる(Draw?)
#define SENTAKUMOJI_POS_Y	(170.0f) //(SCREEN_CENTER_Y)

// 文字修正用のカーソル(入力済み文字に重ねて表示してます)
#define RENAME_CURSOLE_TEX	("data/テスト用画像/テスト用画像3.png")
#define RENAME_CURSOLE_WIDTH	(70.0)
#define RENAME_CURSOLE_HEIGHT	(70.0)
#define RENAME_CURSOLE_POS_X	(SCREEN_CENTER_X-(SENTAKUMOJI_WIDTH*4))//(SCREEN_CENTER_X)						// CENTER_X指定で自動的に真ん中に表示してくれる(Draw?)
#define RENAME_CURSOLE_POS_Y	(170.0f) //(SCREEN_CENTER_Y)

// 最大まで文字が入力されていないときのサークル



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 以下の値は弄らない方が…

//***************************************************
// カーソル関連
//***************************************************
#define CURSOLE_TEX		("data/テスト用画像/テスト用画像.png")
#define CURSOLE_SPACE	(2)					// 次のマスに移動するためにカーソルのX,Yにかける値
#define CURSOLE_WIDTH	(MOJIBAN_WIDTH/10)			// 文字盤が10文字×10文字なので
#define CURSOLE_HEIGHT	(MOJIBAN_HEIGHT/5)
// 「あ」を初期位置に
#define CURSOLE_POS_X	(SCREEN_CENTER_X-CURSOLE_WIDTH - (CURSOLE_WIDTH*CURSOLE_SPACE*4))
#define CURSOLE_POS_Y	((MOJIBAN_POS_Y) - (CURSOLE_HEIGHT*4))// - (CURSOLE_WIDTH*CURSOLE_SPACE))

// 文字盤ではなく選択文字をさしたいばあい
#define CHOISE_CURSOLE_TEX ("data/テスト用画像/ほげ.png")	// 多分使わない？
#define CHOISE_CURSOLE_SPACE	(2)					// 次のマスに移動するためにカーソルのX,Yにかける値
#define CHOISE_CURSOLE_WIDTH	(MOJIBAN_WIDTH/10)			// 文字盤が10文字×10文字なので
#define CHOISE_CURSOLE_HEIGHT	(MOJIBAN_HEIGHT/5)

#define CHOISE_CURSOLE_POS_X	(SCREEN_CENTER_X-CURSOLE_WIDTH - (CURSOLE_WIDTH*CURSOLE_SPACE*4))
#define CHOISE_CURSOLE_POS_Y	((MOJIBAN_POS_Y) - (CURSOLE_HEIGHT*4))// - (CURSOLE_WIDTH*CURSOLE_SPACE))






//*****************************************************************************
// ぐろーばるへんすう
//*****************************************************************************
int namechar;
int lastchar;		// かーそるってえいごでなんだっけ！

RANKDATA	rankdatawk[1];

C2DObject cursole;
C2DObject char_cursole;		// 名前の文字をさすカーソル
C2DObject mojiban;			// ひらがな用文字盤
C2DObject alphabet;
C2DObject moji[CHAR_MAX];
C2DObject select_moji[CHAR_MAX];		// ばばーんとだすようのやつだ

bool char_type;
#define HIRAGANA (0)
#define ABC (1)

bool name_flag;	// 文字盤にいるか名前にいるか(trueが文字盤)

bool moving;	// 移動中華のフラグ

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// カーソル変更関連
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#define CHANGE
#define CHANGE_TIME	(2)
int		cursole_update(CHANGE_TIME * 60);
int		timedayo;
bool cursolechanging;	// カーソル変更中華のフラウ
bool pos_rockon;	// 目標座標決定済みか
//float taeget_x, target_y;
float movesize_X, movesize_Y;
float target_x, target_y;	// カーソル移動用　目標位置と現在位置の座標


//*************************************************************************
// プロトタイプ宣言(cpp内でのみ使用するやつ
//*************************************************************************
void move_cursole(void);
void move_cursole_alpha(void);
void name_char_select(void);
void cursole_change(void);
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

	timedayo = 0;
	// フラグ初期化
	for (int i = 0; i < NAMEMAX; i++)
	{
		rankdata[0].selected[i] = false;
	}
	name_flag = true;
	char_type = HIRAGANA;
	pos_rockon = false;
	cursolechanging = false;

	// カーソルを初期位置に
	rankdata[0].cursole_X = 0;
	rankdata[0].cursole_Y = 0;
	namechar = 0;							// 入力済文字
	// 画像の初期化
	cursole.Init(CURSOLE_POS_X,CURSOLE_POS_Y,CURSOLE_WIDTH,CURSOLE_HEIGHT,CURSOLE_TEX);
	mojiban.Init(MOJIBAN_POS_X, MOJIBAN_POS_Y, MOJIBAN_WIDTH, MOJIBAN_HEIGHT, MOJIBAN_TEX);
	char_cursole.Init(RENAME_CURSOLE_POS_X, RENAME_CURSOLE_POS_Y, RENAME_CURSOLE_WIDTH, RENAME_CURSOLE_HEIGHT, RENAME_CURSOLE_TEX);


	return S_OK;
}

//**********************************************************
// 終了処理
//**********************************************************
void UninitName(void)
{
	// 各画像解放
	char_cursole.Release();
	cursole.Release();
	mojiban.Release();
	alphabet.Release();
	for (int i = 0; i < CHAR_MAX;i++)
	{
		moji[i].Release();
		select_moji[i].Release();
	}
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


	if (char_type == HIRAGANA)
	{
		mojiban.SetTexture(0, 1, 2);
		mojiban.Draw();
	}
	else
	{
		mojiban.SetTexture(1, 1, 2);
		mojiban.Draw();
	}


	//char_cursole.Init(CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*rankdata[0].cursole_X), CURSOLE_POS_Y + ((CURSOLE_HEIGHT*CURSOLE_SPACE)*rankdata[0].cursole_Y), CURSOLE_WIDTH, CURSOLE_HEIGHT, CURSOLE_TEX);
	//char_cursole.Draw();


	//select_moji[0].SetTexture(1, 10, 10);
	//select_moji[0].Draw();

	// 格納文字書き出し
	for (int i = 0; i < NAMEMAX; i++)
	{
		// selectedがtrueならテクスチャ表示
		if (rankdata[0].selected[i] == true)
		{
			// テクスチャのセット
			//select_moji[namechar].Init(SENTAKUMOJI_POS_X + ((SENTAKUMOJI_WIDTH)*namechar), SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
			select_moji[i].SetTexture(rankdata[0].namechar[i], 10, 10);	//第二引数 ますめの数X 第3 ますめの数Y
			select_moji[i].Draw();
		}
	}

	// カーソル描画
	// ばぐってるから
	//cursolechanging = false;
	if (cursolechanging == false)
	{
		// name_flagnで変わる
		if (name_flag == true)
		{	// 文字盤
			cursole.Init(CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*rankdata[0].cursole_X), CURSOLE_POS_Y + ((CURSOLE_HEIGHT*CURSOLE_SPACE)*rankdata[0].cursole_Y), CURSOLE_WIDTH, CURSOLE_HEIGHT, CURSOLE_TEX);
		}
		else
		{	// カーソルのサイズと位置を変えるだけでよくね？
			cursole.Init(SENTAKUMOJI_POS_X + ((RENAME_CURSOLE_WIDTH * 2)*rankdata[0].name_position), RENAME_CURSOLE_POS_Y, RENAME_CURSOLE_WIDTH, RENAME_CURSOLE_HEIGHT, RENAME_CURSOLE_TEX);

		}
	}
	else
	{
		cursole_change();
	}
	cursole.Draw();

}


//*******************************************************:::

//**************************************************************************:
// void Update_name(void)
// 更新処理　名前処理のアップデート
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
	if(name_flag == true)
	{
		move_cursole();
	}
	else
	{	// 文字盤移動処理
		name_char_select();
	}


	// 文字入力の終了
	if (GetKeyboardTrigger(DIK_Z))
	{
		int player_score = GetScore();
		// あたまがはたらかなかった↓
		long long name_number = (rankdata[0].namechar[0] * 100000000) + (rankdata[0].namechar[1] * 1000000) + (rankdata[0].namechar[2] * 10000) + (rankdata[0].namechar[3] * 100) + rankdata[0].namechar[4];
		SaveRanking(player_score,name_number);
	}

	// 入力済みの文字をカーソルで移動
	if (GetKeyboardTrigger(DIK_LEFT))
	{
		if (namechar != 0)
		{
			namechar--;
		}
		rankdata[0].namechar[namechar] = EMPTY_NO;
		rankdata[0].selected[namechar] = false;
	}

	// 文字盤を変えるよ
	if (GetKeyboardTrigger(DIK_X))
	{
		char_type = !char_type;
		// カーソル位置の初期化
		rankdata[0].cursole_X = 0;
		rankdata[0].cursole_Y = 0;
	}

	// カーソルの位置を変える(文字盤⇔名前欄)
	// てかこれを文字入力まで動かせないようにすればよくね？
	if (namechar != 0)
	{
		if (GetKeyboardTrigger(DIK_C))
		{
			if (cursolechanging == false)
			{
				name_flag = !name_flag;
				// rankdata[0].cursole_Y * 10

				if (name_flag == true)
				{
					// name_flagがtrueになった場合、文字盤が表示されるのでカーソルが変わる
					rankdata[0].cursole_X = rankdata[0].namechar[rankdata[0].name_position] % 10;
					rankdata[0].cursole_Y = (rankdata[0].namechar[rankdata[0].name_position] / 10) % 10;
					// 未入力の場合
					if (rankdata[0].namechar[rankdata[0].name_position] == EMPTY_NO)
					{
						rankdata[0].cursole_X = 0;
						rankdata[0].cursole_Y = 0;
					}
					// もしも入力された文字が文字盤と違う場合(「あ」なのに文字盤がアルファベットだったり)文字盤を対応する物に変えてあげる
					long long agumon_X = rankdata[0].namechar[rankdata[0].name_position] % 10;			// X座標
					long long agumon_Y = (rankdata[0].namechar[rankdata[0].name_position] / 10) % 10;	// Y座標

					if (char_type == HIRAGANA && agumon_Y > MOJIBAN_MASUMAX_Y)
					{
						char_type = !char_type;			// 文字盤変更
					}
					else if (char_type == ABC && agumon_Y <= MOJIBAN_MASUMAX_Y)
					{
						char_type = !char_type;
					}

				}
				cursolechanging = true;
			}
		}
	}
	// 00があ　01がい
	//select_moji[0].SetTexture(1,10,10);
}


//********************************************************************
// void move_cursole(void)
// 文字入力処理(文字盤を移動してなめを格納
//********************************************************************
void move_cursole(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
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

	// 文字の削除(不要な場合削除お願いします(＞＜))
	if (GetKeyboardTrigger(DIK_BACKSPACE))
	{	// 名前入力フラグの削除
		select_moji[namechar-1].Release();
		rankdata[0].selected[namechar-1] = false;
		namechar--;
		rankdata[0].name_position = namechar;

	}
	// 決定キーが入力された場合今のカーソル位置の文字を格納
	if (GetKeyboardTrigger(DIK_SPACE) && namechar<NAMEMAX)
	{
		// 1フラグをtrueに
		rankdata[0].selected[namechar] = true;

		// 数字で文字を格納
		if (char_type == HIRAGANA)
		{
			rankdata[0].namechar[namechar] = rankdata[0].cursole_X + (rankdata[0].cursole_Y * 10);
		}
		else
		{
			rankdata[0].namechar[namechar] = rankdata[0].cursole_X + ((rankdata[0].cursole_Y+5) * 10);
		}
		// テクスチャのセット
		select_moji[namechar].Init(SENTAKUMOJI_POS_X + ((SENTAKUMOJI_WIDTH * 2)*namechar), SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
		//select_moji[namechar].SetTexture(1, 10, 10);	//第二引数 ますめの数X 第3 ますめの数Y
		// 空白文字の場合の処理(空白文字入力できるかわからないので保留)

		// 文字入力されたので現在入力中の名前を加算
		if (namechar < NAMEMAX)
		{
			rankdata[0].name_position = namechar;
			namechar++;
		}
	}
	// 上書き処理(ここに書く必要はあるのだろうか…)
	//if()
}

//********************************************************************
// void name_char_select
// 名前編集処理！！！！
// 入力済みの名前をカーソル移動する場合　スカルグレイモンかっこいいすき
//********************************************************************
void name_char_select(void)
{
	RANKDATA *rankdata = &rankdatawk[0];

	if (GetKeyboardTrigger(DIK_A))
	{
		rankdata[0].name_position--;
		if (rankdata[0].name_position < 0)
		{
			rankdata[0].name_position = namechar;
		}
	}
	else if (GetKeyboardTrigger(DIK_D))
	{
		rankdata[0].name_position++;
		if (rankdata[0].name_position >= namechar)
		{
			rankdata[0].name_position = 0;
		}
	}
}

//********************************************************************
// void move_cursole_alpha(void)
// 文字盤のサイズなどが変わっていた時の関数
// 使用しない場合削除
//********************************************************************
void move_cursole_alpha(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
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
	if (GetKeyboardTrigger(DIK_SPACE) && namechar<NAMEMAX)
	{
		// 1フラグをtrueに
		rankdata[0].selected[namechar] = true;
		// 数字で文字を格納
		rankdata[0].namechar[namechar] = rankdata[0].cursole_X + (rankdata[0].cursole_Y+5 * 10);

		// テクスチャのセット
		select_moji[namechar].Init(SENTAKUMOJI_POS_X + ((SENTAKUMOJI_WIDTH * 2)*namechar), SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
		//select_moji[namechar].SetTexture(1, 10, 10);	//第二引数 ますめの数X 第3 ますめの数Y
		// 空白文字の場合の処理(空白文字入力できるかわからないので保留)
		if (namechar < NAMEMAX)
		{
			namechar++;
		}
	}
}


//********************************************************************
// cursole_change
// 文字盤～名前間で行き来するよ
// 絶対バグるから関数にしました
// うまくいったら上にそのままぶちこもう
//********************************************************************
void cursole_change(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	// 目標地点が決まってない場合、距離の計算
	if (pos_rockon == false)
	{
		
		{ // 初期位置のままの場合以下の処理は行わない
		// 名前欄選択位置の文字を取得
			long long agumon_X = rankdata[0].namechar[rankdata[0].name_position] % 10;			// X座標
			long long agumon_Y = (rankdata[0].namechar[rankdata[0].name_position] / 10) % 10;	// Y座標

			// この分岐いる？
			if (name_flag == true)
			{	// 名前から文字盤へ
				// アルファベットの場合位置調整が必要
				if (agumon_Y > MOJIBAN_MASUMAX_Y)
				{
					agumon_Y -= 5;	// マス目の高さだけひいてる
					rankdata[0].cursole_Y -= 5;
				}
				// 文字盤が英語の場合
				if (char_type == ABC)
				{
				}
				target_x = (CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*rankdata[0].cursole_X)) - (SENTAKUMOJI_POS_X + ((RENAME_CURSOLE_WIDTH * 2)*rankdata[0].name_position));
				target_y = (CURSOLE_POS_Y + ((CURSOLE_HEIGHT*CURSOLE_SPACE)*agumon_Y)) - RENAME_CURSOLE_POS_Y;
			}
			else
			{	// 文字盤から名前欄へ
				// 文字盤の種類によって位置調整が必要なので位置を保存
				// 現在のカーソル位置と名前欄の位置の距離を出せばいい
				target_x = (SENTAKUMOJI_POS_X + ((RENAME_CURSOLE_WIDTH * 2)*rankdata[0].name_position) - (CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*rankdata[0].cursole_X)));
				target_y = RENAME_CURSOLE_POS_Y - (CURSOLE_POS_Y + ((CURSOLE_HEIGHT*CURSOLE_SPACE)*rankdata[0].cursole_Y));
				//	これサイズなんだけどさ…いる？
			}
			target_x = target_x / cursole_update;
			target_y = target_y / cursole_update;
			movesize_X = (RENAME_CURSOLE_WIDTH - CURSOLE_WIDTH) / cursole_update;
			movesize_Y = (RENAME_CURSOLE_HEIGHT - CURSOLE_HEIGHT) / cursole_update;
			pos_rockon = true;
		}
	}
	if (name_flag == true)
	{	// 名前のやつから文字盤へ
		cursole.Init(SENTAKUMOJI_POS_X + ((RENAME_CURSOLE_WIDTH * 2)*rankdata[0].name_position) + (target_x*timedayo), RENAME_CURSOLE_POS_Y + (target_y*timedayo), RENAME_CURSOLE_WIDTH-(movesize_X*timedayo), RENAME_CURSOLE_HEIGHT-(movesize_Y*timedayo), RENAME_CURSOLE_TEX);
	}
	else
	{	// 文字盤から名前欄へ
		cursole.Init(CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*rankdata[0].cursole_X) + (target_x*timedayo), CURSOLE_POS_Y + ((CURSOLE_HEIGHT*CURSOLE_SPACE)*rankdata[0].cursole_Y) + (target_y*timedayo), CURSOLE_WIDTH+(movesize_X*timedayo), CURSOLE_HEIGHT+(movesize_Y*timedayo), CURSOLE_TEX);
	}

	timedayo++;
	if (timedayo >= cursole_update)
	{
		//name_flag = !name_flag;
		timedayo = 0;
		cursolechanging = false;
		pos_rockon = false;
	}
}

