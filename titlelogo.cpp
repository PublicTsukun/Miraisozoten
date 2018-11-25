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
#include "GameSound.h"


//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_TITLE		"data/TEXTURE/UI/タイトル/タイトル背景.jpg"// 読み込むテクスチャのファイル名
#define	TEXTURE_LOGO_NAME	"data/TEXTURE/UI/タイトル/タイトル.png"		// 読み込むタイトルロゴのファイル名
#define START_BUTTON		"data/TEXTURE/UI/タイトル/ぼたんをおしてね.png"			// 読み込むスタートボタンのファイル名
#define SINGLE_LOGO			"data/TEXTURE/UI/タイトル/ひとりであそぶ.png"				// 読み込む１人用モードロゴのファイル名
#define MULTI_LOGO			"data/TEXTURE/UI/タイトル/ふたりであそぶ.png"			// 読み込む２人用モードロゴファイル名
#define RANKING_LOGO		"data/TEXTURE/UI/タイトル/らんきんぐ.png"			// 読み込むランキングロゴのファイル名
#define CURSOR_LOGO			"data/TEXTURE/UI/タイトル/カーソル.png"	// 読み込むカーソルロゴのファイル名

//#define	TITLE_LOGO_WIDTH		(1000)		// タイトルロゴの幅640
//#define	TITLE_LOGO_HEIGHT		(300)		// タイトルロゴの高さ640

#define	START_POS_X				(450*SCREEN_SCALE)		// スタートボタンの位置(X座標)
#define	START_POS_Y				(640*SCREEN_SCALE)		// スタートボタンの位置(Y座標)
#define	START_WIDTH				(390*SCREEN_SCALE)		// スタートボタンの幅
#define	START_HEIGHT			(90*SCREEN_SCALE)		// スタートボタンの高さ

#define	SINGLE_POS_X			(450*SCREEN_SCALE)		// １人用モードロゴの位置(X座標)
#define	SINGLE_POS_Y			(180*SCREEN_SCALE)		// １人用モードロゴの位置(Y座標)
#define	SINGLE_WIDTH			(312*SCREEN_SCALE)		// １人用モードロゴの幅
#define	SINGLE_HEIGHT			(72*SCREEN_SCALE)		// １人用モードロゴ高さ

#define	MULTI_POS_X				(450*SCREEN_SCALE)		// 2人用モードロゴの位置(X座標)
#define	MULTI_POS_Y				(380*SCREEN_SCALE)		// 2人用モードロゴの位置(Y座標)
#define	MULTI_WIDTH				(320*SCREEN_SCALE)		// 2人用モードロゴの幅
#define	MULTI_HEIGHT			(72*SCREEN_SCALE)		// 2人用モードロゴ高さ

#define	RANKING_POS_X			(450*SCREEN_SCALE)		// ランキングロゴの位置(X座標)
#define	RANKING_POS_Y			(580*SCREEN_SCALE)		// ランキングロゴの位置(Y座標)
#define	RANKING_WIDTH			(312*SCREEN_SCALE)		// ランキングロゴの幅
#define	RANKING_HEIGHT			(72*SCREEN_SCALE)		// ランキングロゴ高さ

#define	CURSOR1_POS_X			(MULTI_POS_X-MULTI_WIDTH-60)		// カーソルロゴの位置(X座標)
#define	CURSOR1_POS_Y			(240*SCREEN_SCALE)		// カーソルロゴの位置(Y座標)
#define	CURSOR2_POS_X			(MULTI_POS_X+MULTI_WIDTH+60)		// カーソルロゴの位置(X座標)
#define	CURSOR2_POS_Y			(240*SCREEN_SCALE)		// カーソルロゴの位置(Y座標)
#define	CURSOR_WIDTH			(80*SCREEN_SCALE)		// カーソルロゴの幅
#define	CURSOR_HEIGHT			(80*SCREEN_SCALE)		// カーソルロゴ高さ


#define	COUNT_APPERA_START		(30*60)		// スタートボタン出現までの時間 秒*フレーム
#define	INTERVAL_DISP_START		(60)		// スタートボタン点滅の時間

