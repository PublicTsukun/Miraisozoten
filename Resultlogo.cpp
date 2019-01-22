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
#include "GameSound.h"
#include "SceneManager.h"
#include "DefeatCounter.h"
#include "GameSound.h"

//=============================================================================
// マクロ定義
//=============================================================================

class ObjectMove : public C2DObject
{
public:		//演出用
	void MoveY(float move)
	{
		this->Position.y += move;
		this->SetVertex();
	}

	void MoveX(float move)
	{
		this->Position.x += move;
		this->SetVertex();
	}

	bool Use;
	bool Move;

	Vector2 GetPosition(void)
	{
		return this->Position;
	}



};

class DETAIL
{
public:

	ObjectMove DetailBg;//背景
	ObjectMove Closs;	//かける
	ObjectMove Equal;	//イコール
	ObjectMove Knock[2];	//撃破数
	ObjectMove CharTex;	//倒したキャラ
	ObjectMove GetPoint[5];//獲得スコア

	void ScoreInit(int no);
	void ScoreUninit(void);
	void ScoreDraw(void);
	void ScoreUpdate(void);

};

//=============================================================================
// プロトタイプ宣言
//=============================================================================


//=============================================================================
// グローバル変数
//=============================================================================
C2DObject resultbg[2];		//タイトル背景
C2DObject resultscr[NUM_PLACE];
C2DObject resultlogo;
					
RenderBuffer DetailWindow;	//詳細のテクスチャの生成
C2DObject	Detail;			//詳細のテクスチャ表示用
DETAIL	ScoreDetail[DETAIL_MAX];

const char *ScoreDetailTex[] = {
	"data/TEXTURE/UI/タイトル/メニュー画面_青.png",
	"data/TEXTURE/UI/タイトル/メニュー画面_赤.png",
	"data/TEXTURE/UI/タイトル/メニュー画面_黄.png",
};

const char *CharctorTex[] = {
	"data/TEXTURE/Character/00_child.png",
	"data/TEXTURE/Character/02_otaku.png",
	"data/TEXTURE/Character/01_maid.png",

	"data/TEXTURE/Character/aa.png",
	"data/TEXTURE/Character/JK.png",
	"data/TEXTURE/Character/あめりか人.png",

	"data/TEXTURE/Character/UFO.png",
	"data/TEXTURE/Character/宇宙飛行士.png",
	"data/TEXTURE/Character/宇宙人.png",
};

int CharactorScore[] = {

	100,
	500,
	1000,

	100,
	500,
	1000,

	100,
	500,
	1000,

};

int DrawCount ;		//画面内に何枚出たか
int DetailCount;	//合計何枚表示しようとしたか

int g_maxscore;

int slotTimer;
bool slotStart;
int slotCount;
int g_score;

bool excellentf;

