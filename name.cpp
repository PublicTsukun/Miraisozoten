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


//*********************************************************
// 仮決め
#define NEXT_CHAR		(91)	// 決定キー
#define Y_TEST			(-100)	// 調整よう
//********************************************************

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


// 背景画像andロゴ
#define HAIKEI_TEX		("data/TEXTURE/UI/リザルト/りざると背景.png")
#define HAIKEI_WIDTH	(SCREEN_WIDTH/2)		//  あ
#define HAIKEI_HEIGHT	(SCREEN_HEIGHT/2)
#define HAIKEI_ROGO		("data/TEXTURE/UI/りざると.png")
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 文字盤の表示位置を元にカーソル位置を決めています。
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// もじばん
#define MOJIBAN_TEX		("data/TEXTURE/UI/リザルト/五十音プログラム表記用.png")
#define MOJIBAN_WIDTH	(400.0)
#define MOJIBAN_HEIGHT	(200.0)
#define MOJIBAN_POS_X	(SCREEN_CENTER_X)						// CENTER_X指定で自動的に真ん中に表示してくれる(Draw?)
#define MOJIBAN_POS_Y	(SCREEN_CENTER_Y + MOJIBAN_HEIGHT/2)
// 文字盤の最大マス目
#define MOJIBAN_MASUMAX_X	(9)
#define MOJIBAN_MASUMAX_Y	(4)


// もじばん２(選択された文字を出すときに使うやつ）
#define SENTAKUMOJI_TEX		("data/TEXTURE/UI/リザルト/五十音プログラム表記用.png")
#define SENTAKUMOJI_WIDTH	(70.0)
#define SENTAKUMOJI_HEIGHT	(70.0)
#define SENTAKUMOJI_POS_X	(SCREEN_CENTER_X-(SENTAKUMOJI_WIDTH*4))//(SCREEN_CENTER_X)						// CENTER_X指定で自動的に真ん中に表示してくれる(Draw?)
#define SENTAKUMOJI_POS_Y	(170.0f) //(SCREEN_CENTER_Y)

// 文字修正用のカーソル(入力済み文字に重ねて表示してます)
#define RENAME_CURSOLE_TEX	("data/TEXTURE/UI//リザルト/名前矢印.png")
#define RENAME_CURSOLE_WIDTH	(70.0)
#define RENAME_CURSOLE_HEIGHT	(70.0)
#define RENAME_CURSOLE_POS_X	(SCREEN_CENTER_X-(SENTAKUMOJI_WIDTH*4))//(SCREEN_CENTER_X)						// CENTER_X指定で自動的に真ん中に表示してくれる(Draw?)
#define RENAME_CURSOLE_POS_Y	(170.0f) //(SCREEN_CENTER_Y)




// カーソル移動秒数
#define CHANGE_TIME	(1)

//　決定B単y座標
#define KETTEI_Y	(740)

// 最大まで文字が入力されていないときのサークル



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 以下の値は弄らない方が…

//***************************************************
// カーソル関連
//***************************************************
#define CURSOLE_TEX		("data/TEXTURE/UI//リザルト/文字入力カーソル.png")
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

// ランキングの名前
#define NAME_TEX		("data/TEXTURE/UI/リザルト/五十音プログラム表記用.png")
#define NAME_WIDTH	(70.0)
#define NAME_HEIGHT	(70.0)
#define NAME_POS_X	(SCREEN_CENTER_X-(SENTAKUMOJI_WIDTH*4))//(SCREEN_CENTER_X)						// CENTER_X指定で自動的に真ん中に表示してくれる(Draw?)
#define NAME_POS_Y	(170.0f) //(SCREEN_CENTER_Y)
#define RANKING_NO	(5)		// ランキング画面に表示される名前の数


// 間隔調整用
#define NAME_MAX_NO (5)
#define SCORE_MAX_NO (5)
#define NAME_POS_X (210.0)
#define NAME_POS_Y (70.0)
#define NAME_SCORE_POS_Y (150)		// 名前とスコアは同じ高さ
#define NAME_SPACE_01	(50)
#define NAME_SCORE_SIZE (50)

