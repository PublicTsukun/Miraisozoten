//=============================================================================
//
// ゲーム画面処理 [Ranking.cpp]
//
//=============================================================================
#include "Ranking.h"
#include "Library/Input.h"
#include "Library/Fade.h"
#include "Library/ObjectBase2D.h"
#include "Library/ObjectBase3D.h"


//ワークのインクルード
#include "workHagiwara.h"
#include "workKimura.h"
#include "workSato.h"
#include "workSon.h"
#include "workTsu.h"
#include "workUtsugi.h"
#include "workYamaguchi.h"
#include "workYamamoto.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
<<<<<<< HEAD
//RANKING2DObject        Ranking2D;
RANKING			rankingWk[RANKING_MAX];				// ランキング格納ワーク
int				rankCnt;							// 読み込んだランキングの数
//BUF				bufWk[BUFC_MAX];

//=============================================================================
// ランキング処理
//=============================================================================
void Ranking(void)
{
	// ランキング用csvファイル読み込み
	LoadRankingCsv();
	// IDの最大値を抽出する
	int max = rankingWk[0].id;	// id最大値格納用
	for (int i = 1; i < RANKING_MAX - 1; i++)
	{
		if (max < rankingWk[1].id)max = rankingWk[i].id;
	}

	// スコアを取得(一時的にスコアを6位にする)
	rankingWk[SIXTH].score = Random(0,100000);//6位のスコアに今回のスコアをぶちこむ
	rankingWk[SIXTH].id = max + 1;
	// スコアをもとに5位のスコアと比較し、5位のスコアより低ければランキング更新
	if (rankingWk[SIXTH].score >= rankingWk[FIFTH].score)
	{	// 5位よりスコアが高ければランキング更新しない
		RankingSort();
		WriteRankingCsv();
	}
	// ランキングの表示
	RANKING *ranking = &rankingWk[0];	// ポインターを初期化
	PrintDebugProcess("ID表示 : (%d)\n", ranking->id);
	PrintDebugProcess("ランク表示 : (%d)\n", ranking->rank);
	PrintDebugProcess("スコア表示 : (%d)\n", ranking->score);
}
=======
>>>>>>> a7f92b181e2235a7aa760ab3620164ba5260dc83


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitRanking(void)
{
	InitWorkHagiwara();
	InitWorkKimura();
	InitWorkSato();
	InitWorkSon();
	InitWorkTsu();
	InitWorkUtsugi();
	InitWorkYamaguchi();
	InitWorkYamamoto();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitRanking(void)
{
	UninitWorkHagiwara();
	UninitWorkKimura();
	UninitWorkSato();
	UninitWorkSon();
	UninitWorkTsu();
	UninitWorkUtsugi();
	UninitWorkYamaguchi();
	UninitWorkYamamoto();

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateRanking(void)
{
	UpdateWorkHagiwara();
	UpdateWorkKimura();
	UpdateWorkSato();
	UpdateWorkSon();
	UpdateWorkTsu();
	UpdateWorkUtsugi();
	UpdateWorkYamaguchi();
	UpdateWorkYamamoto();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawRanking(void)
{
	DrawWorkHagiwara();
	DrawWorkKimura();
	DrawWorkSato();
	DrawWorkSon();
	DrawWorkTsu();
	DrawWorkUtsugi();
	DrawWorkYamaguchi();
	DrawWorkYamamoto();

}


