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
#define	TEXTURE_SCORE		"data/TEXTURE/スコア数字.png"	// 読み込むテクスチャファイル名
#define	RESULT_SCORE_SIZE_X		(50.0f*SCREEN_SCALE)							// スコアの数字の幅
#define	RESULT_SCORE_SIZE_Y		(75.0f*SCREEN_SCALE)						// スコアの数字の高さ
#define	RESULT_SCORE_INTERVAL_X	(0.0f)							// スコアの数字の表示間隔

#define	NUM_PLACE			(5)							// スコアの桁数 stage.hのMAX_PRICEと桁数合わせること

#define	RESULT_SCORE_POS_X			(SCREEN_CENTER_X-RESULT_SCORE_SIZE_X*NUM_PLACE)						// スコアの表示基準位置Ｘ座標
#define	RESULT_SCORE_POS_Y			(RESULT_SCORE_SIZE_Y+(5.0f+RESULT_LOGO_SIZE_Y*2)*SCREEN_SCALE)				// スコアの表示基準位置Ｙ座標

#define SLOT_INTERVAL		(30)


#define	TEXTURE_RESULTBG		"data/TEXTURE/sgf01a201501112200.jpg"// 読み込むテクスチャのファイル名

#define TEXTURE_RESULT_LOGO		"data/TEXTURE/ranking.jpg"
#define RESULT_LOGO_SIZE_X		(RelativeSX(0.75f)/2)
#define	RESULT_LOGO_SIZE_Y		(75.0f*SCREEN_SCALE)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResultlogo(void);
void UninitResultlogo(void);
void UpdateResultlogo(void);
void DrawResultlogo(void);


#endif