#define FLASH_TIME		(0.05f)

// 決定ボタン
//*****************************************************************************
// 構造体定義
//*****************************************************************************
// カーソル位置のenum
typedef enum
{
	KEYBOARD,
	PLAYER_NAME,
	NAME_FINISH
}CURSOLE_POSITION;



//*****************************************************************************
// ぐろーばるへんすう
//*****************************************************************************

int namechar;
int lastchar;		// かーそるってえいごでなんだっけ！
int name_status;	// 現在の状態
RANKDATA	rankdatawk[1];
CURSOLE		cursolewk;
C2DObject cursole;
C2DObject char_cursole;		// 名前の文字をさすカーソル
C2DObject mojiban;			// ひらがな用文字盤
C2DObject alphabet;
C2DObject select_moji[CHAR_MAX];		// ばばーんとだすようのやつだ
C2DObject haikei;
C2DObject haiki_logo;
C2DObject name_set;						// 決定ボタン

RANKING ranking[5];
Dx9Texture ranktex[5];

// 点滅に使う
float flash_count;
bool flash_count_switch;

bool char_type;
#define HIRAGANA (0)
#define ABC (1)

bool name_flag;	// 文字盤にいるか名前にいるか(trueが文字盤)
int cursole_status;	// カーソルがさしてる場所(name_flagと同じ働き)
bool moving;	// 移動中華のフラグ
bool name_enter;	// ランキングに入ってるかのフラグ trueなら名前入力処理を動かす

					//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					// カーソル変更関連
					//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					//#define CHANGE

int		cursole_update(CHANGE_TIME * 60);
int		timedayo;
bool cursolechanging;	// カーソル変更中華のフラウ
bool pos_rockon;	// 目標座標決定済みか
					//float taeget_x, target_y;
float movesize_X, movesize_Y;
float target_x, target_y;	// カーソル移動用　目標位置と現在位置の座標
bool finish_flag;			// 文字入力終わるかどうかのフラグ
int flash_score;			// 点滅するsuko