#define	COUNT_WAIT_DEMO			(60 * 5)	// デモまでの待ち時間

#define TITLE_SOUND_MAX				(4)

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void SetScale(int no);

//=============================================================================
// グローバル変数
//=============================================================================
C2DObject titlebg;		//タイトル背景
C2DObject titlename;	//タイトルネーム
C2DObject startbutton;	//スタートボタン
C2DObject singlemode;	//シングルモード
C2DObject multimode;	//マルチモード
C2DObject rankingmode;	//ランキング
C2DObject cursor[2];		//カーソル
bool pop;				//popの初期化
int position;			//カーソルの位置　positionの宣言
int x;

int flagCount;

float	ButtonAlpha;

const char *MenuBgTex[] = {
	"data/TEXTURE/UI/タイトル/メニュー画面_青.png",
	"data/TEXTURE/UI/タイトル/メニュー画面_赤.png",
	"data/TEXTURE/UI/タイトル/メニュー画面_黄.png",
};


const Vector2 MenuBgPos[] = {
	Vector2(SINGLE_POS_X,SINGLE_POS_Y),
	Vector2(MULTI_POS_X,MULTI_POS_Y),
	Vector2(RANKING_POS_X,RANKING_POS_Y)
};

const Vector2 MenuBgSize[] = {
	Vector2(SINGLE_WIDTH+100,SINGLE_HEIGHT+20),
	Vector2(MULTI_WIDTH+92,MULTI_HEIGHT+20),
	Vector2(RANKING_WIDTH+100,RANKING_HEIGHT+20)
};

C2DObject MenuBg[3];

