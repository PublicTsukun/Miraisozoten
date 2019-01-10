//=============================================================================
//
// スコア処理 [score.h]
// Author : 
//
//=============================================================================
#ifndef _RESULT_LOGO_H_
#define _RESULT_LOGO_H_


#include <Windows.h>
#include "Library/Common.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_RESULTBG		"data/TEXTURE/UI/リザルト/りざると背景.png"// 読み込むテクスチャのファイル名

#define TEXTURE_RESULT_LOGO		"data/TEXTURE/UI/リザルト/りざると.png"
#define RESULT_LOGO_SIZE_X		(260*SCREEN_SCALE)
#define	RESULT_LOGO_SIZE_Y		(65*SCREEN_SCALE)
#define RESULT_LOGO_COLOR		(0xff112233)	//「りざると」の文字色変えるのここだよ～
												//0xは固定　ff(最初の２桁)がα値
												//			11(次の２桁)がR
												//			22(次の２桁)がG
												//			33(最後の２桁)がB
												//ネットで調べたらいい感じに出てくると思う
												//１６進数２桁でそれぞれの色を決めてね

#define	TEXTURE_SCORE		"data/TEXTURE/UI/スコア数字.png"	// 読み込むテクスチャファイル名
#define	RESULT_SCORE_SIZE_X		(46.0f*SCREEN_SCALE)							// スコアの数字の幅
#define	RESULT_SCORE_SIZE_Y		(70.0f*SCREEN_SCALE)						// スコアの数字の高さ
//#define		RESULT_SCORE_SIZE_X		(92.0f*SCREEN_SCALE)
//#define		RESULT_SCORE_SIZE_Y		(140.0f*SCREEN_SCALE)

#define	RESULT_SCORE_INTERVAL_X	(0.0f)							// スコアの数字の表示間隔

#define	NUM_PLACE			(5)							// スコアの桁数 stage.hのMAX_PRICEと桁数合わせること

#define	RESULT_SCORE_POS_X			(SCREEN_CENTER_X-RESULT_SCORE_SIZE_X*4)						// スコアの表示基準位置Ｘ座標
#define	RESULT_SCORE_POS_Y			(SCREEN_HEIGHT-RESULT_SCORE_SIZE_Y-8.0f*SCREEN_SCALE)				// スコアの表示基準位置Ｙ座標
//#define RESULT_SCORE_POS_Y			(SCREEN_CENTER_Y)

#define SLOT_INTERVAL		(30)

#define DETAIL_MAX			(9)

#define	CLOSS_POS_X			(0.0f)	//×用ポジション　背景との相対座標
#define	CLOSS_POS_Y			(0.0f)

#define	EQUAL_POS_X			(0.0f)	//＝用ポジション　背景との相対座標
#define	EQUAL_POS_Y			(0.0f)

#define CHAR_POS_X			(-320.0f)
#define CHAR_POS_Y			(-10.0f)

#define KNOCK_POS_X			(-147.0f)
#define KNOCK_POS_Y			(0.0f)
#define KNOCK_INTER			(73.0f)

#define GETPOINT_POS_X		(70.0f)
#define GETPOINT_POS_Y		(0.0f)
#define GETPOINT_INTER		(65.0f)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResultlogo(void);
void UninitResultlogo(void);
void UpdateResultlogo(void);
void DrawResultlogo(void);


#endif