//*************************************************************************
// プロトタイプ宣言(cpp内でのみ使用するやつ
//*************************************************************************
void move_cursole(void);
void Flash_Tex(int no);
//*************************************************************************
// HRESULT Initname(void)
// 文字入力の初期化
//*************************************************************************
HRESULT InitName(void)
{
	RANKDATA *rankdata = &rankdatawk[0];

	//
	ranktex[0].LoadTexture("data/TEXTURE/UI/リザルト/1st.png");
	ranktex[1].LoadTexture("data/TEXTURE/UI/リザルト/2nd.png");
	ranktex[2].LoadTexture("data/TEXTURE/UI/リザルト/3rd.png");
	ranktex[3].LoadTexture("data/TEXTURE/UI/リザルト/4th.png");
	ranktex[4].LoadTexture("data/TEXTURE/UI/リザルト/5th.png");

	// 読み込み
	LoadSaveRankingCsv();

	// スコア取得
	int player_score = GetScore();
	name_enter = SaveRankingSort(player_score);	// スコアがランクインしたか？
	//name_enter = SaveRankingSort(99999);	// スコアがランクインしたか？


	SAVERANKING *rankinfo = GetSaveRanking(0);
	for (int i = 0; i < 5; i++,rankinfo++)
	{// 236
		ranking[i].rank.Init(NAME_SCORE_SIZE + 40.0f, NAME_SCORE_POS_Y + ((NAME_SCORE_SIZE * 2)*i), NAME_SCORE_SIZE, NAME_SCORE_SIZE);
		ranking[i].rank.LoadTexture(ranktex[rankinfo->rank-1]);

		for (int t = 0; t < 5; t++)
		{	// スコア描画
			ranking[i].score[t].Init(NAME_POS_X + ((NAME_SCORE_SIZE*2)*(NAME_MAX_NO+(t))), NAME_SCORE_POS_Y +((NAME_SCORE_SIZE*2)*i), NAME_SCORE_SIZE, NAME_SCORE_SIZE);
			ranking[i].score[t].LoadTexture("data/TEXTURE/UI/スコア数字.png");
			int num;
			num = (rankinfo->score / (int)(pow(10, 5-t-1)));
			num %= 10;
			ranking[i].score[t].SetNumber(num);
		}

		// 名前描画
		for (int agmon = 0; agmon < NAME_MAX_NO; agmon++)
		{
			ranking[i].name[agmon].Init(NAME_POS_X+((NAME_SCORE_SIZE*2)*agmon), NAME_SCORE_POS_Y +((NAME_SCORE_SIZE*2)*i), NAME_SCORE_SIZE, NAME_SCORE_SIZE);
			ranking[i].name[agmon].LoadTexture(NAME_TEX);
			int gabmon = rankinfo->name[agmon][0]*10+rankinfo->name[agmon][1];
			ranking[i].name[agmon].SetTexture(gabmon, 10, 10);
		}
	}


	//// 名前初期化
	//for (int i = 0; i < NAMEMAX; i++)
	//{
	//	rankdata[0].namechar[i] = EMPTY_NO;	// 全てを初期値に
	//}

	timedayo = 0;

	// 各フラグ初期化
	for (int i = 0; i < NAMEMAX; i++)
	{
		rankdata[0].selected[i] = false;
	}
	name_flag = true;
	cursole_status = KEYBOARD;	// キーボードへ
	char_type = HIRAGANA;
	pos_rockon = false;
	cursolechanging = false;
	name_enter = false;
	flash_count_switch = false;

	// ステータスを初期状態に
	name_status = BEGIN;

	// カーソルを初期位置に
	cursolewk.pos.x = 0;
	cursolewk.pos.y = 0;
	namechar = 0;							// 入力済文字
											// 画像の初期化
	cursole.Init(CURSOLE_POS_X, Y_TEST + CURSOLE_POS_Y, CURSOLE_WIDTH, CURSOLE_HEIGHT, CURSOLE_TEX);
	mojiban.Init(MOJIBAN_POS_X, Y_TEST + MOJIBAN_POS_Y, MOJIBAN_WIDTH, MOJIBAN_HEIGHT, MOJIBAN_TEX);
	char_cursole.Init(RENAME_CURSOLE_POS_X, Y_TEST + RENAME_CURSOLE_POS_Y, RENAME_CURSOLE_WIDTH, RENAME_CURSOLE_HEIGHT, RENAME_CURSOLE_TEX);
	haikei.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, HAIKEI_WIDTH, HAIKEI_HEIGHT, HAIKEI_TEX);
	name_set.Init(SCREEN_CENTER_X, Y_TEST + KETTEI_Y, 160.0, 80.0, "data/TEXTURE/UI/けってい.png");	//X座標×2に更に文字数をかける
	//haikei_logo.Init

	// カウントセット
	flash_count = 1.0f;

	flash_score = 0;

	for (int i = 0;i<5;i++)
	{
		select_moji[i].Init(SENTAKUMOJI_POS_X + ((SENTAKUMOJI_WIDTH * 2)*i), Y_TEST + SENTAKUMOJI_POS_Y, SENTAKUMOJI_WIDTH, SENTAKUMOJI_HEIGHT, SENTAKUMOJI_TEX);
	}
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
	name_set.Release();
	for (int i = 0; i < 5; i++)
	{
		for (int t = 0; t < 5; t++)
		{
			ranking[i].name[t].Release();
			ranking[i].score[t].Release();
			
		}
		ranking[i].rank.Release();
		ranktex[i].Release();
	}
	for (int i = 0; i < CHAR_MAX; i++)
	{
		select_moji[i].Release();
	}
	//
	/*
	*/
	haikei.Release();
}


