//=============================================================================
//
// タイトル処理 [title.cpp]
//
//=============================================================================
#include "titlelogo.h"
#include "Library/ObjectBase2D.h"
#include "Library/Common.h"
#include "Library/Input.h"
#include "Library/DebugProcess.h"
#include "SceneManager.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_TITLE		"data/TEXTURE/sgf01a201501112200.jpg"// 読み込むテクスチャのファイル名
#define	TEXTURE_LOGO_NAME	"data/TEXTURE/toumeititle.png"		// 読み込むタイトルロゴのファイル名
#define START_BUTTON		"data/TEXTURE/start.jpg"			// 読み込むスタートボタンのファイル名
#define SINGLE_LOGO			"data/TEXTURE/soro.jpg"				// 読み込む１人用モードロゴのファイル名
#define MULTI_LOGO			"data/TEXTURE/mauti.jpg"			// 読み込む２人用モードロゴファイル名
#define RANKING_LOGO		"data/TEXTURE/ranking.jpg"			// 読み込むランキングロゴのファイル名
#define CURSOR_LOGO			"data/TEXTURE/toumeiyazirusi.png"	// 読み込むカーソルロゴのファイル名

#define	TITLE_LOGO_NAMEPOS_X	(SCREEN_CENTER_X)		// タイトルロゴの位置(X座標)320
#define	TITLE_LOGO_NAMEPOS_Y	(RelativeSY(0.25))		// タイトルロゴの位置(Y座標)40
#define TITLE_LOGO_NAMESX		(RelativeSX(0.75)/2)	//タイトルロゴのサイズ(X座標)
#define TITLE_LOGO_NAMESY		(RelativeSY(0.3)/2)		//タイトルロゴのサイズ(Y座標)
//#define	TITLE_LOGO_WIDTH		(1000)		// タイトルロゴの幅640
//#define	TITLE_LOGO_HEIGHT		(300)		// タイトルロゴの高さ640

#define	START_POS_X				(400)		// スタートボタンの位置(X座標)
#define	START_POS_Y				(400)		// スタートボタンの位置(Y座標)
#define	START_WIDTH				(480)		// スタートボタンの幅
#define	START_HEIGHT			(120)		// スタートボタンの高さ

#define	SINGLE_POS_X			(400)		// １人用モードロゴの位置(X座標)
#define	SINGLE_POS_Y			(240)		// １人用モードロゴの位置(Y座標)
#define	SINGLE_WIDTH			(70)		// １人用モードロゴの幅
#define	SINGLE_HEIGHT			(70)		// １人用モードロゴ高さ

#define	MULTI_POS_X				(400)		// 2人用モードロゴの位置(X座標)
#define	MULTI_POS_Y				(400)		// 2人用モードロゴの位置(Y座標)
#define	MULTI_WIDTH				(70)		// 2人用モードロゴの幅
#define	MULTI_HEIGHT			(70)		// 2人用モードロゴ高さ

#define	RANKING_POS_X			(400)		// ランキングロゴの位置(X座標)
#define	RANKING_POS_Y			(500)		// ランキングロゴの位置(Y座標)
#define	RANKING_WIDTH			(70)		// ランキングロゴの幅
#define	RANKING_HEIGHT			(70)		// ランキングロゴ高さ

#define	CURSOR_POS_X			(250)		// カーソルロゴの位置(X座標)
#define	CURSOR_POS_Y			(240)		// カーソルロゴの位置(Y座標)
#define	CURSOR_WIDTH			(50)		// カーソルロゴの幅
#define	CURSOR_HEIGHT			(20)		// カーソルロゴ高さ

#define	COUNT_APPERA_START		(60)		// スタートボタン出現までの時間
#define	INTERVAL_DISP_START		(60)		// スタートボタン点滅の時間