float DetailMove;
int   DetailTimer;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResultlogo(void)
{
	DetailWindow.Init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_X8R8G8B8);
	Detail.Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, RS_X(0.6f/2.0f), RS_Y(0.6f/2.0f));
	Detail.SetTexture(0, 0.001f, 0.001f);
	Detail.SetTexture(2, 0.001f, 0.999f);

	resultbg[0].Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, TEXTURE_RESULTBG);
	resultbg[1].Init(SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_WIDTH*1.67f/ 2, SCREEN_HEIGHT*1.67/ 2, TEXTURE_RESULTBG);

	for (int i = 0; i < NUM_PLACE; i++)
	{
		resultscr[i].Init(RESULT_SCORE_POS_X +i*	RESULT_SCORE_SIZE_X*2, RESULT_SCORE_POS_Y, RESULT_SCORE_SIZE_X, RESULT_SCORE_SIZE_Y,TEXTURE_SCORE);
	}

	slotTimer = 0;
	slotStart = false;
	slotCount = 0;
	g_score = 0;
	g_maxscore = GetScore();

	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		int number;

		number = (g_score % (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace - 1)));
		resultscr[nCntPlace].SetTexture(number, 10, 1);
	}


	resultlogo.Init(SCREEN_CENTER_X, RESULT_LOGO_SIZE_Y + 10.0f, RESULT_LOGO_SIZE_X, RESULT_LOGO_SIZE_Y, TEXTURE_RESULT_LOGO);
	resultlogo.SetVertex(RESULT_LOGO_COLOR);
	
	DrawCount = 0;

	DetailCount = 0;

	excellentf = false;
	DetailMove = 0;
	DetailTimer = 0;
	for (int i = 0; i < DETAIL_MAX; i++)
	{
		ScoreDetail[i].ScoreInit(i);
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResultlogo(void)
{
	resultbg[0].Release();
	resultbg[1].Release();

	for (int i = 0; i < NUM_PLACE; i++)
	{
		resultscr[i].Release();
	}
	resultlogo.Release();

	for (int i = 0; i < DETAIL_MAX; i++)
	{
		ScoreDetail[i].ScoreUninit();
	}

	DetailWindow.Release();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResultlogo(void)
{
		resultbg[0].Draw();
		for (int i = 0; i < NUM_PLACE; i++)
		{
			resultscr[i].Draw();
		}
		resultlogo.Draw();

		DetailWindow.BeginDraw();
		resultbg[1].Draw();

		for (int i = 0; i < DETAIL_MAX; i++)
		{
			ScoreDetail[i].ScoreDraw();
		}


		DetailWindow.EndDraw();
		Detail.Draw(DetailWindow.GetTexture());

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResultlogo(void)
{
	if (slotCount >= NUM_PLACE
		&& (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(BUTTON_UP)))
	{
		Scene::SetScene(SCENE_TITLE);
	}


	//===========================================================================
	//取得スコア表示
	//===========================================================================
	int slotadd = 0;		//スロット加算数

	slotTimer++;				//タイマー加算

	if (DetailCount == DETAIL_MAX && !slotStart)
	{
		slotStart = true;//一定時間でスロットスタート
		slotTimer = 0;
		if (slotCount < NUM_PLACE)
		{
			PlaySE(SCORE_SLOT);
		}
	}
	if (slotStart == true)//スロットが動いてるとき
	{

		for (int i = 0; i < NUM_PLACE - slotCount; i++)//指定の桁をスロット
		{

			slotadd = (int)(powf(10.0f, (float)(NUM_PLACE - i - 1)));//スロット演出
			g_score += slotadd;
			if (g_score >= (int)(powf(10.0f, NUM_PLACE + 1)))
			{
				g_score = g_maxscore % (int)(powf(10.0f, slotCount));//オーバーフローする前に戻す
			}
		}

		int number;
		int number2;

		number = (g_score % (int)(powf(10.0f, (float)(slotCount + 1)))) / (int)(powf(10.0f, (float)(slotCount)));	//指定桁確認
		number2 = (g_maxscore % (int)(powf(10.0f, (float)(slotCount + 1)))) / (int)(powf(10.0f, (float)(slotCount)));//指定桁確認

		if (slotCount < NUM_PLACE)
		{
			if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(BUTTON_UP))
			{
				slotCount = NUM_PLACE;
				StopSE(SCORE_SLOT);
				PlaySE(SCORE_DECISION);
			}
			if (slotTimer > SLOT_INTERVAL && number == number2)//演出ストップ処理
			{
				slotCount++;
				slotTimer = 0;

				if (slotCount == NUM_PLACE)
				{
					StopSE(SCORE_SLOT);
					PlaySE(SCORE_DECISION);
				}
				else
				{
					PlaySE(SLOT_STOP);
				}
			}
		}
		else if (slotCount >= NUM_PLACE)
		{
			g_score = g_maxscore;
			slotStart = false;

			if (!PlayCheckSE(SCORE_DECISION) && excellentf == false)
			{
				//PlaySE(EXCELLENT);
				PlaySE(AORI);
				excellentf = true;
			}
		}

	}
	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		int number;

		number = (g_score % (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace - 1)));
		resultscr[nCntPlace].SetTexture(number, 10, 1);
	}


	//===========================================================================
	//スコア詳細
	//===========================================================================
	DetailTimer++;

	if (DetailTimer == 60)
	{
		ScoreDetail[0].DetailBg.Move = true;
	}

	for (int i = 0; i < DETAIL_MAX; i++)
	{
		if (ScoreDetail[i].DetailBg.Move)
		{
			ScoreDetail[i].DetailBg.MoveX(-DETAIL_SPEED);

		}


		if (ScoreDetail[i].DetailBg.GetPosition().x <= SCREEN_CENTER_X
			&&ScoreDetail[i].DetailBg.Move == true)
		{
			ScoreDetail[i].DetailBg.Move = false;
			PlaySE(SLOT_STOP);
			if (ScoreDetail[i + 1].DetailBg.Use && ((i + 1) < DETAIL_MAX))
			{
				ScoreDetail[i + 1].DetailBg.Move = true;
				DrawCount++;
			}
			DetailCount++;

		}


		if (DrawCount >= 3)//3マイ出てきたらスクロール
		{
			DetailMove -= 4;
			for (int j = 0; j < DETAIL_MAX; j++)
			{
				ScoreDetail[j].DetailBg.MoveY(-4.0);

			}

			if (DetailMove == -200)
			{
				DetailMove = 0;
				DrawCount--;

			}

		}

		//スクロール処理
		if (DetailCount == DETAIL_MAX)
		{
			if (GetMouseZ() > 0)
			{
				if (ScoreDetail[0].DetailBg.GetPosition().y < 140.0)
				{
					ScoreDetail[DETAIL_MAX - i - 1].DetailBg.MoveY(GetMouseZ());//下から変えていく　上から変えるとバグる
				}
			}
			else if (GetMouseZ() < 0)
			{
				if (ScoreDetail[DETAIL_MAX - 1].DetailBg.GetPosition().y > SCREEN_HEIGHT - 140.0)
				{
					ScoreDetail[i].DetailBg.MoveY(GetMouseZ());
				}
			}
		}
		PrintDebugProcess("%f  %f\n", ScoreDetail[i].DetailBg.GetPosition().x, ScoreDetail[i].DetailBg.GetPosition().y);

		ScoreDetail[i].ScoreUpdate();
	}

}


