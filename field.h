//=============================================================================
//
// フィールド処理 [field.cpp]
//
//=============================================================================
#ifndef _FEILD_H_
#define _FEILD_H_

#include "Library/Math.h"
#include <Windows.h>


#define	GROUND_SIZE_X		(1000)
#define	GROUND_SIZE_Y		(1000)
#define GROUND_POS_X		(0)
#define GROUND_POS_Y		(0)
#define GROUND_POS_Z		(GROUND_SIZE_Y)
#define GROUND_ROT			(PI/2)

#define	WALL_SIZE_X		(1000)
#define	WALL_SIZE_Y		(1000)

#define LEFTWALL_POS_X	(-GROUND_SIZE_X)
#define LEFTWALL_POS_Y	(WALL_SIZE_Y)
#define LEFTWALL_POS_Z	(GROUND_POS_Z)
#define LEFTWALL_ROT	(-PI/2)

#define RIGHTWALL_POS_X	(GROUND_SIZE_X)
#define RIGHTWALL_POS_Y	(WALL_SIZE_Y)
#define RIGHTWALL_POS_Z	(GROUND_POS_Z)
#define RIGHTWALL_ROT	(PI/2)

#define BACKWALL_POS_X	(GROUND_POS_X)
#define BACKWALL_POS_Y	(WALL_SIZE_Y)
#define BACKWALL_POS_Z	(GROUND_SIZE_Y)


#define	CEILING_SIZE_X		(1000)
#define	CEILING_SIZE_Y		(1000)
#define CEILING_POS_X		(GROUND_POS_X)
#define CEILING_POS_Y		(WALL_SIZE_X * 2)
#define CEILING_POS_Z		(GROUND_POS_Z)
#define CEILING_ROT			(PI/2)


//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitField(void);
void UninitField(void);
void DrawField(void);

#endif