//*************************************************************
// 描画処理
//**************************************************************
void DrawName(void)
{
	RANKDATA *rankdata = &rankdatawk[0];


	haikei.Draw();			// 背景画像

	switch (name_status)
	{
		// 名前入力に入っている場合の描画
	case NAME_SELECT:
	{	


		// ここから下関数にしてわけるかも？
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
		// 格納文字書き出し
		for (int i = 0; i < NAME_MAX; i++)
		{
			// selectedがtrueならテクスチャ表示
			if (rankdata[0].selected[i] == true)
			{
				// テクスチャのセット
				int numnum;
				numnum = rankdata[0].namechar[i][0] * 10 + rankdata[0].namechar[i][1];
				select_moji[i].SetTexture(numnum, 10, 10);	//第二引数 ますめの数X 第3 ますめの数Y
				select_moji[i].Draw();
			}
		}

		// 決定ボタン(一度でも文字が最大まで入力された場合表示
		if (rankdata[0].selected[NAME_MAX - 1] == true)
		{
			name_set.Draw();
		}
		

		// カーソル描画
		// ばぐってるから
		//cursolechanging = false;
		if (cursolechanging == false)
		{
			// カーソルの表示位置を変更する

			// name_flagnで変わる
			switch (cursole_status)
			{
			case KEYBOARD:
			{	// 文字盤
				cursole.SetStatus(CURSOLE_POS_X + ((CURSOLE_WIDTH*CURSOLE_SPACE)*cursolewk.pos.x), Y_TEST + CURSOLE_POS_Y + ((CURSOLE_HEIGHT*CURSOLE_SPACE)*cursolewk.pos.y), CURSOLE_WIDTH, CURSOLE_HEIGHT);
				break;
			}
			case PLAYER_NAME:
			{	// カーソルのサイズと位置を変えるだけでよくね？
				//cursole.SetStatus(SENTAKUMOJI_POS_X + ((RENAME_CURSOLE_WIDTH * 2)*rankdata[0].name_position), Y_TEST + RENAME_CURSOLE_POS_Y, RENAME_CURSOLE_WIDTH, RENAME_CURSOLE_HEIGHT);
				break;
			}
			case NAME_FINISH:
			{	// カーソルを表示しない
				cursole.SetStatus(-100, -100, 0.0, 0.0);
				break;
			}
			}
		}
		else
		{
			//cursole_change();
		}
		cursole.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, fabs(sinf(flash_count)) + 0.3f));
		cursole.Draw();
	}
	break;

	case NAME_SELECT_END:
	{

	}
	default:
		// ランキング描画用の関数…
		for (int i = 0; i < 5; i++)
		{
			ranking[i].rank.Draw();
			for (int t = 0; t < 5; t++)
			{
				ranking[i].name[t].Draw();
				ranking[i].score[t].Draw();
			}
		}
		break;
	}
}


