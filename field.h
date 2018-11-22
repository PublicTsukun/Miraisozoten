//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#ifndef _FEILD_H_
#define _FEILD_H_

#include "Library/Math.h"
#include <Windows.h>



#define	WALL_SIZE_X		(1990)
#define	WALL_SIZE_Y		(1090)



#define WALL_POS_X	(0.00f)
#define WALL_POS_Y	(460.00f)
#define WALL_POS_Z	(2000.00f)




//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitField(void);
void UninitField(void);
void DrawField(void);
void UpdateField(void);


#endif