//=========================================================
//クラス内関数
//=========================================================
//初期化
void DETAIL::ScoreInit(int no)
{
	DefeatCounter *DefeatCounter = GetDefeatCounter(0);


	DetailBg.Init(SCREEN_WIDTH + 400.0, 140 + no * 200, 400.0, 100.0, ScoreDetailTex[no % 3]);
	DetailBg.Use = true;
	DetailBg.Move = false;

	Closs.Init(SCREEN_WIDTH + 400.0, 140 + no * 200, 400.0, 100.0, "data/TEXTURE/UI/リザルト/×.png");
	Closs.Use = false;
	Closs.Move = false;

	Equal.Init(SCREEN_WIDTH + 400.0, 140 + no * 200, 400.0, 100.0, "data/TEXTURE/UI/リザルト/=.png");
	Equal.Use = false;
	Equal.Move = false;

	CharTex.Init(SCREEN_WIDTH + 100.0, 140 + no * 200, 100.0, 100.0, CharctorTex[no]);
	CharTex.Use = false;
	CharTex.Move = false;
	CharTex.SetTexture(1, 2, 1);


	for (int i = 0; i < 2; i++)
	{
		Knock[i].Init(SCREEN_WIDTH + 400.0, 140 + no * 200, 39.0, 80.0, "data/TEXTURE/UI/スコア数字.png");
		Knock[i].Use = false;
		Knock[i].Move = false;

		int num;
		num = (DefeatCounter + no)->GetCount();
		num /= pow(10, i);
		num %= 10;
		Knock[i].SetTexture(num, 10, 1);
	}

	for (int i = 0; i < 5; i++)
	{
		GetPoint[i].Init(SCREEN_WIDTH + 400.0, 140 + no * 200, 39.0, 80.0, "data/TEXTURE/UI/スコア数字.png");
		GetPoint[i].Use = false;
		GetPoint[i].Move = false;

		int num;
		num = CharactorScore[no]*(DefeatCounter + no)->GetCount();
		num /= pow(10, i);
		num %= 10;
		GetPoint[i].SetTexture(num, 10, 1);
	}
}
//終了処理
void DETAIL::ScoreUninit(void)
{
	//ObjectMove DetailBg;//背景
	//ObjectMove Closs;	//かける
	//ObjectMove Equal;	//イコール
	//ObjectMove Knock;	//撃破数
	//ObjectMove CharTex;	//倒したキャラ
	//ObjectMove GetPoint;//獲得スコア

	DetailBg.Release();
	Closs.Release();
	Equal.Release();
	CharTex.Release();

	for (int i = 0; i < 2; i++)
	{
		Knock[i].Release();
	}

	for (int i = 0; i < 5; i++)
	{
		GetPoint[i].Release();
	}
}
//描画処理
void DETAIL::ScoreDraw(void)
{
	DetailBg.Draw();
	Closs.Draw();
	Equal.Draw();
	CharTex.Draw();

	for (int i = 0; i < 2; i++)
	{
		Knock[i].Draw();
	}

	for (int i = 0; i < 5; i++)
	{
		GetPoint[i].Draw();
	}

}
//更新処理
void DETAIL::ScoreUpdate(void)
{

	Vector2 ClossPos = Vector2(CLOSS_POS_X, CLOSS_POS_Y);
	Closs.SetStatus(DetailBg.GetPosition() + ClossPos, Vector2(400.0, 100.0));
	Closs.SetVertex();
	Vector2 EqualPos = Vector2(EQUAL_POS_X, EQUAL_POS_Y);
	Equal.SetStatus(DetailBg.GetPosition() + EqualPos, Vector2(400.0, 100.0));
	Equal.SetVertex();
	Vector2 CharPos = Vector2(CHAR_POS_X, CHAR_POS_Y);
	CharTex.SetStatus(DetailBg.GetPosition() + CharPos, Vector2(100.0, 100.0));
	CharTex.SetVertex();

	for (int i = 0; i < 2; i++)
	{
		Vector2 KnockPos = Vector2(KNOCK_POS_X + KNOCK_INTER*i, KNOCK_POS_Y);
		Knock[i].SetStatus(DetailBg.GetPosition() + KnockPos, Vector2(39.0, 80.0));
		Knock[i].SetVertex();
	}

	for (int i = 0; i < 5; i++)
	{
		Vector2 GetPointPos = Vector2(GETPOINT_POS_X + GETPOINT_INTER*i, GETPOINT_POS_Y);
		GetPoint[i].SetStatus(DetailBg.GetPosition() + GetPointPos, Vector2(39.0, 80.0));
		GetPoint[i].SetVertex();
	}
}
