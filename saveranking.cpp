//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : 萩原奈歩
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "workHagiwara.h"
#include "saveranking.h"
#include <stdio.h>
#include <stdlib.h>
#include "Library/ObjectBase2D.h"
#include <windows.h>
#include "Library/DebugProcess.h"
#include "Library/Input.h"
#include "Library/Math.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int Compare(const void *p, const void *q);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//RANKING2DObject        SaveRanking2D;
SAVERANKING			rankingWk[RANKING_MAX];				// ランキング格納ワーク
int				rankCnt;							// 読み込んだランキングの数
//BUF				bufWk[BUFC_MAX];


//=============================================================================
// ランキング用csvファイル読み込み処理
//=============================================================================
void LoadSaveRankingCsv(void)
{
	FILE *fp;							
	char buf[BUFC_MAX];					// 一時保存用(一行)
	char *tkn[RANKING_CSV_MAX];			// 一時保存用(分割した配列)
	SAVERANKING *ranking = &rankingWk[0];	// ポインターを初期化
	int skip = 1;						// 行数を指定して飛ばす(最初の1行)
	rankCnt = 0;						// カウンタ初期化

	if ((fp = fopen(RANKING_CSV, "r")) != NULL)
	{
		// ファイルの終わりまでくり返し読み込む
		while (fgets(buf, BUFC_MAX, fp) != NULL)
		{	// カンマで分割
			for (int i = 0;i < RANKING_CSV_MAX; i++)
			{
				if(i == 0)
				{
					tkn[i] = strtok(buf, ",");
				}
				else
				{
					tkn[i] = strtok(NULL, ",");
				}
			}
			// 指定した行数を飛ばす
			if (skip > 0)
			{
				skip--;
				continue;
			}
			// charをintに変換する
			ranking->id = atoi(tkn[RANKING_CSV_ID]);//同点の時に使う
			ranking->rank = atoi(tkn[RANKING_CSV_RANK]);//順位
			ranking->score = atoi(tkn[RANKING_CSV_SCORE]);//スコア

			long long name_num = atoll(tkn[RANKING_CSV_NAME]);

			for (int i = 0;i < NAME_MAX ;i++)
			{
				ranking->name[NAME_MAX - i - 1][1] = name_num % 10;
				name_num /= 10;
				ranking->name[NAME_MAX - i - 1][0] = name_num % 10;
				name_num /= 10;
			}
			rankCnt++;	//読み込み数カウント
			ranking++;	//次のデータに
		}
		fclose(fp);
	}
}

//=============================================================================
// ランキングの取得
//=============================================================================
SAVERANKING *GetSaveRanking(int no)
{
	return &rankingWk[no];
}
//=============================================================================
// 読み込んだ数取得関数
//=============================================================================
int GetSaveRankingCnt(void)
{
	return (rankCnt);
}
//=============================================================================
// ランキング用csvファイル書き込み処理
//=============================================================================
void WriteSaveRankingCsv(void)
{
	FILE *fp;
	SAVERANKING*ranking = &rankingWk[0];			//ポインタを初期化

		// csvファイル上書き
	if ((fp = fopen(RANKING_CSV, "w")) != NULL)//書き込み用
	{
		// 1行目を出力
		fprintf(fp, "id .rank,score ,name\n");
		// 各データをカンマ区切りで出力
		for (int i = 0;i < RANKING_MAX - 1;i++, ranking++)
		{	//3位までのデータを書き込む
			fprintf(fp, "%3d,%4d,%6d,", ranking->id, ranking->rank, ranking->score);
			for (int i = 0;i < NAME_MAX;i++)
			{
				fprintf(fp, "%d%d", ranking->name[i][0], ranking->name[i][1]);
			}
			fprintf(fp, "\n");
		}
		fclose(fp);
	}
	
}
//=============================================================================
// ランキング更新処理(ソート)
//=============================================================================
bool SaveRankingSort(int score)
{

	// IDの最大値を抽出する
	int max = rankingWk[0].id;	// id最大値格納用
	for (int i = 1; i < RANKING_MAX - 1; i++)
	{
		if (max < rankingWk[i].id)max = rankingWk[i].id;
	}

	rankingWk[5].id = max+1;//6位に最大IDと
	rankingWk[5].score = score;//今回取得したスコアを格納
	for (int i = 0; i < 5; i++)
	{
		rankingWk[5].name[i][0] = 2;
		rankingWk[5].name[i][1] = 6;

	}
	//その後ソート
	SAVERANKING *ranking = &rankingWk[0];					// ポインターを初期化
	int num = sizeof rankingWk / sizeof(SAVERANKING);		// 要素数を求める
	qsort(rankingWk, num, sizeof(SAVERANKING), Compare);	// クイックソート

	//ソートが終わったら 順位を更新
	for (int i = 0; i < RANKING_MAX; i++, ranking++)
	{
		ranking->rank = i + 1;

		if (i >= 1)
		{
			if (rankingWk[i].score == rankingWk[i - 1].score)
			{
				rankingWk[i].rank = rankingWk[i - 1].rank;
			}
		}
	}

	if ((rankingWk[5].score == score) && (rankingWk[5].id == max + 1))//今回ランクインできたかどうかで返り値を変更
	{
		return false;//変わっていなければ偽
	}
	else
	{
		return true;//最下位が変わっていれば真　　
	}
}


//============================================================================
//ranking の確認
//=============================================================================
int CheckRank(int Score)
{
	for (int i = 0; i < RANKING_MAX - 1; i++)
	{
		if (rankingWk[i].score == Score)
		{
			return i;
		}
	}
	return -1;
}
//============================================================================
// 比較関数処理(降順ソート)
//=============================================================================
int Compare(const void *p, const void *q)
{
	// スコアで比較
	int n = ((SAVERANKING*)q)->score - ((SAVERANKING*)p)->score;
	// スコアが同じだった場合
	if (n == 0)
	{	// idの値が大きいほうを上位にする
		int m = ((SAVERANKING*)q)->id - ((SAVERANKING*)p)->id;
		return m;
	}
	
	// int型オーバーフロー対処
	//if ((RANKING*)q > (RANKING*)p) return -1;
	//if ((RANKING*)q < (RANKING*)p) return 1;
	return n;
}
void DebugRank(void)
{
	SAVERANKING *ranking = &rankingWk[0];
	PrintDebugProcess("名前１ : (%d)(%d)\n", ranking->name[0][0], ranking->name[0][1]);
	PrintDebugProcess("名前２ : (%d)(%d)\n", ranking->name[1][0], ranking->name[1][1]);
	PrintDebugProcess("名前３ : (%d)(%d)\n", ranking->name[2][0], ranking->name[2][1]);
	PrintDebugProcess("名前４ : (%d)(%d)\n", ranking->name[3][0], ranking->name[3][1]);
	PrintDebugProcess("名前５ : (%d)(%d)\n", ranking->name[4][0], ranking->name[4][1]);
}
//********************************************************
// void Enter_the_no(int rank,int no)
// 引数　int rank(指定順位) int no(ランクに入れたい値)
//　指定された順位に指定された値を入れる
void Enter_the_no(int rank,int num,int y,int x)
{
	//rankingWk[rank].name[0][2] = {};

	rankingWk[rank].name[num][0] = y;
	rankingWk[rank].name[num][1] = x;

}