//***************************************************************************
// void Update_name(void)
// 更新処理　名前処理のアップデート
// ジュレイモン僕に足りないものって何だったの
//***************************************************************************
void Update_Name(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	if (GetKeyboardTrigger(DIK_8))
	{
		name_enter = !name_enter;
	}

	// フラグがtrueなら名前入力ＯＫ
	if (name_status != NAME_SELECT_END && name_enter == true && GetKeyboardTrigger(DIK_0) || IsButtonTriggered(BUTTON_UP))
	{
		name_status = NAME_SELECT;
	}
	else if (name_enter == false && GetKeyboardTrigger(DIK_0) || IsButtonTriggered(BUTTON_UP))
	{
		PlaySE(DECIDE);
		Scene::SetScene(SCENE_TITLE);
	}


	switch (name_status)
	{
	case NAME_SELECT:
	{
		if (cursole_status != NAME_FINISH)
		{	// 決定ボタンにカーソルが居ない(キーボード)
			// カーソル移動

				move_cursole();


			// 文字盤を変える(カーソル移動中は実行できない）
			if (GetKeyboardTrigger(DIK_X) || IsButtonTriggered(LSTICK_RIGHT | LSTICK_LEFT) && cursolechanging == false)
			{
				char_type = !char_type;
				// カーソル位置の初期化
				cursolewk.pos.x = 0;
				cursolewk.pos.y = 0;
			}

			// カーソルの位置を変える(文字盤⇔名前欄)
		}
		else
		{	// 以下、決定ボタンにいる際の処理(name_status = NAME_FINISH)
			if (GetKeyboardTrigger(DIK_2) || IsButtonTriggered(BUTTON_DOWN))
			{	// まだ決定しないよ
				rankdata[0].selected[namechar - 1] = false;	// 入力文字のフラグをオフに
				rankdata[0].namechar[namechar-1][0] = 0;
				rankdata[0].namechar[namechar-1][1] = 0;// 文字入力フラグ初期化(あの位置へ）
				namechar--;									// 現在入力中の文字数を減らすよ
				//rankdata[0].name_position = namechar - 1;
				cursole_status = KEYBOARD;
			}
			// 決定ボタンにカーソルが存在しておりLキーが押された場合
			if (GetKeyboardTrigger(DIK_L) || IsButtonTriggered(BUTTON_UP))
			{

				for (int i = 0; i < NAMEMAX; i++)
				{
					Enter_the_no(CheckRank(GetScore()),i, rankdata[0].namechar[i][0], rankdata[0].namechar[i][1]);
				}

				// データ出力
				WriteSaveRankingCsv();
				// 再ロード
				//LoadSaveRankingCsv();
				// ランキングへ
				name_status = NAME_SELECT_END;
			}
		}

	}
	break;
	case NAME_SELECT_END:
	{
		if ((GetKeyboardTrigger(DIK_0) || IsButtonTriggered(BUTTON_UP)))// 個々のボタン相談する
		{
			PlaySE(DECIDE);
			Scene::SetScene(SCENE_TITLE);
		}
	}
//defalt:
	break;
	}

	Flash_Tex(0);
	// 点滅
	
}