float Scale[3] = { 1.0f,1.0f,1.0f };


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitlelogo(void)
{
	pop = true;
	x = 0;
	flagCount = 0;

	titlebg.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, TEXTURE_TITLE);
	titlename.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y-60, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, TEXTURE_LOGO_NAME);

	startbutton.Init(START_POS_X, START_POS_Y, START_WIDTH, START_HEIGHT, START_BUTTON);
	singlemode.Init(SINGLE_POS_X, SINGLE_POS_Y, SINGLE_WIDTH, SINGLE_HEIGHT, SINGLE_LOGO);
	multimode.Init(MULTI_POS_X, MULTI_POS_Y, MULTI_WIDTH, MULTI_HEIGHT, MULTI_LOGO);
	rankingmode.Init(RANKING_POS_X, RANKING_POS_Y, RANKING_WIDTH, RANKING_HEIGHT, RANKING_LOGO);

	cursor[0].Init(CURSOR1_POS_X, CURSOR1_POS_Y, CURSOR_WIDTH, CURSOR_HEIGHT, CURSOR_LOGO);
	cursor[1].Init(CURSOR2_POS_X, CURSOR2_POS_Y, CURSOR_WIDTH, CURSOR_HEIGHT, CURSOR_LOGO);

	for (int i = 0; i < 3; i++)
	{
		MenuBg[i].Init(MenuBgPos[i].x, MenuBgPos[i].y, MenuBgSize[i].x, MenuBgSize[i].y, MenuBgTex[i]);
	}
	
	ButtonAlpha = 0.0f;
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

	cursor[0].Release();
	cursor[1].Release();

	for (int i = 0; i < 3; i++)
	{
		MenuBg[i].Release();
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitlelogo(void)
{
		titlebg.Draw();

		//スタートボタンが表示されている状態でEnterを押すとメニューが表示される
		if (pop == true)
		{
			startbutton.Draw();
			titlename.Draw();
		}

		if (pop == false)
		{
			for (int i = 0; i < 3; i++)
			{
				MenuBg[i].Draw();
			}

			singlemode.Draw();
			multimode.Draw();
			rankingmode.Draw();
			cursor[0].Draw();
			cursor[1].Draw();

		}
}


//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitlelogo(void)
{

	if (pop == false)//選択画面の時
	{
		flagCount++;//カウントを進めて
		if (flagCount >= COUNT_APPERA_START)//もしカウントが一定に達したら
		{
			pop = true;//スタートボタンに戻る
			flagCount = 0;//カウントリセット
			x = 0;//矢印は上に
		}
		PrintDebugProcess("flagCount: (%d)\n", flagCount);



		//↓入力でカーソルを下に移動
		if (GetKeyboardTrigger(DIK_DOWN))
		{
			x = x + 1;
			flagCount = 0;//カウントリセット
			PlaySE(CURSOL);

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
			flagCount = 0;//カウントリセット
			PlaySE(CURSOL);

		}

		//カーソルが一番上にある状態で↑入力すると一番下に戻る
		if (x < 0)
		{
			x = CURSORMAX - 1;
		}

		//デバッグ表示
		PrintDebugProcess("x : (%d)\n", x);
	}
	switch (x)//カーソルの座標に各モードロゴのＹ座標を合わせる
	{
	case SINGLE:
	{
		cursor[0].SetStatus(CURSOR1_POS_X, SINGLE_POS_Y+50, CURSOR_WIDTH, CURSOR_HEIGHT);
		cursor[1].SetStatus(CURSOR2_POS_X, SINGLE_POS_Y+50, CURSOR_WIDTH, CURSOR_HEIGHT);
		break;
	}

	case MULTI:
	{
		cursor[0].SetStatus(CURSOR1_POS_X, MULTI_POS_Y+50, CURSOR_WIDTH, CURSOR_HEIGHT);
		cursor[1].SetStatus(CURSOR2_POS_X, MULTI_POS_Y+50, CURSOR_WIDTH, CURSOR_HEIGHT);
		break;
	}

	case RANKING:
	{
		cursor[0].SetStatus(CURSOR1_POS_X, RANKING_POS_Y+50, CURSOR_WIDTH, CURSOR_HEIGHT);
		cursor[1].SetStatus(CURSOR2_POS_X, RANKING_POS_Y+50, CURSOR_WIDTH, CURSOR_HEIGHT);
		break;
	}
	default:
		break;
	}
	SetScale(x);

	for (int i = 0; i < 2; i++)
	{
		cursor[i].SetTexture(x,3,1);
	}

	cursor[1].SetVertex();
	cursor[0].SetVertex(0, Vector2((1.0f / 3.0f)*(x + 1), 0.0f));
	cursor[0].SetVertex(1, Vector2((1.0f / 3.0f)*x, 0.0f));
	cursor[0].SetVertex(2, Vector2((1.0f / 3.0f)*(x + 1), 1.0f));
	cursor[0].SetVertex(3, Vector2((1.0f / 3.0f)*x, 1.0f));


	//ゲーム画面に移行
	if (GetKeyboardTrigger(DIK_RETURN)&& pop == false)
	{

		PlaySE(DECIDE);

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
			Scene::SetScene(SCENE_RANKING);
		}
	}

	else if (GetKeyboardTrigger(DIK_RETURN) && pop == true)
	{
		pop = false;
		PlaySE(MODE);
	}


	ButtonAlpha += 0.06;
	startbutton.SetVertex(D3DXCOLOR(1.0f, 1.0f, 1.0f, fabs(sinf(ButtonAlpha)) + 0.3f));
}

void SetScale(int no)
{
	for (int i = 0; i < 3; i++)
	{
		if (i == no)
		{
			Scale[i] += 0.02f;

			if (Scale[i] >= 1.0f)
			{
				Scale[i] = 1.0f;
			}
		}
		else
		{
			Scale[i] -= 0.01f;
		
			if (Scale[i] <= 0.8f)
			{
				Scale[i] = 0.8f;
			}
		
		}
		PrintDebugProcess("Scale[%d] %f\n", i, Scale[i]);
	}



		singlemode.SetStatus(Scale[0],0.0f);
		multimode.SetStatus(Scale[1], 0.0f);
		rankingmode.SetStatus(Scale[2], 0.0f);
		MenuBg[0].SetStatus(Scale[0], 0.0f);
		MenuBg[1].SetStatus(Scale[1], 0.0f);
		MenuBg[2].SetStatus(Scale[2], 0.0f);

	
}