#define	COUNT_WAIT_DEMO			(60 * 5)	// デモまでの待ち時間

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// グローバル変数
//=============================================================================
C2DObject titlebg;		//タイトル背景
C2DObject titlename;	//タイトルネーム
C2DObject startbutton;	//スタートボタン
C2DObject singlemode;	//シングルモード
C2DObject multimode;	//マルチモード
C2DObject rankingmode;	//ランキング
C2DObject cursor;		//カーソル
bool pop;				//popの初期化
int position;			//カーソルの位置　positionの宣言
int x;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitlelogo(void)
{
	pop = true;
	x = 0;

	titlebg.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, TEXTURE_TITLE);
	titlename.Init(TITLE_LOGO_NAMEPOS_X, TITLE_LOGO_NAMEPOS_Y, TITLE_LOGO_NAMESX, TITLE_LOGO_NAMESY, TEXTURE_LOGO_NAME);
	startbutton.Init(START_POS_X, START_POS_Y, START_WIDTH, START_HEIGHT, START_BUTTON);
	singlemode.Init(SINGLE_POS_X, SINGLE_POS_Y, SINGLE_WIDTH, SINGLE_HEIGHT, SINGLE_LOGO);
	multimode.Init(MULTI_POS_X, MULTI_POS_Y, MULTI_WIDTH, MULTI_HEIGHT, MULTI_LOGO);
	rankingmode.Init(RANKING_POS_X, RANKING_POS_Y, RANKING_WIDTH, RANKING_HEIGHT, RANKING_LOGO);
	cursor.Init(CURSOR_POS_X, CURSOR_POS_Y, CURSOR_WIDTH, CURSOR_HEIGHT, CURSOR_LOGO);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitlelogo(void)
{
		titlebg.Release();
		titlename.Release();
		startbutton.Release();
		singlemode.Release();
		multimode.Release();
		rankingmode.Release();
		cursor.Release();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitlelogo(void)
{
		titlebg.Draw();
		titlename.Draw();

		//スタートボタンが表示されている状態でEnterを押すとメニューが表示される
		if (pop == true)
		{
			startbutton.Draw();
		}

		if (pop == false)
		{
			singlemode.Draw();
			multimode.Draw();
			rankingmode.Draw();
			cursor.Draw();
		}
}


//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitlelogo(void)
{

	//↓入力でカーソルを下に移動
	if (GetKeyboardTrigger(DIK_DOWN))
	{
		x = x + 1;
	}

	//カーソルが一番下にある状態で↓入力すると一番上に戻る
	if (x >= CURSORMAX)
	{
		x = 0;
	}

	//↑入力でカーソルを上に移動
	if (GetKeyboardTrigger(DIK_UP))
	{
		x = x - 1;
	}

	//カーソルが一番上にある状態で↑入力すると一番下に戻る
	if (x < 0)
	{
		x = CURSORMAX-1;
	}
	
	//デバッグ表示
	PrintDebugProcess("x : (%d)\n", x);

	switch (x)//カーソルの座標に各モードロゴのＹ座標を合わせる
	{
	case SINGLE:
	{
		cursor.SetStatus(CURSOR_POS_X, SINGLE_POS_Y, CURSOR_WIDTH, CURSOR_HEIGHT);
		break;
	}

	case MULTI:
	{
		cursor.SetStatus(CURSOR_POS_X, MULTI_POS_Y, CURSOR_WIDTH, CURSOR_HEIGHT);
		break;
	}

	case RANKING:
	{
		cursor.SetStatus(CURSOR_POS_X, RANKING_POS_Y, CURSOR_WIDTH, CURSOR_HEIGHT);
		break;
	}
	default:
		break;
	}
	cursor.SetVertex();//ポリゴンを反映

	//ゲーム画面に移行
	if (GetKeyboardTrigger(DIK_RETURN)&& pop == false)
	{
		if(x == SINGLE)
		{
			Scene::SetScene(SCENE_GAME);
		}

		else if (x == MULTI)
		{
			Scene::SetScene(SCENE_GAME);
		}

		//リザルト(ランキング)画面に移行
		else if (x == RANKING)
		{
			Scene::SetScene(SCENE_RESULT);
		}
	}

	else if (GetKeyboardTrigger(DIK_RETURN) && pop == true)
	{
		pop = false;
	}

}
