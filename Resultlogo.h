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


#define	TEXTURE_SCORE		"data/TEXTURE/UI/スコア数字.png"	// 読み込むテクスチャファイル名
#define	RESULT_SCORE_SIZE_X		(46.0f*SCREEN_SCALE)							// スコアの数字の幅
#define	RESULT_SCORE_SIZE_Y		(70.0f*SCREEN_SCALE)						// スコアの数字の高さ
#define	RESULT_SCORE_INTERVAL_X	(0.0f)							// スコアの数字の表示間隔

#define	NUM_PLACE			(5)							// スコアの桁数 stage.hのMAX_PRICEと桁数合わせること

#define	RESULT_SCORE_POS_X			(SCREEN_CENTER_X-RESULT_SCORE_SIZE_X*4)						// スコアの表示基準位置Ｘ座標
#define	RESULT_SCORE_POS_Y			(SCREEN_HEIGHT-RESULT_SCORE_SIZE_Y-8.0f*SCREEN_SCALE)				// スコアの表示基準位置Ｙ座標

#define SLOT_INTERVAL		(30)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResultlogo(void);
void UninitResultlogo(void);
void UpdateResultlogo(void);
void DrawResultlogo(void);


#endif