//********************************************************************
// void move_cursole(void)
// 文字入力処理(文字盤を移動してなめを格納
//********************************************************************
void move_cursole(void)
{
	RANKDATA *rankdata = &rankdatawk[0];
	if (GetKeyboardTrigger(DIK_W) || IsButtonTriggered(LSTICK_UP))
	{
		cursolewk.pos.y--;
		if (char_type == HIRAGANA && cursolewk.pos.y < 0)
		{
			cursolewk.pos.y = MOJIBAN_MASUMAX_Y;
		}
		else if(char_type!=HIRAGANA && cursolewk.pos.y <0)
		{
			cursolewk.pos.y = 2;	// アルファベット最大たてます
		}
	}
	else if (GetKeyboardTrigger(DIK_S) || IsButtonTriggered(LSTICK_DOWN))
	{	// したキーが押された
		cursolewk.pos.y++;
		// チェック
		if (char_type == HIRAGANA && cursolewk.pos.y > MOJIBAN_MASUMAX_Y)
		{
			cursolewk.pos.y = 0;
		}
		else if (char_type != HIRAGANA && cursolewk.pos.y >2)
		{
			cursolewk.pos.y = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_D) || IsButtonTriggered(LSTICK_RIGHT))
	{
		// 右キー
		cursolewk.pos.x++;
		// チェック
		if (cursolewk.pos.x >MOJIBAN_MASUMAX_X)
		{
			cursolewk.pos.x = 0;
		}
	}
	else if (GetKeyboardTrigger(DIK_A) || IsButtonTriggered(LSTICK_LEFT))
	{
		// 左キー
		cursolewk.pos.x--;
		// チェック
		if (cursolewk.pos.x < 0)
		{
			cursolewk.pos.x = MOJIBAN_MASUMAX_X;
		}
	}

	// 文字の削除(不要な場合削除お願いします(＞＜))
	if (GetKeyboardTrigger(DIK_BACKSPACE) || IsButtonTriggered(BUTTON_DOWN) )
	{	// 名前入力フラグの削除
		//select_moji[namechar - 1].Release();	//テクスチャ解放
		rankdata[0].selected[namechar - 1] = false;	// 入力文字のフラグをオフに
		rankdata[0].namechar[namechar-1][0] = 0;		// 文字入力フラグ初期化(あの位置へ）
		rankdata[0].namechar[namechar-1][1] = 0;
		namechar--;									// 現在入力中の文字数を減らすよ
		//rankdata[0].name_position = namechar - 1;

	}


	// 決定キーが入力された場合今のカーソル位置の文字を格納
	if (GetKeyboardTrigger(DIK_SPACE) || IsButtonTriggered(BUTTON_UP))
	{
		//if (namechar < NAMEMAX)
		{
			// 既に選択されている場合上書き処理

			/*else*/ if (namechar < NAMEMAX)
			{
				// 指定位置
				// 1フラグをtrueに
				rankdata[0].selected[namechar] = true;

				// 数字で文字を格納
				if (char_type == HIRAGANA)
				{
					rankdata[0].namechar[namechar][0] = (int)cursolewk.pos.y;
					rankdata[0].namechar[namechar][1] = (int)cursolewk.pos.x;
				}
				else
				{
					rankdata[0].namechar[namechar][0] = (int)cursolewk.pos.y + 5;
					rankdata[0].namechar[namechar][1] = (int)cursolewk.pos.x;
				}
				//	今回の決定によって5文字目が入力された場合
				if (rankdata[0].selected[NAMEMAX - 1] == true)
				{
					cursole_status = NAME_FINISH;
				}
				
				//select_moji[namechar].SetTexture(1, 10, 10);	//第二引数 ますめの数X 第3 ますめの数Y
				// 空白文字の場合の処理(空白文字入力できるかわからないので保留)

				// 文字入力されたので現在入力中の名前を加算
			}
			if (namechar < NAMEMAX)
			{
				namechar++;
				//rankdata[0].name_position = namechar;

			}
		}




	}
	PrintDebugProcess("namechar %d", namechar);

}


//********************************************************************
// void Flash_Tex(int no)
// テクスチャの点滅！
// 引数　int 戻り値 なし
//********************************************************************
void Flash_Tex(int no)
{
	//if (flash_count_switch == false)
	//{	// 減産
	//	flash_count -= (FLASH_TIME / 60.0f);
	//	if (flash_count < 0.0f)
	//	{
	//		flash_count = 0.0f;
	//		flash_count_switch = true;
	//	}
	//}
	//else
	//{
	//	flash_count += (FLASH_TIME / 60.0);
	//	if (flash_count > 1.0f)
	//	{
	//		flash_count = 1.0f;
	//		flash_count_switch = false;
	//	}
	//}
	flash_count += FLASH_TIME;
	if (name_enter == true && name_status == BEGIN || name_status == NAME_SELECT_END)
	{	// プレイヤーのスコアとランキングのスコアを比較する？
		int player_score = GetScore();
		SAVERANKING *rankinfo = GetSaveRanking(0);
		for (int i = 0; i < 5;i++, rankinfo++)
		{
			if (player_score == rankinfo->score)
			{
				flash_score = i;
			}
		}
		for (int t = 0; t < 5; t++)
		{
			ranking[flash_score].name[t].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, fabs(sinf(flash_count)) + 0.3f));
			ranking[flash_score].score[t].SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, fabs(sinf(flash_count)) + 0.3f));
		}


	}
	else
	{	// キーボードなどが表示されてるやつ
		if (cursole_status == NAME_FINISH)
		{
			name_set.SetVertex(D3DXCOLOR(1.0f,1.0f,1.0f,fabs(sinf(flash_count)) +0.3f));
		}
		else
		{
 			cursole.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f,fabs(sinf(flash_count)) +0.3f));
		}
	}
}


// ファイル読みこみ
// とりあえず
/*
順位　１２３４５６７８９１０













*/