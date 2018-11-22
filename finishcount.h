//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#ifndef _FINISH_COUNT_
#define _FINISH_COUNT_


#include <Windows.h>
#include "Library/Common.h"

#define FINISHCOUNT_TEX		"data/TEXTURE/UI/カウントダウン.png"

#define FINISHLOGO_TEX		"data/TEXTURE/UI/しゅーりょー.png"



HRESULT InitFinishCount(void);
void UninitFinishCount(void);
void DrawFinishCount(void);
void UpdateFinishCount(void);


#endif