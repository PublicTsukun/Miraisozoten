//=============================================================================
//
// ランキング処理 [ranking.h]
// Author : 萩原奈歩
//
//=============================================================================
#ifndef _SAVE_RANKING_H_
#define _SAVE_RANKING_H_
#include "workHagiwara.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RANKING_CSV		_T("data/EXCEL_DATA/ranking.csv")	// サンプル用画像
#define RANKING_MAX			(6)								// スコアの最大値
#define BUFC_MAX			(1024)							// スコアの最大値
#define NAME_MAX			(5)								// 名前の最大値

//*****************************************************************************
// クラス定義
//*****************************************************************************
class SAVERANKING
{
public:
	int			id;
	int			rank;
	int			score;
	int			name[NAME_MAX][2];//名前保存用[何文字目][0->子音　1->母音]
};

//*****************************************************************************
// 列挙型
//*****************************************************************************

enum
{
	RANKING_CSV_ID = 0,		// ID
	RANKING_CSV_RANK,		// 順位
	RANKING_CSV_SCORE,		// スコア
	RANKING_CSV_NAME,		//名前
	RANKING_CSV_MAX,
};

enum
{	// 順位
	FIRST = 0,		//1位
	SECOND,			//2位
	THIRD,			//3位
	FOURTH,			//4位
	FIFTH,			//5位
	SIXTH,			//6位
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
SAVERANKING *GetSaveRanking(int no);
int GetSaveRankingCnt(void);
void WriteSaveRankingCsv(void);
void LoadSaveRankingCsv(void);
void DebugRank(void);
bool SaveRankingSort(int score);

#endif