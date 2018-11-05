//=============================================================================
//
// タイトル処理 [title.h]
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "Library/Math.h"
#include <Windows.h>

enum cursor { SINGLE,MULTI,RANKING,CURSORMAX };
//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitTitlelogo(void);
void UninitTitlelogo(void);
void DrawTitlelogo(void);
void UpdateTitlelogo(void);
#endif
